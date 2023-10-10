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

/* ----- WIC( Windows Imaging Component ) ----- */

/* BMP 파일 불러와서 그리기 */

// 이미지는 픽셀로 이루어진 배열이며 이 정보를 파일로 저장한 것을 jpg, png 와 같은 그림파일이다.
// BMP 포멧은 픽셀 데이터를 배열로 저장하고 있기 때문에 간단하다.

/*
BMP 파일 구조

[이름]			[타입]				[설명]
BMP 헤더		BITMAPFILEHEADER	BMP 파일에 대한 정보
비트맵 정보		BITMAPINFOHEADER	BITMAP 구조에 대한 상세 정보
팔레트			LOGPALETTE			팔레트 인덱스와 색상에 대한 배열
비트맵 데이터	void *				실제 픽셀 배열
*/

/*
BITMAPFILEHEADER

WORD bfType : 파일 타입이다. 무조건 BM이 되어야 한다.
	=> ( 0x4D42 - B : 42, M : 4D 이지만 엔디언으로 인해 바뀌는 점 주의 )
DWORD bfSize : BMP 파일의 크기( byte )
WORD bfReserved1 : 예약 공간1
WORD bfReserved2 : 예약 공간2
DWORD bfOffBits : 비트맵 데이터가 있는 주소에 대한 오프셋
*/

/*
BITMAPINFOHEADER

DWORD biSize : 헤더의 크기( byte )
LONG biWidth : 비트맵 가로
LONG biHeigh : 비트맵 세로
WORD biPlanes : 1로 고정
WORD biBitCount : 1픽셀에 사용되는 비트 수( 1, 8, 16, 32 주로 사용 )
DWORD biCompression : 압축방식
DWORD biSizeImage : 비트맵의 크기
LONG biXPelsPerMeter : 미터당 가로 화소 수
LONG biYPelsPerMeter : 미터당 세로 화소 수
DWORD biClrUsed : 팔레트의 색상 수
DWORD biClrImportant : 무시
*/

/*
1. BMP 파일 열기
2. BITMAPFILEHEADER 읽기
3. BITMAPINFOHEADER 읽기
4. BITMAPFILEHEADER 의 bfOffBits 만큼 건너 뛰기
5. 픽셀 데이터 읽기
*/

/*
#include "D2DFramework.h"

class ImageExample : public D2DFramework
{
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspBitmap;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance,
		LPCWSTR title = L"Direct2D Example",
		UINT width = 1024,
		UINT height = 768) override;
	void Render() override;

public:
	HRESULT LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap);
};

Microsoft::WRL::ComPtr<ID2D1Bitmap> mspBitmap;
	BMP 파일을 읽어올 ID2D1Bitmap 인터페이스를 추가한다.
HRESULT LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap);
	반환값으로는 HRESULT 를 사용하고, Bitmap 인터페이스에 대한 포인터의 주소를 받아서 오브젝트를 생성한다.
	포인터의 포인터를 사용하는 이유를 다시 한 번 정리해 보면 다음과 같다.
		일반 변수를 매개변수로 받아서 값을 수정할 때 - 변수의 주소값이 필요
		포인터 변수를 매개변수로 받아서 값을 수정할 때 - 포인터 변수의 주소값이 필요
*/

/*
HRESULT ImageExample::LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
	std::ifstream file;
	file.open("Data/32.bmp", std::ios::binary);

	BITMAPFILEHEADER bmh;
	BITMAPINFOHEADER bmi;

	file.read(reinterpret_cast<char*>(&bmh), sizeof(BITMAPFILEHEADER));
	file.read(reinterpret_cast<char*>(&bmi), sizeof(BITMAPINFOHEADER));
	if (bmh.bfType != 0x4D42)
	{
		return E_FAIL;
	}
	if (bmi.biBitCount != 32)
	{
		return E_FAIL;
	}

	std::vector<char> pPixels(bmi.biSizeImage);
	file.seekg(bmh.bfOffBits);
	file.read(&pPixels[0], bmi.biSizeImage);

	int pitch = bmi.biWidth * (bmi.biBitCount / 8);

	file.close();

	HRESULT hr = mspRenderTarget->CreateBitmap(
		D2D1::SizeU(bmi.biWidth, bmi.biHeight),
		D2D1::BitmapProperties(
			D2D1::PixelFormat(
				DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE
			)
		),
		ppBitmap
	);

	ThrowIfFailed(hr);

	(*ppBitmap)->CopyFromMemory(
		nullptr,
		&pPixels[0],
		pitch
	);
	return S_OK;
}

1. 파일 읽기
	a. ifstream 을 사용하여 binary 모드를 열은다.
2. 파일 헤더 읽기
	a. BITMAPFILEHEADER 구조체로 읽어 오면 편하다.
	b. ifstream.read() 는 char* 를 매개변수로 넘겨줘야 한다.
	c. 따라서 reinterpret_cast 를 사용하여 구조체를 char* 로 변환하였다.
3. 비트맵 헤더 읽기
	a. BITMAPINFORHEADER 구조체로 읽어 오면 편하다.
	b. 헤더를 읽어 오면 비트맵 기본 정보를 알 수 있으므로 잘못된 파일은 걸러 준다.
4. 픽셀로 건너뛰기
	a. ifstream.seek() 을 사용하면 바이트 단위로 이동이 가능하다.
	b. 헤더의 bfOffBits 에 실제 픽셀에 대한 위치가 저장되어 있다.
5. 비트맵 읽기
	a. 비트맵을 저장할 공간으로 std::vector<char>를 사용했다.
		i. 크기는 비트맵 헤더의 biSizeImage 값이다.
	b. istream.read() 는 char* 를 받기 때문에 std::vector 에서 잔재주를 부려야 한다.
		i. std::vector 의 내부 자료형을 순차적
		ii. 따라서 첫 번째 우너소의 주소를 얻어오면 char* 와 같은 형이 된다.
6. 비트맵 생성
	a. ID2D1HwndRenderTarget::CreateBitmap 을 사용해 비트맵 인터페이스를 생성한다.
		i. 지난 예제의 프레임 버퍼 생성과 유사한다.
		ii. RGBA 원소들의 저장 순서는 BGRA 이다.

주의할 점은 std::vector 를 포인터로 변경하는 방식이다.
사실 BITMAP 은 조금 더 복잡한 구조이다. 헤더에서 압축 여부나 RGBA 포멧 정보등을 읽어 서 그에 맞게 파일을 읽어야 하지만,
여기에서는 주어진 파일에 대한 것만 처리했다.
기본적으로 BMP 파일은 Bottom-Up 으로 저장한다. 가끔 BITMAP 헤더에 biHeight 가 음수인 경우가 있는데 이 경우는 Top-Down 방식이다.
*/

/*
뒤집힌 이미지, pitch 단위로 읽어서 올바른 위치( 역순 )에 저장하면 된다.
HRESULT ImageExample::LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
	...
	file.seekg(bmh.bfOffBits);

	int pitch = bmi.biWidth * (bmi.biBitCount / 8);
	for (int y = bmi.biHeight - 1; y >= 0; y--)
	{
		file.read(&pPixels[y * pitch], pitch);
	}
	file.close();
	...
}
*/

/*
BMP 를 그릴 때 배경을 제거하고 그려보자
	배경색 RGM 30, 199, 250
	모든 픽셀을 수동으로 읽어서 배경색과 같으면 투명하게 만들어 주면 된다.
		한 바이트씩 전체 비트맵을 읽어 오는 코딩 작성
		읽어온 색상이 배경색과 같으면 RGBA를 모두 0으로 만든다.
		LoadBMP() 의 비트맵 생성에서 다음 속성을 변경해 줘야 한다.
HRESULT hr = mspRenderTarget->CreateBitmap(
	D2D1::SizeU(bmi.biWidth, bmi.biHeight),
	D2D1::BitmapProperties(
		D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_PREMULTIPLIED
		)
	),
	ppBitmap
);
*/

/*
HRESULT ImageExample::LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
	1. 파일 열기
	std::ifstream file;
	file.open("Data/32.bmp", std::ios::binary);

	BITMAPFILEHEADER bmh;
	BITMAPINFOHEADER bmi;

	2. BITMAPFILEHEADER 읽기
	file.read(reinterpret_cast<char*>(&bmh), sizeof(BITMAPFILEHEADER));
	3. BITMAPINFOHEADER 읽기
	file.read(reinterpret_cast<char*>(&bmi), sizeof(BITMAPINFOHEADER));
	if (bmh.bfType != 0x4D42)
	{
		return E_FAIL;
	}
	if (bmi.biBitCount != 32)
	{
		return E_FAIL;
	}

	std::vector<char> pPixels(bmi.biSizeImage);
	4. 픽셀로 건너뛰기
	file.seekg(bmh.biOffBits);
	5. 비트맵 읽기
	int pitch = bmi.biWidth * (bmi.biBitCount / 8);
	int index{};

	for (int y = bmi.biHeight - 1; y >= 0; y--)
	{
		index = y * pitch;
		for (int x = 0; x < bmi.biWidth; x++)
		{
			char r{}, g{}, b{}, a{};

			file.read(&b, 1);
			file.read(&g, 1);
			file.read(&r, 1);
			file.read(&a, 1);

			if (r == 30 || g == 199 || r == 250)
			{
				r = g = b = a = 0;
			}

			pPixels[index++] = b;
			pPixels[index++] = g;
			pPixels[index++] = r;
			pPixels[index++] = a;
		}
	}

	file.close();

	HRESULT hr = mspRenderTarget->CreateBitmap(
		D2D1::SizeU(bmi.biWidth, bmi.biHeight),
		D2D1::BitmapProperties(
			D2D1::PixelFormat(
				DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED
			)
		),
		ppBitmap
	);

	ThrowIfFailed(hr);

	(*ppBitmap)->CopyFromMemory(
		nullptr,
		&pPixels[0],
		pitch
	);
	return S_OK;
}
*/

/* Windows Imaging Component */

// 위 예제에서 구현한 비트맵 로딩 함수는 실전에서는 사용하기 어렵다. BMP 포멧은 용량도 클 뿐 아니라, 완벽하게 구현하지
// 않아서 못 읽는 경우가 더 많다. png 와 같은 포멧들은 압축 해제 방식 떄문에 구현하기 매우 어렵다.

// 마이크로소프트에서는 윈도우 시스템 개발자들을 위해 디지털 이미지들을 위해 저수준( low-level ) API 를 추가해 주었다.
// Windows Imaging Component 는 Windows Vista 부터 포함되어 있으며 Windows XP 이하는 추가로 설치하면 사용이 가능하다.

/*
#include <wincodec.h>
#include "D2DFramework.h"

class ImageExample : public D2DFramework
{
	Microsoft::WRL::ComPtr<IWICImagingFactory> mspWICFactory;
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspBitmap;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance,
		LPCWSTR title = L"Direct2D Example",
		UINT width = 1024,
		UINT height = 768) override;
	void Render() override;

public:
	void Release() override;

	public HRESULT LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap);
	HRESILT LoadWICImage(LPCWSTR filename, ID2D1Bitmap** ppBitmap);
};

WIC 를 사용하기 위해서는 wincodec.h 를 포함시켜야 한다. WIC 역시 팩토리 패턴이라 팩토리를 위한 스마트 포인터를 멤버로 선언하고, 개별적인 해제가 필요하므로 Release 를 오버라이딩 했다.
기존 함수와 구분하기 위해서 WIC를 사용한 파일 읽기용으로 LoadWICImage 멤버함수도 추가했다.
*/

/*
#include <fstream>
#include <vector>
#include "ImageExample.h"

#pragma comment( lib, "WindowsCodecs.lib" )

HRESULT ImageExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	CoInitialize(nullptr);
	HRESULT hr = ::CoCreateInstance(CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(mspWICFactory.GetAddressOf()));

	D2DFramework::Initialize(hInstance, title, width, height);

	LoadWICImage(L"Data/32.bmp", mspBitmap.GetAddressOf());

	return S_OK;
}

void ImageExample::Release()
{
	D2DFramework::Release();

	mspWICFactory.ReleaseAndGetAddressOf();

	CoUninitialize();
}

#pragma comment( lib, "WindowsCodecs.lib" ) : Direct2D 와 마찬가지로 사용할 라이브러리 WindowsCodecs.lib 를 병합시켜 준다.

CoInitialize(nullptr); : COM 오브젝트를 사용하기 위해 시스템을 초기화 한다.
	DirectX 도 COM 을 사용한다고 했는데, 초기화를 불러 준 적은 없다. DirectX 는 COM 환셩을 100% 사용하지 않고
	개념만 일부 사용하는 형식을 취하고 있다.
	다른 플랫폼으로의 확장을 위해 윈도우 전용의 COM 시스템을 사용할 수 없었을 것이다. 하지만 WIC 는 이름 그대로
	윈도우 전용 환경이므로 COM 을 완벽하게 적용해야만 한다.

HRESULT CoCreateInstance()
	REFCLSID rclsid Reference to Class ID, 생성할 오브젝트의 클래스 구분자
	LPUNKNOWN pUnkOuter 집합체( aggregate object )를 위한 포인터, nullptr 을 넘기면 집합체가 아닌 단일 개체로 생성한다.
	DWORD dwClsContxt Class Context, 생성된 객체가 실행되는 환경을 지정한다.
	REFIID riid Refernce to interface ID
	LPVOID *ppv riid로 지정한 인터페이스 포인터에 대한 주소로 생성된 인터페이스 포인터를 돌려 준다.

매개변수는 5개를 요구하지만 인자는 4개만 줄 수 있다. IID_PPV_ARGS() 는 매크로로 내부에서 2개의 매개변수를 넘겨 준다.
두 개 모두 명시해도 되지만, riid는 우리가 선언한 mspWICFactory로 부터 유추할 수 있기 때문에 코딩 몇 줄 줄이기 위해 사용하는 것이다.
풀어서 쓰면 IID_IWICImaginaFactory, mspWICFactory.GetAddressOf() 로 넘겨주면 된다.
*/

/*
파일 읽기
	1. 디코더 생성
	2. 디코더에서 프레임(frame) 획득
	3. 컨버터(Converter)를 사용해 데이터를 변환
	4. 변환된 데이터에서 비트맵 생성
*/

/*
HRESULT ImageExample::LoadWICImage(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
	Mircrosoft::WRL::ComPtr<IWICBitmapDecoder> bitmapDecoder;
	HRESULT hr{};

	hr = mspWICFactory->CreateDecoderFromFilename(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecoderMetadataCacheOnLoad,
		BitmapDecoder.GetAddressof());
	ThorwIfFailed(hr);

	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
	ThrowIfFailed(bitmapDecoder->GetFrame(0, frame.GetAddressOf()));

	return S_OK;
}

HRESULT IWICImagingFactory::CreateDecoderFromFilename()
	LPCWSTR wzFilename null-terminated wide char string
	const GUID *pguidVendor Globally Unique Identifider ( 절대 중복되지 않는 고유한 난수로 자주 보게됨 )
		고유의 포멧을 가진 회사 별 고유의 디코더를 지정할 수 있다.
	DWORD dwDesiredAccess 읽기,쓰기,읽기쓰기 등의 파일 접근 방식을 지정한다.
	WICDecodeOptions metadataOptions 메타 데이터 옵션이다.
		데이터를 설명하기 위한 데이터로 meta는 ~에 대한 이라는 의미이다. 이미지는 단순한 픽셀 데이터지만,
		gif와 같이 여러 장이 모여 있는 경우도 있다. 이러한 픽셀 데이터에 대한 추가 데이터가 메타 데이터가 되는 것이다.
		캐시를 할 것인지, 바로 로딩할 것인지를 정한다.
	IWICBitmapDecoder **ppIDecoder 생성된 디코더를 담을 포인터 주소

HRESULT IWICBitmapFrameDecode::GetFrame()
	IWICBitmapFrameDecode **ppIBitmapFrame 디코딩된 프레임을 담을 포인터의 주소이다.
*/

/*
HRESULT ImageExample::LoadWICImag(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
	...
	// 포멧 컨버터
	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	ThrowIfFailed(mspWICFactory->CreateFormatConverter(converter.GetAddressOf()));

	hr = converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0,
		WICBitmapPaletteTypeCustom);
	ThrowIfFailed(hr);

	hr = mspRenderTarget->CreateBitmapFromWicBitmap(
		converter.Get(),
		mspBitmap.ReleaseAndGetAddressOf());
	ThrowIfFailed(hr);

	return S_OK;
}

HRESULT IWICImagingFactory::CreateFormatConverter():
	IWICFormatConverter **ppIFormatConverter 생성된 컨버터를 담을 포인터의 주소이다.

HRESULT IWICFromatConverter::Initialize()
	IWICBitmapSource *pISource 변환할 비트맵을 지정한다. 디코딩한 프레임을 넘겨주면 된다.
	REFWICPixelFormatGUID dstFormat 변환 후의 픽셀 포멧을 지정한다.
	WICBitmapDitherType dither 디더링 타입을 지정한다.
		컴퓨터는 현실 세계 보다 표현할 수 있는 색상이 제한적이기 때문에 점과 점을 패턴으로 연결하는 편법을 사용한다.
	IWICPalette *pIPalette 변환에 적용할 때 사용할 색상 팔레트를 지정한다.
	double alphaThresholdPercent 알파값의 임계점을 지정한다. 가령 알파가 25미만인 픽셀을 모두 투명하게 만들거나 할 수 있다.
	WICBitmapPaletteType paletteTranslate 변환에 사용할 팔레트 타입을 지정한다.
*/

/* ----- 스프라이트( Sprite ) ----- */

// 컴퓨터 그래픽에서 2D 이미지, 특히 독립적을 따로 움직이는 오브젝트를 스프라이트라고 부른다.
// 요적이라는 어원처럼 이미지가 배경 이미지 위로 떠 다니는 모습이 비슷해 지어진 이름이다.
// 초기 게임기나 컴퓨터들은 이런 스프라이트를 하드웨어로 제어하여 빠른 처리를 하려고 노력했다.

/* ----- 싱글턴( Singleton )패턴 ----- */

// 관리자는 하나만 존재하면 된다.
// 클래스 개념으로 설명하면 여러 번 생성자가 불리더라도 인스턴스가 하나만 유지되는 형태다.
// 이런 스타일의 코딩을 위해서 고안된 것이 싱글턴 패턴이다.

/*
생성자가 여러 번 호출되어도 실제로 생성되는 객체는 하나
또 다시 생성자가 호출되면, 최초 생성 이후에는 이미 생성된 객체를 반환

단 하나의 객체를 위해서는 어쩔 수 없이 정적 멤버를 사용할 수 밖에 없긴 하지만, 외부로 노출되지 않는 장점이 있다.

class Singleton final
{
public:
	static Singletone& Instance()
	{
		static Singleton instance;
		return instance;
	}

private:
	Singleton();
	Singleton(const Singleton&);
	void operator = (const Singleton&);

public:
	~Singleton();

public:
	void MyFunction();
};

Singleton::Instance().MyFunction();

class ... final : 매니저는 그 자체로 기능 구현이 끝나는 클래스
	즉, 더이상 파생되어서는 안되므로 final 키워드를 명시적으로 붙여 주는 것이 좋다.
static Singleton& Instance() : 싱글턴 패턴은 지금까지의 객체 인스턴스화 방식과는 다르게 이 함수를 통해서 접근한다.

private:
	Singleton();
	Singleton(const Singleton&);
	void operator=(const Singleton&);
순서대로 기본 생성자, 복사 생성자, 대입 연산자이다.
이들을 private으로 막아 버린 이유는 전역 객체나 정적 객체들 처럼 다른 곳에서 내부에 접근 불가능하도록 막기 위해서 이다.
기본적으로 내부 정적 변수 instance를 통해 모든 기능을 제어하므로 클래스가 복사되거나 변경되면 안되기 때문이다.

물론 싱글턴 역시 패턴을 잘 알지 못하는 개발자에게는 추적이 어려운 방식이기도 한다.
아무리 좋은 기술이라도 적절한 곳에 적절히 사용해야 그 효과를 볼 수 있는 것 처럼, 싱글턴 패턴 역시 너무 남발하지 않는 것이 좋다.
다음과 같은 문제가 있을 수 있다.
	스레드 동시성 문제
		인터넷 검색을 해 보면 thread-safe 방식의 싱글턴 패턴을 많이 발견할 수 있다.
	앱 종료시까지 메모리에 상주
	테스트가 어려움
		소프트웨어 공학론 중 단위 테스트라는 것이 있다. 개별 단위로 테스트를 수행하는 것인데,
		싱글턴을 사용하면 이런 방식에 위배 된다.ㅏ
	순환 종속 발생
		A 는 B 의 싱글턴을 사용
		B 는 A 의 인스턴스를 사용
		관리자를 만들다보면 위와 같은 경우가 많이 발생한다. 이러한 것을 순환 종속이라 부르면 OOP 에서는 피하는 개념이다.
	클래스 확장이 어려움
		OOP 의 개발-폐쇄 개념이다.
		싱글턴을 사용하면 구현과 인터페이스가 하나로 묶이게 되므로 확장성은 좋지 않다.
*/

/* ----- 이미지 보간( Image Interpolation ) ----- */

// 실제로 우리가 보는 이미지는 모눈종이에 찍은 점이다. 그렇기 때문에 표현하려는 이미지가 정확하게 픽셀의 가운데가 될 수 없는 경우도 있다.
// 이러한 문제를 해결하기 위한 것이 보간( Interpolation )이며 다음과 같은 방법이 자주 사용된다.

/*
Nearest-neighbor : 가장 가까운 픽셀을 선택한다.
Linear : 2개의 가까운 픽셀을 선택한 다음 선을 그리고 색상을 중간값으로 만들어 준다.
Bilinear : 4개의 가까운 픽셀을 선택한 다음 각 픽셀의 평균 색상을 사용한다.
Trilinear : 8개의 가까운 픽셀을 선택한 다음 평균색상을 사용한다. 단, x y z 좌표 평면을 사용하므로 주로 3D에서 사용된다.
Cubic : 16개의 픽셀을 선택하여 평균 색상을 사용한다.
*/

/* ----- erase-remove idiom ----- */

/*
컨테이너에서 우너소를 지우는 작업은 주의를 기울여야 한다.
특히나 순환하는 도중에 삭제하는 것은 위험하다.

배열로 된 Actor들 중 조건에 만족하는 것을 지워야 한다고 치자.
Actor myArray[100];
for(int i = 0; i < 100; i++)
{
	if(deleted)
	{
		// 배열을 하나씩 줄여야 한다.
	}
}
물론 정적 배열에서 하나를 삭제하는 것은 배열의 크기를 매번 재할당해서 복사해야 하므로 좋은 방식이 아니다.
	1. 지울 항목을 제외한 99개의 배열 생성
	2. 99개의 원소 복사
	3. 기존 배열을 수정된 배열로 교체
*/

/*
범위기반 반복문은 도중에 삭제가 불가능 하다. 반복문 안에 들어 오는 것은 원소의 값이므로 이를 지울 방법은 없다.
따라서 반복자를 사용해야만 한다.

list<int> myArray = { 1, 2, 3, 4, 5 };
auto itr = myArray.begin();
while (itr != myArray.cend())
{
	if (*itr == 3)
	{
		myArray.remove(3);
	}
	itr++;
}

컨테이너의 remove 함수는 해당 값과 동일한 모든 우너소를 지워 버린다. 각 원소들을 지운 후 파괴자를 호출하고 컨테이너의 사이즈를 조절한다.
그런데 이렇게 표현하면 list iterator not incrementable 이라는 에러가 발생한다.

리스트의 원소[3]을 지우고 나면 현재 itr에 있는 값은 무엇일까?
[1][2][4][5][itr]
이미 지워진 공간을 가리키고 있다. 그래서 그 다음 itr++가 작동하지 않는 것이다.
따라서 위와 같이 탐색 도중에 remove를 사용할 수 없다.
*/

/*
이를 위해 컨테이너는 list::erase 라는 개별 함수가 있다. list::erase() 함수는 iterator 를 입력 받아 해당 원소를 지우고 크기를 조절한 뒤 올바른 iterator 를 돌려 준다.
따라서, 다음과 같이 사용해야 한다.

list<int> myArray = { 1,2,3,4,5 };

auto itr = myArray.begin();
while (itr != myArray.cend())
{
	if (*itr == 3)
	{
		itr = myArray.erase(itr);
	}
	else
	{
		itr++;
	}
}

그런데, 슈팅 게임처럼 자주 컨테이너의 내용이 변경되는 경우를 생각해 보면, 수시로 여러개의 오브젝트들이 삭제될 것이다.
따라서 list::erase() 가 한 루프안에서 수십번 발생하게 된다. 리스트에서 원소 삭제에 대한 부담이 적다고는 하나, 비효율적이다.

이러한 방식을 해결하기 위해 erase remove idiom 이라는 알고리즘이 등장했다.
std::remove() : 실제로 컨테이너에서 원소를 지우지 않는다.
	=> 지울 원소를 컨테이너 끝을 보낸다.
std::remove_if() : 조건에 만족하는 원소에 대해 remove를 수행한다.
*/

/*
위 알고리즘을 수행하고 나면 뒤에 붙은 불필요한 원소의 iterator 가 반환된다. 따라서 다음과 같이 해줘야 안전한 코딩이 된다.

std::list<int> myArray = { 1,2,3,4,5 };

auto logicalEnd = std::remove_if(
	myArray.begin(), myArray.end(), [](int e) {return e == 3; }
);

myArray.erase(logicalEnd, myArray.end());

erase(remove()) 형태로 구현하라는 의미로 erase-remove idiom 이다.
*/

/*
정리하자면, 수 많은 오브젝트를 가진 컨테이너에서 자주 오브젝트를 삭제해야 한다면
	1. 지워질 오브젝트는 별도로 관리( 플래그 등 )
	2. 컨테이너 전체를 대상으로 erase-remove idiom 수행
*/

/* ----- 컴퓨터 그래픽스 이론 #1 ----- */

// https://docs.microsoft.com/windows/uwp/graphics-concepts/

/*
좌표계( Coordinate System ) 및 기하학( Geometry )

수학시간에 자주 보던 x축 y축으로 되어 있던 평면은 르네 데카르트가 고안한 x-y 평면 기하학에서 출발했다.
이러한 공간을 데카르트 좌표계라 부르며 x축과 y축이 교차하는 형태를 따서 직교 좌표계라 부른다.

도형을 표기하기 위한 최소 단위는 점이다. 이러한 점은 그 기준이 되는 축으로 수직으로 연결한 값을 좌표로 가지게 된다.
그래서 직교 좌표계라 부른다.

여기에 z 축을 하나 추가하면 3차원 공간이 가능해 진다. x-y 평면, x-z평면, y-z평면 으로 이루어지는 이 좌표계는 z축 방향에 따라 두 가지로 나뉜다.

손가락의 엄지 손가락 방향으로 z 축이 증가한다라는 의미로 각각 왼손 좌표계, 오른손 좌표계라 부른다.
DirectX 는 왼손 좌표계를 사용하며 OpenGL은 오른손 좌표계를 사용한다. 유니티나 언리얼 엔진 역시 왼손좌표계를 사용한다.
*/

/*
Vertex & Vector

좌표계를 사용하면 공간에 꼭짓점(정점, 단수 Vertex, 복수 Vertices)과 방향(Vector)을 지정할 수 있다.
여러 개의 버텍스를 사용하면 선이나 도형을 만들 수 있게 된다.
이렇게 만들 수 있는 도형 들 중 가장 기본 형태를 Primitives라 부르며 수 많은 Primitives 들로 이루어진 도형을 메시라 부른다.

Mesh 라는 단어의 뜻이 그물망, 망사라는 뜻인데 3차원으로 표현한 도형의 형태가 Mesh 쳐럼 생겼기 때문이다.
우리가 자주 사용하는 단어 중 폴리곤이라는 것이 있다. 이 폴리곤은 Primitives를 의미하는데, 초창기 가장 많이 사용된 오브젝트를 표현하는 가장 최소 단위가 삼각형이었고
이를 폴리곤이라 불렀기 때문에 일반적으로 통용되고 있을 뿐이다.
최근에는 사각형 Primitives 로 사용하는 3D 편집 프로그램도 있기도 해서 기존의 삼각형 폴리곤과 구분하기 위해 Primitives 라는 단어를 더 많이 사용하려고 하는 것 같다.

Vertices( 꼭짓점 ) : 도형을 구성하는 꼭짓점들의 정보( 도형의 기본 정보 )
Edges( 모서리 ) : 두 버텍스를 연결하면 모서리( edge )가 만들어진다.
	=> 주어진 버텍스들로 만들 수 있는 모서리의 경우의 수는 매우 다양하므로 모서리 정보가 매우 중요하다.
Face( 면 ) : 에지들을 연결하면 행태를 가지는 평면이 만들어 지는데, 3차원 공간이므로 그 평면니 어느쪽을 바라 보는지가 중요해 진다.
	=> 이러한 방향성을 지정하는 것이 Face 이다.
Polygons : Face 가 지정되면 도형을 이루는 최소 단위인 폴리곤이 만들어 진다.
Surfaces : 동일한 특성을 가지는 폴리곤들을 묶어서 집합을 만들어서 서피스라 부른다.
*/

/*
법선 벡터( Normal Vector )

메시의 각 페이스에는 해당 페이스가 바라보는 방향을 나타내는 정보가 필요하다. 3차원 렌더링을 효율적으로 처리하기 위해 뒷면은 그리지 않는 방식을 사용하기 때문에 해당 정보는 매우 중요하다.
이러한 정보를 법선 벡터라 부르며 해당 면에 수직인 단위 벡터( 길이가 1인 벡터 )를 사용한다.
이런 정보는 좌표계에 따라 정의 되며 왼손 좌표계에서는 버텍스의 시계 방향 순서로 결정된다.

그리고 버텍스에서 법선벡터가 존재하는데, 이 정보를 사용하여 음영 처리를 할 수 있다.
*/

/*
Transform

Model Space
	3D 오브젝트는 자체적인 원점을 가진 좌표계를 가지고 있다.
	보통 아티스트는 캐릭터를 원점 기준으로 모델링하고 리소스를 제공해 준다.
	이러한 좌표가 로컬 좌표계라 하며 모델 공간이라고도 한다.
	이 단계에서는 변환 없이 디자인한 대로 버텍스들이 저장되어 있다.
World Transform
	게임에서는 다양한 오브젝트들을 배치해서 화면을 구성한다. 이 때 기중이 되는 좌표가 월드 좌표계이다.
	캐릭터를 월드에 배치하려면 위치를 지정하고 적당히 회전하고 크기도 조절해야 하낟. 즉 모델 공간에서
	월드 공간으로 변환이 일어나는 것이다. 이 과정을 World Transform( 월드 변환 )이라 부른다.
View Transform
	3D 환경은 표현을 위해 카메라를 사용하며, 그 카메라에 찍힌( 투영된 ) 이미지를 화면에 표시한다.
	이를 위해 수행되는 변환을 View Transform 혹은 Camera Transform 이라 한다. 이 역시 단순한 행렬의
	곱셈일 뿐이다. 카메라를 원점으로 하는 좌표계에 각 버텍스를 변환해서 배치한다고 생각하면 된다.
Projection Transform
	지금까지는 3차원 공간에서 점을 이리 저리 움직이는 과정일 뿐이었다.
	하지만 모니터에 3차우너 공간을 표현하기 위해서는 투영이라는 과정이 필요하다. 흔히 미술 시간에 배운 원근법을 적용하거나 하는 기법을 사용하낟.
	이러한 과정 역시 수학으로 표현이 가능하며, 이 과정을 Projection Transform 이라 부른다.
	이 과정을 거치고 나면 3차원 공간의 버텍스들이 2차우너 공간으로 투영된다.
Clipping ScreenSpace
	마지막으로 수행하는 과정이 모니터에 그리는 과정이다. 화면에 배치된 3D 모델에 색상을 입히고 셰이더를 적용하고 특수효과를 입히는 마무리 단계이다.
	이때 중요한 것은 화면에 보이지 않는 접들은 이런 복잡한 연산을 수행할 필요가 없다.
	3D 그래픽은 비주얼도 비주얼이지만 성능이 최우선이므로 불필요한 계산은 최대한 배제하는 것이 좋다.
	화면 공간으로 잘라 주는 작업을 Clipping 이라 부른다.
*/

/* ----- 컴퓨터 그래픽스 이론 #2 ----- */

/*
Device

디바이스는 다음과 같은 기능을 포함하고 있다.
	Transform Module : 기하학 변환에 관련된 벡터, 행렬의 연산을 수행한다.
	Lighting Module : 조명 처리에 관련된 연산을 수행한다. 조명에 대한 연산은 광원과 버텍스의 노멀벡터들과의 상대 위치 및 방향에 대한 계산 결과로 보간하는 형태로 수행된다.
	Rasterizer : 래스터화라는 개념은 모니터의 최소 단위가 화소라 발생하는 문제를 해겨하기 위한 방법이다.
삼각형을 화면에 그리려면 픽셀의 한계로 원형을 유지하기 어렵다. 이런 문제를 다양한 기법으로 최대한 그럴 듯 하게 만들어 주는 것이 래스터화 이다.
*/

/*
HAL( Hardware Abstraction Layer ) Device

하드웨어 추상화 계층 디바이스는 DirectX의 기본 디바이스 유형으로, 위에서 언급한 변환/조명/래스터화 모듈의 전부 또는 일부를 하드웨어에서 구현하게 된다.
개발자들은 직접 그래픽 카드( 하드웨어 )에 접근할 수 없으며, 개발자들은 단지 DirectX 의 함수를 호출하며 DirectX가 HAL을 통해 그래픽카드에 접근한다.
이런 방식을 사용하고 있는 이유는 하드웨어 제조사별로 자신들만의 노하우로 그래픽카드를 만들기 때문에 내부 작동 방식이나 사양이 달라 질 수 있다.
이런 서로 다른 기능들을 게임 개발자가 모두 익히는 것은 거의 불가능하기 때문에 DirectX에서 표준 인터페이스를 만들고 하드웨어 레벨의 기능은 추상화 시켜 둔 것이다.
*/

/*
Reference Device

하드웨어 추상화 계층을 사용하게 되면 개발자는 많은 정보를 얻을 수 없다.
그래픽 제조사 마다 결과값을 넘겨 주는 방식도 다르고 결과값 마저도 다르기 때문에 독자적인 디버깅 툴을 제공하기도 한다.
이 문제를 해결하기 위해 DirectX에서는 모든 모듈의 기능을 지원하는 참조 장치를 추가했다.
참조 장치라고 부르는 이유는 이 장치는 디버깅을 위한 특수한 목적으로 탄색되었기 때문이다.
속도 보다는 정확도를 위해 구현되었고, 소프트웨어에서 구현되기 때문에 기능 테스트를 위해 사용할 수 있다.
*/

/*
Device Lost

게임을 플레이하다 보면 Alt + Tab 으로 작업을 전환하거나 절전 모드가 작동하거나 다른 게임을 실행할 경우 비정상적으로 종료되는 경험을 하였을 것이다.
3D 그래픽을 표현하기 위해서는 상당히 많은 하드웨터 자원을 사용해야 하는데,
이 자원들에 다른 앱에 의한 손상이 발생할 가능성이 높기 때문에 DirectX 에서는 장치의 상태를 작동 or 손상 상태로 구분한다.
이렇게 장치가 분실되면 모든 비디오 메모리를 해제하고 재설정하거나 최악의 경우으넨 사용이 가능한 다른 장치를 선택해야만 한다.
이 과정이 잘못되면, 앱이 응답하지 않는 결과가 발생하므로 상용 게임을 제작할 때는 주의해야 할 부분이다.
다행히 최신 DirectX에서는 이런 빈도수가 많이 줄어서 거의 발생하지 않지만 물리적으로 장치가 제거되거나 절전모드에 들어갈 때는 여전히 주의해야 한다.
*/

/*
Swap Chain

부드러운 애니메이션을 위해서 여러 개의 버퍼(전면 버퍼, 후면 버퍼)를 사용한 버퍼링이 있다.
이런 버퍼들의 집합을 Swap Chain이라 부르며 이 과정을 Flip 혹은 Swap이라 부른다.

화면에 3D 장면을 그리는 과정에는 컴퓨터의 성능도 중요하지만 모니터 역시 빼놓을 수 없는 구성 요소이기도 하다.
모니터는 초당 60 ~ 100 회(60Hz ~ 100Hz) 정도 새로고침을 수행하는데 이건 컴퓨터의 처리 속도보다 현저하게 느린 속도 이다.

게임을 하다보면 테어링이라는 단어를 들어 보았을 것이다. 모니터의 화면 갱신 주기와 우리가 만든 3D 화면의 갱신주기가
서로 충돌을 일으키게 되면 테어링이라는 증상이 일어나게 되는 것이다.

즉, 버퍼를 교환하는 중에 모니터 갱신이 발생하면 교환 중이던 2개의 이미지가 동시에 표현되면서 이런 증상이 생기게 되는 것이다.
그래서 나온 것이 수직 동기화이다.
쉽게 말하면 모니터가 갱신이 현재 갱신 주기를 모두 마칠 때 까지 기다렸다가 화면에 그리는 것이다.
물론, 그릴 때 갱신 주기를 놓치면 다음 번 까지 기다려야 하므로 1/60초를 그냥 허비하게 되는 셈으로 입력 랙과 같은 증상이 발생하기도 한다.
*/

/*
Lighting

3D 장면을 구성하는 핵심 요소 중 하나는 조명이다. 조명은 단순히 밝기만을 제어하는 것이 아니라 위와 같이 반사, 난반사를 포함하여 재질에도 영향을 주는 복잡한 계산을 필요로 한다.
초기 그래픽카드들은 이런 기능을 강조하기 위해 T&L 가속이라는 용어를 사용할 정도로 조명은 중요하고 복잡한 연산이 필요하다.
가장 기본적인 조명에는 지향광과 주변광이 있다.
둘다 씬에 배치된 물체에 사물을 비추는 용도로 사용되지만 각각 특성이 있다.
*/

/*
Direct Light

직접 오브젝트를 비추며 항상 방향과 색이 있다.
방향이 존재하기 때문에 페이스의 노멸과 연산을 통해 밝기를 정할 수 있다.
*/

/*
Ambient Light

장면의 모든 오브젝트에 영향을 주는 빛으로 종류, 위치와 상관없이 전체를 채우는 일정한 강도를 가진다.
흔히 태양광으로 사용된다.
*/

/*
Ray-Tracing

기존의 방법들은 화면에 그릴 버텍스에 대한 광원의 위치, 각도등을 계산하는 방식이다.
하드웨어의 성능이 높아지면서 조금 더 그럴듯한 장면을 그리기 위해 사용되는 기법이 광선추적이다.

화면에 표시되는 점에서 가상의 빛이 발사된다고 가정하고 그 빛이 진행하는 방향을 역으로 추적하는 방식이다.
하나의 픽셀에 수 많은 연산 처리가 들어가기 때문에 매우 복잡하고 계산이 어렵다.

복잡한 계산인 만큼 실사와 매우 유사한 결과물을 그릴 수 있게 된다.
다만 이 기법은 DirectX 기본 지원이 아니기 때문에 직접 구현해야 하며 하드웨어 가속의 지원이 없으면 연산 부하가 커서 게임에 사용하기 힘들다.
*/

/* ----- 컴퓨터 그래픽스 이론 #3 ----- */

/*
Shading

그림자를 처리하는 셰이딩은 3D 객체를 표현하기 위한 필수적인 기법이다.

Flat Shading : 가장 간단한 방식으로 면의 법선과 광원과의 방향으로 음영을 칠하는 방법이다.
Gauraud Shading : 헨리 고러드가 고안한 보간 방법으로 가장 많이 사용되는 방식이다. 각 버텍스의 법선벡터로 평균을 구한 다음 가중치를 생성한다.
	=> 이 가중치들을 쌍선형보간하여 부드러운 색상들을 만들어 낸다.
Phong Shading : 그래픽스에 큰 역할을 한 베트남 출신의 연구자 부이투옹 퐁이 개발한 방식이다. 각 면의 법선 벡터에 따라 조명에 대한 연산을 보간하는 방식으로 
	=> 당시에는 매우 획기적인 아이디어였지만 요즘은 표준 방식이다. 렌더링된 픽셀 당 계산을 수행하는 방식이라 픽셀 셰이더의 등장과 함께 대세가 되었다.
*/

/*
Depth Buffer & Stencil Buffer

3차원 공간의 오브젝트를 프로젝션 공간으로 매핑할 때 주의해야 할 점은 어떤 오브젝트가 앞에 있는 지를 파악하는 것이다.

이렇게 깊이를 관리하기 위해 별도의 버퍼를 사용하는데, 이를 깊이 버퍼라 하며 z 값을 사용한다고 해서 z-buffer 혹은 w-buffer라 부르기도 한다.
이 개념을 응용하면 미술시간에 수행한 스텐실 효과를 낼 수 있다.

위와 같은 공판화를 사용해 이미지를 그리는 기법을 스텐실 기법이라고 한다. 이 공판화를 버퍼로 옮겨서 3D 장면에도 적용할 수 있으며 이를 스텐실 버퍼라 부른다.
스텐실 버퍼를 사용하면 다음과 같이 그릴 영역과 그리지 않을 영역을 간단히 지정할 수 있어서 다양한 효과에 사용할 수 있다.
*/

/*
Texture

텍스쳐는 질감이나 감촉을 의미하는 단어로 3차원 오브젝트의 표면에 세부적인 표현을 위해 색을 칠하거나 색상을 지정하는 것을 의미한다.
가장 기본적인 방법은 2D 이미지를 사용해 3D 오브젝트에 상세적인 표현을 하는 것이다.
즉, 컴퓨터 그래픽에서의 텍스쳐는 개체에 질감을 더하는 픽셀의 비트맵이라 볼 수 있다.

둥근 지구본을 평면으로 펼쳐서 지도를 제작하는 과정과 반대의 과정으로 2차원의 이미지를 3차원 오브젝트에 적용하는 방식을 사용한다.
Texture Map을 사용하여 3D 오브젝트의 면에 적용하는 방식으로 매핑이라고 부른다.
텍스쳐의 가장 기본적인 단위를 Texel 이라 부르며 Texture Element 혹은 Texture Pixel을 의미한다.
텍셀의 집합 역시 좌표계가 존재하며 다음과 같은 형태가 된다.

좌표계의 가로/세로는 U/V축이며 0~1 로 단위화 되어 있는 공간이다.
따라서 텍스쳐 매핑은 종종 UV 매핑이라고도 부른다.
*/

/*
텍스쳐 필터링( Texture Filtering )

3D 개체는 특성상 화면에 매우 가깝거나 매우 멀게 표현될 때가 있다.
그렇게 되면 텍셀하나가 엄청 넓은 픽셀로 매핑되거나 혹은 수 많은 텍셀이 하나의 픽셀로 매핑되는 경우가 발생한다.
쉽게 말하자면 텍스쳐 비트맵이 엄청 확대되거나 축소된다는 뜻이다.

따라서 그럴듯하게 3D 개체를 표현하기 위해서는 텍셀 색상을 혼합하여 픽셀에 알맞는 색상을 찾아야 하는데 이런 복잡한 과정을
텍스쳐 필터링이라 부른다.

Nearest-Point Sampling : DirectX 에서 기본적으로 수행하는 필터링 방식으로 텍셀의 주소를 가장 가까운 정수에 지정하는 방식을 사용한다.
물론 가장 단순한 방식이라 텍스쳐의 크기와 오브젝트의 크기가 같으면 정확한 이미지를 보여주지만 확대/축소 되었을 때는 이미지가 흐릿하게 나타날 수도 있다.

Bilinear Textur Filtering : 선형 텍스쳐 필터링은 계산할 점을 기준으로 선을 그어 양 끝의 값에 대한 중간값을 취하는 방식을 말한다.
대부룬의 최신 그래픽 카드는 리니어 필터링에 최적화되어 있다.

Linear Filtering
	우선 선형 필터링은 두 지점 사이의 위치를 기준으로 보간을 수행하는 방식을 의미한다.
Bi-Linear Filtering
	이중 선형 필터링은 선형 필터링을 2차원으로 확장하여 상/하, 좌/우 4개의 점을 기준으로 값을 계산하는 방식이다.
Tri-Linear Filtering
	마찬가지로 삼중 선형 필터링은 3차원으로 확장하여 육면체 8개의 점을 기준으로 값을 계산하는 방식이다.
Anisotropic Texture Filtering
	기존의 필터링은 빠른 대신 멀리 있는 텍스쳐는 흐려진다는 단점이 있다.
	이런 단점을 해결하기 위해 등장한 개념이 비등방성 필터링이다.
	비등방성이라는 뜻은 방향에 따라 물체의 물리적 성질이 다른 것을 말한다. 동일한 금속면이라도 방향에 따라 빛을 반사하는 정도가 다름을 의미하는데,
	이런 특성을 사용해서 거리에 따라 텍스쳐 공간을 왜곡 사용하는 필터링 방식이다.

	당연히 샘플링할 포인트가 많아지므로 연산 부하가 크지만 먼 곳도 선명한 표현이 가능하다.

Mip-Maps
	복잡한 필터링으로 그럴듯하게 만드는 것보다 거리에 따라 서로 다른 해상도의 텍스쳘르 적용하자는 개념이 Mip-Map 이다.
	라틴어 multum in parvo의 첫글자를 따서 MIP-map이라 부르는데 개발자의 용어인 피라미드를 여전히 사용하기도 한다.

	카메라에서 보여지는 오브젝트의 거리에 따라 서로 다른 텍스쳐를 사용하며 각 단계별로 주로 2의 거듭제곱 크기로 지정한다.
	각 단계는 품질의 레벨이라는 용어라 표현한다.
*/

/*
Anti-Aliasing

안티에일리어싱( 윈신호 제거 )는 높은 해상도의 이미지를 낮은 해상도에서 표현할 때 발생하는 깨진 패턴을 최소화시켜주는 기법이다.
즉 오브젝트에 매핑한 텍스쳐가 원본 해상도보다 낮게 축소되어 표시될 때 발생하는 이미지 깨짐을 막아주는 것이다.

텍스쳐 필터링과 같아 보인다. 하지만 안티에일리어싱은 화면 전체에 대한 연산이라는 점에서 개체에 적용되는 텍스쳐 필터링과는 개념이 다른다.

높은 수준으로 AA를 적용하면 결과물들이 자동으로 보정되므로 텍스쳐 필터링이 필요 없게 되기도 한다.
하지만 당연히 사양이 올라가게 되므로 AA와 텍스쳐 필터링을 적절히 섞어서 사용하는 것이 중요하다.

SSAA
	최종 픽셀의 색상을 구하기 위해 주위의 픽셀의 값을 샘플링하여 평균을 구하는 방식이다.
	초기에는 가장 무식하게 원래 해상도보다 크게 렌더링하여 축소한 결과물을 사용하는 방식을 사용했다.
	그러다가 각 픽셀 주변의 색을 샘플링하여 결과를 만들게 되었는데 계산량이 많은 것에는 변함이 없다.
MSAA
	기존 SSAA의 무식한 연산을 조금 다이어트하려고 등장한 개념으로 최신 그래픽카드들은 대부분 이를 지원한다.
	전체 화면을 모두 샘플링하지 말고 폴리곤의 외곽선만 샘플링한다는 개념이다.
*/

/* ----- 컴퓨터 그래픽스 이론 #4 ----- */

/*
파이프라인

3차원 그래픽에서 어떻게 그리는 지를 담당하는 것이 렌더링 파이프라인이다.
사전적인 의미로 렌더링은 무언가를 만든다는 뜻이고, 파이프라인은 수송관이라는 뜻이다. 즉, 무엇인가를 만드는 수송관이라는 뜻이다.

Input Assembler : 그리기 위한 모든 입력을 조합한다.
Vertex Shader : 정점들의 위치나 기타 정보들로 음영을 잘 입힐 수 있게 준비해 준다.
	=> 하지만 거의 일반명사로 자리 잡혀서, 이제는 그냥 그래픽스와 관련된 처리를 하는 거의 모든 부분을 셰이더라 부른다.
Hull Shader : 간략한 설계도로부터 실제 선체를 다시 만들어 낸다고 생각하면 된다.
	=> 간단한 도형에서 보기 좋은 도형으로 바뀌는 역할
Tessellator : 분할기라고 하는데 사전적 의미는 위 그림과 같은 격자무늬를 말한다.
	=> Hull Shader 에서 만든 더 세분화된 도형을 삼각형으로 더 잘게 쯔개서 표현한다.
	=> 이렇게 자른 삼각형에서 텍스쳐를 매핑하기 위한 정보까지 추출해 낸다.
Domain Shader : 세분화된 삼각형의 각 꼭지점의 위치를 계산한다.
Geometry Shader : 기하 도형 셰이더이다.
	=> 여기에서는 삼각형, 선, 점 등에 대한 계산을 한다.
Rasterizer : 2차원으로 변환된 위치 정보들을 화면에 표시할 준비를 한다.
	=> 모니터의 격자에 그림을 그리기 위해 각각의 위치를 만들어 낸다. 그리고 지금까지의 셰이더 정보를 토대로 보여질 그림에 대한 정보를 채운다.
Pixel Shader : 각 픽셀에 저장된 정보를 이용하여 색상을 칠한다.
	=> 그리고 보간 등의 기법을 적용해 최종 픽셀을 만들어 낸다.
Output Merger : 깊이 스텐실 버퍼 등을 이용하여 지금까지 그린 이미지가 화면에 나타날지, 보일지 말지 등에 대한 처리를 한 후에 최종적으로 화면에 보낸다.
*/

/* ----- DXGI Flip Model ----- */

/*
여러 개의 버퍼를 사용해 자연스러운 애니메이션을 표현하는 방법 들 중 가장 자주 사용하는 방법은 Bit Mode(Bit Bit)와 Flip Mode이다.

DWM : Desktop Window Manager, Windows7 에서 추가된 윈도우 관리자이다.

Bit Mode
	앱이 프레임에 그린다.(쓰기)
	D3D가 버퍼의 내용을 다른 버퍼로 복사한다.(읽기,쓰기)
	복사가 끝나면 DWM이 화면으로 그린다.(읽기,쓰기)
Flip Mode
	앱이 프레임에 그리기(쓰기)
	D3D가 버퍼를 DWM으로 넘겨준다.
	DWM이 화면에그린다.(읽기,쓰기)

Flip 방식이 읽기, 쓰기 연산이 빠져서 더 빠르다.
과거의 DirectX는 독점 모드(전체화면 모드)에서만 Flip을 지원했는데 Windows7 과 DWM에 의해 창모드에서도 사용이 가능해 졌다.
*/

/*
Dirty Rectangle & Scroll Rectangle

동영상 코덱 등에서는 파일 크기를 줄이기 위해 이전 장면과 현재 장면의 변경된 내용만 그리는 압축을 자주 사용하낟.
이렇게 변화해야 할 영역을 갱신이 필요한 더러운 영역이라 부른다.
게임에서도 성능향상을 위해 혹은 동영상을 표현하기 위해 이런 방식을 사용할 수 있다.

Dirty Rect 방식 중 스크롤 형태를 가지는 방식이 있다.

화면이 스크롤 되어 기존 영역의 위치가 변경되고 일부가 갱신될 경우 버퍼를 스크롤하고, 일부 영역만 그리는 방식을 사용하면 전체를 갱신하는 것에 비해 효율적으로 화면을 표시할 수 있다.

1. 현재 전면 버퍼의 내용이 화면에 그려진 상태이다.
2. 후면 버퍼의 dirty rect를 설정해 변경될 영역을 그린다.
3. IDXGISwapChain::Present 를 호출할 때 다음 정보를 넘겨 준다.
	a. Dirty Rectangles : 변경된 영역
	b. Scroll Rectangles : 스크롤 영역
	c. Scroll Offset : 스크롤된 오프셋
4. 버퍼를 Swap 하여 화면에 표시
*/

/* ----- 투명한 오브젝트 처리 ----- */

/*
알파 테스트

BMP에 투명도를 적용할 때 사용한 기법이다. 단순히 그릴 이미지의 알파값이 특정 숫자보다 적으면 해당 픽셀을 그리지 않는 방식이다.
따라서 디자이너가 채색한 알파 속성에 따라 외곽선이 남게 되며 확대/축소로 인해 이미지 손상이 발생하게 된다.
*/

/*
알파 블렌드

알파 블렌딩은 이미 그렺니 픽셀과 현재 픽셀의 알파값을 혼합하여 연산을 수행하는 방식으로 투명도를 처리한다.
알파 테스트 보다는 나아보이지만, 3D 게임은 회전하는 이미지를 보여줘야 한다. 그로 인해 알파 순서가 매우 중요하다.

회전 각도에 따라 알파 연산을 수행하는 순서가 달라지면서 투명한 오브젝트가 사라지는 증상이 발생하게 된다.
정확하게는 투명한 오브젝트 뒤에 있는 녀석들이 사라지는 증상이다.

그래픽 디자이너에게 요청해서 메시를 서로 분리하는 방법이 있다.
기본적으로 알파 연산은 오브젝트(메시) 단위로 일어나므로 분리해서 그리면 해결된다.
물론 나무와 풀과 같은 것은 불가능 하다.

이를 해결하기 위해 알파 정렬 이라는 방식도 사용한다.
*/

/*
Alpha-To-Coverage

위에서 알파테스팅을 섞는 방법을 설명했지만 Alpha Test 는 퀄리티가 좋지 않다.

최신 그래픽카드들은 이러한 문제를 위해 Alpha-To-Coverage 라는 기능을 지원한다.
혹은 Screen-Door 효과라고도 한다. 방충망 정도라고 보면 될 것이다.

최근 게임들을 보면 투명한 오브젝트들을 확대하면 점과 같은 것들이 보일 것이다.
이 기법이 바로 Alpha-To-Coverage 혹은 Screen-Door 효과이다.

일반 알파 계산과는 달리 각각의 픽셀들을 뒤에 있는 녀석들과 블렌딩하는 방식이 아니라, 지정한 패턴으로 그릴것과
그리지 않는 것을 지정하는 방식이다.
다시말해, 텍스쳐의 알파채널을 사용해 Anti-Aliasing의 마스크로 사용하는 방식으로 블렌딩 처리와는 다른 개념이다.

이런 방식은 풀이나 나뭇잎 같은 복잡하고 투명한 영역이 밚은 오브젝트가 모여 있는 장면을 표현하는 데 주로 사용한다.
*/

/* ----- SIMD( Single Instruction Multiple Data ) ----- */

/*
직역하면 하나의 명령어로 여러 개의 데이터를 동시에 처리한다는 의미가 된다.
과거 빠른 연산을 자랑하던 슈퍼 컴퓨터에서 여러 데이터를 병렬로 관리하고 이를 프로세서가 한 번에
한 벡터씩 처리하는 방식을 사용했다.
하지만 게임 업계가 발전하면서 오디오/비디오 처리에서 유사한 특성을 발견하고 그 수요가 증가함에 따라 최근에는
데스크탑 컴퓨터에 서 자주 사용되고 있다.

멀티미디어의 리소스를 관리하다 보면 큰 데이터 집합에서 동일한 값을 추가하거나 빼는 경우가 많은데
이럴 때 SIMD를 사용하면 획기적으로 실행시간을 줄일 수 있게 된다.

가령 10 X 10 해상도의 4바이트( RGBA )로 구성된 이미지를 처리하려면 다음과 같다.
하나의 명령이 하나의 데이터에 접근할 수 있다면 위와 같이 픽셀의 구성 요소인 색상을 하나씩 가져와야 한다.
따라서 10 X 10 X 4 = 400 번의 연산이 필요하다.

하지만 하나의 명령이 여러개의 데이터를 가져올 수 있다면 어떨까? RGBA를 하나의 벡터로 만들어 처리한 다면 다음과 같다.
위와 같이 SIMD에선 10 X 10 = 100 의 연산만 필요하게 된다.

단순히 읽기만이 아니라 쓰기에도 적용될 수 있으므로 위 예시보다 더 효율이 좋다.
*/

/* SSE( Streaming SIMD Extensions ) */

/*
과거 CPU를 구매하다 보면 SSE, SSE-2 같은 용어들을 본적이 있다. 최근에는 AVX( Advanced Vector Extensions )가 주로 사용된다.
기본 SIMD 의 확장 개념으로 정수만 사용이 가능하다는 단점을 해소함과 동시에 부동소수점에 대한 연산을 추가한 버전이다.

SSE2 규격은 SIMD 명령을 128bit 레지스터들을 사용하여 32bit 정수( 혹은 실수 ) 4개를 한 번에 처리할 수 있다.
3D 연산에서 가장 많이 사용되는 데이터가 ( x, y, z, w )의 원소를 가진 벡터라 3D 게임의 연산을 획기적으로 높일 수 있다.
행렬은 4개의 벡터를 가진 집합으로 생각하면 행렬 역시 빠른 처리가 가능하다.
*/

/* ----- DirectMath with SIMD ----- */

/*
마이크로소프트에서는 SIMD를 지원하기 위해 새로운 타입 _m128을 선언해 뒀고, 이를 DirectXMath가 사용한다.
_m128 타입은 CPU의 레지스터에 바로 대응되는 형식이다.
*/

/*
호출 규칙

일반적으로 변수는 선언되는 타입에 따라 규격이 정해지므로 SIMD를 지원하는 변수 형식을 사용하면 되지만,
함수의 경우는 조금 다르다.
함수를 사용하는 곳( 호출자 )의 변수를 호출된 함수의 인수로 복사가 일어나는 경우 스택 메모리와 레지스터에 값이 복사되는 형식을 지정할 필요가 있다.

간단히 인수 전달 규칙 몇 가지만 살펴보죠.
	__cdecl : C/C++ 표준이다. 매개변수를 스택에 역순( 오른쪽 -> 왼쪽 )으로 저장한다.
	__fastcall :  마이크로 소프트 전용으로 인수들을 레지스터에 저장한 다음 남은 것들은 역순으로 스택에 push한다.
	x64 기본 규칙 : 4개의 레지스터를 사용하는 fastcall 형식이다.
	__vectorcall : 마이크로 소프트 전용으로 인수들을 레지스터에 저장한 다음 스택에 역순으로 push한다.
		=> x64 보다 더 많은 레지스터를 활용하여 벡터 집합에 특화된 처리가 가능하다.
각 규칙의 큰 특징은 레지스터 사용 여부이다. 메모리보다 월등히 빠른 레지스터를 사용하면 처리 속도를 향상시킬 수 있다.
당연히 레지스터를 사용하면 좋지만, 사용자의 컴퓨터는 다양한 구성으로 되어 있어서 x64 플랫폼이 아닐 수도 있으며,
SSE-2 를 지원하지 않을 수도 있다.
DirectXMath 에서는 XM_CALLCONV( directX Math CALL CONVention )를 사용해 플랫폼에 따라 __fastcall / __vectorcall 을 자동으로 적용해 준다.
*/

/*
Register Type vs Memory Type

조금이라도 더 빠른 연산을 위해 이런 특수한 개념들을 추가하다보니, 자연스럽게 해당 목적에 맞도록 새로운 데이터 타입을 만들어야 했다.

__m128 형식으로 4개의 float 원소를 가지는 벡터에 딱 맞는 크기이다.
따라서 XMVECTOR 를 지역 변수나 전역변수로 사용할 경우 SIMD 지원을 쉽게 처리할 수 있다.

하지만, 힙에서는 조금 더 복잡하다. 메모리 정렬의 문제로 인해 64비트 운영체제에서는 모든 힙이 16바이트로 정렬되지만,
32비트 운영체제에서는 8바이트로 정렬된다.

물론 모든 구조체 정렬을 align 기능으로 지정해도 되지만, 플랫폼 독립적인 코드를 사용하려면 XMVECTOR 를
XMFLOAT 으로 잘게 쪼개서 XMFLOAT4 형식을 사용하는 것이 더 안전하다.
*/