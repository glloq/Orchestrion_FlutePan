// FlutePan.cpp
#include "FlutePan.h"

FlutePan::FlutePan() : active(false) {
  // initialisation des temps d'activation et des états à 0
  for (int i = 0; i < 16; i++) {
    solenoidActivationTimes[i] = 0;
    solenoidStates[i] = false;
  }

  //initialisation des sorties en fonction du nombre de mcp utilisé
  for (int m = 0; m < MAX_MCPs; m++) {
    mcp[m].begin_I2C(MCP_BASE_ADDRESS + m);
    for (int pin = 0; pin < 16; pin++) {
      mcp[m].pinMode(pin, OUTPUT);
      mcp[m].digitalWrite(pin, LOW);
    }
  }
  // Initialisation du ventilateur
  pinMode(FAN_PIN, OUTPUT);
  analogWrite(FAN_PIN, 128);  // Ajustez selon les besoins
}

void FlutePan::playMidiNote(byte note, byte velocity) {
  int totalPin = note - BASE_MIDI_NOTE;
  int mcpIndex = totalPin / 16;
  int pinIndex = totalPin % 16;

  if (mcpIndex < MAX_MCPs) {
      mcp[mcpIndex].digitalWrite(pinIndex, HIGH);
  }
  solenoidStates[totalPin] = true;
  solenoidActivationTimes[totalPin] = millis();  // Enregistrement du moment de l'activation
  active = true;
}

void FlutePan::stopMidiNote(byte note) {
  int totalPin = note - BASE_MIDI_NOTE;
  int mcpIndex = totalPin / 16;
  int pinIndex = totalPin % 16;

  if (mcpIndex < MAX_MCPs) {
    mcp[mcpIndex].digitalWrite(pinIndex, LOW);
  }
  solenoidStates[totalPin] = false;
  active = false;
    
}


void FlutePan::update() {
  uint32_t currentTime = millis();
  
  // Vérifier si un solénoïde est actif depuis trop longtemps
  for (int totalPin = 0; totalPin < NOTE_NUMBER; totalPin++) {
    int mcpIndex = totalPin / 16;
    int pinIndex = totalPin % 16;
      
    if (solenoidStates[totalPin] && currentTime - solenoidActivationTimes[totalPin] > MAX_ACTIVATION_TIME) {
      if (mcpIndex < MAX_MCPs) {
        mcp[mcpIndex].digitalWrite(pinIndex, LOW);
      }
      solenoidStates[totalPin] = false;
      solenoidActivationTimes[totalPin] = 0;
    }
  }

    // Vérifier à nouveau si tous les solénoïdes sont désactivés
    active = false;
}