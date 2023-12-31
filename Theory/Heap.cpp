/* ----- < Heap & Heap Sort > ----- */

/* Heap */

// 최댓값, 최솟값을 효율적으로 찾기 위해 원소들을 완전한 이진트리( Complete Binary Tree )에 집어 넣은 구조를 힙( Heap )이라 부른다.
// 컴파일러가 전역 변수 및 동적 변수를 저장하기 위한 힙( Heap : 마구 쌓아 놓다라는 의미 )과는 다른 의미이다.

// Max Heap : 부모의 값이 항상 자식들보다 큰 경우
// Min Heap : 부모의 값이 항상 자식들보다 작은 경우

/*
Max Heap
				[1] : 최초의 데이터
			[2] : 힙 구조는 왼쪽 부터 쌓아야 한다.	=> 부모가 값이 커야 하므로 두 개의 값을 서로 바꾼다.

				[2]
			[1]		[3] : 왼쪽에 자식이 있으니 오른쪽에 추가한다. => 부모가 커야 하므로 값을 바꾼다.

				[3]
			[1]		[2]
		[4] : 리프노드가 가늑 찼으므로 다시 가장 좌측의 자식으로 만들어 준다. => 부모가 더 커야 하므로 바꿔준다.

				[3]
			[4]		[2]
		[1] : 다시 한 번 부모를 살펴 보고 부모가 더 커야 하므로 바꿔준다.

				[4]
			[3]		[2]
		[1]

				[4]
			[3]		[2]
		[1]		[5] : 가장 좌측 노드가 채워졌으니 그 옆으로 새로운 리프를 추가한다.

				[5]
			[4]		[2]
		[1]		[3]	: 이전 과정과 마찬가지로 큰 값의 부모로 교체한다.

1. 원소를 추가
	a. 리프 노드 탐색
		ㄱ. 자식이 없으면 왼쪽에 추가
		ㄴ. 자식이 하나면 오른쪽에 추가
		ㄷ. 자식이 둘이면 다음 이웃( 리프 )으로
2. 추가된 원소와 그 부모 노드를 비교
	a. Heap 규칙에 맞지 안으면 부모와 교환
	b. 규칙에 맞을 때 까지 a 번 반복
*/

// 실제 Heap 구조는 트리보다 배열을 사용한다.
// [5][4][2][1][3]
// Heap 의 특성상 마지막을 제외한 모든 레벨에 노드가 들어 있고, 항상 왼쪽부터 채워지므로 레벨 순서로 배열을 채우는 것이다.

/*
#. 왼쪽 자식의 인덱스 = 부모의 인덱스 * 2
#. 오른쪽 자식의 인덱스 = ( 부모의 인덱스 * 2 ) + 1
#. 부모의 인덱스 = ( 자식의 인덱스 ) / 2

1: [1] : 빈칸에 원소를 넣으면 된다.
2: [1][2] : 왼쪽/오른쪽에 자식이 없으므로 왼쪽에 추가한다. => 가장 마지막 인덱스에 추가
	=> [2][1]
3: [2][1][3] : 추가
	=> [3][1][2] : 부모보다 큰 값이므로 치환
4: [3][1][2][4] : 추가
	=> [3][4][2][1] : 부모보다 큰 값이므로 치환
	=> [4][3][2][1] : 부모보다 큰 값이므로 치환
5: [4][3][2][1][5] : 추가
	=> [4][5][2][1][3] : 부모보다 큰 값이므로 치환
	=> [5][4][2][1][3] : 부모보다 큰 값이므로 치환
*/

//#include <iostream>
//#include <vector>
//
//class Heap
//{
//	std::vector<int> mHeap;
//
//public:
//	void Insert(int value)	// 새로운 값을 힙에 삽입하는 함수, 삽입할 값은 맨 끝에 추가하고, 그 값을 부모 노드들과 비교하여 조건에 맞게 위치를 조정
//	{	// 1. 삽입할 값을 배열의 끝에 추가
//		mHeap.push_back(value);
//		// 2. 현재 추가한 값의 인덱스를 변수에 저장
//		int i = mHeap.size() - 1;
//		// 3. 추가된 노드의 부모 노드의 인덱스를 변수에 저장
//		int half = (i - 1) / 2;
//		// 4. 추가한 값이 부모 값보다 큰지 확인
//		while (i != 0 && value > mHeap[half])
//		{
//			mHeap[i] = mHeap[half];
//			mHeap[half] = value;
//			i = half;
//
//			half = (i - 1) / 2;
//		}
//	}
//
//	void Print()
//	{
//		for (auto& e : mHeap)
//		{
//			std::cout << e << ' ';
//		}
//	}
//};
//
//int main()
//{
//	Heap h;
//
//	h.Insert(1);
//	h.Insert(2);
//	h.Insert(3);
//	h.Insert(4);
//	h.Insert(5);
//
//	h.Print();
//}

// Heap 구조는 가장 상단에 최대값/최소값을 가지는 자료구조이다. 따라서 데이터를 꺼낼 땐 최상단의 원소를 꺼내는 방식이다.
// 이 때, 중요한 것은 남아 있는 자료들 역시 Heap 을 만족해야 한다는 것이다.

/*
				[5]
			[4]		[2]
		[1]		[3]	: 우선 5를 지우고 나면 트리 형태가 깨진다.
					=> 그러므로 루트에서 지우지 말고 리프에서 지우기 위해 루트와 마지막 원소( 3 )를 바꾼다.

				[3]
			[4]		[2]
		[1]		[5] : 현재 상태는 힙 규칙에 맞지 않으니 힙 규칙에 맞도록 수정해야 한다.
					=> 우선 루트와 자식들의 값을 비교해서 큰 값이 있으면 위로 올린다.

				[4]
			[3]		[2]
		[1]		[5]

1. 루트와 마지막 원소를 치환한다.
2. 루트에서 힙 규칙에 맞게 수정한다.
	a. Heap 규칙에 맞게 수정한다.
	b. 규칙에 맞을 때 까지 a 번 반복
*/

//#include <iostream>
//#include <vector>
//
//class Heap
//{
//	std::vector<int> mHeap;
//
//public:
//	void Insert(int value)
//	{
//		mHeap.push_back(value);
//
//		unsigned long i = mHeap.size() - 1;
//		unsigned long half = (i - 1) / 2;
//
//		while (i != 0 && value > mHeap[half])
//		{
//			mHeap[i] = mHeap[half];
//			mHeap[half] = value;
//			i = half;
//
//			half = (i - 1) / 2;
//		}
//	}
//
//	int Pop()
//	{
//		// 1. 힙이 비어있을 경우, 0을 반환
//		if (mHeap.size() == 0)
//		{
//			return 0;
//		}
//		// 2. 최대 값을 추출하면서 힙의 특성을 유지한다.
//		int item = mHeap.front();
//		mHeap[0] = mHeap.back();
//		mHeap.pop_back();
//
//		int i{};
//		// 3. 루트 노드부터 시작하여 자식 노드 중 더 큰 값을 찾아 힙 특성을 만족하도록 노드를 조정
//		while (i < mHeap.size())
//		{	// 1. 현재 노드의 자식 중에서 더 큰 값을 가진 자식의 인덱스를 계산한다.
//			unsigned long big_child = (i * 2) + 1;
//			// 2. 현재 노드의 자식이 없는 경우 탈출
//			if (big_child >= mHeap.size())
//			{
//				break;
//			}
//			// 3. 현재 노드의 오른쪽 자식이 왼쪽 자식 보다 더 큰 값일 경우, 인덱스를 오르쪽 자식으로 변환
//			if (big_child + 1 < mHeap.size() && mHeap[big_child] < mHeap[big_child + 1])
//			{
//				big_child++;
//			}
//			// 4. 현재 노드의 값이 자식 중 가장 큰 값보다 크거나 같다면 힙의 특성을 만족하고 조정이 필요하지 않음
//			if (mHeap[i] >= mHeap[big_child])
//			{
//				break;
//			}
//			std::swap(mHeap[i], mHeap[big_child]);
//			// 5. i를 big_child로 업데이트하여 다음 레벨의 자식 노드로 이동
//			i = big_child;
//		}
//		return item;
//	}
//};

/* Heap Sort */

// Heap 자료구조의 루트가 항상 최댓값 혹은 최솟값을 가지고 있다는 점을 사용해 정렬로 사용할 수 있다.
// Heapify

/*
Heapify는 주로 힙( Heap ) 데이터 구조를 유지하거나 재구성하는 작업을 의미한다. 
힙은 일종의 완전 이진 트리( Binary Tre e) 구조로서, 최댓값이나 최솟값을 빠르게 찾아내는 데 사용된다. 
Heapify는 이러한 힙의 특성을 유지하면서 데이터를 삽입하거나 삭제할 때 필요한 작업

Insertion( 삽입 ) : 힙에 새로운 요소를 추가할 때, 힙의 특성을 유지하기 위해 Heapify 작업이 수행 
	=> 일반적으로 새로운 요소를 힙의 맨 끝에 추가한 후, 부모 노드와 값을 비교하면서 적절한 위치로 올바른 순서로 조정해 나간다.
Deletion( 삭제 ) : 힙에서 최댓값이나 최솟값을 삭제할 때도 Heapify 작업이 필요 
	=> 삭제 후에 힙의 특성을 유지하기 위해 빈 자리에 다른 값을 넣고, 그 값을 아래쪽으로 조정해나가면서 힙의 구조를 복원한다.

Heapify 작업은 보통 상향식( Bottom-up )으로 수행된다. 
즉, 힙의 마지막 레벨부터 시작하여 위쪽으로 올라가며 부모와 자식 노드들을 비교하고 교환하여 힙의 특성을 만족시킨다. 
이렇게 함으로써 새로운 요소를 추가하거나 기존 요소를 삭제할 때도 효율적인 힙 구조를 유지할 수 있다.
*/

/* STL */

// std::make_heap() : [first, end) 범위의 원소를 힙으로 만들어 준다.
//					=> 기본 값은 std::less<>로 최대힙이다.
// std::push_heap() : Heap 에 원소를 추가한다.
//					=> 컨테이너가 Heap 이어야만 한다.
//					=> 실제 원소 추가는 컨테이너의 기능을 사용해야 한다.
// std::pop_heap() : Heap 에서 원소를 빼낸다.
//					=> 컨테이너가 Heap 이어야 한다.
//					=> 실제 원소 제거는 컨테이너의 기능을 사용해야 한다.
// std::sort_heap() : Heap 원소를 정렬한다.
//					=> 컨테이너가 Heap 이어야 한다.
//					=> 정렬을 하고 나면 더 이상 Heap 이 아니게 된다.

//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//int main()
//{
//	std::vector<int> v{ 1,2,3,4,5 };
//
//	// Max Heap
//	std::make_heap(v.begin(), v.end());
//
//	for (auto& e : v)
//	{
//		std::cout << e << '\n';
//	}
//
//	std::cout << "------------------\n";
//
//	// Min Heap
//	v = { 4,2,5,1,3 };
//
//	std::make_heap(v.begin(), v.end(), std::greater<>());
//
//	for (auto& e : v)
//	{
//		std::cout << e << '\n';
//	}
//}