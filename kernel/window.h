/**
	@File:			window.h
	@Author:		Ihsoh
	@Date:			2014-11-20
	@Description:
*/

#ifndef	_WINDOW_H_
#define	_WINDOW_H_

#include "types.h"
#include "image.h"

#define	TITLE_BAR_HEIGHT		30
#define	TITLE_BAR_BGCOLOR		(__window_title_bar_bgcolor)
#define	TITLE_BAR_BGCOLOR_NT	(__window_title_bar_bgcolor_nt)
#define	WINDOW_BORDER_COLOR		(__window_border_color)
#define	WINDOW_BORDER_COLOR_NT	(__window_border_color_nt)

extern uint32 __window_title_bar_bgcolor;
extern uint32 __window_title_bar_bgcolor_nt;
extern uint32 __window_border_color;
extern uint32 __window_border_color_nt;

#define	WINDOW_STATE_NONE		0
#define	WINDOW_STATE_SHOW		1
#define	WINDOW_STATE_HIDDEN		2
#define	WINDOW_STATE_CLOSED		3

#define	CLOSE_BUTTON_WIDTH		55
#define	CLOSE_BUTTON_HEIGHT		30

#define	HIDDEN_BUTTON_WIDTH		55
#define	HIDDEN_BUTTON_HEIGHT	30

#define	WINDOW_STYLE_NONE				0x00000000
#define	WINDOW_STYLE_CLOSE				0x00000001
#define	WINDOW_STYLE_MINIMIZE			0x00000002
#define	WINDOW_STYLE_MAXIMIZE			0x00000004
#define	WINDOW_STYLE_NO_TITLE			0x00000008
#define	WINDOW_STYLE_NO_WMGR			0x00000010
#define	WINDOW_STYLE_NO_BORDER			0x00000020

#define	WINDOW_EVENT_PAINT			1
#define	WINDOW_EVENT_FOCUS			2
#define	WINDOW_EVENT_UNFOCUS		3
#define	WINDOW_EVENT_WILL_CLOSE		4
#define	WINDOW_EVENT_HIDDEN			5
#define	WINDOW_EVENT_SHOW			6

#define	WINDOW_KEY_BUFFER_SIZE		16

#define	WINDOW_TITLE_SIZE			1024

typedef struct WindowEventParams
{
	uint32					wid;
	int32					event_type;
	int32					mouse_x;
	int32					mouse_y;
	int32					mouse_button;
	struct CommonImage *	screen;
	void *					data;
	struct Window *			window;
} * WindowEventParamsPtr;

typedef void (* WindowEvent)(	struct Window * window,
								struct WindowEventParams * params);

typedef BOOL (* WindowKeyPressCallback)(struct Window * window,
										uint32 key);

typedef struct Window
{
	uint32					id;										// 窗体ID。
	int32					uwid;									// User Window ID。
	int32					x;										// 窗体X坐标。
	int32					y;										// 窗体Y坐标。
	uint32					width;									// 窗体宽度。
	uint32					height;									// 窗体高度。
	ASCCHAR					title[WINDOW_TITLE_SIZE];				// 窗体标题。
	uint32					bgcolor;								// 窗体工作区背景色。
	int32					state;									// 窗体状态。
	uint32					style;									// 窗体样式。
	int32					over_close_button;						// 鼠标是否悬于关闭按钮之上。
	int32					over_hidden_button;						// 鼠标是否悬于隐藏按钮之上。
	WindowEvent				event;									// 窗体的事件函数。
	struct CommonImage		workspace;								// 窗体的工作区的画布。
	struct CommonImage		title_bar;								// 窗体的标题栏的画布。
	uint8					key_buffer[WINDOW_KEY_BUFFER_SIZE];		// 窗体的按键缓冲区。
	uint32					key_count;								// 窗体的按键缓冲区的按键数量。
	WindowKeyPressCallback	cb_key_press;							// 窗体获取焦点并且有按键被按下时，会调用该函数。
																	// 如果该函数返回FALSE，则表示不要把按键添加到key_buffer中。
	BOOL					locked;									// 如果该值为TRUE，则锁住窗体，不把工作区的内容更新到显存。
	int32					old_state;								// 旧的状态。
	BOOL					is_top;									// 指示窗体是否为最顶，该值由WinmgrRenderWindow函数更新。
	uint32					focused_ctrl;							// 当前获得焦点的控件的ID。如果该ID为CONTROL_INVALID_ID，则窗体没有获得焦点的控件。
} * WindowPtr;

extern
BOOL
WinmgrInit(void);

extern
void
WinmgrUninit(void);

extern
BOOL
WinmgrRenderWindow(	IN struct Window * window,
				IN BOOL top);

extern
uint8
WinmgrGetKey(IN struct Window * window);

extern
uint8
WinmgrPeekKey(IN struct Window * window);

#define	WINMGR_HAS_KEY(window)	((window) == NULL ? 0 : (window)->key_count)

extern
void
WinmgrClearKeyBuffer(IN WindowPtr window);

extern
void
WinmgrDispatchEvent(IN WindowPtr window,
					IN int32 type,
					IN void * data);

extern
void
WinmgrFocusControl(	IN WindowPtr window,
					IN uint32 cid);

extern
void
WinmgrUnfocusControl(IN WindowPtr window);

#endif
