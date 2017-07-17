#include <Adafruit_NeoPixel.h>
#include "NeoPatterns.h"
#include "notes.h"

//CONNECTIONS
#define BUTTON_PIN      A5
#define VIBRATION_PIN   13
#define VIBRATION_PIN   13
#define MODE_A_PIN      10
#define MODE_B_PIN      11
#define MODE_C_PIN      12
#define SPEAKER_PIN     6

//neopixel
#define PIXELRING_PIN   9
#define PIXELRING_COUNT 23

//TX RX ID
word ID = 61308;   
word ID_RX = 61308;   


//STATE MACHINE
int state = 0;


void ledComplete();
NeoPatterns leds (PIXELRING_COUNT, PIXELRING_PIN, NEO_GRB + NEO_KHZ400, & ledComplete);

uint32_t spento = leds.Color(0, 0, 0);
uint32_t bianco = leds.Color(255, 255, 255);
uint32_t blue = leds.Color(20, 20, 200);
uint32_t indigo = leds.Color(75, 0, 130);





void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  initradio();
  leds.begin();
  leds.SetFullColor(spento);
}

void loop() {
  leds.update();
  stateMachine();
}


void stateMachine() {
  switch (state) {
    case 0:

      if (receiveData()) {
        state = 1;
        leds.Fade(indigo, spento, 100, 20, FORWARD); //start fade animation
      }
      break;

    case 1:
      playMelody(); //play the melody

      //aspetto bottone
      if (checkbutton()) {
        //se premuto trasmetto sto arrivando
        leds.SetFullColor(spento);
        sendData();
        state = 0;
      }
      break;
  }
}

void ledComplete() {
  leds.reverse();
}





