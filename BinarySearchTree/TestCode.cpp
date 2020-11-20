#include <cassert>

#include "BinarySearchTree.h"
#include "TreeNode.h"


using namespace bst;
void testCode();
void testCode2();
void testCode3();

int main()
{
    /*testCode();
    testCode2();
    testCode3();*/

    BinarySearchTree<int> tree;
    tree.Insert(std::make_unique<int>(11));
    tree.Insert(std::make_unique<int>(13));
    tree.Insert(std::make_unique<int>(-6));
    tree.Insert(std::make_unique<int>(3));
    tree.Insert(std::make_unique<int>(-3));
    tree.Insert(std::make_unique<int>(-5));
    tree.Insert(std::make_unique<int>(17));
    tree.Insert(std::make_unique<int>(20));
    tree.Insert(std::make_unique<int>(22));
    tree.Insert(std::make_unique<int>(12));

    tree.Clear();

    return 0;

}

void testCode()
{
    
    BinarySearchTree<int> tree;
    bool bDeleted{};
    std::vector<int> v;

    tree.Insert(std::make_unique<int>(1));

    v = tree.TraverseInOrder(tree.GetRootNode().lock());
    assert(v.size() == 1);
    assert(v[0] == 1);

    bDeleted = tree.Delete(1);
    assert(bDeleted);
    v = tree.TraverseInOrder(tree.GetRootNode().lock());
    assert(v.size() == 0);

    tree.Insert(std::make_unique<int>(11));
    tree.Insert(std::make_unique<int>(13));
    tree.Insert(std::make_unique<int>(6));
    tree.Insert(std::make_unique<int>(3));
    tree.Insert(std::make_unique<int>(-3));
    tree.Insert(std::make_unique<int>(-5));
    tree.Insert(std::make_unique<int>(17));
    tree.Insert(std::make_unique<int>(20));
    tree.Insert(std::make_unique<int>(0));
    tree.Insert(std::make_unique<int>(12));

    tree.Delete(20);
    tree.Delete(-3);
    tree.Delete(11);
    tree.Delete(5);
    tree.Delete(6);
    tree.Delete(17);
    tree.Delete(13);


}

void testCode2()
{

    bool bDelete = false;
    bool bSearch = false;
    BinarySearchTree<int> tree;
    std::vector<int> traverseResult;

    bDelete = tree.Delete(15);
    bSearch = tree.Search(15);
    traverseResult = tree.TraverseInOrder(tree.GetRootNode().lock());
    assert(!bDelete);
    assert(!bSearch);
    assert(traverseResult.empty());

    tree.Insert(std::make_unique<int>(15));
    traverseResult = tree.TraverseInOrder(tree.GetRootNode().lock());
    bDelete = tree.Delete(15);
    assert(bDelete);
    assert(traverseResult.size() == 1);
    assert(traverseResult[0] == 15);
    assert(tree.GetRootNode().lock() == nullptr);

    BinarySearchTree<int> tree1;
    tree1.Insert(std::make_unique<int>(10));
    tree1.Insert(std::make_unique<int>(5));
    tree1.Insert(std::make_unique<int>(15));
    bDelete = tree1.Delete(10);
    assert(bDelete);
    traverseResult = tree1.TraverseInOrder(tree1.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 15);

    BinarySearchTree<int> tree2;
    tree2.Insert(std::make_unique<int>(10));
    tree2.Insert(std::make_unique<int>(5));
    tree2.Insert(std::make_unique<int>(15));
    tree2.Insert(std::make_unique<int>(13));
    tree2.Insert(std::make_unique<int>(20));
    bDelete = tree2.Delete(10);
    assert(bDelete);
    traverseResult = tree2.TraverseInOrder(tree2.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 13);
    assert(traverseResult[2] == 15);
    assert(traverseResult[3] == 20);

    BinarySearchTree<int> tree3;
    tree3.Insert(std::make_unique<int>(10));
    tree3.Insert(std::make_unique<int>(5));
    tree3.Insert(std::make_unique<int>(15));
    tree3.Insert(std::make_unique<int>(20));
    bDelete = tree3.Delete(10);
    assert(bDelete);
    traverseResult = tree3.TraverseInOrder(tree3.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 15);
    assert(traverseResult[2] == 20);

    BinarySearchTree<int> tree4;
    tree4.Insert(std::make_unique<int>(10));
    tree4.Insert(std::make_unique<int>(5));
    tree4.Insert(std::make_unique<int>(15));
    tree4.Insert(std::make_unique<int>(13));
    tree4.Insert(std::make_unique<int>(14));
    tree4.Insert(std::make_unique<int>(20));
    bDelete = tree4.Delete(10);
    assert(bDelete);
    traverseResult = tree4.TraverseInOrder(tree4.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 13);
    assert(traverseResult[2] == 14); //needs debugging....
    assert(traverseResult[3] == 15);
    assert(traverseResult[4] == 20);

    BinarySearchTree<int> tree5;
    tree5.Insert(std::make_unique<int>(10));
    tree5.Insert(std::make_unique<int>(5));
    tree5.Insert(std::make_unique<int>(15));
    tree5.Insert(std::make_unique<int>(13));
    tree5.Insert(std::make_unique<int>(20));
    bDelete = tree5.Delete(15);
    assert(bDelete);
    traverseResult = tree5.TraverseInOrder(tree5.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 10);
    assert(traverseResult[2] == 13);
    assert(traverseResult[3] == 20);

    BinarySearchTree<int> tree6;
    tree6.Insert(std::make_unique<int>(10));
    tree6.Insert(std::make_unique<int>(5));
    tree6.Insert(std::make_unique<int>(15));
    tree6.Insert(std::make_unique<int>(1));
    tree6.Insert(std::make_unique<int>(2));
    bDelete = tree6.Delete(5);
    assert(bDelete);
    traverseResult = tree6.TraverseInOrder(tree6.GetRootNode().lock());
    assert(traverseResult[0] == 1);
    assert(traverseResult[1] == 2);
    assert(traverseResult[2] == 10);
    assert(traverseResult[3] == 15);


    BinarySearchTree<int> tree7;
    tree7.Insert(std::make_unique<int>(10));
    tree7.Insert(std::make_unique<int>(5));
    tree7.Insert(std::make_unique<int>(15));
    tree7.Insert(std::make_unique<int>(13));
    tree7.Insert(std::make_unique<int>(20));
    tree7.Insert(std::make_unique<int>(17));
    tree7.Insert(std::make_unique<int>(25));
    bDelete = tree7.Delete(15);
    assert(bDelete);
    traverseResult = tree7.TraverseInOrder(tree7.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 10);
    assert(traverseResult[2] == 13);
    assert(traverseResult[3] == 17);
    assert(traverseResult[4] == 20);
    assert(traverseResult[5] == 25);

    BinarySearchTree<int> tree8;
    tree8.Insert(std::make_unique<int>(15));
    tree8.Insert(std::make_unique<int>(10));
    tree8.Insert(std::make_unique<int>(20));
    tree8.Insert(std::make_unique<int>(5));
    tree8.Insert(std::make_unique<int>(13));
    tree8.Insert(std::make_unique<int>(12));
    tree8.Insert(std::make_unique<int>(14));
    bDelete = tree8.Delete(10);
    assert(bDelete);
    traverseResult = tree8.TraverseInOrder(tree8.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 12);
    assert(traverseResult[2] == 13);
    assert(traverseResult[3] == 14);
    assert(traverseResult[4] == 15);
    assert(traverseResult[5] == 20);

    BinarySearchTree<int> tree9;
    tree9.Insert(std::make_unique<int>(10));
    tree9.Insert(std::make_unique<int>(5));
    tree9.Insert(std::make_unique<int>(15));
    tree9.Insert(std::make_unique<int>(13));
    tree9.Insert(std::make_unique<int>(20));
    tree9.Insert(std::make_unique<int>(25));
    bDelete = tree9.Delete(15);
    assert(bDelete);
    traverseResult = tree9.TraverseInOrder(tree9.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 10);
    assert(traverseResult[2] == 13);
    assert(traverseResult[3] == 20);
    assert(traverseResult[4] == 25);

    BinarySearchTree<int> tree10;
    tree10.Insert(std::make_unique<int>(15));
    tree10.Insert(std::make_unique<int>(10));
    tree10.Insert(std::make_unique<int>(20));
    tree10.Insert(std::make_unique<int>(5));
    tree10.Insert(std::make_unique<int>(13));
    tree10.Insert(std::make_unique<int>(14));
    bDelete = tree10.Delete(10);
    assert(bDelete);
    traverseResult = tree10.TraverseInOrder(tree10.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 13);
    assert(traverseResult[2] == 14);
    assert(traverseResult[3] == 15);
    assert(traverseResult[4] == 20);

    BinarySearchTree<int> tree11;
    tree11.Insert(std::make_unique<int>(10));
    tree11.Insert(std::make_unique<int>(5));
    tree11.Insert(std::make_unique<int>(15));
    tree11.Insert(std::make_unique<int>(13));
    tree11.Insert(std::make_unique<int>(20));
    tree11.Insert(std::make_unique<int>(17));
    tree11.Insert(std::make_unique<int>(25));
    tree11.Insert(std::make_unique<int>(18));
    bDelete = tree11.Delete(15);
    assert(bDelete);
    traverseResult = tree11.TraverseInOrder(tree11.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 10);
    assert(traverseResult[2] == 13);
    assert(traverseResult[3] == 17);
    assert(traverseResult[4] == 18);
    assert(traverseResult[5] == 20);
    assert(traverseResult[6] == 25);

    bDelete = tree11.Delete(15);
    assert(!bDelete);

    bDelete = tree11.Delete(17);
    assert(bDelete);
    traverseResult = tree11.TraverseInOrder(tree11.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 10);
    assert(traverseResult[2] == 13);
    assert(traverseResult[3] == 18);
    assert(traverseResult[4] == 20);
    assert(traverseResult[5] == 25);

    bDelete = tree11.Delete(17);
    assert(!bDelete);

    bDelete = tree11.Delete(10);
    assert(bDelete);
    traverseResult = tree11.TraverseInOrder(tree11.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 13);
    assert(traverseResult[2] == 18);
    assert(traverseResult[3] == 20);
    assert(traverseResult[4] == 25);


    BinarySearchTree<int> tree12;
    tree12.Insert(std::make_unique<int>(15));
    tree12.Insert(std::make_unique<int>(7));
    tree12.Insert(std::make_unique<int>(20));
    tree12.Insert(std::make_unique<int>(5));
    tree12.Insert(std::make_unique<int>(11));
    tree12.Insert(std::make_unique<int>(9));
    tree12.Insert(std::make_unique<int>(14));
    tree12.Insert(std::make_unique<int>(10));
    bDelete = tree12.Delete(7);
    assert(bDelete);
    traverseResult = tree12.TraverseInOrder(tree12.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 9);
    assert(traverseResult[2] == 10);
    assert(traverseResult[3] == 11);
    assert(traverseResult[4] == 14);
    assert(traverseResult[5] == 15);
    assert(traverseResult[6] == 20);

    bDelete = tree12.Delete(7);
    assert(!bDelete);

    bDelete = tree12.Delete(9);
    assert(bDelete);
    traverseResult = tree12.TraverseInOrder(tree12.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 10);
    assert(traverseResult[2] == 11);
    assert(traverseResult[3] == 14);
    assert(traverseResult[4] == 15);
    assert(traverseResult[5] == 20);

    bDelete = tree12.Delete(9);
    assert(!bDelete);

    bDelete = tree12.Delete(10);
    assert(bDelete);

    traverseResult = tree12.TraverseInOrder(tree12.GetRootNode().lock());
    assert(traverseResult[0] == 5);
    assert(traverseResult[1] == 11);
    assert(traverseResult[2] == 14);
    assert(traverseResult[3] == 15);
    assert(traverseResult[4] == 20);

    return;

}

void testCode3()
{
    bst::BinarySearchTree<float> tree;
    std::vector<float> v1;
    //test for empty tree
    assert(tree.GetRootNode().lock() == nullptr);
    assert(tree.Delete(1.f) == false);
    assert(tree.Search(1.f) == false);

    //test for single noded tree
    tree.Insert(std::make_unique<float>(1.2f));
    assert(*tree.GetRootNode().lock()->Data == 1.2f);
    assert(tree.Search(1.2f) == true);

    v1 = tree.TraverseInOrder(tree.GetRootNode().lock());
    assert(v1.size() == 1);
    assert(v1[0] == 1.2f);
    assert(tree.Delete(1.3f) == false);
    assert(tree.Delete(1.2f) == true);
    assert(tree.GetRootNode().lock() == nullptr);

    //A bunch of test....
    tree.Insert(std::make_unique<float>(50.f));
    tree.Insert(std::make_unique<float>(25.f));
    tree.Insert(std::make_unique<float>(75.f));
    tree.Insert(std::make_unique<float>(12.5f));
    tree.Insert(std::make_unique<float>(37.5f));
    tree.Insert(std::make_unique<float>(38.f));
    tree.Insert(std::make_unique<float>(62.5f));
    tree.Insert(std::make_unique<float>(87.5f));
    tree.Insert(std::make_unique<float>(6.f));
    tree.Insert(std::make_unique<float>(3.f));
    tree.Insert(std::make_unique<float>(30.f));
    tree.Insert(std::make_unique<float>(31.f));
    tree.Insert(std::make_unique<float>(32.f));
    tree.Insert(std::make_unique<float>(88.f));
    tree.Insert(std::make_unique<float>(89.f));

    v1 = tree.TraverseInOrder(tree.GetRootNode().lock());
    assert(v1.size() == 15);
    assert(v1[0] == 3.f);
    assert(v1[1] == 6.f);
    assert(v1[2] == 12.5f);
    assert(v1[3] == 25.f);
    assert(v1[4] == 30.f);
    assert(v1[5] == 31.f);
    assert(v1[6] == 32.f);
    assert(v1[7] == 37.5f);
    assert(v1[8] == 38.f);
    assert(v1[9] == 50.f);
    assert(v1[10] == 62.5f);
    assert(v1[11] == 75.f);
    assert(v1[12] == 87.5f);
    assert(v1[13] == 88.f);
    assert(v1[14] == 89.f);

    assert(tree.Search(34.f) == false);
    assert(tree.Search(62.5f) == true);

    assert(tree.Delete(34.f) == false);
    assert(tree.Delete(12.5f) == true);
    assert(tree.Delete(37.5f) == true);
    assert(tree.Delete(25.f) == true);
    assert(tree.Delete(25.f) == false);
    assert(tree.Delete(87.5f) == true);

    assert(tree.Delete(50.f) == true); //case for deleting root node
   // tree.TestBinarySearchTreeCondition(tree.GetRootNode().lock());

    assert(tree.GetRootNode().lock() != nullptr);
    //assert(*tree.GetRootNode().lock()->Data == 38.f);



    assert(tree.Search(37.5f) == false);

    v1 = tree.TraverseInOrder(tree.GetRootNode().lock());
    assert(v1.size() == 10);
    assert(v1[0] == 3.f);
    assert(v1[1] == 6.f);
    assert(v1[2] == 30.f);
    assert(v1[3] == 31.f);
    assert(v1[4] == 32.f);
    assert(v1[5] == 38.f);
    assert(v1[6] == 62.5f);
    assert(v1[7] == 75.f);
    assert(v1[8] == 88.f);
    assert(v1[9] == 89.f);

    //test for reassigned node
    assert(tree.Delete(32.f) == true);
    assert(tree.Delete(6.f) == true);
    assert(tree.Delete(88.f) == true);

    v1 = tree.TraverseInOrder(tree.GetRootNode().lock());
    assert(v1.size() == 7);
    assert(v1[0] == 3.f);
    assert(v1[1] == 30.f);
    assert(v1[2] == 31.f);
    assert(v1[3] == 38.f);
    assert(v1[4] == 62.5f);
    assert(v1[5] == 75.f);
    assert(v1[6] == 89.f);

}