#pragma once

#include <iostream>

namespace mytree
{
	struct Node
	{
		int mData;
		Node* mLeft;
		Node* mRight;
		Node(int data, Node* left, Node* right)
		{
			mData = data;
			mLeft = left;
			mRight = right;
		}
	};
	class bst
	{
	private:
		Node* mpRoot{};

	public:
		bst()
		{
			mpRoot = CreateNode(0);
		}

		Node* GetRoot()
		{
			return mpRoot;
		}

		Node* CreateNode(int data)
		{
			return new Node(data, nullptr, nullptr);
		}

		Node* Insert(Node* pParent, int data)
		{
			if (pParent == nullptr)
			{
				mpRoot = CreateNode(data);
				return mpRoot;
			}
			if (data < pParent->mData)
			{
				pParent->mLeft = Insert(pParent->mLeft, data);
			}
			else if (data > pParent->mData)
			{
				pParent->mRight = Insert(pParent->mRight, data);
			}
			return pParent;
		}

	public:
		void Visit(Node* node)
		{
			std::cout << node->mData << " -> ";
		}
		
		void InOrder(Node* node)
		{
			if (node == nullptr)
			{
				return;
			}

			InOrder(node->mLeft);
			Visit(node);
			InOrder(node->mRight);
		}
	};
}
