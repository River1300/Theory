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

/* ----- < Relationship > ----- */

// 한 명의 친구를 정의하려면 그 친구 개인의 특석이나 능력을 묘사해야 할 뿐 아니라, 다른 사람과의 관계 역시 매우 중요하다.
// 사람과 사람의 관계는 매우 다양하며 심지어 소속된 학교, 동아리에 따라 복잡하게 펼쳐질 것
// 즉, 그 친구가 맺고 있는 관계들을 알아둬야 더욱 더 인간관계를 넓히고 원활한 사회생활을 할 수 있다.

// OOP는 현실 세계의 오브젝트를 프로그램에 도입한 개념이므로 마찬가지로 오브젝트들의 관계를 표현할 수 있다.
// 클래스의 개념 자체가 워낙 복잡하고 기능도 많기 때문에 실제로 게임 제작할 때 어떤 구조로 클래스를 설계하는 지 고민되는 경우가 있다.

// A, B 오브젝트가 있을 때 그 둘의 관계

/*
is-part-of	: Composition( 결합 )
has-a		: Aggregation( 집단화 )
use-a		: Association( 연관화 )
is-a		: Generalization( 일반화 ) 혹은 Specialication( 특수화 )
*/

/* is-part-of( Composition ) */

// 자동차를 살펴 보면, 자동차는 엔진을 가지고 있는데 엔진 역시 매우 복잡한 구조를 가지고 있다.
// 효율적으로 자동차를 생산하기 위해서는 엔진 역시 개별 공정으로 생산한 후 마지막 조립 공정에서 조립하는 방식을 취하게 된다.
// 사용자의 입장에서 바라보면 엔진은 필수 부품이라 자동차를 구매한 후 폐차할때까지 교체하지 않고 사용하게 된다.

/*
객체로 바라보면 복잡한 객체( 자동차 )는 조금 더 간단한 객체( 엔진 )로 구성되어 있다고 할 수 있으며, 이러한 관계를 A is-part-of B 라는 관계라 부른다.
	A 는 B 의 일부 구성 요소
	A 는 한 번에 하나의 객체에만 존재
	A 는 B 에 의해 관리됨
	A 는 B 의 존재를 알지 못함

class Status
{
public:
	int mHP;
	int mMP;
};
class Player
{
	Status mStatus;
};

플레이어 클래스는 매우 다양한 속성을 가지고 있지만 그 중 능력치 역시 매우 복잡한 구조일 것이다.
이런 상황에서는 능력치를 다른 클래스로 만들어서 멤버로 가지고 있는 것이 효율적일 것이다.

Status 는 Player 의 멤버 중 하나 이다.
Player 는 능력치, 아이템, 장비, 스킬 등 다양한 속성을 가지고 있으며 Status 는 속성 중 하나다.
Player 인스턴스를 여러 개 만들어도 Status 는 각각 독립적으로 객체에 존재한다.
warrior 의 능력치가 wizard 의 능력치가 될 수 없다.
Status 의 Life-Cycle 은 Player 에 의해 생성되고 관리된다.
Player 가 생성되면 같이 생성되고 소멸될 때 같이 소멸된다.
Status 는 Player 접근할 수 없다.
능력치는 체력, 마력 등 수치 정보들이므로 Player의 정보가 필요하지 않느다.
*/

/* has-a( Aggregation ) */

// 자동차는 타이어를 4개 가지고 있다. 기본적인 관계는 엔진과 같지만 타이어는 마모되면 언제든 교체해야 한다.
//		=> 타이어의 수명은 별도록 관리되어야 한다.

/*
	B 는 A 의 일부 구성 요소
	B 는 한 번에 여러 오브젝트에 소속
	B 는 A 에 의해 관리되지 않음
	B 는 A 의 존재를 알지 못함

class Player
{
};
class Auction
{
	Player* mPlayers;
};
RPG 게임에서는 여러 플레이어들의 거래를 도와주는 경매장 시스템이 있다. 경매장에서 거래를 시작하면 해당 플레이어를
목록에 추가해야 하므로 플레이어들의 배열과 같은 형태에 추가하거나 삭제해서 관리 해줘야 한다.

Player 는 Auction 의 일부 구성 요소
Player 는 한 번에 여러 오브젝트에 소속
	와우 같은 경우는 지역 별 경매장이 존재하고 여기에 모두 다 아이템을 판매할 수 있다.
Player 는 Auction 에 의해 관리되지 않음
	경매장이 폐괘된다고 플레이어가 사라지면 않된다.
Player 는 Auction 의 존재를 알지 못함
	플레이어는 낙찰된 아이템이나 금액을 우편으로 받기 때문에 굳이 경매장의 세부 정보를 알 필요가 없다.
*/

/* use-a( Association ) */

// 운전자는 집에 있으면 차는 면허만 있다면 온 가족이 사용할 수 있다.

/*
B 는 A 와 관련이 없음
B 는 한 번에 여러 오브젝트에 사용
B 가 A 에 의해 관리되지 않음
B 는 A 의 존재를 알 수도 있고 모를 수도 있음

class Potion
{
public:
	int mCount;
	int mRecovery;
};
class Player
{
	Potion* pPotion;
};
Potion 은 Player 와 관련이 없음
	물약은 체력 회복만 해주면 되므로 플레이어와 상관 관계가 없다.
Potion 은 한 번에 여러 오브젝트에 소속
	파티원이 여러명일 경우는 각 파티원마다 물약을 가지고 있어야 한다.
Potion 은 Player 에 의해 관리되지 않음
	파티원이 한 명 사망해도 다른 파티원은 여전히 물약을 가지고 있어야 한다.
Potion 은 Player 의 존재를 알 수도 있고 모를 수도 있음
	고정 회복량을 가지는 물약은 Player 를 몰라도 되지만, 최대 체력 비율로 회복해 주는 물약 이라면 Player 의 최대 체력을 알아야 함
*/

/* is-a( Generalization, Specialication ) */

// 현실에는 다양한 종류의 자동차들이 있다. 다양한 차들을 효율적으로 관리하기 위해서는 공통적으로 가지는 특성을 묶어서 상위 개념을 만드는 것이 좋다.
// 차로 기능하기 위한 필수 개념인 엔진, 타이어, 문 등의 정보들을 묶어서 재활용할 수 있도록 일반화( Generalization ) 해 준다.

// 일반화된 개념을 사용하면 다양한 차종을 만들 때 편리하다. 중복되는 속성을 묶어 노았으니 이를 사용한 후 각 제조사별 고유한 기능만
// 추가하면 다양한 차종을 찍어낼 수 있을 것인데 이를 특수화( Specialication )이라 부른다.

/* ----- < 멀티 태스킹 > ----- */

// 이전에는 DOS(Disk Operating System)라는 시스템이 있었다.
//	=> 이 환경은 텍스트 기반으로, 한 번에 하나의 프로그램을 실행하는 방식이었다.

// 그래픽 기반( GUI: Graphical User Interface )으로 대격변을 일으킨 것은 윈도우라는 환경( Windows 3.1, Apple LISA )
// 이런 형태로 운영체제가 발전하다 보니, 프로그램이 여러 개 화면에 동시에 실행되는 기술이 필요해 졌다.
//		=> 이렇게 여러( multi ) 작업( task )을 실행하는 것이 멀티 태스킹( multi-tasking )이다.

// 컴퓨터는 기본적으로 주어진 입력을 계산하여 출력하는 순차 작업이다. 따라서 여러개가 실행되는 형태를 흉내내려면, 간단히 줄을 세우고
// 순서대로 작업을 관리하면 된다. 그러다가 급한 작업( 사용자가 활성화 한 윈도우 )이 요청되면 가장 앞으로 빼서 우선 처리를 하면 된다.
// 이런 처리가 빠르게 진행되기 때문에 우리 눈에는 동시에 프로그램이 실행되는 것 처럼 보이는 것 뿐이다.
//		=> 이러한 것을 스케쥴링( scheduling )이라 부른다.

/* 프로세스( Process ) */

// 운영체제의 작업 단위는 프로세스( Process )다. 윈도우에서 Ctrl + Shift + ESC 를 누르면 작업 관리자가 나오면 가장 첫번째 탭이 프로세스 목록이다.
// 우리가 제작하는 프로그램들은 하드 디스크에 저장되어 있으며, 이를 실행하면 프로세스가 되어 메모리에 등록되며 OS에서 관리되기 시작한다.

// 프로세스는 사용자의 입력에 의해 휴면/활성 상태가 된다. 이런 상태 변화를 위해서는 각 프로세스의 현재 진행 상태를 저장해 뒀다가 복원해야 한다.
// 이러한 것을 컨텍스트( Context )라 부르고 작업 전환( Alt + Tab )이 일어나면 현재 프로세스와 이전 프로세스의 컨텍스트를 교체해 주는 방식으로 진행된다.
//		=> 이를 컨텍스트 스위칭( Context Switching )이라 한다.

// 프로그램에서 처리하는 양이 많으면 많을 수록 이런 컨텍스트 스위칭은 컴퓨터를 느리게 하는 원인이 된다.
// 게임을 하다 Alt + Tab을 누르면 다른 프로그램보다 늦게 전환될 때가 있는데, 내부에서는 이러한 컨텍스트 스위칭이 일어나기 때문이다.

/* 스레드( Thread ) */

// MMORPG 에서는 수 많은 플레이어들이 서로 이동하는데, 이러한 이동 정보는 네트워크를 통해 전달된다.

/*
while( 네트워크 데이터 수신 완료 )
{
	데이터 수신
}
player.Move();

이렇게 작성하면? while로 인해 한 명의 움직이기 위해서는 게임의 모든 것이 다 멈춰 버린다.

하나의 프로세스에서도 당연히 동시에 처리할 필요가 있다. 이러한 것을 스레드( Thread )라고 부른다.
		=> 엄밀하게는 동시가 아니라 스케쥴링이다.
		=> 멀티코어 CPU는 각각의 코어에 스레드를 실행하여 조금 더 병렬처리에 가까워지긴 하였다.
이러한 스레드는 기본적으로 프로세스의 자원을 공유하는 방식이므로 ContextSwitiching 같은 오버헤드는 없지만, 공유하는 데이터를 여러 스레드가 동시에 접근하기 때문에 다양한 문제가 발생한다.
*/

/* 교착 상태 */

// 사다리 하나와 두 명의 작업자가 있다.
// 한 명은 위에서 아래로, 한 명은 아래에서 위로 하나의 사다리를 통해 이동하려고 한다면 다른 한 사람은 기다려야 한다.
//		=> 그런데 만약 동시에 이동을 한다면? 두 사람은 서로 다른 사람이 비켜주길 기다리고, 기다림은 끝나지 않는다.
//			=> 이러한 상태를 교착상태( deadlock )라 부른다.
// 스레드는 자원을 공유하기 때문에 이런 데드락 상태를 주의해야 한다. 현재까지 교착상태를 해결하는 알고리즘은 없다. 오직 예방만 있을 뿐

/* 상호배제( Mutual exclusion ) */

// 상호배제는 특정 스레드가 자원을 사용중일 때 다른 스레드가 이 자원에 접근하지 못하도록 막는 것을 의미한다. 위 예에서 사다리는 공유를 하면 안되는 자원이다.
// 이러한 자원에 동시 접근 허용하면 반드시 교착상태가 되어 버리므로, 이러한 자원을 따로 임계구역이라 지정하여 주의깊게 관리해야 한다.

// 사다리에 처음 접근한 사람은 해당 사다리를 임계구역으로 지정하고, 잠금상태로 변경하여 다른 사람에게 알린다.
// 다른 사람은 사다리를 사용하기 전에 상태를 살펴보고 잠겨 있으면 잠금이 해제될 때 까지 기다렸다가 사다리를 사용한다.

/*
		프로세스( Process )					|			스레드( Thread )
프로그램이 실행되어 메모리에 등록된 상태	|한 프로세스에서 실행되는 여러 흐름의 단위
	자신의 정보를 Context 에 저장			|		프로세스의 공유 메모리에 접근
		운영체제가 제어						|			프로세스가 제어
	Context-Switching 의 문제				|		자원 공유의 문제( deadlock )
*/

/* ----- < 유용한 파일 포멧 > ----- */

// 실제 게임을 만들다 보면, 하나의 객체 안에 서로 다른 객체를 포함하는 경우가 많다.
// Monster 의 경우 이름, 레벨, HP, MP 로 되어 있는데, 레벨 HP MP 는 몬스터 만이 아니라 플레이어도 가지고 있어야 하므로 다른 구조로 분리시켜 두는 것이 좋다.
// 이렇게 중첩된 데이터의 경우는 csv로 표현하기 어렵다.

/*
struct Status
{
	int mLevel;
	int mHP;
	int mMP;
};
struct Item
{
	std::string mName;
	int mGold;
};
class Monster
{
private:
	std::string mName;

	Status mStatus;
	std::vector<Item> mDropItems;
};
*/

// 아이템이나 스테이터스는 플레이어도 NPC 도 사용이 가능하므로, POD 로 분리시켜 둔다. 위 내용을 csv로 표현하려면
// mName, mLevel, mHP, mMP, mName, mStatus 와 같이 모든 내부 데이터를 행으로 나열하여 표현이 가능하긴 하지만, 이럴 경우 혼동이 발생할 수 있다.

/* 문서객체모델( DOM : Document Object Model ) */

// 웹( web )은 텍스트 문서로 되어 있다. 그렇게 하는 것이 전세계 모든 사람들이 컴퓨터 종류, 운영체제, 브라우저 등에
// 구애받지 않고 웹서핑이 가능하기 때문이다.
// 하지만 브라우저 개발사들 마다 자신만의 기능을 사용하게 되면서 브라우저 전쟁이 벌어지게 되었다.
// 여러 브라우저들이 각각 멋대로 문서를 해석하기 시작하면서 최초의 모두에게 동일한 화면이라는 계획이 어긋나 버렸고,
// 결국 W3C( WWW Consortium )에서 권고안을 발표한 것이 바로 DOM 이다.

// 처음 시작은 웹에서 문서를 객체화로 정리하는 것이긴 했지만, 객체지향 언어들에서 해당 개념을 자료구조를 표현하는 용도로도
// 자주 사용하게 되었다. 다음 용어들이 DOM의 핵심 기능들이다.

/*
document : 객체화된 문서를 나타낸다.
element : 문서에 속한 각 노드를 의미한다.
nodelist : element 의 배열이다.
attribute : element 에 속한 값이다.
*/

/* XML( Extensible Markup Language ) */

// W3C( WWW Consortium )에서 개발한 마크업 언어이다. 태그 등을 이용해 문서나 데이터 구조를 표현하는 것을 마크업 언어라고 하는데,
// 가장 대표적인 것이 웹에서 사용하는 HTML( HyperText Markup Language )이다. XML 은 웹페이지에 특화된 HTML 과 달리
// 좀더 범용적으로 데이터를 표현하기 위해 만들어진 것으로, 인터넷으로 연결된 컴퓨터들 끼리 데이터를 쉽게 주고 받을 수 있도록
// 고안된 언어이다. 그 덕에 일반 프로그램의 자료구조 표현에도 매우 유용하다.

/*
<? xml version = "1.0" encoding = "UTF-8" standalone = "no" ?>
<monster>
	<name>악마</name>
	<status>
		<level>10 </level>
		<hp>10 </hp>
		<mp>10 </mp>
	</status>
</monster>
*/

/* JSON( JaveScript Object Notation ) */

// 최근 유행하고 있는 형식으로, 사람이 일기 쉬운 형태로 데이터를 표현하는 것이 큰 장점이다.
// 자바스크립트 언어에서 파생되어 탄생했지만, 언어적인 키워드가 없어서 다른 프로그래밍 언어에서도 쉽게 사용이 가능하다.
// 무엇보다 프로그래머에게는 매우 익숙한 스타일이라 최근 널리 사용되고 있다.

/*
{
	"name": "악마",
	"status":
	{
		"level":10,
		"hp":10,
		"mp":10
	}
	...
	"array":["elem1": 1, "elem2":2, "elem3":3 ]
}
*/

/* 저작권 */

// 프로그램을 개발하다 보면, 외부의 라이브러리를 사용할 경우가 많다. 이렇게 다른 사람의 코드를 사용할 때는 저작권을 꼭 지켜야 한다.
// 게임 리소스등을 고의로 무료인척 뿌리고 게임 출시하면 감시하다 변호사를 고용하는 경우가 있다.
// 다행이 프로그래머들은 오픈소스( Open Source : 소스 코드 공개 )정신이 투철해서 무료로 배포하는 경우가 상당히 많다.

/*
GPL( General Public License ) : 제법 엄격하다. 모든 코드 GPL 로 공개, 라이선스 및 저작권 명시
LPGL( Lesser General Public License ) : 위 규약이 너무 엄격해서 제안된 방식. 단순 사용은 공개하지 않아도 됨, 수정한 코드는 LPGP로 공개, 라이선스 저작권 명시
BSD( Berkeley Software Distribution ) : 미국 정부가 제공하는 돈으로 운영되는 라이브러리. 라이선스 및 저작권 명시
Apache( Apache License ) : 아파치 재단이 소유한 저작권으로 BSD 와 비슷함. 변경사항 표기, 아파치 상표권 침해 금지 조항, 라이선스 및 저작권 명시
MIT( MIT License ) : MIT 대학에서 학생들에게 배포 목적으로 시작한 라이선스.
WTFPL Beerware( Do What The Fuck You Want To Public License Beer Linces ) : 하고 싶은대로 하라는 의미
*/

/* ----- < XML > ----- */

/*
XML 은 간단히 다음과 같은 4가지 요소로 되어 있다.
	선언
		헤더와 같은 의미로 해당 문서가 XML 포멧을 따르고 있음을 지정한다. 보통 <? ~ ?> 의 현태로 XML 버전, 언어 인코딩 정보를 담고 있다.
		=> <?xml version="1.0" encoding="EUC-KR"?>
	태그
		< ~ > 의 형태로 다음과 같이 주로 사용된다.
			시작 태그 : <section>
			끝 태그 : </section>
			빈 태그 : <section /> : 원소의 내용이 없는 경우
	원소
		시작 태그 부터 끝 태그 사이의 내용이다.
		=> <section> Hello, World </section>
	속성
		이름/값으로 이루어진 구조로 시작태그에 포함된다.
		=> <img src="wallpaper.jpg" alt="바탕화면"> 바탕화면 이미지 </img>

element 는 부모/자식처럼 종속 관계를 가질 수 있다.
	<parent>
		<child> </child>
		<child2/>
	</parent>
*/

/* 간단한 XML 파일 분석 */

/*
<?xml version="1.0" encoding="utf-8"?>
<TextureAtlas imagePath="sprites.png" width="256" height="256">
	<sprite n="bug1_1.png" x="0" y="0" w="24" h="24"/>
	<sprite n="bug1_2.png" x="24" y="0" w="24" h="24"/>
	<sprite n="bug1_3.png" x="48" y="0" w="24" h="24"/>
	<sprite n="bug1_4.png" x="72" y="0" w="24" h="24"/>
</TextureAtlas>

간단히 다음과 같은 파일을 하나 만들어서 저장한다. 화면에 그릴 이미지의 영역을 표현한 데이터로 다음과 같은 element 를 가지고 있다.
*/

/*
<TextureAtlas imagePath="sprites.png" width="256" height="256">
	Element : TextureAtlas
	Attributes : 
		imagePath="sprites.png" : 이미지 파일 경로
		width="256" : 이미지 너비
		height="256" : 이미지 높이
*/

/*
<sprite n="bug1_1.png" x="0" y="0" w="24" h="24"/>
	Element : sprite
	Attributes :
		x="0" : x offset
		y="0" : y offset
		w="24" : 너비
		h="24" : 높이
*/

/* ----- < TinyXML > ----- */

// http://github.com/leethomason/tinyxml2 에서 다운 받기
// 압축을 푼 후에 TinyXML2.h, TinyXML2.cpp 파일 두개를 찾는다.
// 프로젝트 폴더에 넣기
// 프로젝트 폴더에 데이터를 넣기 위한 폴더 생성( Data )

/*
XMLNode : 최상위 기반 클래스
XMLDocument : XML 문서 즉 파일을 관리하는 클래스
XMLDeclaration : XML 헤더 부분을 관리
XMLComment : XML 에 추가되는 주석을 담고 있다.
XMLElement : XML 원소를 나타내며 컨테이너 클래스로 다른 원소, 텍스트, 주석 등을 포함할 수 있다. 원소는 속성을 가질 수 있다.
XMLText : XML 텍스트를 나타내며 자식 원소 노드들을 가질 수 있다.
XMLUnknown : TinyXML 에서 파싱하지 못하는 구문은 Unknown 으로 대체된다.
XMLAttribute : XML 속성으로 < name, value > 쌍으로 되어 있다.
XMLHandle : XMLNode 포인터의 래퍼 클래스로 Null 체크를 지원한다.
	=> TinyXML2 의 기본 표현은 아니지만 다음과 같이 조금 더 코딩을 쉽게하기 위한 표기법이다.
		=> handle.FirstChild("Doc").FirstChild("Element").FirstChild().NextSibling().ToElement();
XMLConstHandle : 위 Handle 의 상수 버전
XMLVisitor : 비지터 패턴으로 구현된 탐색자
	=> Visitor Pattern : OOP 에 사용되는 디자인 패턴, 방문자 패턴이라고도 하며 객체와 알고리즘을 분리하는 방식으로 방문자는
		=> 인터페이스로 구현되며 객체에서는 accept() 메서드를 이용해 방문자를 받아 들인다.
XMLPrinter : 비지터를 이용해 XML의 내용을 프린트 한다.
*/

/* ----- < 문자열 인코딩 > ----- */

/* 문자 집합( Character Set ) */

/*
문자 집합은 말 그대로 문자( 글자 및 기호 )들의 집합이다. 이러한 문자 집합은 해당 문자를 컴퓨터가 이해하도록 하기 위해 각각 코드
( 숫자로 된 일련 번호 )로 매칭시켜 준다.

ASCII
	American Standard Code for Information Interchange
	알파벳, 숫자, 기호를 1 byte에 처리하기 위한 집합
	0 ~ 127 ( 최상단 1 bit 는 오류 검출용 패리티 비트 )
UNICODE
	Universal Coded Character Set
	OS, 컴파일러, 플랫폼에 따라 서로 다르게 문자집합을 처리하던 문제를 통합하기 위한 표준
	기본적으로 16진수 표기법이며, U+FFFF까지의 2 byte 로 하나의 문자를 표현
	상형문자, 특수기호, 향후를 대비한 예약 공간등을 추가하면서 현재는 U+0000 ~ U+10FFFF 까지 확장
*/

/* 인코딩( Encoding ) */

// 위 문자집합들은 숫자와 문자를 매칭시켜 둔 표이다. 따라서 사람이 사용하는 문자를 컴퓨터가 이해하는 숫자로,
// 반대로 숫자를 문자로 변환하는 기법이 필요한데, 이를 인코딩, 디코딩이라 부른다.

// 아스키 코드는 1:1 매핑 방식이라 사실 이런 인코딩/디코딩 과정이 필요 없었지만, 다양한 언어를 표현하다 보니
// 대 혼란을 격게 된다.

/*
비주얼 스튜디오 -> 파일 -> 다른 이름으로 저장... -> 저장 버튼 옆의 아래 화살표 기호를 누른다.
고급 저장 옵션이라 나오는 창에 인코딩 종류가 모두 인코딩 방식이다.

EUC-KR : Extended Unix Code - Korean
	확장 유닉스 코드인 EUC는 유닉스 시스템에서 언어를 표현하기 위한 인코딩 방식, 완성형
CodePage 949 : 마이크로소프트사가 도입한 코드 페이지( 인코딩을 위해 사용되는 테이블 ) DOS에서는 개별 인코딩 방식, 윈도우 에서는 EUC-KR의 상위호환
*/

/* UTF( Unicode Transformation Format ) */

// 유니코드 표에는 엄청 많은 문자들이 존재한다. 따라서 유니코드를 인코딩하는 표준이 필요한데 이런 방식을 UTF라 한다.

/*
Universal Coded Character Set Transformation Format - 8 bit

UTF-8 인코딩은 유니코드 문자 하나를 표현하기 위해 1 ~ 4 바이트를 사용한다. ASCII 문자들은 당연히 1바이트로 표현된다.
유니코드 매핑을 간단히 살펴 보면 다음과 같다.
	아스키 코드 : 1 바이트
	영어권 확장 : 2 바이트
	다국어( 한글 ) : 3 바이트
	상형문자 및 예비 : 4 바이트
*/

// UTF-16 : 기본적으로 다국어 표현까지 16 bit( 2byte )그대로 표현하고, 초과 범위에 대해서는 32 bit( 4byte )로 인코딩한다.
// UTF-32 : 32bit( 8byte )는 모든 유니코드를 그대로 저장하고도 남는다.

/*
가변 너비 인코딩( Variable-Width Encoding )

크기가 가변적인 방식의 인코딩을 일컫는다. UTF-8, UTF-16 은 가변 너비 인코딩이다. 유니코드가 아닌 방식으로는 크게 DBCS 와 MBCS 가 있다.

이름은 문자집합인데 엄밀히 말하면 인코딩이다.
	DBCS( Double-Byte Character Set )
	2 바이트로 된 문자 집합
	0 ~ 65,535 까지 문자 할당
	중국어/일본어/한국어( CJK )를 지원하기 위해 도입
	최상위 비트가 0이면 ASCII, 1이면 뒤엥 오는 바이트까지 추가하여 2바이트로 문자 표현

	MBCS( Multi-Byte Character Set )
	DBCS 와 비슷하지만 마이크로 소프트에서 사용하는 방식

UTF-16, UTF-32 는 각각 2바이트, 4바이트로 저장하다보니 엔디안 문제가 발생한다. 그래서 바이트로 저장되는 UTF-8이 거의 표준 자리를 잡았다.
*/

/* ----- < 정규표현식( Regular Expression ) > ----- */

// 특정한 규칙을 가진 문자열의 집합을 표현하는 데 사용하는 언어, 상당히 많은 언어에서 지원하며, 기능을 갖춘 텍스트 편집기에서도 사용이 가능하다.
// 기능은 매우 복잡해서 언어를 하나 배우는 개념이다. https://regexone.com/

// Ctrl + F 로 빠른 찾기 기능을 띄운다.
// 하단의 기능 중 '정규식 사용' 버튼을 킨다.

/*
\" ( .* ) \" : "" 로 둘러싸인 문자열을 찾는다.

\" ... \" : C++ 언어와 마찬가지로 특수 문자를 사용하기 위해서는 \를 붙여 준다.
	=> 즉 따옴표로 시작, 따옴표로 끝이라는 의미
( ... * ) : 괄호는 Capture Group 으로 또 하나의 패턴을 지정하고 싶을 때 사용한다.
	=> 현재 표현식 안에서 다른 패턴을 지정할 것이므로 괄호로 묶어 준다.
	=> 마지막에 붙은 *은 0번 이상 반복된다는 뜻으로 해당 패턴이 나타나는 모든 것을 찾아 준다.
. : any character 즉 문자를 의미한다.
*/

/*
\" ( [ ^\" ] * ) \" : 따옴표로 시작하고 따옴표로 끝나는데 따옴표 안에 따옴표가 없는 모든 패턴을 찾는다.
	=> """aaa"""와 같은 중첩 따옴표가 있을 경우 "", "aaa", "" 이렇게 찾아올 수 있다.

[ ... ] : 문자 클래스로 이 안에 있는 내용을 찾는다.
^\" : ^는 Not 이라는 뜻이다. 즉 따옴표가 아닌 모든 문자들을 의미한다.
*/

/* ----- < JSON > ----- */

// 요즘 나오는 모바일 게임은 쉬운 서버 구축을 위해 HTTP 방식을 많이 사용하는데 여기에 태워 보내는 데이터들은 주로 문자열이므로 JSON 문자열을 많이 사용한다.
// 물론 서버만이 아니더라도 관리가 쉽고 유연해서 다양한 분야에서 사용되고 있다.
// JSON 형식에 대한 자세한 설명은 공식 페이지에서 살펴 볼 수 있다. http://json.org/json-ko.html

/*
// Configuration options
{
	// Default encoding for text
	"my-encoding" : "UTF-8",
	// Plug-ins loaded at start-up
	"my-plug-ins" : [
		"python",
		"c++",
		"ruby"
		],
	// Tab indent size
	"my-indent" : { "length" : 3, "use_space": true }
}

주석도 가능하며, C++ 의 초기화 유니폼 초기화식과도 매우 유사하기 때문에 Java, C++, C#, Python 등 다양한 언어에서 널리 사용되는 방식이다.
기본적으로 "이름" : 값 쌍으로 되어 있으며, 객체는 {} 기호를 배열은 [] 기호를 사용한다.

기본 표현식 : "Object Name" : Value
배열 표현식 : "Object Name" : [Value, Value, ...]
오브젝트 중첩 : "Object Name" : { "Child" : Value }

값은 다음과 같은 형식이 가능하다.
	문자열
	숫자
	불리언
	null
	오브젝트
	배열
*/

/*
mName		mStatus				mDropItems
"슬라임"	mLevel = 1;			{ mName = "끈적한 젤리", mGold = 1; }
			mHP = 1;
			mMP = 1;
"늑대인간"	mLevel = 5;			{ mName = "발톱", mGold = 2 }
			mHP = 5;			{ mName = "늑대가죽", mGold = 5 }
			mMP = 5;
"악마"		mLevel = 10;		{ mName = "날개", mGold = 10 }
			mHP = 10;			{ mName = "손톱", mGold = 5 }
			mMP = 10;
*/

/*
위와 같은 데이터를 json 으로 표기하면 다음과 같다.
{
"monsters": [
		{
		"name": "슬라임",
			"status" : {
				"level": 1,
				"hp": 1,
				"mp": 1
			},
			"items" : [
				{
					"name": "끈적한 젤리",
					"gold": 1
				}
			]
		},
		{
		"name": "늑대인간",
			"status" : {
				"level": 5,
				"hp" : 5,
				"mp" : 5
			},
			"items" : [
				{
					"name": "발톱",
					"gold" : 2
				},
				{
					"name": "늑대가죽",
					"gold" : 2
				},
			]
		},
		{
		"name": "악마",
			"status" : {
				"level": 10,
				"hp" : 10,
				"mp" : 10
			},
			"items" : [
				{
					"name": "날개",
					"gold" : 10
				},
				{
					"name": "손톱",
					"gold" : 5
				},
			]
		},
	]
}
*/

/* ----- < RapidJson > ----- */

// https://github.com/Tencent/rapidjson

/*
NuGet

비주얼 스튜디오에서 제공하는 패키지 자동 설치/관리 도구

프로젝트 -> NuGet 패키지 관리를 선택한다.
검색창에 RapidJson 을 입력하고 최신 버전을 선택한다.
오른쪽 설치 버튼을 선택한다.
*/

/*
RapidJson 은 문자열로 되어 있는 JSON String 을 DOM 으로 해석( Parsing )할 수 있으며 해당 DOM 을 통해 값에 접근하거나
수정할 수 있게 된다. 물론 DOM 을 다시 JSON 문자열로 변환할 수 있다.

rapidjson::Document : DOM 으로 표현된 JSON 객체이다.
	=> 최상위( root ) Value 로 부터 시작하는 트리 구조를 가진다.
rapidjson::Value : JSON 에 저장되는 모든 값을 통틀어 Value 라 부른다.
	=> Int, Int64, Uint, Uint64, Bool, Double, Float, String, Object, Array 등의 타입을 가질 수 있다.
*/

//{
//	"hello": "world",
//	"t": true,
//	"f": false,
//	"n": null,
//	"i": 123,
//	"pi": 3.1416,
//	"a": [1, 2, 3, 4]
//}

/*
위와 같은 JSON 문자열을 해석( Parse )하면 다음과 같은 DOM 이 된다.

Document

Object :	string{"hello"} : string{"world"}
			string{"t"}		: true
			string{"f"}		: false
			string{"n"}		: null
			string{"i"}		: number{123}
			string{"pi"}	: number{3.1416}
			string{"a"}		: array{size=4}		: number{1}, number{2}, number{3}, number{4}
*/

/*
객체를 JSON 화 하는 과정은 크게 2가지가 있다.

객체 -> JSON : C++ 클래스를 바로 JSON 문자열로 변환한다.

객체 -> DOM -> JSON : C++ 클래스를 DOM 객체로 만든 후 다시 JSON 문자열로 변환한다.
	=> 모바일 게임에서 서버와 통신을 JSON 으로 하는 경우가 있는데 이런 경우는 DOM 객체를 가지고 있는 것이 편할 경우가 있다.
*/