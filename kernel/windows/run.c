/**
	@File:			run.c
	@Author:		Ihsoh
	@Date:			2015-12-18
	@Description:
		运行窗体。
*/

#include "run.h"
#include "../types.h"
#include "../memory.h"
#include "../window.h"
#include "../enfont.h"
#include "../console.h"
#include "../vesa.h"

#include "../windows/taskbar.h"

#include "../window/control.h"
#include "../window/button.h"
#include "../window/edit.h"

#define	_TITLE		"Run"

#define	_COLUMN		40

#define	_WIDTH		(10 + ENFONT_WIDTH * _COLUMN + 10)
#define	_HEIGHT		70

static WindowPtr _window;
static EditPtr _edt_cmd;
static ButtonPtr _btn_run;

/**
	@Function:		WinRunInit
	@Access:		Public
	@Description:
		初始化运行窗体。
	@Parameters:
	@Return:
*/
void
WinRunInit(void)
{
	_window = NULL;
	_edt_cmd = NULL;
	_btn_run = NULL;
}

/**
	@Function:		_WinRunExecuteCommand
	@Access:		Private
	@Description:
		运行文本框中的命令。
	@Parameters:
	@Return:
*/
static
void
_WinRunExecuteCommand(void)
{
	ASCCHAR cmd[1024];
	if(CtrlEditGetText(_edt_cmd, cmd, sizeof(cmd)))
		ConExecuteCommand(cmd);
	_window->state = WINDOW_STATE_HIDDEN;
}

/**
	@Function:		_WinRunControlEvent
	@Access:		Private
	@Description:
		控件的事件函数。
	@Parameters:
		id, uint32, IN
			控件ID。
		type, uint32, IN
			事件类型。
		param, void *, IN
			事件附带的参数。
	@Return:
*/
static
void
_WinRunControlEvent(IN uint32 id,
					IN uint32 type,
					IN void * param)
{
	if(id == _btn_run->id)
	{
		if(type == BUTTON_LBUP)
			_WinRunExecuteCommand();
	}
	else if(id == _edt_cmd->id)
	{
		if(type == EDIT_INPUT)
		{
			uint32 * data = (uint32 *)param;
			if(data[0] == '\n')
				_WinRunExecuteCommand();
		}
	}
}

/**
	@Function:		_WinRunEvent
	@Access:		Private
	@Description:
		窗体的事件函数。
	@Parameters:
		window, struct Window *, IN
			指向窗体对象的指针。
		params, struct WindowEventParams *, IN
			指向窗体事件参数对象的指针。
	@Return:
*/
static
void
_WinRunEvent(	IN struct Window * window,
				IN struct WindowEventParams * params)
{
	BOOL top = ScrGetTopWindow() == window;
	switch(params->event_type)
	{
		case WINDOW_EVENT_WILL_CLOSE:
		{
			_window->state = WINDOW_STATE_HIDDEN;
			break;
		}
		case WINDOW_EVENT_PAINT:
		{
			NMLEDIT(_edt_cmd, &window->workspace, params, TRUE);
			BUTTON(_btn_run, &window->workspace, params, TRUE);
			break;
		}
	}
}

/**
	@Function:		WinRunShow
	@Access:		Public
	@Description:
		显示运行窗体。
	@Parameters:
	@Return:
		BOOL
			返回TRUE则成功，否则失败。
*/
BOOL
WinRunShow(void)
{
	if(_window == NULL)
	{
		_window = ScrCreateWindow(
			_WIDTH, _HEIGHT,
			0xffffffff,
			WINDOW_STYLE_CLOSE | WINDOW_STYLE_MINIMIZE,
			_TITLE,
			_WinRunEvent);
		if(_window == NULL)
			return FALSE;
		_window->x = 0;
		_window->y = VesaGetHeight() - TASKBAR_HEIGHT - _HEIGHT - TITLE_BAR_HEIGHT;
		rect_common_image(&_window->workspace, 0, 0, _WIDTH, _HEIGHT, 0xffffffff);	
		_edt_cmd = NEW(Edit);
		INIT_EDIT(	_edt_cmd,
					10, 10,
					1,
					_COLUMN,
					EDIT_STYLE_SINGLE_LINE,
					_WinRunControlEvent);
		_btn_run = NEW(Button);
		INIT_BUTTON(_btn_run,
					0,
					0,
					"Run",
					_WinRunControlEvent);
		_btn_run->x = _WIDTH - 10 - GET_BUTTON_WIDTH(_btn_run);
		_btn_run->y = _HEIGHT - 10 - GET_BUTTON_HEIGHT(_btn_run);
	}
	if(_window != NULL)
	{
		WinmgrFocusControl(_window, _edt_cmd->id);
		SET_EDIT_TEXT(_edt_cmd, "");
		_window->state = WINDOW_STATE_SHOW;
		ScrSetTopWindow(_window);
	}
	return TRUE;
}
