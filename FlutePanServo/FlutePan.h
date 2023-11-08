#ifndef FLUTEPAN_H
#define FLUTEPAN_H

#include "settings.h"
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
/***********************************************************************************************
----------------------------       PanFlute Object       ----------------------------------------
************************************************************************************************/
class FlutePan {
private:
  Adafruit_MCP23X17 mcp;
  uint32_t solenoidActivationTimes[16];  // Pour suivre quand chaque solénoïde a été activé
  bool solenoidStates[16];  // Pour suivre l'état actif/désactivé des solénoïdes
  int activeSolenoids; // variable pour compter les solénoïdes actifs et adapter le ventilateur
  bool solenoidChanged; // Variable pour indiquer si un solénoïde a changé d'état

public:
  FlutePan();
  void playMidiNote(byte note, byte velocity);
  void stopMidiNote(byte note);
  void setFanState(bool state);
  void adjustFanSpeed();
  void update();  // Gérer le temps d'activation des solénoïdes
};

#endif
