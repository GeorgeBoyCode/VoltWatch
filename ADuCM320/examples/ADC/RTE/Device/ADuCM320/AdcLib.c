/**
 *****************************************************************************
   @addtogroup adc 
   @{
   @file       AdcLib.c
   @brief      Set of ADC peripheral functions.
   
   @internal   002 @endinternal
   @version    V1.0
   @author     ADI
   @date       November 2015
   @par Revision History:
      - V0.1, June 2013: initial version.
      - V0.2, June 2013: Fixed Dogygen comments for AdcRd() and AdcPin().
      - V0.3, August 2013: Fixed AdcSeqCfg() delay, added IDAC channels.
      - V0.4, December 2013: Updated AdcSpeed() for S2 silicon.
      - V0.5, January 2014: Fixed Dogygen comments for AdcPin() and AdcRd().
      - V0.6, February 2014: Fixed AdcRd(), Changed tabbing.
      - V0.7, November 2014: Added AdcDma
      - V1.0, November 2015: Changed Library format


All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.  It is the 
responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/


#include   "AdcLib.h"

/**
   @brief int AdcGo(int iStart)
       ==========Start ADC conversion.
   @param iStart :{ADCCON_C_TYPE_NO,ADCCON_C_TYPE_DIO,ADCCON_C_TYPE_SINGLE,
            ADCCON_C_TYPE_CONT,ADCCON_C_TYPE_PLA}         \n
      - ADCCON.0-2,
      - 0 or ADCCON_C_TYPE_NO for Idle mode.
      - 1 or ADCCON_C_TYPE_DIO for P2.4 to trigger ADC conversion.
      - 2 or ADCCON_C_TYPE_SINGLE for Single conversion.
      - 3 or ADCCON_C_TYPE_CONT for continuous conversions.
      - 4 or ADCCON_C_TYPE_PLA for PLA triggered conversions.
   @return 1.
**/

int AdcGo(int iStart)
   {
   int   i1 = 0;
   
   i1 = (pADI_ADC->ADCCON & 0xFFFC);           //Read ADCCON register.
   i1 |= ADCCON_PUP + ADCCON_REFB_PUP;         //Ensure ADC is Powered up.       
   pADI_ADC->ADCCON = i1 + iStart;
   return 1;
   }
/**
   @brief int AdcRd(int iChan)
         ==========Reads the ADC status.
   @param iChan :{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,
            AIN10,AIN11,AIN12,AIN13,AIN14,AIN15,AIN_IDAC3,AIN_IDAC1,
            AIN_IDAC0,AIN_IDAC2,TEMP_SENSOR,VREFP_PADC,PVDD_IDAC2,
            IOVDD_2,AVDD_2,VREFN_PADC}         \n
      Set to select ADC channel number.
   @return ADC data (ADCDATn).  MSb of data is bit 27.  Bits 28 to 31
            give extended sign.
      Value of 0x0ffffxxx => VRef.
      Value of 0x00000000 => 0V.
      Value of 0xF0000000 => -Vref.
      Bit2 contains "old flag".
      Bit3 contains valid flag.
   @warning   Returns ADCDATn even if it does not contain new data.
      Multiple reads reduce chance of invalid return but this is still 
      possible if this function is interrupted twice with eactly the wrong 
      timing.  See User Guide.  User should check for this possibility.
**/

int AdcRd(int iChan)
   {   
   int i1;
   
   if((i1 = pADI_ADC->ADCDAT[iChan])==0)
      {
      if((i1 = pADI_ADC->ADCDAT[iChan])==0)
         {
         i1 = pADI_ADC->ADCDAT[iChan]; //Read twice for extra 100ns delay.
         i1 = pADI_ADC->ADCDAT[iChan];
         }
      }
   return i1;
   }
 
/**
   @brief int AdcBuf(int iBufPDn, int iBufByp, int iRBufCfg)
         ==========Configures ADC buffers.
   @param iBufPDn :{IBUFCON_IBUF_PD_NONE| IBUFCON_IBUF_PD_NSIDE| 
            IBUFCON_IBUF_PD_PSIDE| IBUFCON_IBUF_PD_BOTH}         \n
   - IBUFCON.[3:2]
   - Combination of the following features :
      - 0 or IBUFCON_IBUF_PD_NONE for both input buffers powered on.
      - 4 or IBUFCON_IBUF_PD_NSIDE to power down N-Side only.
      - 8 or IBUFCON_IBUF_PD_PSIDE to power down P-Side only.
      - 0x10 or IBUFCON_IBUF_PD_BOTH to power down both sides of input buffer.
      - 8 or ADCCON_BUFPOWN to power down negative reference buffer.
   @param iBufByp :{IBUFCON_IBUF_BYP_NONE| IBUFCON_IBUF_BYP_NSIDE| 
            IBUFCON_IBUF_BYP_PSIDE| IBUFCON_IBUF_BYP_BOTH}         \n
      - IBUFCON.[1:0]
      - Combination of the following features :
      - 0 or IBUFCON_IBUF_BYP_NONE for both input buffers enabled.
      - 1 or IBUFCON_IBUF_BYP_NSIDE to by-pass N-Side only.
      - 2 or IBUFCON_IBUF_BYP_PSIDE to by-pass P-Side only.
      - 4 or IBUFCON_IBUF_BYP_BOTH to by-pass both sides of input buffer.
   @param iRBufCfg :{0,ADCCON_REFB_PUP}
   - ADCCON.7 - Not currently used
   - Combination of the following features :
      - 0 to powered down reference buffer. Only set for power down mode and 
            when ADC not required.     \n
      - 1 or ADCCON_REFB_PUP. Power up internal reference buffer - must be 
            set for ADC operation.     \n
   @return 1.
**/

int AdcBuf(int iBufPDn, int iBufByp, int iRBufCfg)
   {
   int   i1 = 0;

   i1 = (pADI_InBuf->IBUFCON & 0xFFF0);
   i1 |= (iBufPDn + iBufByp);      
   pADI_InBuf->IBUFCON = i1;
   return pADI_InBuf->IBUFCON;
   }

/**
   @brief int AdcSpeed(int iDiv)
         ========== ADC conversion = ACLK/iDiv.
   @param iDiv :{20-127}
      - Set iDiv to desired 16MHz division factor - S1 silicon:
      - Set iDiv to desired 20MHz division factor - S2 silicon:
   @return ADCCNV MMR.  Not normally of interest.
**/

int AdcSpeed(int iDiv)
   {
   int i1 = 0;
   
   if(pADI_LV->LVID == 0x71)  //For S1 silicon.
      {
      i1  = 0x80000;          //Acquisition delay = 500ns.
      }
   else                       //For S2 Silicon and further.
      {
      i1  = 0xA0000;          //Acquisition delay = 500ns.
      }
   pADI_ADC->ADCCNVC = i1 | (iDiv &0x3FF);
   return pADI_ADC->ADCCNVC;
   }

/**
   @brief int AdcPin(int iInN, int iInP)
         ==========Sets up input channels for non Sequencer based conversions.
   @param iInN :{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,AIN10,
            AIN11,AIN12,AIN13,AIN14,AIN15,VREFP_NADC,VREFN_NADC,AGND,PGND} \n
      - ADCCHA.[12:8]
         - 0x00 to 0x0f or AIN0 to AIN15 for input pins AIN0 to AIN15.
         - 0x11 or VREFN_NADC for negative reference - Use for Single ended 
               measurements.  \n
         - 0x12 or AGND
         - 0x13 or PGND
   @param iInP :{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,AIN10,AIN11,
            AIN12,AIN13,AIN14,AIN15,AIN_IDAC3,AIN_IDAC1,AIN_IDAC0,AIN_IDAC2,
            TEMP_SENSOR,VREFP_PADC,PVDD_IDAC2,IOVDD_2,AVDD_2,VREFN_PADC}   \n   
      - ADCCHA.[4:0]
   @return 1.
**/

int AdcPin(int iInN, int iInP)
   {
   int   i1 = 0;

   i1 =  (iInN << 8);  
   pADI_ADC->ADCCHA = i1 + iInP;
   return 1;
   }

/**
   @brief int AdcCal(int iGain, int iOffset)
         ==========Loads calibration registers.
   @param iGain :{0-0x3FFF}
      - iGain
      - ADCGN.[13:0]
   @param iOffset :{0-0x3FFF}
      - iOffset
      - ADCOF.[13:0]
   @return 1
   @warning Only set when ADC is in Idle mode (ADCCON[2:0] = 000b.
**/

int AdcCal(int iGain, int iOffset)
   {
   pADI_ADC->ADCGN = (unsigned int)(iGain &0x3FFF);
   pADI_ADC->ADCOF = (unsigned int)(iOffset &0x3FFF);
   return 1;
   }
/**
   @brief int AdcSeqCfg(int iEnable, int iChP, int iDelay)
         ==========Sets up Positive input channels for Sequencer based conversions.
   @param iEnable :{0,ADCSEQ_EN}
      - 0 to disable ADC Sequencer.
      - 0x40000000 to enable Sequencer.
   @param iChP :{AIN0_Seq|AIN1_Seq|AIN2_Seq|AIN3_Seq|AIN4_Seq|AIN5_Seq|
         AIN6_Seq|AIN7_Seq|AIN8_Seq|AIN9_Seq|AIN10_Seq|AIN11_Seq|AIN12_Seq|
         AIN13_Seq|AIN14_Seq|AIN15_Seq|IDAC3_Seq|IDAC1_Seq|IDAC0_Seq|
         IDAC2_Seq|TEMP_Seq|VREFP_Seq|PVDD_Seq|IOVDD_2_Seq|AVDD_2_Seq|
         VREFN_Seq}   \n
      - ADCSEQ.[28:0]
   @param iDelay :{0-0xFF}
      - ADCSEQC[27:20]
   @return 1.
**/
int AdcSeqCfg(int iEnable, int iChP, int iDelay)
   {
   unsigned long ul1;
   pADI_ADC->ADCSEQ = (iEnable + iChP);
   ul1 = pADI_ADC->ADCSEQC & 0xF00FFFFF;        //clear delay bits.
   pADI_ADC->ADCSEQC = ul1 | (iDelay<<20);
   return 1;
   }
   
 /**
   @brief  int AdcSeqDiffCfg(int iDiff0,int iDiff2,int iDiff4,int iDiff6)
         ==========Sets up Differential input pairs
               for Sequencer based conversions - AIN0, AIN2, AIN4, AIN6.   \n
   @param iDiff0 :{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,AIN10,
         AIN11,AIN12,AIN13,AIN14,AIN15,VREFP_NADC,VREFN_NADC,AGND,PGND}   \n
      - ADCSEQC.[4:0]
         - 0x00 to 0x0f or AIN0 to AIN15 for input pins AIN0 to AIN15.
         - 0x10 or VREFP_NADC for Positive ADC reference.
         - 0x11 or VREFN_NADC for negative reference - Use for Single ended 
               measurements.   \n
         - 0x12 or AGND
         - 0x13 or PGND
   @param iDiff2 :{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,AIN10,
         AIN11,AIN12,AIN13,AIN14,AIN15,VREFP_NADC,VREFN_NADC,AGND,PGND}   \n
      - ADCSEQC.[9:5]
         - 0x00 to 0x0f or AIN0 to AIN15 for input pins AIN0 to AIN15.
         - 0x10 or VREFP_NADC for Positive ADC reference.
         - 0x11 or VREFN_NADC for negative reference - Use for Single ended 
               measurements.   \n
         - 0x12 or AGND
         - 0x13 or PGND
   @param iDiff4 :{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,AIN10,
         AIN11,AIN12,AIN13,AIN14,AIN15,VREFP_NADC,VREFN_NADC,AGND,PGND}   \n
      - ADCSEQC.[14:10]
         - 0x00 to 0x0f or AIN0 to AIN15 for input pins AIN0 to AIN15.
         - 0x10 or VREFP_NADC for Positive ADC reference.
         - 0x11 or VREFN_NADC for negative reference - Use for Single ended 
               measurements.   \n
         - 0x12 or AGND
         - 0x13 or PGND
   @param iDiff6 :{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,AIN10,
         AIN11,AIN12,AIN13,AIN14,AIN15,VREFP_NADC,VREFN_NADC,AGND,PGND}   \n
      - ADCSEQC.[19:15]
         - 0x00 to 0x0f or AIN0 to AIN15 for input pins AIN0 to AIN15.
         - 0x10 or VREFP_NADC for Positive ADC reference.
         - 0x11 or VREFN_NADC for negative reference - Use for Single ended 
               measurements.   \n
         - 0x12 or AGND
         - 0x13 or PGND      
   @return 1.
**/  
int AdcSeqDiffCfg(int iDiff0,int iDiff2,int iDiff4,int iDiff6)
   {
   int i1;
   
   i1 = (pADI_ADC->ADCSEQC & 0x0FF00000);
   i1 |= iDiff0 + (iDiff2 <<5) + (iDiff4 <<10) +(iDiff2 <<15);
   pADI_ADC->ADCSEQC = i1;
   return 1;   
   }
   
/**
   @brief int AdcSeqStart(unsigned long iStart)
             ==========Starts/Halts ADC Sequencer.
   @param iStart :{0,ADCSEQ_ST}   
      - 0 to halt.
      - 0x80000000 or ADCSEQ_ST to restart ADC sequencer.
   @return 1:

**/

int AdcSeqStart(unsigned long iStart)
   {
   pADI_ADC->ADCSEQ |= (iStart & 0x80000000);  
   return 1;
   }

/**
   @brief int AdcDigCompCfg(int iEnable, int iDir, int iThreshold)   
             ==========Configure ADC Digital comparator.
   @param iEnable :{ADCCMP_EN_EN,ADCCMP_EN_DIS}   
      - 1 or ADCCMP_EN_EN to enable ADC digital comparator.
      - 0 or ADCCMP_EN_DIS to disable ADC digital comparator.
   @param iDir :{ADCCMP_DIR_EN,ADCCMP_DIR_DIS}
      - 0x2 or ADCCMP_DIR_EN to trigger on ADCTH greater than ADCDAT4.
      - 0 or ADCCMP_DIR_DIS to trigger on ADCTH less than ADCDAT4.
   @param iThreshold :{0-0xFFFF}
      - ADCTH value, ADC Comparator threshold value.
   @return 1:
**/

int AdcDigCompCfg(int iEnable, int iDir, int iThreshold)
   {
   pADI_ADC->ADCCMP = iEnable + iDir + iThreshold;
   return 1;
   }

	 /**
	@brief int AdcDma(int iEnable)	
	 			==========Configure ADC DMA operation	
	@param iEnable :{0,ADCCON_CNV_DMA,ADCCON_SEQ_DMA}	
		- 0 to disable ADC DMA operation
      - 0x8  or ADCCON_CNV_DMA to enable ADC DMA non sequencer operation
      - 0x10 or ADCCON_SEQ_DMA to enable ADC DMA Sequencer operation
	@return 1:

**/
int AdcDma(int iEnable)
{
   int i1;
   
   i1 = pADI_ADC->ADCCON & 0xFFE7;
   i1 |= iEnable;
   pADI_ADC->ADCCON = i1;
   return 1;
}


/**@}*/
