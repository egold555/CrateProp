#include "AudioPlayer.h"
#include <SoftwareSerial.h>

#define PIN_AUDIO_RX 9
#define PIN_AUDIO_TX 10

#define PIN_DRILL 5
#define PIN_LIGHT 6
#define PIN_SENSOR 2

#define AUDIO_BOOT 1
#define AUDIO_VOICE 2

int state = LOW;

void setup() {
  setupAudio(PIN_AUDIO_RX, PIN_AUDIO_TX);
  pinMode(PIN_DRILL, OUTPUT);
  pinMode(PIN_LIGHT, OUTPUT);
  pinMode(PIN_SENSOR, INPUT);

  digitalWrite(PIN_DRILL, LOW);
  digitalWrite(PIN_LIGHT, LOW);
  
  randomSeed(analogRead(A0) + 37 * analogRead(A1));
  
  playAudio(AUDIO_BOOT);
  delay(3000);
}

void motionDetected() {
    playAudio(AUDIO_VOICE);
    digitalWrite(PIN_DRILL, HIGH);
    digitalWrite(PIN_LIGHT, HIGH);
    for (int i = 0; i < 5; ++i) {
      delay(random(600, 1200)); // on time
      digitalWrite(PIN_DRILL, LOW);
      delay(random(200,600)); // off time
      
      digitalWrite(PIN_DRILL, HIGH);
    }
    digitalWrite(PIN_DRILL, LOW);
    digitalWrite(PIN_LIGHT, LOW);
    delay(3000);
}

void motionStopped(){
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
