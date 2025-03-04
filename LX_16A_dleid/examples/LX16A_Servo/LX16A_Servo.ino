#include <LX_16A_dleid.h>

LX_16A_dleid myServo(Serial);
void setup() {
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
int id = myServo.LobotSerialServoReadID();
Serial.print("id:");
Serial.println(id);
myServo.LobotSerialServoMove(254, 500, 1000);
delay(1000);
   myServo.LobotSerialServoMove(254, 480, 1000);     
delay(1000);
}
