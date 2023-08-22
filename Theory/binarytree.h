#pragma once

/* ----- < �ڷ� ���� Ʈ�� > ----- */

/* Tree */

// ���ݱ����� ������( Sequential )���� ������ �ڷ�鿡 ���� ����ô�. ������ ���� ȯ�濡���� ��� ��ü���� ������ ����θ� ����Ǿ� ���� �ʴ�.
// ��ġ ���������� ������� ���ó�� ��ü���� ����Ǿ� �־� Tree�� �θ���.
//		=> Ʈ�� ������ ���� ������ �Ųٷ� ���� ����ó�� ���� �ȴ�.

/*
LEVEL 0					A[ Root Node ]
Level 1				B �ѤѤѤѤǤѤѤѤ� C[ Parent Node ]
Level 2			D �ѤǤ� E			F �ѤǤ� G[ Child Node ]
Level 3		H �ѤǤ� I	 J

Ʈ���� Ư���� ������ ������ ����.
	Node : Ʈ���� ���� �� ������
	Edge : Ʈ���� �����ϴ� ��
	���� �ϳ��� Root Node �� ����
	�� Node �� �����ϴ� ��δ� �ϳ� ��

��Ʈ ���( root node ) : ������ �Ѹ��� �ش��Ѵ�.
	=> �θ�( Parent )�� ���� ���
	=> �ϳ��� Ʈ���� �ϳ��� ��Ʈ ��常 ����
���� ���( leaf node ) : �����ٿ� �ش��Ѵ�. �ܸ� ���( Terminal Node )��� �Ѵ�.
	=> �ڽ�( Children )�� ���� ���
���� ���( internal node ) : ���� ��尡 �ƴ� ����
	=> �θ�� �ڽ��� �ִ� ���
����( sibling ) : ���� �θ� ���� ����
����( level ) : ������ ���̸� ������ ��� ����
����( depth ) : Ʈ���� �ְ� ����. ����( height )��� �Ѵ�.
*/

/* ----- < ���� Ʈ��( Binary Tree ) > ----- */

/*
�̷� Ʈ�� ���� �߿��� ���� ���� �ϳ��� ��忡 �ִ� 2���� �ڽ��� ������ Ʈ���� Ư���� ����Ʈ��( Binary Tree )�� �θ���.
��ǻ�� �ڷᱸ������ ��κ��� Ʈ���� �ٷ� �̷��� ���� Ʈ���� ���Ѵ�.
�ִ� 2���� �����ٴ� Ư�� ������ 2�� Ʈ���� �Ѵ�.
*/

// Full Binary Tree : Proper Binary Tree �Ǵ� 2-Tree��� �θ��µ�, ���� ��带 ������ ��� ��尡 �� ���� �ڽ��� ������ �ִ� ����
// Perfect Binary Tree : ������带 ������ ��� ��尡 �� ���� �ڽ��� ������ ������, ��� ���� ��尡 ���� ������ �����ϴ� �����̴�.
//		=> �� Full Binary Tree�� Ư���� �����̴�.
// Complete Binary Tree : ������ ������ �����ϰ�� ��� ������ ��尡 ��� �ְ�, ������ ���Ұ� �߰��� ���� ���� ���� ä������.

#include <iostream>
#include <queue>
#include <stack>

namespace mytree
{
	struct Node	// Ʈ���� ��带 ��Ÿ���� ����ü, ������ ������ �ϳ��� ����, ������ ���� ��带 ����Ű�� �����͸� �ϳ��� ��� �ִ�.
	{
		int mData;
		Node* mLeft;
		Node* mRight;
		Node(int data, Node* left, Node* right)	// Ŭ������ ���� �����Ǵ� Node, �ڽ��� �Ӽ��� �ڽ��� �ʱ�ȭ
		{
			mData = data;
			mLeft = left;
			mRight = right;
		}
	};

	class binarytree
	{
	private:
		Node* mpRoot{};	// ��Ʈ ��带 ����ų ������

	public:
		binarytree()	// �⺻ �����ڷ� ��Ʈ ��带 �ϳ� �����.
		{
			mpRoot = CreateNode(0);
		}
		Node* GetRoot()	// ��Ʈ ��� ��ȯ
		{
			return mpRoot;
		}
		Node* CreateNode(int data)	// ���� ��带 �ϳ� ����� ��ȯ�Ѵ�.
		{
			return new Node(data, nullptr, nullptr);
		}
		Node* InsertLeft(Node* parent, int data)	// ����( �θ� ��� )�� ���� �ڽ� ��带 �����Ѵ�.
		{
			parent->mLeft = CreateNode(data);
			return parent->mLeft;
		}
		Node* InsertRight(Node* parent, int data)	// ����( �θ� ��� )�� ������ �ڽ� ��带 �����Ѵ�.
		{
			parent->mRight = CreateNode(data);
			return parent->mRight;
		}

/* Ʈ�� ��ȸ( Tree Traversal ) */

// Ʈ���� �ٽ��� ��ȸ �� �˻�
// ��ȸ( Traverse )�� Ʈ���� ��� ���Ҹ� �� ���� ���� ���� ������ ���Ѵ�.
//		=> Breadth-First Algorithm( �ʺ� �켱 �˰��� )
//			=> �ʺ� �켱, �� ���η� �о� ������ �ȴ�. ���ζ�� �ǹ̴� Ʈ������ ���� ������ �ִ� ������ ���� Ž���ؾ� �Ѵٴ� ��
//		=> Depth-First Algorithm( ���� �켱 �˰��� )
//			=> ���� �켱, �� ���η� �о�� �Ѵ�.

/*
Bread-First Algorithm
	��Ʈ���� ���� ��Ʈ ���� �ٷ� ����ϸ� �ȴ�.
	1�� ���� �ڽ� 2
	1�� ������ �ڽ� 3
	�� ������ 2�� ����, ������ �ڽ�, �׸��� 3�� ����, ������ �ڽ�
	���� ����� ���� ���� ��� Queue
*/
		void Visit(Node* node) { std::cout << node->mData << " -> "; }

		void BreadthFirst()
		{
			std::queue<Node*> q;
			q.push(mpRoot);

			while (!q.empty())
			{
				auto node = q.front();
				Visit(node);
				q.pop();
				if (node->mLeft != nullptr)	// ���� ���� ���� ����( ���� �� )
				{
					q.push(node->mLeft);
				}
				if (node->mRight != nullptr)
				{
					q.push(node->mRight);
				}
			}
		}

/*
Depth-First Algorithm
	��Ʈ���� ���� ��Ʈ ���� �ٷ� ����ϸ� �ȴ�.
	1�� ���� �ڽ� 2
	2�� ����ؼ� �İ� ����. 2�� ���� �ڽ� 4
	4�� �ڽ��� ������ ���� �ö󰡼� 2�� ������ �ڽ� 5
	3�� �������� 
	�� �������� ���� Ž���� �����ؾ� �ϹǷ� �������� ���� �����ϰ� Stack ���� ���
*/
		void DepthFirst()
		{
			std::stack<Node*> stack;
			stack.push(mpRoot);

			while (!stack.empty())
			{
				auto node = stack.top();
				Visit(node);
				stack.pop();
				if (node->mRight != nullptr)
				{
					stack.push(node->mRight);
				}
				if (node->mLeft != nullptr)
				{
					stack.push(node->mLeft);
				}
			}
		}

// Stack -> Call Stack : ���ȣ��
//		=> ��Ʈ�� �߽����� left subtree, right subtree�� ������ �ְ�
//		=> �� �����ε� ���������� ������ �ִ�.

		void DepthFirstRecursive(Node* pNode)	// Pre-Order
		{
			if (pNode == nullptr)
			{
				return;
			}

			Visit(pNode);
			DepthFirstRecursive(pNode->mLeft);
			DepthFirstRecursive(pNode->mRight);
		}

// InOrder, PreOrder, PostOrder
// Visit�� ��� �δ��Ŀ� ���� ��� ����� �ٸ���.
//		=> In-Order : ���� ���� Ʈ���� ��� �湮 -> ��Ʈ ��� -> ������ ���� Ʈ���� ��ȸ
//		=> Pre-Order : ��Ʈ ��� -> ���� ���� Ʈ�� -> ������ ���� Ʈ�� ��ȸ
//		=> Post-Order : ���� ���� Ʈ�� -> ������ ���� Ʈ�� -> ��Ʈ ���

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

		void PostOrder(Node* node)
		{
			if (node == nullptr)
			{
				return;
			}

			PostOrder(node->mLeft);
			PostOrder(node->mRight);
			Visit(node);
		}
	};
}
