#include "binarytree.h"

int main()
{
	mytree::binarytree myTree;

	auto pRoot = myTree.GetRoot();
	pRoot->mData = 1;

	auto pNode = myTree.InsertLeft(pRoot, 2);
	myTree.InsertLeft(pNode, 4);
	myTree.InsertRight(pNode, 5);
	pNode = myTree.InsertRight(pRoot, 3);
	myTree.InsertLeft(pNode, 6);
	myTree.InsertRight(pNode, 7);

	std::cout << "--- In Order ---\n";
	myTree.InOrder(pRoot);
	std::cout << "\n--- Pre Order ---\n";
	myTree.DepthFirstRecursive(pRoot);
	std::cout << "\n--- Post Order ---\n";
	myTree.PostOrder(pRoot);
}