#include "AudioPlayer.h"
#include <SoftwareSerial.h>

#define PIN_AUDIO_RX 9
#define PIN_AUDIO_TX 10

#define PIN_DRILL 5
#define PIN_SENSOR 2

#define AUDIO_BOOT 1
#define AUDIO_VOICE 2
#define AUDIO_DBG_MOTION_START 3
#define AUDIO_DBG_MOTION_END 4

int state = LOW;

void setup() {
  setupAudio(PIN_AUDIO_RX, PIN_AUDIO_TX);
  pinMode(PIN_DRILL, OUTPUT);
  pinMode(PIN_SENSOR, INPUT);
  digitalWrite(PIN_DRILL, HIGH);
  randomSeed(analogRead(A0) + 37 * analogRead(A1));
  Serial.begin(9600);
  Serial.println(F("Hello World."));
  playAudio(AUDIO_BOOT);
}

void motionDetected() {
    Serial.println(F("Motion detected!"));
    playAudio(AUDIO_VOICE);
    digitalWrite(PIN_DRILL, LOW);
    delay(7500);
    digitalWrite(PIN_DRILL, HIGH);
    delay(3000);
}

void motionStopped(){
  Serial.println(F("Motion stopped!"));
  playAudio(AUDIO_DBG_MOTION_END);
  delay(15000); //Cooldown
}

void testSensor() {

  if (digitalRead(PIN_SENSOR) == HIGH) {

    if (state == LOW) {
      motionDetected();
      state = HIGH;
    }
  }
  else {
    if (state == HIGH) {
      motionStopped();
      state = LOW;
    }
  }
}

void loop() {
  testSensor();
}
