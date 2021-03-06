/**
	@File:			wmgr.h
	@Author:		Ihsoh
	@Date:			2015-08-15
	@Description:
		窗体管理器。
*/

#ifndef	_WINDOWS_WMGR_H_
#define	_WINDOWS_WMGR_H_

#include "../types.h"
#include "../window.h"

extern
BOOL
WinWmgrInit(void);

extern
BOOL
WinWmgrShow(IN int32 x,
			IN int32 taskbar_y);

extern
BOOL
WinWmgrHide(void);

extern
void
WinWmgrUpdate(IN uint32 offset);

#endif
		