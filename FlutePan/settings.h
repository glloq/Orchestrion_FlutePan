#ifndef SETTINGS_H
#define SETTINGS_H
#include "stdint.h"

#define DEBUG 1


constexpr uint8_t ON_PIN = 4; // pin bouton on/off

//Gestion air
constexpr uint8_t FAN_PIN = 9; // pin PWM ventilateur 
constexpr uint8_t FAN_PWM_MIN = 90; // pin min PWM ventilateur 
constexpr uint8_t FAN_PWM_MAX = 127; // pin max PWM ventilateur 


//  adresse I2C MCP23017
constexpr uint8_t MCP_ADDRESSES = 0x20; 
constexpr int MAX_ACTIVATION_TIME =5000;// temps max actif pour un electroaimant


#endif
