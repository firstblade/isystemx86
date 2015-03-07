/**
	@File:			scall_system.h
	@Author:		Ihsoh
	@Date:			2014-7-29
	@Description:
*/

#ifndef	_SCALL_SYSTEM_H_
#define	_SCALL_SYSTEM_H_

#include "types.h"
#include "sparams.h"
#include "lock.h"

#define	SCALL_EXIT				0
#define	SCALL_ALLOC_M			1
#define	SCALL_FREE_M			2
#define	SCALL_GET_PARAM			3
#define	SCALL_GET_DATETIME		4
#define	SCALL_SET_CLOCK			5
#define	SCALL_MQUEUE_S_CREATE	6
#define	SCALL_MQUEUE_S_DELETE	7
#define	SCALL_MQUEUE_S_PUSH		8
#define	SCALL_MQUEUE_S_POP		9
#define	SCALL_MQUEUE_C_PUSH		10
#define	SCALL_MQUEUE_C_POP		11
#define	SCALL_RUN_IN_BG			12
#define	SCALL_SET_RETVALUE		13

extern
void
system_call_system(	IN uint32 func,
					IN uint32 base,
					IN OUT struct SParams * sparams);

#endif
