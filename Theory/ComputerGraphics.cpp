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

