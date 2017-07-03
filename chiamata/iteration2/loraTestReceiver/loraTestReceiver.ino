int buttonPin = 5;

boolean buttonState = 0;
boolean buttonStateOLD = 0;

int state = 0;

int ledPin = 13;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);        
  digitalWrite(ledPin, LOW);
}

void loop() {
  stateMachine();
  Serial.println(digitalRead(buttonPin));
}



void stateMachine() {
  switch (state) {
    case 0: //nothing is happening
      
      if (checkbutton()) {
        state = 1;
        //effettuo la chiamata

        //accendo il led
        digitalWrite(ledPin, HIGH);
        
      }
      break;
    case 1:
      //aspetto conferma ricezione
      //se rivevo conferma -> state=2
      break;
    case 2:
      //notifico chiamata ricevuta
      //aspetto e torno a stato 0
      break;
  }
}


bool checkbutton() {
  buttonState = digitalRead(buttonPin);
  bool debounce = false;

  Serial.println(buttonState);
  
  if (buttonState && !buttonStateOLD) {
    debounce = true;
  } else {
    debounce = false;
  }
  buttonStateOLD = buttonState;
  return (debounce);
}

