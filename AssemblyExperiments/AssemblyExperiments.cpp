#include <stdio.h>
//#include <Windows.h>
//#include <conio.h>



int main()
{
	

	int a;
	int b;

	int c;

	a = 1;
	b = 2;
	c = a + b;

	printf("c code : %d\n", c);

	__asm
	{
		mov eax,1
		mov edx,2
		add eax,edx
		mov dword ptr[c],eax

	}

	printf("asm code : %d\n", c);
	//_getch();

	return 0;


}