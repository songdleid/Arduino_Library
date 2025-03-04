/*

*/

#ifndef OleidLX16A_H
#define OleidLX16A_H

#include "Arduino.h"

#define GET_LOW_BYTE(A) (uint8_t)((A))
//宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
//宏函数 获得A的高八位
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//宏函数 以A为高八位 B为低八位 合并为16位整形

#define ID_ALL 254  //ID为254时，会向所有舵机进行广播，可用于读取未知ID的舵机信息

#define LOBOT_SERVO_FRAME_HEADER         0x55
#define LOBOT_SERVO_MOVE_TIME_WRITE      1
#define LOBOT_SERVO_MOVE_TIME_READ       2
#define LOBOT_SERVO_MOVE_TIME_WAIT_WRITE 7
#define LOBOT_SERVO_MOVE_TIME_WAIT_READ  8
#define LOBOT_SERVO_MOVE_START           11
#define LOBOT_SERVO_MOVE_STOP            12
#define LOBOT_SERVO_ID_WRITE             13
#define LOBOT_SERVO_ID_READ              14
#define LOBOT_SERVO_ANGLE_OFFSET_ADJUST  17
#define LOBOT_SERVO_ANGLE_OFFSET_WRITE   18
#define LOBOT_SERVO_ANGLE_OFFSET_READ    19
#define LOBOT_SERVO_ANGLE_LIMIT_WRITE    20
#define LOBOT_SERVO_ANGLE_LIMIT_READ     21
#define LOBOT_SERVO_VIN_LIMIT_WRITE      22
#define LOBOT_SERVO_VIN_LIMIT_READ       23
#define LOBOT_SERVO_TEMP_MAX_LIMIT_WRITE 24
#define LOBOT_SERVO_TEMP_MAX_LIMIT_READ  25
#define LOBOT_SERVO_TEMP_READ            26
#define LOBOT_SERVO_VIN_READ             27
#define LOBOT_SERVO_POS_READ             28
#define LOBOT_SERVO_OR_MOTOR_MODE_WRITE  29
#define LOBOT_SERVO_OR_MOTOR_MODE_READ   30
#define LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE 31
#define LOBOT_SERVO_LOAD_OR_UNLOAD_READ  32
#define LOBOT_SERVO_LED_CTRL_WRITE       33
#define LOBOT_SERVO_LED_CTRL_READ        34
#define LOBOT_SERVO_LED_ERROR_WRITE      35
#define LOBOT_SERVO_LED_ERROR_READ       36

class LX_16A_dleid
{
public:
    LX_16A_dleid(HardwareSerial &SerialX = Serial);

  // 写入舵机ID
  void LobotSerialServoSetID(uint8_t oldID, uint8_t newID); 

  // 控制舵机转动
  void LobotSerialServoMove(uint8_t id, int16_t position, uint16_t time);

  // 读取ID
  int LobotSerialServoReadID();

  // 读取舵机位置
  int LobotSerialServoReadPosition(uint8_t id);

  // 读取偏差
  int LobotSerialServoReadDev(uint8_t id);

  // 读取转动范围
  int LobotSerialServoReadAngleRange(uint8_t id);

  // 读取电压
  int LobotSerialServoReadVin(uint8_t id);

  // 读取电压范围
  int LobotSerialServoReadVinLimit(uint8_t id);

  // 读取温度报警阈值
  int LobotSerialServoReadTempLimit(uint8_t id);

  // 读取温度
  int LobotSerialServoReadTemp(uint8_t id);

  // 读取舵机状态
  int LobotSerialServoReadLoadOrUnload(uint8_t id);

  // 停止转动
  void LobotSerialServoStopMove(uint8_t id);

  // 设置舵机模式
  void LobotSerialServoSetMode(uint8_t id, uint8_t Mode, int16_t Speed);


  // 舵机上电
  void LobotSerialServoLoad(uint8_t id);

  // 舵机掉电
  void LobotSerialServoUnload(uint8_t id);
private: 
    HardwareSerial &serial_port;

    int LobotSerialServoReceiveHandle(byte *ret) ;
    byte LobotCheckSum(byte buf[]);
};


#endif // FINITESTATE_H