//
// Created by ferra on 16-Apr-20.
//

#ifndef JOYSTICK_DYN_APP_MOTORS_H
#define JOYSTICK_DYN_APP_MOTORS_H

#endif //JOYSTICK_DYN_APP_MOTORS_H
#include <stdbool.h>
#include <stdint.h>

//Distància entre les rodes serà 2*L, la distància de les rodes al centre del motor serà L.
static const float L = 1.0;
//El radi de les rodes serà L.
static const float r = 1.0;
//El mòdul de l'esquerra tindrà la id 1.
static const uint8_t ID_MOTOR_LEFT = 1;
//El mòdul de la dreta tindrà la id 2.
static const uint8_t ID_MOTOR_RIGHT = 2;

//Velocitat màxima dels motors dels mòduls Dynamixel.
static const uint16_t DYN_MAX_SPEED = 0x03ff;
//Velocitat mínima dels motors dels mòduls Dynamixel.
static const uint16_t DYN_MIN_SPEED = 0x0001;

/*
 *Les tres funcions següents permeten modificar valors dels registres dels
 * mòduls Dynamixel a fi de controlar el que fan els motors.
 */

//aquesta funció posa els motors del mòdul corresponent a la id passada a mode endless turn.
int dyn_turnContinuous(uint8_t id);

//aquesta funció posa la velocitat del motor del mòdul corresponent a la id passada a la velocitat passada. La direcció serà true
//si volem que giri en sentit horari, i viceversa.
int dyn_setTurnSpeed(uint8_t id, uint16_t speed, bool direction);

//aquesta funció atura el motor del mòdul corresponent a la id passada.
int dyn_stop(uint8_t id);

//aquesta funció llegeix els bytes de velocitat de gir d'un mòdul i els assigna als punters passats.h
int dyn_readTurnSpeed(uint8_t id, uint16_t *speed, bool *direction);

//aquesta funció comprova si els motors estan en mode endless turn i assigna al punter passat true si és així, false si no.
int dyn_readTurnContinuous(uint8_t id, bool *continuous);


/*
 *A continuació tenim funcions d'alt nivell per a controlar el moviment del robot.
 * Aquestes criden a les tres anteriors a fi d'evitar repetir codi i fer més
 * robust el nostre programa.
 */

//aquesta funció atura el moviment del robot.
int robotStop();

//aquesta funció mou el robot en línea recta de forma contínua, en la direcció en la
// que mira, a la velocitat passada i en el sentit corresponent al signe d'aquesta.
int robotMoveContinuous(int16_t speed);

//el robot gira sobre sí mateix amb la velocitat proporcionada
//(si és positiva, sentit antihorari, si és negativa, sentit horari)
int robotSpinContinuous(int16_t speed);

// aquesta funció mou el robot cap a la direcció especificada (1
//és cap a l'esquerra, 0 és cap a la dreta), a la velocitat especificada
//(suposem que és la de la roda més ràpida), cap endavant si la velocitat
//és positiva i cap endarrera si la velocitat és negativa.
int moveSideContinuous(int16_t speed, int side);




/*
 * Aquestes funcions controlen més finament el moviment del robot.
 * de moment no les implementarem per a aquesta pràctica.
 * Tindran en compte les mesures del robot i substituiran les anteriors funcions.
 * Utilitzaran també timers, que al final no hem d'implementar en aquesta pràctica
 * Les unitats proporcionades seran metres, metres per segon, radiants i radiants per segon.
 */

//el mateix que la versió contínua, però per a un temps concret. Quan passa el temps s'atura.
int robotMoveTime(int16_t speed, float time);

//el mateix que RobotMoveContinuous, però la velocitat ve donada en unitats reals.
int robotMoveContinuousRealSpeed(float speed);

//el mateix que la versió contínua, però per a una distància concreta. Quan la recorre s'atura.
int robotMoveDistance(float speed, float distance);

//el mateix que en la versió contínua, però al cap d'un temps proporcionat s'atura
int robotSpinTime(int16_t speed, float time);

// aquesta funció mou el robot en un arc de circumferència de radi especificat,
// a la velocitat angular especificada, cap endavant si és positiva i cap endarrera si és negativa,
// i en el sentit especificat pel signe del radi (si el radi és positiu, el centre és a l'esquerra
// del robot, si és negatiu, és a la dreta del robot (observem que, en el cas particular de radi 0,
//el centre de gir és al centre del robot i la funció fa el mateix que robotSpinContinuous)
int robotTurnContinuous(float angularSpeed, float radius);

int moveSideTime(int16_t speed, bool side, float time);

//el mateix que la funció anterior, però per a un angle concret de gir. Quan el recorre s'atura.
int robotTurnAngle(float angularSpeed, float radius, float angle);

