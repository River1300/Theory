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

void QuadTree::Insert(Node* node)	// �־��� ��带 ���� ����Ʈ���� �����ϴ� �Լ�
{									// ���ο� ��带 �߰��ϰų� ������ �߰��� ��带 �����ϴ� ����
	// 1. ���ο� ��带 �����Ϸ��� ȣ���Ͽ��µ� �� ��尡 nullptr�� ��쿡�� �ƹ��� �۾��� ���� �ʰ� �Լ��� �����Ѵ�.
	if (node == nullptr)
	{
		return;
	}

	// 2. ���� ������ �ƴϸ� ����
	//	=> ����Ʈ���� ������ ������ ���� ������ ���� ������ ��������� �����ϴ� �����̴�. 
	//	=> �� ��尡 Ư�� ������ ��Ÿ���µ�, ���� ����� ������ ���� ����Ʈ���� ���� �ۿ� �ִٸ� 
	//	=> �� ���� ����Ʈ���� ������ ���Ե��� �ʾƾ� �Ѵ�.
	if (!IsInBound(node->position))
	{
		return;
	}

	// 3. ���� ������ ���� ����( 1 X 1 )�̶�� �� �̻� ���� �Ұ���, �� ���� Ư�� ������ ��Ÿ����, 
	//	=> �� ������ �ּ� ������ 1x1 ũ�Ⱑ �Ǿ��� �� �ش� ���� �� �̻� ���ҵ��� �ʰ� ���� ������ �˴ϴ�.
	if (std::abs(topLeft.x - bottomRight.x) <= 1 &&
		std::abs(topLeft.y - bottomRight.y) <= 1)
	{
		// 1. �ش� ��尡 ���� ���� ���� ���, ���� ��忡 ���� �־��ش�. 
		//	=> �׸��� ���� ��ȯ, ����Ʈ������ �ش� ��� ���Ŀ� �� �̻� �������� �ʰ� ��带 ����ϵ��� ǥ��
		if (this->node == nullptr)
		{
			this->node = node;
		}
		return;
	}

	// 4. ����
	//	=> �� ����� ������ �� ���� �����ϰ�, �� ���ҵ� ������ ���� ���� ����Ʈ���� ����� ���� ��������� ó��
	if ((topLeft.x + bottomRight.x) / 2 >= node->position.x)	// ������ �������� ����( ���� )
	{
		if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)	// ������ �������� �Ʒ���( ���� )
		{
			// 1. ����
			//	[ ][ ]
			//	[*][ ]
			if (sw == nullptr)	// ���� ����� ���� ���� ����
			{
				sw = std::make_unique<QuadTree>(Point(topLeft.x, (topLeft.y + bottomRight.y) / 2),
					Point((topLeft.x + bottomRight.x) / 2, bottomRight.y));
			}
			sw->Insert(node);
		}
		else
		{
			// 2. �ϼ�
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
	// 5. ����
	else
	{
		if ((topLeft.y + bottomRight.y) / 2 >= node->position.y)
		{
			// 1. ����
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
			// 2. �ϵ�
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
	// 1. ���� ������ �ƴϸ� ����
	if (!IsInBound(pt))
	{
		return nullptr;
	}

	// 2. node �� ���� ������ �� �̻� ���� �Ұ����� ���� ����
	if (node != nullptr)
	{
		return node;
	}

	// 3. ����
	if ((topLeft.x + bottomRight.x) / 2 >= pt.x)
	{
		// 1. �ϼ�
		if ((topLeft.y + bottomRight.y) / 2 >= pt.y)
		{
			if (nw == nullptr)
			{
				return nullptr;
			}
			return nw->Search(pt);
		}
		// 2. ����
		else
		{
			if (sw == nullptr)
			{
				return nullptr;
			}
			return sw->Search(pt);
		}
	}
	// 4. ����
	else
	{
		// 1. �ϵ�
		if ((topLeft.y + bottomRight.y) / 2 >= pt.y)
		{
			if (ne == nullptr)
			{
				return nullptr;
			}
			return ne->Search(pt);
		}
		// 2. ����
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

bool QuadTree::IsInBound(Point pt)	// �־��� ��ǥ�� ���� ����Ʈ���� ���� ���� �ִ��� ���θ� �Ǵ��ϴ� �Լ�
{									// ����Ʈ���� �� ���� Ư�� ������ ��Ÿ���µ�, �� ������ ���� ���� ���� ������ �Ʒ��� ���̴�.
	// 1. �־��� ��ǥ pt�� x���� topLeft.x �� bottomRight.x ���̿� ������, 
	//	=> y���� topLeft.y �� bottomRight.y ���̿� �ִ����� Ȯ���Ͽ� �ش� ��ǥ�� ����Ʈ���� ���� ���� �ִ��� ���θ� �Ǵ�
	return (pt.x >= topLeft.x && pt.x <= bottomRight.x && pt.y >= topLeft.y && pt.y <= bottomRight.y);
}
