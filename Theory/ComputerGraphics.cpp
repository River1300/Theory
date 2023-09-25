/* ----- ��ǻ�� �׷��Ƚ� ----- */

// �������� ��ǻ�� �޸𸮿� �̹����� �����ϰ� �ִٰ� �̸� �׷��� ī�� �޸𸮷� �����ϴ� ����� ����ߴ�.
// ���� ��Ȯ�ϰԴ� �׷���ī�尡 Frame Buffer �� ������ �� CPU �� ��û�ؼ� �����͸� �о� ���� ����̾���.
// ���� ���� �����ڵ��� �ַ� �޸𸮿� ȭ�鿡 �׸� �̹����� ��� �ִ� ��찡 ���Ҵµ� �̸� �����ؼ� Back Buffer ��� �ҷ���.
// Frame Buffer �� ����� �������� ����� ���� Front Buffer ��� �Ѵ�.

/*
	[RAM]		[V-RAM]
BackBuffer -> FrameBuffer -> ȭ��

���� ���� �ַ� �ĸ� ���۴� ������ ������ ���ϰ� �ϱ� ���� �迭 ���·� �����Ѵ�.

1. ������ ����ī�� FrameBuffer( 1024 X 768 BITMAP )
2. ȭ�� ������ ��� �ִ� �޸�( BackBuffer )
3. ������ ���� ī�忡 �̹��� ���( BackBuffer -> FrameBuffer )
	a. �ùķ��̼� - FrameBuffer(BITMAP)�� ����Ϳ� �׷��� Ȯ��
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

������ �׽�Ʈ�� ���� 1024 X 768 ũ��� ������� ���� ũ��� �����.
BYTECOUNT �� �� �ȼ��� ����Ʈ ���� RGBA �� ������ �����̹Ƿ� 4����Ʈ�� �����Ѵ�.

Microsoft::WRL::ComPtr<ID2D1Bitmap> mspFrameBitmap; : ���� �����ӹ��ۿ� BITMAP Ŭ�����̴�. ID2D1Bitmap Ŭ������ Direct2D���� �����ϴ� BITMAP Ŭ�����̴�.
std::unique_ptr<UINT8[]> mspBackBuffer; : �ĸ���۸� ���� �迭�̴�. �� �ȼ��� �Ʒ��� ���� 4����Ʈ�� �� ������ �ȴ�.
	[RED][GREEN}[BLUE][ALPHA]
����, �迭�� ũ��� ���� X ���� X ����Ʈ���� �ȴ�.
UINT8 �� ����ũ�μ���Ʈ���� ������ ������ �� unsigned char Ÿ���̴�.

�ܼ��� 1�� �迭�ε� �����ϰ� ����Ʈ�����͸� ����Ͽ� ������ ������ ���ð� ���� ���� �����̴�.
���� �迭( new UINT[], std::array )�� �Ҵ��ϰ� �Ǹ� �ش� �޸𸮴� ���ÿ� ��ϵȴ�. ������ ������ �Լ��� ���� ������ ���� �ſ� �������� �������� ū �迭�� �Ҵ��� ������ �ݹ� ���� ������.
�ֽ� �����Ϸ� ���� ���� ������ �ܰ迡�� ������ �߻��ϱ⵵ �Ѵ�.
���� �ſ� ū �迭�� �Ҵ��Ϸ��� �������� ���� �÷� �δ� ���� ����. ���� ��ǻ���� �޸� ������ ��ŭ ����� �� �ִ�.
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

D2DFramework::Init(hwnd); : ��� Ŭ������ ���� �Լ��� ȣ���ؼ� �⺻ �ʱ�ȭ�� �����Ѵ�.
mspBackBuffer = std::make_unique<UINT8[]>(BITMAP_WIDTH*BITMAP_HEIGHT*BITMAP_BYTECOUNT); :
	���� �ĸ���۷� ����� �迭�� �����Ѵ�. ���Ҵ� UINT8 �̸�, ũ��� ���� x ���� x �ȼ��̴�.
HRESULT CreateBitmap(D2D1_Size_U size, const D2D1_BITMAP_PROPERTIES& bitmapProperties, ID2D1Bitmap **bitmap); :
	size : ������ ��Ʈ���� ũ��( pixel ���� )
	bitmapProperties : D2D1_BITMAP_PROPERTIES ����ü�� �ȼ� ����� DPI �� ����( ����Ÿ�ٿ��� ���캻 �Ͱ� ���� )
	bitmap : ID2D1Bitmap �������̽��� ���� �������� �ּ�
mspRenderTarget->DrawBitmap(mspFrameBitmap.Get()); :
	����Ÿ�ٿ� ��Ʈ���� �׸���. ��ǥ�� ������ �⺻ �Ű������� 0, 0 �� ��µȴ�. ����η� �̵��� ���� �ſ� �پ��� �Ű������� ����������
	��κ� �⺻������ �����Ǿ� �־ ��Ʈ�ʸ� �Ѱ��൵ �ȴ�.
*/

/* �ĸ���� ǥ�� */

// �غ��� �ĸ���۸� �����ӹ��۷� �̵��� ����ϴµ� �� ������ Flip, Present �� �θ���.
// ���� �ϵ���� ���ӱ���� ������ ���� ������, �ĸ������ ������ �����ӹ��ۿ� �����ϴ� ������� ����ȭ �غ���.

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
	const D2D1_RECT_U *dstRect, : BITMAP �� ������ ����, nullptr �� �����ϸ� BITMAP ��ü ����
	const void		  *srcData, : ������ ����
	UINT32			  pitch		: ����( width X byteCount )
	);
�� �Լ��� ����ϸ� BITMAP ���ҽ��� �޸� ������ ������ ������ �� �� �ִ�.
*/

/* ȭ�鿡 �ȼ� �׸��� */

// x, y ��ǥ�� ������ �ָ� �ش� ��ǥ�� ���� ��� ���
// �ĸ� ���۴� �⺻������ 1�� �迭�̹Ƿ� 2���� ������ �Ű������� �ε����� ����ϴ� ���� �ʿ��ϴ�.

/*
[0,0][0,1][0,2]
[1,0][1,1][1,2]
[2,0][2,1][2,2]

[0][1][2][3][4][5]...

���� ���� �����Ϸ��� x,y �� ���� �и��Ͽ� x �� ������, y �� ������ ���� �����ϰ� ����� �����ϴ�.
index = x + y * ( width )
�׷���, �ĸ� ���۴� �� �ȼ��� 4����Ʈ�� �Ǿ� �ִ�.
�⺻�����δ� ������ ������� ����� ���������� width ���� �ٸ���. �� �ȼ��� �������� ����Ʈ�� �̷���� �����Ƿ�( width * byteCount )
�� ����ؾ� �Ѵ�. ���� �� �����ϱ� ���� �ʺ�( width )�� �ƴ϶� ����( pitch )��� �ܾ �ַ� ����Ѵ�.
������� Ư���� scanline �̶�� �Ѵ�.
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

DrawPixel(1, 1, D2D1::ColorF::White); : �׽�Ʈ�� ���� ��ƾ�� �� ������ �߰��ϸ� 1, 1 �� ��� ���� ���� �� �ִ�.
*/

/* ����( Alpha )���� �뵵 */

// �ȼ������� ������ ���� �׻� ���İ��� �����ߴ�. �� ���� ���� ����ϴ� ���ϱ�?

/*
FillRectToBuffer(0, 0, 100, 100, D2D1::ColorF::Red);
FillRectToBuffer(50, 50, 100, 100, D2D1::ColorF::Green);

�׷��� ������ �����԰� ���ÿ� �� �ȼ��� ���� �� �ִ� ���� �þ�鼭 ������ ������ �� �ְ� �Ǿ��µ� �̸� ���Ķ� �θ���.
������ �̹���(RGB) ǥ�� �̿ܿ� ������ ä���� �ξ� ������ �����ϴ� ����̶� ���� ä���̶�� �Ѵ�.

�� �̹������� ó�� �翬�� ���� ��ǥ�� �ȼ��� ���߿� �׸� ������ ��������µ�, ���⿡ ���ĸ� ����Ͽ� ������ �� �پ��� ȿ���� �� �� �ִ�.

��� = ���� ���� * (1.0f - alpha) + �ű� ���� * alpha
*/

/* ----- �׷���ī�� ----- */

// ����� ȭ���� ũ�� CPU, �׷���ī��, ����� ����� �������� �̷���� �ִ�.
// �׷���ī��, ����ī��, ���÷���ī��, �׷��Ⱥ���, ���÷��̾����, ��������� �� �پ��� �̸����� �Ҹ��� �ִ�.

/*
�׷���ī��� ũ�� ������ ���� �������� �Ǿ� �ִ�.

	GPU( Graphic Processing Unit ) : 
		3���� �׷����� �����ϸ鼭 ������ �׷��� ���� ���� CPU ��� �����ϸ� �ȴ�.
		CPU ���� ���� �Ҽ��� ���� ó���� 3D ������Ʈ�� ȭ���� �ȼ��� ��ȯ�ϴ� ����������( ���̴���� ���� ��� )���� �Ǿ� �ִ�.
	V-RAM( Video Random Access Memory ) :
		�׷��ȿ� ���Ǵ� ������ �����ϴ� ���� �޸�, �̹��� ������ �ε��ؼ� ���� �Ѵٴ��� �ϰų� 3D ������Ʈ�� ��( Vertex )��
		�����ϴ� �뵵�ε� ��������� ���� ū ������ ȭ�鿡 �׸� ������ �޸�( Frame Buffer )�� ��� �ִ� ���̴�.
		���⿡�� �ٷ�, ����ͷ� ȭ���� ���۵ȴ�.
	���( Output ) :
		����Ϳ� �����ϴ� �������̽��̴�.
		VGA ����( Ȥ�� D-Sub ), DVI, HDMI, Display Port �� �پ��� �԰��� ���� �Ѵ�.

	[CPU]			[GPU]			[�����]
	RAM				VRAM
Application		 FrameBuffer
*/

/* ----- ��Ʈ��( BITMAP ) ----- */

// Bit + Map �� ���ڷ� ��Ʈ�� ������ ���̶�� �ǹ��̴�. ������ �̹����� �����ϴ� �̹��� ���� ���� �� �ϳ��̸� ���� �⺻���� ����̴�.

/*
�ȼ� �� �Ҵ��ϴ� ��Ʈ�� ũ�⿡ ���� �پ��� ���� ǥ���� �� �ְ� �ȴ�.

�ȼ� �� ��Ʈ ��	:	�ȼ��� �Ҵ��� �� �ִ� �� ��
1					2 ^ 1 = 2
8					2 ^ 8 = 256
16					2 ^ 16 = 65,546
24					2 ^ 24 = 16,777,216
32					2 ^ 32 = 4,294,947,296

���ſ��� 256�� ������ ������ ���� �� ������ �׸��� ���� �ȷ�Ʈ��� ������ ����ߴ�.
���� ���̺��� ������ �غ��ؼ� �� �ε����� �̹����� ǥ���ϴ� ����̴�.
24��Ʈ( �������� 256 Į��� ���ϸ� �����̶� true color ��� �ߴ�. )�̻󿡼��� �׷� �ʿ䰡 ���� �ʼ����� ���� ������ ǥ���� �� �ְ� �Ǿ���.
*/

/* ----- WIC( Windows Imaging Component ) ----- */

/* BMP ���� �ҷ��ͼ� �׸��� */

// �̹����� �ȼ��� �̷���� �迭�̸� �� ������ ���Ϸ� ������ ���� jpg, png �� ���� �׸������̴�.
// BMP ������ �ȼ� �����͸� �迭�� �����ϰ� �ֱ� ������ �����ϴ�.

/*
BMP ���� ����

[�̸�]			[Ÿ��]				[����]
BMP ���		BITMAPFILEHEADER	BMP ���Ͽ� ���� ����
��Ʈ�� ����		BITMAPINFOHEADER	BITMAP ������ ���� �� ����
�ȷ�Ʈ			LOGPALETTE			�ȷ�Ʈ �ε����� ���� ���� �迭
��Ʈ�� ������	void *				���� �ȼ� �迭
*/

/*
BITMAPFILEHEADER

WORD bfType : ���� Ÿ���̴�. ������ BM�� �Ǿ�� �Ѵ�.
	=> ( 0x4D42 - B : 42, M : 4D ������ ��������� ���� �ٲ�� �� ���� )
DWORD bfSize : BMP ������ ũ��( byte )
WORD bfReserved1 : ���� ����1
WORD bfReserved2 : ���� ����2
DWORD bfOffBits : ��Ʈ�� �����Ͱ� �ִ� �ּҿ� ���� ������
*/

/*
BITMAPINFOHEADER

DWORD biSize : ����� ũ��( byte )
LONG biWidth : ��Ʈ�� ����
LONG biHeigh : ��Ʈ�� ����
WORD biPlanes : 1�� ����
WORD biBitCount : 1�ȼ��� ���Ǵ� ��Ʈ ��( 1, 8, 16, 32 �ַ� ��� )
DWORD biCompression : ������
DWORD biSizeImage : ��Ʈ���� ũ��
LONG biXPelsPerMeter : ���ʹ� ���� ȭ�� ��
LONG biYPelsPerMeter : ���ʹ� ���� ȭ�� ��
DWORD biClrUsed : �ȷ�Ʈ�� ���� ��
DWORD biClrImportant : ����
*/

/*
1. BMP ���� ����
2. BITMAPFILEHEADER �б�
3. BITMAPINFOHEADER �б�
4. BITMAPFILEHEADER �� bfOffBits ��ŭ �ǳ� �ٱ�
5. �ȼ� ������ �б�
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
	BMP ������ �о�� ID2D1Bitmap �������̽��� �߰��Ѵ�.
HRESULT LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap);
	��ȯ�����δ� HRESULT �� ����ϰ�, Bitmap �������̽��� ���� �������� �ּҸ� �޾Ƽ� ������Ʈ�� �����Ѵ�.
	�������� �����͸� ����ϴ� ������ �ٽ� �� �� ������ ���� ������ ����.
		�Ϲ� ������ �Ű������� �޾Ƽ� ���� ������ �� - ������ �ּҰ��� �ʿ�
		������ ������ �Ű������� �޾Ƽ� ���� ������ �� - ������ ������ �ּҰ��� �ʿ�
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

1. ���� �б�
	a. ifstream �� ����Ͽ� binary ��带 ������.
2. ���� ��� �б�
	a. BITMAPFILEHEADER ����ü�� �о� ���� ���ϴ�.
	b. ifstream.read() �� char* �� �Ű������� �Ѱ���� �Ѵ�.
	c. ���� reinterpret_cast �� ����Ͽ� ����ü�� char* �� ��ȯ�Ͽ���.
3. ��Ʈ�� ��� �б�
	a. BITMAPINFORHEADER ����ü�� �о� ���� ���ϴ�.
	b. ����� �о� ���� ��Ʈ�� �⺻ ������ �� �� �����Ƿ� �߸��� ������ �ɷ� �ش�.
4. �ȼ��� �ǳʶٱ�
	a. ifstream.seek() �� ����ϸ� ����Ʈ ������ �̵��� �����ϴ�.
	b. ����� bfOffBits �� ���� �ȼ��� ���� ��ġ�� ����Ǿ� �ִ�.
5. ��Ʈ�� �б�
	a. ��Ʈ���� ������ �������� std::vector<char>�� ����ߴ�.
		i. ũ��� ��Ʈ�� ����� biSizeImage ���̴�.
	b. istream.read() �� char* �� �ޱ� ������ std::vector ���� �����ָ� �η��� �Ѵ�.
		i. std::vector �� ���� �ڷ����� ������
		ii. ���� ù ��° ��ʼ��� �ּҸ� ������ char* �� ���� ���� �ȴ�.
6. ��Ʈ�� ����
	a. ID2D1HwndRenderTarget::CreateBitmap �� ����� ��Ʈ�� �������̽��� �����Ѵ�.
		i. ���� ������ ������ ���� ������ �����Ѵ�.
		ii. RGBA ���ҵ��� ���� ������ BGRA �̴�.

������ ���� std::vector �� �����ͷ� �����ϴ� ����̴�.
��� BITMAP �� ���� �� ������ �����̴�. ������� ���� ���γ� RGBA ���� �������� �о� �� �׿� �°� ������ �о�� ������,
���⿡���� �־��� ���Ͽ� ���� �͸� ó���ߴ�.
�⺻������ BMP ������ Bottom-Up ���� �����Ѵ�. ���� BITMAP ����� biHeight �� ������ ��찡 �ִµ� �� ���� Top-Down ����̴�.
*/

/*
������ �̹���, pitch ������ �о �ùٸ� ��ġ( ���� )�� �����ϸ� �ȴ�.
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
BMP �� �׸� �� ����� �����ϰ� �׷�����
	���� RGM 30, 199, 250
	��� �ȼ��� �������� �о ������ ������ �����ϰ� ����� �ָ� �ȴ�.
		�� ����Ʈ�� ��ü ��Ʈ���� �о� ���� �ڵ� �ۼ�
		�о�� ������ ������ ������ RGBA�� ��� 0���� �����.
		LoadBMP() �� ��Ʈ�� �������� ���� �Ӽ��� ������ ��� �Ѵ�.
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
	1. ���� ����
	std::ifstream file;
	file.open("Data/32.bmp", std::ios::binary);

	BITMAPFILEHEADER bmh;
	BITMAPINFOHEADER bmi;

	2. BITMAPFILEHEADER �б�
	file.read(reinterpret_cast<char*>(&bmh), sizeof(BITMAPFILEHEADER));
	3. BITMAPINFOHEADER �б�
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
	4. �ȼ��� �ǳʶٱ�
	file.seekg(bmh.biOffBits);
	5. ��Ʈ�� �б�
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

// �� �������� ������ ��Ʈ�� �ε� �Լ��� ���������� ����ϱ� ��ƴ�. BMP ������ �뷮�� Ŭ �� �ƴ϶�, �Ϻ��ϰ� ��������
// �ʾƼ� �� �д� ��찡 �� ����. png �� ���� ������� ���� ���� ��� ������ �����ϱ� �ſ� ��ƴ�.

// ����ũ�μ���Ʈ������ ������ �ý��� �����ڵ��� ���� ������ �̹������� ���� ������( low-level ) API �� �߰��� �־���.
// Windows Imaging Component �� Windows Vista ���� ���ԵǾ� ������ Windows XP ���ϴ� �߰��� ��ġ�ϸ� ����� �����ϴ�.

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

WIC �� ����ϱ� ���ؼ��� wincodec.h �� ���Խ��Ѿ� �Ѵ�. WIC ���� ���丮 �����̶� ���丮�� ���� ����Ʈ �����͸� ����� �����ϰ�, �������� ������ �ʿ��ϹǷ� Release �� �������̵� �ߴ�.
���� �Լ��� �����ϱ� ���ؼ� WIC�� ����� ���� �б������ LoadWICImage ����Լ��� �߰��ߴ�.
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

#pragma comment( lib, "WindowsCodecs.lib" ) : Direct2D �� ���������� ����� ���̺귯�� WindowsCodecs.lib �� ���ս��� �ش�.

CoInitialize(nullptr); : COM ������Ʈ�� ����ϱ� ���� �ý����� �ʱ�ȭ �Ѵ�.
	DirectX �� COM �� ����Ѵٰ� �ߴµ�, �ʱ�ȭ�� �ҷ� �� ���� ����. DirectX �� COM ȯ���� 100% ������� �ʰ�
	���丸 �Ϻ� ����ϴ� ������ ���ϰ� �ִ�.
	�ٸ� �÷��������� Ȯ���� ���� ������ ������ COM �ý����� ����� �� ������ ���̴�. ������ WIC �� �̸� �״��
	������ ���� ȯ���̹Ƿ� COM �� �Ϻ��ϰ� �����ؾ߸� �Ѵ�.

HRESULT CoCreateInstance()
	REFCLSID rclsid Reference to Class ID, ������ ������Ʈ�� Ŭ���� ������
	LPUNKNOWN pUnkOuter ����ü( aggregate object )�� ���� ������, nullptr �� �ѱ�� ����ü�� �ƴ� ���� ��ü�� �����Ѵ�.
	DWORD dwClsContxt Class Context, ������ ��ü�� ����Ǵ� ȯ���� �����Ѵ�.
	REFIID riid Refernce to interface ID
	LPVOID *ppv riid�� ������ �������̽� �����Ϳ� ���� �ּҷ� ������ �������̽� �����͸� ���� �ش�.

�Ű������� 5���� �䱸������ ���ڴ� 4���� �� �� �ִ�. IID_PPV_ARGS() �� ��ũ�η� ���ο��� 2���� �Ű������� �Ѱ� �ش�.
�� �� ��� ����ص� ������, riid�� �츮�� ������ mspWICFactory�� ���� ������ �� �ֱ� ������ �ڵ� �� �� ���̱� ���� ����ϴ� ���̴�.
Ǯ� ���� IID_IWICImaginaFactory, mspWICFactory.GetAddressOf() �� �Ѱ��ָ� �ȴ�.
*/

/*
���� �б�
	1. ���ڴ� ����
	2. ���ڴ����� ������(frame) ȹ��
	3. ������(Converter)�� ����� �����͸� ��ȯ
	4. ��ȯ�� �����Ϳ��� ��Ʈ�� ����
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
	const GUID *pguidVendor Globally Unique Identifider ( ���� �ߺ����� �ʴ� ������ ������ ���� ���Ե� )
		������ ������ ���� ȸ�� �� ������ ���ڴ��� ������ �� �ִ�.
	DWORD dwDesiredAccess �б�,����,�б⾲�� ���� ���� ���� ����� �����Ѵ�.
	WICDecodeOptions metadataOptions ��Ÿ ������ �ɼ��̴�.
		�����͸� �����ϱ� ���� �����ͷ� meta�� ~�� ���� �̶�� �ǹ��̴�. �̹����� �ܼ��� �ȼ� ����������,
		gif�� ���� ���� ���� �� �ִ� ��쵵 �ִ�. �̷��� �ȼ� �����Ϳ� ���� �߰� �����Ͱ� ��Ÿ �����Ͱ� �Ǵ� ���̴�.
		ĳ�ø� �� ������, �ٷ� �ε��� �������� ���Ѵ�.
	IWICBitmapDecoder **ppIDecoder ������ ���ڴ��� ���� ������ �ּ�

HRESULT IWICBitmapFrameDecode::GetFrame()
	IWICBitmapFrameDecode **ppIBitmapFrame ���ڵ��� �������� ���� �������� �ּ��̴�.
*/

/*
HRESULT ImageExample::LoadWICImag(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
	...
	// ���� ������
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
	IWICFormatConverter **ppIFormatConverter ������ �����͸� ���� �������� �ּ��̴�.

HRESULT IWICFromatConverter::Initialize()
	IWICBitmapSource *pISource ��ȯ�� ��Ʈ���� �����Ѵ�. ���ڵ��� �������� �Ѱ��ָ� �ȴ�.
	REFWICPixelFormatGUID dstFormat ��ȯ ���� �ȼ� ������ �����Ѵ�.
	WICBitmapDitherType dither ����� Ÿ���� �����Ѵ�.
		��ǻ�ʹ� ���� ���� ���� ǥ���� �� �ִ� ������ �������̱� ������ ���� ���� �������� �����ϴ� ����� ����Ѵ�.
	IWICPalette *pIPalette ��ȯ�� ������ �� ����� ���� �ȷ�Ʈ�� �����Ѵ�.
	double alphaThresholdPercent ���İ��� �Ӱ����� �����Ѵ�. ���� ���İ� 25�̸��� �ȼ��� ��� �����ϰ� ����ų� �� �� �ִ�.
	WICBitmapPaletteType paletteTranslate ��ȯ�� ����� �ȷ�Ʈ Ÿ���� �����Ѵ�.
*/

/* ----- ��������Ʈ( Sprite ) ----- */

// ��ǻ�� �׷��ȿ��� 2D �̹���, Ư�� �������� ���� �����̴� ������Ʈ�� ��������Ʈ��� �θ���.
// �����̶�� ���ó�� �̹����� ��� �̹��� ���� �� �ٴϴ� ����� ����� ������ �̸��̴�.
// �ʱ� ���ӱ⳪ ��ǻ�͵��� �̷� ��������Ʈ�� �ϵ����� �����Ͽ� ���� ó���� �Ϸ��� ����ߴ�.

/* ----- �̱���( Singleton )���� ----- */

// �����ڴ� �ϳ��� �����ϸ� �ȴ�.
// Ŭ���� �������� �����ϸ� ���� �� �����ڰ� �Ҹ����� �ν��Ͻ��� �ϳ��� �����Ǵ� ���´�.
// �̷� ��Ÿ���� �ڵ��� ���ؼ� ��ȵ� ���� �̱��� �����̴�.

/*
�����ڰ� ���� �� ȣ��Ǿ ������ �����Ǵ� ��ü�� �ϳ�
�� �ٽ� �����ڰ� ȣ��Ǹ�, ���� ���� ���Ŀ��� �̹� ������ ��ü�� ��ȯ

�� �ϳ��� ��ü�� ���ؼ��� ��¿ �� ���� ���� ����� ����� �� �ۿ� ���� ������, �ܺη� ������� �ʴ� ������ �ִ�.

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

class ... final : �Ŵ����� �� ��ü�� ��� ������ ������ Ŭ����
	��, ���̻� �Ļ��Ǿ�� �ȵǹǷ� final Ű���带 ��������� �ٿ� �ִ� ���� ����.
static Singleton& Instance() : �̱��� ������ ���ݱ����� ��ü �ν��Ͻ�ȭ ��İ��� �ٸ��� �� �Լ��� ���ؼ� �����Ѵ�.

private:
	Singleton();
	Singleton(const Singleton&);
	void operator=(const Singleton&);
������� �⺻ ������, ���� ������, ���� �������̴�.
�̵��� private���� ���� ���� ������ ���� ��ü�� ���� ��ü�� ó�� �ٸ� ������ ���ο� ���� �Ұ����ϵ��� ���� ���ؼ� �̴�.
�⺻������ ���� ���� ���� instance�� ���� ��� ����� �����ϹǷ� Ŭ������ ����ǰų� ����Ǹ� �ȵǱ� �����̴�.

���� �̱��� ���� ������ �� ���� ���ϴ� �����ڿ��Դ� ������ ����� ����̱⵵ �Ѵ�.
�ƹ��� ���� ����̶� ������ ���� ������ ����ؾ� �� ȿ���� �� �� �ִ� �� ó��, �̱��� ���� ���� �ʹ� �������� �ʴ� ���� ����.
������ ���� ������ ���� �� �ִ�.
	������ ���ü� ����
		���ͳ� �˻��� �� ���� thread-safe ����� �̱��� ������ ���� �߰��� �� �ִ�.
	�� ����ñ��� �޸𸮿� ����
	�׽�Ʈ�� �����
		����Ʈ���� ���з� �� ���� �׽�Ʈ��� ���� �ִ�. ���� ������ �׽�Ʈ�� �����ϴ� ���ε�,
		�̱����� ����ϸ� �̷� ��Ŀ� ���� �ȴ�.��
	��ȯ ���� �߻�
		A �� B �� �̱����� ���
		B �� A �� �ν��Ͻ��� ���
		�����ڸ� ����ٺ��� ���� ���� ��찡 ���� �߻��Ѵ�. �̷��� ���� ��ȯ �����̶� �θ��� OOP ������ ���ϴ� �����̴�.
	Ŭ���� Ȯ���� �����
		OOP �� ����-��� �����̴�.
		�̱����� ����ϸ� ������ �������̽��� �ϳ��� ���̰� �ǹǷ� Ȯ�强�� ���� �ʴ�.
*/