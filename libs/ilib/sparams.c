//Filename:		sparams.c
//Author:		Ihsoh
//Date:			2014-8-1
//Descriptor:	System parameters

#include "types.h"
#include "sparams.h"

void system_call(uint func, uint sub_func, struct SParams * sparams)
{
	uint addr = (uint)sparams;
	uint eax = (func << 16) | (sub_func & 0xFFFF);
	asm volatile(
		"movl	%0, %%eax\n\t"
		"movl	%1, %%edx\n\t"
		"int	$0xa0\n\t"
		:
		:"r"(eax), "r"(addr)
		:"eax", "edx"
	);
}
