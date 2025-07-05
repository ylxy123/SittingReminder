#include "devadc.h"



//ADC-CH 1 ADC-CH2
void APP_AdcConfig(void)
{
  /* Enable GPIOA clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Configure PA7 pin in analog input mode */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_ANALOG);
  
  /* Configure PA6 pin in analog input mode */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);

  /* Set ADC clock to pclk/4 */
  LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV4);

  /* Set ADC resolution to 12 bit */
  LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);

  /* ADC conversion data alignment: right aligned */
  LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

  /* No ADC low power mode activated */
  LL_ADC_SetLowPowerMode(ADC1, LL_ADC_LP_MODE_NONE);

  /* Sampling time 239.5 ADC clock cycles */
  LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_239CYCLES_5);

  /* ADC regular group conversion trigger by software. */
  LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

  /* Set ADC conversion mode to single mode: one conversion per trigger */
  LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

  /* ADC regular group behavior in case of overrun: data overwritten */
  LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

  /* Disable ADC regular group sequencer discontinuous mode  */
  LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

  /* Dose not enable internal conversion channel */
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_NONE );
}



void APP_AdcCalibrate(void)
{
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {

    /* Enable ADC calibration */
    LL_ADC_StartCalibration(ADC1);

    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
    {
    }

    /* The delay between the end of ADC calibration and ADC enablement is at least 4 ADC clocks */
    LL_mDelay(1);
  }
}

void APP_AdcEnable(void)
{
  /* Enable ADC */
  LL_ADC_Enable(ADC1);

  /* The delay between ADC enablement and ADC stabilization is at least 8 ADC clocks */
  LL_mDelay(1);
}

uint32_t APP_AdcConvert(uint32_t channel)
{
  uint16_t AdcConvertValue = 0;
  /* Configure channel need ADC is disable */
  if(LL_ADC_IsEnabled(ADC1))
  {
    LL_ADC_Disable(ADC1);
  }
  /* Set channel as conversion channel */
  LL_ADC_REG_SetSequencerChannels(ADC1, channel);
  
  /* Enable ADC */
  APP_AdcEnable();

  /* Start ADC conversion */
  LL_ADC_REG_StartConversion(ADC1);
  
  /* Wait ADC conversion complete */
  while(LL_ADC_IsActiveFlag_EOC(ADC1)==0);
  
  /* Clear eoc flag */
  LL_ADC_ClearFlag_EOC(ADC1);
  
  /* Get conversion value */
  AdcConvertValue = LL_ADC_REG_ReadConversionData12(ADC1);
  
  LL_ADC_Disable(ADC1);
  
  /* Clear the selected channel */
  LL_ADC_REG_SetSequencerChRem(ADC1, channel);
  
  return (uint32_t)AdcConvertValue; 
}


void dev_adc_init(void)
{
    /* Enable ADC1 clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);

  /* Configure ADC parameters */
  APP_AdcConfig();

  /*  ADC automatic self-calibration */
  APP_AdcCalibrate();

}