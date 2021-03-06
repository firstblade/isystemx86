#ifndef	_BMP_H_
#define	_BMP_H_

#include "types.h"
#include <dslib/list.h>
#include <ilib/ilib.h>

#define	BI_RGB			0
#define	BI_BITFIELDS	3

typedef	struct
{
	FILE *		imgfile_ptr;
	uint8 *		data_ptr;
	uint8 *		pixel_array_ptr;
	int32		width, height, color_depth, compression, palette_size;
	int32		red_mask, green_mask, blue_mask;
	int32		red_shift, green_shift, blue_shift;
	DSLListPtr	palette_r;
	DSLListPtr	palette_g;
	DSLListPtr	palette_b;
	int32		row_size;
} IMGLBMP, * IMGLBMPPtr;

IMGLBMPPtr
imgl_bmp_create(IN CASCTEXT file);

BOOL
imgl_bmp_destroy(IN IMGLBMPPtr bmpobj);

int32
imgl_bmp_get_width(IN IMGLBMPPtr bmpobj);

int32
imgl_bmp_get_height(IN IMGLBMPPtr bmpobj);

uint32
imgl_bmp_get_color(	IN IMGLBMPPtr bmpobj,
					IN int32 x, 
					IN int32 y);

#endif
