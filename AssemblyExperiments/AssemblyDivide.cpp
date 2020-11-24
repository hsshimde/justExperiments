#include <stdio.h>
#include <Windows.h>	
#include <conio.h>

int main()
{

	int a;
	int b;

	int c;

	a = 15;
	b = 5;
	c = a / b;

	printf("c code : %d\n", c);

	__asm
	{
		xor edx, edx
		mov eax, 15


		move ebx, 5
		div  ebx 
		mov dword ptr[c], ebx
	}

	printf("asm code : %d\n", c);


	return 0;


}