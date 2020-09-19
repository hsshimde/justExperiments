#pragma once
#pragma once
#ifndef __TREE__H__
#define __TREE__H__
#include <iostream>
#include <string>
#include <vector>
typedef double Data;

const double nil = -0.2345612;
class Node
{
private:
	//static nodeptr NIL;
public:
	enum class Color{BLACK,RED};
	Color color;
public:
	//static int nodecnt;
	typedef Node* nodeptr;
	nodeptr parent;
	nodeptr left;
	nodeptr right;
	Data data;
	Node(Node* pr, Data d, Color co, nodeptr l = nullptr, nodeptr r = nullptr) :parent(pr), data(d), color(co), left(l), right(r) {  }
	~Node() {}
	const nodeptr& getParent() { return parent; }
	const nodeptr& getParent()const { return parent; }
	nodeptr& ParentIntention();
	const nodeptr& ParentIntention()const;
	friend std::ostream& operator<<(std::ostream& os, const nodeptr& n);
	const nodeptr& getUncle()const;
	nodeptr& getUncle();
	const nodeptr& getGrandParent()const { return this->parent->parent; }
	nodeptr& getGrandparent() { return this->parent->parent; }
	nodeptr& getBrother();
	const nodeptr& getBrother()const;
	bool checkNode()const;
	void swapColor(nodeptr& b) { Node::Color tmp = this->color; this->color = b->color; b->color = tmp; }
};
typedef Node* nodeptr;
typedef std::vector<nodeptr> nodevec;
void showNode(const nodeptr& node);

class RedBlackTree
{
private:

	//nodeptr justInserted;
	typedef Node* nodeptr;

	nodeptr justInserted;
	nodeptr Root;
	nodeptr NIL;
	int nodecnt;
	int redblackCnt;
	void RemoveNode(nodeptr& n);
	nodeptr InsertNode(nodeptr& n,const nodeptr& par,Data d);
	//nodeptr SearchNode(Node* n,Data d);
	void clearNode(nodeptr& n);
	void ShowAll(const nodeptr& n)const;
	nodeptr& Search(nodeptr& n, Data d);
	void checkTree(nodeptr& n);
	void insert_case1(nodeptr& n);
	void insert_case2_1(nodeptr& n);
	void insert_case2_2(nodeptr& n);
	void rotateRight(nodeptr& x,nodeptr& par);
	void rotateLeft(nodeptr& n);
	nodeptr whichOne(nodeptr& n);
	void repairTree(nodeptr& parent,nodeptr& x);
	void delete_case1(nodeptr& p, nodeptr& s);
	void delete_case2(nodeptr& p, nodeptr& s,nodeptr& a);
	void delete_case3(nodeptr& p, nodeptr& x,nodeptr& a);
	void delete_case4(nodeptr& p, nodeptr& s);
	void delete_case5(nodeptr& p, nodeptr& s,nodeptr& a);
	void show_node(const nodeptr& no)const { std::cout << no << std::endl; }
	void pre_show(const nodeptr& no)const;
	void show_mid(const nodeptr& no)const;

	void checkredblack(const nodeptr& node);
	void checkblackcount(const nodeptr& no,nodevec& vec)const;
	int howManyBlacks(const nodeptr& no)const;
	
	//static int nodecnt;
public:
	
	RedBlackTree();
	~RedBlackTree() { Terminate(); delete NIL; }
	void Insert(Data d);
	void Remove(Data d);
	//Node* Search(Data d);
	void Clear();
	void ShowTree()const;
	void Terminate();
	void Pre_Show()const;
	void showRoot()const;
	void showMid()const;
	void checkRedBlack();
	bool checkBlackCnt()const;
	void findNode(const Data d);
	//bool checkredblack(const nodeptr& node)const;
	
};


#endif