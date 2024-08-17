
//CDAC example
//TASK a give sema key for every 2sec o TASK B


#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable/GCC/portmacro_mpu.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

SemaphoreHandle_t xSemaphore;
TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;


int global_var=0;

typedef	struct student{

	char name[7];
	uint8_t roll_no;

}student_t;

void sensortask_1(void *pvparameters);
void Alarmtask_1(void *pvparameters);
void Task_3(void *pvparameters);
void ButtonTask(void *pvparameters);

void DAVE_Initialsisation(void);

//Semaphore..

TaskHandle_t xManager_Handle_1,xEmployee_Handle_2;
SemaphoreHandle_t xWork;
void Manager(void *pvparameters);
void Employee(void *pvparameters);

int main(void)
{

	DAVE_Initialsisation();

	xSemaphore = xSemaphoreCreateCounting( 5, 1 );
	if( xSemaphore != NULL )
	{
		printf("counting semaphore created successfully!\n");
	}
	BaseType_t result;

	result=xTaskCreate(sensortask_1,"sensortask_1",2048,NULL,5,&xHandle_1);

	if(result==pdPASS)
	{
		printf("sensortask created\n");
	}
	result=xTaskCreate(Alarmtask_1,"Alarmtask_1",2048,NULL,5,&xHandle_2);

	if(result==pdPASS)
	{
		printf("Alarmtask created\n");
	}

	vTaskStartScheduler();

}


void sensortask_1(void *pvparameters)
{

	while(1)
	{
		xSemaphoreTake(xSemaphore,portMAX_DELAY);
		global_var++;
		printf("SENSOR TASK  RUNNING: %d\n",global_var);

	}

}
void Alarmtask_1(void *pvparameters)
{

	while(1)
	{

		xSemaphoreGive(xSemaphore);   //sending multiple latching events 
		xSemaphoreGive(xSemaphore);
		xSemaphoreGive(xSemaphore);
		xSemaphoreGive(xSemaphore);
		xSemaphoreGive(xSemaphore);
		xSemaphoreGive(xSemaphore);
		xSemaphoreGive(xSemaphore);
	//if value cannot increment more than 5.
		vTaskDelay(7000/ portTICK_PERIOD_MS);
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




