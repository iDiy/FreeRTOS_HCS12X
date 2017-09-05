/******************************************************************************
*                                                     								              														                            
*                             Copyright (C) 2013 
*
* Tongji University - Freescale Automotive Electronics Laboratary, Inc.
* 
*                            All Rights Reserved	
* Filename:     vector.c                
*														                            
* Revision:     For S12XEP100 only 										                    
*														                            
* Functions:    vector locations of All msCAN module Interrupts
*														                            
* Description:  The file decides the vector locations of All msCAN module Interrupts
*
* Notes:        User can add new vector locations to other module but msCAN module        
*
******************************************************************************/
#include <hidef.h>    
#include <mc9s12xep100.h>     
//#include "xl_atd_averagecpu.h"

#pragma CODE_SEG __NEAR_SEG NON_BANKED
extern void near RTI_ISR(void);
extern void near SCI2_ISR(void);
extern void near SCI1_ISR(void);
extern void near SCI0_ISR(void);
extern void near SCI5_ISR(void);
extern void near SCI3_ISR(void);
extern void near SCI4_ISR(void);
extern void near SCI6_ISR(void);
extern void near SCI7_ISR(void);
extern void near /*118*/ vPortYield( void );
extern void near /*7*/ vPortTickInterrupt( void );

/* ISR prototype */
#define ISR(x) __interrupt void x(void)
typedef void (*near tIsrFunc)(void);
ISR(Cpu_Interrupt)
{
  /*lint -save -e950 Disable MISRA rule (1.1) checking. */
  asm(BGND);
  /*lint -restore Enable MISRA rule (1.1) checking. */
}

/******************************************************************************
 * ISRs
 ******************************************************************************/
__interrupt void 
CAN0_RxNotificationISR(void) 
{
  /* insert your code here */

  //Can0RxNotify();
                          /* clear XGATE channel interrupt flag */
  XGIF2 |= 0x0200;
}

/******************************************************************************
Function Name	:	CAN1_RxNotificationISR
Engineer		:	r27624	
Date			:	03/05/2004
Parameters		:	NONE
Returns			:	NONE
Notes			:	Notification of message received on CAN1 
******************************************************************************/
__interrupt void 
CAN1_RxNotificationISR(void) 
{
  /* insert your code here */
  
  //Can1RxNotify();
                          /* clear XGATE channel interrupt flag */
  XGIF2 |= 0x0020;
}

/******************************************************************************
Function Name	:	CAN2_RxNotificationISR
Engineer		:	r27624	
Date			:	03/05/2004
Parameters		:	NONE
Returns			:	NONE
Notes			:	Notification of message received on CAN2 
******************************************************************************/
__interrupt void 
CAN2_RxNotificationISR(void) 
{
  /* insert your code here */
  
  //Can2RxNotify();
                          /* clear XGATE channel interrupt flag */
  XGIF2 |= 0x0002;
}

/******************************************************************************
Function Name	:	CAN3_RxNotificationISR
Engineer		:	r27624	
Date			:	03/05/2004
Parameters		:	NONE
Returns			:	NONE
Notes			:	Notification of message received on CAN3 
******************************************************************************/
__interrupt void 
CAN3_RxNotificationISR(void) 
{
  /* insert your code here */
  
  //Can3RxNotify();
                          /* clear XGATE channel interrupt flag */
  XGIF3 |= 0x2000;
}

/******************************************************************************
Function Name	:	CAN4_RxNotificationISR
Engineer		:	r27624	
Date			:	03/05/2004
Parameters		:	NONE
Returns			:	NONE
Notes			:	Notification of message received on CAN4 
******************************************************************************/
__interrupt void 
CAN4_RxNotificationISR(void) 
{
  /* insert your code here */
  
  //Can4RxNotify();
                          /* clear XGATE channel interrupt flag */
    XGIF3 |= 0x0200;
}

#pragma CODE_SEG DEFAULT

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
static const tIsrFunc _InterruptVectorTable[] @0xFF10U = { /* Interrupt vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
  /* ISR name                               No.  Address Pri XGATE Name            Description*/
  &Cpu_Interrupt,                       /* 0x08  0xFF10   -   -    ivVsi           */
  &vPortYield,                       /* 0x09  0xFF12   -   -    ivVsyscall      */
  &Cpu_Interrupt,                       /* 0x0A  0xFF14   -   -    ivVmpuaccesserr */
  &Cpu_Interrupt,                       /* 0x0B  0xFF16   -   no   ivVxsei         */
  &Cpu_Interrupt,                       /* 0x0C  0xFF18   1   no   ivVReserved115  */
  &Cpu_Interrupt,                       /* 0x0D  0xFF1A   1   no   ivVReserved114  */
  &Cpu_Interrupt,                       /* 0x0E  0xFF1C   1   no   ivVReserved113  */
  &Cpu_Interrupt,                       /* 0x0F  0xFF1E   1   no   ivVReserved112  */
  &Cpu_Interrupt,                       /* 0x10  0xFF20   1   no   ivVReserved111  */
  &Cpu_Interrupt,                       /* 0x11  0xFF22   1   no   ivVReserved110  */
  &Cpu_Interrupt,                       /* 0x12  0xFF24   1   no   ivVReserved109  */
  &Cpu_Interrupt,                       /* 0x13  0xFF26   1   no   ivVReserved108  */
  &Cpu_Interrupt,                       /* 0x14  0xFF28   1   no   ivVReserved107  */
  &Cpu_Interrupt,                       /* 0x15  0xFF2A   1   no   ivVReserved106  */
  &Cpu_Interrupt,                       /* 0x16  0xFF2C   1   no   ivVReserved105  */
  &Cpu_Interrupt,                       /* 0x17  0xFF2E   1   no   ivVReserved104  */
  &Cpu_Interrupt,                       /* 0x18  0xFF30   1   no   ivVReserved103  */
  &Cpu_Interrupt,                       /* 0x19  0xFF32   1   no   ivVReserved102  */
  &Cpu_Interrupt,                       /* 0x1A  0xFF34   1   no   ivVReserved101  */
  &Cpu_Interrupt,                       /* 0x1B  0xFF36   1   no   ivVReserved100  */
  &Cpu_Interrupt,                       /* 0x1C  0xFF38   1   no   ivVReserved99   */
  &Cpu_Interrupt,                       /* 0x1D  0xFF3A   1   no   ivVReserved98   */
  &Cpu_Interrupt,                       /* 0x1E  0xFF3C   1   no   ivVatd1compare  */
  &Cpu_Interrupt,                       /* 0x1F  0xFF3E   1   no   ivVatd0compare  */
  &Cpu_Interrupt,                       /* 0x20  0xFF40   1   no   ivVtimpaie      */
  &Cpu_Interrupt,                       /* 0x21  0xFF42   1   no   ivVtimpaaovf    */
  &Cpu_Interrupt,                       /* 0x22  0xFF44   1   no   ivVtimovf       */
  &Cpu_Interrupt,                       /* 0x23  0xFF46   1   no   ivVtimch7       */
  &Cpu_Interrupt,                       /* 0x24  0xFF48   1   no   ivVtimch6       */
  &Cpu_Interrupt,                       /* 0x25  0xFF4A   1   no   ivVtimch5       */
  &Cpu_Interrupt,                       /* 0x26  0xFF4C   1   no   ivVtimch4       */
  &Cpu_Interrupt,                       /* 0x27  0xFF4E   1   no   ivVtimch3       */
  &Cpu_Interrupt,                       /* 0x28  0xFF50   1   no   ivVtimch2       */
  &Cpu_Interrupt,                       /* 0x29  0xFF52   1   no   ivVtimch1       */
  &Cpu_Interrupt,                       /* 0x2A  0xFF54   1   no   ivVtimch0       */
  &Cpu_Interrupt,                       /* 0x2B  0xFF56   1   no   ivVsci7         */
  &Cpu_Interrupt,                       /* 0x2C  0xFF58   1   no   ivVpit7         */
  &Cpu_Interrupt,                       /* 0x2D  0xFF5A   1   no   ivVpit6         */
  &Cpu_Interrupt,                       /* 0x2E  0xFF5C   1   no   ivVpit5         */
  &Cpu_Interrupt,                       /* 0x2F  0xFF5E   1   no   ivVpit4         */
  &Cpu_Interrupt,                       /* 0x30  0xFF60   1   no   ivVReserved79   */
  &Cpu_Interrupt,                       /* 0x31  0xFF62   1   no   ivVReserved78   */
  &Cpu_Interrupt,                       /* 0x32  0xFF64   1   no   ivVxst7         */
  &Cpu_Interrupt,                       /* 0x33  0xFF66   1   no   ivVxst6         */
  &Cpu_Interrupt,                       /* 0x34  0xFF68   1   no   ivVxst5         */
  &Cpu_Interrupt,                       /* 0x35  0xFF6A   1   no   ivVxst4         */
  &Cpu_Interrupt,                       /* 0x36  0xFF6C   1   no   ivVxst3         */
  &Cpu_Interrupt,                       /* 0x37  0xFF6E   1   no   ivVxst2         */
  &Cpu_Interrupt,                       /* 0x38  0xFF70   1   no   ivVxst1         */
  &Cpu_Interrupt,                       /* 0x39  0xFF72   1   no   ivVxst0         */
  &Cpu_Interrupt,                       /* 0x3A  0xFF74   1   no   ivVpit3         */
  &Cpu_Interrupt,                       /* 0x3B  0xFF76   1   no   ivVpit2         */
  &Cpu_Interrupt,                       /* 0x3C  0xFF78   1   no   ivVpit1         */
  &Cpu_Interrupt,                       /* 0x3D  0xFF7A   1   no   ivVpit0         */
  &Cpu_Interrupt,                       /* 0x3E  0xFF7C   1   -    ivVhti          */
  &Cpu_Interrupt,                       /* 0x3F  0xFF7E   1   no   ivVapi          */
  &Cpu_Interrupt,                       /* 0x40  0xFF80   1   no   ivVlvi          */
  &Cpu_Interrupt,                       /* 0x41  0xFF82   1   no   ivViic1         */
  &Cpu_Interrupt,                       /* 0x42  0xFF84   1   no   ivVsci5         */
  &Cpu_Interrupt,                       /* 0x43  0xFF86   1   no   ivVsci4         */
  &Cpu_Interrupt,                       /* 0x44  0xFF88   1   no   ivVsci3         */
  &Cpu_Interrupt,                       /* 0x45  0xFF8A   1   no   ivVsci2         */
  &Cpu_Interrupt,                       /* 0x46  0xFF8C   1   no   ivVpwmesdn      */
  &Cpu_Interrupt,                       /* 0x47  0xFF8E   1   no   ivVportp        */
  &Cpu_Interrupt,                       /* 0x48  0xFF90   1   no   ivVcan4tx       */
  &Cpu_Interrupt,                       /* 0x49  0xFF92   1   no   ivVcan4rx       */
  &Cpu_Interrupt,                       /* 0x4A  0xFF94   1   no   ivVcan4err      */
  &Cpu_Interrupt,                       /* 0x4B  0xFF96   1   no   ivVcan4wkup     */
  &Cpu_Interrupt,                       /* 0x4C  0xFF98   1   no   ivVcan3tx       */
  &Cpu_Interrupt,                       /* 0x4D  0xFF9A   1   no   ivVcan3rx       */
  &Cpu_Interrupt,                       /* 0x4E  0xFF9C   1   no   ivVcan3err      */
  &Cpu_Interrupt,                       /* 0x4F  0xFF9E   1   no   ivVcan3wkup     */
  &Cpu_Interrupt,                       /* 0x50  0xFFA0   1   no   ivVcan2tx       */
  &Cpu_Interrupt,                       /* 0x51  0xFFA2   1   no   ivVcan2rx       */
  &Cpu_Interrupt,                       /* 0x52  0xFFA4   1   no   ivVcan2err      */
  &Cpu_Interrupt,                       /* 0x53  0xFFA6   1   no   ivVcan2wkup     */
  &Cpu_Interrupt,                       /* 0x54  0xFFA8   1   no   ivVcan1tx       */
  &Cpu_Interrupt,                       /* 0x55  0xFFAA   1   no   ivVcan1rx       */
  &Cpu_Interrupt,                       /* 0x56  0xFFAC   1   no   ivVcan1err      */
  &Cpu_Interrupt,                       /* 0x57  0xFFAE   1   no   ivVcan1wkup     */
  &Cpu_Interrupt,                       /* 0x58  0xFFB0   1   no   ivVcan0tx       */
  &Cpu_Interrupt,                       /* 0x59  0xFFB2   1   no   ivVcan0rx       */
  &Cpu_Interrupt,                       /* 0x5A  0xFFB4   1   no   ivVcan0err      */
  &Cpu_Interrupt,                       /* 0x5B  0xFFB6   1   no   ivVcan0wkup     */
  &Cpu_Interrupt,                       /* 0x5C  0xFFB8   1   no   ivVflash        */
  &Cpu_Interrupt,                       /* 0x5D  0xFFBA   1   no   ivVflashfd      */
  &Cpu_Interrupt,                       /* 0x5E  0xFFBC   1   no   ivVspi2         */
  &Cpu_Interrupt,                       /* 0x5F  0xFFBE   1   no   ivVspi1         */
  &Cpu_Interrupt,                       /* 0x60  0xFFC0   1   no   ivViic0         */
  &Cpu_Interrupt,                       /* 0x61  0xFFC2   1   no   ivVsci6         */
  &Cpu_Interrupt,                       /* 0x62  0xFFC4   1   no   ivVcrgscm       */
  &Cpu_Interrupt,                       /* 0x63  0xFFC6   1   no   ivVcrgplllck    */
  &Cpu_Interrupt,                       /* 0x64  0xFFC8   1   no   ivVectpabovf    */
  &Cpu_Interrupt,                       /* 0x65  0xFFCA   1   no   ivVectmdcu      */
  &Cpu_Interrupt,                       /* 0x66  0xFFCC   1   no   ivVporth        */
  &Cpu_Interrupt,                       /* 0x67  0xFFCE   1   no   ivVportj        */
  &Cpu_Interrupt,                       /* 0x68  0xFFD0   1   no   ivVatd1         */
  &Cpu_Interrupt,                       /* 0x69  0xFFD2   1   no   ivVatd0         */
  &Cpu_Interrupt,                       /* 0x6A  0xFFD4   1   no   ivVsci1         */
  &Cpu_Interrupt,                       /* 0x6B  0xFFD6   1   no   ivVsci0         */
  &Cpu_Interrupt,                       /* 0x6C  0xFFD8   1   no   ivVspi0         */
  &Cpu_Interrupt,                       /* 0x6D  0xFFDA   1   no   ivVectpaie      */
  &Cpu_Interrupt,                       /* 0x6E  0xFFDC   1   no   ivVectpaaovf    */
  &Cpu_Interrupt,                       /* 0x6F  0xFFDE   1   no   ivVectovf       */
  &Cpu_Interrupt,                       /* 0x70  0xFFE0   1   no   ivVectch7       */
  &Cpu_Interrupt,                       /* 0x71  0xFFE2   1   no   ivVectch6       */
  &Cpu_Interrupt,                       /* 0x72  0xFFE4   1   no   ivVectch5       */
  &Cpu_Interrupt,                       /* 0x73  0xFFE6   1   no   ivVectch4       */
  &Cpu_Interrupt,                       /* 0x74  0xFFE8   1   no   ivVectch3       */
  &Cpu_Interrupt,                       /* 0x75  0xFFEA   1   no   ivVectch2       */
  &Cpu_Interrupt,                       /* 0x76  0xFFEC   1   no   ivVectch1       */
  &Cpu_Interrupt,                       /* 0x77  0xFFEE   1   no   ivVectch0       */
  &vPortTickInterrupt,                       /* 0x78  0xFFF0   1   no   ivVrti          */
  &Cpu_Interrupt,                       /* 0x79  0xFFF2   1   no   ivVirq          */
  &Cpu_Interrupt,                       /* 0x7A  0xFFF4   -   -    ivVxirq         */
  &Cpu_Interrupt,                       /* 0x7B  0xFFF6   -   -    ivVswi          */
  &Cpu_Interrupt                        /* 0x7C  0xFFF8   -   -    ivVtrap         */
};

/* end vector.c */
