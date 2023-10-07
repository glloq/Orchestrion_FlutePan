// FlutePan.h
#ifndef FLUTEPAN_H
#define FLUTEPAN_H

#include "settings.h"
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

class FlutePan {
private:
    Adafruit_MCP23X17 mcp;
    uint32_t solenoidActivationTimes[16];  // Pour suivre quand chaque solénoïde a été activé
    bool solenoidStates[16];  // Pour suivre l'état actif/désactivé des solénoïdes
    bool active;  // Pour savoir si un solénoïde est actuellement actif

public:
    FlutePan();
    void begin();
    void playMidiNote(byte note, byte velocity);
    void stopMidiNote(byte note);
    void update();  // Gérer le temps d'activation des solénoïdes
};

#endif // FLUTEPAN_H
