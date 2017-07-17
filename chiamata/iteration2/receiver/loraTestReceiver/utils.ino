boolean buttonState = 0;
boolean buttonStateOLD = 0;


//LOGIC FOR DEBOUNCING BUTTONS

bool checkbutton() {
  buttonState = digitalRead(BUTTON_PIN);
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


//SOME CODE TO MAKE THE MELODY WORK

int melody[] = {
  NOTE_C4,  NOTE_G3,  NOTE_G3,  NOTE_A3,  NOTE_G3,  0,     NOTE_B3, NOTE_C4
};
int noteDurations[] = {  
  4,        8,        8,        4,        4,        4,      4,       4
};
void playMelody(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(SPEAKER_PIN, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER_PIN);
  }
}

