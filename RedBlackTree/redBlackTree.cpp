#include <algorithm>
#include <iterator>
#include <vector>
#include "redBlackTree.h"




const nodeptr& Node::getUncle() const
{
	if (this->parent == this->getGrandParent()->right)
	{
		return this->getGrandParent()->left;
	}

	else
	{
		return this->getGrandParent()->right;
	}
}

nodeptr& Node::getUncle() 
{
	if (this->parent == this->getGrandParent()->right)
	{
		return this->getGrandParent()->left;
	}

	else
	{
		return this->getGrandParent()->right;
	}
}
nodeptr& Node::getBrother()
{
	if (this == this->parent->left)
	{
		return this->parent->right;
	}

	else
	{
		return this->parent->left;
	}
}
const nodeptr& Node::getBrother() const
{

	if (this == this->parent->left)
	{
		return this->parent->right;
	}

	else
	{
		return this->parent->left;
	}
}
bool Node::checkNode() const
{
	if (this->color == Node::eColor::RED)
	{
		if (this->right->color == Node::eColor::RED
			|| this->left->color == Node::eColor::RED)
		{
			return false;
		}
		
	}
	return true;

}

void Node::swapColor(nodeptr& b) 
{
	Node::eColor tmp = this->color; 
	this->color = b->color;
	b->color = tmp; 
}


RedBlackTree::RedBlackTree()
{
	Root = justInserted = nullptr;
	nodecnt = 0;
	redblackCnt = 0;
	NIL = new Node(NIL,nil, Node::eColor::BLACK, NIL, NIL);
}
//nodeptr RedBlackTree::NIL = new Node(NIL, -1, Node::eColor::BLACK,NIL,NIL);

void RedBlackTree::Insert(Data d)
{
	Root = InsertNode(Root,NIL,d);
	
	checkTree(justInserted);
	
}

nodeptr RedBlackTree::InsertNode(nodeptr& n, const nodeptr& parent, Data d)
{
	if (n == NIL)
	{
		RedBlackTree::justInserted = new Node(parent, d, Node::eColor::RED,NIL,NIL);
		nodecnt++;
		return justInserted;
	}
	else if (n == nullptr)
	{
		RedBlackTree::justInserted = new Node(parent, d, Node::eColor::BLACK, NIL, NIL);
		nodecnt++;
		return justInserted;
	}
		
	else if (n->data > d)
	{
		n->left = InsertNode(n->left, n, d);
	}
	

	else if (n->data < d)
	{
		n->right = InsertNode(n->right, n, d);
	}
	
	return n;

}
nodeptr& Node::ParentIntention()
{
	if (this == this->getParent()->right)
	{
		return this->getParent()->right;
	}

	else
	{
		return this->getParent()->left;
	}
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
		 {
			 RemoveNode(target);
		}

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
			Root->color = Node::eColor::BLACK;
			delete tmp;
		}
		else
		{
			nodeptr tmp = Root;
			nodeptr* new_Root = &Root;
			*new_Root = Root->right;
			Root->parent = NIL;
			Root->color = Node::eColor::BLACK;
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
	{
		tmp = tmp->left;
	}

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
	
		nodeptr newTarget = whichOne(no);
	
		RemoveNode(newTarget);
		return;
	}


	if (no->color == Node::eColor::BLACK)
	{
		if (x->color == Node::eColor::RED)
		{
			x->color = Node::eColor::BLACK;
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
	if (x != NIL)
	{
		s = x->getBrother();
	}
	else
	{
		s = (x == p->right) ? p->left : p->right;
	}
	
	
	nodeptr l = s->left;
	
	nodeptr r = s->right;
	Node::eColor s_col = s->color;
	Node::eColor p_col = p->color;
	Node::eColor l_col = l->color;
	Node::eColor r_col = r->color;
	using std::cout;
	using std::endl;

	/*std::cout << "형제 노드: " << s << std::endl;
	std::cout << "왼쪽 자식 : " << l << std::endl;
	std::cout << "오른쪽 자식 : " << r << std::endl;
	*/
	if (p_col == Node::eColor::RED 
		&& s_col == Node::eColor::BLACK 
		&&l_col == Node::eColor::BLACK 
		&& r_col == Node::eColor::BLACK)
	{
		//cout << "=====case 1======\n";
		delete_case1(p, s);
	}
	else if (x == p->left
		&& s_col == Node::eColor::BLACK
		&& r_col == Node::eColor::RED)
	{
		//cout << "=====case 2======\n";
		delete_case2(p, s, r);

	}
	else if (x == p->right
		&& s_col == Node::eColor::BLACK
		&& l_col == Node::eColor::RED)
	{
	//	cout << "=====case 2======\n";
		delete_case2(p, s, l);
	}
	else if (x == p->left
		&& s_col == Node::eColor::BLACK
		&& l_col == Node::eColor::RED
		&& r_col == Node::eColor::BLACK)
	{
	//	cout << "=====case 3======\n";
		delete_case3(p, s, l);
	}
	else if (x == p->right && s_col == Node::eColor::BLACK
		&& l_col == Node::eColor::BLACK
		&& r_col == Node::eColor::RED)
	{
	//	cout << "=====case 3======\n";
		delete_case3(p, s, r);
	}
	else if (p_col == Node::eColor::BLACK
		&& s_col == Node::eColor::BLACK
		&& l_col == Node::eColor::BLACK
		&& r_col == Node::eColor::BLACK)
	{
	//	cout << "=====case 4======\n";
		delete_case4(p, s);
	}
	else if (s == p->right
		&& p_col == Node::eColor::BLACK
		&& s_col == Node::eColor::RED
		&& l_col == Node::eColor::BLACK
		&& r_col == Node::eColor::BLACK)
	{
	//	cout << "=====case 5======\n";
		delete_case5(p, s, r);
	}

	else if (s == p->left
		&& p_col == Node::eColor::BLACK
		&& s_col == Node::eColor::RED
		&& l_col == Node::eColor::BLACK
		&& r_col == Node::eColor::BLACK)
	{
	//	cout << "=====case 5======\n";
		delete_case5(p, s, l);
	}
	
}
const nodeptr& Node::ParentIntention() const
{
	if (this == this->getParent()->right)
	{
		return this->getParent()->right;
	}

	else
	{
		return this->getParent()->left;
	}
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
	{
		clearNode(n->left);
	}

	if (n->right != NIL)
	{
		clearNode(n->right);
	}

	delete n;
}
void RedBlackTree::ShowAll(const nodeptr& n) const
{
	if (n->left != NIL)
	{
		ShowAll(n->left);
	}


	show_node(n);

	if (n->right != NIL)
	{
		ShowAll(n->right);
	}

}


void RedBlackTree::checkTree(nodeptr& x) 
{
	if (x->parent->color == Node::eColor::RED)
	{
		nodeptr uncle = x->getUncle();
		nodeptr grandP = x->getGrandparent();
		if (uncle->color == Node::eColor::RED)
		{
			insert_case1(x);
		}

		else
		{
			if (x == x->parent->left && x->parent == grandP->left)
			{
				insert_case2_2(x);
			}

			else if (x == x->parent->right && x->parent == grandP->right)
			{
				insert_case2_2(x);
			}

			else
			{
				insert_case2_1(x);
			}
		}
	}
	
}
void RedBlackTree::insert_case1(nodeptr& n)
{
	nodeptr uncle = n->getUncle();
	nodeptr grandP = n->getGrandParent();

	uncle->color = n->parent->color = Node::eColor::BLACK;
	if (grandP != Root)
	{
		grandP->color = Node::eColor::RED;
	}


	if (grandP->parent->color == Node::eColor::RED)
	{
		checkTree(grandP);
	}
	
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
	if (tmp != NIL)
	{
		tmp->parent = par;
	}
	no->parent = grandP;
	par->parent = no;
}
void RedBlackTree::rotateRight(nodeptr& x,nodeptr& p)
{

	nodeptr y;
	//if (x == NIL)std::cout << "이런 x가 " << x << "라니\n";
	if (x != NIL)
	{
		y = x->getBrother();
	}

	else
	{
		y = (x == p->right) ? p->left : p->right;
	}
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

	if (y != NIL)
	{
		y->parent = grandP;
	}
	
	p->parent =	grandP->parent;

	if (grandP != Root)
	{
		grandP->ParentIntention() = p;
	}

	else
	{
		nodeptr* root = &Root;
		*root = p;
	}
	grandP->parent = p;


	p->color = Node::eColor::BLACK;
	grandP->color = Node::eColor::RED;
}

void RedBlackTree::delete_case1(nodeptr& p, nodeptr& s)
{
	std::cout << "=====case 1======\n";
	p->color = Node::eColor::BLACK;
	s->color = Node::eColor::RED;
}
void RedBlackTree::delete_case2(nodeptr& p, nodeptr& s, nodeptr& a)
{
	std::cout << "=====case 2======\n";
	Node::eColor p_col = p->color;
	rotateRight(a,s);
	s->color = p_col;
	p->color = Node::eColor::BLACK;
	if (s == Root)
	{
		s->color = Node::eColor::BLACK;
	}

	a->color = Node::eColor::BLACK;
}
void RedBlackTree::delete_case3(nodeptr& p, nodeptr& s, nodeptr& a)
{
	std::cout << "=====case 3======\n";
	rotateLeft(a);
	a->color = Node::eColor::BLACK;
	s->color = Node::eColor::RED;
	delete_case2(p, a, s);
}
void RedBlackTree::delete_case4(nodeptr& p, nodeptr& s)
{
	std::cout << "=====case 4======\n";
	//std::cout << p << std::endl;
	s->color = Node::eColor::RED;
	
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
	
	if (sib->right->color == Node::eColor::BLACK &&
		sib->left->color == Node::eColor::BLACK)
	{
		delete_case1(sib->parent, sib);
	}

	else if (sib == sib->parent->right && sib->right->color == Node::eColor::RED)
	{
		delete_case2(p, sib, sib->right);
	}


	else if (sib == sib->parent->left && sib->left->color == Node::eColor::RED)
	{
		delete_case2(p, sib, sib->left);
	}

	else if (sib == sib->parent->right
		&& sib->right->color == Node::eColor::BLACK
		&& sib->left->color == Node::eColor::RED)
	{
		delete_case3(p, sib, sib->left);
	}

	else if (sib == sib->parent->left
		&& sib->left->color == Node::eColor::BLACK
		&& sib->right->color == Node::eColor::RED)
	{
		delete_case3(p, sib, sib->right);
	}
}
void RedBlackTree::Terminate()
{
	if (Root != nullptr)
	{
		Clear();
	}
}


void RedBlackTree::checkRedBlack()
{
	checkredblack(Root);
	std::cout << redblackCnt << "개 가 조건에 불일치\n";
}
void RedBlackTree::checkredblack(const nodeptr& node)
{
	if (node->color == Node::eColor::RED)
	{
		if (node->right->color == Node::eColor::RED
			|| node->left->color == Node::eColor::RED)
		{
			redblackCnt++;
		}
	}
	if (node->left != NIL)
	{
		checkredblack(node->left);
	}

	if (node->right != NIL)
	{
		checkredblack(node->right);
	}
	
	
}
bool RedBlackTree::checkBlackCnt() const
{
	nodevec nvec{};
	checkblackcount(Root, nvec);
	std::cout << "리프 노드는 " << nvec.size() << "개 입니다.\n";
	//nodevec::iterator it = nvec.begin();


	size_t cnt{ howManyBlacks(nvec[0])};


	std::cout << cnt << "개입니다.\n";

	for (unsigned int i = 1; i < nvec.size(); i++)
	{
		if (cnt != howManyBlacks(nvec[i]))
		{
			return false;
		}
	}
	return true;

}
void RedBlackTree::checkblackcount(const nodeptr& no, nodevec& vec) const
{
	if (no->left == NIL && no->right == NIL && no != NIL)
	{
		vec.push_back(no);
	}
	else
	{

		if (no->left != NIL)
		{
			checkblackcount(no->left, vec);
		}
		
		if (no->right != NIL)
		{
			checkblackcount(no->right, vec);
		}
	}

}


size_t RedBlackTree::howManyBlacks(const nodeptr& no) const
{
	size_t cnt{};
	nodeptr tmp{ no };

	while (tmp!=NIL)
	{
		if (tmp->color == Node::eColor::BLACK)
			++cnt;
		tmp = tmp->parent;

	}
	return cnt;
}



void RedBlackTree::findNode(const Data d)
{
	

	if (Root == nullptr)
	{
		std::cout << "트리가 비어있습니다.\n";
		return;
	}


	nodeptr target = Search(Root, d);


	if (target == NIL)
	{
		std::cout << "값이 존재하지 않습니다.\n";
	}
	else
	{	
		std::cout << "\t\t\t" << target->parent << std::endl;
		std::cout << "\t\t\t" << target << std::endl;
		std::cout << "\t" << target->left;
		std::cout << "\t\t\t" << target->right << std::endl;
	}
}