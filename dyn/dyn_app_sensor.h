/*
 * dyn_sensor.h
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 */

#ifndef DYN_SENSOR_H_
#define DYN_SENSOR_H_
#include <stdbool.h>
#include <stdint.h>




#endif /* DYN_SENSOR_H_ */

//El mòdul del sensor tindrà la id 3 en el nostre projecte
static const uint8_t ID_SENSOR = 3;


//Aquesta funció llegeix el valor del sensor IR de l'esquerra i assigna a la variable passada aqest valor
int dyn_readDistanceLeft(uint8_t id, uint8_t *distance);

//Aquesta funció llegeix el valor del sensor IR del centre i assigna a la variable passada aqest valor
int dyn_readDistanceCenter(uint8_t id, uint8_t *distance);

//Aquesta funció llegeix el valor del sensor IR de la dreta i assigna a la variable passada aqest valor
int dyn_readDistanceRight(uint8_t id, uint8_t *distance);