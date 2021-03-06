/**
	@File:			timer.c
	@Author:		Ihsoh
	@Date:			2015-08-19
	@Description:
		定时器。
*/

#include "timer.h"
#include "types.h"
#include "memory.h"
#include "tasks.h"

static uint32		_ticks;
static TimerPtr		_timers[MAX_TIMER_COUNT];

/**
	@Function:		TmrInit
	@Access:		Public
	@Description:
		初始化定时器。
	@Parameters:
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
TmrInit(void)
{
	_ticks = 0;
	uint32 ui;
	for(ui = 0; ui < MAX_TIMER_COUNT; ui++)
		_timers[ui] = NULL;
	return TRUE;
}

/**
	@Function:		_TmrDispatchTick
	@Access:		Private
	@Description:
		分发Tick事件。
	@Parameters:
	@Return:
*/
static
void
_TmrDispatchTick(void)
{
	uint32 ui;
	for(ui = 0; ui < MAX_TIMER_COUNT; ui++)
	{
		TimerPtr timer = _timers[ui];
		if(timer != NULL && timer->enabled && timer->ticks != 0)
			timer->ticks--;
	}
}

/**
	@Function:		TmrDispatchTick
	@Access:		Public
	@Description:
		执行各个定时器的事件。
	@Parameters:
	@Return:
*/
void
TmrDispatchTick(void)
{
	uint32 ui;
	for(ui = 0; ui < MAX_TIMER_COUNT; ui++)
	{
		TimerPtr timer = _timers[ui];
		if(timer != NULL && timer->enabled && timer->ticks == 0)
		{
			timer->event();
			timer->ticks = timer->interval;
		}
	}
}

/**
	@Function:		TmrIncTicks
	@Access:		Public
	@Description:
		滴答数递增1。
	@Parameters:
	@Return:
*/
void
TmrIncTicks(void)
{
	_ticks++;
	_TmrDispatchTick();
}

/**
	@Function:		TmrGetTicks
	@Access:		Public
	@Description:
		获取从定时器初始化以来的滴答数。
	@Parameters:
	@Return:
		uint32
			从定时器初始化以来的滴答数。
*/
uint32
TmrGetTicks(void)
{
	return _ticks;
}

/**
	@Function:		TmrNew
	@Access:		Public
	@Description:
		新建一个定时器。
	@Parameters:
		interval, uint32, IN
			引发事件的时间间隔，单位：ms。
		event, TimerEvent, IN
			事件函数指针。
	@Return:
		TimerPtr
			指向定时器对象的指针。返回NULL则新建失败。
*/
TimerPtr
TmrNew(	IN uint32 interval,
		IN TimerEvent event)
{
	if(interval == 0 || event == NULL)
		return NULL;
	TimerPtr timer = NEW(Timer);
	if(timer == NULL)
		return NULL;
	uint32 ui;
	for(ui = 0; ui < MAX_TIMER_COUNT; ui++)
		if(_timers[ui] == NULL)
		{
			timer->interval = interval;
			timer->event = event;
			timer->enabled = FALSE;
			timer->ticks = interval;
			_timers[ui] = timer;
			return timer;
		}
	DELETE(timer);
	return NULL;
}

/**
	@Function:		TmrDelete
	@Access:		Public
	@Description:
		删除一个定时器。
	@Parameters:
		timer, TimerPtr, IN
			指向定时器对象的指针。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
TmrDelete(IN TimerPtr timer)
{
	if(timer == NULL)
		return FALSE;
	uint32 ui;
	for(ui = 0; ui < MAX_TIMER_COUNT; ui++)
		if(_timers[ui] == timer)
		{
			_timers[ui] = NULL;
			DELETE(timer);
			return TRUE;
		}
	return FALSE;
}

/**
	@Function:		TmrSetInterval
	@Access:		Public
	@Description:
		设置一个定时器的时间间隔。
	@Parameters:
		timer, TimerPtr, OUT
			指向定时器对象的指针。
		interval, uint32, IN
			新的时间间隔。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
TmrSetInterval(	OUT TimerPtr timer,
				IN uint32 interval)
{
	if(timer == NULL || interval == 0)
		return FALSE;
	timer->interval = interval;
	return TRUE;
}

/**
	@Function:		TmrStart
	@Access:		Public
	@Description:
		开始一个定时器。
	@Parameters:
		timer, TimerPtr, OUT
			指向定时器对象的指针。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
TmrStart(OUT TimerPtr timer)
{
	if(timer == NULL)
		return FALSE;
	timer->enabled = TRUE;
	return TRUE;
}

/**
	@Function:		TmrStop
	@Access:		Public
	@Description:
		停止一个定时器。
	@Parameters:
		timer, TimerPtr, OUT
			指向定时器对象的指针。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
TmrStop(OUT TimerPtr timer)
{
	if(timer == NULL)
		return FALSE;
	timer->enabled = FALSE;
	return TRUE;
}

/**
	@Function:		TmrGetCount
	@Access:		Public
	@Description:
		获取定时器数量。
	@Parameters:
	@Return:
		uint32
			定时器数量。
*/
uint32
TmrGetCount(void)
{
	uint32 count = 0;
	uint32 ui;
	for(ui = 0; ui < MAX_TIMER_COUNT; ui++)
		if(_timers[ui] != NULL)
			count++;
	return count;
}

/**
	@Function:		TmrClear
	@Access:		Public
	@Description:
		清除所有定时器。
	@Parameters:
	@Return:
*/
void
TmrClear(void)
{
	uint32 ui;
	for(ui = 0; ui < MAX_TIMER_COUNT; ui++)
		if(_timers[ui] != NULL)
		{
			DELETE(_timers[ui]);
			_timers[ui] = NULL;
		}
}

/**
	@Function:		TmrSetEvent
	@Access:		Public
	@Description:
		设置一个定时器的事件函数。
	@Parameters:
		timer, TimerPtr, OUT
			指向定时器对象的指针。
		event, TimerEvent, IN
			新的时间函数。
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
TmrSetEvent(OUT TimerPtr timer,
				IN TimerEvent event)
{
	if(timer == NULL || event == NULL)
		return FALSE;
	timer->event = event;
	return TRUE;
}
