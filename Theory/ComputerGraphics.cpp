/* ----- 컴퓨터 그래픽스 ----- */

// 기존에는 컴퓨터 메모리에 이미지를 저장하고 있다가 이를 그래픽 카드 메모리로 전송하는 방식을 사용했다.
// 좀더 적확하게는 그래픽카드가 Frame Buffer 를 갱신할 때 CPU 에 요청해서 데이터를 읽어 가는 방식이었다.
// 따라서 게임 개발자들은 주로 메모리에 화면에 그릴 이미지를 들고 있는 경우가 많았는데 이를 구분해서 Back Buffer 라고 불렀다.
// Frame Buffer 를 비슷한 개념으로 만들기 위해 Front Buffer 라고도 한다.

/*
	[RAM]		[V-RAM]
BackBuffer -> FrameBuffer -> 화면

위와 같이 주로 후면 버퍼는 데이터 전송을 편리하게 하기 위해 배열 형태로 관리한다.

1. 가상의 비디오카드 FrameBuffer( 1024 X 768 BITMAP )
2. 화면 정보를 담고 있는 메모리( BackBuffer )
3. 가상의 비디오 카드에 이미지 출력( BackBuffer -> FrameBuffer )
	a. 시뮬레이션 - FrameBuffer(BITMAP)를 모니터에 그려서 확인
*/

/*
#include "D2DFramework.h"
#include <memory>

const int BITMAP_WIDTH = 1024;
const int BITMAP_HEIGHT = 768;
const int BITMAP_BYTECOUNT = 4;

class BitmapExample : public D2DFramework
{
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspFrameBitmap{};
	std::unique_ptr<UTIN8[]> mspBackBuffer;

public:
	virtual HRESULT Initialize(HISNTANCE hInstance,
		LPCWSTR title = L"Direct2D Example",
		UINT width = 1024,
		UINT height = = 768) override;
	void Render() override;
};

간단한 테스트를 위해 1024 X 768 크기로 윈도우와 같은 크기로 만든다.
BYTECOUNT 는 한 픽셀의 바이트 수로 RGBA 로 구성할 예정이므로 4바이트로 지정한다.

Microsoft::WRL::ComPtr<ID2D1Bitmap> mspFrameBitmap; : 가상 프레임버퍼용 BITMAP 클래스이다. ID2D1Bitmap 클래스는 Direct2D에서 제공하는 BITMAP 클래스이다.
std::unique_ptr<UINT8[]> mspBackBuffer; : 후면버퍼를 위한 배열이다. 한 픽셀은 아래와 같은 4바이트가 한 묶음이 된다.
	[RED][GREEN}[BLUE][ALPHA]
따라서, 배열의 크기는 가로 X 세로 X 바이트수가 된다.
UINT8 은 마이크로소프트에서 별도로 정의해 둔 unsigned char 타입이다.

단순한 1차 배열인데 복잡하게 스마트포인터를 사용하여 선언한 이유는 스택과 힙의 차이 때문이다.
정적 배열( new UINT[], std::array )로 할당하게 되면 해당 메모리는 스택에 등록된다. 하지만 스택은 함수나 로컬 변수를 위한 매우 한정적인 공간으로 큰 배열을 할당해 버리면 금방 넘쳐 버린다.
최신 컴파일러 같은 경우는 컴파일 단계에서 오류를 발생하기도 한다.
따라서 매우 큰 배열을 할당하려면 동적으로 힙에 올려 두는 것이 좋다. 힙은 컴퓨터의 메모리 여유분 만큼 사용할 수 있다.
*/

/*
#include "BitmapExample.h"

HRESULT BitmapExample::Initialize(
	HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	D2DFramework::Initialize(hInstance, title, width, height);

	mspBackBuffer = std::make_unique<UINT8[]>(
		BITMAP_WIDTH * BITMAP_HEIGHT * BITMAP_BYTECOUNT);

	HRESULT hr = mspRenderTarget->CreateBitmap(
		D2D1::SizeU(BITMAP_WIDTH, BITMAP_HEIGHT),
		D2D1::BitmapProperties(
			D2D1::PixelFormat(
				DXGI_FORMAT_R8G8B8A8_UNORM,
				D2D1_ALPHA_MODE_IGNORE)
		),
		mspFrameBitmap.GetAddressOf()
	);

	ThrowIfFailed(hr);

	return S_OK;
}
void BitmapExample::Render()
{
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	mspRenderTarget->DrawBitmap(mspFrameBitmap.Get());

	mspRenderTarget->EndDraw();
}

D2DFramework::Init(hwnd); : 기반 클래스의 가상 함수를 호출해서 기본 초기화를 수행한다.
mspBackBuffer = std::make_unique<UINT8[]>(BITMAP_WIDTH*BITMAP_HEIGHT*BITMAP_BYTECOUNT); :
	힙에 후면버퍼로 사용할 배열을 생성한다. 원소는 UINT8 이며, 크기는 가로 x 세로 x 픽셀이다.
HRESULT CreateBitmap(D2D1_Size_U size, const D2D1_BITMAP_PROPERTIES& bitmapProperties, ID2D1Bitmap **bitmap); :
	size : 생성할 비트맵의 크기( pixel 단위 )
	bitmapProperties : D2D1_BITMAP_PROPERTIES 구조체로 픽셀 포멧과 DPI 를 지정( 렌더타겟에서 살펴본 것과 동일 )
	bitmap : ID2D1Bitmap 인터페이스에 대한 포인터의 주소
mspRenderTarget->DrawBitmap(mspFrameBitmap.Get()); :
	렌더타겟에 비트맵을 그린다. 좌표는 생략된 기본 매개변수로 0, 0 에 출력된다. 선언부로 이동해 보면 매우 다양한 매개변수가 존재하지만
	대부분 기본값으로 설정되어 있어서 비트맵만 넘겨줘도 된다.
*/

/* 후면버퍼 표시 */

// 준비한 후면버퍼를 프레임버퍼로 이동해 줘야하는데 이 과정을 Flip, Present 라 부른다.
// 직접 하드웨어 가속기능을 구현할 수는 없으니, 후면버퍼의 내용을 프레임버퍼에 복사하는 방식으로 간략화 해보자.

/*
...
class BitmapExample : public D2DFramework
{
	...
public:
	virtual HRESULT Initialize(HINSTANCE hInstance,
		LPCWSTR title = L"Direct2D Example",
		UINT width = 1024,
		UINT height = 768) override;
	void Render() override;

	void PresentBuffer();
};

void BitmapExample::PresentBuffer()
{
	mspFrameBitmap->CopyFromMemory(
		nullptr,
		&mspBackBuffer[0],
		BITMAP_WIDTH * BITMAP_BYTECOUNT
	);
}

HRESULT CopyFromMemory(
	const D2D1_RECT_U *dstRect, : BITMAP 에 저장할 영역, nullptr 을 지정하면 BITMAP 전체 영역
	const void		  *srcData, : 복사할 버퍼
	UINT32			  pitch		: 간격( width X byteCount )
	);
이 함수를 사용하면 BITMAP 리소스에 메모리 버퍼의 내용을 복사해 줄 수 있다.
*/

/* 화면에 픽셀 그리기 */

// x, y 좌표와 색상을 주면 해당 좌표에 점을 찍는 기능
// 후면 버퍼는 기본적으로 1차 배열이므로 2차원 공간의 매개변수를 인덱스로 계산하는 것이 필요하다.

/*
[0,0][0,1][0,2]
[1,0][1,1][1,2]
[2,0][2,1][2,2]

[0][1][2][3][4][5]...

위와 같이 매핑하려면 x,y 를 각각 분리하여 x 를 나머지, y 를 몫으로 보면 간단하게 계산이 가능하다.
index = x + y * ( width )
그런데, 후면 버퍼는 한 픽셀이 4바이트로 되어 있다.
기본적으로는 동일한 방식으로 계산이 가능하지만 width 값이 다르다. 한 픽셀이 여러개의 바이트로 이루어져 있으므로( width * byteCount )
를 사용해야 한다. 따라서 용어를 통일하기 위해 너비( width )가 아니라 간격( pitch )라는 단어를 주로 사용한다.
모니터의 특성인 scanline 이라고도 한다.
index  = x * byteCount + y * ( pitch )
pitch = width * byteCount
*/

/*
class BitmapExample : public D2DFramework
{
public:
	...
	void ClearBuffer(D2D1::ColorF color);
	void PresentBuffer();
	void DrawPixelToBuffer(int x, int y, D2D1::ColorF color);
};
void BitmapExample::DrawPixelToBuffer(int x, int y, D2D1::ColorF color)
{
	int pitch = BITMAP_WIDTH * BITMAP_BYTECOUNT;
	int index = pitch * y + x * BITMAP_BYTECOUNT;

	mspBackBuffer[index] = static_cast<UINT8>(color.r * 255);
	mspBackBuffer[index + 1] = static_cast<UINT8>(color.g * 255);
	mspBackBuffer[index + 2] = static_cast<UINT8>(color.b * 255);
	mspBackBuffer[index + 3] = static_cast<UINT8>(color.a * 255);
}

DrawPixel(1, 1, D2D1::ColorF::White); : 테스트로 렌더 루틴에 위 내용을 추가하면 1, 1 에 흰색 점을 찍을 수 있다.
*/

/* 알파( Alpha )값의 용도 */

// 픽셀포멧을 지정할 때는 항상 알파값이 존재했다. 이 값은 언제 사용하는 것일까?

/*
FillRectToBuffer(0, 0, 100, 100, D2D1::ColorF::Red);
FillRectToBuffer(50, 50, 100, 100, D2D1::ColorF::Green);

그래픽 성능이 발전함과 동시에 한 픽셀에 담을 수 있는 값이 늘어나면서 투명도를 조절할 수 있게 되었는데 이를 알파라 부른다.
기존의 이미지(RGB) 표현 이외에 별도의 채널을 두어 투명도를 지정하는 방식이라 알파 채널이라고도 한다.

위 이미지에서 처럼 당연히 같은 좌표의 픽셀은 나중에 그린 값으로 덮어쓰여지는데, 여기에 알파를 사용하여 섞으면 더 다양한 효과를 줄 수 있다.

결과 = 기존 색상 * (1.0f - alpha) + 신규 색상 * alpha
*/

/* ----- 그래픽카드 ----- */

// 모니터 화면은 크게 CPU, 그래픽카드, 모니터 출력의 과정으로 이루어져 있다.
// 그래픽카드, 비디오카드, 디스플레이카드, 그래픽보드, 디스플레이어댑터, 비디오어댑터 등 다양한 이름으로 불리고 있다.

/*
그래픽카드는 크게 다음과 같은 구성으로 되어 있다.

	GPU( Graphic Processing Unit ) : 
		3차원 그래픽이 유행하면서 등장한 그래픽 연산 전용 CPU 라고 생각하면 된다.
		CPU 보다 빠른 소수점 연산 처리와 3D 오브젝트를 화면의 픽셀로 변환하는 파이프라인( 셰이더라는 것을 사용 )으로 되어 있다.
	V-RAM( Video Random Access Memory ) :
		그래픽에 사용되는 내용을 저장하는 전용 메모리, 이미지 파일을 로딩해서 저장 한다던지 하거나 3D 오브젝트의 점( Vertex )를
		저장하는 용도로도 사용하지만 가장 큰 목적은 화면에 그릴 내용을 메모리( Frame Buffer )에 들고 있는 것이다.
		여기에서 바로, 모니터로 화면이 전송된다.
	출력( Output ) :
		모니터와 연결하는 인터페이스이다.
		VGA 단자( 혹은 D-Sub ), DVI, HDMI, Display Port 등 다양한 규격이 존재 한다.

	[CPU]			[GPU]			[모니터]
	RAM				VRAM
Application		 FrameBuffer
*/

/* ----- 비트맵( BITMAP ) ----- */

// Bit + Map 의 약자로 비트로 구성된 맵이라는 의미이다. 디지털 이미지를 저장하는 이미지 파일 포멧 중 하나이며 가장 기본적인 방식이다.

/*
픽셀 당 할당하는 비트의 크기에 따라 다양한 색을 표현할 수 있게 된다.

픽셀 당 비트 수	:	픽셀에 할당할 수 있는 색 수
1					2 ^ 1 = 2
8					2 ^ 8 = 256
16					2 ^ 16 = 65,546
24					2 ^ 24 = 16,777,216
32					2 ^ 32 = 4,294,947,296

과거에는 256색 이하의 색상을 조금 더 멋지게 그리기 위해 팔레트라는 개념을 사용했다.
색상 테이블을 별도로 준비해서 그 인덱스로 이미지를 표현하는 방식이다.
24비트( 예전에는 256 칼라와 비교하면 혁신이라 true color 라고도 했다. )이상에서는 그럴 필요가 없이 필셀마다 직접 색상을 표현할 수 있게 되었다.
*/

