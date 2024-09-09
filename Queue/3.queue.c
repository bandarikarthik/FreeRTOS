/*
 * main.c
 *
 *  Created on: 2024 Jun 29 17:11:11
 *  Author: PC
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


   vTaskStartScheduler();

}

 void Task_1(void *pvparameters)
{
     student_t	*ps1,*ps2;
	 student_t	xstudent,xstudent2;

	 strcpy(xstudent.name ,"karthik");
	 xstudent.roll_no = 3;

	 strcpy(xstudent2.name ,"Asha");
	 xstudent2.roll_no = 4;

     ps1 = &xstudent;


  xQueueSend(myQueue,(void*)&ps1,0);

  ps1 = &xstudent2;

  xQueueSend(myQueue,(void*)&ps1,0);

	while(1)
	{

      vTaskDelay(pdMS_TO_TICKS(1000));

	}

}

void Task_2(void *pvparameters)
{
	student_t xrStudent[2],*pxrStudent;
	while(1){

		if(myQueue!=NULL){

	for(int i = 0;i < 2; i++){

			if(xQueueReceive(myQueue, (void*)&pxrStudent ,5)){

				strcpy(xrStudent[i].name , pxrStudent->name);

				xrStudent[i].roll_no =  pxrStudent->roll_no;

			}


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
/****************************************************************************************************************/


//enhance version in tASK 1




/*
 * main.c
 *
 *  Created on: 2024 Jun 29 17:11:11
 *  Author: PC
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


   vTaskStartScheduler();

}

 void Task_1(void *pvparameters)
{
     student_t	*ps1;
	 student_t	xstudent[2];

	 strcpy(xstudent[0].name ,"karthik");
	 xstudent[0].roll_no = 3;

	 strcpy(xstudent[1].name ,"Asha ji");
	 xstudent[1].roll_no = 4;

     ps1 = &xstudent[0];


  xQueueSend(myQueue,(void*)&ps1,0);

  ps1 = &xstudent[1];

  xQueueSend(myQueue,(void*)&ps1,0);

	while(1)
	{

      vTaskDelay(pdMS_TO_TICKS(1000));

	}

}

void Task_2(void *pvparameters)
{
	student_t xrStudent[2],*pxrStudent;
	while(1){

		if(myQueue!=NULL){

	for(int i = 0;i < 2; i++){

			if(xQueueReceive(myQueue, (void*)&pxrStudent ,5)){

				strcpy(xrStudent[i].name , pxrStudent->name);

				xrStudent[i].roll_no =  pxrStudent->roll_no;

			}


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


