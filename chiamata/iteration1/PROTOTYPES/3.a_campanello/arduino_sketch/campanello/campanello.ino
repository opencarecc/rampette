/*
  DigitalReadSerial
  Reads a digital input on pin 2, prints the result to the serial monitor

  This example code is in the public domain.
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 12;
int ledPin = 13;
int bellPin = 11;

int state = 0;

boolean buttonState = LOW;
boolean buttonStateOLD = LOW;

int brightness = 0;
bool asc = true;

int fadeDalay = 5;
long oldMillis = 0;

long chiamataMillis;
int wait = 10000;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(bellPin, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop() {
  stateMachine();
}


bool checkButton() {
  buttonState = digitalRead(pushButton);
  bool debounce = false;
  if (buttonState && !buttonStateOLD) {
    debounce = true;
    Serial.println("pigio");
  } else {
    debounce = false;
  }
  buttonStateOLD = buttonState;
  return (debounce);
}


void stateMachine() {
  switch (state) {
    case 0:
      analogWrite(ledPin, 0);
      if (checkButton()) {
        callTheBell();
        state = 1;
        Serial.println(state);
        chiamataMillis = millis();
      }
      break;
    case 1:
      fadeUpdate();
      if (millis() - chiamataMillis > wait) {
        state = 2;
        Serial.println(state);
      }
      break;
    case 2:
      notifyReceived();
      state = 0;
      analogWrite(ledPin, 0);
      Serial.println(state);
      break;
  }
}

void fadeUpdate() {
  if (millis() - oldMillis > fadeDalay) {
    if (brightness < 1) {
      asc = true;
    } else if (brightness > 254) {
      asc = false;
    }

    if (asc) {
      brightness++;
    } else {
      brightness--;
    }
    Serial.println(brightness);
    analogWrite(ledPin, brightness);
    oldMillis = millis();
  }
}

void notifyReceived() {
  for (int n = 0; n < 3; n++) {
    for (int i = 0; i < 255; i++) {
      analogWrite(ledPin, i);
      delay(1);
    }
    delay(200);
  }
}

void callTheBell(){
  digitalWrite(bellPin,HIGH);
  delay(200);
  digitalWrite(bellPin,LOW);
}



