/* ----- < 컴퓨터 기초 > ----- */

/* 최초의 컴퓨터 */

// 스위치의 집합 on / off : 물리적인 스위치를 전기 신호로 바꿔 꺼져 있는 상태를 0, 켜저 있는 상태를 1로 표현하는 간단한 기계
//							=> 0 과 1 로만 이뤄진 이진법 숫자

/* 기술의 발전 */

// On / Off 를 담당하는									진공관( Vaccum-Tube )
// 진공관의 1 / 220의 초소형으로 ENIAC을 만들 수 있는	트랜지스터( Transistor )
// 트랜지스터 10만개를 쌓아서 만든						집적회로( IC )

/* ----- < CPU > ----- */

// Central Processing Unit( 중앙 처리 장치 ) : 연산 + 제어 + 기억
//												=> 연산 : ALU( Arithmetic Logic Unit ) 연산과 비교, 판단을 담당
//												=> 제어 : Control Unit 명령어 해석, 실행을 위해 CPU 내부의 회로 흐름을 관리
//												=> 기억 : Register Set 처리할 명령어를 저장

// CPU 성능
// 초당 행할 수 있는		연산 싸이클( Hz로 표기 )
// 한 번에 처리할 수 있는	명령 크기( Bit로 표기 )

// CPU는 레지스터( Register )라는 고속 저장 장소를 가지고 있는데, 흔히 RAM이라고 불리는 메모리가 아닌 CPU 내부에 있는 저장 장소
// 레지스터들을 사용하여 연산 및 제어를 하는데, 이 레지스터의 크기에 따라 8비트 / 16비트 / 32비트 컴퓨터냐 하는 단위가 정해짐
//		=> 이러한 레지스터가 표현할 수 있는 값의 범위를 워드라 부름
//		=> 워드는 레지스터의 크기로 CPU가 1 사이클에 처리할 수 있는 비트의 수를 나타냄

/* ----- < Memory > ----- */

// CPU 의 저장 공간만으로는 부족하여 외부에 추가적으로 저장 공간 메모리( Memory )를 만듬
//		=> ROM( Read Only Memory ) : 고정 기억 장치, 컴퓨터를 구동하기 위한 정보 저장, 전원을 꺼도 사라지지 않음
//		=> RAM( Random Access Memory ) : 임의 접근 기억 장치, 임의의 영역에 접근하여 읽고 쓰기가 가능한 주기억 장치
//										=> 어느 위치에 접근하더라도 동일한 시간이 소여, 전원이 끊어지면 사라짐

/* ----- < 프로그래밍 언어 > ----- */

// 기계어 : 0, 1 들의 묶음
// 어셈블리어( 저수준 언어 ) : 최소한 의미를 가지는 단어들
// 고수준언어 : C 계열, Jave 등

// 컴퓨터가 실행할 수 있게 하려면 결국 [고수준언어] -> [저수준언어] -> [기계어]로 변환 과정을 거쳐야 한다.
//		=> Compiler : 고수준언어를 저수준언어로 변환, Compiler라는 것은 수집/기록을 뜻함
//					=> 내부적으로는 의미 있는 단어들을 모으고 그것들의 연관 관계를 기록해서 저수준언어로 변환
//		=> Link : 외부 정보들을 엮어 주는 과정을 뜻함
//		=> Build : Complie 과 Link 를 하나로 묶어서 Build라 칭함

// High Level Language -- COMPLIE ---> Assembly Language -- LINK + 추가 기능 ---> Application( App.exe )

// 앱의 실행 순서
// App.exe -- Double Click ---> OS -- Load ---> RAM ---> CPU
//	=> RAM : 프로그램의 내용( 명령어들의 집합 )이 등록된다.
//	=> CPU : 명령 집합의 첫번째 명령부터 수행을 시작한다.

/* ----- < 2진수와 비트, 바이트 > ----- */

// 2진법( Binary System ) : 0 과 1 로 이루어진 숫자체계
//							=> 17의 2진수 : 10001
//							=> 3의 2진수 : 11
// 16진법 : 0 ~ 9 ~ A ~ F
//			=> 79의 16진수 : 4F
//			=> 15의 16진수 : F

/* 2진수와 16진수 */

// 16진수 F를 2진수로 변환하면 F( 16 ) == 15( 10 ) == 1111( 2 )가 되어 16진수 한 자리를 표현하려면 4비트가 필요
//		=> 이는 1 바이트에는 16진수 2자리가 되는 셈 FF( 16 ) == 255( 10 ) == 1111 1111( 2 )
//		=> 2진수 한 자리를 컴퓨터에서는 비트( bit )라고 하며 8개의 비트를 묶어서 1 바이트( byte )라고 정의
// 1Byte = 2진수( 8자리 ) = 16진수( 2자리 )

/* 양수 음수 */

// 양수와 음수를 구분하기 위해 가장 앞의 비트를 사용, 4비트의 저장 공간이 있다면, 앞의 한 비트는 부호로 사용, 3비트만 값으로 표현
//		=> 나머지 3비트는 서로 부호만 다른 두 값의( ex. +1 / -1 )합은 0이 되어야 하는 조건을 만족시키기 위해 2의 보수를 사용
//			=> 10의 보수 : 3의 '10의 보수' 는 7, 둘을 합해서 10을 만들 수 있는 숫자
//							=> 10 은 3 보다 자리수가 하나 많으므로 같은 자리수에서 구하는 방법은 9 - 3 + 1 = 7
//							=> 진법에서의 보수는 위와 같이 현재 자리수에서 가장 큰 값을 뺀 다음 1을 더하는 형태가 된다.
//			=> 2의 보수 : 0101의 '2의 보수' 는 1111 - 0101 + 1 = 1011
//							=> 이런 보수들은 합하면 바로 0이 된다.

/* ----- < 소수 형식 > ----- */

/* 고정소수점( fixed point ) */

// 각각 정수부 / 소수부를 나누어서 저장, "1.2" 와 같은 소수는 1을 정수부에 0.2는 소수부에 비트를 나누어 저장
// 그러면 부호부 + 정수부 + 소수부로 나누어서 소수형식을 저장할 수 있게 된다.
//		=> 단점 : 정밀도( Precision )가 떨어짐, 32비트 중 1비트는 부호, 15비트는 정수, 16비트는 소수
//				=> 정수는 15비트라 32.767까지만, 소수는 16비트라 0.65535까지 표현이 가능
//				=> 수학 계산에서는 큰 문제가 될 수 있음

/* 부동소수점( floating point ) */

// 10의 -1승 = 0.1
// 가수( significand ) : 12
// 밑( base ) : 10
// 지수( exponent ) : -1
// 1.2 = 12 X 10의 -1승
// 컴퓨터 수학에서는 밑( base ) 10을 e로 표현하는데 12e-1로 표기할 수 있다. 즉 e는 항상 고정이므로 무시하고 가수와 지수로
//		=> 소수점 표현이 가능하다. 부호부 1비트 + 지수부 8비트 + 가수부 23비트
//		=> 이런 곱셈형태로 소수점이 표현 가능하고 지수에 따라 소수점의 위치가 변하기 때문에 부동 소수점이라 부른다.

/* 아스키 */

// 영어 128개( 7비트 )와 에러 검출용 비트( Parity Bit )를 추가해서 8비트로 완성된 표준 부호
//		=> 이렇게 아스키 코드를 사용하여 문자를 표현하는 타입이 char
//		=> 내부에는 코드에 해당하는 숫자가 들어 있지만, 사용자에게 보여줄 때는( 출력 )문자를 표시

//#include <iostream>
//
//int main()
//{
//	char myChar;
//
//	myChar = 'a';
//	myChar += 1;
//}

// 컴퓨터는 내부적으로 문자를 다룰 수 없어서 이렇게 숫자를 사용

/* ----- < 16비트 / 32비트 / 64비트 컴퓨터 > ----- */

// CPU : 연산 + 제어 + 기억 3대 요소를 담당
//		=> 초당 행할 수 있는 연산 사이클( Hz로 표기 )과 한 번에 처리할 수 있는 명령 크기( 16비트, 32비트 등 )로 CPU의 성능 구분
// CPU 레지스터 : 고속 저장 장소로써 흔히 RAM이라 불리는 메모리가 아닌 CPU 내부에 존재하는 저장 장소
//				=> 이런 레지스터들을 사용하여 연산 및 제어를 하는데, 이 레지스터의 크기에 따라 8비트, 16비트, 32비트 컴퓨터 단위가 정해짐
// 워드 : 레지스터가 표현할 수 있는 값의 범위
//		=> CPU 구조에서 사용하는 단위로 CPU가 1 사이클에 처리할 수 있는 비트의 수를 나타냄
//		=> 16비트 컴퓨터에서 한 사이클에 1워드( 16비트 )의 명령을 수행할 수 있다.
//		=> 이 명령은 기계어/어셈블리어의 명령어 하나를 수행한다는 뜻

// 32비트 플랫폼 x86
// 64비트 플랫폼 x64

/* ----- < 비트 연산 > ----- */

/*
|       | 논리부정 | 논리곱 | 논리합 | 베타적논리합 |
|       | ( NOT )  | ( AND )| ( OR ) |  ( XOR )		|
| a | b |	!a	   |  a & b |  a | b |   a ^ b		|
| 0 | 0 |	 1	   |    0   |    0   |     0		|
| 1 | 0 |    0	   |    0   |    1   |     1		|
| 0 | 1 |    1     |    0   |    1   |     1		|
| 1 | 1 |	 0     |    1   |    1   |     0		|
*/

/* & 논리 곱 */

//				1 0 1 1
//	AND ( & )	0 1 0 1
//				0 0 0 1

/* | 논리 합 */

//				1 0 1 1
//	OR ( | )	0 1 0 1
//				1 1 1 1

/* ^ 베타적 논리합 */

//				1 0 1 1
//	XOR ( ^ )	0 1 0 1
//				1 1 1 0

/* ----- < 색상 표현 > ----- */

// 비트 연산을 가장 많이 하는 것은 게임에서 색상 처리다.
// 총 3비트로 되어 있는 변수가 있다고 가정하면 앞에서 부터 RGB 각각 1로 표기하고 자리수를 3자리로 만들면
//		=> R : 100 , G : 010 , B : 001
//		=> 이러한 2진수 색상을 섞으면 : 노란색 = 빨간색 + 녹색 : 100 | 010 = 110
//						=> 흰색 = 빨간색 + 녹색 + 파란색 : 100 | 010 | 001 = 111
// 포토샵, 그림판 등을 보면 RGB 값을 각각 0 ~ 255 사이로 지정
// 1 바이트가 255까지 기록할 수 있기 때문에, 컴퓨터 그래픽스에서는 각각 한 바이트로 RGB를 표현하는 것
// 여기에 투명도인 알파를 더해서 ARGB, 총 4바이트를 사용

/* ----- < 한글과 컴퓨터 > ----- */

/* 조합형 */

// 자음/모음만 저장하고 각각 초성/중성/종성에 조합하여 표현하는 방식
// 초성 : 자음
// 중성 : 모음
// 종성 : 자음
// 큰 값이 27인데 비트로 표현하려면, 11011(2) 최소 5비트가 필요, 따라서 8비트로는 표현이 불가능하므로, 16비트( 2바이트 )로 확장하여 사용하기로 하였다.
// 1비트( 영어/한글 ), 5비트( 초성 ), 5비트( 중성 ), 5비트( 종성 )
// 각 파트를 조합해서 위치 조절해 가면서 그려줘야 한다.

/* 완성형 */

// 조합형을 처리하기가 매우 귀찮아서 모두 집어 넣은 것
// 무식하지만, 그리기가 매우 편하기 때문에 결국 완성형이 국제 표준으로 자리잡았다.
// 그러나 만들어지는 글자의 총 개수가 11,172개나 되어 이 글자들 중 사용하지 않는 것을 추려서 65,535개가 등록

/* 유니코드 */

// 컴퓨터가 전 세계에 보금되면서, 모든 국가의 극자를 표현해야 할 필요가 생겼다.
// 그래서 1991년 유니코드라는 단체를 만들고 전세계 글자를 기호화 하였다.

/* ----- < 힙( Heap ) 스택( Stack ) > ----- */

// 프로그래핑이 실행될 때 필요한 메모리는 다음과 같은 종류가 있다.
//	=> 텍스트( Text )또는 코드( Code ) 영역
//		=> 실제 사용자 코드가 탑재
//	=> 데이터( Data ) 공간
//		=> 전역 변수, 크게 초기화된 값과 초기화되지 않은 값으로 나눔
//	=> 힙( Heap )
//		=> 자유 공간( free store )이라고도 하며 사용자가 실행시간에 제어
//	=> 레지스터( Register )
//		=> 함수 반환 주소, 스택의 위치 등 내부적으로 사용되는 정보
//	=> 스택( Stack )
//		=> 지역 변수, 함수 매개변수

/*
메모리 끝
	[ STACK ]
	[ HEAP ]
	[ DATA ]
메모리 시작
*/

/*
Stack은 구조의 특성상 아래에서 부터 쌓는 방식이므로 가장 마지막에 위치한다.

#include <iostream>

void MyFunction1();
void MyFunction2();

char gString[] = "MEMORY LAYOUT";
int gInteger;

int main()
{
	int* allocated = new int;
	MyFunction1();
	delete allocated;
}
void MyFunction1()
{
	int local;
	MyFunction2();
}
void MyFunction2()
{
	int local;
}
*/

/*
메모리 끝
	[main()]
	[MyFunction1()]
	[int local]
	[MyFunction2()]
	[int local]
	[allocated = new int]
	[int gInteger]
	[char gString[]...]
메모리 시작
*/

// Stack Memory는 생각보다 작다. Visual Studio 표준은 1MB밖에 되지 않는다.
// Data : 프로그램 시작시에 할당, 종료시에 해제
//		=> 전역변수 및 static 변수
// Heap : 실행시에 동적으로 할당
//		=> new, malloc...
// Stack : 함수 호출 시 생성되는 매개변수 및 지역 변수, 반환 시 종료