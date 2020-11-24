#include <stdio.h>

int main()
{

	int a;
	int b;

	int c;

	a = 3;
	b = 5;
	c = a * b;

	printf("c code : %d\n", c);

	__asm
	{
		mov eax, 3
		mov ebx, 5
		mul ebx
		mov dword ptr[c], eax

	}

	printf("asm code : %d\n", c);


	return 0;


}