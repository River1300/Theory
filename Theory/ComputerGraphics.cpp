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
