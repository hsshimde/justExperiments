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
//			cout << "�Է��� ���� �Է��ϼ���:";
//			cin >> tmp;
//			tr.Insert(tmp);
//			break;
//
//		case Menu::REMOVE:
//			cout << "������ ���� �Է��ϼ���:";
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
//				cout << "�� ���������� ������� ���� �������� �ʽ��ϴ�.\n";
//			else
//				cout << "�� �������� ������� ���� ����!~~\n";
//
//			break;
//
//		case Menu::FIND:
//			cout << "ã�� ���� �Է��ϼ���:";
//			cin >> tmp;
//			tr.findNode(tmp);
//			break;
//
//		}
//		if (menu == Menu::END)
//			break;
//	}
//	cout << "���α׷��� �����մϴ�.\n";
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