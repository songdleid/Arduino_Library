/*
   RelayTest.ino
   Created: 2024.5.31
   Author:   宋隽颢
*/

#include <Arduino.h>
#include "RelayDleid.h"



#define RelayInletToWait_IONum 24  //静水区进水水泵继电器
#define RelayWaitToLive_IONum 26  //静水区-生活区—进水继电器
#define RelayCycleToLive_IONum 25  //油膜区-生活区—循环继电器
#define RelayOilToOutlet_IONum 27  //油膜区放水继电器
#define RelayEffluentToOutlet_IONum 28 //生活区放水继电器



RelayDleid relay1(RelayInletToWait_IONum, true);
RelayDleid relay2(RelayWaitToLive_IONum, true);
RelayDleid relay3(RelayCycleToLive_IONum, true);
RelayDleid relay4(RelayOilToOutlet_IONum, true);
RelayDleid relay5(RelayEffluentToOutlet_IONum, true);

bool running = false;
unsigned long interval = 1000; // 默认开关频率为1000毫秒
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  relay1.begin();
  relay2.begin();
  relay3.begin();
  relay4.begin();
  relay5.begin();
  Serial.println("Relay Test Initialized. Send 'START' to start, 'STOP' to stop, 'FREQ <milliseconds>' to set frequency.");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.equalsIgnoreCase("START")) {
      running = true;
      Serial.println("Relay started.");
    } else if (input.equalsIgnoreCase("STOP")) {
      running = false;
        relay1.close();
        relay2.close();
        relay3.close();
        relay4.close();
        relay5.close();  
      Serial.println("Relay stopped.");
    } else if (input.startsWith("FREQ")) {
      input.remove(0, 5);
      interval = input.toInt();
      Serial.print("Frequency set to ");
      Serial.print(interval);
      Serial.println(" milliseconds.");
    }
  }

  if (running) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (relay1.getNowState()) {
        relay1.close();
        relay2.close();
        relay3.close();
        relay4.close();
        relay5.close();       
        Serial.println("Relay OFF");
      } else {
        relay1.open();
        relay2.open();
        relay3.open();
        relay4.open();
        relay5.open();
        Serial.println("Relay ON");
      }
    }
  }
}
