#include "bst.h"

int main()
{
	mytree::bst b;

	auto pRoot = b.Insert(nullptr, 8);
	b.Insert(pRoot, 3);
	b.Insert(pRoot, 10);
	b.Insert(pRoot, 1);
	b.Insert(pRoot, 6);

	b.InOrder(pRoot);
}