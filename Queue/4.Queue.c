/*

#define ARRAY_SIZE 5U
typedef int sensorData_t[ARRAY_SIZE];
sensorData_t sensorData[5];

Basic one with one array having typedef send and receive queue

 */




#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable/GCC/portmacro_mpu.h>
#include <freertos\queue.h>

TaskHandle_t xHandle_1,xHandle_2,xHandle_3,Button_Task;

TaskHandle_t volatile next_task_handle;

QueueHandle_t myQueue;

typedef	struct student{

char name[7];
uint8_t roll_no;

}student_t;

 void Task_1(void *pvparameters);
 void Task_2(void *pvparameters);
 void Task_3(void *pvparameters);
 void ButtonTask(void *pvparameters);

#define ARRAY_SIZE 5U

typedef int sensorData_t[ARRAY_SIZE];

QueueHandle_t sensorQueue;

void DAVE_Initialsisation(void);

int main(void)
{

DAVE_Initialsisation();

BaseType_t status;

status = xTaskCreate(Task_1,"Task_1",200,NULL,3,&xHandle_1);

configASSERT(status == pdPASS);

status = xTaskCreate(Task_2,"Task_2",200,NULL,2,&xHandle_2);

configASSERT(status == pdPASS);

myQueue = xQueueCreate(5, sizeof( student_t* ));  //this creation is very important it can save HEAP memory
configASSERT(myQueue != NULL);

sensorQueue = xQueueCreate(5, sizeof( sensorData_t* ));  //this creation is very important it can save HEAP memory
configASSERT(sensorQueue != NULL);


   vTaskStartScheduler();

}

 void Task_1(void *pvparameters)
{

	 sensorData_t sensorData =  {1, 2, 3, 4, 5};
	 sensorData_t  *ptrsensorData;
	 ptrsensorData = &sensorData;
	 xQueueSend(sensorQueue,(void*)&ptrsensorData,0);

	while(1)
	{

      vTaskDelay(pdMS_TO_TICKS(1000));

	}

}

void Task_2(void *pvparameters)
{
	sensorData_t xrStudent,*pxrStudent;
	while(1){

		if(sensorQueue!=NULL){



				if(xQueueReceive(sensorQueue, (void*)&pxrStudent ,5)){

				/*	xrStudent[0] = (*pxrStudent)[0];
					xrStudent[1] = (*pxrStudent)[1];
					xrStudent[2] = (*pxrStudent)[2];
					xrStudent[3] = (*pxrStudent)[3];
					xrStudent[4] = (*pxrStudent)[4];
				 */

					 memcpy(xrStudent, *pxrStudent, sizeof(sensorData_t));

				}




		}
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
