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
