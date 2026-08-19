/**
 *****************************************************************************
   @example  ADC_Demo.c
   @brief    ADC Demo file
      Decription: Demo for ADC.
      - Sets up ADC for continuous sampling of AIN4 input channel in Single ended mode
      - Result converted to Voltage value and string sent to UART.
      - UART configured for 9600-8-N-1
      - 8x VDACs setup as voltage sources also
      
  
   @version  V0.4
   @author   ADI
   @date     December 2015
   @par Revision History:
   - V0.1, June 2013: initial version.
   - V0.2, December 2013: Added code for S2 silicon
   - V0.3, January 2014: adjusted bit weight calculation
	 - V0.4, November 2015: Changed ADuCM3xx.h to DeviceHeader.h

All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#include <stdio.h>
#include <string.h>
#include <DeviceHeader.h>
#include <DacLib.h>
#include <IntLib.h>
#include <WdtLib.h>
#include <UrtLib.h>
#include <DioLib.h>
#include <AdcLib.h>
// Function Definitions
void delay(long int);
void ResultsToUart(unsigned long ulVal, unsigned char ucChan);
void UartSetup(void);
void ADCSetUp(void);
void VDACSetup(void);

// Global Variable definitions
volatile unsigned char ucSendToUart = 0; 
volatile unsigned char ucTxBufferEmpty = 0;	  // Indicates UART Tx buffer empty
volatile unsigned int uiTest = 0;
unsigned char szTemp[64] = "";		           // Used to store ADC1 result before printing to UART
volatile unsigned char ucCOMSTA0 = 0;          // Variable used to store COMSTA0, UART status register
volatile unsigned char ucCOMIID0 = 0;          // Variable used to store COMIID0, UART Interrupt status register	 
volatile unsigned char ucComRx = 0;            // Variable used to read UART Rx buffer contents into 
volatile long ultest,ADCTEST1,ADCTEST2 = 0;

// Following are a list of variables used to read the ADC
volatile long ulAIN0Result = 0;
volatile unsigned int ucClipLErr = 0;          // Read ADCxDAT.1 status bit
volatile unsigned int ucClipHErr = 0;          // Read ADCxDAT.0 status bit
float  fVoltage = 0.0;   			              // ADC value converted to voltage
float fVolts = 0.0;

int main (void)
{
   int i,j,k;
   unsigned char nLen = 0; 
  
   WdtCfg(0,T3CON_PRE_DIV1,T3CON_IRQ_EN,0);    // Disable the Watchdog timer resets
   
   if (pADI_ID->CHIPID == 0x561)                      // check for S2 silicon
   {
      pADI_RESET->RSTKEY =  0x2009;                   //By Default Software and Watchdog resets don't reset the LV die and GPIOs
      pADI_RESET->RSTKEY =  0x0426;                   //During debug it's useful that Software tools have the ability to reset them
      pADI_RESET->RSTCFG = RSTCFG_GPIO_PLA_RETAIN_DIS;//So disable retain function during debug.
   }
   if (pADI_LV->LVID == 0x73)                         // check for S2 silicon
   {
      pADI_LV_RST->LVRST = LVRST_RETAIN_DIS;
   }

   DioOenPin(pADI_GP2,PIN4,1);                 // Configure P2.4 as an output - to toggle LED with Timer 2
   //delay before program starts
   for (i = 0; i<100; i++)
   {
      DioTgl(pADI_GP2, BIT4);       // Toggle LED, P2.4
      for (j = 0; j<100000; j++) k = pADI_GP2->GPIN;
   }

   DioSet(pADI_GP2, BIT4);
   pADI_CLKCTL->CLKCON5 = 0x00;                // Enable clock to all peripherals
   pADI_CLKCTL->CLKCON1 = 0x200;               // PCLK 20MHz, HCLK 80MHz
   UartSetup();
   VDACSetup();
   
   pADI_LV_INT->INTSEL = 0xFF;                 // Enable all LV1 interrupt sources
   NVIC_EnableIRQ(LVD1_IRQn);			           // Enable LV1 IRQ
   sprintf ( (char*)szTemp, "ADuCM320i ADC Demo \r\n" ); // Scan string 
   nLen = strlen((char*)szTemp);               // Call function to calcualte the length of scanned string
   if (nLen <64)
   {
      for ( i = 0 ; i < nLen ; i++ )	        // loop to send String to UART
       {
          ucTxBufferEmpty = 0;	              // Clear flag
          UrtTx(pADI_UART,szTemp[i]);          // Load UART Tx register.
          while (ucTxBufferEmpty == 0)         // Wait for UART Tx interrupt
          {
          }
       }
     }
   ADCSetUp(); 
   AdcGo(ADCCON_C_TYPE_CONT);
   while (1)
    {
      if (ucSendToUart == 1)
       {
         ResultsToUart(ADCTEST1, 4);
       }
   }
}

// This function converts ADC reading to a voltage and sends it to the UART
void ResultsToUart(unsigned long ulVal, unsigned char ucChan)
{
   unsigned char i = 0;
   unsigned char nLen = 0; 

   if (pADI_LV->LVID == 0x71)                     // check for S1 silicon
   {
      fVolts   = (2.5 / 65535);                   // Internal reference, calculate lsb size in volts
      fVoltage = ((ulVal>>12) * fVolts);          // Calculate ADC result in volts
      fVoltage = (fVoltage *2.51)/2.5;
   }
   else if (pADI_LV->LVID == 0x73)                // check for S2 silicon
   {
      fVolts   = (2.51 / 65535);                 // Internal reference, calculate lsb size in volts
      fVoltage = ((ulVal>>12) * fVolts);          // Calculate ADC result in volts
   }
   else
   {
      fVolts   = (2.5 / 65535);                   // Internal reference, calculate lsb size in volts
      fVoltage = ((ulVal>>12) * fVolts);          // Calculate ADC result in volts
   }

   sprintf ( (char*)szTemp, "%fV,%x \r\n",fVoltage,ucChan );// Scan string with the ADC1 Result  
   nLen = strlen((char*)szTemp);               // Call function to calcualte the length of scanned string
   if (nLen <64)
   {
      for ( i = 0 ; i < nLen ; i++ )	        // loop to send ADC result	to UART
       {
          ucTxBufferEmpty = 0;	              // Clear flag
          UrtTx(pADI_UART,szTemp[i]);          // Load UART Tx register.
          while (ucTxBufferEmpty == 0)         // Wait for UART Tx interrupt
          {
          }
       }
       AdcGo(ADCCON_C_TYPE_CONT);
   }
	
}
// This function initialises all 8x VDACs and sets their output
void VDACSetup(void)
{
   DacPwrDwn(pADI_VDAC0,0);                        // power up VDAC0
   DacPwrDwn(pADI_VDAC1,0);                        // power up VDAC1  
   DacPwrDwn(pADI_VDAC2,0);                        // power up VDAC2
   DacPwrDwn(pADI_VDAC3,0);                        // power up VDAC3   
   DacPwrDwn(pADI_VDAC4,0);                        // power up VDAC4
   DacPwrDwn(pADI_VDAC5,0);                        // power up VDAC5  
   DacPwrDwn(pADI_VDAC6,0);                        // power up VDAC6
   DacPwrDwn(pADI_VDAC7,0);                        // power up VDAC7

   DacCfg(pADI_VDAC0,DACCON_MODE_12BIT,INT_REF);   // Turn on VDAC0, and use internal reference
   DacCfg(pADI_VDAC1,DACCON_MODE_12BIT,INT_REF);   // Turn on VDAC1, and use internal reference
   DacCfg(pADI_VDAC2,DACCON_MODE_12BIT,INT_REF);   // Turn on VDAC2, and use internal reference
   DacCfg(pADI_VDAC3,DACCON_MODE_12BIT,INT_REF);   // Turn on VDAC3, and use internal reference
   DacCfg(pADI_VDAC4,DACCON_MODE_12BIT,INT_REF);   // Turn on VDAC4, and use internal reference
   DacCfg(pADI_VDAC5,DACCON_MODE_12BIT,INT_REF);   // Turn on VDAC5, and use internal reference
   DacCfg(pADI_VDAC6,DACCON_MODE_12BIT,INT_REF);   // Turn on VDAC6, and use internal reference
   DacCfg(pADI_VDAC7,DACCON_MODE_12BIT,INT_REF);   // Turn on VDAC7, and use internal reference
      
 
   DacWr(pADI_VDAC0,0x08000000);                   // Set VDAC0 to mid-scale 
   DacWr(pADI_VDAC1,0x04000000);                   // Set VDAC1 to quarter-scale
   DacWr(pADI_VDAC2,0x0C000000);                   // Set VDAC2 to 3/4-scale
   DacWr(pADI_VDAC3,0x08000000);                   // Set VDAC3 to mid-scale
   DacWr(pADI_VDAC4,0x08000000);                   // Set VDAC4 to mid-scale 
   DacWr(pADI_VDAC5,0x04000000);                   // Set VDAC5 to quarter-scale
   DacWr(pADI_VDAC6,0x08000000);                   // Set VDAC6 to mid-scale 
   DacWr(pADI_VDAC7,0x04000000);                   // Set VDAC7 to quarter-scale
}                       

void ADCSetUp(void)
{
   AdcBuf(IBUFCON_IBUF_PD_BOTH,
   IBUFCON_IBUF_BYP_BOTH,ADCCON_REFB_PUP);         // Bypass and power down internal buffer
   if (pADI_LV->LVID == 0x71)                     // check for S1 silicon
   {
      AdcSpeed(160);                                   // Value for 100KSPS
   }
   else if (pADI_LV->LVID == 0x73)                // check for S2 silicon
   {
      AdcSpeed(200);                                   // Value for 100KSPS
   }
    
   AdcGo(ADCCON_C_TYPE_NO);                        // Power up ADC
   // For Single ended mode
   AdcPin(VREFN_NADC,AIN4);                        // +ve = AIN4, -ve=VREFN
   // Differential measurement
//    AdcPin(AIN5,AIN4);                           // +ve = AIN4, -ve=VREFN
}


// Function used to setup the UART block
void UartSetup(void)
{
   DioCfg(pADI_GP1,0x5);                              // Configure P1[1:0] as UART pins
   UrtCfg(pADI_UART,B9600,COMLCR_WLS_EIGHTBITS,0);  // Configure UART for 9600 baud rate
   //UrtCfg(pADI_UART,B115200,COMLCR_WLS_EIGHTBITS,0);  // Configure UART for 115200 baud rate
   UrtIntCfg(pADI_UART,COMIEN_ERBFI|
      COMIEN_ETBEI|COMIEN_ELSI);                      // Enable Rx, Tx and Rx buffer full Interrupts
   NVIC_EnableIRQ(UART_IRQn);                         // Enable UART interrupt source in NVIC
}

// Simple Delay routine
void delay (long int length)
{
   while (length >0)
      length--;
}

void LV0_Int_Handler()
{
   pADI_LV_INT->INTCLR = 0x1;                   // clear Irq source
   pADI_GP2->GPTGL = 0x2;                       // Toggle P2.1
}

void LV1_Int_Handler()
{
   unsigned char ucLVIrqStatus = 0;
   
   ucLVIrqStatus = pADI_LV_INT->INTSTA;
   if ((ucLVIrqStatus & 0x1) == 0x1)           // ADC software conversion IRQ
   {
      pADI_LV_INT->INTCLR = 0x1;               // clear Irq source
      ADCTEST1 = pADI_ADC->ADCDAT[4];          // Read ADC4DAT register
      pADI_GP2->GPTGL = 0x10;                  // Toggle P2.4
      uiTest++;
      if (uiTest == 256)
      {
         ucSendToUart = 1;
         uiTest = 0;
         pADI_ADC->ADCCON = 0x280;
      }
   }
   if ((ucLVIrqStatus & 0x2) == 0x2)               // ADC Sequencer IRQ
   {
      uiTest++;
      pADI_LV_INT->INTCLR = INTCLR_CLR_ADC_SEQ;    // clear Irq source
   }
   if ((ucLVIrqStatus & 0x4) == 0x4)               // ADC Digital Comparator IRQ
   {
      uiTest++;
      pADI_LV_INT->INTCLR = INTCLR_CLR_DCOMP;      // clear Irq source
   }
   if ((ucLVIrqStatus & 0x8) == 0x8)               // ADC Analog Comparator IRQ
   {
      uiTest++;
      pADI_LV_INT->INTCLR = INTCLR_CLR_ACOMP;      // clear Irq source
   }
	 if ((ucLVIrqStatus & 0x40) == 0x40)             // D2D read ECC error IRQ
   {
      uiTest++;
      pADI_LV_INT->INTCLR = INTCLR_CLR_RDECC_ERR;  // clear Irq source
   }
   if ((ucLVIrqStatus & 0x80) == 0x80)             // D2D Write ECC error IRQ
   {
      uiTest++;
      pADI_LV_INT->INTCLR = INTCLR_CLR_WRECC_ERR;  // clear Irq source
   }
}


void UART_Int_Handler()
{  	
   ucCOMSTA0 = UrtLinSta(pADI_UART);
   ucCOMIID0 = UrtIntSta(pADI_UART);
   if ((ucCOMIID0 & 0x2) == 0x2)	              // Transmit buffer empty
   {
	  ucTxBufferEmpty = 1;
   }	
   if ((ucCOMIID0 & 0x4) == 0x4)	              // Receive byte
   {
	  ucComRx	= UrtRx(pADI_UART);
   }
}
