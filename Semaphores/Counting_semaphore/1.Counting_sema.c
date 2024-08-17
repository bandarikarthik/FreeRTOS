//Counting Semaphore. 
//best example 

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

TaskHandle_t xManager_Handle_1,xEmployee_Handle_2;
SemaphoreHandle_t xWork;
void Manager(void *pvparameters);
void Employee(void *pvparameters);

int main(void)
{

	DAVE_Initialsisation();

	BaseType_t status;
	xWork = xSemaphoreCreateCounting(5,0);//just creates

	configASSERT(xWork != NULL);

	status = xTaskCreate(Manager,"Manager",200,NULL,3,&xManager_Handle_1);

	configASSERT(status == pdPASS);

	status = xTaskCreate(Employee,"employee",200,NULL,1,&xEmployee_Handle_2);

	configASSERT(status == pdPASS);

	myQueue = xQueueCreate(1, sizeof( uint8_t ));  //this creation is very important it can save HEAP memory
	configASSERT(myQueue != NULL);


	vTaskStartScheduler();

}

void Manager(void *pvparameters)
{
uint8_t global,xTdata[] = "Sema Task sent\r\n";


global = 0;
	while(1)
	{
		global++;
		vTaskDelay(pdMS_TO_TICKS(1000));

		if(global == 2){

			global = 0;
			UART_Transmit(&UART_0,xTdata,sizeof(xTdata)-1);
			xSemaphoreGive(xWork);  //1
			xSemaphoreGive(xWork);  //2
			xSemaphoreGive(xWork);  //3

		}
	}
}

void Employee(void *pvparameters)
{
	uint8_t xTdata[] = "Sema Task received\r\n";


	while(1){

		xSemaphoreTake(xWork,portMAX_DELAY);  //wait until key is available. means it will go into block state until key
												//is given back.
		UART_Transmit(&UART_0, xTdata, sizeof(xTdata)-1);

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



/*after os-schedular starts manager task give key after 2sec
as employe is in block state coz there is no key availabe it means key will be available 
after 2 sec 

so   manager task gives 3 key, so when it goes to block state then employee task task key and decrement te semacount
internally 

back to back event occured also no problem it will execute




output

Sema Task sent
Sema Task received
Sema Task received
Sema Task received
Sema Task sent
Sema Task received
Sema Task received
Sema Task received
Sema Task sent
Sema Task received
Sema Task received
Sema Task received

*/
