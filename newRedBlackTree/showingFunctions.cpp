#include "redBlackTree.h"

std::ostream& operator<<(std::ostream& os, const nodeptr& n)
{
	if (n->data == nil)
	{
		os << "[NIL]";
	}
	else
	{
		os << n->data << '[';
		if (n->color == Node::eColor::RED)
		{
			os << "R]";
		}
		else
		{
			os << "B]";
		}
	}
	return os;
}



void RedBlackTree::ShowTree() const
{
	if (Root != nullptr)
	{
		std::cout << "���� �����Դϴ�.\n";
		ShowAll(Root);
		std::cout << "�� ���� " << nodecnt << "�� �Դϴ�.\n";
	}
	else
	{
		std::cout << "Ʈ���� �����Ͱ� �������� �ʽ��ϴ�.\n";
	}
}

void RedBlackTree::pre_show(const nodeptr& no) const
{
	if (no->left != NIL)
	{
		pre_show(no->left);
	}

	if (no->right != NIL)
	{
		pre_show(no->right);
	}

	show_node(no);

}

void RedBlackTree::Pre_Show() const
{
	if (Root != nullptr)
	{
		pre_show(Root);
	}
	else
	{
		std::cout << "Ʈ���� �����Ͱ� �������� �ʽ��ϴ�.\n";
	}
}
void RedBlackTree::showRoot() const
{
	if (Root != nullptr)
	{
		std::cout << Root << std::endl;
	}

	else
	{
		std::cout << "Ʈ���� ������ϴ�.\n";
	}
}
void RedBlackTree::showMid() const
{
	if (Root != nullptr)
	{
		show_mid(Root);
	}

	else
	{
		std::cout << "Ʈ���� �����Ͱ� �������� �ʽ��ϴ�.\n";
	}

}
void RedBlackTree::show_mid(const nodeptr& no) const
{
	show_node(no);


	if (no->left != NIL)
	{
		show_mid(no->left);
	}


	if (no->right != NIL)
	{
		show_mid(no->right);
	}


}