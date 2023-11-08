#include "AirManager.h"
#include "settings.h"
#include <Arduino.h>
AirManager::AirManager() : nbrActif(0) {
  //ventilateur
  analogWrite(FAN_PIN, FAN_PWM_MIN);
  ongoingPWM=FAN_PWM_MIN;

  //servomoteur 
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(SERVO_MAX_ANGLE); // Initialisez la position du servo (soufflet ouvert)
  servoAngle=SERVO_MAX_ANGLE;
  nextnote =  millis()+NOTE_INTERVAL;
  nextUpdate = millis()+UPDATE_INTERVAL;
}

void AirManager::noteOn(int velocity) {
  // Incrémentez le nombre de notes actives
  nbrActif++;
  //adapte la vitesse en fct du nombre de note active
  changeSpeed(nbrActif);


  // descendre le soufflet en fonction de la velocité 
  if (servoAngle>(SERVO_MAX_ANGLE+ANGLE_STEP_NOTE)){
    servoAngle=servoAngle-ANGLE_STEP_NOTE;
  }else{
    servoAngle=SERVO_MIN_ANGLE;
  }
  servoMotor.write(servoAngle);
}

void AirManager::noteOff() {
  // Décrémentez le nombre de notes actives
  nbrActif--;
  if (nbrActif < 0) {
    nbrActif = 0;
  }
  changeSpeed(nbrActif);
}

void AirManager::changeSpeed(int nbrActif) {
  // Adaptez la vitesse du ventilateur en fonction du nombre de notes actives
  int fanSpeed = map(nbrActif, 0, NOTE_NUMBER, FAN_PWM_MIN, FAN_PWM_MAX);
  analogWrite(FAN_PIN, fanSpeed);
}

void AirManager::activateFan(bool active) {
  if (active) {
    analogWrite(FAN_PIN, FAN_PWM_MIN);
  } else {
    analogWrite(FAN_PIN, 0);

  }
}

void AirManager::update() {
  if(nbrActif>0){//
    // update du soufflet 
    int now=millis();
    if(now>nextnote){//attendre le temps entre 2 note pour remonter le soufflet
      if(now>nextUpdate){//atendre jusqu'a next update


      // Remontez progressivement le soufflet en l'absence de notes actives
        servoAngle = constrain(servoAngle + ANGLE_STEP_UP, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
        servoMotor.write(servoAngle);
        nextUpdate = millis()+UPDATE_INTERVAL;// next update time
      }
    }
  }
}
