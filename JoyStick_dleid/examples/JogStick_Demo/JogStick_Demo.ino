#include "JoyStick_dleid.h"

JoyStick_dleid  JoyStick1(Serial);
void setup() {
  Serial.begin(9600);
}
//===============================================================================
//  Main
//===============================================================================
void loop() {
  // Check each button input and print the status to the Serial Monitor Window
  
  Serial.print("UP = "),Serial.print(JoyStick1.getUpBtnState()),Serial.print("t   ");
  Serial.print("DOWN = "),Serial.print(JoyStick1.getDownBtnState()),Serial.print("t   ");
  Serial.print("LEFT = "),Serial.print(JoyStick1.getLeftBtnState()),Serial.print("t   ");
  Serial.print("RIGHT = "),Serial.print(JoyStick1.getRightBtnState()),Serial.print("t   ");
  Serial.print("E = "),Serial.print(JoyStick1.getEBtnState()),Serial.print("t   ");
  Serial.print("F = "),Serial.print(JoyStick1.getFBtnState()),Serial.print("n   ");

  // Print the full X/Y joystick values (0-1023)
  Serial.print("X = "),Serial.print(JoyStick1.getJognumX());Serial.print("t");
  Serial.print("Y = "),Serial.print(JoyStick1.getJognumY());Serial.println("n");  

  delay(200);
 }