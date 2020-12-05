#include "uart.h"
#include "delay.h"
#include "dma.h"
#include "lcd.h"
#include "keyscan.h"

#define SENT_SIZE 8020
unsigned char buffer[SENT_SIZE];

unsigned char send_buffer[]="STM32f103 DMA TEST";

int main()
{
	u16 i,j;
	u8 t1,t2,key,flag1;
	
	Usart1_Init(115200);
//	uart_init(115200);
	delay_init();
	LCD_Init();
	Key_Init();
	LCD_ShowString(30,90,250,16,24,"Please PRESS KEY_UP");
	DMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)buffer,SENT_SIZE);
	j=sizeof(send_buffer);
	while(1)
	{
		for(i=0;i<SENT_SIZE;i++)
		{	
			if(t1>=j)
			{	
				if(t2)
				{
					buffer[i]=0x0a;
					t1=0;
				}
				else
				{
					buffer[i]=0x0d;					
					t2=1;
				}
			}
			else
			{
				buffer[i]=send_buffer[t1];
				t1++;
				t2=0;
			}
		}
		key=KeyScan(1);
		
		
			if(key==KEY_3_DW)
			{
				LCD_ShowString(30,150,200,16,16,"Start Transimit....");
				LCD_ShowString(30,170,200,16,24,"   %");//œ‘ æ∞Ÿ∑÷∫≈
				flag1=1;
				USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
				DMA_Enable(DMA1_Channel4);
			}
		if(flag1==1)
		{
			float bfb;
			while(1)
			{
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)==RESET)
				{
					bfb=DMA_GetCurrDataCounter(DMA1_Channel4);
					bfb=(1-bfb/SENT_SIZE)*100;
					LCD_ShowNum(30,170,bfb,3,24);
				}
				else
				{	
					DMA_ClearFlag(DMA1_FLAG_TC4);
					LCD_ShowNum(30,170,100,3,24);
					LCD_ShowString(30,150,200,16,16,"finish..........");
					flag1=0;
					break;
				};
			}
		}
	}
}



