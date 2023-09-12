/* ----- 윈도우 개발 히스토리 ----- */

/* Windows API */

// 마이크로소프트 윈도우 운영체제에서 사용하는 API 이며, 윈도우 개발의 원조이다. Windows 3.1 의 탄생부터 함께했기 때문에 C 언어로되어 있다.
// 동적 링크 라이브러리( DLL ) 방식을 사용하며 OS 제어, GUI, 그래픽, 멀티미디어 등을 제어할 수 있다.

/*
운영체제가 크게 변경될 때마다 번전이 변경되었으며 크게 다음과 같이 발전했다.

Win16 : 16비트 버전 윈도우로 Windows 3.1 개발에 사용된다.
Win32 : 32비트 버전 윈도우로 Windows 95 부터 사용된다.
Win32s : subset 의 약자로 Win32 의 일부 기능이란 의미이다.
	=> 일부 16비트 윈도우에서 Win32 를 사용하기 위해 만들어 졌다.
Win32 for 64bit : 64용 이지만 새로운 API 를 추가하진 않았다.
	=> 운영체제 내부에 가상의 레이어( WOW64 )를 만들어 32비트 프로그램을 64비트 운영체제에서도 실행할 수 있도록 만들어졌다.

따라서, 가장 최신 API 는 Win32 라보 볼 수 있다.
*/

/* MFC( Microsoft Foundation Class Library ) */

// Window API 가 C 로 되어 있어서 이를 조금 더 편리하게 사용하기 위해 C++ 로 래핑( Wrapping )한 API를 말한다.
// 비주얼 편집기, 다양한 템플릿, 나름 스마트포인터 등의 당시엔 획기적인 기능들을 가지고 있으며, Visual Studio 에 기본 내장되어 있어서 많이 사용하던 기능이다.
// 하지만 Microsoft 조차 출시 후 MFC 가 사용하기 어려우니 Visual Basic 을 사용하라고 권장할 정도로 매우 복잡하다.
// C++ 표준에서 벗어난 함수들을 Microsort 스타일로 사용했기 때문에 결국 2014년 공식적으로 향후 지원을 중단했다.

/* Windows Template Library */

// 마이크로소프트 내부에서 사용하기 위해 별도의 라이브러리를 만들어서 사용하였는데 Win32 와 대응되는 코드가 많아서 인기가 좋았다고 한다.
// 점점 입소문이 나면서 오픈소스로 풀려서 지금도 업데이트 되고 있다.

/* Windows Form */

// 마이크로소프트에서 야심차게 통합 플랫폼 .NET 을 발표하면서 제공된 API 이다.널리 사용할 수 있도록 오픈소스로 제공되었으며
// 기존의 MFC 를 대체할 수 있도록 만들어진 녀석이다. 하지만 2014년에 공식 지원이 중단되어 버그 수정만 이뤄지게 되었고,
// 크로스-플랫폼 구현의 내부 용도로만 사용된다.

/* Windows Presentation Platform */

// 최초로 운영체제에서 하드웨어 가속을 지원하기 위해 개발된 API이다.
// 확대해도 안깨지는 벡터 그래픽, 폰트에 디자인을 수행할 수 있는 타이포그래피, 애니메이션 등 그래픽에 특화된 API로
// 내부에서는 DirectX 를 사용해 하드웨어 가속을 지원한다.
// 그런데 게임 개발자들 사이에서는 평가가 애매하였다. 하드웨어 가속을 위해서는 DirectX 를 사용하는 것이 이득이고,
// 일반 애플리케이션을 만들기 위해서는 복잡했기 때문이다.

/* Windows RT( Runtime ) */

// Windows 8 과 함께 발표된 새로운 크로스-플랫폼 API이다.
// 윈도우폰과 같은 모바일에 대응하기 위해 만들어졌으며 모든 구조가 순순한 C++ 이라 속도가 빠르다.
// 나름 신경써서 만든 녀석이지만 마이크로소프트의 애플화 계획이 무산되면서 끝날 줄로만 알았다.

/* UWP( Universal Windows Platform ) */

// Windows 10 과 함께 발표된 API 로 WinRT 의 개선판으로 윈도우 10 모바일, Xbox, PC 를 통합하려는 야심찬 계획으로 출발했다.
// 최근 XBOX 차세대기와 PC 의 통합 행보가 더욱 강화되면서 어쩔 수 없이 UWP 를 다뤄야할 날이 올지도 모르겠다.

/* ----- 메시지와 이벤트 ----- */

// 3단계인 윈도우 메시지 처리를 알아 보기 전에 윈도우 OS 의 작동원리를 알아보자.

/*
윈도우는 여러 개의 응용프로그램들이 한꺼번에 실행된다. 이런 멀티테스킹 환경을 위해 개발한 것이 이벤트 메시지 시스템이다.

[키보드] -> [입력 큐] -> [운영체제 윈도우 관리자] -> [실행중인 응용 프로그램 A] { 메시지 큐 -> 이벤트 핸들러 }
[마우스] ->										  -> [실행중인 응용 프로그램 B] { 메시지 큐 -> 이벤트 핸들러 }
												  -> [실행중인 응용 프로그램 C] { 메시지 큐 -> 이벤트 핸들러 }

위와 같이 운영체제에서 조작에 필요한 정보들을 받아서 실행중인 응용프로그램에게 각각 메시지를 보내주고, 응용프로그램은 그 메시지를 받아와서
필요한 처리를 하는 방식이다.
이때 보내는 측에서 보면 메시지( Message )를 보낸다고 하며, 받는 측에서는 이벤트( Event )가 발생했다고 판단한다.

응용프로그램에 전달된 메시지를 처리할 때는 메인 루프와 메시지 처리를 통해서 실행된다.

	[Event Queue]				[Main Loop]												[Window Procedure]
1. A 키를 눌렀다.			GetMessage()->TranslateMessage()->DispatchMessage()		처리 -> 메시지 처리
2. 윈도 사이즈가 바뀌었다.
3. ...

위와 같이 메인루프는 이벤트가 있으면 GetMessage 를 통해 메시지를 가져온다. 그리고 TranslateMessage 로 가져온 메시지를 처리하기
쉽게 변환한다. DispatchMessage 로 해당 메시지를 윈도 생성시 등록한 위도 프로시저에 넘겨준다.
*/

// 이런 윈도우 내부의 처리를 살펴 볼 수 있는 것이 Spy++ 이라는 도구이다.
// 도구 -> Spy++ 을 실행해 보면 운영체제가 어떻게 윈도우를 핸들로 관리하는가, 어떤 메시지가 전송되는가를 살펴볼 수 있다.

/* ----- GDI ----- */

/*
GDI : 최초 윈도우와 함께 등장한 그래픽 시스템으로 폰트, 윈도우 배경색 등 OS의 핵심 기능을 처리한다.
WinG : GDI는 정적인 표현만 가능해서, 게임 제작에 특화된 WinG 시스템을 추가했다.
	=> DirectDraw 의 등장으로 WinG 는 아예 사라졌다.
DirectDraw : 하드웨어 가속이라는 개념이 등장하면서 게임 전용으로 DirectX 가 발표되었다.
	=> DirectDraw 는 DirectX 의 일부분으로 직접 하드웨어에 접근하여 빠른 처리가 가능했다.
	=> 하지만 Direct3D 보다 월등하게 느려서, 대부분의 게임이 Direct3D 를 사용해 2D 를 처리했다.
	=> 결국 구버전으로 사라졌다.( DirectX7 이 마지막 )
GDI+ : 게임이 아닌 일반 윈도우 프로그램도 멋진 그래픽을 지원하기 위해, 기존의 GDI 에 하드웨어 가속을 지원하여 GDI+ 라는 시스템을 개발했다.
Direct2D : GDI+ 를 대체하기 위해 추가되었다. 최근 마이크로소프트는 Direct2D 를 밀어주고 있다.
*/

/* ----- Window GDI( Graphics Device Interface ) ----- */

/*
텍스트 기반의 콘솔에서 벗어나 화려한 그래픽으로 무장한 윈도우 OS 의 탄생과 함께한 기능이다.
요즘 자주 사용되지 않지만 당시에는 What You See Is What You Get 이라는 캐치프라이즈를 들고 나와서 비주얼적인 것을 매우 강조했다.
따라서 그래픽 출력에 대한 것이 매우 중요한 기능이었고, 이를 만족하기 위해 Windows Graphics Interface( GDI )라는 개념을 만들었다.

인터페이스라는 단어는 클래스에서도 나왔는데 어떠한 장치들 간에서도 잘 작동하는 규약이다.
GDI 역시 이런 특성을 가지고 있어서, 컴퓨터의 출력을 단순히 모니터에 한정 지은 것이 아니라 프린터 등 다양한 출력장치로 동일하게 보낼 수 있다.
윈도우프로그래머는 서로 다른 하드웨어에 직접 엑세스할 필요 없이 GDI를 통하면 동일한 코딩으로 서로 다른 장치에 출력을 할 수 있게 된다.

	[응용 프로그램] -> [GDI32.dll] -> [GDI] <=> [그래픽 드라이버]
위와 같이 프로그래머는 장치에 대해 세부적인 기능이나 명세를 알 필요 없이 공통된 GDI.dll 라이브러리가 제공하는 기능만 사용하면,
운영체제가 알아서 드라이버와 통신하면서 화면이나 프린터에 그래픽을 출력할 수 있게 된다.
*/

/* Device Context */

// 해당 장치에 데이터를 출력하기 위한 정보( 주로 구조체 )들을 디바이스 컨텍스트라고 보면 된다.
// 윈도우의 모든 그리기 오브젝트는 이러한 DC 를 통해 이루어진다.

/*
Rectangle(hDC, 0, 0, 100, 100); DC 에 사각형을 그리는 함수이다.
HDC hDC : DC 에 대한 핸들이다.
int left : 사각의 좌상단 논리좌표 X
int top : 사각의 좌상단 논리좌표 Y
int right : 사각의 우하단 논리좌표 X
int bottom : 사각의 우하단 논리좌표 Y

논리 좌표( Logical Coordinate )는 실제 장치에서 사용되는 물리 좌표( Physical Coordinate )와 구분되는 좌표계이다.

여기서 그린 사각형 0,0 ~ 100,100의 좌표를 가지고 있어서 윈도우의 좌상단에 그려진다.
하지만 장치( 모니터 )에서는 좌상단이 다른 곳이다. 이와 같이 장치와 응용프로그램의 좌표계를 구분지어서 사용하기 위해 만든 것이
논리 좌표/물리 좌표 이다.
*/

/* ----- GDI+ ----- */

// Windows XP 의 발표와 함께, 기존 GDI 의 성능을 개선하고, 새로운 기능( 벡터 그래픽, 이미지, 폰트 등 )을 추가한 것이 GDI+ 이다.
// 프로그래머의 시점에서 보자면, 장치독립적이던 기존 특성은 그대로 유지하고 C++ 클래스화 되어 있다는 점이 매력적이다.

/*
	[응용프로그램] -> [GDI+, C++ API] -> [GDI+, Flat API] <=> [그래픽 드라이버]
*/

/*
#pragma comment (lib, "Gdiplus.lib") : GDI 는 윈도우 자체에 내장되어 있지만 GDI+ 는 선택사항이다.
	=> 따라서 선언과 별개로 정의들이 필요한데, 이 정의는 gdiplus.dll 이라는 동적 연결 라이브러리( Dynamic Link Library )로
	=> 되어 있다. 이를 사용하려면 위와 같이 라이브러리 파일을 등록해 줘야 한다.

Gdiplus::GdiplusStartupInput gdiplusStartupInput; : GDI+ 를 초기화 하기 위한 정보를 가진 구조체
	UINT32 GdiplusVersion : 버전을 명시한다. 항상 1이다. 업데이트가 없어서
	DebugEventProc DebugEventCallback : 디버그용 빌드에서 asset, warning 을 위해 호출할 콜백 함수
	BOOL SuppressBackgroundThread : GDI+ 백그라운드 스레드를 사용할지 말지에 대한 값이다. TRUE로 지정하면, 이미지 처리등 GDI+ 의 기능이 스레드로 개별 동작을 하게 된다.
	BOOL SuppressExtrenalCodecs : 외부 이미지 코델을 사용할지 말지에 대한 값이다. 하지만 1.0에서는 지원하지 않는 방식이므로 앞으로도 지원하지 않는다.
*/

/*
ULONG_PTR gdiplusToken;

기존에 알고 있던 토큰은 언어를 구성하는 최소 단위 였지만, 여기선 다른 의미로 사용된다.
주로 네트워크 환경이나 보안등에서 사용하는 개념이다. 과거 버스를 탈때 버스 티겟과 같은 것이 있었다.

즉, 여기에서의 토큰은 GDI+ 를 사용하는 번호를 발급받음으로 우리 프로그램의 자격증명을 얻는 것이다.
이 번호를 가지고 있으면 GDI+ 기능을 이용할 수 있는 것이다.
*/

/*
Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

GDI+ 를 구동한다. 기본 시스템이 아니므로 위와 같이 명시해줘야 한다.

	매개변수
		ULONG_PTR* token : GDI+ 를 사용할 토큰을 돌려 준다.
			=> 함수에서 값을 돌려 줄 예정이므로 포인터로 지정한다.
		GdiplusStartupInput* input : GDI+ 를 구동할 옵션을 지정한 GdiplusStartupInput 구조체를 포인터로 넘겨 준다.
		GdiplusStartupOutput* output : GDI+ 를 구동한 후 필요한 정보들을 GdiplusStartupOutput 구조체로 넘겨준다.
			=> 여기에는 백그라운드 스레드일 때 작업이 끝났을 때를 처리하는 알림 함수들이 넘어 온다.
			=> nullptr 이면 반환하지 않는다.
	반환값
		Gdiplus::Status 는 GDI+ 의 상태를 정의해 둔 열거형으로, 정상적으로 수행되었으면 OK가 된다.
*/

/*
Gdiplus::GdiplusShutdown(gdiplusToken); : GDI+ 를 종료하고 사용한 모든 리소스를 지운다.
	=> 종료할 때는 시작할 때 건네 받은 토큰을 반드시 넘겨줘야만 한다.
Graphics graphics(hdc); : GDI+ 는 클래스화 되어 있다. 선, 커브, 도형, 이미지, 텍스트 등의 대부분 그래픽 오브젝트 그리기를 담당하는 클래스가 Graphics 이며, hdc로 부터 인스턴스를 생성했다.

Graphics 생성자는 다음과 같은 항목을 가진다.
	HDC : DC 에 직접 그리기
	HWND, BOOL : 윈도우에 직접 그리기
	Image* : 이미지에 그리기
	HDC, HANDLE : DC 와 특정 장치를 명시해서 그리기
*/

/* ----- 랜덤 ----- */

// 임의의 무엇인가를 한다는 것은 편법으로 비슷한 결과를 도출하는 것이다.
// 컴퓨터 이론에서는 유사 난수( pseudo-random number )라 한다.

/*
int main()
{
	for (int i = 0; i < 20; i++) std::cout << rand() % 10 << ' ';
	std::cout << '\n';
}

int rand() : 가장 기본적인 랜덤
	=> 0 ~ 32767 의 값을 반환한다. 
	=> 만약, 0 ~ 9 까지의 난수를 발생하고 싶다면 rand() 를 통해 만들어진 0 ~ 32767 의 값을 10으로 나눈 나머지를 출력해 주면 된다.
하지만 이는 랜덤이 아니다. 해당 프로그램을 다시 실행해 보면 동일한 배열이 나올것이다. 몇 번을 재실행 해도 동일하다.
일부 게임은 이런 것들 때문에 가챠 테이블이 털리기도 했지만 기본적으로 rand() 의 목표는 재현 가능한 난수를 생성하는 것에 있다.
서버와 클라이언트에서 동일하게 랜덤 숫자를 생성할 경우도 많기 때문에 게임에서는 더욱 더 중요한 개념이다.

이렇게 랜덤을 결정할 때 기준이 되는 것을 시드( seed )라 부른다. rand() 은 시드에 따라 생성되는 규칙이 다르며 동일한 시드라면
같은 패턴으로 반복되어 지는 것이다.
*/

/*
srand(unsigned int)time(unllptr);
for (int i = 0; i < 20; i++) std::cout << rand() % 10 << '\n';

rand() 함수의 시드값을 지정한다.

실행될때마다 달라지는 랜덤 값을 만든다. 편법으로 자주 사용되는 것이 현재 시간을 시드로 생성하는 것
실행할 때 마다 시간이 달라지기 때문에 그럴듯한 랜덤 값이 만들어진다.
*/

/*
#include <iostream>
#include <vector>
#include <random>

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	나머지 연산을 사용한 랜덤
	for (int i = 0; i < 20; i++)
	{
		std::cout << gen() % 10 << ' ';
	}

	std::cout << '\n';

	균등한 분포토를 가진 랜덤
	std::uniform_int_distribution<> dist(0, 9);
	for (int i = 0; i < 20; i++)
	{
		std::cout << dist(gen) << '\n';
	}
}

std::random_device : 컴퓨터 디바이스로부터 임의의 숫자를 생성해 낸다. 이 값을 시드로 자주 사용한다.

mt19937 이 임의의 숫자를 생성하므로 바로 나머지 연산을 적용해도 되지만 1 ~ 5까지의 랜덤 배열은 다음과 같은 것도 랜덤이다.
가챠와 같은 랜덤 테이블을 만들 때는 적당히 고르게 퍼져있는 형태가 좋은데 이러한 기능도 제공한다.
template<class IntType = int>
class std::uniform_int_distribution;

탬플릿 클래스인 uniform_int_distribution 은 min, max 값을 지정해서 생성자를 불러 줄 수 있는데 [min, max]에 해당하는 값으로
고르게 분포시켜 주는 역할을 한다. 이렇게 생성한 인스턴스에 랜덤 생성기를 넘겨주면 해당 랜덤 숫자를 분포기의 규칙에 따라 생성해 주는 방식이다.
*/

/* ----- 설계방식 ----- */

/* 하향식 설계( Top-down design ) */

/*
전체 구조를 설계한 후 세부 사항을 구체화하는 방식
	1. 전체 시스템의 분석 최우선
	2. 시스템을 작은 단위로 분해
	3. 각 단위 별로 다시 하향식 설계
	4. 모든 기능을 취합해 요구사항을 검토
	5. 코딩
먼저 숲을 보고, 나무를 파악하는 방식
사전 작업이 조금 걸리지만, 그 만큼 코딩에 들어가는 시간은 매우 줄어든다.
하지만 전체가 구현되기 전까지는 테스트가 힘들 수 있다.
*/

/* 상향식 설계( Bottom-up design ) */

/*
작은 기능을 먼저 구현한 후 시스템으로 조립하는 방식
	1. 시스템의 기본 요소를 구현
	2. 단위 테스트
	3. 기본 요소들을 모아서 하위 시스템을 구현
	4. 단위 테스트
	5. 하위 시스템들 모아서 프로그램 완성
	6. 단위 테스트
나무에서 출발해 숲을 보는 방식
코딩과 테스트에 집중하는 만큼 시간이 오래 걸린다. 단위 테스트를 자동화 할 수 있다면 매우 안정적이고 효율적인 방법
*/