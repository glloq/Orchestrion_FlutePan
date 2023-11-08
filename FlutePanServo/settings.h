#ifndef SETTINGS_H
#define SETTINGS_H
#include "stdint.h"

#define DEBUG 1

//-----------------------    SETUPS   --------------------------
constexpr uint8_t BASE_MIDI_NOTE = 64; // Note MIDI de la première flûte
constexpr uint8_t NOTE_NUMBER = 16; // Nombre de flûtes/notes
// Tableau pour spécifier l'ordre des sorties pour chaque note (solenoid)
constexpr uint8_t SOLENOID_ORDER[NOTE_NUMBER] = { 7, 6, 5, 4, 3, 2, 1, 0, 8, 9, 10, 11, 12, 13, 14, 15};
constexpr uint8_t MCP_ADDRESS = 0x20; // C'est l' adresse pour le MCP.
constexpr int MAX_ACTIVATION_TIME = 3000; // Temps maximal actif pour un électroaimant avant desactivation automatique


//-----------------------    AIR MANAGER   --------------------------
constexpr uint8_t FAN_PIN = 9; // Broche PWM du ventilateur
constexpr uint8_t FAN_PWM_MIN = 90; // Valeur minimale PWM du ventilateur
constexpr uint8_t FAN_PWM_MAX = 127; // Valeur maximale PWM du ventilateur

constexpr uint8_t SERVO_PIN = 5; // Broche signal du servo
constexpr uint8_t SERVO_MIN_ANGLE=50; //angle du servmoteur pour souflet fermé
constexpr uint8_t SERVO_MAX_ANGLE=120; //angle du servmoteur pour souflet ouvert
constexpr uint8_t UPDATE_INTERVAL = 200; // temps en  ms entre deux updates pour l'angle du servo pour reduire l'utilisation processeur
constexpr uint8_t NOTE_INTERVAL = 500; // temps en  ms entre deux note pour laisser le temp au soufflet de descendre
constexpr uint8_t ANGLE_STEP_NOTE = 30; // angle du servo a descendre en un coup pour la velocité maximum
constexpr uint8_t ANGLE_STEP_UP = 5; // angle du servo a remonter a chaque update() de air manager


//-----------------------    Options  -----------------------
constexpr uint8_t ON_PIN = 4; // Broche du bouton marche/arrêt du ventilateur
constexpr uint8_t enableExtraOctaves = 5; // Broche du bouton extra octave 

#endif
