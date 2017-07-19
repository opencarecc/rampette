////////////////////////////////////////////
///////////////////BUTTON///////////////////
////////////////////////////////////////////

boolean buttonState = 0;
boolean buttonStateOLD = 0;

bool checkbutton() {
  buttonState = digitalRead(buttonPin);
  bool debounce = false;
  if (!buttonState && buttonStateOLD) {
    debounce = true;
    Serial.println("button pressed");

  } else {
    debounce = false;
  }
  buttonStateOLD = buttonState;
  return (debounce);
}

////////////////////////////////////////////
//////////////////LED_PATTERN///////////////
////////////////////////////////////////////

int direction = 1;
int fadeVal = 0;
long lastVibration = 0;
int fadeInterval = 10;
int fadeIncrement = 5;

void fadeLed() {

  if (millis() - lastVibration > fadeInterval) {
    fadeVal += fadeIncrement * direction ;

    lastVibration = millis();
    if (direction == 1 && fadeVal > 255) {
      direction = -1;
    }
    if (direction == -1 && fadeVal < 0) {
      direction = 1;
    }
  }
  analogWrite(ledPin, fadeVal);
}

////////////////////////////////////////////
////////////////////TIMEOUT/////////////////
////////////////////////////////////////////

long timeStarted = 0;
long timeout_interval = 10000;

boolean timeout() {
  if (millis() - timeStarted > timeout_interval) {
    return true;
  } else {
    return false;
  }
}

void resetTimer() {
  timeStarted = millis();
}


