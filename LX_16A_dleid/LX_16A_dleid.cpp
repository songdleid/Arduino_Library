/*
  LX_16A_dleid
  Created:  2024.4.15
  Author:   宋隽颢

  MIT License
  Copyright (c) 2023 MicroBeaut
*/

#include "LX_16A_dleid.h"

LX_16A_dleid::LX_16A_dleid(HardwareSerial &SerialX) : serial_port(SerialX)
{
}

// 校验和
byte LX_16A_dleid::LobotCheckSum(byte buf[])
{
  byte i;
  uint16_t temp = 0;
  for (i = 2; i < buf[3] + 2; i++)
  {
    temp += buf[i];
  }
  temp = ~temp;
  i = (byte)temp;
  return i;
}

// 解析接收到的数据包信息，并返回
int LX_16A_dleid::LobotSerialServoReceiveHandle(byte *ret)
{
  bool frameStarted = false;
  bool receiveFinished = false;
  byte frameCount = 0;
  byte dataCount = 0;
  byte dataLength = 2;
  byte rxBuf;
  byte recvBuf[32];
  byte i;

  while (serial_port.available())
  {
    rxBuf = serial_port.read();
    delayMicroseconds(100);
    if (!frameStarted)
    {
      if (rxBuf == LOBOT_SERVO_FRAME_HEADER)
      {
        frameCount++;
        if (frameCount == 2)
        {
          frameCount = 0;
          frameStarted = true;
          dataCount = 1;
        }
      }
      else
      {
        frameStarted = false;
        dataCount = 0;
        frameCount = 0;
      }
    }
    if (frameStarted)
    {
      recvBuf[dataCount] = (uint8_t)rxBuf;
      if (dataCount == 3)
      {
        dataLength = recvBuf[dataCount];
        if (dataLength < 3 || dataCount > 7)
        {
          dataLength = 2;
          frameStarted = false;
        }
      }
      dataCount++;
      if (dataCount == dataLength + 3)
      {

        if (LobotCheckSum(recvBuf) == recvBuf[dataCount - 1])
        {

          frameStarted = false;
          memcpy(ret, recvBuf + 4, dataLength);
          return 1;
        }
        return -1;
      }
    }
  }
}
  // 写入舵机ID
  void LX_16A_dleid::LobotSerialServoSetID(uint8_t oldID, uint8_t newID)
  {
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = oldID;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_ID_WRITE;
    buf[5] = newID;
    buf[6] = LobotCheckSum(buf);
    serial_port.write(buf, 7);
  }

  // 控制舵机转动
  void LX_16A_dleid::LobotSerialServoMove(uint8_t id, int16_t position, uint16_t time)
  {
    byte buf[10];
    if (position < 0)
      position = 0;
    if (position > 1000)
      position = 1000;
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 7;
    buf[4] = LOBOT_SERVO_MOVE_TIME_WRITE;
    buf[5] = GET_LOW_BYTE(position);
    buf[6] = GET_HIGH_BYTE(position);
    buf[7] = GET_LOW_BYTE(time);
    buf[8] = GET_HIGH_BYTE(time);
    buf[9] = LobotCheckSum(buf);
    serial_port.write(buf, 10);
  }

  // 读取ID
  int LX_16A_dleid::LobotSerialServoReadID()
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = ID_ALL; // ID_ALL为254，表示向所有舵机进行广播，可用于读取未知ID的舵机信息
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_ID_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
      ret = (int16_t)BYTE_TO_HW(0x00, buf[1]);
    else
      ret = -2048;
    return ret;
  }
  // 读取舵机位置
  int LX_16A_dleid::LobotSerialServoReadPosition(uint8_t id)
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_POS_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
      ret = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
    else
      ret = -2048;
    return ret;
  }

  // 读取偏差
  int LX_16A_dleid::LobotSerialServoReadDev(uint8_t id)
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_ANGLE_OFFSET_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
      ret = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
    else
      ret = -2048;
    return ret;
  }
  // 读取转动范围
  int retL;
  int retH;
  int LX_16A_dleid::LobotSerialServoReadAngleRange(uint8_t id)
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_ANGLE_LIMIT_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
    {
      retL = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
      retH = (int16_t)BYTE_TO_HW(buf[4], buf[3]);
    }
    else
      ret = -2048;
    return ret;
  }
  // 读取电压
  int LX_16A_dleid::LobotSerialServoReadVin(uint8_t id)
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_VIN_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
      ret = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
    else
      ret = -2049;

    return ret;
  }

  // 读取电压范围
  int vinL;
  int vinH;
  int LX_16A_dleid::LobotSerialServoReadVinLimit(uint8_t id)
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_VIN_LIMIT_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
    {
      vinL = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
      vinH = (int16_t)BYTE_TO_HW(buf[4], buf[3]);
    }
    else
      ret = -2048;
    return ret;
  }

  // 读取温度报警阈值
  int LX_16A_dleid::LobotSerialServoReadTempLimit(uint8_t id)
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_TEMP_MAX_LIMIT_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
      ret = (int16_t)BYTE_TO_HW(0x00, buf[1]);
    else
      ret = -2049;

    return ret;
  }

  // 读取温度
  int LX_16A_dleid::LobotSerialServoReadTemp(uint8_t id)
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_TEMP_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
      ret = (int16_t)BYTE_TO_HW(0x00, buf[1]);
    else
      ret = -2049;

    return ret;
  }

  // 读取舵机状态
  int LX_16A_dleid::LobotSerialServoReadLoadOrUnload(uint8_t id)
  {
    int count = 10000;
    int ret;
    byte buf[6];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_READ;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);

    while (serial_port.available())
      serial_port.read();

    while (!serial_port.available())
    {
      count -= 1;
      if (count < 0)
        return -2048;
    }

    if (LobotSerialServoReceiveHandle(buf) > 0)
      ret = (int16_t)BYTE_TO_HW(0x00, buf[1]);
    else
      ret = -2049;

    return ret;
  }
  // 停止转动
  void LX_16A_dleid::LobotSerialServoStopMove(uint8_t id)
  {
    byte buf[6];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 3;
    buf[4] = LOBOT_SERVO_MOVE_STOP;
    buf[5] = LobotCheckSum(buf);
    serial_port.write(buf, 6);
  }
  // 设置舵机模式
  void LX_16A_dleid::LobotSerialServoSetMode(uint8_t id, uint8_t Mode, int16_t Speed)
  {
    byte buf[10];

    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 7;
    buf[4] = LOBOT_SERVO_OR_MOTOR_MODE_WRITE;
    buf[5] = Mode;
    buf[6] = 0;
    buf[7] = GET_LOW_BYTE((uint16_t)Speed);
    buf[8] = GET_HIGH_BYTE((uint16_t)Speed);
    buf[9] = LobotCheckSum(buf);

    serial_port.write(buf, 10);
  }

  // 舵机上电
  void LX_16A_dleid::LobotSerialServoLoad(uint8_t id)
  {
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
    buf[5] = 1;
    buf[6] = LobotCheckSum(buf);

    serial_port.write(buf, 7);
  }
  // 舵机掉电
  void LX_16A_dleid::LobotSerialServoUnload(uint8_t id)
  {
    byte buf[7];
    buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
    buf[2] = id;
    buf[3] = 4;
    buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
    buf[5] = 0;
    buf[6] = LobotCheckSum(buf);

    serial_port.write(buf, 7);
  }
