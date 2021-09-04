#include <Arduino.h>
int redLed = 13;
int greenLed = 12;
int sensor = A0;
int rewardInteval = 5;
int punishDelay = 10;

const unsigned long eventInterval = rewardInteval*1000;
unsigned long previousTime = 0;


void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}

void punish() {
  Serial.println("bad boy :(");
  digitalWrite(redLed, HIGH);
  delay(1000);
  digitalWrite(redLed, LOW);
  delay(punishDelay*1000);
}


void reward() {
  Serial.println("good boy! :)");
  digitalWrite(greenLed, HIGH);
  delay(1000);
  digitalWrite(greenLed, LOW);
}


void loop() {
  int v_sensor = analogRead(sensor);

  if(v_sensor > 700) {
    Serial.println(v_sensor);
    punish();
  } else {
    digitalWrite(redLed, LOW);
    
    /* Updates frequently */
    unsigned long currentTime = millis();

    /* This is the event */
    // @TODO: reset the time after punish.
    if (currentTime - previousTime >= eventInterval) {
      /* Event code */
      reward();
      delay(3000);
      
    /* Update the timing for the next time around */
      previousTime = currentTime;
    }
  }

  Serial.println(v_sensor);
}
