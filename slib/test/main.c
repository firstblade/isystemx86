#include <ilib/ilib.h>

int value0 = 0x1996;
int value1 = 0x2015;
int value2 = 0x2333;

int add(int a, int b)
{
	return a + b;
}

int add1(int a, int b)
{
	return add(a, b);
}

int sub(int a, int b)
{
	return a - b;
}

int get_value0(void)
{
	return value0;
}

int get_value1(void)
{
	return value1;
}

void test(void)
{
	printf("test.so: 1 + 2 = %d\n", add1(1, 2));
	void * vptr = malloc(1024);
	if(vptr == NULL)
		printf("test.so: %s\n", "Cannot allocate memory!");
	else
		free(vptr);
}
