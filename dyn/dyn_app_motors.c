//
// Created by ferra on 16-Apr-20.
//



#include "dyn_app_motors.h"
#include "timers.h"
#include "dyn_instr.h"
#include <stdlib.h>

//TODO: implementar les funcions del header

int dyn_turnContinuous(uint8_t id){
    uint8_t vals[4] = {0x00, 0x00, 0x00, 0x00};
    return dyn_write(id, DYN_REG__CW_ANGLE_LIMIT_L, vals, 4);
}

int dyn_setTurnSpeed(uint8_t id, uint16_t speed, bool direction){}//TODO

int dyn_stop(uint8_t id){}//TODO

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

    //trobem el valor absolut de la velocitat.
    uint16_t absSpeed = abs(speed);

    //Si la velocitat és més gran que la màxima, posem els motors a màxima velocitat.
    if(absSpeed > DYN_MAX_SPEED){absSpeed = DYN_MAX_SPEED;}

    //Fem les operacions per a canviar la velocitat i direcció dels motors

    //si anem cap endavant (sign és true), volem que la roda esquerra giri en sentit antihorari, i, si és false, horari
    int speedLeft = dyn_setTurnSpeed(ID_MOTOR_LEFT, absSpeed, !sign);
    //si anem cap endavant (sign és true), volem que la roda esquerra giri en sentit horari, i, si és false, antihorari
    int speedRight = dyn_setTurnSpeed(ID_MOTOR_RIGHT, absSpeed, sign);

    //Creem un array amb els returns de les funcions bàsiques.
    int returns[4] = {setupLeft, setupRight, speedLeft, speedRight};

    //Si alguna ha donat algun error (return major que 0), el retornem.
    for(int i = 0; i < 4; i++){
        if(returns[i] > 0){return returns[i];}
    }

    //Si no hi ha hagut cap error, retornmem 0.
    return 0;
}