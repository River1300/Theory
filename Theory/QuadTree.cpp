#include <cmath>
#include "QuadTree.h"

QuadTree::QuadTree() : topLeft{ Point() }, bottomRight{ Point() }, node{ nullptr },
						nw{ nullptr }, ne{ nullptr }, sw{ nullptr }, se{ nullptr }
{
}

QuadTree::QuadTree(Point topLeft, Point bottomRight) : QuadTree()
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
}

void QuadTree::Insert(Node* node)	// 주어진 노드를 현재 쿼드트리에 삽입하는 함수
{									// 새로운 노드를 추가하거나 기존에 추가된 노드를 관리하는 역할
	// 1. 새로운 노드를 삽입하려고 호출하였는데 그 노드가 nullptr인 경우에는 아무런 작업을 하지 않고 함수를 종료한다.
	if (node == nullptr)
	{
		return;
	}

	// 2. 현재 영역이 아니면 무시
	//	=> 쿼드트리는 공간을 나누어 하위 영역에 대한 정보를 재귀적으로 구성하는 구조이다. 
	//	=> 각 노드가 특정 영역을 나타내는데, 만약 노드의 영역이 현재 쿼드트리의 범위 밖에 있다면 
	//	=> 그 노드는 쿼드트리의 구조에 포함되지 않아야 한다.
	if (!IsInBound(node->position))
	{
		return;
	}

	// 3. 현재 영역이 단위 영역( 1 X 1 )이라면 더 이상 분할 불가능, 각 노드는 특정 영역을 나타내며, 
	//	=> 이 영역이 최소 단위인 1x1 크기가 되었을 때 해당 노드는 더 이상 분할되지 않고 값을 가지게 됩니다.
	if (std::abs(topLeft.x - bottomRight.x) <= 1 &&
		std::abs(topLeft.y - bottomRight.y) <= 1)
	{
		// 1. 해당 노드가 아직 값이 없는 경우, 현재 노드에 값을 넣어준다. 
		//	=> 그리고 나서 반환, 쿼드트리에서 해당 노드 이후에 더 이상 분할하지 않고 노드를 담당하도록 표시
		if (this->node == nullptr)
		{
			this->node = node;
		}
		return;
	}

	// 4. 서쪽
	//	=> 각 노드의 영역을 네 개로 분할하고, 그 분할된 영역에 대한 하위 쿼드트리를 만들어 각각 재귀적으로 처리
	if ((topLeft.x + bottomRight.x) / 2 >= node->position.x)	// 중점을 기준으로 왼쪽( 서쪽 )
	{
		if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)	// 중점을 기준으로 아래쪽( 남쪽 )
		{
			// 1. 남서
			//	[ ][ ]
			//	[*][ ]
			if (sw == nullptr)	// 현재 노드의 서쪽 하위 영역
			{
				sw = std::make_unique<QuadTree>(Point(topLeft.x, (topLeft.y + bottomRight.y) / 2),
					Point((topLeft.x + bottomRight.x) / 2, bottomRight.y));
			}
			sw->Insert(node);
		}
		else
		{
			// 2. 북서
			//	[*][ ]
			//	[ ][ ]
			if (nw == nullptr)
			{
				nw = std::make_unique<QuadTree>(Point(topLeft.x, topLeft.y),
					Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2));
			}
			nw->Insert(node);
		}
	}
	// 5. 동쪽
	else
	{
		if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)
		{
			// 1. 남동
			//	[ ][ ]
			//	[ ][*]
			if (se == nullptr)
			{
				se = std::make_unique<QuadTree>(Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2),
					Point(bottomRight.x, bottomRight.y));
			}
			se->Insert(node);
		}
		else
		{
			// 2. 북동
			//	[ ][*]
			//	[ ][ ]
			if (ne == nullptr)
			{
				ne = std::make_unique<QuadTree>(Point((topLeft.x + bottomRight.x) / 2, topLeft.y),
					Point(bottomRight.x, (topLeft.y + bottomRight.y) / 2));
			}
			ne->Insert(node);
		}
	}
}

Node* QuadTree::Search(Point pt)
{
	// 1. 현재 영역이 아니면 무시
	if (!IsInBound(pt))
	{
		return nullptr;
	}

	// 2. node 에 값이 있으면 더 이상 분할 불가능한 단위 영역
	if (node != nullptr)
	{
		return node;
	}

	// 3. 서쪽
	if ((topLeft.x + bottomRight.x) / 2 >= pt.x)
	{
		// 1. 북서
		if ((topLeft.y + bottomRight.y) / 2 >= pt.y)
		{
			if (nw == nullptr)
			{
				return nullptr;
			}
			return nw->Search(pt);
		}
		// 2. 남서
		else
		{
			if (sw == nullptr)
			{
				return nullptr;
			}
			return sw->Search(pt);
		}
	}
	// 4. 동쪽
	else
	{
		// 1. 북동
		if ((topLeft.y + bottomRight.y) / 2 >= pt.y)
		{
			if (ne == nullptr)
			{
				return nullptr;
			}
			return ne->Search(pt);
		}
		// 2. 남동
		else
		{
			if (se == nullptr)
			{
				return nullptr;
			}
			return se->Search(pt);
		}
	}

	return nullptr;
}

bool QuadTree::IsInBound(Point pt)	// 주어진 좌표가 현재 쿼드트리의 범위 내에 있는지 여부를 판단하는 함수
{									// 쿼드트리의 각 노드는 특정 영역을 나타내는데, 그 영역은 왼쪽 위의 점과 오른쪽 아래의 점이다.
	// 1. 주어진 좌표 pt의 x값이 topLeft.x 와 bottomRight.x 사이에 있으며, 
	//	=> y값이 topLeft.y 와 bottomRight.y 사이에 있는지를 확인하여 해당 좌표가 쿼드트리의 범위 내에 있는지 여부를 판단
	return (pt.x >= topLeft.x && pt.x <= bottomRight.x && pt.y >= topLeft.y && pt.y <= bottomRight.y);
}
