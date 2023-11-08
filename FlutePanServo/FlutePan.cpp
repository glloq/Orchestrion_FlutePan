#include "FlutePan.h"

FlutePan::FlutePan() : activeSolenoids(0), solenoidChanged(false) {
  // Initialisation des temps d'activation et des états à 0
  for (int i = 0; i < 16; i++) {
    solenoidActivationTimes[i] = 0;
    solenoidStates[i] = false;
  }
  // Check I2C
  if (!mcp.begin_I2C()) {
    Serial.println("Error.");
    while (1);
  }
  // Initialisation des sorties
  for (int pin = 0; pin < 16; pin++) {
    mcp.pinMode(pin, OUTPUT);
    mcp.digitalWrite(pin, LOW);
  }
  // Initialisation du ventilateur
  pinMode(FAN_PIN, OUTPUT);
  analogWrite(FAN_PIN, 128);  // Ajustez selon les besoins
}

void FlutePan::playMidiNote(byte note, byte velocity) {
  //************************
  if (enableExtraOctaves) {
    if(note >= (BASE_MIDI_NOTE+ NOTE_NUMBER) && note <= (BASE_MIDI_NOTE + NOTE_NUMBER + 12)){
      note=note-12;
    }
    if(note <= (BASE_MIDI_NOTE) && note <= (BASE_MIDI_NOTE - 12)){
      note=note+12;
    }
  }

  //*********************************
  int totalPin = note - BASE_MIDI_NOTE;
  if (totalPin >= 0 && totalPin < 16) {
    int solenoidIndex = totalPin;

    if (!solenoidStates[solenoidIndex]) {
      solenoidStates[solenoidIndex] = true;
      solenoidActivationTimes[solenoidIndex] = millis();
      solenoidChanged = true; // Un solénoïde a changé d'état
      activeSolenoids++; // Incrémenter le compteur de solénoïdes actifs
      int mcpPin= SOLENOID_ORDER[solenoidIndex];//adapte la sortie a l'ordre du branchement sur les sortie du mcp
      mcp.digitalWrite(mcpPin, HIGH);
    }
  }
}

void FlutePan::stopMidiNote(byte note) {
  //*******************************************
  if (enableExtraOctaves) {
    if(note >= (BASE_MIDI_NOTE+ NOTE_NUMBER) && note <= (BASE_MIDI_NOTE + NOTE_NUMBER + 12)){
      note=note-12;
    }
    if(note <= (BASE_MIDI_NOTE) && note <= (BASE_MIDI_NOTE - 12)){
      note=note+12;
    }
  }

//****************************************************
  int totalPin = note - BASE_MIDI_NOTE;
  if (totalPin >= 0 && totalPin < 16) {
    int solenoidIndex = totalPin;
    
    if (solenoidStates[solenoidIndex]) {
      solenoidStates[solenoidIndex] = false;
      solenoidChanged = true; // Un solénoïde a changé d'état
      activeSolenoids--; // Décrémenter le compteur de solénoïdes actifs
      int mcpPin= SOLENOID_ORDER[solenoidIndex];//adapte la sortie a l'ordre du branchement sur les sortie du mcp
      mcp.digitalWrite(mcpPin, LOW);
    }
  }
}

void FlutePan::adjustFanSpeed() {
  int fanSpeed = map(activeSolenoids, 0, 16, FAN_PWM_MIN, FAN_PWM_MAX);
  analogWrite(FAN_PIN, fanSpeed);
}

void FlutePan::update() {
  if (solenoidChanged) {
    adjustFanSpeed();
    solenoidChanged = false; // Réinitialiser le changement de solénoïde
  }

  uint32_t currentTime = millis();
  if(activeSolenoids>0){
    for (int i = 0; i < 16; i++) {
      if (solenoidActivationTimes[i] != 0 && currentTime - solenoidActivationTimes[i] > MAX_ACTIVATION_TIME) {
        mcp.digitalWrite(i, LOW);
        solenoidActivationTimes[i] = 0;
      }
    }
  }
}
