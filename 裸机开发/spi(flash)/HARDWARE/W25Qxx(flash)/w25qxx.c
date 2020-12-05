#include "w25qxx.h"
#include "spi.h"
#include "delay.h"

u8 Buf[4096];

void W25q_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstruct);
	
	W25QCS=1;
	SPI2_Init();
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	SPI2_SetSpeed(SPI_BaudRatePrescaler_2);	
}

u8 W25q_ReSR(void)
{
	u8 dat=0;
	W25QCS=0;
	SPI2_RW_Byte(W25X_ReadStatusReg);
	dat=SPI2_RW_Byte(0xff);
	W25QCS=1;
	return dat;
}

void W25q_WrSR(u8 dat)
{
	W25QCS=0;
	SPI2_RW_Byte(W25X_WriteStatusReg);
	SPI2_RW_Byte(dat);
	W25QCS=1;
}

void W25q_Write_Enable(void)
{
	W25QCS=0;
	SPI2_RW_Byte(W25X_WriteEnable);
	W25QCS=1;
}

void W25q_Write_Disable(void)
{
	W25QCS=0;
	SPI2_RW_Byte(W25X_WriteDisable);
	W25QCS=1;
}

//等待空闲
void W25q_Wait_Busy(void)   
{   
	while((W25q_ReSR()&0x01)==0x01);  		// 等待BUSY位清空
} 

void W25q_Erase_Sector(u32 add)
{
	add*=4096;
	W25q_Write_Enable();
	W25q_Wait_Busy();
	W25QCS=0;
	SPI2_RW_Byte(W25X_SectorErase);
	SPI2_RW_Byte((u8)(add>>16));
	SPI2_RW_Byte((u8)(add>>8));
	SPI2_RW_Byte((u8)add);
	W25QCS=1;
	W25q_Wait_Busy();
}

void W25q_Erase_Chip(void)
{
	W25q_Write_Enable();
	W25q_Wait_Busy();
	W25QCS=0;
	SPI2_RW_Byte(W25X_ChipErase);
	W25QCS=1;
	W25q_Wait_Busy();
}

void W25q_Write_Page(u8 *sendbuf,u32 sendadd,u16 sendnum)
{
	u16 i;

	W25q_Write_Enable();
//	W25q_Wait_Busy();
	W25QCS=0;
	SPI2_RW_Byte(W25X_PageProgram);
	SPI2_RW_Byte((u8)(sendadd>>16));
	SPI2_RW_Byte((u8)(sendadd>>8));
	SPI2_RW_Byte((u8)sendadd);
	for(i=0;i<sendnum;i++)
	{
		SPI2_RW_Byte(sendbuf[i]);
	}
	W25QCS=1;
	W25q_Wait_Busy();
}

void W25q_Wr_nocheck(u8 *sendbuf,u32 sendadd,u16 sendnum)
{
	u16 leftnum;
	leftnum=256-sendadd%256;
	if(leftnum>=sendnum)
		leftnum=sendnum;
	while(1)
	{
		W25q_Write_Page(sendbuf,sendadd,leftnum);
		if(leftnum==sendnum) break;
		else
		{
			sendnum-=leftnum;
			sendadd+=leftnum;
			sendbuf+=leftnum;
			if(sendnum>256)
				leftnum=256;
			else
				leftnum=sendnum;
		}
	}
}

void W25q_Re_Page(u8 *sendbuf,u32 sendadd,u16 sendnum)
{
	u16 i;
	W25QCS=0;
	SPI2_RW_Byte(W25X_ReadData);
	SPI2_RW_Byte((u8)(sendadd>>16));
	SPI2_RW_Byte((u8)(sendadd>>8));
	SPI2_RW_Byte((u8)sendadd);
	for(i=0;i<sendnum;i++)
	{
		sendbuf[i]=SPI2_RW_Byte(0xff);
	}
	W25QCS=1;	
}

void W25q_Wr_Check(u8 *sendbuf,u32 sendadd,u16 sendnum)
{	
	u32 seposadd,i;
	u16 sepyadd;
	u16 seleft;
	seposadd=sendadd/4096;
	sepyadd=sendadd%4096;
	seleft=4096-sepyadd;
	if(seleft>=sendnum)
		seleft=sendnum;
	while(1)
	{
		W25q_Re_Page(Buf,seposadd*4096,4096);
		for(i=0;i<seleft;i++)
		{
			if(Buf[sepyadd+i]!=0xff)
			break;	
		}
		if(i<seleft)
		{
			W25q_Erase_Sector(seposadd);

			for(i=0;i<seleft;i++)
			{
				Buf[sepyadd+i]=sendbuf[i];	
			}
			W25q_Wr_nocheck(Buf,seposadd*4096,4096);
		}
		else 
			W25q_Wr_nocheck(sendbuf,sendadd,seleft);
		if(seleft==sendnum)
			break;
		else
		{
			sendbuf+=seleft;
			sendadd+=seleft;
			sendnum-=seleft;
			seposadd++;
			sepyadd=0;
			if(sendnum>4096)
				seleft=4096;
			else
				seleft=sendnum;
		}
	}
}

//进入掉电模式
void W25q_PowerDown(void)   
{ 
  	W25QCS=0;                           	 	//使能器件   
    SPI2_RW_Byte(W25X_PowerDown);        //发送掉电命令  
	W25QCS=1;                            	//取消片选     	      
    delay_us(3);                               //等待TPD  
}   
//唤醒
void W25q_WAKEUP(void)   
{  
  	W25QCS=0;                            	//使能器件   
    SPI2_RW_Byte(W25X_ReleasePowerDown);	//  send W25X_PowerDown command 0xAB    
	W25QCS=1;                            	//取消片选     	      
    delay_us(3);                            	//等待TRES1
}   

//读取芯片ID
//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64 
//0XEF17,表示芯片型号为W25Q128 	  
u16 W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	W25QCS=0;				    
	SPI2_RW_Byte(0x90);//发送读取ID命令	    
	SPI2_RW_Byte(0x00); 	    
	SPI2_RW_Byte(0x00); 	    
	SPI2_RW_Byte(0x00); 	 			   
	Temp|=SPI2_RW_Byte(0xFF)<<8;  
	Temp|=SPI2_RW_Byte(0xFF);	 
	W25QCS=1;				    
	return Temp;
}









