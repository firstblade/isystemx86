/**
	@File:			syscall.h
	@Author:		Ihsoh
	@Date:			2015-10-06
	@Description:
*/

#ifndef	_SYSCALL_SYSCALL_H_
#define	_SYSCALL_SYSCALL_H_

#define	SCALL_SCREEN		0
#define	SCALL_KEYBOARD		1
#define	SCALL_FS			2
#define	SCALL_SYSTEM		3
#define	SCALL_MOUSE			4
#define SCALL_GUI			5

// ============================== File System ==============================
#define	SCALL_FOPEN			0
#define	SCALL_FCLOSE		1
#define	SCALL_FWRITE		2
#define	SCALL_FREAD			3
#define	SCALL_FAPPEND		4
#define	SCALL_FRESET		5
#define	SCALL_EXISTS_DF		6
#define	SCALL_CREATE_DIR	7
#define	SCALL_CREATE_FILE	8
#define	SCALL_DEL_DIR		9
#define	SCALL_DEL_FILE		10
#define	SCALL_DEL_DIRS		11
#define	SCALL_RENAME_DIR	12
#define	SCALL_RENAME_FILE	13
#define	SCALL_FLEN			14
#define	SCALL_FCREATE_DT	15
#define	SCALL_FCHANGE_DT	16
#define	SCALL_DF_COUNT		17
#define	SCALL_DF			18
#define	SCALL_FIX_PATH		19
#define	SCALL_LOCK_FS		20
#define	SCALL_UNLOCK_FS		21
#define	SCALL_FS_LOCK_STATE	22
#define	SCALL_FEOF			23

// ============================== GUI ==============================
#define	SCALL_GUI_IS_VALID				0x00000001
#define	SCALL_GUI_CREATE_WINDOW			0x00000002
#define	SCALL_GUI_CLOSE_WINDOW			0x00000003
#define	SCALL_GUI_SET_WINDOW_STATE		0x00000004
#define	SCALL_GUI_GET_WINDOW_STATE		0x00000005
#define	SCALL_GUI_SET_WINDOW_POSITION	0x00000006
#define	SCALL_GUI_GET_WINDOW_POSITION	0x00000007
#define	SCALL_GUI_SET_WINDOW_SIZE		0x00000008
#define	SCALL_GUI_GET_WINDOW_SIZE		0x00000009
#define	SCALL_GUI_SET_WINDOW_TITLE		0x0000000a
#define	SCALL_GUI_GET_WINDOW_TITLE		0x0000000b
#define	SCALL_GUI_HAS_KEY				0x0000000c
#define	SCALL_GUI_GET_KEY				0x0000000d
#define	SCALL_GUI_GET_MOUSE				0x0000000e
#define	SCALL_GUI_FOCUSED				0x0000000f
#define	SCALL_GUI_FOCUS					0x00000010
#define	SCALL_GUI_SET_PIXEL				0x00000011
#define	SCALL_GUI_GET_PIXEL				0x00000012
#define	SCALL_GUI_DRAW_RECT				0x00000013
#define	SCALL_GUI_DRAW_IMAGE			0x00000014
#define	SCALL_GUI_DRAW_TEXT				0x00000015
#define	SCALL_GUI_DRAW_LINE				0x00000016
#define	SCALL_GUI_GET_MESSAGE			0x00000017
#define	SCALL_GUI_SET_TEXT				0x00000018
#define	SCALL_GUI_GET_TEXT				0x00000019
#define	SCALL_GUI_UPDATE				0x0000001a
#define	SCALL_GUI_RENDER_TEXT_BUFFER	0x0000001b
#define	SCALL_GUI_FREE_MSGDATA			0x0000001c
#define	SCALL_GUI_ENABLE_CONTROL		0x0000001d
#define	SCALL_GUI_DISABLE_CONTROL		0x0000001e

#define	SCALL_GUI_NEW_BUTTON			((CONTROL_BUTTON << 8) | 0x00000001)

#define	SCALL_GUI_NEW_LABEL				((CONTROL_LABEL << 8) | 0x00000001)

#define	SCALL_GUI_NEW_LIST				((CONTROL_LIST << 8) | 0x00000001)
#define	SCALL_GUI_SET_LIST_TEXT			((CONTROL_LIST << 8) | 0x00000002)
#define	SCALL_GUI_ENABLE_LIST_ITEM		((CONTROL_LIST << 8) | 0x00000003)
#define	SCALL_GUI_DISABLE_LIST_ITEM		((CONTROL_LIST << 8) | 0x00000004)

// ============================== Keyboard ==============================
#define	SCALL_GET_CHAR			0
#define	SCALL_GET_STR_N			1
#define	SCALL_GET_SHIFT			2
#define	SCALL_GET_CONTROL		3
#define	SCALL_GET_ALT			4
#define	SCALL_GET_KEY_STATUS	5
#define	SCALL_HAS_KEY			6

// ============================== Mouse ==============================
#define	SCALL_GET_MPOSITION		0
#define	SCALL_GET_MLBSTATE		1
#define	SCALL_GET_MRBSTATE		2

// ============================== Screen ==============================
#define	SCALL_PRINT_CHAR			0
#define	SCALL_PRINT_CHAR_P			1
#define	SCALL_PRINT_STR				2
#define	SCALL_PRINT_STR_P			3
#define	SCALL_CLEAR_SCREEN			4
#define	SCALL_SET_CURSOR			5
#define	SCALL_GET_CURSOR			6
#define	SCALL_VESA_IS_VALID			7
#define	SCALL_GET_SCREEN_SIZE		8
#define	SCALL_SET_SCREEN_PIXEL		9
#define	SCALL_GET_SCREEN_PIXEL		10
#define	SCALL_DRAW_SCREEN_IMAGE		11
#define	SCALL_GET_TEXT_SCREEN_SIZE	12
#define	SCALL_LOCK_CURSOR			13
#define	SCALL_UNLOCK_CURSOR			14
// NOT USED							15
// NOT USED							16
#define	SCALL_SET_TARGET_SCREEN		17

#define	SCALL_CREATE_WINDOW			18
#define	SCALL_DESTROY_WINDOW		19
#define	SCALL_SHOW_WINDOW			20
#define	SCALL_HIDE_WINDOW			21
#define	SCALL_WINDOW_GET_KEY		22
#define	SCALL_DRAW_WINDOW			23

#define	SCALL_PRINT_ERR_CHAR		24
#define	SCALL_PRINT_ERR_CHAR_P		25
#define	SCALL_PRINT_ERR_STR			26
#define	SCALL_PRINT_ERR_STR_P		27

#define	SCALL_FLUSH_SCREEN 			28

#define	SCALL_WRITE_CONSOLE_BUFFER	29
#define	SCALL_RENDER_TEXT_BUFFER	30

// ============================== System ==============================
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
#define	SCALL_EXEC				14
#define	SCALL_WAIT				15
#define	SCALL_MEMORY_BLOCK_SIZE	16
#define	SCALL_DISPATCH_TICK		17

#endif