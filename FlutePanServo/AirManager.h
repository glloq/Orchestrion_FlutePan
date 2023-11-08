#ifndef AIRMANAGER_H
#define AIRMANAGER_H

#include <Servo.h>

class AirManager {
  private:
    Servo servoMotor;
    int nbrActif;//nombre de notes active en cours
    //bool changeNote; //boolean pour informer une extinction de note et revoir la vitesse du ventilo
    int ongoingPWM;//nombre de notes active en cours
    int servoAngle;//angle servo en cours
    int nextUpdate;//time for update
    int nextnote;//time between the bellow down and start to go up 
    void changeSpeed(int nbrActif);//adapte la vitesse du ventilo en fct du nombre de notes en cours
    
  public:
    AirManager();
    void noteOn(int velocity);//incremente le nombres de notes active en meme temps et adapte la vitesse du ventilateur
    void noteOff();// desincremente le nombre de note active 
    void activateFan(bool active);// active ou desactive le ventilateur
    void update();//fonction appelé par update de flutePan pour la gestion de la vitesse et de la hauteur du soufflet
};

#endif
