//
// Created by ferra on 16-Apr-20.
//



#include "dyn_app_motors.h"
#include "timers.h"
#include "dyn_instr.h"
#include <stdlib.h>

int dyn_turnContinuous(uint8_t id){
    uint8_t vals[4] = {0x00, 0x00, 0x00, 0x00};
    return dyn_write(id, DYN_REG__CW_ANGLE_LIMIT_L, vals, 4);
}

int dyn_setTurnSpeed(uint8_t id, uint16_t speed, bool direction){

    //agafem els últims 8 bits de la velocitat.
    uint8_t low = speed & 0xff;
    //agafem els primers 8bits de la velocitat.
    uint8_t high = (speed >> 8);

    //si s'ha de moure el el sentit de les agulles del rellotge, posem un 1 al bit de direcció.
    if(direction){high += 0x04;}

    //posem els valors a escriure a memòria en un array
    uint8_t data[2] = {low, high};

    //escrivim els valors a la memòria, i retornem la resposta que axò doni.
    return dyn_write(id, DYN_REG__MOVING_SPEED_L, data, 2);

}

int dyn_stop(uint8_t id){
    //Posem la velocitat amb la id seleccionada a 0. Posem turn direction en sentit horari, do forma arbitrària.
    return dyn_setTurnSpeed(id, 0, true);
}

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

int robotSpinContinuous(int16_t speed){

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

    //Si girem sobre nosaltres mateixos en sentit antihorari (sign és true), volem que les rodes girin en sentit horari, i, si és false, antihorari
    int speedLeft = dyn_setTurnSpeed(ID_MOTOR_LEFT, absSpeed, sign);
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

int moveSideContinuous(int16_t speed, int side) {
    //Si li passem el valor 0, aturem el robot.
    if (speed == 0) { return robotStop(); }

    //Posem els mòduls en mode turnContinuous
    int setupLeft = dyn_turnContinuous(ID_MOTOR_LEFT);
    int setupRight = dyn_turnContinuous(ID_MOTOR_RIGHT);

    //Mirem el signe de la velocitat per a saber en quina direcció hem de girar les rodes
    bool sign = (speed > 0);

    //trobem el valor absolut de la velocitat.
    uint16_t absSpeed = abs(speed);

    //Si la velocitat és més gran que la màxima, posem els motors a màxima velocitat.
    if (absSpeed > DYN_MAX_SPEED) { absSpeed = DYN_MAX_SPEED; }

    //Fem les operacions per a canviar la velocitat i direcció dels motors, mirant primer de tot el costat
    //cap on volem anar. Si el side es positiu, ESQUERRA, per tant haurem de reduir a la meitat la velocitat
    // de la roda de la l'esquerra. Si el side es negatiu, DRETA, per tant haurem de reduir a la meitat la
    //velocitat de la roda de la dreta.
    int speedLeft = 0;
    int speedRight = 0;
    if (side == 1) {
        //ESQUERRA.
        //Si anem cap endavant (sign és true), volem que la roda esquerra giri en sentit antihorari, i, si és false, horari
        speedLeft = dyn_setTurnSpeed(ID_MOTOR_LEFT, absSpeed / 2, !sign);
        //Si anem cap endavant (sign és true), volem que la roda dreta giri en sentit horari, i, si és false, antihorari
        speedRight = dyn_setTurnSpeed(ID_MOTOR_RIGHT, absSpeed, sign);
    } else {
        //DRETA
        //Si anem cap endavant (sign és true), volem que la roda esquerra giri en sentit antihorari, i, si és false, horari
        speedLeft = dyn_setTurnSpeed(ID_MOTOR_LEFT, absSpeed, !sign);
        //Si anem cap endavant (sign és true), volem que la roda dreta giri en sentit horari, i, si és false, antihorari
        speedRight = dyn_setTurnSpeed(ID_MOTOR_RIGHT, absSpeed / 2, sign);
    }



    //Creem un array amb els returns de les funcions bàsiques.
    int returns[4] = {setupLeft, setupRight, speedLeft, speedRight};

    //Si alguna ha donat algun error (return major que 0), el retornem.
    for (int i = 0; i < 4; i++) {
        if (returns[i] > 0) { return returns[i]; }
    }

    //Si no hi ha hagut cap error, retornmem 0.
    return 0;
}

int dyn_readTurnSpeed(uint8_t id, uint16_t *speed, bool *direction){

    //creem variables on guardarem els bytes que volem llegir
    uint8_t valL;
    uint8_t valH;

    //llegim els bytes corresponents a la turn speed.
    int read1 = dyn_read_byte(id, DYN_REG__MOVING_SPEED_L, &valL);
    int read2 = dyn_read_byte(id, DYN_REG__MOVING_SPEED_H, &valH);

    //concatenem els bytes i treiem el bit de direcció
    *speed = (valL + (valH << 8)) & 0x3ff;

    //obtenim el signe
    *direction = valH >> 2;

    //si hi ha hagut algun error al llegir, retornem 1. Si no, retornem 0.
    return (read1 > 0) | (read2 > 0);
}

int dyn_readTurnContinuous(uint8_t id, bool *continuous){

    //creem una variable temporal per a llegir els registres de la memòria del mòdul Dynamixel corresponent als angle limits.
    uint8_t tmp;
    //creem una variable per a guardar possibles errors de lectura.
    int read;

    //llegim un dels valors a comprovar
    read = dyn_read_byte(id, DYN_REG__CW_ANGLE_LIMIT_L, &tmp);
    //Si hi ha error de lectura, suposem que el robot no està en el mode endless turn (arbitràriament) i retornem un error
    if(read != 0){ *continuous = false; return 1;}
    //Si el valor llegit és diferent de 0, no estem en mode endless turn. S'ha fet la comprovació amb èxit i retornem 0
    if(tmp != 0x00){*continuous = false; return 0;}

    //Repetim el mateix per a la resta:

    read = dyn_read_byte(id, DYN_REG__CW_ANGLE_LIMIT_H, &tmp);
    if(read != 0){ *continuous = false; return 2;}
    if(tmp != 0x00){*continuous = false; return 0;}

    read = dyn_read_byte(id, DYN_REG__CCW_ANGLE_LIMIT_L, &tmp);
    if(read != 0){ *continuous = false; return 3;}
    if(tmp != 0x00){*continuous = false; return 0;}

    read = dyn_read_byte(id, DYN_REG__CCW_ANGLE_LIMIT_H, &tmp);
    if(read != 0){ *continuous = false; return 4;}
    if(tmp != 0x00){*continuous = false; return 0;}

    //Si tot l'anterior no ha retornat false ni hi ha hagut cap error de lectura, estem en mode endless turn:
    *continuous = true;
    return 0;



}