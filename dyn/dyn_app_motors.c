//
// Created by ferra on 16-Apr-20.
//



#include "dyn_app_motors.h"
#include <stdlib.h>

//TODO: implementar les funcions del header

/*Com no tenim accés al robot,
 *
 *
 */

int robotStop(){

    //Aturem els dos motors
    int left = dyn_stop(ID_MOTOR_LEFT);
    int right = dyn_stop(ID_MOTOR_RIGHT);

    //Si algun dels dos motors dóna error (retorna alguna cosa diferent de 0), retornem aquest error. Si no, retornem 0.
    if(left > 0){return left;}
    return right;
}

int robotMoveContinuous(int16_t speed){

    //Si li passem el valor 0, aturem el robot.
    if(speed == 0){return robotStop();}

    //Posem els mòduls en mode turnContinuous
    int setupLeft = dyn_turnContinuous(ID_MOTOR_LEFT);
    int setupRight = dyn_turnContinuous(ID_MOTOR_RIGHT);

    //Mirem el signe de la velocitat per a saber en quina direcció hem de girar les rodes
    bool sign = (speed > 0);

    //si la velocitat és positiva, tira endavant i la roda de l'esquerra gira en sentit antihorari, i viceversa.
    int directionLeft = dyn_setTurnDirection(ID_MOTOR_LEFT, !sign);
    //si la velocitat és positiva, tira endavant i la roda de la dreta gira en sentit horari, i viceversa.
    int dierctionRight = dyn_setTurnDirection(ID_MOTOR_RIGHT, sign);

    //trobem el valor absolut de la velocitat.
    uint16_t absSpeed = abs(speed);

    //Si la velocitat és més gran que la màxima, posem els motors a màxima velocitat.
    if(absSpeed > DYN_MAX_SPEED){absSpeed = DYN_MAX_SPEED;}

    //Fem les operacions per a canviar el goalSped dels mòduls.
    int speedLeft = dyn_setTurnSpeed(ID_MOTOR_LEFT, absSpeed);
    int speedRight = dyn_setTurnSpeed(ID_MOTOR_RIGHT, absSpeed);

    //Creem un array amb els returns de les funcions bàsiques.
    int returns[6] = {setupLeft, setupRight, directionLeft, dierctionRight, speedLeft, speedRight};

    //Si alguna ha donat algun error (return major que 0), el retornem.
    for(int i = 0; i < 6; i++){
        if(returns[i] > 0){return returns[i];}
    }

    //Si no hi ha hagut cap error, retornmem 0.
    return 0;
}