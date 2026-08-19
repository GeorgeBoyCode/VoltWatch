/**
 *****************************************************************************
   @file     DioLib.h
   @brief    Set of Digital IO peripheral functions.
   
   @internal   001 @endinternal
   @version  V1.0
   @author   ADI
   @date     April 2015 
   @par Revision History:
   - V0.1, March 2013: initial version. 
   - V1.0, April 2015: Changed library format


All files provided by ADI, including this file, are
provided as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#ifdef __cplusplus
extern "C" {
#endif 

#include "DeviceHeader.h"

#define PIN0 0x0 
#define PIN1 0x1 
#define PIN2 0x2 
#define PIN3 0x3 
#define PIN4 0x4 
#define PIN5 0x5 
#define PIN6 0x6 
#define PIN7 0x7

// port configuration
extern int DioCfg(ADI_GPIO_TypeDef *pPort, int iMpx);
extern int DioCfgPin(ADI_GPIO_TypeDef *pPort, int iPin, int iMode);
extern int DioOen(ADI_GPIO_TypeDef *pPort, int iOen);
extern int DioOenPin(ADI_GPIO_TypeDef *pPort, int iPin, int iOen);
extern int DioPul(ADI_GPIO_TypeDef *pPort, int iPul);
extern int DioPulPin(ADI_GPIO_TypeDef *pPort, int iPin, int iPul);
extern int DioIen(ADI_GPIO_TypeDef *pPort, int iIen);
extern int DioIenPin(ADI_GPIO_TypeDef *pPort, int iPin, int iIen);
extern int DioRd(ADI_GPIO_TypeDef *pPort);
extern int DioWr(ADI_GPIO_TypeDef *pPort, int iVal);
extern int DioSet(ADI_GPIO_TypeDef *pPort, int iVal);
extern int DioClr(ADI_GPIO_TypeDef *pPort, int iVal);
extern int DioTgl(ADI_GPIO_TypeDef *pPort, int iVal);
extern int DioOde(ADI_GPIO_TypeDef *pPort, int iOde);
extern int DioOdePin(ADI_GPIO_TypeDef *pPort, int iPin, int iOde);
#ifdef __cplusplus
}
#endif 

