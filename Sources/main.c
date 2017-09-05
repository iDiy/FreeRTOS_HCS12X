#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



#include <string.h>
#include "xgate.h"
#include "mcu.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* Demo application includes. */
#include "flash.h"
#include "PollQ.h"
#include "dynamic.h"
#include "partest.h"
#include "comtest2.h"
#include "BlockQ.h"
#include "integer.h"
#include "death.h"

#if 0
#pragma push

/* this variable definition is to demonstrate how to share data between XGATE and S12X */
#pragma DATA_SEG SHARED_DATA
volatile int shared_counter; /* volatile because both cores are accessing it. */

/* Two stacks in XGATE core3 */ 
#pragma DATA_SEG XGATE_STK_L
word XGATE_STACK_L[1]; 
#pragma DATA_SEG XGATE_STK_H
word XGATE_STACK_H[1];

#pragma pop
#endif

#define ROUTE_INTERRUPT(vec_adr, cfdata)                \
  INT_CFADDR= (vec_adr) & 0xF0;                         \
  INT_CFDATA_ARR[((vec_adr) & 0x0F) >> 1]= (cfdata)

#define SOFTWARETRIGGER0_VEC  0x72 /* vector address= 2 * channel id */

static void SetupXGATE(void) {
  /* initialize the XGATE vector block and
     set the XGVBR register to its start address */
  XGVBR= (unsigned int)(void*__far)(XGATE_VectorTable - XGATE_VECTOR_OFFSET);

  /* switch software trigger 0 interrupt to XGATE */
  ROUTE_INTERRUPT(SOFTWARETRIGGER0_VEC, 0x81); /* RQST=1 and PRIO=1 */

  /* when changing your derivative to non-core3 one please remove next five lines */
  #if 0
  XGISPSEL= 1;
  XGISP31= (unsigned int)(void*__far)(XGATE_STACK_L + 1);
  XGISPSEL= 2;
  XGISP74= (unsigned int)(void*__far)(XGATE_STACK_H + 1);
  XGISPSEL= 0;
  #endif

  /* enable XGATE mode and interrupts */
  XGMCTL= 0xFBC1; /* XGE | XGFRZ | XGIE */

  /* force execution of software trigger 0 handler */
  XGSWT= 0x0101;
}


/*-----------------------------------------------------------
	Definitions.
-----------------------------------------------------------*/

/* Priorities assigned to demo application tasks. */
#define mainFLASH_PRIORITY			( tskIDLE_PRIORITY + 2 )
#define mainCHECK_TASK_PRIORITY		( tskIDLE_PRIORITY + 3 )
#define mainQUEUE_POLL_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define mainCOM_TEST_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define mainBLOCK_Q_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define mainDEATH_PRIORITY			( tskIDLE_PRIORITY + 1 )

/* LED that is toggled by the check task.  The check task periodically checks
that all the other tasks are operating without error.  If no errors are found
the LED is toggled with mainCHECK_PERIOD frequency.  If an error is found 
then the toggle rate increases to mainERROR_CHECK_PERIOD. */
#define mainCHECK_TASK_LED			( 7 )
#define mainCHECK_PERIOD			( ( TickType_t ) 3000 / portTICK_PERIOD_MS  )
#define mainERROR_CHECK_PERIOD		( ( TickType_t ) 500 / portTICK_PERIOD_MS )

/* The constants used in the idle task calculation. */
#define intgCONST1				( ( long ) 123 )
#define intgCONST2				( ( long ) 234567 )
#define intgCONST3				( ( long ) -3 )
#define intgCONST4				( ( long ) 7 )
#define intgEXPECTED_ANSWER		( ( ( intgCONST1 + intgCONST2 ) * intgCONST3 ) / intgCONST4 )


/* Baud rate used by the serial port tasks (ComTest tasks).
IMPORTANT:  The function COM0_SetBaudRateValue() which is generated by the
Processor Expert is used to set the baud rate.  As configured in the FreeRTOS
download this value must be one of the following:

0 to configure for 38400 baud.
1 to configure for 19200 baud.
2 to configure for 9600 baud.
3 to configure for 4800 baud. */
#define mainCOM_TEST_BAUD_RATE			( ( unsigned long ) 2 )

/* LED used by the serial port tasks.  This is toggled on each character Tx,
and mainCOM_TEST_LED + 1 is toggles on each character Rx. */
#define mainCOM_TEST_LED				( 3 )

/*-----------------------------------------------------------
	Local functions prototypes.
-----------------------------------------------------------*/

/*
 * The 'Check' task function.  See the explanation at the top of the file.
 */
static void vErrorChecks( void* pvParameters );

/*
 * The idle task hook - in which the integer task is implemented.  See the
 * explanation at the top of the file.
 */
void vApplicationIdleHook( void );

/*
 * Checks the unique counts of other tasks to ensure they are still operational.
 */
static long prvCheckOtherTasksAreStillRunning( void );



/*-----------------------------------------------------------
	Local variables.
-----------------------------------------------------------*/

/* A few tasks are defined within this file.  This flag is used to indicate
their status.  If an error is detected in one of the locally defined tasks then
this flag is set to pdTRUE. */
portBASE_TYPE xLocalError = pdFALSE;


/*-----------------------------------------------------------*/

/* 
 * This is called from the main() function generated by the Processor Expert.
 */
void vMain( void )
{
	/* Start some of the standard demo tasks. */
	vStartLEDFlashTasks( mainFLASH_PRIORITY );
	#if 0
	vStartPolledQueueTasks( mainQUEUE_POLL_PRIORITY );
	vStartDynamicPriorityTasks();
	vAltStartComTestTasks( mainCOM_TEST_PRIORITY, mainCOM_TEST_BAUD_RATE, mainCOM_TEST_LED );
	vStartBlockingQueueTasks( mainBLOCK_Q_PRIORITY );
	vStartIntegerMathTasks( tskIDLE_PRIORITY );
		
	/* Start the locally defined tasks.  There is also a task implemented as
	the idle hook. */
	xTaskCreate( vErrorChecks, "Check", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
	
	/* Must be the last demo created. */
	vCreateSuicidalTasks( mainDEATH_PRIORITY );
	#endif

	/* All the tasks have been created - start the scheduler. */
	vTaskStartScheduler();
	
	/* Should not reach here! */
	for( ;; );
}
/*-----------------------------------------------------------*/

static void vErrorChecks( void *pvParameters )
{
TickType_t xDelayPeriod = mainCHECK_PERIOD;
TickType_t xLastWakeTime;

	/* Initialise xLastWakeTime to ensure the first call to vTaskDelayUntil()
	functions correctly. */
	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Delay until it is time to execute again.  The delay period is 
		shorter following an error. */
		vTaskDelayUntil( &xLastWakeTime, xDelayPeriod );

		/* Check all the demo application tasks are executing without 
		error. If an error is found the delay period is shortened - this
		has the effect of increasing the flash rate of the 'check' task
		LED. */
		if( prvCheckOtherTasksAreStillRunning() == pdFAIL )
		{
			/* An error has been detected in one of the tasks - flash faster. */
			xDelayPeriod = mainERROR_CHECK_PERIOD;
		}

		/* Toggle the LED each cycle round. */
		vParTestToggleLED( mainCHECK_TASK_LED );
	}
}
/*-----------------------------------------------------------*/

static long prvCheckOtherTasksAreStillRunning( void )
{
portBASE_TYPE xAllTasksPassed = pdPASS;

	if( xArePollingQueuesStillRunning() != pdTRUE )
	{
		xAllTasksPassed = pdFAIL;
	}

	if( xAreDynamicPriorityTasksStillRunning() != pdTRUE )
	{
		xAllTasksPassed = pdFAIL;
	}

	if( xAreComTestTasksStillRunning() != pdTRUE )
	{
		xAllTasksPassed = pdFALSE;
	}

	if( xAreIntegerMathsTaskStillRunning() != pdTRUE )
	{
		xAllTasksPassed = pdFALSE;
	}
	
	if( xAreBlockingQueuesStillRunning() != pdTRUE )
	{
		xAllTasksPassed = pdFALSE;
	}	

    if( xIsCreateTaskStillRunning() != pdTRUE )
    {
    	xAllTasksPassed = pdFALSE;
    }

	/* Also check the status flag for the tasks defined within this function. */
	if( xLocalError != pdFALSE )
	{
		xAllTasksPassed = pdFAIL;
	}
	
	return xAllTasksPassed;
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
/* This variable is effectively set to a constant so it is made volatile to
ensure the compiler does not just get rid of it. */
volatile long lValue;

	/* Keep performing a calculation and checking the result against a constant. */

	/* Perform the calculation.  This will store partial value in
	registers, resulting in a good test of the context switch mechanism. */
	lValue = intgCONST1;
	lValue += intgCONST2;
	lValue *= intgCONST3;
	lValue /= intgCONST4;

	/* Did we perform the calculation correctly with no corruption? */
	if( lValue != intgEXPECTED_ANSWER )
	{
		/* Error! */
		portENTER_CRITICAL();
			xLocalError = pdTRUE;
		portEXIT_CRITICAL();
	}

	/* Yield in case cooperative scheduling is being used. */
	#if configUSE_PREEMPTION == 0
	{
		taskYIELD();
	}
	#endif		
}
/*-----------------------------------------------------------*/




void main(void) {
  /* put your own code here */
  MCUInit(32);
  
//SetupXGATE();
vMain();

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
