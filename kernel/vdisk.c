/**
	@File:			vdisk.c
	@Author:		Ihsoh
	@Date:			2014-6-5
	@Description:
		提供虚拟硬盘的功能。
*/


#include "vdisk.h"
#include "types.h"
#include "memory.h"
#include "screen.h"
#include <ilib/string.h>

static uint8 * vdiska = NULL;
static uint8 * vdiskb = NULL;

/**
	@Function:		VdskInit
	@Access:		Public
	@Description:
		初始化虚拟硬盘。
	@Parameters:
		symbol, int8 *, IN
			盘符。VA 或 VB。
	@Return:
*/
void
VdskInit(IN int8 * symbol)
{
	uint32 ui;
	if(strcmp(symbol, "VA") == 0)
	{
		vdiska = (uint8 *)MemAlloc(VDISK_BUFFER_SIZE);
		if(vdiska != NULL)
			for(ui = 0; ui < VDISK_BUFFER_SIZE; ui++)
				vdiska[ui] = 0;	
	}
	else if(strcmp(symbol, "VB") == 0)
	{
		vdiskb = (uint8 *)MemAlloc(VDISK_BUFFER_SIZE);
		if(vdiskb != NULL)
			for(ui = 0; ui < VDISK_BUFFER_SIZE; ui++)
				vdiskb[ui] = 0;	
	}
}

/**
	@Function:		VdskDestroy
	@Access:		Public
	@Description:
		销毁指定虚拟硬盘资源。
	@Parameters:
		symbol, int8 *, IN
			盘符。
	@Return:	
*/
void
VdskDestroy(IN int8 * symbol)
{
	if(strcmp(symbol, "VA") == 0)
	{
		if(vdiskb != NULL)
			MemFree(vdiska);
	}	
	else if(strcmp(symbol, "VB") == 0)
		if(vdiskb != NULL)
			MemFree(vdiskb);
}

/**
	@Function:		VdskGetSectorCount
	@Access:		Public
	@Description:
		获取虚拟硬盘的扇区数量。
	@Parameters:
	@Return:
		uint32
			扇区数量。		
*/
uint32
VdskGetSectorCount(void)
{
	return VDISK_SECTORS;
}

/**
	@Function:		VdskGetSize
	@Access:		Public
	@Description:
		获取指定虚拟硬盘容量，单位为KB。
	@Parameters:
		symbol, int8 *, IN
			盘符。
	@Return:
		uint32
			指定虚拟硬盘容量。		
*/
uint32
VdskGetSize(IN int8 * symbol)
{
	if(strcmp(symbol, "VA") == 0)
		if(vdiska == NULL)
			return 0;
		else
			return VDISK_BUFFER_SIZE / 1024;
	else if(strcmp(symbol, "VB") == 0)
		if(vdiskb == NULL)
			return 0;
		else
			return VDISK_BUFFER_SIZE / 1024;
	else
		return 0;
}

/**
	@Function:		VdskReadSector
	@Access:		Public
	@Description:
		读取一个扇区的数据。
	@Parameters:
		symbol, int8 *, IN
			磁盘标识符。
		pos, uint32, IN
			LBA表示法的逻辑地址。
		buffer, uint8 *, OUT
			指向用于储存扇区数据的缓冲区。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
VdskReadSector(	IN int8 * symbol, 
				IN uint32 pos, 
				OUT uint8 * buffer)
{
	uint8 * start = NULL;
	uint32 ui;
	if(strcmp(symbol, "VA") == 0)
		start = vdiska;
	else if(strcmp(symbol, "VB") == 0)
		start = vdiskb;
	else
		return FALSE;
	if(start == NULL || pos >= VDISK_SECTORS)
		return FALSE;
	for(ui = 0; ui < VDISK_SECTOR_SIZE; ui++)
		*(buffer + ui) = *(start + pos * VDISK_SECTOR_SIZE + ui);
	return TRUE;
}

/**
	@Function:		VdskWriteSector
	@Access:		Public
	@Description:
		写入数据到一个扇区。
	@Parameters:
		symbol, int8 *, IN
			磁盘标识符。
		pos, uint32, IN
			LBA表示法的逻辑地址。
		buffer, uint8 *, IN
			指向包含将要写入扇区的数据的缓冲区。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。	
*/
BOOL
VdskWriteSector(IN int8 * symbol,
				IN uint32 pos,
				IN uint8 * buffer)
{
	uint8 * start = NULL;
	uint32 ui;
	if(strcmp(symbol, "VA") == 0)
		start = vdiska;
	else if(strcmp(symbol, "VB") == 0)
		start = vdiskb;
	else
		return FALSE;
	if(start == NULL || pos >= VDISK_SECTORS)
		return FALSE;
	for(ui = 0; ui < VDISK_SECTOR_SIZE; ui++)
		*(start + pos * VDISK_SECTOR_SIZE + ui) = *(buffer + ui);
	return TRUE;
}

/**
	@Function:		VdskReadSectors
	@Access:		Public
	@Description:
		读取一个或多个扇区的数据。最多一次可以读取256个扇区的数据。
	@Parameters:
		symbol, int8 *, IN
			磁盘标识符。
		pos, uint32, IN
			LBA表示法的逻辑地址。
		count, uint8, IN
			要读取的扇区的数量。当该参数为0时代表要读取256个扇区。
		buffer, uint8 *, OUT
			指向用于储存扇区数据的缓冲区。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。		
*/
BOOL
VdskReadSectors(IN int8 * symbol,
				IN uint32 pos,
				IN uint8 count,
				OUT uint8 * buffer)
{
	BOOL r = TRUE;
	int32 c;
	if(count == 0)
		c = 256;
	else
		c = count;
	while(c > 0)
	{
		if(!VdskReadSector(symbol, pos, buffer))
		{
			r = FALSE;
			break;		
		}		
		pos++;
		buffer += 512;
		c--;
	}
	return r;
}

/**
	@Function:		VdskWriteSectors
	@Access:		Public
	@Description:
		写入数据到一个或多个扇区。最多一次可以写入256个扇区的数据。
	@Parameters:
		symbol, int8 *, IN
			磁盘标识符。
		pos, uint32, IN
			LBA表示法的逻辑地址。
		count, uint8, IN
			要写入数据的扇区的数量。当该参数为0时代表要读取256个扇区。
		buffer, uint8 *, IN
			指向包含将要写入扇区的数据的缓冲区。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
VdskWriteSectors(	IN int8 * symbol,
					IN uint32 pos,
					IN uint8 count,
					IN uint8 * buffer)
{
	BOOL r = TRUE;
	int32 c;
	if(count == 0)
		c = 256;
	else
		c = count;
	while(c > 0)
	{
		if(!VdskWriteSector(symbol, pos, buffer))
		{
			r = FALSE;
			break;
		}
		pos++;
		buffer += 512;
		c--;
	}
	return r;
}
