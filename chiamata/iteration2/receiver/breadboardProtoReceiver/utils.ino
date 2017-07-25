////////////////////////////////////////////
///////////////////BUTTON///////////////////
////////////////////////////////////////////

boolean buttonState = 0;
boolean buttonStateOLD = 0;

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

////////////////////////////////////////////
///////////////////MELODY///////////////////
////////////////////////////////////////////

int melody[] = {
  NOTE_C6,  NOTE_G5,  NOTE_G5,  NOTE_A5,  NOTE_G5,  0,     NOTE_B5, NOTE_C6
};
int noteDurations[] = {
  4,        8,        8,        4,        4,        4,      4,       4
};

int melodyLength = 8;
int playngNoteIndex = 0;
long lastNotePlayedTime = 0;
int noteDuration = 1000 / noteDurations[0];
int pauseBetweenNotes = noteDuration * 1.10;


void playMelody() {
  if (millis() - lastNotePlayedTime > noteDuration + pauseBetweenNotes) {
    lastNotePlayedTime = millis();
    noteDuration = 1000 / noteDurations[playngNoteIndex];
    pauseBetweenNotes = noteDuration * 1.30;
    tone(SPEAKER_PIN, melody[playngNoteIndex], noteDuration);
    playngNoteIndex++;
    Serial.println(playngNoteIndex);

    if (playngNoteIndex == melodyLength) { //se finisco la melodia ricomincio
      playngNoteIndex = 0;
    }
  }
}

void resetMelody() {
  playngNoteIndex = 0;
}


////////////////////////////////////////////
//////////////////VIBRATION/////////////////
////////////////////////////////////////////

boolean vibrationStatus = false;
long lastVibration = 0;
void vibrate() {
  if (millis() - lastVibration > 1000) {
    vibrationStatus = !vibrationStatus;
    lastVibration = millis();
  }
  digitalWrite(VIBRATION_PIN, vibrationStatus);
}

void stopVibration() {
  digitalWrite(VIBRATION_PIN, LOW);
}

////////////////////////////////////////////
/////////////////////MODE///////////////////
////////////////////////////////////////////
void checkMode() {
//  Serial.print(digitalRead(MODE_A_PIN));
//  Serial.print("-");
//  Serial.print(digitalRead(MODE_B_PIN));
//  Serial.print("-");
//  Serial.println(digitalRead(MODE_C_PIN));

  if (!digitalRead(MODE_A_PIN)) {
    mode = 0;
  } else if (!digitalRead(MODE_B_PIN)) {
    mode = 1;
  } else if (!digitalRead(MODE_C_PIN)) {
    mode = 2;
  }
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



