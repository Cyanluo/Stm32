#ifndef _W25QXX_H_
#define _W25QXX_H_
#include "sys.h"

#define W25QCS PBout(12)

//÷∏¡Ó±Ì
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

void W25q_Init(void);
void W25q_Write_Page(u8 *sendbuf,u32 sendadd,u16 sendnum);
u8 W25q_ReSR(void);
void W25q_WrSR(u8 dat);
void W25q_Write_Enable(void);
void W25q_Write_Disable(void);
void W25q_Wate_Busy(void);
void W25q_Erase_Sector(u32 add);
void W25q_Erase_Chip(void);
void W25q_Wr_nocheck(u8 *sendbuf,u32 sendadd,u16 sendnum);
void W25q_Re_Page(u8 *sendbuf,u32 sendadd,u16 sendnum);
void W25q_Write_Page(u8 *sendbuf,u32 sendadd,u16 sendnum);
void W25q_Wr_Check(u8 *sendbuf,u32 sendadd,u16 sendnum);
void W25q_PowerDown(void);
void W25q_WAKEUP(void); 
u16 W25QXX_ReadID(void); 


#endif
