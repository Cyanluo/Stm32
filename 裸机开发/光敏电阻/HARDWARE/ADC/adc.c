#include"adc.h"

void ADC1_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	ADC_InitTypeDef ADC_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(ADC1);
	
	ADC_Initstruct.ADC_ContinuousConvMode=DISABLE;
	ADC_Initstruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_Initstruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_Initstruct.ADC_Mode=ADC_Mode_Independent;
	ADC_Initstruct.ADC_NbrOfChannel=1;
	ADC_Initstruct.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC1,&ADC_Initstruct);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));		
}

u16 Get_Adc(u8 ch)
{
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_1Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC1);
}

u16 Get_Average_Val(u8 ch,u8 cn)
{
	u16 i,val=0;
	for(i=0;i<cn;i++)
	{
		val+=Get_Adc(ch);
	}
	return val/cn;
}

void ADC3_Init(void)
{
	ADC_InitTypeDef ADC_Initstruct;
	GPIO_InitTypeDef GPIO_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF |RCC_APB2Periph_ADC3,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOF,&GPIO_Initstruct);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_DeInit(ADC3);
	ADC_Initstruct.ADC_ContinuousConvMode=DISABLE;
	ADC_Initstruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_Initstruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_Initstruct.ADC_Mode=ADC_Mode_Independent;
	ADC_Initstruct.ADC_NbrOfChannel=1;
	ADC_Initstruct.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC3,&ADC_Initstruct);
	
	ADC_Cmd(ADC3,ENABLE);
	
	ADC_ResetCalibration(ADC3);
	while(ADC_GetResetCalibrationStatus(ADC3));
	ADC_StartCalibration(ADC3);
	while(ADC_GetCalibrationStatus(ADC3));
}



u16 Get_Adc3(u8 ch)
{
	ADC_RegularChannelConfig(ADC3,ch,1,ADC_SampleTime_1Cycles5);
	ADC_SoftwareStartConvCmd(ADC3,ENABLE);
	while(!ADC_GetFlagStatus(ADC3,ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC3);
}


