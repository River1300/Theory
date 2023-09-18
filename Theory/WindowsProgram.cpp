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

/* ----- DirectX ----- */

// Microsoft 에서 제공하는 멀티미디어 종합 라이브러리
// 하드웨어에 직접 접근한다는 의미로 Direct 라는 용어가 붙은 것이라 하드웨어의 성능을 100% 발휘할 수 있게 하여, 높은 품질의 3차원 그래픽을 만들 수 있게 해준다.

/*
Direct9 및 과거 버전 : 2002년부터 2011년 정도 까지 대부분의 개발자들이 사용한 버전,
		=> 따라서 책이나 인터넷 자료를 찾아보면 이 버전의 코드가 가장 많을 수 있다.
Direct10 : 새로운 그래픽 기술을 적용하기 위해 DirectX 의 오래된 구조를 싹 바꿔버린 버전,
		=> Direct9 와 상당히 차이가 많아서 개발자들이 9 -> 10 전환을 피하다 보니 9가 더 인기 있었던 것 일 수도 있다.
Direct11 : 기본 구조는 DX10 을 차용하고 추가적인 하드웨어 제어 기능을 도입했다.
		=> DirectX11 은 Windows7을 지원하는 가장 최신 라이브러리이다. 초보자, 인디게임등 추천하는 버전이다.
Direct12 : DX11 이 CPU 부하가 크다는 평가를 인식해서 CPU 관련 개선이 추가되었다. 여기에 그래픽카드의 성능을 더 발휘하기 위해
		=> 조금 더 Low-Level 기능이 강화되었다.
		=> 때문에 DX11 에서는 간단한 한 줄로 처리되던 것이 DX12 에서는 상당히 많은 세부 작업으로 나눠진 경우가 있다.
		=> DX12 부터는 Windows10 지원, 전문가, GPU 하드웨어 전문가, 대규모 팀에서 추천하는 버전
*/

/*
DirectX 는 종합 라이브러리 이므로 다음과 같은 여러가지 구성요소로 되어 있다.

DXGI : DirectX Graphics Infrastructure 로 드라이버-하드웨어 간의 통신을 위한 API
Direct2D : 2D 그래픽 표현 API
Direct3D : 3D 그래픽 표현 API
XInput : 윈도우 및 Xbox 컨트롤러를 통합하여 지원하는 입력 지원 API
DirectMusic : 사운드 트랙 재생
DirectAudio : DirectX8 이후에 음향과 3D 음향이 통합되었다.
DirectWrite : DirectX10.1 부터 지우너하는 글꼭 표현 API
DirectCompute : DirectX11 에 포함된 그래픽 프로세서를 사용한 연산 API

내부적으로 COM( Component Object Model ) 기술이 적용되어, 여러 라이브러리( 컴포넌트 )들의 집합으로 되어 있다.
*/

/* Direct2D */

/*
1. Direct2D Factory 생성
	HRESULT hr = D2D1CreateFactory(
					D2D1_FACTORY_TYPE_SINGLE_THREADED, &gpD2DFactory);
					=> Direct2D 의 멀티스레딩 모드를 지정, Direct2D 렌더링 엔진이 다중 스레드 환경에서 어떻게 동작할지 결정
					=> D2D1_FACTORY_TYPE_SINGLE_THREADED 를 사용하는 경우, 
						=> Direct2D 자체 내부적으로 스레드 관리를 수행하지 않는다. 따라서 Direct2D를 사용하는 
						=> 애플리케이션에서 직접 스레드 관리를 해야한다. 이 모드는 멀티스레드 환경에서 
						=> 단일 스레드에서만 Direct2D를 사용하는 경우에 적합하다.
					=> 반면에 D2D1_FACTORY_TYPE_MULTI_THREADED를 사용하면,
						=> Direct2D 렌더링 엔진이 멀티스레드 환경에서 내부적으로 스레드 관리를 수행하므로, 
						=> 애플리케이션 개발자가 직접 스레드 동기화를 처리할 필요가 없다. 
						=> 이 모드는 멀티스레드 환경에서 Direct2D를 사용할 때 권장되는 모드다.

2. 렌더 타겟 생성
	hr = gpD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hwnd,
			D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top),
			&gpRenderTarget);
			=> 클라이언트 영역을 구해온 뒤 윈도우 핸들에서 렌더타겟을 생성한다. ( 윈도우 내부에 그래픽을 그리는 것 )

3. 그리기
	void OnPaint(HWND hwnd)
	{
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);

		gpRenderTarget->BeginDraw();
		gpRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
		gpRenderTarget->EndDraw();

		EndPaint(hwnd, &ps);
	}
	=> 렌더 타겟에 그릴 준비를 하고 GDI 와 비슷한 개념으로 시작과 끝을 각각 지정하고 그 사이에 그리기

4. 리소스 해제
*/

/* ----- COM( Component Object Model ) ----- */

// 재사용이 가능한 컴포넌트( Component )를 만들어 배포를 쉽게 해준다.

/*
PC 조립 : 
	S 사의 HDD + C 사의 CPU + N 사의 그래픽카드를 조합하여 PC 를 완성한다.
	이처럼 PC 를 이루는 각 부품들이 바로 컴포넌트이며 이를 사용하여 조립할 수 있게 해주는 규격이 COM 이다.
*/

/*
Microsoft 의 COM 의 기능적인 특성은 다음과 같다.
	COM 오브젝트는 인터페이스에 의해 실행되는 클래스 또는 클래스 집합이다.
	인터페이스는 가상 함수의 집합이다.
	인터페이스는 IDirect3DDevice 처럼 I 접두어가 붙는다.
	각 오브젝트 및 인터페이스는 고유의 ID 값을 가진다.
		=> IID_ 접두어가 붙는다. ( Interface ID )
	C++ 객체와 같은 방식으로 생성하지 못한다.
		=> 이를 쉽게 해주는 DirectX API 의 헬퍼 함수들을 사용한다.
		=> 객체의 수명 역시 COM 방식이 따로 존재한다.
		=> 사용후에는 꼭 Release() 함수를 호출해 주어야 한다.
			=> 내부적으로 관리하기 때문에 new, delete 를 사용하지 않는다.
	COM 오브젝트의 메서드( 멤버함수 )들은 결과 코드를 나타내는 HRESULT 를 반환한다.
		=> 32 비트 정수로 성공/실패 여부 및 기타 정보를 나타낸다.
		=> Winerror.h 에 대부분 정의되어 있다.
		=> 성공은 주로 S_ 로 시작하며 실패는 E_ 로 시작한다.
*/

/* ----- Factory 패턴 ----- */

/*
객체 지향 프로그래밍( OOP )에서 클래스는 특정한 인스턴스를 생성하기 위한 정보들을 가지고 있는 것 이다.
인스턴스를 생성하기 위해서는 생성자를 이용해 특정 조건에 맞게 생성하기 위해 여러가지 정보들을 생성자의 매개변수로 넘겨준다.
매개변수도 중요하지만 동적 객체를 위해서는 메모리에 할당하는 방식( new 같은 기능 )도 중요하다.
OOP 의 특징인 다형성으로 넘어가게 되면 더욱 더 복잡해 진다.
*/

/*
int main()
{
	Character* pCharacter{};

	switch (job)
	{
	case WARRIOR:
		pCharacter = new Warrior(...);
		break;
	case WIZARD:
		pCharacter = new Wizard(...);
		break;
	case THIEF:
		pCharacter = new Thief(...);
		break;
		...
	}
}

위와 같이 각 직업에 맞게 생성자를 호출해줘야 하는데, 매우 불편하다. 업데이트로 신규 직업이 추가되면 더욱 더 힘들어진다.
이런 오브젝트의 생성을 관리하는 별도의 오브젝트가 있으면 좋겠다라는 생각에서 시작한 것이 Factory 패턴이다.
오브젝트를 찍어내는 공장인 셈이다.
즉, 오브젝트 생성을 처리하는 오브젝트 Factory 라고 볼 수 있다.
*/

/* 포인터의 포인터? 이중 포인터? */

// COM 객체 즉 DirectX 를 사용하면 이런 형태를 자주 사용하게 된다.

/*
void Swap(int* a, int* b) { ... }

int value1{ 1 };
int value2{ 2 };
Swap(&value1, &value2);

값으로 전달해서는 변수 값을 변경할 수 없다. 참조를 위해 포인터를 사용하는 것
*/

/*
void Swap(char** a, char** b) { ... }

char* value1{ "ab" };
char* value2{ "cd" };
Swap(&value1, &value2);

동적으로 생성된 자료구조는 특히 위와 같은 형태가 될 수 밖에 없으며, 이러한 것을 포인터의 포인터라고 부르는 개념이다.
참조형을 사용하지 않는 이유는 아직 다양한 플랫폼을 지원하기 위해서는 C++ 보다는 조금 더 빠른 C 를 사용하기 떄문이다.
*/

/* ----- COM 객체의 함수 호출 ----- */

// void **ppIDevice
// COM 함수를 사용하다 보면 **( 포인터에 대한 포인터, pp )를 자주 보게 된다.
// 위 매개변수를 풀어서 기술하자면 Deviec 인터페이스에 대한 포인터의 주소가 된다.

// C++ 객체와 달리 COM 객체는 함수에 바로 접근할 수 없다.
// 인터페이스에 대한 포인터를 획득한 다음 그 인터페이스에서 함수를 호출하는 방식을 취해야 한다.

/*
IMyInterface* pIMy;
...
pIMy->Functions();

그런데 인터페이스는 직접 생성하는 것이 아니라 대부분 COM 에서 제공하는 헬퍼 함수를 통해 생성한다.
따라서 인터페이스를 생성하기 위해서는 주소를 넘겨 줘야 한다.

IMyInterface* pIMy;

HRESULT hr = CreateMyCOM(&pIMy);

pIMy->Function();
*/

/* ----- 모니터와 픽셀 ----- */

// 초기에는 출력 값이 On/Off 불빛으로 들어와서 하나 하나 해독해야 했지만, 모니터가 등장하면서 사용자에게 시각적으로 결과를 보여 줄 수 있게 되었다.
// 화면에 어떤 멋진 최신 3D 그래픽이 나오더라도 컴퓨터는 내부에서 0 과 1 들의 뭉치로만 인식 할 뿐이다.

// 최초의 모니터는 화면에 0 과 1 만 표시할 수 있었기 때문에 0( 검은색 ), 1( 흰색 )의 흑백 모니터 였다.
// 백열 전구들이 패널에 빼곡하게 나열되어 있었고 여기에 화면을 표시했다.
// 이런 전구 하나가 화면에 표시되는 화면( Picture )의 원소( Element )가 된다고 하여 Pixel( 픽셀, 화소 )이라고 불렀다.
// 또한, 가로 X 세로 전구의 갯수를 Resolution( 해상도 )라고 한다.
// 기술이 좀더 발전하면서 흑백이 아닌 칼라를 표실할 수 있게 되었다. 하나의 픽셀을 세분화한 Sub Pixel( 서브 픽셀 )을 도입하면서 가능해졌는데 빛의 3요소인 RGB 를 섞어서 표시한 것이다.
// 화면의 점 하나( 픽셀 )는 RGB 세 개의 값을 조합해서 만들 수 있다.

/* ----- DPI( Dots Per Inch ) ----- */

// 원래는 인쇄물에서 자주 사용되던 용어인데, 스마트 폰이 등장하고 작은 화면에서 높은 해상도를 보여주기 위해 최근에는 자주 사용된다.
// 1인치에 몇 개의 점이 들어가 있는가에 따른 단위로 높으면 높은 퀄리티의 이미지를 볼 수 있다.

/*
PPI 는 Pixel Per Inch 의 약자로 점이 아닌 픽셀이 기준이다.

모바일 개발을 진행할 때 iOS 는 DPI 를 사용하고 Android 는 PPI 를 사용한다.
*/

/* ----- 감마 보정( Gamma Correction ) ----- */

/*
게임에서 감마 설정을 열면 왼쪽은 안보이고 오른쪽은 거의 보일 정도로 밝기를 조절해 주는 방식의 설정이 있다.

사람의 눈은 밝기에 대해 비선형적으로 반응한다.
아주 밝음이 1이고 아주 어두움이 0이라고 가정하면 단계별로 차이를 느끼는 것이 아니라 어느 지점이 되면 어둡고 밝게 되는 것인데,
컴퓨터를 통해 얼마 되지 않는 색상( RGB 0 ~ 255 단계 )으로 이미지를 표현하면 밝기를 변화시켜도 갑자기 안보이게 되는 ( posterization, 단절현상 )이 발생하게 된다.
특히나 어두운 부분에 대해서는 매우 심하게 나타난다.

따라서, 최소한의 색상 공간안에서 사람이 잘 구분할 수 있도록 색상 분포를 수정하는 작업을 감마 보정이라 한다.
정확하게는 Gamma Encoding 이 맞다.
*/

/*
1.0 이 기본 감마( 직선이라 Linear 라고도 한다. )이며 2.2 곡선을 Gamma 보정이라고 자주 사용한다.
카메라로 촬영한 기본 색상은 1.0 직선 처럼 생성되지만 실제로 사람의 눈이 인식하는 색상은 2.2 곡선과 같은 형태로 분포된다.
*/

/*
단순히 색상 공간을 32단계로 잘게 쪼개보자. 선형 방식은 검은색 -> 흰색의 단계를 일정한 비율로 줄여 나가는 것이며,
감마 보간은 최대한 고르게 색상이 분포되도록 수정해 준 것이다.

2.2 보정을 사용하면 어두운 부분이 잘 표현되어 있기 때문에 공포 게임등에서 이런 감마 보적을 중요하게 생각한다.
*/

/* ----- Wrap Mode of Extend Mode ----- */

// 이미지를 표현할 때 원본보다 크게 그릴 경우가 있다. 이를 표현하는 방법을 Extend Mode 라 한다.
// 3D 그래픽에서는 기하 도형을 이미지로 감싸는 방식이라 Wrap 이라고도 한다.

/*
CLAMP : 마지막 픽셀을 늘려서 사용
WRAP : 이미지를 반복( 타일링 )
MIRROR : 반전시킨 이미지를 사용
*/

/* ----- 프레임 워크 ----- */

// 프레임워크( Framework )란 뼈대 혹은 체계를 뜻한다. 즉, 프로그래밍에서는 특정 운영체제,
// 특정 그래픽 라이브러리를 위한 응용프로그램 표준 구조를 구현한 클래스와 라이브러리를 애플리케이션 프레임워크( Application Framework )라 부른다.

/* 라이브러리 / API / SDK / Framework */

/*
Library :
	프로그램에서 자주 사용할 편리한 함수 및 기능들을 모아 둔 모듈을 말한다.
	쉽게 사용할 수 있도록 정의를 담은 헤더( .h )파일과 컴파일된 라이브러리( .lib )형태로 제공된다.

Application Programming Interface :
	앱 개발을 위해 주로 운영체제에서 필요한 기능들을 제공하는 인터페이스이다.
	앱과 하드웨어를 연결해 주는 역할을 한다.

Software Development Kit : 
	API 와 거의 같은 의미이지만 개발을 도와주는 다양한 도구( 유틸리티 )들을 제공하기도 한다.

Framework :
	지금까지 살펴본 도구들은 게임 개발을 도와주는 도우미로 실제 게임의 흐름에는 관여하지 않는다.
	그래픽 라이브러리, 사운드 라이브러리 등과 같이 특정한 기능을 편리하게 만들 수 있게 도와줄 뿐이다.
	하지만, 프레임워크는 개념이 약간 다르다. 이런 도구들을 모아서 다양한 앱을 만들 수 있도록 앱의 기본 흐름을 규정한다.
	심지어 데이터에 사용할 파일 포멧 같은 경우도 프레임워크가 지정한 것을 사용해야만 한다.

그래픽, 사운드와 같은 복잡한 기능들은 라이브러리나 SDK의 도움을 받고, 기본적인 초기화 해제 작업을 미리 작업해 두면
그것이 바로 프레임워크가 된다.
이렇게 프레임워크로 묶어두면 다음에 게임을 만들 때 매우 편리해 진다.
*/

/* Microsoft::WRL::ComPtr */

// 프레임워크를 만들려면 뭔가 그럴듯 하게 만들고 싶은데 COM 오브젝트들은 C++ 객체와 생성/소멸 취급 방법이 다르니
// 스마트포인터를 사용할 수가 없다.

/*
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

...

SAFE_RELEASE(gpRadialBrush);

#define 은 컴파일될 때 해당 내용을 바꿔치기 해주므로 간단히 위와 같이 사용할 수 있지만, 최근 추세는 define을 잘 사용하지 않는 분위기도 하니 다른 방법을 찾아 보자.
*/

// 마이크로소프트에서는 최신 트렌드에 맞게 COM 오브젝트에 대한 스마트 포인터 기능을 Windows 8.x SDK 부터 추가했는데 그것이 바로 ComPtr 이다.
// Microsoft::WRL::ComPtr 은 COM 오브젝트에 대한 스마트 포인터 템플릿으로 Windows RunTime(WRT) C++ 프로그래밍에서 사용할 수 있다.
// 순수 C++ 템플릿이기에 WRT 및 고대의 Win32 역시 그대로 사용이 가능하며 Windows 8 SDK 는 Windows 7과 하위호환도 되므로 안심하고 사용할 수 있다.
// ComPtr은 std::shared_ptr 과 같은 방식으로 내부에서 참조 카운트를 가지고 있으며 여러곳에서 사용하다가 참조 카운트가 0 이 되면 해제되는 방식을 취하고 있다.

/*
#include <wrl.h>
#include <wrl/client.h>

<wrl.h> 를 포함하면 간단히 사용이 가능하다. <wrl.h> 에는 ComPtr 이외에도 많은 기능들이 들어 있기 때문에 좀 더 가볍게 사용하고 싶다면 <wrl/client.h>를 포함시키면 된다.

Microsoft::WRL::ComPtr<T> variable;

Microsoft::WRL::ComPtr<ID2D1Factory> mspD2DFactory{};
*/

/* 초기화 및 해제 */

// 일반적으로 COM 객체는 팩토리 또는 헬퍼 함수를 통해서 생성되고, 매개변수로 인터페이스에 대한 포인터의 주소(**)를 넘겨주는 형태
// ComPtr은 이런 특성을 GetAddressOf() 메서드를 제공한다.

/*
HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mspD2DFactory.GetAddressOf());
만약 ComPtr 오브젝트를 클래스 멤버로 사용하고 있고, 이미 초기화가 되어 있는지 명확하지 않으면 안전하게 ReleaseAndGetAddressOf() 메서드를 사용할 수 있다.
해제는 자동으로 이루어지지만 명시적으로 수행하고 싶을 떄는 Reset() 메서드를 사용하면 된다.
mspD2DFactory.Reset();
*/

/* 메서드에서의 ComPtr */

/*
ComPtr 역시 자신의 인터페이스를 통해 메서드를 호출할 때는 일반 포인터와 동일하게 사용하면 된다.
mspRenderTarget->BeginDraw();

간혹 COM 오브젝트의 메서드 호출에서 COM 오브젝트의 포인터가 필요한 경우가 있다.
hr = mspRenderTarget->CreateGradientStopCollection(
	gradientStops.Get(),
	2,
	D2D1_GAMMA_2_2,
	D2D1_EXTEND_MODE_CLAMP,
	&pGradientStops
	);
단순히 mspRenderTarget->CreateGradientStopCollection(gradientStops, ... )를 호출해도 특별한 문제가 없다.
하지만 위와 같이 명시적으로 Get()을 통해 포인터에 접근하는 것이 좋다.
*/

/*
매개변수로 사용할 때는 주의해야 한다. 기본적으로 shared_ptr 방식이므로 그냥 넘겨주면 참조 카운트가 하나 증가해 버린다.
이를 피하기 위해 다음과 같이 사용한다.
void Func(const Microsoft::WRL::ComPtr<T>& param);
또는
void Func(T* param);
*/

/* 예외 처리 */

/*
#include <d2d1.h>
#include <wrl/client.h>
#include <exception>
#include <stdio.h>

class com_exception : public std::exception
{
public:
	com_exception(HRESULT hr) : result(hr) {}

	virtual const char* what() const override
	{
		static char str[64] = {};
		sprintf_s(
			str, "Failure with HRESULT of %08x",
			static_cast<unsigned int>(result);
		);
		return str;
	}

private:
	HRESULT result;
};

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw com_exception(hr);
	}
}

com_exception 클래스는 멤버 변수로 HRESULT 를 가지고 있으며 생성자
com_exception(HRESULT)와 오버라이드한 what() 멤버 함수로 되어 있는 간단한 클래스이다.
그리고 클래스이긴 하지만 예외 처리에서 사용되는 구문과 통일하기 위해서 소문자로 만들었다.
*/

/*
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HISNTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	...
	try
	{
		myFramework.Init(hwnd);
	}
	catch (const com_exception& e)
	{
		static wchar_t wstr[64] = {};
		size_t len;

		mbstowcs_s(&len, wstr, e.what(), 64);
		MessageBox(
			nullptr, wstr, L"DirectX Exception",
			MB_ICONEXCLAMATION | MB_OK
		);
	}
	...
}
*/

/* ----- 윈도우 헬퍼 ----- */

/*
WinMain() 함수는 다음과 같은 세가지로 구분할 수 있다.
	1. 윈도우 생성
		=> Init() 함수로 통합
	2. 메시지 루프
		=> GameLoop 함수로 통합
	3. 윈도우 프로시저( 메시지 처리 )
		=> 멤버함수로 만들어 클래스에 포함
*/

/* 윈도우 프로시져 */

/*
윈도우 생성에 필요한 인자들
	HINSTANCE : WinMain 함수에서 인스턴스를 받아서 윈도우 생성
	LPCWSTR : 윈도우 이름으로 캡션에 표기되는 문자열
	윈도우 크기 : 윈도우의 크기를 지정할 때 사용
*/

/* ----- Direct2D 리소스 ----- */

// 하드웨어의 성능을 활용한 그리기 API( Application Programming Interface )는 CPU 중심의 리소스들과 CPU에서도 잘 실행되는 그리기 명령들을 가지고 있으며 그 중 일부만 하드웨어 가속을 지원한다.
// 왜냐하면 GPU는 제작사별로 성능이나 스펙이 다르기 때문에 하드웨어 가속 리소스를 사용하지 못하는 경우도 존재하므로 가능할 때는 GPU 리소스를 사용하고 그렇지 못하면 CPU의 리소스를 사용할 수 있어야 하기 때문이다.

/*
Direct2D 는 이러한 개념을 위해 리소스를 크게 2가지로 구분한다.
	장치 독립적인 리소스( Device-Independent Resource )
		ID2D1Factory 와 같이 CPU 에서 보관되는 리소스
	장치 의존적인 리소스( Device-Dependent Resource )
		ID2D1RenderTarget과 같이 GPU 에 보관되는 리소스
		하드웨어 가속이 사용가능하다면 GPU 의 리소스에 매핑(연결)되어 빠른 그리기가 가능
*/

/* ----- 장치 손실( Device Lost ) ----- */

// 이러한 하드웨어 가속 리소스는 빠르고 높은 품질이라는 장점 대신 CPU/RAM 에 비해 매우 한정적인 GPU/V-RAM 을 사용하다 보니 리소스 부족현상을 격게 된다.
// ALT + TAB 으로 작업 전환을 하거나 시스템 윈도우가 만들어 질 때, 절전 모드가 작동하거나 전체화면 모드로 다른 앱이 실행되거나 등 그래픽에 민감한 작업을 할 경우 Device Lost 가 발생하게 된다.

// 특히 게임은 엄청난 GPU/V-RAM 을 사용하므로 이런 현상이 자주 발생한다. 이런 장치 손실이 발생하면, 장치 의존적인 리소스는 아무것도 사용할 수 없는 상태가 되기 때문에 기존 리소스들은 모두 해제하고 다시 만들어야 한다.

/*
하지만 DirectX11 이후가 되면서 마이크로소프트에서 이런 불편함을 해소할 기능을 추가했다.
가상 그래픽 디바이스 인터페이스라는 개념을 사용하여 여러 개의 앱이 하나의 장치를 사용해도 문제가 없도록 개선했기 때문에 거의 발생하지 않는다.
하지만, 실제 물리적인 장치와 연결이 끊어지는 다음과 같은 경우는 어쩔 수 없이 장치 손실이 발생한다.
	그래픽 카드 드라이버 업그레이드
	절전용 그래픽카드에서 고성능 그래픽 카드로 변경될 때
		=> 요즘은 CPU에 내장 그래픽카드가 달린 경우가 많다. 성능이 당연히 떨어지므로 게임은 별도의 그래픽카드를 사용하는 형태 등으로 두 그래픽카드가 스위칭 되는 경우다.
	실제 장치가 응답이 없을 경우
	외장 그래픽카드( USB 등 )가 실제로 제거되거나 추가될 때
*/

// DirectX11 이전 버전 역시 위 같은 경우는 발생한다. 하지만 기존과 달리 ALT + TAB 등의 작업 전환에서는 장치 손실이 발생하지 않아, 매우 안정적인 게임을 만들 수 있게 되었다.
// Direct2D 에서는 장치 손실을 체크할 수 있는 시점은 모든 그리기가 끝나서 화면에 표시하는 시점, 즉 ID2D1HwndRenderTarget:EndDraw() 함수의 반환값으로 알 수 있다.
// 이 반환값이 S_OK 아니라면 장치 손실에 대한 처리를 해야 한다.

/* ----- 인라인 함수( inline function ) ----- */

// inline 키워드는 함수를 인라인 함수로 만들어 주는 것으로, 단어 그대로 줄 안에 있는 함수라는 뜻
// 함수를 개별 호출로 처리하는 것이 아니라 프로그램 코드 내부에 함수 코드를 삽입해 준다는 의미
// #define 처럼

/*
void f()
{

}
int main()
{
	f();
}

일반적인 함수 호출 과정은 다음과 같다.
	main() 진입
	f() 호출
	호출 스택( Call Stack )에 매개변수 정보들 저장
	f() 반환
	호출 스택에서 Pop
*/

/*
inline void f()
{

}
int main()
{
	f();
}

하지만 인라인 함수는 다음과 같다.
	main() 진입
	f() 해당하는 코드 실행
*/

// 함수 호출에 필요한 호출 스택에 정보를 Push, Pop 하는 과정이 없어서 빠르게 처리할 수 있다.
// 장점 : 빠른 성능
// 단점 : 자주 호출하는 인라인함수는 코드의 양이 길어진다.

/*
일반 함수는 선언/정의 앞에 inline 키워드를 붙인다.

inline void Test();

void Text();
...
inline void Text()
{

}
*/

/*
멤버 함수는 반드시 헤더파일에 정의해야 한다.( 코드를 바로 복사할 수 있어야 하기 때문 )

class MyClass
{
	inline void Func()
	{

	}
};

class MyClass
{
	void Func();
};
inline void MyClass::Func() {}

inline 으로 선언해도 컴파일러가 판단해서 거부할 수도 있다.
*/