#pragma once

// 쿼드 트리는 말 그대로 4개의 자식을 가진 트리로, 2차원 영역을 재귀적으로 4분할 하면서 생성하는 자료구조

/*
쿼드트리( QuadTree )는 이미지나 공간을 분할하거나 압축하기 위한 계층적인 자료 구조를 말한다. 
이는 이미지나 공간을 4개의 구역으로 분할하는 방식으로 작동한다. 
각 분할된 영역은 원본 영역의 1/4 크기이며, 각 분할된 영역 역시 쿼드트리의 노드로서 처리될 수 있다.

쿼드트리는 주로 이미지 압축이나 검색을 위해 사용된다. 
이미지 압축에서는 색상 정보를 쿼드트리로 표현하여 비슷한 색상을 하나의 노드로 묶어 압축을 실시한다. 
검색에서는 공간을 분할하여 특정 지점의 속성을 찾는 등 다양한 용도로 활용된다.

이러한 쿼드트리는 재귀적인 구조로 표현되며, 각 노드는 자신의 분할된 영역을 나타내는 정보와 해당 영역의 속성을 가지고 있다. 
쿼드트리는 계층 구조로서 데이터를 분할하고 표현하기 때문에 다양한 공간 분할 문제에서 유용하게 활용된다.
*/

#include <memory>

// #. x, y 좌표계 구조
struct Point
{
	int x;
	int y;

	Point() : x{ 0 }, y{ 0 }
	{

	};
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

// #. 트리에 사용할 노드 구조
struct Node
{
	Point position;
	int data;

	Node() : position{}, data{ 0 }
	{

	}
	Node(Point p, int data)
	{
		this->position = p;
		this->data = data;
	}
};

// #. 쿼드트리
class QuadTree
{
	// 1. 트리의 범위
	Point topLeft;
	Point bottomRight;

	// 2. 현재 노드
	Node* node;

	// 3. 하위 쿼드트리
	//	=> 쿼드트리는 이미지나 공간을 분할하는 재귀적인 구조를 가진다. 
	//	=> 이렇게 구조화된 쿼드트리를 표현하기 위해 각 분할 영역을 나타내는 "하위 쿼드트리"를 사용한다.
	//	=> 전체 공간을 분할하여 북서(NW), 북동(NE), 남서(SW), 남동(SE)의 4개 영역으로 나누고, 
	//	=> 각 영역은 다시 그 영역 내부에서 쿼드트리의 형태로 분할된다. 
	//	=> 그래서 각 영역마다 하위 쿼드트리를 유지하면서 공간을 분할하고 표현한다.
	//	=> 이렇게 하위 쿼드트리를 가리키는 것으로 인해 쿼드트리의 구조가 계층적으로 재귀적형태가 된다.
	std::unique_ptr<QuadTree> nw;
	std::unique_ptr<QuadTree> ne;
	std::unique_ptr<QuadTree> sw;
	std::unique_ptr<QuadTree> se;

public:
	QuadTree();
	QuadTree(Point topLeft, Point bottomRight);
	void Insert(Node* node);
	Node* Search(Point pt);
	bool IsInBound(Point pt);
};

