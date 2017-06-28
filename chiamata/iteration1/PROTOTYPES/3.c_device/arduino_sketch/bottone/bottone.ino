#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include "NeoPatterns.h"

int ledPin = 17;

int buttonAPin = 4;
boolean buttonAState = LOW;
boolean buttonAStateOLD = LOW;

int state = 0;

void ledComplete();
NeoPatterns leds (10, ledPin, NEO_GRB + NEO_KHZ800, & ledComplete);

uint32_t spento = leds.Color(0, 0, 0);
uint32_t bianco = leds.Color(255, 255, 255);
uint32_t blue = leds.Color(20, 20, 200);
uint32_t indigo = leds.Color(75, 0, 130);


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
      if (checkButtonA()) {
        goToState(1);
        leds.Fade(indigo, spento, 100, 20, FORWARD);
      }
      break;

    case 1:
      if (checkButtonA()) {
        goToState(2);
        leds.spinner(indigo, 120, FORWARD, 5);
      }
      break;

    case 2:
      if (checkButtonA()) {
        for (int n=0;n<3;n++){ 
          for (int i=0;i<255;i++){
            leds.ColorSet(leds.Color(i,i,i));
            delay(1);
          }
          delay(200);
        }
        goToState(0);
        leds.SetFullColor(spento);

        
      }
      break;
  }
}


void goToState(int s) {
  state = s;
  Serial.print("entering state #");
  Serial.println(state);

}

