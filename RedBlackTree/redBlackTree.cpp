#include <algorithm>
#include <iterator>
#include <vector>
#include "redBlackTree.h"

typedef Node* nodeptr;
//int Node::nodecnt = 0;
std::ostream& operator<<(std::ostream& os,const nodeptr& n)
{
	if (n->data==nil)
		os << "[NIL]";
	else
	{
		os << n->data << '[';
		if (n->color == Node::Color::RED)os << "R]";
		else os << "B]";
	}
	return os;
}

const nodeptr& Node::getUncle()const
{
	if (this->parent == this->getGrandParent()->right)
		return this->getGrandParent()->left;

	else
		return this->getGrandParent()->right;
}
nodeptr& Node::getUncle()
{
	if (this->parent == this->getGrandParent()->right)
		return this->getGrandParent()->left;

	else
		return this->getGrandParent()->right;
}
nodeptr& Node::getBrother()
{
	if (this == this->parent->left)
		return this->parent->right;

	else
		return this->parent->left;
}
const nodeptr& Node::getBrother()const
{

	if (this == this->parent->left)
		return this->parent->right;

	else
		return this->parent->left;
}
bool Node::checkNode()const
{
	if (this->color == Node::Color::RED)
	{
		if (this->right->color == Node::Color::RED
			|| this->left->color == Node::Color::RED)
			return false;
		
	}
	return true;

}

RedBlackTree::RedBlackTree()
{
	Root = justInserted = nullptr;
	nodecnt = 0;
	redblackCnt = 0;
	NIL = new Node(NIL,nil, Node::Color::BLACK, NIL, NIL);
}
//nodeptr RedBlackTree::NIL = new Node(NIL, -1, Node::Color::BLACK,NIL,NIL);

void RedBlackTree::Insert(Data d)
{
	Root = InsertNode(Root,NIL,d);
	
	checkTree(justInserted);
	
}

nodeptr RedBlackTree::InsertNode(nodeptr& n, const nodeptr& parent, Data d)
{
	if (n == NIL)
	{
		RedBlackTree::justInserted = new Node(parent, d, Node::Color::RED,NIL,NIL);
		nodecnt++;
		return justInserted;
	}
	else if (n == nullptr)
	{
		RedBlackTree::justInserted = new Node(parent, d, Node::Color::BLACK, NIL, NIL);
		nodecnt++;
		return justInserted;
	}
		
	else if (n->data > d)
		n->left = InsertNode(n->left, n, d);
	

	else if (n->data < d)
		n->right = InsertNode(n->right, n, d);
	
	return n;

}
nodeptr& Node::ParentIntention()
{
	if (this == this->getParent()->right)
		return this->getParent()->right;

	else
		return this->getParent()->left;
}
nodeptr& RedBlackTree::Search(nodeptr& n, Data d)
{
	if (n == NIL || n->data == d)
		return n;

	else if (n->data > d)
		return Search(n->left, d);


	else
		return Search(n->right, d);

}
void RedBlackTree::Remove(Data d)
{
	nodeptr target = Search(Root, d);

	if (target != NIL)--nodecnt;
	else return;

	 if (target == Root)
	{
		if (Root->left != NIL && Root->right != NIL)
			RemoveNode(target);

		else if (Root->left == NIL && Root->right == NIL)
		{
				delete Root;	
				Root = nullptr;
		}

		else if (Root->left != NIL)
		{
			nodeptr tmp = Root;
			nodeptr* new_Root = &Root;
			*new_Root = Root->left;
			Root->parent = NIL;
			Root->color = Node::Color::BLACK;
			delete tmp;
		}
		else
		{
			nodeptr tmp = Root;
			nodeptr* new_Root = &Root;
			*new_Root = Root->right;
			Root->parent = NIL;
			Root->color = Node::Color::BLACK;
			delete tmp;
			
		}
	}

	else
	{
		RemoveNode(target);
	}
}
nodeptr RedBlackTree::whichOne(nodeptr& n)
{
	nodeptr tmp = n->right;
	while (tmp->left != NIL)
		tmp = tmp->left;

	n->data = tmp->data;

	return tmp;
}

void RedBlackTree::RemoveNode(nodeptr& no)
{
	nodeptr x;
	if (no->right == NIL &&	no->left == NIL)

	{	
		no->ParentIntention() = NIL;
		x = NIL;
		//std::cout << "이쪽?\n";
	}

	else if (no->right != NIL &&
		no->left == NIL)
	{
		x = no->right;
		no->ParentIntention() = x;
		x->parent= no->parent;
		
	}
	else if (no->right == NIL &&
		no->left != NIL)
	{
		x = no->left;
		no->ParentIntention() = x;
		x->parent = no->parent;
	}

	else
	{
	//	std::cout << no << " 대신 ";
		//std::cout << no->data << "대신 ,";
		nodeptr newTarget = whichOne(no);
	//	std::cout << no->data << "를 삭제합니다.\n";
		RemoveNode(newTarget);
		return;
	}


	if (no->color == Node::Color::BLACK)
	{
		if (x->color == Node::Color::RED)
		{
			x->color = Node::Color::BLACK;
		}
		else
		{
		//	std::cout << "여기까지 오나?\n";
			repairTree(no->parent,x);
		}
	}
		delete  no;
}

void RedBlackTree::repairTree(nodeptr& p, nodeptr& x)
{
	std::cout << x << "를 대상으로 수선\n";
	nodeptr s;
	if (x != NIL)s = x->getBrother();
	else
		s = (x == p->right) ? p->left : p->right;
	
	//std::cout << "여기까진 돼?\n";
	nodeptr l = s->left;
	
	nodeptr r = s->right;
	Node::Color s_col = s->color;
	Node::Color p_col = p->color;
	Node::Color l_col = l->color;
	Node::Color r_col = r->color;
	using std::cout;
	using std::endl;

	/*std::cout << "형제 노드: " << s << std::endl;
	std::cout << "왼쪽 자식 : " << l << std::endl;
	std::cout << "오른쪽 자식 : " << r << std::endl;
	*/
	if (p_col == Node::Color::RED 
		&& s_col == Node::Color::BLACK 
		&&l_col == Node::Color::BLACK 
		&& r_col == Node::Color::BLACK)
	{
		//cout << "=====case 1======\n";
		delete_case1(p, s);
	}
	else if (x == p->left
		&& s_col == Node::Color::BLACK
		&& r_col == Node::Color::RED)
	{
		//cout << "=====case 2======\n";
		delete_case2(p, s, r);

	}
	else if (x == p->right
		&& s_col == Node::Color::BLACK
		&& l_col == Node::Color::RED)
	{
	//	cout << "=====case 2======\n";
		delete_case2(p, s, l);
	}
	else if (x == p->left
		&& s_col == Node::Color::BLACK
		&& l_col == Node::Color::RED
		&& r_col == Node::Color::BLACK)
	{
	//	cout << "=====case 3======\n";
		delete_case3(p, s, l);
	}
	else if (x == p->right && s_col == Node::Color::BLACK
		&& l_col == Node::Color::BLACK
		&& r_col == Node::Color::RED)
	{
	//	cout << "=====case 3======\n";
		delete_case3(p, s, r);
	}
	else if (p_col == Node::Color::BLACK
		&& s_col == Node::Color::BLACK
		&& l_col == Node::Color::BLACK
		&& r_col == Node::Color::BLACK)
	{
	//	cout << "=====case 4======\n";
		delete_case4(p, s);
	}
	else if (s == p->right
		&& p_col == Node::Color::BLACK
		&& s_col == Node::Color::RED
		&& l_col == Node::Color::BLACK
		&& r_col == Node::Color::BLACK)
	{
	//	cout << "=====case 5======\n";
		delete_case5(p, s, r);
	}

	else if (s == p->left
		&& p_col == Node::Color::BLACK
		&& s_col == Node::Color::RED
		&& l_col == Node::Color::BLACK
		&& r_col == Node::Color::BLACK)
	{
	//	cout << "=====case 5======\n";
		delete_case5(p, s, l);
	}
	
}
const nodeptr& Node::ParentIntention()const
{
	if (this == this->getParent()->right)
		return this->getParent()->right;

	else
		return this->getParent()->left;
}
void RedBlackTree::Clear()
{
	if(Root!=nullptr)
	{ 
	clearNode(Root);
	nodecnt = 0;
	Root = nullptr;
	}
}
void RedBlackTree::clearNode(nodeptr& n)
{
	if (n->left != NIL)
		clearNode(n->left);

	if (n->right != NIL)
		clearNode(n->right);

	delete n;
}
void RedBlackTree::ShowAll(const nodeptr& n)const
{
	if (n->left !=NIL)
		ShowAll(n->left);
	show_node(n);
	if (n->right != NIL)
		ShowAll(n->right);

}
void RedBlackTree::ShowTree()const
{
	if (Root != nullptr)
	{
		std::cout << "전위 형식입니다.\n";
		ShowAll(Root);
		std::cout << "총 노드는 " << nodecnt << "개 입니다.\n";
	}
	else
		std::cout << "트리에 데이터가 존재하지 않습니다.\n";
}

void RedBlackTree::checkTree(nodeptr& x)
{
	if (x->parent->color == Node::Color::RED)
	{
		nodeptr uncle = x->getUncle();
		nodeptr grandP = x->getGrandparent();
		if (uncle->color == Node::Color::RED)
			insert_case1(x);

		else
		{
			if (x == x->parent->left && x->parent == grandP->left)
				insert_case2_2(x);

			else if (x== x->parent->right && x->parent == grandP->right)
				insert_case2_2(x);

			else
				insert_case2_1(x);
		}
	}
	
}
void RedBlackTree::insert_case1(nodeptr& n)
{
	nodeptr uncle = n->getUncle();
	nodeptr grandP = n->getGrandParent();

	uncle->color = n->parent->color = Node::Color::BLACK;
	if(grandP!=Root)grandP->color = Node::Color::RED;
	if (grandP->parent->color == Node::Color::RED)checkTree(grandP);
	
}
void RedBlackTree::insert_case2_1(nodeptr& n)
{
	nodeptr par = n->parent;
	rotateLeft(n);
	rotateRight(par,par->parent);
}
void RedBlackTree::insert_case2_2(nodeptr& n)
{
	rotateRight(n,n->parent);
}

void RedBlackTree::rotateLeft(nodeptr& no)
{
	nodeptr tmp = (no == no->parent->right) ? no->left : no->right;
	nodeptr grandP = no->getGrandParent();
	nodeptr par = no->parent;
	if (no == no->parent->right)
	{
		par->right = tmp;
		no->left = par;
	}
	else
	{
		par->left = tmp;
		no->right = par;
	}
	if(tmp!=NIL)tmp->parent = par;
	no->parent = grandP;
	par->parent = no;
}
void RedBlackTree::rotateRight(nodeptr& x,nodeptr& p)
{

	nodeptr y;
	//if (x == NIL)std::cout << "이런 x가 " << x << "라니\n";
	if (x != NIL)
		y = x->getBrother();

	else
		y = (x == p->right) ? p->left : p->right;

	nodeptr grandP = p->parent;
	if (x==p->left)
	{
		p->right = grandP;
		grandP->left = y;
	}
	else
	{
		p->left = grandP;
		grandP->right = y;
	}

	if(y!=NIL)
		y->parent = grandP;
	
	p->parent =
		grandP->parent;

	if (grandP != Root)
		grandP->ParentIntention() = p;

	else
	{
		nodeptr* root = &Root;
		*root = p;
	}
	grandP->parent = p;


	p->color = Node::Color::BLACK;
	grandP->color = Node::Color::RED;
}

void RedBlackTree::delete_case1(nodeptr& p, nodeptr& s)
{
	std::cout << "=====case 1======\n";
	p->color = Node::Color::BLACK;
	s->color = Node::Color::RED;
}
void RedBlackTree::delete_case2(nodeptr& p, nodeptr& s, nodeptr& a)
{
	std::cout << "=====case 2======\n";
	Node::Color p_col = p->color;
	rotateRight(a,s);
	s->color = p_col;
	p->color = Node::Color::BLACK;
	if (s == Root)
		s->color = Node::Color::BLACK;

	a->color = Node::Color::BLACK;
}
void RedBlackTree::delete_case3(nodeptr& p, nodeptr& s, nodeptr& a)
{
	std::cout << "=====case 3======\n";
	rotateLeft(a);
	a->color = Node::Color::BLACK;
	s->color = Node::Color::RED;
	delete_case2(p, a, s);
}
void RedBlackTree::delete_case4(nodeptr& p, nodeptr& s)
{
	std::cout << "=====case 4======\n";
	//std::cout << p << std::endl;
	s->color = Node::Color::RED;
	
	if (p != Root)
	{
		repairTree(p->parent, p);
	}

	
}
void RedBlackTree::delete_case5(nodeptr& p, nodeptr& s, nodeptr& a)
{
	std::cout << "=====case 5======\n";
	nodeptr	sib = (a == s->right) ? s->left : s->right;


	rotateRight(a,s);
	
	if (sib->right->color == Node::Color::BLACK &&
		sib->left->color == Node::Color::BLACK)
		delete_case1(sib->parent, sib);

	else if (sib == sib->parent->right && sib->right->color == Node::Color::RED)
		delete_case2(p, sib, sib->right);

	else if (sib == sib->parent->left && sib->left->color == Node::Color::RED)
		delete_case2(p, sib, sib->left);

	else if (sib == sib->parent->right
		&& sib->right->color == Node::Color::BLACK
		&& sib->left->color == Node::Color::RED)
		delete_case3(p, sib, sib->left);

	else if (sib == sib->parent->left
		&& sib->left->color == Node::Color::BLACK
		&& sib->right->color == Node::Color::RED)
		delete_case3(p, sib, sib->right);
}
void RedBlackTree::Terminate()
{
	if(Root!=nullptr)
	Clear();

}
void RedBlackTree::pre_show(const nodeptr& no)const
{
	if (no->left != NIL)
		pre_show(no->left);
	if (no->right != NIL)
		pre_show(no->right);
	show_node(no);

}
void RedBlackTree::Pre_Show()const
{
	if (Root != nullptr)
		pre_show(Root);
	else
		std::cout << "트리에 데이터가 존재하지 않습니다.\n";
}
void RedBlackTree::showRoot()const
{
	if (Root != nullptr)
		std::cout << Root << std::endl;

	else
		std::cout << "트리가 비었습니다.\n";
}
void RedBlackTree::showMid()const
{
	if (Root != nullptr)
		show_mid(Root);

	else
		std::cout << "트리에 데이터가 존재하지 않습니다.\n";
}
void RedBlackTree::show_mid(const nodeptr& no)const
{
	show_node(no);
	if (no->left != NIL)
		show_mid(no->left);
	if (no->right != NIL)
		show_mid(no->right);
	

}
void RedBlackTree::checkRedBlack()
{
	checkredblack(Root);
	std::cout << redblackCnt << "개 가 조건에 불일치\n";
}
void RedBlackTree::checkredblack(const nodeptr& node)
{
	if (node->color == Node::Color::RED)
	{
		if (node->right->color == Node::Color::RED
			|| node->left->color == Node::Color::RED)
			redblackCnt++;
	}
	if (node->left != NIL)
		checkredblack(node->left);

	if (node->right != NIL)
		checkredblack(node->right);
	
	
}
bool RedBlackTree::checkBlackCnt()const
{
	nodevec nvec;
	checkblackcount(Root, nvec);
	std::cout << "리프 노드는 " << nvec.size() << "개 입니다.\n";
	//nodevec::iterator it = nvec.begin();
	int cnt = howManyBlacks(nvec[0]);
	std::cout << cnt << "개입니다.\n";
	for (unsigned int i = 1; i < nvec.size(); i++)
	{
		if (cnt != howManyBlacks(nvec[i]))
			return false;
	}
	return true;

}
void RedBlackTree::checkblackcount(const nodeptr& no, nodevec& vec)const
{
	if (no->left == NIL && no->right == NIL&& no!=NIL)
		vec.push_back(no);
	else
	{
		if (no->left != NIL)
			checkblackcount(no->left, vec);

		if (no->right != NIL)
			checkblackcount(no->right, vec);
	}

}
int RedBlackTree::howManyBlacks(const nodeptr& no)const
{
	int cnt = 0; 
	nodeptr tmp = no;
	while (tmp!=NIL)
	{
		if (tmp->color == Node::Color::BLACK)
			++cnt;
		tmp = tmp->parent;

	}
	return cnt;
}

void RedBlackTree::findNode(const Data d)
{
	using std::cout;
	using std::endl;
	if (Root == nullptr)
	{
		cout << "트리가 비어있습니다.\n";
		return;
	}
	nodeptr target = Search(Root, d);
	if (target == NIL)
		std::cout << "값이 존재하지 않습니다.\n";

	else
	{	
		cout << "\t\t\t" << target->parent << endl;
		cout << "\t\t\t" << target << endl;
		cout << "\t" << target->left;
		cout << "\t\t\t" << target->right << endl;
	}
}