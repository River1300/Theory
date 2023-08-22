#pragma once

/* ----- < 자료 구조 트리 > ----- */

/* Tree */

// 지금까지는 순차적( Sequential )으로 연관된 자료들에 대해 살펴봤다. 하지만 실제 환경에서는 모든 객체들이 단일한 관계로만 연결되어 있지 않다.
// 마치 나뭇가지가 뻗어나가는 모습처럼 객체들이 연결되어 있어 Tree라 부른다.
//		=> 트리 구조는 보통 나무를 거꾸로 보는 형상처럼 설계 된다.

/*
LEVEL 0					A[ Root Node ]
Level 1				B ㅡㅡㅡㅡㅗㅡㅡㅡㅡ C[ Parent Node ]
Level 2			D ㅡㅗㅡ E			F ㅡㅗㅡ G[ Child Node ]
Level 3		H ㅡㅗㅡ I	 J

트리의 특성은 간단히 다음과 같다.
	Node : 트리에 속한 각 데이터
	Edge : 트리를 연결하는 선
	오직 하나의 Root Node 만 존재
	두 Node 를 연결하는 경로는 하나 뿐

루트 노드( root node ) : 나무의 뿌리에 해당한다.
	=> 부모( Parent )가 없는 노드
	=> 하나의 트리는 하나의 루트 노드만 존재
리프 노드( leaf node ) : 나뭇잎에 해당한다. 단말 노드( Terminal Node )라고도 한다.
	=> 자식( Children )이 없는 노드
내부 노드( internal node ) : 리프 노드가 아닌 노드들
	=> 부모와 자식이 있는 노드
형제( sibling ) : 같은 부모를 가진 노드들
레벨( level ) : 동일한 깊이를 가지는 노드 집합
깊이( depth ) : 트리의 최고 레벨. 높이( height )라고도 한다.
*/

/* ----- < 이진 트리( Binary Tree ) > ----- */

/*
이런 트리 구조 중에서 위와 같이 하나의 노드에 최대 2개의 자식을 가지는 트리를 특별히 이진트리( Binary Tree )라 부른다.
컴퓨터 자료구조에서 대부분의 트리는 바로 이러한 이진 트리를 말한다.
최대 2개를 가진다는 특성 때문에 2진 트리라 한다.
*/

// Full Binary Tree : Proper Binary Tree 또는 2-Tree라고도 부르는데, 리프 노드를 제외한 모든 노드가 두 개의 자식을 가지고 있는 형태
// Perfect Binary Tree : 리프노드를 제외한 모든 노드가 두 개의 자식을 가지고 있으며, 모든 리프 노드가 같은 레벨에 존재하는 형태이다.
//		=> 즉 Full Binary Tree의 특별한 형태이다.
// Complete Binary Tree : 마지막 레벨을 제외하고는 모든 레벨에 노드가 들어 있고, 리프로 원소가 추가될 때는 왼쪽 부터 채워진다.

#include <iostream>
#include <queue>
#include <stack>

namespace mytree
{
	struct Node	// 트리의 노드를 나타내는 구조체, 정수형 데이터 하나와 왼쪽, 오른쪽 하위 노드를 가르키는 포인터를 하나씩 들고 있다.
	{
		int mData;
		Node* mLeft;
		Node* mRight;
		Node(int data, Node* left, Node* right)	// 클래스를 통해 생성되는 Node, 자신의 속성은 자신이 초기화
		{
			mData = data;
			mLeft = left;
			mRight = right;
		}
	};

	class binarytree
	{
	private:
		Node* mpRoot{};	// 루트 노드를 가리킬 포인터

	public:
		binarytree()	// 기본 생성자로 루트 노드를 하나 만든다.
		{
			mpRoot = CreateNode(0);
		}
		Node* GetRoot()	// 루트 노드 반환
		{
			return mpRoot;
		}
		Node* CreateNode(int data)	// 새로 노드를 하나 만들어 반환한다.
		{
			return new Node(data, nullptr, nullptr);
		}
		Node* InsertLeft(Node* parent, int data)	// 인자( 부모 노드 )의 왼쪽 자식 노드를 삽입한다.
		{
			parent->mLeft = CreateNode(data);
			return parent->mLeft;
		}
		Node* InsertRight(Node* parent, int data)	// 인자( 부모 노드 )의 오른쪽 자식 노드를 삽입한다.
		{
			parent->mRight = CreateNode(data);
			return parent->mRight;
		}

/* 트리 순회( Tree Traversal ) */

// 트리의 핵심은 순회 및 검색
// 순회( Traverse )는 트리의 모든 원소를 한 번씩 살펴 보는 과정을 말한다.
//		=> Breadth-First Algorithm( 너비 우선 알고리즘 )
//			=> 너비 우선, 즉 가로로 읽어 나가면 된다. 가로라는 의미는 트리에서 같은 레벨에 있는 노드들을 먼저 탐색해야 한다는 뜻
//		=> Depth-First Algorithm( 깊이 우선 알고리즘 )
//			=> 깊이 우선, 즉 세로로 읽어야 한다.

/*
Bread-First Algorithm
	루트에서 부터 루트 노드는 바로 출력하면 된다.
	1의 왼쪽 자식 2
	1의 오른쪽 자식 3
	그 다음은 2의 왼쪽, 오른쪽 자식, 그리고 3의 왼쪽, 오른쪽 자식
	먼저 저장된 값을 먼저 출력 Queue
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
				if (node->mLeft != nullptr)	// 왼쪽 값을 먼저 저장( 오름 차 )
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
	루트에서 부터 루트 노드는 바로 출력하면 된다.
	1의 왼쪽 자식 2
	2로 계속해서 파고 들어간다. 2의 왼쪽 자식 4
	4의 자식은 없으니 위로 올라가서 2의 오른쪽 자식 5
	3도 마찬가지 
	단 왼쪽으로 먼저 탐색을 수행해야 하므로 오른쪽을 먼저 저장하고 Stack 으로 출력
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

// Stack -> Call Stack : 재귀호출
//		=> 루트를 중심으로 left subtree, right subtree로 나뉘어 있고
//		=> 그 밑으로도 마찬가지로 나뉘어 있다.

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
// Visit을 어디에 두느냐에 따라 출력 방식이 다르다.
//		=> In-Order : 왼쪽 서브 트리를 모두 방문 -> 루트 노드 -> 오른쪽 서브 트리로 순회
//		=> Pre-Order : 루트 노드 -> 왼쪽 서브 트리 -> 오른쪽 서브 트리 순회
//		=> Post-Order : 왼쪽 서브 트리 -> 오른쪽 서브 트리 -> 루트 노드

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
