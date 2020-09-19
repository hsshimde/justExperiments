#include <vector>
#include <string>
#include <iostream>
#include "redBlackTree.h"
int  main()
{
	using namespace std;
	RedBlackTree tr;

	for (int i = 1; i <= 10; i++)
		tr.Insert(i);
		

	tr.showMid();

	Data tmp;
	while (cin>>tmp&&tmp!=9999)
	{
		tr.Remove(tmp);
		tr.ShowTree();
	}

	tr.Terminate();
	

}