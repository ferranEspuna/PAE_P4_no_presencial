
#include <stdint.h>
#include "dyn_instr.h"
#include "dyn_app_sensor.h"
#include "dyn_instr.h"


int dyn_readDistanceLeft(uint8_t id, uint8_t *distance){
    //Cridem a la funció read_byte amb la variable a la que volem assignar el valor i el número del registre que ens interessa.
    return dyn_read_byte(id, DYN_REG__DISTANCE_LEFT, distance);
}

int dyn_readDistanceCenter(uint8_t id, uint8_t *distance){
    //Cridem a la funció read_byte amb la variable a la que volem assignar el valor i el número del registre que ens interessa.
    return dyn_read_byte(id, DYN_REG__DISTANCE_CENTER, distance);
}

int dyn_readDistanceRight(uint8_t id, uint8_t *distance){
    //Cridem a la funció read_byte amb la variable a la que volem assignar el valor i el número del registre que ens interessa.
    return dyn_read_byte(id, DYN_REG__DISTANCE_RIGHT, distance);
}



