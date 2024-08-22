


#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable/GCC/portmacro_mpu.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include<freertos/timers.h>




void DAVE_Initialsisation(void);
void Inside_while(void);
void Task1(void *pvparameters);

TimerHandle_t Motor_timer_hadle;
TaskHandle_t Task1Handle;

void Turn_Motor_OFF(TimerHandle_t xTimer ){

	const char* pdata = "Turning Motor OFF\r\n";
	uint8_t size = strlen(pdata)+1;
	uint8_t Send_Data[size];

	sprintf((char*)Send_Data,"%s",pdata);
	UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);


}

int main(void){


	BaseType_t status;

	DAVE_Initialsisation();

	Motor_timer_hadle = xTimerCreate("MOTOR OFF",  //name
						pdMS_TO_TICKS(2000),  //duration
						pdTRUE,    //do you need autoreload means 2 sec \//	value is reloaded automatically

						NULL,   //if you have multiple timers then you are identified \	//	with this TimerID

						Turn_Motor_OFF); //after timer expires control goes to \this function

	status = xTaskCreate(Task1, "TASK1", 1024, NULL, 1, &Task1Handle);
	//start the timer only when user says to start

	xTimerStart(Motor_timer_hadle,0);


	vTaskStartScheduler();



}

void Task1(void *pvparameters)
{

	const char* pdata = "Running Task1 \r\n";
	uint8_t size = strlen(pdata)+1;
	uint8_t Send_Data[size];


	while(1)
	{
		sprintf((char*)Send_Data,"%s",pdata);
		 UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);
		 vTaskDelay(pdMS_TO_TICKS(1000));
	}

}

void DAVE_Initialsisation(void){

DAVE_STATUS_t status;

status = DAVE_Init();           /* Initialization of DAVE APPs  */

		if (status != DAVE_STATUS_SUCCESS)
		{
			/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
  XMC_DEBUG("DAVE APPs initialization failed\n");

  	  	  	  while(1U)
  	  	  	  	  {


  	  	  	  	  }

		}


}







