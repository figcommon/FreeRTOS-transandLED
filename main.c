#include "sys.h"
#include "delay.h"
#include "led.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xfffff )

void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

int main( void )
{
	
	delay_init(168);		  
	LED_Init();		        
  
	SystemInit();

  SystemCoreClockUpdate();
	
	xTaskCreate(vTask1,"Task 1",240,NULL,1,NULL );		
	
	xTaskCreate(vTask2, "Task 2",240,NULL,1, NULL);
	
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
}

void vTask1( void *pvParameters )
{
const char *pcTaskName = "Task 1 is running\n";
volatile unsigned long ul;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		//GPIO_ResetBits(GPIOA,GPIO_Pin_6); LED0????GPIOF.9??,?  ??LED0=0;
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
		delay_ms(110);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
		delay_ms(110);
	}
} 

void vTask2( void *pvParameters )
{
const char *pcTaskName = "Task 2 is running\n";
volatile unsigned long ul;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		//GPIO_ResetBits(GPIOA,GPIO_Pin_7); LED1????GPIOF.10??,? ??LED1=0;
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
		delay_ms(100);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
		delay_ms(100);
	}
}


void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}