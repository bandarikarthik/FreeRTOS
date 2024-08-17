//print priority of main, task1, task2 

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable/GCC/portmacro_mpu.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

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

//Semaphore..
uint8_t ReadData[2];
TaskHandle_t xManager_Handle_1,xEmployee_Handle_2;
SemaphoreHandle_t xWork;
void Manager(void *pvparameters);
void Employee(void *pvparameters);

int main(void)
{

	DAVE_Initialsisation();

	BaseType_t status;

	BaseType_t mainPriority;

	// Get the priority of the main task (before creating tasks)


	xWork = xSemaphoreCreateBinary(); //just creates
	configASSERT(xWork != NULL);

	xSemaphoreTake(xWork,0); //it will goes to next statement if sema not available as key is not present
							// if u keep or dont kep no issue

	status = xTaskCreate(Manager,"Manager",200,NULL,3,&xManager_Handle_1);

	configASSERT(status == pdPASS);

	status = xTaskCreate(Employee,"employee",200,NULL,1,&xEmployee_Handle_2);

	configASSERT(status == pdPASS);

	myQueue = xQueueCreate(1, sizeof(uint8_t ));  //this creation is very important it can save HEAP memory
	configASSERT(myQueue != NULL);

	UART_Receive(&UART_0, ReadData,2);

	mainPriority = uxTaskPriorityGet(NULL);  // Get Task A's priority
	printf("Task A Priority: %lu\n", (unsigned long)mainPriority);

	vTaskStartScheduler();

	while(1){


	}

}

void Manager(void *pvparameters)
{

	uint8_t global,xTdata[] = "Task_1\r\n";
	UBaseType_t priority;
	global = 0;
	while(1)
	{

		priority = uxTaskPriorityGet(NULL);  // Get Task A's priority
	    printf("Task A Priority: %lu\n", (unsigned long)priority);
	    vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for a second

	}
}

void Employee(void *pvparameters)
{
	uint8_t xTdata[] = "Sema Task received\r\n";
	UBaseType_t priority;
	while(1){

		priority = uxTaskPriorityGet(NULL);  // Get Task B's priority
		printf("Task B Priority: %lu\n", (unsigned long)priority);
		 vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for a second
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
