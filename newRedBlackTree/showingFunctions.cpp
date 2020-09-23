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
		std::cout << "전위 형식입니다.\n";
		ShowAll(Root);
		std::cout << "총 노드는 " << nodecnt << "개 입니다.\n";
	}
	else
	{
		std::cout << "트리에 데이터가 존재하지 않습니다.\n";
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
		std::cout << "트리에 데이터가 존재하지 않습니다.\n";
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
		std::cout << "트리가 비었습니다.\n";
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
		std::cout << "트리에 데이터가 존재하지 않습니다.\n";
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