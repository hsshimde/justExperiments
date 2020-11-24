#include <stdio.h>

int main()
{
	
	int a;
	int b;

	int c;

	a = 3;
	b = 1;
	c = a - b;

	printf("c code : %d\n", c);

	__asm
	{
		mov eax, 3
		mov edx, 1
		sub eax, edx
		mov dword ptr[c], eax

	}

	printf("asm code : %d\n", c);
	

	return 0;


}