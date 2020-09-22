#include <vector>
#include <string>
#include <iostream>
#include "redBlackTree.h"
int  main()
{
	using namespace std;
	RedBlackTree tr;

	for (int i = 1; i < 3000; i++)
	{
		tr.Insert(i);
	}

	tr.showMid();

	tr.Pre_Show();

	tr.Terminate();
	

}