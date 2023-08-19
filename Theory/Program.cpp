/* ----- < 구조체 메모리 정렬 문제 > ----- */

//#include <iostream>
//struct OneByte
//{
//	char myChar;	// char TYPE : 1 BYTE
//};
//#pragma pack(push, 1)
//struct FiveByte	// #. 생각하기로는 5 BYTE를 차지하는 것이 정상이지만 8 BYTE를 차지한다.
//{
//	char myChar;	// char TYPE : 1 BYTE
//	int myInt;		// int TYPE : 4 BYTE
////		=> 컴파일러가 효율적으로 메모리를 관리하기 위해 구조체 멤버들의 크기를 조절
////		=> myChar 1 BYTE, 3 BYTE Padding, myInt 4 BYTE
////		=> 4바이트 단위로 주소를 관리하면 편하기 때문에 1바이트 뒤에 3바이트의 패딩을 추가한다.
////		=> 그래서 구조체의 실제 크기는 8바이트가 된다.
//};
//#pragma pack(pop)
////	=> 구조체의 바이트를 관리하는 pack(), 1 바이트 단위로 패킹
//int main()
//{
//	std::cout << sizeof(OneByte) << '\n';
//	std::cout << sizeof(FiveByte) << '\n';
//}

/* ----- < 울타리 말뚝 오류 > ----- */

// Off-By-One Error (OBOE), Off-By-One Bug(OBOB), OB1 Error
// 경계선 문제로 발생하는 것으로, 배열과 같이 크기가 정해져 있는 자료 구조에 허용값을 하나 넘어가는 경우를 일컫는 오류이다.

/* 반복문의 조건에서 부등호 실수 */

/*
for(index = 0; index < 5; index++)
{	0 ~ 4까지 5번 반복한다. 만약 5를 실행시키고자 한다면 index <= 5라고 명시해야 한다.
	loop statements
}
*/

/* 인덱스는 0에서 시작하는 것을 오해 */

// FencePost error, Telegraph pole, Lamp-post, Picket Fence Error등 다양한 이름이 있는데 모두 말뚝과 관련된 표현이다.
// 10미터의 울타리가 있는데, 여기에 2미터 간격으로 말뚝을 설치하려면 몇 개가 필요하나? 10 / 2 = 5 라고 생각하기 쉬운데 틀렸다.
// 시작은 0 부터 시작하기 때문에 0 지점에 1개 ~ 2, 4, 6, 8, 10 총 6개가 필요하다.
// N개의 배열은 인덱스 0에서 시작하므로 N - 1이 가장 마지막 값이다.

/* ----- < 컴파일과 링크 > ----- */

/* 헤더파일과 소스파일 */

// c++ 언어는 선언과 정의로 구분되어 있다. 많은 양의 코드를 입력하게 되며, 효율적으로 작성하기 위해 반복되는 작업들을 따로 묶어서 선언하는 경우가 많다.
// 또한 다른 사람이 만들어 둔 편리한 기능들을 가져다 사용할 경우도 있다. 그래서 선언과 정의를 다음과 같이 개별 파일로 묶어 둔다.

// 헤더( header )파일 : .h, .hxx, .hpp, 함수나 변수의 선언을 모아둔 파일, 어떠한 기능이 있는지, 어떤 규격( 매개변수, 이름, 반환값 등 )인지 알려주는 용도
// 소스( source )파일 : .cpp, .c, .cxx, 함수나 변수의 정의를 모아둔 파일, 실제로 기능을 구현하는 곳
// 라이브러리( library )파일 : .lib, .dll, 소스파일을 코드가 아닌 컴파일된 기계어로 제공하는 파일, 주로 자신이 만든 기능을 배포하거나, 프레임워크 처럼 한 번 만들고 자주 수정하지 않는 기능을 포함시킬 때 사용

/* #inclue 지시자( Directive ) */

/*
#pragma once

int Square(int x);
*/

// Square 함수에 대한 선언, 헤더는 크게 사용자가 만든 헤더와 시스템 헤더로 구분된다.
// 시스템 헤더 : c++ 언어 및 Standard Library에서 기본적으로 제공하는 기능들
// 사용자 헤더 : 프로그래머가 직접 만든 헤더

// 첫번째 전처리기 지시자인 #pragma once는 단 한 번만 선언하라는 의미
//		=> #include를 사용하여 MyHeader.h를 여러 소스파일에서 포함시킬 수 있는데, 이럴 경우 중복 선언 에러가 발생할 수 있다.
//		=> 따라서 중복선언을 피하기 위해 #pragma once를 명시해줘야 한다.

/*
#include "MyHeader.h"

int Square(int x)
{
	return x * x;
}	
*/

// #include < ... > : 시스템 헤더 파일을 포함
// #include " ... " : 사용자 헤더 파일을 포함( 현재 소스가 있는 디렉토리, 현재 헤더가 있는 디렉토리, 시스템에 정의되어 있는 디렉토리 )

/* 컴파일과 링크 */

// 기본적으로 헤더 파일은 컴파일에 사용되지 않는다. 대신 소스파일의 전처리기 지시자 #include를 통해 소스 파일에 포함된다.
// 전처리기( Pre-Processor )라고 부르는 이유가 바로 컴파일 이전 단계에 수행되어 소스파일을 수정하기 때문이다.

/*
즉, .cpp를 컴파일 할 때는 내부적으로 다음과 같이 된다.
int Square(int x);

int Square(int x)
{
	return x * x;
}
#include 지시자가 .h를 포함시키기 때문에 헤더파일의 내용이 해당 라인에 삽입되는 것
*/

/*
Main.cpp 역시 마찬가지

iostream 내용들 ...

int Square(int x);

int main()
{
	std::cout<<Square(2)<<std::endl;
	std::cout<<pow(2,2)<<std::endl;
}
주의할 것은 이 단계에서는 함수의 선언만 포함되며, 정의는 .cpp에 속해 있다.
*/

// 1. 빌드 -> 솔루션 정리 : 현재 프로젝트의 중간 파일들을 모두 청소
// 2. .cpp를 열고 빌드 -> 컴파일 : 컴파일 진행( Ctrl + F7 )
// 3. 마찬가지로 Main.cpp를 열고 빌드 -> 컴파일
//		=> 프로젝트 폴더에 Debug라는 폴더가 있고 해당 폴더를 열어보면 컴파일 결과물을 볼 수 있다.
// 컴파일러가 컴파일을 성곡하면 각각 .obj라는 목적어 파일( Object File )을 만들어 둔다.
//		=> 목적어 파일은 헤더 파일의 내용을 포함 시킨 후 다음 단계인 링크에 필요한 정보( 변수 및 함수의 선언+정의 정보 )를 미리 모아두는 것

// 만들어진 목적어 파일을 연동하여 실행파일을 만든 것이 링크

/* 정적 라이브러리( Static Library )와 동적 라이브러리( Dynamic-Link Library ) */

// 컴파일이 모두 끝난 .obj 파일들을 한 번에 묶어서 링크에 사용할 수 있도록 해 주는 것이 라이브러( Static Library )다.

/* 정적 라이브러리 */

// static 즉 변경할 수 없다는 의미
// 한 번 만들어진 라이브러리는 .lib 파일로 사용하는데 이렇게 한 번 만들어진 내부 기능은 변경할 수 있는 방법이 없다.
// 만약 버그 수정이나 기능 추가등으로 인해 내용을 변경해야 한다면 lib 파일을 재배포 하는 방법 밖에 없다.
// 정적 라이브러리는 보통 헤더파일( .h )과 라이브러리 파일( .lib )을 제공하며, 이를 각각 컴파일/링크 단계에 추가해 준다.
// 헤더는 당연히 우리의 소스 코드에 직접 #include 를 통해 지정해 준다.
// 라이브러리는 외부 종속성에 추가해 주는데, 비주얼 스튜디오에서는 프로젝트 옵션의 추가 종속성에 추가
//		=> 프로젝트 -> 속성 -> 링커 -> 입력 -> 추가 종속성 에 추가할 라이브러리 파일을 넣어 주면 된다.

/* 동적 라이브러리 */

// 정적 라이브러리는 내용이 변경되어 라이브러리 파일을 재배포해도 큰 문제가 있다.
//	=> 사용자가 해당 라이브러리를 갱신하기 위해서는 자신의 프로젝트를 다시 빌드해 줘야만 한다.
//		1. 게임의 치명적인 버그 발션
//		2. 디버그 해보니 외부 라이브러리의 버그로 새로운 버전으로 업데이트 필요
//		3. 새로운 라이브러리를 다운 받고 프로젝트 다시 빌드
//		4. 사용자에게 실행파일 재배포
// 위와 같은 흐름이되는데, 개발 프로세스에서 3번 이슈는 치명적
//		=> 상용 프로젝트는 빌드 한 번 하는데 몇 시간씩 걸린다. QA팀은 프로젝트가 빌드되면 전체 검수를 다시 해야 한다.
//		=> 사용자에게 재배포해야 하는 이슈도 크다.

// 이런 문제를 해결하기 위한 것이 실행 시간에 링크가 가능한 동적라이브러리( .dll )
// 링크 과정에서 간단한 정보만을 남겨 놓고, 실행 시간에 그 정보를 이용해 기능을 링크 하는 방식을 사용한다.
//		=> 라이브러리의 기능이 변경되어도 다시 빌드할 필요 없이 간단히 라이브러리만 배포하면 된다.

// 동적 라이브러리는 헤더파일( .h )과 라이브러리파일( .lib ) 그리고 동적라이브러리 파일( .lib )을 제공한다.
// 동적 라이브러리의 .lib 는 정적 라이브러리의 그것과는 달리 내부에 함수 본체와 같은 상세 정보는 없고 오직 정보만을 기록하고 있다.
//		=> 함수 본체는 dll에 들어 있다.

/*
정적 라이브러리					동적 라이브러리
lib 파일						dll 파일
실행 파일만으로 실행			실행파일과 별도의 dll을 이용하여 실행
외부 정보를 참조하지 않기 떄문	실행 시간에 DLL 파일을 뒤져야 하므로
에 빠르다.						느리다.
라이브러리 기능을 수정하기가	라이브러리를 쉽게 업그레이드 가능
어렵다.							하다.
서로 다른 프로젝트에서 사용하	서로 다른 프로젝트에서도 하나의
려면 각각 라이브러리를 링크해	DLL만 있으면 사용이 가능하다.
야만 한다.						
*/

/* ----- < 스택( Stack )과 큐( Queue ) > ----- */

// 컴퓨터는 기본적으로 입력을 받아 계산하고 출력하는 것
//	=> 자료를 입력/출력으로 전달할 때나 계산에 사용할 때의 정보가 매우 중요
//	=> 기본 형인 정수만 사용해서는 표현 범위가 제한 되기 때문에 다양한 방식을 사용하는데 이러한 것을 자료 구조( Data Structure )라 부름

// 이러한 자료 구조 중 가장 기본적이면서 하드웨어, 소프트웨어 구조 모두에서 사용되는 것이 스택과 큐이다.

/* 스택( Stack ) : LIFO - Last In First Out */

// 사전적으로 쌓는다는 의미
// 책을 쌓게 되면, 순서대로 위에서 부터 하나씩 꺼내야 한다. 가장 바닥에 놓인 책을 뽑는 것은 안된다.
// 이러한 특성을 후입선출 또는 Last In First Out, LIFO라 한다.

/*
입력 : Push, 가장 꼭대기에 데이터를 집어 넣음
출력 : Pop, 가장 꼭대기의 데이터를 가져옴

스택은 가장 최근 작업이 중요한 경우에 주로 사용된다. 대표적으로 함수 호출 관리에 스택을 사용한다.
*/

/* 큐( Queue ) : FIFO - First In First Out */

// 사전적으로 줄을 서다라는 의미
// 가장 먼저 온 손님은 그 만큼 오래 기다렸기 때문에 가장 먼저 처리해 줘야 하는 것

/*
입력 : Push, 가장 뒤에 데이터를 집어 넣음
출력 : Pop, 가장 앞의 데이터를 가져옴

큐는 여러 개 실행되는 작업을 순차적으로 처리할 때 사용, 대표적으로 윈도우 메시지 처리 및 프로세스 관리에 사용
*/

/* Overflow & Underflow */

// 컴퓨터 메모리 공간은 한정적이기 때문에 자료 구조들은 한계치가 존재한다.
// Overflow : 준비된 공간을 넘쳐서 데이터를 집어 넣을 때 발생
// Underflow : 준비된 공간에 아무런 값이 없는데, 값을 가져가려고 할 때 발생

/*
가장 유명한 Stack Overflow

void Infinite();

int main()
{
	Infinite();
}

void Infinite()
{
	Infinite();
}
이 프로그램을 실행하면 Stack Overflow 예외가 발생한다.
함수가 호출될 때마다 호출스택( Call Stack )에 함수의 정보를 쌓아 올리는 방식이므로 준비한 스택을 넘쳐 버리게 됨
*/

/* ----- < C/C++ 언어의 Compile 원리 > ----- */

// left <- right : 기본적으로 C++ 언어는 오른쪽에서 왼쪽으로 해석된다.
// a = b = 0 : b 에 먼저 0 을 대입한 후, a 에 b 를 대입하는 순서

// const int a : a is int which is constant( a는 정수이며 상수형 )
// int const a : a is constant int( a는 상수형 정수 )	=> 같은 의미

// const int * a : a is pointer to int which is constant( a 는 포인터로 정수를 가리키며 그 정수는 상수 )
// int * const b : b is constant pointer to int( b 는 상수 포인터로 정수를 가리킨다. )
// int const * c : c is pointer to constant int( c 는 상ㅇ수 정수를 가리키는 포인터 )

// *a = 1 : ERROR( a 가 가리키는 정수는 상수이므로 값을 변경할 수 없다. )
// a++ : OK( a 는 일반 포인터이므로 이동 가능 )
// *b = 1 : OK( b 는 일반 정수를 가리키므로 값을 변경할 수 있다. )
// b++ : ERROR( b 는 상수 포인터이므로 이동 불가능 )
// *c = 1 : ERROR( c 는 상수 정수를 가리키므로 값을 변경할 수 없다. )
// c++ : OK( c 는 일반 포인터이므로 이동 가능 )
// const int * 와 int const * 는 결국 같은 의미

/* ----- < 성능 체크 > ----- */

// 속도( Time ) : 얼마나 더 빨리 실행되는가
// 메모리( Space ) : 얼마나 많은 메모리를 사용하는가

/*
#include <iostream>
#include <chrono>

using Comparison = bool (*)(int, int);

오름차순 함수(int x, int y)
내림차순 함수(int x, int y)

void Sort(int numbers[], int count, Comparison f)
{
	int temp{};
	for(int i=0;i<count;i++)
	{
		for(int j=i+1;j<count;j++)
		{
			if(f(numbers[i],numbers[j]))
			{
				temp = numbers[i];
				numbers[i] = numbers[j];
				nummbers[j]=temp;
			}
		}
	}
}
int main()
{
	int scores[10]{20, 10, 40, 15, 30, 70, 60, 90, 80, 40};

	auto startTime = std::chrono::system_clock::now();
	Sort(scores, NumArray, Asscending);
	auto endTime = std::chrono::system_clock::now();

	auto duration = endTime - statTime;

	std::cout<<"Sort() runds : "<<duration.count()<<"ms\n";
}
Sort() 함수를 실행하기 전에 컴퓨터의 현재 시간을 저장한 다음, 함수를 수행하고 다시 현재 시간을 저장하는 것
이 두 시간의 차이를 구하면, Sort() 함수의 실행시간을 알 수 있다.
하지만, 위 코드를 실행하면 실행할 때마다 다른 시간이 출력된다.
*/

// 실제로 시간 복잡도 측정은 다음과 같은 이유로 물리적으로 측정하기 어렵다.
//	1. 매우 빠른 실행 단위 : 간단히 스탑워치 같은 것으로 해당 함수의 실행 시간을 측정해 볼 수 있겠지만 프로그램의 한 블럭은
//		=> ms( 1/1000초 ) 단위로 매우 빠르게 실행되는 코드 뭉치들의 집합이므로 정확하게 측정하기 어렵다.
//	2. 성능 차이 : 게임용 최상의 데스크탑과 문서 작업용 노트북에서 측정한 값으로 비교할 수도 없다.
//	3. 환경 차이 : 동일한 성능의 PC를 가진 두 사용자가 있다고 가정, A 사용자는 엑셀 10개와 사이버펑크와 같은 무거운 게임을
//		=> 실행 시켜둔 상태이고, B 사용자는 부팅을 방금 마친 상태다. 당연히 A 가 더 느릴 것

/* Complexity */

// 실제로 단위로 측정하는 것이 아니라 코드만을 가지고 정량을 구해볼 수 있다.

/*
#include <iostream>

int Sum(int scores[], int count)
{
	int total{0};

	for(int i=0;i<count;i++) total += scores[i];

	return total;
}
int main()
{
	int socre[5]{20,10,40,5,30};
	std::cout<<Sum(scores,5)<<'\n';
}
시간 복잡도 : 알고리즘의 시작 ~ 끝 까지 소요되는 시간을 분석, 시간을 층정하는 것은 컴퓨터에 따라 다를 수 있기 때문에 수행 횟수를 산출
공간 복잡도 : 알고리즘 연산 도중에 사용되는 메모리를 분석, 바이트 단위로 측정하지 않고 주로 일반적인 단위로 산출

시간 복잡도 구하기
	=> 코드의 각 문장을 횟수 1 로 보고 카운트, Sum의 성능은 코드 2줄 + 반복문 count(n)
공간 복잡도 구하기
	=> 공간은 해당 함수가 얼마나 많은 메모리를 사용하느냐에 따라 결정되므로 바이트 크기와는 상관없이 변수의 개수를 카운트
	=> 함수의 매개변수로 주어지는 값은 무시 Sum의 변수 2개
*/

/*
void Sort(int numbers[], int count, Comparison f)
{
	int temp{};
	for(int i = 0; i < count; i++)
	{
		for(int j = i + 1; j < count; j++)
		{
			if(f(numbers[i], numbers[j]))
			{
				temp = numbers[i];
				numbers[i] = numbers[j];
				nummbers[j] = temp;
			}
		}
	}
}
시간 복잡도 : 반복문 N * N, 반복문 안에 있는 if 문 4줄 N의 제곱 X 4 = 4n^2
공간 복잡도 : 3

T(f(n)) = 4n^2
n=1 : 4 * 1 = 4
n=2 : 4 * 4 = 16
n=3 : 4 * 9 = 36
n=4 : 4 * 16 = 64
n의 크기에 따라 시간 복잡도가 급증한다.
*/

/* Big O 표기법 */

// n 개의 데이터를 처리하는데 A 의 코드는 n, B 의 코드는 n^2 이런 식으로 정량화한 다음 비교하면 A가 더 좋은 방법임을 알 수 있다.

// 구체적인 측정 단위( second, ms 혹은 byte, KByte )를 사용하지 않고 추상적으로 코드의 성능을 표기
// 시간이나 공간이 얼마나 늘어나느냐에 초점을 맞춘다.
// 최악의 경우를 가정한다.

// 곱하기 : 변수를 제외한 상수는 무시
// 더하기 : 가장 높은 차수만 고려
// 다양한 값이 반복되는 경우 : 최악의 경우 선택

/*
T(f(n)) = n + 2 : O(n) 상수 2는 무시, 상수는 n0으로 볼 수 있다. 따라서 가장 높은 차수 n만 남는다.

S(f(n)) = 2 : O(1) 가장 높은 차수를 가진 것만 남겨야 하는데 이미 상수, 이 경우는 1로 변경, 이런 형태를 상수 시간이라 한다.

T(f(n)) = 4n^2 : O(n^2) 곱하기에 사용된 4와 같은 상수 역시 버린다.

S(n) = 3 : O(1)
*/

/* 재귀함수에서의 복잡도 */

/*
#include <iostream>

void CountDown(int n)
{
	if(n==0)
	{
		std::cout<<"Fire!\n";
		return;
	}
	std::cout<<n<<'\n';
	CountDown(n - 1);
}
시간 복잡도 : 함수 내부에서는 기본적으로 모두 상수라서 무시된다. 중요한 것은 재귀호출이 몇 번 불리느냐이다.
		=> n 으로 시작하면 n, n - 1, n - 2, ... 0 까지 총 n 번 이다. O(n)
공간 복잡도 : 재귀호출은 매 호출마다 Call Stack에 하나씩 프레임이 쌓이는 형태,
		=> 메모리에 그대로 남아 있는 상태, 즉 이 경우가 가장 메모리를 많이 차지하는 상황이 되므로 Stack Frame을 계산해 줘야 한다.
		=> n 번 재귀호출이 발생하므로 상수 무시하면 n이 된다. O(n)
*/

/* Big O 패턴 */

/*
O(1) : 상수 - 가장 빠른 알고리즘, 입력과 상관 없이 상수 시간만 소요

O(log n) : 로그식 - 큰 값을 일정한 크기의 영역으로 쪼개서 계산하는 경우에 해당, 바이너리 검색

O(n) : 선형 - 지수가 1이라 1차라고 한다. for, while과 같은 단순 반복문

O(n log n) : 선형 로그 - 큰 값을 일정한 크기의 영역으로 쪼개서 계산한 후 다시 하나로 조립, 큌, 머지

O(n^2) : 2차 다형식 - 지수가 2중 for, while

O(2^n) : 지수식 - 2의 지수 형태

O(n!) : 팩토리얼
*/

/* ----- < POD( Plain Old Data ) > ----- */

// 단순한 메모리 구조를 가지는 객체 : C 언어에서 제공되는 타입들
//		=> POD의 장점은 원본 메모리에서 다른 메모리로 복사나 이동이 매우 쉬워서 컴퓨터 성능에 큰 부담이 없다는 점이다.

/*
C++ 에서는 POD 를 다음과 같은 의미론( Semantic )으로 정의해 두었다.
	Standard Layout Type( 표준 레이아웃 타입 ) : C 언어와 같은 레이아웃을 가지고 있다.
	Trivial Type( 간단한 타입 ) : 사용자가 정의한 매우 간단한 자료 구조를 말한다.
POD는 Tivial Type만 가능하며, 성능과 관련되어 있다.

그런데 사용자가 클래스에 생성자를 붙이면 Trivial Type이 아니게 된다.

#include <iostream>

class ClassA
{
public:
	ClassA() {}
};
class ClassB
{
public:
	ClassB() = default;
};
int main()
{
	std::cout << std::is_trivial<ClassA>::value << std::is_pod<ClassA>::value << '\n';
	std::cout << std::is_trivial<ClassB>::value << std::is_pod<ClassB>::value << '\n';
}

ClassA 는 사용자가 기본 생성자를 작성해 줬고, ClassB 는 = default 를 사용해 암시적 기본 생성자라는 것을 명확하게 표시하였다.
POD가 되기 위해서는 = default 키워드로 암시적 기본 생성자를 명시해야된다.
*/

/* ----- < 무명 객체( Anonymous Object ) > ----- */

/*
#include <iostream>

int Square(int x)
{
	return x * x;
}
int main()
{
	int x{ 2 };
	std::cout<<Square(x)<<'\n';
}

return x * x; 일반 타입 역시 객체라고 생각해 보면, x * x를 담아 둘 수 있는 임시 객체가 필요하다.
		=> 계산 결과를 저장한 다음 반환해야 하니 int temp = x * x; return temp; 와 같은 작업이 있어야 한다.
컴파일러 내부에서는 이 작업이 이루어 진다. 임시로 사용하는 객체로 해당 코드 이외에는 사용할 필요가 없으므로, 굳이 변수명을 붙이지 않고 사용한다.
		=> 이를 이름 없는 객체라 부른다.

Square(x) 에서 x 가 리터럴 2로 치환
인자 2가 Square(int x) 의 매개변수 x 에 복사
x * x 를 무명객체에 저장
무명 객체 반환 & 소멸

반환값 이외에도 대부분의 연산식에서도 무명객체가 사용된다.
*/

/*
class MyClass
{
public:
	int mValue;
	MyClass(int value) : mValue{ value }
	{
		std::cout<<"[MyClass()] : "
			<< mValue
			<< '\n';
	}
	MyClass operator+(const MyClass& c)
	{
		return MyClass{ mValue + c.mValue };
	}
};
int Square(MyClass c)
{
	return c.mValue * c.mValue;
}
int main()
{
	MyClass c1{ 1 }, c2{ 2 };

	std::cout<<"-----\n";
	Square(c1 + c2);

	std::cout<<"-----\n";
	std::cout<<(c1 + c2).mValue<<'\n';

	std::cout<<"-----\n";
	MyClass c3{ c1 + c2 };
}

실행 결과
[MyClass()] : 1
[MyClass()] : 2
-----
[MyClass()] : 3
-----
[MyClass()] : 3
3
-----
[MyClass()] : 3
실제로 생성한 c1, c2 외에도 생성자가 추가로 불리었다. 이들은 무명 객체이다.
+ 연산자를 오버로딩한 코드에서 새로운 객체를 만들어서 반환
*/