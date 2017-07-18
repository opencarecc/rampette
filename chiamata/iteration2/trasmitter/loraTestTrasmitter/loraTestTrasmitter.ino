
////////////////////////////////////////////
/////////////////CONNECTIONS////////////////
////////////////////////////////////////////
int buttonPin = 13;
int ledPin = 12;


////////////////////////////////////////////
/////////////////STATE_MACHINE//////////////
////////////////////////////////////////////

int state = 0;

////////////////////////////////////////////
////////////////LORA_DEVICE_ID//////////////
////////////////////////////////////////////

const word ID = 61309;   
const word ID_RX = 61308;   

//const word ID = 61311;   
//const word ID_RX = 61310;   

//const word ID = 61313;   
//const word ID_RX = 613012;   


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  initradio();
}

void loop() {
  stateMachine();
}

void stateMachine() {
  switch (state) {
    case 0: //nothing is happening

      if (checkbutton()) {
        state = 1;
        Serial.println("going to state 1");

        //effettuo la chiamata
        sendData();
        //accendo il led
        digitalWrite(ledPin, HIGH);
      }
      break;
    case 1:
      //aspetto conferma ricezione
      if (receiveData()) {
        state = 2;
        Serial.println("going to state2");
      }
      //se rivevo conferma -> state=2
      break;
    case 2:
      //notifico chiamata ricevuta
      //aspetto e torno a stato 0
      //delay(2000);
      digitalWrite(ledPin, LOW);
       Serial.println("resetting to state0");

      state = 0;
      break;
  }
}

