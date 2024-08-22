


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
#include<freertos/event_groups.h>

// Bit masks for the events
#define TEMP_EVENT_BIT      (1 << 0)  // Event bit 0 (temperature)
#define PRESSURE_EVENT_BIT  (1 << 1)  // Event bit 1 (pressure)


void DAVE_Initialsisation(void);

void Temperature(void *pvparameters);
void Pressure(void *pvparameters);
void Calibration(void *pvparameters);

TimerHandle_t Motor_timer_hadle;
TaskHandle_t temp_handle,pressure_handle,calibration_handle;

//Event Group handler

EventGroupHandle_t xSensorEG;

uint32_t temp_eventbit;
uint32_t pressure_eventbit;
uint32_t allbits;

int main(void){


	BaseType_t status;

	DAVE_Initialsisation();



	xSensorEG = xEventGroupCreate();
    if (xSensorEG == NULL) {

        return 1;
    }
	xTaskCreate(Temperature, "Temperature", 1024, NULL, 1, &temp_handle);

	xTaskCreate(Pressure, "Pressure", 1024, NULL, 1, &pressure_handle);

	xTaskCreate(Calibration, "Calibration", 1024, NULL, 2, &calibration_handle);



	vTaskStartScheduler();



}

void Temperature(void *pvparameters)
{

	const char* pdata = "Running Temperature\r\n";
	uint8_t size = strlen(pdata)+1;
	uint8_t Send_Data[size];


	while(1)
	{
		sprintf((char*)Send_Data,"%s",pdata);
		UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);
		//vTaskDelay(pdMS_TO_TICKS(1000));  //u can keep pooling delay for understanding
		  for(int i = 0; i < 0xFFFFF;i++);
		xEventGroupSetBits(xSensorEG, TEMP_EVENT_BIT);  // Signal temperature event  when it completes

	}

}



void Pressure(void *pvparameters)
{

	const char* pdata = "Running Pressure\r\n";
	uint8_t size = strlen(pdata)+1;
	uint8_t Send_Data[size];


	while(1)
	{
		 sprintf((char*)Send_Data,"%s",pdata);
		 UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);
		// vTaskDelay(pdMS_TO_TICKS(1000)); //u can keep pooling delay for understanding
         for(int i = 0; i < 0xFFFFF;i++);
		 xEventGroupSetBits(xSensorEG, PRESSURE_EVENT_BIT);  // Signal pressure event when it completes

	}

}

void Calibration(void *pvparameters)
{
	const char* pdata = "calibration task started\r\n";
	const char* pdata1 = "calibration task finished\r\n";

	uint8_t size = strlen(pdata)+1,size1 = strlen(pdata1)+1;
	uint8_t Send_Data[size],Send_Data1[size1];
	uint32_t result;

	while(1)
	{
		sprintf((char*)Send_Data,"%s",pdata);
		UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);

		result = xEventGroupWaitBits(xSensorEG, TEMP_EVENT_BIT | PRESSURE_EVENT_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

        if ((result & (TEMP_EVENT_BIT | PRESSURE_EVENT_BIT)) == (TEMP_EVENT_BIT | PRESSURE_EVENT_BIT))
        {

     //Calibrate here when you received completion signal of both temperature and pressure.

    	sprintf((char*)Send_Data1,"%s",pdata1);
    	UART_Transmit(&UART_0,(uint8_t*) Send_Data1, sizeof(Send_Data1)-1);


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






