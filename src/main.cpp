#include <Arduino.h>
int redLed = 13;
int greenLed = 12;
int sensor = A0;
int punishDelay = 10;

int REWARDING = 1;

const long soundThreshold = 700;

const unsigned long redLedOnTime = 5000;
unsigned long previousTimeRedLed = 0;
int redLedState = LOW;

const unsigned long greenLedOnTime = 5000;
unsigned long previousTimeGreenLed = 0;
int greenLedState = LOW;

const unsigned long rewardInteval = 10000;
unsigned long previousRewardTime = 0;

unsigned long previousPunishTime = 0;


void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  int v_sensor = analogRead(sensor);
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  // if sound sensor measures above the threshold
  if(v_sensor > soundThreshold && redLedState == 0) {
    // this is the punishment:
    Serial.println("bad boy! :(");

    // set rewarding off
    REWARDING = 0;

    // turn on RED led
    redLedState = 1;
    digitalWrite(redLed, redLedState);
    // start timer for red led's on time
    previousTimeRedLed = currentTime;
    
    //shut off GREEN led
    greenLedState = 0;
    digitalWrite(greenLed, greenLedState);
  }
  
  // keep red led on until reached "redLedOnTime"
  if (redLedState == 1 && currentTime - previousTimeRedLed >= redLedOnTime) {
    // turn of red led
    redLedState = !redLedState;
    digitalWrite(redLed, redLedState);
    previousTimeRedLed = currentTime;

    // turn REWARDING ON
    REWARDING = 1;
    // reset rewarding time
    previousRewardTime = currentTime;
  }
  

  // BOF REWARD
  // keep green led on until reached "greenLedOnTime"
  if (greenLedState == 1 && currentTime - previousTimeGreenLed >= greenLedOnTime) {
    greenLedState = !greenLedState;
    digitalWrite(greenLed, greenLedState);
    previousTimeGreenLed = currentTime;
  }
  // trigger reward on "rewardInterval" as long as REWARDING is ON
  if (REWARDING == 1 && currentTime - previousRewardTime >= rewardInteval) {
    // This is the reward:
    Serial.println("good boy! :)");

    // turn on GREEN led
    greenLedState = 1;
    digitalWrite(greenLed, greenLedState);
    // start timer for green led's on time
    previousTimeGreenLed = currentTime;
    // reset rewarding time
    previousRewardTime = currentTime;
  }


/*
  // 1. trigger punish, first turning red led on
  if(v_sensor > 700) {
    //Serial.println(v_sensor);
    Serial.println("bad boy :(");
    digitalWrite(redLed, HIGH);
    previousTimeRedLed = currentTime;
  } else {
    // 3. reward loop
    if (currentTime - previousRewardTime >= rewardInteval) {
      //reward();
      Serial.println("good boy! :)");
      digitalWrite(greenLed, HIGH);
      previousTimeGreenLed = currentTime;
      previousRewardTime = currentTime;
    }
  }
*/
  //Serial.println(v_sensor);
}
