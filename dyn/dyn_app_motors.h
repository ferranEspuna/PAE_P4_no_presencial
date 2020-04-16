//
// Created by ferra on 16-Apr-20.
//

#ifndef JOYSTICK_DYN_APP_MOTORS_H
#define JOYSTICK_DYN_APP_MOTORS_H

#endif //JOYSTICK_DYN_APP_MOTORS_H
#include <stdbool.h>
#include <stdint.h>

/*
 *Les tres funcions següents permeten modificar valors dels registres dels
 * mòduls Dynamixel a fi de controlar el que fan els motors.
 */

//aquesta funció posa els motors del mòdul corresponent a la id passada a mode continuous turn
int turnContinuous(uint8_t id);

//aquesta funció posa la target speed del mòdul corresponent a la id passada a la velocitat passada
int setTurnSpeed(uint8_t id, uint16_t speed);

//aquesta funció posa el gir del mòdul corresponent a la id passada en el sentit passat (true és horari i false antihorari)
int setTurnDirection(uint8_t id, bool val);


/*
 *A continuació tenim funcions d'alt nivell per a controlar el moviment del robot.
 * Aquestes criden a les tres anteriors a fi d'evitar repetir codi i fer més
 * robust el nostre programa.
 */

//aquesta funció atura el moviment del robot.
int stop();

//aquesta funció mou el robot en línea recta de forma contínua, en la direcció en la
// que mira, a la velocitat passada i en el sentit corresponent al signe d'aquesta.
int robotMoveContinuous(int16_t speed);

//el mateix que la versió contínua, però per a un temps concret. Quan passa el temps s'atura.
int robotMoveTime(int16_t speed, float time);

//el robot gira sobre sí mateix amb la velocitat proporcionada
//(si és positiva, sentit antihorari, si és negativa, sentit horari)
int robotSpinContinuous(int16_t speed);

//el mateix que en la versió contínua, però al cap d'un temps proporcionat s'atura
int robotSpinTime(int16_t speed, float time);

// aquesta funció mou el robot cap a la direcció especificada (true
//és cap a l'esquerra, false és cap a la dreta), a la velocitat especificada
//(suposem que és la de la roda més lenta), cap endavant si la direcció
//és positiva i cap endarrera si la direcció és negativa.
int moveSideContinuous(int16_t speed, bool side);

int moveSideTime(int16_t speed, bool side, float time);


/*
 * Aquestes funcions controlen més finament el moviment del robot.
 * de moment no les implementarem per a aquesta pràctica.
 * Tindran en compte les mesures del robot i substituiran les anteriors funcions.
 * Les unitats proporcionades seran metres, metres per segon, radiants i radiants per segon.
 */

//el mateix que RobotMoveContinuous, però la velocitat ve donada en unitats reals.
int robotMoveContinuousRealSpeed(float speed);

//el mateix que la versió contínua, però per a una distància concreta. Quan la recorre s'atura.
int robotMoveDistance(float speed, float distance);

// aquesta funció mou el robot en un arc de circumferència de radi especificat,
// a la velocitat angular especificada, cap endavant si és positiva i cap endarrera si és negativa,
// i en el sentit especificat (true significa que el centre de gir és a la dreta del robot,
// false significa que és a l'esquerra)
int robotTurnContinuous(float angularSpeed, float radius, bool side);

//el mateix que la funció anterior, però per a un angle concret de gir. Quan el recorre s'atura.
int robotTurnAngle(float angularSpeed, float radius, bool direction, float angle);

