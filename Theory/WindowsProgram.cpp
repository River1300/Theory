/* ----- ������ ���� �����丮 ----- */

/* Windows API */

// ����ũ�μ���Ʈ ������ �ü������ ����ϴ� API �̸�, ������ ������ �����̴�. Windows 3.1 �� ź������ �Բ��߱� ������ C ���εǾ� �ִ�.
// ���� ��ũ ���̺귯��( DLL ) ����� ����ϸ� OS ����, GUI, �׷���, ��Ƽ�̵�� ���� ������ �� �ִ�.

/*
�ü���� ũ�� ����� ������ ������ ����Ǿ����� ũ�� ������ ���� �����ߴ�.

Win16 : 16��Ʈ ���� ������� Windows 3.1 ���߿� ���ȴ�.
Win32 : 32��Ʈ ���� ������� Windows 95 ���� ���ȴ�.
Win32s : subset �� ���ڷ� Win32 �� �Ϻ� ����̶� �ǹ��̴�.
	=> �Ϻ� 16��Ʈ �����쿡�� Win32 �� ����ϱ� ���� ����� ����.
Win32 for 64bit : 64�� ������ ���ο� API �� �߰����� �ʾҴ�.
	=> �ü�� ���ο� ������ ���̾�( WOW64 )�� ����� 32��Ʈ ���α׷��� 64��Ʈ �ü�������� ������ �� �ֵ��� ���������.

����, ���� �ֽ� API �� Win32 �� �� �� �ִ�.
*/

/* MFC( Microsoft Foundation Class Library ) */

// Window API �� C �� �Ǿ� �־ �̸� ���� �� �����ϰ� ����ϱ� ���� C++ �� ����( Wrapping )�� API�� ���Ѵ�.
// ���־� ������, �پ��� ���ø�, ���� ����Ʈ������ ���� ��ÿ� ȹ������ ��ɵ��� ������ ������, Visual Studio �� �⺻ ����Ǿ� �־ ���� ����ϴ� ����̴�.
// ������ Microsoft ���� ��� �� MFC �� ����ϱ� ������ Visual Basic �� ����϶�� ������ ������ �ſ� �����ϴ�.
// C++ ǥ�ؿ��� ��� �Լ����� Microsort ��Ÿ�Ϸ� ����߱� ������ �ᱹ 2014�� ���������� ���� ������ �ߴ��ߴ�.

/* Windows Template Library */

// ����ũ�μ���Ʈ ���ο��� ����ϱ� ���� ������ ���̺귯���� ���� ����Ͽ��µ� Win32 �� �����Ǵ� �ڵ尡 ���Ƽ� �αⰡ ���Ҵٰ� �Ѵ�.
// ���� �Լҹ��� ���鼭 ���¼ҽ��� Ǯ���� ���ݵ� ������Ʈ �ǰ� �ִ�.

/* Windows Form */

// ����ũ�μ���Ʈ���� �߽����� ���� �÷��� .NET �� ��ǥ�ϸ鼭 ������ API �̴�.�θ� ����� �� �ֵ��� ���¼ҽ��� �����Ǿ�����
// ������ MFC �� ��ü�� �� �ֵ��� ������� �༮�̴�. ������ 2014�⿡ ���� ������ �ߴܵǾ� ���� ������ �̷����� �Ǿ���,
// ũ�ν�-�÷��� ������ ���� �뵵�θ� ���ȴ�.

/* Windows Presentation Platform */

// ���ʷ� �ü������ �ϵ���� ������ �����ϱ� ���� ���ߵ� API�̴�.
// Ȯ���ص� �ȱ����� ���� �׷���, ��Ʈ�� �������� ������ �� �ִ� Ÿ�����׷���, �ִϸ��̼� �� �׷��ȿ� Ưȭ�� API��
// ���ο����� DirectX �� ����� �ϵ���� ������ �����Ѵ�.
// �׷��� ���� �����ڵ� ���̿����� �򰡰� �ָ��Ͽ���. �ϵ���� ������ ���ؼ��� DirectX �� ����ϴ� ���� �̵��̰�,
// �Ϲ� ���ø����̼��� ����� ���ؼ��� �����߱� �����̴�.

/* Windows RT( Runtime ) */

// Windows 8 �� �Բ� ��ǥ�� ���ο� ũ�ν�-�÷��� API�̴�.
// ���������� ���� ����Ͽ� �����ϱ� ���� ����������� ��� ������ ������ C++ �̶� �ӵ��� ������.
// ���� �Ű�Ἥ ���� �༮������ ����ũ�μ���Ʈ�� ����ȭ ��ȹ�� ����Ǹ鼭 ���� �ٷθ� �˾Ҵ�.

/* UWP( Universal Windows Platform ) */

// Windows 10 �� �Բ� ��ǥ�� API �� WinRT �� ���������� ������ 10 �����, Xbox, PC �� �����Ϸ��� �߽��� ��ȹ���� ����ߴ�.
// �ֱ� XBOX �������� PC �� ���� �ຸ�� ���� ��ȭ�Ǹ鼭 ��¿ �� ���� UWP �� �ٷ���� ���� ������ �𸣰ڴ�.