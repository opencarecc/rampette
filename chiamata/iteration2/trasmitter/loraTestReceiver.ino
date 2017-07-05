int buttonPin = 5;

boolean buttonState = 0;
boolean buttonStateOLD = 0;

int state = 0;

int ledPin = 12;

///////////////// ID of transmitting boards, choose one.//////////////
word ID = 61308;   // ID di questo trasmettitore
word ID_RX = 61308;   // ID  del modulo ricevente interno al negozio
/////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  initradio();


}

void loop() {
  stateMachine();
}


void stateMachine() {
  switch (state) {
    case 0:
      //sto in ricezione

      
      if (receiveData()) {
        //se ricevo vado a state 1
        state = 1;
      }

      //notifico chiamata effettuata
      digitalWrite(ledPin, HIGH);

      break;

    case 1:

      //aspetto bottone
      if (checkbutton()) {
        //se premuto trasmetto sto arrivando
        sendData();
        state = 2;
      }
      break;
    case 2:
      //
        digitalWrite(ledPin, LOW);

      state = 0;
      break;
  }
}




