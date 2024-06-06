/*
  OLED_DLEID.cpp
  Created:  2024.4.15
  Author:   宋隽颢

  MIT License
  Copyright (c) 2023 MicroBeaut
*/

#include "OledDleid.h"

#define OLED_RESET 4
/**
 * @brief OledDleid 构造函数
 *
 * 初始化 OledDleid 对象，设置 OLED 显示屏的宽度、高度、TWI 接口指针、I2C 地址、复位引脚、电源切换模式和时钟参数。
 *
 * @param width OLED 显示屏的宽度
 * @param height OLED 显示屏的高度
 * @param twi TWI 接口指针，默认为 &Wire
 * @param i2caddr I2C 地址，默认为 0
 * @param rst_pin 复位引脚，默认为 -1
 * @param switchvcc 电源切换模式，默认为 SSD1306_SWITCHCAPVCC
 * @param clkDuring 时钟参数（期间），默认为 400000UL
 * @param clkAfter 时钟参数（之后），默认为 100000UL
 */
OledDleid::OledDleid(uint8_t width, uint8_t height, uint8_t adr, TwoWire *twi, uint8_t switchvcc, uint8_t rst_pin, uint32_t clkDuring,
                     uint32_t clkAfter) : _width(width), _height(height), _twi(twi), _iicAdr(adr), _switchvcc(switchvcc)
{
  _twi->begin();
  //下面这一行代码不可用
  //Oled_Display = Adafruit_SSD1306(_width, _height, twi, rst_pin);
     Oled_Display = Adafruit_SSD1306(rst_pin);
}
// Don't forget to add a destructor to delete Oled_Display
OledDleid::~OledDleid()
{
}

/**
 * @brief 激活
 */
void OledDleid::begin()
{
  Oled_Display.begin(_switchvcc, _iicAdr);
  Oled_Display.clearDisplay();
  _connectionState = true;
}

/**
 * @brief 清除指定矩形区域并显示文本（不立即更新显示）
 *
 * 在 OLED 屏幕上清除指定的矩形区域，并在该区域显示文本内容。但不会立即更新 OLED 屏幕的显示。
 *
 * @param x 矩形区域的起始 x 坐标
 * @param y 矩形区域的起始 y 坐标
 * @param str 要显示的文本字符串
 * @param size_t 文本字体大小
 */
void OledDleid::clear_RectNOdisplay(uint8_t x, uint8_t y, const char str[], uint8_t size_t)
{
    uint8_t len = strlen(str);
  // 获取文本的宽度和高度
  int16_t textWidth = len * 6 * size_t, textHeight = 8 * size_t; // 注意目前库里面的ascii码是6-8，如果有变动，其中数字要更改
  // 清除要显示文本的局部区域
  Oled_Display.fillRect(x, y, textWidth, textHeight, BLACK); // 使用黑色填充矩形，覆盖之前的显示内容

}
/**
 * @brief 清除 OLED 矩形区域内的显示内容(立即显示)
 *
 * 在 OLED 显示屏的指定矩形区域内清除显示内容，用黑色填充该区域。
 *
 * @param x 矩形区域的起始横坐标
 * @param y 矩形区域的起始纵坐标
 * @param str 要清除的文本内容
 * @param size_t 文本字号大小
 */
void OledDleid::clear_RectDisplay(uint8_t x, uint8_t y, const char str[], uint8_t size_t)
{
    uint8_t len = strlen(str);
  // 获取文本的宽度和高度
  int16_t textWidth = len * 6 * size_t, textHeight = 8 * size_t; // 注意目前库里面的ascii码是6-8，如果有变动，其中数字要更改
  // 清除要显示文本的局部区域
  Oled_Display.fillRect(x, y, textWidth, textHeight, BLACK); // 使用黑色填充矩形，覆盖之前的显示内容
  // 更新显示
  Oled_Display.display();
}

/**
 * @brief 显示英文字符串
 *
 * 在 OLED 显示屏上显示指定的英文字符串。
 *
 * @param x 横坐标
 * @param y 纵坐标
 * @param str 字符串
 * @param size_t 字体大小
 */
void OledDleid::Englishwords_display(uint8_t x, uint8_t y, const char str[], uint8_t size_t)
{
  this->ConnectionState();
  if (_connectionState == false)
  {
    return;
  }
  uint8_t len = strlen(str);
  // 获取文本的宽度和高度
  int16_t textWidth = len * 6 * size_t, textHeight = 8 * size_t; // 注意目前库里面的ascii码是6-8，如果有变动，其中数字要更改
  // 清除要显示文本的局部区域
  Oled_Display.fillRect(x, y, textWidth, textHeight, BLACK); // 使用黑色填充矩形，覆盖之前的显示内容

  // 设置文本颜色和大小
  Oled_Display.setTextColor(WHITE);
  Oled_Display.setTextSize(size_t);

  // 设置光标位置并显示文本
  Oled_Display.setCursor(x, y);
  Oled_Display.print(str);

  // 更新显示
  Oled_Display.display();
}


/**
 * @brief 显示英文字符串（不立即显示）
 *
 * 在 OLED 显示屏上显示指定的英文字符串。
 *
 * @param x 横坐标
 * @param y 纵坐标
 * @param str 字符串
 * @param size_t 字体大小
 */
void OledDleid::Englishwords_NoDisplay(uint8_t x, uint8_t y, const char str[], uint8_t size_t)
{
  this->ConnectionState();
  if (_connectionState == false)
  {
    return;
  }
  uint8_t len = strlen(str);
  // 获取文本的宽度和高度
  int16_t textWidth = len * 6 * size_t, textHeight = 8 * size_t; // 注意目前库里面的ascii码是6-8，如果有变动，其中数字要更改
  // 清除要显示文本的局部区域
  Oled_Display.fillRect(x, y, textWidth, textHeight, BLACK); // 使用黑色填充矩形，覆盖之前的显示内容

  // 设置文本颜色和大小
  Oled_Display.setTextColor(WHITE);
  Oled_Display.setTextSize(size_t);

  // 设置光标位置并显示文本
  Oled_Display.setCursor(x, y);
  Oled_Display.print(str);
}

/**
 * @brief 显示OLED屏幕
 *
 * 该函数用于在OLED屏幕上显示内容。通过调用Oled_Display对象的display()函数来实现。
 */
void OledDleid::display()
{
  Oled_Display.display();
}

/**
 * @brief 显示浮点数
 *
 * 在 OLED 显示屏上指定位置显示浮点数。
 *
 * @param x X 坐标位置
 * @param y Y 坐标位置
 * @param numb 要显示的浮点数
 * @param precision 保留的小数位数
 * @param size_t 字体大小
 */
void OledDleid::FloatNum_display(uint8_t x, uint8_t y, const float numb, uint8_t precision, uint8_t size_t)
{
  this->ConnectionState();
  if (_connectionState == false)
  {
    return;
  }
  const char *str = floatToString(numb, precision);
  // 覆写要显示的区域-------------------------------------------------------
  uint8_t len = strlen(str);
  // 获取文本的宽度和高度
  int16_t textWidth = len * 6 * size_t, textHeight = 8 * size_t; // 注意目前库里面的ascii码是6-8，如果有变动，其中数字要更改
  // 清除要显示文本的局部区域
  Oled_Display.fillRect(x, y, textWidth, textHeight, BLACK); // 使用黑色填充矩形，覆盖之前的显示内容

  // 设置文本颜色和大小
  Oled_Display.setTextColor(WHITE);
  Oled_Display.setTextSize(size_t);

  // 设置光标位置并显示文本
  Oled_Display.setCursor(x, y);
  Oled_Display.print(str);

  // 更新显示
  Oled_Display.display();
  // 释放动态分配的内存
  delete[] str;
}

/**
 * @brief 显示浮点数(不立即显示)
 *
 * 在 OLED 显示屏上指定位置显示浮点数。
 *
 * @param x X 坐标位置
 * @param y Y 坐标位置
 * @param numb 要显示的浮点数
 * @param precision 保留的小数位数
 * @param size_t 字体大小
 */
void OledDleid::FloatNum_NoDisplay(uint8_t x, uint8_t y, const float numb, uint8_t precision, uint8_t size_t)
{
  this->ConnectionState();
  if (_connectionState == false)
  {
    return;
  }
  const char *str = floatToString(numb, precision);
  // 覆写要显示的区域-------------------------------------------------------
  uint8_t len = strlen(str);
  // 获取文本的宽度和高度
  int16_t textWidth = len * 6 * size_t, textHeight = 8 * size_t; // 注意目前库里面的ascii码是6-8，如果有变动，其中数字要更改
  // 清除要显示文本的局部区域
  Oled_Display.fillRect(x, y, textWidth, textHeight, BLACK); // 使用黑色填充矩形，覆盖之前的显示内容

  // 设置文本颜色和大小
  Oled_Display.setTextColor(WHITE);
  Oled_Display.setTextSize(size_t);

  // 设置光标位置并显示文本
  Oled_Display.setCursor(x, y);
  Oled_Display.print(str);

  // 释放动态分配的内存
  delete[] str;
}
// 绘制进度条方法
/**
 * @brief 绘制进度条
 *
 * 在 OLED 显示屏上绘制一个进度条。
 *
 * @param x 进度条左上角的 x 坐标
 * @param y 进度条左上角的 y 坐标
 * @param width 进度条的宽度
 * @param height 进度条的高度
 * @param progress 进度值，范围为 0 到 100
 */
void OledDleid::drawProgressBar(int x, int y, int width, int height, int progress)
{
  this->ConnectionState();
  if (_connectionState == false)
  {
    return;
  }
  // 绘制进度条外框
  Oled_Display.drawRect(x, y, width, height, SSD1306_WHITE);

  // 清除进度条填充区域
  Oled_Display.fillRect(x + 1, y + 1, width - 2, height - 2, SSD1306_BLACK);

  // 计算进度条填充宽度
  int barWidth = map(progress, 0, 100, 0, width - 2);

  // 填充进度条
  Oled_Display.fillRect(x + 1, y + 1, barWidth, height - 2, SSD1306_WHITE);

  Oled_Display.display();
}

// 显示图片方法
/**
 * @brief 显示图像
 *
 * 将给定的图像数据绘制到 OLED 屏幕上。
 *
 * @param x 图像左上角的 x 坐标
 * @param y 图像左上角的 y 坐标
 * @param imageData 图像数据的指针
 * @param height 图像的高度
 * @param width 图像的宽度
 */
void OledDleid::displayImage(int x, int y, const uint8_t *imageData, int width, int height)
{
  this->ConnectionState();
  if (_connectionState == false)
  {
    return;
  }
  // 将图片数据绘制到屏幕上
  Oled_Display.drawBitmap(x, y, imageData, width, height, SSD1306_WHITE);
  Oled_Display.display();
}

// 显示图片方法
/**
 * @brief 显示图像(不立即显示)
 *
 * 将给定的图像数据绘制到 OLED 屏幕上。
 *
 * @param x 图像左上角的 x 坐标
 * @param y 图像左上角的 y 坐标
 * @param imageData 图像数据的指针
 * @param height 图像的高度
 * @param width 图像的宽度
 */
void OledDleid::NoDisplayImage(int x, int y, const uint8_t *imageData, int width, int height)
{
  this->ConnectionState();
  if (_connectionState == false)
  {
    return;
  }
  // 将图片数据绘制到屏幕上
  Oled_Display.drawBitmap(x, y, imageData, width, height, SSD1306_WHITE);
}

/**
 * @brief 清空显示
 */
void OledDleid::clearDisplay()
{
  this->ConnectionState();
  if (_connectionState == false)
  {
    return;
  }
  Oled_Display.drawBitmap(0, 0, clearBMP128_64, 128, 64, SSD1306_WHITE);
  Oled_Display.display();
  Oled_Display.clearDisplay();
}

/**
 * @brief 将浮点数转换为字符串
 *
 * 将给定的浮点数按照指定的精度转换为字符串，并存储在指定的缓冲区中。
 *
 * @param value 浮点数
 * @param precision 精度，即小数点后的位数
 * @param buffer 存储转换结果的缓冲区
 * @param bufferSize 缓冲区的大小
 */
const char *OledDleid::floatToString(float value, uint8_t precision)
{
  // 计算浮点数的长度
  int floatLength = 1; // 初始值为1，用于存储整数部分
  if (value < 0)
  {
    floatLength++;  // 如果是负数，需要额外一个字符存储负号
    value = -value; // 将负数转换为正数
  }
  int integerPart = (int)value; // 整数部分
  while (integerPart /= 10)
  { // 计算整数部分的位数
    floatLength++;
  }
  if (precision > 0)
  {
    floatLength++;            // 如果有小数部分，需要额外一个字符存储小数点
    floatLength += precision; // 小数部分的位数
  }

  // 动态分配内存来存储转换后的字符串
  char *buffer = new char[floatLength + 1]; // +1 是为了存储字符串结束符'\0'

  // 调用 dtostrf() 函数将浮点数转换为字符串
  dtostrf(value, floatLength, precision, buffer);

  return buffer;
}

// 非阻塞延迟函数
bool OledDleid::nonBlockingDelay(unsigned long interval)
{
  static unsigned long previousMillis = 0; // 用于存储上次更新的时间

  unsigned long currentMillis = millis(); // 获取当前时间

  // 检查是否达到了间隔时间
  if (currentMillis - previousMillis >= interval)
  {
    // 保存当前时间作为下一次的上次更新时间
    previousMillis = currentMillis;

    // 返回 true 表示到达了定时间隔
    return true;
  }

  // 返回 false 表示未到达定时间隔
  return false;
}
// 指定地址IIC设备是否存在
bool OledDleid::OledFound()
{
  // 检查 OLED 屏幕连接状态
  _twi->beginTransmission(_iicAdr);
  return _twi->endTransmission() == 0;
  Serial.println("not dectect...");
}
void OledDleid::ConnectionState()
{
  if (!this->OledFound())
  {
    _connectionState = false;
  }
  //如果是连接状态，下面代码跳过
  if (!_connectionState)
  {
    if (this->OledFound())
    {
      //延时200ms，去抖动
      if (nonBlockingDelay(200))
      {
        this->begin();
        //万一抖动失效，保险起见，再次判断
       if (this->OledFound())
       {
          this->begin();
          _connectionState = true;
       }
      }
    }
  }
  ///Serial.println(_connectionState);
}