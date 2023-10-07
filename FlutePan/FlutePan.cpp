// FlutePan.cpp
#include "FlutePan.h"

FlutePan::FlutePan() : active(false) {
    // Constructeur: initialisation des temps d'activation et des états à 0
    for (int i = 0; i < 16; i++) {
        solenoidActivationTimes[i] = 0;
        solenoidStates[i] = false;
    }
}

void FlutePan::begin() {
  if (!mcp.begin_I2C()) {
    Serial.println("Error.");
    while (1);
  }

    for(int i = 0; i < 16; i++) {
        mcp.pinMode(i, OUTPUT);
        mcp.digitalWrite(i, LOW);
    }

    // Initialisation du ventilateur
    pinMode(FAN_PIN, OUTPUT);
    analogWrite(FAN_PIN, 128);  // Ajustez selon les besoins
}

void FlutePan::playMidiNote(byte note, byte velocity) {
    int solenoidIndex = note % 16;  // Pour s'assurer que nous avons un index valide
    mcp.digitalWrite(solenoidIndex, HIGH);
    solenoidStates[solenoidIndex] = true;
    solenoidActivationTimes[solenoidIndex] = millis();  // Enregistrement du moment de l'activation
    active = true;
}

void FlutePan::stopMidiNote(byte note) {
    int solenoidIndex = note % 16;
    mcp.digitalWrite(solenoidIndex, LOW);
    solenoidStates[solenoidIndex] = false;

    // Vérifier si tous les solénoïdes sont désactivés
    active = false;
    for (int i = 0; i < 16; i++) {
        if (solenoidStates[i]) {
            active = true;
            break;
        }
    }
}

void FlutePan::update() {
    uint32_t currentTime = millis();
    for (int i = 0; i < 16; i++) {
        if (solenoidActivationTimes[i] && currentTime - solenoidActivationTimes[i] > MAX_ACTIVATION_TIME) {
            mcp.digitalWrite(i, LOW);
            solenoidStates[i] = false;
            solenoidActivationTimes[i] = 0;
        }
    }

    // Vérifier à nouveau si tous les solénoïdes sont désactivés
    active = false;
    for (int i = 0; i < 16; i++) {
        if (solenoidStates[i]) {
            active = true;
            break;
        }
    }
}
