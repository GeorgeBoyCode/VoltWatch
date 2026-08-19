/**
 *****************************************************************************
   @addtogroup wdt 
   @{
   @file     WdtLib.c
   @brief    Set of watchdog Timer peripheral functions.
   
   @internal   001 @endinternal
   @version  V1.0
   @author   ADI
   @date     April 2015 
   @par Revision History:
   - V0.1, March 2013: initial version. 
   - V1.0, April 2015: Changed library format


All files  provided by ADI, including this file, are
provided as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#include "WdtLib.h"


/**
   @brief int WdtLd(int iTld);
         ========== Sets timer reload value.
   @param iTld :{0-0xFFFF}
      - Sets reload value T3LD to iTld. 
   @return 1.
**/

int WdtLd(int iTld)
{      
   pADI_WDT->T3LD= iTld;
   return 1;
}

/**
   @brief int WdtVal(void);
         ========== Reads timer value.
   @return Timer value T3VAL.
**/

int WdtVal(void)
{
   return pADI_WDT->T3VAL;
}

/**
   @brief int WdtCfg(int iMod, int iPre, int iInt, int iPd);
         ========== Configures the watchdog timer.
   @param iMod :{T3CON_MOD_FREERUN, T3CON_MOD_PERIODIC}
      - T3CON_MOD_FREERUN, the timer operates in free running mode.
      - T3CON_MOD_PERIODIC, the timer operates in periodic mode.
   @param iPre :{T3CON_PRE_DIV1,T3CON_PRE_DIV16,T3CON_PRE_DIV256,T3CON_PRE_DIV4096}
      - T3CON_PRE_DIV1, for a prescaler of 1.
      - T3CON_PRE_DIV16, for a prescaler of 16.
      - T3CON_PRE_DIV256, for a prescaler of 256.
      - T3CON_PRE_DIV4096, for a prescaler of 4096.
   @param iInt :{T3CON_IRQ_DIS,T3CON_IRQ_EN}
      - T3CON_IRQ_DIS, to generate a reset on a timer timeout.
      - T3CON_IRQ_EN, to generate an interrupt on a timer timeout.
   @param iPd :{T3CON_PMD_DIS,T3CON_PMD_EN}
      - T3CON_PMD_DIS, the timer continues to count when in hibernate mode.
      - T3CON_PMD_EN, the timer stops counting when in hibernate mode.
   @return 1.
**/

int WdtCfg(int iMod, int iPre, int iInt, int iPd)
{
   int	i1;
   i1 = pADI_WDT->T3CON & 0x20;  // keep bit 5 
   i1 |= iMod;
   i1 |= iPre;
   i1 |= iInt;
   i1 |= iPd;
   pADI_WDT->T3CON = i1;
   return 1;	
}

/**
   @brief int WdtGo(int iEnable);
         ========== Enable or reset the watchdog timer.
   @param iEnable :{T3CON_ENABLE_DIS,T3CON_ENABLE_EN}
      - T3CON_ENABLE_DIS, to reset the timer.
      - T3CON_ENABLE_EN, to enable the timer.
   @return 1.
**/

int WdtGo(int iEnable)
{
  if (iEnable == T3CON_ENABLE_DIS)
    T3CON_ENABLE_BBA = 0;   
  else
    T3CON_ENABLE_BBA = 1;
   return 1;
}

/**
   @brief int WdtClrInt(void);
         ========== Clear timer interrupts.
   @return 1 if the interrupt was cleared successfully, 0 otherwise.
**/

int WdtClrInt(void)
{
   if(T3STA_CLRI_BBA ==0){
      pADI_WDT->T3CLRI = 0xCCCC;
      return 1;
   }
   else{
      return 0;
   }
}


/**
   @brief int WdtSta(void);
         ========== Returns timer Status.
   @return value of T3STA:
      - T3STA_CLRI, T3CLRI write sync in progress.
      - T3STA_LD, T3LD write sync in progress.
      - T3STA_CON, T3CON write sync in progress.
      - T3STA_LOCK, Set automatically when user code sets T3CON_ENABLE.
**/

int WdtSta(void)
{
   return pADI_WDT->T3STA;
}

/**@}*/
