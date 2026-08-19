/**
 *****************************************************************************
   @addtogroup dio 
   @{
   @file     DioLib.c
   @brief    Set of Digital IO peripheral functions.
   
   @internal   001 @endinternal
   @version  V1.0
   @author   ADI
   @date     April 2015 
   @par Revision History:
   - V0.1, March 2013: initial version. 
   - V0.2, November 2013: DioSet() and DioClr() modified for S2 silicon.
   - V0.3, January 2014: Fixed DioIenPin().
   - V1.0, April 2015: Changed library format


All files provided by ADI, including this file, are
provided as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#include "DioLib.h"

/**
   @brief int DioCfg(ADI_GPIO_TypeDef *pPort, int iMpx)
         ========== Sets Digital IO port multiplexer.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iMpx :{0-0xFFFF}
      - Set iMpx accoring to the multiplex options required.
   @return 1.
**/

int DioCfg(ADI_GPIO_TypeDef *pPort, int iMpx)
{  
   pPort->GPCON = iMpx;
   return 1;
}

/**
   @brief int DioCfgPin(ADI_GPIO_TypeDef *pPort, int iPin, int iMode)
         ========== Configures the mode of 1 GPIO of the specified port.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iPin :{PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7}
      - PIN0 to configure Px.0.		
      - PIN1 to configure Px.1.
      - PIN2 to configure Px.2.
      - PIN3 to configure Px.3.   
      - PIN4 to configure Px.4.    
      - PIN5 to configure Px.5. 
      - PIN6 to configure Px.6.
      - PIN7 to configure Px.7.
   @param iMode :{0, 1, 2, 3}
      - Set the mode accoring to the multiplex options required.
   @return 1.
**/

int DioCfgPin(ADI_GPIO_TypeDef *pPort, int iPin, int iMode)
{  
   unsigned short a = pPort->GPCON;
   a &= (0xFFFF - (0x3 << (2 * iPin)));   // keep all configurations except iPin
   a += (iMode << (2 * iPin));            // configure iPin
   pPort->GPCON = a;
   return 1;
} 

/**
   @brief int DioOen(ADI_GPIO_TypeDef *pPort, int iOen)
         ========== Enables the output drive of port pins.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iOen :{0-0xFF}
      - Select combination of BIT0 to BIT7 outputs to connect to pin e.g.
      - 0, none of the pins are configured as outputs.
      - BITX|BITY, only Pin X and Pin Y are configured as outputs on the specified port.
   @return 1.
**/

int DioOen(ADI_GPIO_TypeDef *pPort, int iOen)
{
   pPort->GPOE = iOen;
   return 1;
}

/**
   @brief DioOenPin(ADI_GPIO_TypeDef *pPort, int iPin, int iOen)
         ========== Enables the output drive of 1 GPIO of the specified port.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iPin :{PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7}
      - PIN0 to configure Px.0.		
      - PIN1 to configure Px.1.
      - PIN2 to configure Px.2.
      - PIN3 to configure Px.3.   
      - PIN4 to configure Px.4.    
      - PIN5 to configure Px.5. 
      - PIN6 to configure Px.6.
      - PIN7 to configure Px.7.
   @param iOen :{0, 1}
      - 0 to disable the output drive
      - 1 to enable the output drive
   @return 1.
**/

int DioOenPin(ADI_GPIO_TypeDef *pPort, int iPin, int iOen)
{
   unsigned short a = pPort->GPOE;
   a &= (0xFF - (0x1 << iPin));     // keep all configurations except iPin
   a += (iOen << iPin);             // configure iPin
   pPort->GPOE = a;
   return 1;		
}

/**
   @brief int DioPul(ADI_GPIO_TypeDef *pPort, int iPul)
         ========== Sets the pull-up/ pull-down resistor of port pins.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iPul :{0-0xFF}
      - Select combination of BIT0 to BIT7 to enable the pull ups of pins e.g.
      - 0, all pull-ups/ pull-downs are disabled.
      - BITX|BITY, all pull ups are disabled except on Pin X and Pin Y of the specified port.
   @note GP0, GP1, GP2 and GP3 have pull-ups, GP4 and GP5 have pull-downs 
   @return 1.
**/

int DioPul(ADI_GPIO_TypeDef *pPort, int iPul)
{
   pPort->GPPUL = iPul;
   return 1;
}

/**
   @brief DioPulPin(ADI_GPIO_TypeDef *pPort, int iPin, int iPul)
         ========== Configures the pull-up/ pull-down of 1 GPIO of the specified port.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iPin :{PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7}
      - PIN0 to configure Px.0.		
      - PIN1 to configure Px.1.
      - PIN2 to configure Px.2.
      - PIN3 to configure Px.3.   
      - PIN4 to configure Px.4.    
      - PIN5 to configure Px.5. 
      - PIN6 to configure Px.6.
      - PIN7 to configure Px.7.
   @param iPul :{0, 1}
      - 0 to disable the pull-up/ pull-down
      - 1 to enable the pull-up/ pull-down
   @return 1.
**/

int DioPulPin(ADI_GPIO_TypeDef *pPort, int iPin, int iPul)
{
  unsigned short a = pPort->GPPUL;
  a &= (0xFF - (0x1 << iPin));      // keep all configurations except iPin
  a += (iPul << iPin);              // configure iPin
  pPort->GPPUL = a;
  return 1;		
}

/**
   @brief int DioIen(ADI_GPIO_TypeDef *pPort, int iIen)
         ========== Enables the input path of port pins.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iIen :{0-0xFF}
      - Select combination of BIT0 to BIT7 inputs to connect to pin e.g.
      - 0, none of the pins are configured as inputs.
      - BITX|BITY, only Pin X and Pin Y are configured as inputs on the specified port.
   @return 1.
**/

int DioIen(ADI_GPIO_TypeDef *pPort, int iIen)
{
   pPort->GPIE = iIen;
   return 1;
}

/**
   @brief DioIenPin(ADI_GPIO_TypeDef *pPort, int iPin, int iIen)
         ========== Enables the input path of 1 GPIO of the specified port.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iPin :{PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7}
      - PIN0 to configure Px.0.		
      - PIN1 to configure Px.1.
      - PIN2 to configure Px.2.
      - PIN3 to configure Px.3.   
      - PIN4 to configure Px.4.    
      - PIN5 to configure Px.5. 
      - PIN6 to configure Px.6.
      - PIN7 to configure Px.7.
   @param iOen :{0, 1}
      - 0 to disable the input path
      - 1 to enable the input path
   @return 1.
**/

int DioIenPin(ADI_GPIO_TypeDef *pPort, int iPin, int iIen)
{
   unsigned short a = pPort->GPIE;
   a &= (0xFF - (0x1 << iPin));     // keep all configurations except iPin
   a += (iIen << iPin);             // configure iPin
   pPort->GPIE = a;
   return 1;		
}

/**
   @brief int DioRd(ADI_GPIO_TypeDef *pPort)
         ========== Reads values of port pins.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @return value on port pins.
**/

int DioRd(ADI_GPIO_TypeDef *pPort)
{
   return (pPort->GPIN);
}

/**
   @brief int DioWr(ADI_GPIO_TypeDef *pPort, int iVal)
         ========== Writes values to outputs.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iVal :{0-0xFF}
      - Select combination of BIT0 to BIT7 outputs to be high.
      - unselected outputs will be low.
   @return value on port pins.
**/

int DioWr(ADI_GPIO_TypeDef *pPort, int iVal)
{     
   pPort->GPOUT = iVal;
   return (pPort->GPOUT);
}

/**
   @brief int DioSet(ADI_GPIO_TypeDef *pPort, int iVal)
         ========== Sets individual outputs.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iVal :{0-0xFF}
      - Select combination of BIT0 to BIT7 outputs to be high.
      - unselected outputs will be unchanged.
   @return value on port pins.
**/
int DioSet(ADI_GPIO_TypeDef *pPort, int iVal)
{
   if(pPort == pADI_GP1 && pADI_ID->CHIPID == 0x560)  //GPIO fix only needed for first silicon CHIPID == 0x560
      pADI_GPIO_FIX->GP1SET = iVal;
   else
      pPort->GPSET = iVal;
   return (pPort->GPOUT);
}

/**
   @brief int DioClr(ADI_GPIO_TypeDef *pPort, int iVal)
         ========== Clears individual outputs.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iVal :{0-0xFF}
      - Select combination of BIT0 to BIT7 outputs to be cleared.
      - unselected outputs will be unchanged.
   @return value on port pins.
**/

int DioClr(ADI_GPIO_TypeDef *pPort, int iVal)
{
   if(pPort == pADI_GP2 && pADI_ID->CHIPID == 0x560)  //GPIO fix only needed for first silicon CHIPID == 0x560
      pADI_GPIO_FIX->GP2CLR = iVal;
   else
      pPort->GPCLR = iVal;
   return (pPort->GPOUT);
}

/**
   @brief int DioTgl(ADI_GPIO_TypeDef *pPort, int iVal)
         ========== Toggles individual outputs.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iVal :{0-0xFF}
      - Select combination of BIT0 to BIT7 outputs to be toggled.
      - unselected outputs will be unchanged.
   @return value on port pins.
**/
int DioTgl(ADI_GPIO_TypeDef *pPort, int iVal)
{
   pPort->GPTGL = iVal;
   return (pPort->GPOUT);
}

/**
   @brief int DioOde(ADI_GPIO_TypeDef *pPort, int iOde)
         ========== Sets open drain of port pins.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iOde :{0-0xFF}
      - Select combination of BIT0 to BIT7 outputs to be open drain.
   @return 1.
**/

int DioOde(ADI_GPIO_TypeDef *pPort, int iOde)
{
   pPort->GPODE = iOde;
   return 1;
}

/**
   @brief DioOdePin(ADI_GPIO_TypeDef *pPort, int iPin, int iOde)
         ========== Configures the open drain of 1 GPIO of the specified port.
   @param pPort :{pADI_GP0,pADI_GP1,pADI_GP2,pADI_GP3,pADI_GP4,pADI_GP5}
      - pADI_GP0 for GP0.
      - pADI_GP1 for GP1.
      - pADI_GP2 for GP2.
      - pADI_GP3 for GP3.
      - pADI_GP4 for GP4.
      - pADI_GP5 for GP5.
   @param iPin :{PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7}
      - PIN0 to configure Px.0.		
      - PIN1 to configure Px.1.
      - PIN2 to configure Px.2.
      - PIN3 to configure Px.3.   
      - PIN4 to configure Px.4.    
      - PIN5 to configure Px.5. 
      - PIN6 to configure Px.6.
      - PIN7 to configure Px.7.
   @param iOde :{0, 1}
      - 0 to disable open drain
      - 1 to enable open drain
   @return 1.
**/

int DioOdePin(ADI_GPIO_TypeDef *pPort, int iPin, int iOde)
{
   unsigned short a = pPort->GPODE;
   a &= (0xFF - (0x1 << iPin));     // keep all configurations except iPin
   a += (iOde << iPin);             // configure iPin
   pPort->GPODE = a;
   return 1;		
}


/**@}*/
