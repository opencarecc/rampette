#include <Adafruit_NeoPixel.h>
#include "NeoPatterns.h"
#include "notes.h"

////////////////////////////////////////////
/////////////////CONNECTIONS////////////////
////////////////////////////////////////////

#define BUTTON_PIN      A5
#define VIBRATION_PIN   13
#define MODE_A_PIN      10
#define MODE_B_PIN      11
#define MODE_C_PIN      12
#define SPEAKER_PIN     6

////////////////////////////////////////////
//////////////////NEO_PIXELS////////////////
////////////////////////////////////////////

#define PIXELRING_PIN   9
#define PIXELRING_COUNT 23

void ledComplete();
NeoPatterns leds (PIXELRING_COUNT, PIXELRING_PIN, NEO_GRB + NEO_KHZ400, & ledComplete);

uint32_t spento = leds.Color(0, 0, 0);
uint32_t bianco = leds.Color(255, 255, 255);
uint32_t blue = leds.Color(20, 20, 200);
uint32_t indigo = leds.Color(75, 0, 130);

////////////////////////////////////////////
////////////////LORA_DEVICE_ID//////////////
////////////////////////////////////////////
const word ID = 61308;
const word ID_RX = 61309;

////TX RX ID
//word ID = 61310;
//word ID_RX = 61311;
//
////TX RX ID
//word ID = 61312;
//word ID_RX = 61313;


////////////////////////////////////////////
/////////////////STATE_MACHINE//////////////
////////////////////////////////////////////

int state = 0;

////////////////////////////////////////////
////////////////RECEIVER_MODE///////////////
////////////////////////////////////////////

int mode = 0 ;
//0=light
//1=light+vibration
//2=light+vibration+sound


void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(VIBRATION_PIN, OUTPUT);
  digitalWrite(VIBRATION_PIN, LOW);

  pinMode(MODE_A_PIN, INPUT_PULLUP);
  pinMode(MODE_B_PIN, INPUT_PULLUP);
  pinMode(MODE_C_PIN, INPUT_PULLUP);

  initradio();

  leds.begin();
  leds.SetFullColor(spento);
}

void loop() {
  leds.update();
  stateMachine();
  checkMode();
}


void stateMachine() {
  switch (state) {
    case 0:

      if (receiveData()) {
        state = 1;
        leds.Fade(bianco, spento, 20, 20, FORWARD); //start fade animation
        resetTimer();

      }
      break;

    case 1:
      if (mode == 2) {
        playMelody(); //play the melody
        vibrate();
      }
      else if (mode == 1) {
        vibrate();
      }
      
      //aspetto bottone
      if (checkbutton()) {
        //se premuto trasmetto sto arrivando
        leds.SetFullColor(spento);
        sendData();
        state = 0;
        resetMelody();
        stopVibration();
      }
       if (timeout()) {
        state = 0;
      }
      break;
  }
}

void ledComplete() {
  leds.reverse();
}





