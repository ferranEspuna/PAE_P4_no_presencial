#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>

#include "main.h"
#include "../dyn/dyn_app_common.h"
#include "../dyn_test/dyn_emu.h"
#include "../dyn_test/b_queue.h"
#include "../joystick_emu/joystick.h"
#include "../dyn/dyn_app_motors.h"

uint8_t estado = Ninguno, estado_anterior = Ninguno, finalizar = 0;
/**
 * main.c
 */
int main(void)
{
	pthread_t tid, jid;
	uint8_t tmp;
    uint16_t speed;
    bool direction;
    bool endless;

	//Init semaphores for TX data handshake
    sem_unlink("/semaphore_tx_msp");
    sem_unlink("/semaphore_tx_cli");
    sem_tx_msp = sem_open("/semaphore_tx_msp",O_CREAT,0644,0);
    sem_tx_cli = sem_open("/semaphore_tx_cli",O_CREAT,0644,0);

	//Init queue for RX data
	init_queue();

	//Start thread for dynamixel module emulation
	pthread_create(&tid, NULL, dyn_emu, (void*) &tid);
	pthread_create(&jid, NULL, joystick_emu, (void*) &jid);



	/**
	 * Tests leds
	 */

	 /*
	//Testing some high level function
	printf("MAIN: Setting LED to 0 \n");
    dyn_led_control(1, 0);
    printf("MAIN: Getting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 0);
    printf("MAIN: Setting LED to 1 \n");
	dyn_led_control(1, 1);
	printf("MAIN: Getting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 1);
	*/

    /**
     * Tests movimient continu
     */

    //Posem el robot en mode moviment continu.
    robotMoveContinuous(1000);
    //Comprovem que el motor esquerre estigui en mode endless turn.
    dyn_readTurnContinuous(ID_MOTOR_LEFT, &endless);
    assert(endless == true);
    //El mateix per al motor dret
    dyn_readTurnContinuous(ID_MOTOR_RIGHT, &endless);
    assert(endless == true);

    //Llegim la velocitat i direcció del mòdul esquerre i comprovem que són els esperats.
	dyn_readTurnSpeed(ID_MOTOR_LEFT, &speed, &direction);
	assert(speed == 1000);
	assert(direction == false);

	//El mateix per al mòdul dret.
    dyn_readTurnSpeed(ID_MOTOR_RIGHT, &speed, &direction);
    assert(speed == 1000);
    assert(direction == true);


    //Repetim amb velocitat negativa, per a veure si es posa en la direcció contrària.
    robotMoveContinuous(-3);

    dyn_readTurnSpeed(ID_MOTOR_LEFT, &speed, &direction);
    assert(speed == 3);
    assert(direction == true);

    dyn_readTurnSpeed(ID_MOTOR_RIGHT, &speed, &direction);
    assert(speed == 3);
    assert(direction == false);


    //Repetim amb una velocitat superior a la màxima, per a veure si es posa a velocitat màxima.
    robotMoveContinuous(3000);

    dyn_readTurnSpeed(ID_MOTOR_LEFT, &speed, &direction);
    assert(speed == DYN_MAX_SPEED);
    assert(direction == false);

    dyn_readTurnSpeed(ID_MOTOR_RIGHT, &speed, &direction);
    assert(speed == DYN_MAX_SPEED);
    assert(direction == true);

    robotSpinContinuous(500);
    dyn_readTurnSpeed(1, &speed, &direction);
    assert(speed == 500);
    assert(direction == false);
    dyn_readTurnSpeed(2, &speed, &direction);
    assert(speed == 500);
    assert(direction == false);

    robotSpinContinuous(-400);
    dyn_readTurnSpeed(1, &speed, &direction);
    assert(speed == 400);
    assert(direction == true);
    dyn_readTurnSpeed(2, &speed, &direction);
    assert(speed == 400);
    assert(direction == true);

    //Volem anar cap endavant i a la dreta.
    moveSideContinuous(300,1);
    dyn_readTurnSpeed(1, &speed, &direction);
    assert(speed == 150);
    assert(direction == false);
    dyn_readTurnSpeed(2, &speed, &direction);
    assert(speed == 300);
    assert(direction == true);

    moveSideContinuous(-200,0);
    dyn_readTurnSpeed(1, &speed, &direction);
    assert(speed == 200);
    assert(direction == true);
    dyn_readTurnSpeed(2, &speed, &direction);
    assert(speed == 100);
    assert(direction == false);


    /**
     * Test de parada
     */

    //Cridem a la funció per a aturar el robot
    robotStop();

    //Comprovem que el mòdul esquerre està a velocitat 0
    dyn_readTurnSpeed(ID_MOTOR_LEFT, &speed, &direction);
    assert(speed == 0);

    //El mateix per al mòdul dret
    dyn_readTurnSpeed(ID_MOTOR_RIGHT, &speed, &direction);
    assert(speed == 0);



    printf("************************\n");
	printf("Test passed successfully :) \n");
	printf("Pulsar 'q' para terminar, qualquier tecla para seguir\r");







	fflush(stdout);//	return 0;

	while(estado != Quit)
	{
		Get_estado(&estado, &estado_anterior);
		if(estado != estado_anterior){
			Set_estado_anterior(estado);
			printf("estado = %d\n", estado);
			fflush(stdout);
			switch(estado){
			case Sw1:
				printf("Boton Sw1 ('a') apretado\n");
				break;
			case Sw2:
				printf("Boton Sw2 ('s') apretado\n");
				break;
			case Quit:
				printf("Adios!\n");
				break;
			//etc, etc...
			}
			fflush(stdout);
		}
	}
	printf("Programa terminado\n");
	//Signal the emulation thread to stop
	pthread_kill(tid, SIGTERM);
	pthread_kill(jid, SIGTERM);
}
