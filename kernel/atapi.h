/**
	@File:			atapi.h
	@Author:		Ihsoh
	@Date:			2015-02-26
	@Description:
*/

#ifndef	_ATAPI_H_
#define	_ATAPI_H_

#include "types.h"
#include "386.h"

/* The default and seemingly universal sector size for CD-ROMs. */
#define ATAPI_SECTOR_SIZE 2048
 
/* The default ISA IRQ numbers of the ATA controllers. */
#define ATA_IRQ_PRIMARY     0x0E
#define ATA_IRQ_SECONDARY   0x0F
 
/* The necessary I/O ports, indexed by "bus". */
#define ATA_DATA(x)         (x)
#define ATA_FEATURES(x)     (x+1)
#define ATA_SECTOR_COUNT(x) (x+2)
#define ATA_ADDRESS1(x)     (x+3)
#define ATA_ADDRESS2(x)     (x+4)
#define ATA_ADDRESS3(x)     (x+5)
#define ATA_DRIVE_SELECT(x) (x+6)
#define ATA_COMMAND(x)      (x+7)
#define ATA_DCR(x)          (x+0x206)   /* device control register */
 
/* valid values for "bus" */
#define ATA_BUS_PRIMARY     0x1F0
#define ATA_BUS_SECONDARY   0x170
/* valid values for "drive" */
#define ATA_DRIVE_MASTER    0xA0
#define ATA_DRIVE_SLAVE     0xB0
 
/* ATA specifies a 400ns delay after drive switching -- often
 * implemented as 4 Alternative Status queries. */
#define ATA_SELECT_DELAY(bus) \
  {KnlInByte(ATA_DCR(bus));KnlInByte(ATA_DCR(bus));KnlInByte(ATA_DCR(bus));KnlInByte(ATA_DCR(bus));}

#define	ATAPI_MAX_SIZE			(MB(700))
#define	ATAPI_SECTOR_COUNT 		(ATAPI_MAX_SIZE / ATAPI_SECTOR_SIZE)
#define	ATAPI_SECTOR512_COUNT	(ATAPI_MAX_SIZE / 512)

extern
BOOL
AtapiInit(void);

extern
BOOL
AtapiIsLocked(void);

extern
int32
AtapiGetLockTid(void);

extern
void
AtapiAttemptToUnlock(IN int32 tid);

extern
int32
AtapiReadSector(	IN uint32 bus,
					IN uint32 drive,
					IN uint32 lba,
					OUT uint8 * buffer);

extern
BOOL
AtapiReadSector512(	IN uint32 bus,
					IN uint32 drive,
					IN uint32 pos, 
					OUT uint8 * buffer);

extern
BOOL
AtapiReadSector512s(IN uint32 bus,
					IN uint32 drive,
					IN uint32 pos,
					IN uint32 count,
					OUT uint8 * buffer);

#endif
