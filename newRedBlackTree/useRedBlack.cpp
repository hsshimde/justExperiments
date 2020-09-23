//#include <iostream>
//#include <vector>
//#include <string>
//#include "redBlackTree.h"
//enum class Menu
//{
//	INSERT,REMOVE,SHOW,CLEAR,PRESHOW,SHOWROOT,SHOWMID,CHECK,FIND,END
//};
//
// std::vector<std::string> arr= { "Insert","Remove","Show","Clear","Pre show","show root","show mid","check red black tree","Find the node","End" };
//Menu menuChoice();
//void showNode(const nodeptr& node) { std::cout << node << std::endl; }
//
//int main()
//{
//	typedef RedBlackTree tree;
//	typedef Node* nodeptr;
//	tree tr;
//	for (int i = 0;i<100; i++)
//		tr.Insert(i);
//	using namespace std;
//	Data tmp;
//	Menu menu;
//	while (1)
//	{
//		switch (menu=menuChoice())
//		{
//		case Menu::INSERT:
//			cout << "입력할 값을 입력하세요:";
//			cin >> tmp;
//			tr.Insert(tmp);
//			break;
//
//		case Menu::REMOVE:
//			cout << "삭제할 값을 입력하세요:";
//			cin >> tmp;
//			tr.Remove(tmp);
//			break;
//
//		case Menu::SHOW:
//			tr.ShowTree();
//			break;
//
//		case Menu::CLEAR:
//			tr.Clear();
//			break;
//
//		case Menu::PRESHOW:
//			tr.Pre_Show();
//			break;
//
//		case Menu::SHOWROOT:
//			tr.showRoot();
//			break;
//
//		case Menu::SHOWMID:
//			tr.showMid();
//			break;
//
//		case Menu::CHECK:
//			tr.checkRedBlack();
//			if (!tr.checkBlackCnt())
//				cout << "각 리프까지의 블랙노드의 수가 동일하지 않습니다.\n";
//			else
//				cout << "각 리프까지 블랙노드의 수가 동일!~~\n";
//
//			break;
//
//		case Menu::FIND:
//			cout << "찾을 값을 입력하세요:";
//			cin >> tmp;
//			tr.findNode(tmp);
//			break;
//
//		}
//		if (menu == Menu::END)
//			break;
//	}
//	cout << "프로그램을 종료합니다.\n";
//
//	//tr.Terminate();
//
//	return 0;
//		
//}
//Menu menuChoice()
//{
//	using std::cout;
//	using std::cin;
//	using std::endl;
//	int ch;
//	int tmp;
//	do
//	{
//		for (int i = 0; (unsigned int)i < arr.size(); i++)
//			cout <<'['<<i+1<<']' <<arr[i] << "  ";
//
//		cin >> tmp;
//		ch = tmp - 1;
//
//
//	} while ((Menu)ch<Menu::INSERT || (Menu)ch>Menu::END);
//
//		return (Menu)ch;
//
//}