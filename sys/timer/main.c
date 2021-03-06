#include <ilib/ilib.h>

static
void
delay(void);

int
main(	IN int argc,
		IN char * argv[])
{
	for(;;)
	{
		dispatch_tick();
		delay();
	}
	return 0;
}

static
void
delay(void)
{
	uint32 ui;
	for(ui = 0; ui < 0x00000001; ui++)
		asm volatile("pause");
}
