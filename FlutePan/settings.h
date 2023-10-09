#ifndef SETTINGS_H
#define SETTINGS_H
#include "stdint.h"

#define DEBUG 1

//reglages flute
constexpr uint8_t BASE_MIDI_NOTE = 64; //note midi de la premiere flute 
constexpr uint8_t NOTE_NUMBER = 16; // nombre de flute/notes

constexpr uint8_t MAX_MCPs = (NOTE_NUMBER + 15) / 16; //donne le nombre de MCPs nécessaires.
constexpr uint8_t MCP_BASE_ADDRESS = 0x20; // C'est l' adresse de départ pour le premier MCP.

//Gestion air
constexpr uint8_t FAN_PIN = 9; // pin PWM ventilateur 
constexpr uint8_t FAN_PWM_MIN = 90; // pin min PWM ventilateur 
constexpr uint8_t FAN_PWM_MAX = 127; // pin max PWM ventilateur 

constexpr int MAX_ACTIVATION_TIME =5000;// temps max actif pour un electroaimant

//options
constexpr uint8_t ON_PIN = 4; // pin bouton on/off ventilateur 



#endif
