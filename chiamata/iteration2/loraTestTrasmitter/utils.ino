bool checkbutton() {
  buttonState = digitalRead(buttonPin);
  bool debounce = false;

  if (buttonState && !buttonStateOLD) {
    debounce = true;
  } else {
    debounce = false;
  }
  buttonStateOLD = buttonState;
  return (debounce);
}
