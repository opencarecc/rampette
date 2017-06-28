#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include "NeoPatterns.h"

int ledPin = 12;

int buttonAPin = 5;
boolean buttonAState = LOW;
boolean buttonAStateOLD = LOW;

int state = 0;

void ledComplete();
NeoPatterns leds (10, ledPin, NEO_GRB + NEO_KHZ800, & ledComplete);

uint32_t spento = leds.Color(0, 0, 0);
uint32_t bianco = leds.Color(255, 255, 255);
uint32_t blue = leds.Color(20, 20, 200);
uint32_t indigo = leds.Color(75, 0, 130);

long chiamataMillis = 0;
int wait = 10000;

void setup() {
  leds.begin();
  Serial.begin(9600);
  pinMode(buttonAPin, INPUT);
  leds.SetFullColor(spento);

}

void loop() {
  leds.update();
  stateMachine();
}

// bodyColor Completion Callback
void ledComplete() {
  //Serial.println("complete");
  leds.reverse();
}

bool checkButtonA() {
  buttonAState = digitalRead(buttonAPin);
  // Serial.println(buttonAState);
  bool debounce = false;
  if (buttonAState && !buttonAStateOLD) {
    debounce = true;
  } else {
    debounce = false;
  }
  buttonAStateOLD = buttonAState;
  return (debounce);
}


void stateMachine() {
  switch (state) {
    case 0:
      leds.ColorSet(leds.Color(0, 0, 0));
      Serial.print(".");
      if (millis() - chiamataMillis > wait) {
        state = 1;
        Serial.println(state);
      }
      break;

    case 1:
      for (int i = 0; i < 100; i++) {
        leds.ColorSet(leds.Color(i, i, i));
        delay(1);
      }
      delay(200);

      goToState(0);
      leds.SetFullColor(spento);
      if (checkButtonA()) {
        state = 0;
        chiamataMillis = millis();
      }
      break;

  }
}


void goToState(int s) {
  state = s;
  Serial.print("entering state #");
  Serial.println(state);

}

