/**
 *****************************************************************************  
   @addtogroup dac 
   @{
   @file       DacLib.c
   @brief      Set of DAC peripheral functions.
   - First power up DAC with DacPwrDwn()
   - The configure DAC via DacCfg().
   - Output DAC value with DacWr().
   - Example:
      DacPwrDwn(pADI_VDAC3,0);
      DacCfg(pADI_VDAC3,0,INT_REF);
      for(i1 = 0; i1<0x10000000; i1 += 0x1000000)
         DacWr(pADI_VDAC3,i1);

   @internal   002 @endinternal
   @version    V1.0
	@author     ADI
	@date       November 2015
   @par Revision History:
   - V0.1, May 2013: initial version.
   - V0.2, January 2013: changed DacCfg(), removed DacBufCfg()
   - V1.0, November 2015: Changed library format

All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#include	"DacLib.h"

/**
	@brief int DacWr(int iChan, int iData)
			==========Writes the DAC value.
	@param pPort :{pADI_VDAC0,pADI_VDAC1,pADI_VDAC2,pADI_VDAC3,pADI_VDAC4,pADI_VDAC5,pADI_VDAC6,pADI_VDAC7}
      - pADI_VDAC0 for VDAC0.
      - pADI_VDAC1 for VDAC1.
      - pADI_VDAC2 for VDAC2.
      - pADI_VDAC3 for VDAC3.
      - pADI_VDAC4 for VDAC4.
      - pADI_VDAC5 for VDAC5.
      - pADI_VDAC6 for VDAC6.
      - pADI_VDAC7 for VDAC7.
	@param iData :{}	\n
		- DACxDAT
		- Data to output to DAC.
	@return DAC data.
**/
int DacWr(ADI_VDAC_TypeDef *pPort, int iData)
{
   pPort->DACDAT = iData;
   return  pPort->DACDAT;
}

/**
	@brief int DacCfg(int iChan, int iMode, int iRng)
			==========Sets the output range of a DAC.
	@param pPort :{pADI_VDAC0,pADI_VDAC1,pADI_VDAC2,pADI_VDAC3,pADI_VDAC4,pADI_VDAC5,pADI_VDAC6,pADI_VDAC7}
      - pADI_VDAC0 for VDAC0.
      - pADI_VDAC1 for VDAC1.
      - pADI_VDAC2 for VDAC2.
      - pADI_VDAC3 for VDAC3.
      - pADI_VDAC4 for VDAC4.
      - pADI_VDAC5 for VDAC5.
      - pADI_VDAC6 for VDAC6.
      - pADI_VDAC7 for VDAC7.
	@param iMode :{0}
		- DACCON.2,3
		- 0 for 12 bit mode.
	@param iRng :{INT_REF, AVDD_REF}
		- DACCON.0,1
		- 0 or INT_REF to use internal as VDAC reference.
		- 3 or AVDD_REF	to use AVDD as VDAC reference.
	@return new DACCON.
**/
	
int DacCfg(ADI_VDAC_TypeDef *pPort, int iMode, int iRng)
{
   pPort->DACCON = (iMode+iRng+0x10);
	return  pPort->DACCON; 
}

 /**
	@brief int DacPwrDwn(int iChan, int iIcfg)
			==========Powers up or down selected VDAC
        Need to write to call DacCfg() after this function
	@param pPort :{pADI_VDAC0,pADI_VDAC1,pADI_VDAC2,pADI_VDAC3,pADI_VDAC4,pADI_VDAC5,pADI_VDAC6,pADI_VDAC7}
      - pADI_VDAC0 for VDAC0.
      - pADI_VDAC1 for VDAC1.
      - pADI_VDAC2 for VDAC2.
      - pADI_VDAC3 for VDAC3.
      - pADI_VDAC4 for VDAC4.
      - pADI_VDAC5 for VDAC5.
      - pADI_VDAC6 for VDAC6.
      - pADI_VDAC7 for VDAC7.
	@param iIcfg :{0,DACCON_PD}	\n
		- 0x100 or DACCON_PD to power down VDAC channel
		- 0 to Power up VDAC channel
	@return new DACCON.
**/  
   
int DacPwrDwn(ADI_VDAC_TypeDef *pPort, int iIcfg)
{
   pPort->DACCON = iIcfg;
	return  pPort->DACCON; 
}

/**@}*/
