/*
 * main.h
 *
 *  Created on: 19 mar. 2020
 *      Author: droma
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

sem_t* sem_tx_msp;
sem_t* sem_tx_cli;

#endif /* MAIN_H_ */
