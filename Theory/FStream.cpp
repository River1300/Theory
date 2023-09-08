/* ----- < ����� ��Ʈ�� > ----- */

// ��ǻ�ʹ� �Է� -> ��� -> ��� ���� �۾��Ѵ�.

/*
��Ʈ���� �ʿ伺

���� ����� �� ���� ó���� �� �ִ� ���� �ʴ� 1 ����Ʈ��� ������ ����. �׷��� �� ���� �Է��� 100 ����Ʈ ���Դٸ�?
�׷� ���� �Է��� ó���ϱ� ���� 100 �� ������ ��¸� �ϰ� �־�� �Ѵ�.
�־��� ��쿡�� 1�ʿ� �Է¹��� 100 ����Ʈ�� ����ϴ� 100 �� ���� ���α׷��� ���� ���� �� �ִ�.

�̷��� ������ ��������( BottleNeck )�̶� �θ���.
*/

// ��Ʈ����( �Ǵ� ���۸� )�� �̷��� ���������� ��ȭ�ϱ� ���� ���̵���, �ּ��� ���α׷��� ���ߴ� ���� �����ڴ� �ذ�å�̴�.

/*
'a'
"Mu Data"  => Stream => buffer => ���
123
*/

// ���� �����Ͱ� ������, �ش� �����͵��� ��Ʈ������ ���۷� ���ݾ� �������� ������� ���޵Ǵ� ����̴�.
// �׷��� �Է��� ���� �������� �ʰ� ���������� ���� �� �ְ� �ǰ� ��µ� �������� ���� �� �� �ִ�.
// �׷���, �翬�ϰ� ���۴� Ŀ���� �ȴ�.

/*
							ios_base

							  ios
				ostream					istream
	ostringstream	ofstream	ostringstream	ofstream

ios �� ios_base �� ��� ����� ��Ʈ���� ���ʰ� �Ǵ� Ŭ������ �߿��� !, bool �����ڸ� ������ ������ Ÿ�԰� ������� �⺻���� ó����
����ϰ� �ִ�. �̸� ��� �޾� ���� �Է�/������� ���еǸ�, �ٽ� ���ڿ�/���� �� ���еǾ� �Ļ��Ǿ� �ִ�.
�̷� �������� ����� ���� cout, cin �� ����ϵ� ��� ��Ʈ���� ���� �����ϴٴ� ������ �ִ�.
*/

/* ----- < ����ó�� > ----- */

// �Ϲ������� ��ǻ���� �޸�( 1�� �����ġ )�� �뷮�� ���� ������, �� ū �����͵��� �޸� ���� �뷮�� ū ���� ��� ��ġ�� �����Ѵ�.
// �ϵ� ��ũ( HDD )�� �̿� ���ϸ�, ������ ���� Ư¡�� ������ �ִ�.
//		1. �� �ֹ߼� : ������ ���� �����Ͱ� ���� �ִ�.
//		2. �������� : ó������ ������� �����Ϳ� ����

// ���������� Ư������ ���� ������ ��ũ�� �����ϸ� ����Ʈ�� �迭ó�� �Ҵ�ȴ�.
// �޸𸮿� �Ҵ�� ����Ʈ ������ ���������� �̷��� ������ �ؼ��Ϸ��� ��� ���������� �߿��ϴ�.
// ���� �ؽ�Ʈ �����̸� �� ����Ʈ�� �� ������ ���ڰ� �Ǹ�, ���� ���� ���¶�� 4����Ʈ�� ������ �ϳ��� ��Ÿ���� ���� �ȴ�.

/*
������ �о ȭ�鿡 ���

1. ������Ʈ ����
2. ���� ������ �ϳ� �ʿ��ϴ� �޸��忡 ������ ���� �ۼ��Ѵ�.
	{
		--- MONSTER DATA ---
		JELLY,1,1,1
		WOLF,5,5,5
		DEMON,10,10,10
	}
3. ���� ���� ������Ʈ�� Data ��� ������ ����� �� �ȿ� �ؽ�Ʈ ������ �����Ѵ�.
4. main.cpp �� �����Ѵ�.

ũ�� ���� ��Ʈ���� ����ϴ� ������ ������ ����.
	1. ���� ��Ʈ�� ��ü ����
		�б�/���� ��带 �����Ͽ� ��ü�� �����Ѵ�.
		�����ڿ��� ������ �����ϰų�, �� ��ü�� ������ �� open() ��� �Լ��� �� �� �ִ�.
	2. ���� �۾�
		��Ʈ�� ��ü���� �����͸� �������ų� ���� �ִ´�.
	3. ���� �ݱ�
		close() ��� �Լ��� ȣ���Ѵ�. ������ �ݾƵ��� ������ �ش� ������ �ٽ� �� �� ����.
*/

//#include <iostream>
//#include <fstream>	// ���ϰ� ���õ� ����½�Ʈ���� fstream�� ���� �Ǿ� �ִ�.
//bool LoadFile(const char* filename)
//{
//	std::ifstream ist(filename); // ifstream �ν��Ͻ��� �����Ѵ�.
//	if (!ist)
//	{
//		std::cerr << filename << " ������ ã�� �� �����ϴ�.\n";
//		return false;
//	}
//	// ���������� ��Ʈ�� ��ü�� �����ϰ� ���� �ش� ������ ���� �ΰ�, ���ο��� ��ġ�� ���� ���� ó������ ���߰� ���� �غ� �Ѵ�.
//	// ���ڸ� �ϳ��� �����´�.
//	// >> ������ : �� ��ü�� Ÿ�Կ� �°� �ڵ����� �����͸� �����´�.
//	// get() ����Լ� : �Է����� ���� �������� ���� �����͸� �����´�.
//	char ch;
//	while (ist >> ch)
//	{
//		std::cout << ch;
//	}
//
//	ist.close();	// ��� �۾��� ������ close �� ���� ������ �ݾ� �ش�.
//	return true;
//}
//int main()
//{
//	// ���� ��δ� C:/dir1/dir2 �� ���� ������� ����̺� ���� ����Ѵ�.
//	// �ٸ�, ������ ��� ���͸����� ���� �˻��Ѵ�. ���� ���͸���� �ϴ� ���� ���������� ����Ǵ� ��ġ�� �ǹ��ϴ� ������
//	// ���� �߿��� ������Ʈ ������ �����ϴ� ���͸��� ���� ���͸��� �ȴ�.
//	LoadFile("Data/SimpleData.txt");
//}

/* ���� üũ */

// ���� ��Ʈ�� ��ü�� ���������� ������ ���� ó���� ���� ����� �׻� ���ο��� ���� ���� �÷���( error state flag )�� ����� �д�.
// �̷��� ���� �÷��״� ������ ���� ��� �Լ��� Ȯ�� �����ϴ�.

/*
good() : ���� ����
fail() : ����ġ ���� ó��( ������ ��������� ���ڰ� �´ٴ��� )
eof() : ������ ���� ����. ��Ȯ�ϰԴ� ������ �ƴ� ������ �� �� �ִ�.
bad() : �ɰ��� ����( ���� �ջ� �� )
rdstate() : read error state flag �� ���ڷ� ���� ���� �÷��� ��� ���� �´�.
*/

//#include <iostream>
//#include <fstream>
//bool LoadFile(const char* filename)
//{
//	std::ifstream ist(filename);
//	if (!ist)
//	{
//		std::cerr << filename << " ������ ã�� �� �����ϴ�.\n";
//		return false;
//	}
//	char ch;
//	while (ist.get(ch))
//	{
//		if (!ist.bad())
//		{
//			std::cerr << "������ �ջ�Ǿ����ϴ�.\n";
//			ist.close();
//			return false;
//		}
//		if (!ist.fail())
//		{
//			std::cerr << "�߸��� ���� �����Դϴ�.\n";
//			ist.close();
//			return false;
//		}
//		std::cout << ch;
//	}
//	ist.close();
//	return true;
//}

// ���� ���� ó�� ������ �� ��, ���Ϸ� ������ ������ �� ������ �˻��ϴ� ���� ���� �Ϲ����̴�.
// iostream ������ exceptions() ��� ��� �Լ��� ���� ���� �� �Ϲ�ȭ�� ����ó���� ������ �� �ִ�.

//#include <iostream>
//#include <fstream>
//bool LoadFile(const char* filename)
//{
//	std::ifstream ist;
//	// exceptions ��� �Լ��� ���� ���� ��Ʈ�� ������ ������, �ش� ������ �߻����� �� �ڵ������� ���ܸ� �߻����� �ش�.
//	// ���� �ҽ��� �ٸ� �������� ���� Ž���� ���� �����ڴ� �⺻ �����ڸ� ���������, open() ��� �Լ��� ���� ���� ������ �ҷ� ���.
//	ist.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//
//	try
//	{
//		ist.open(filename);
//		char ch;
//		while (ist.get(ch))
//		{
//			std::cout << ch;
//		}
//		ist.close();
//	}
//	catch (std::ifstream::failure e)
//	{
//		std::cerr << "���� ���� ���� ���ܰ� �߻��߽��ϴ�.\n" << e.what() << '\n';
//		ist.close();
//		return false;
//	}
//	return true;
//}

/* ���� ������ ���� */

// ���� ������ ���α׷��Ӱ� ���� �����ϴ� ��찡 ��κ��̴�. �� ���õ����ʹ� ������ ���� ���� Ŭ������ �������� �پ��� ���͸� ����� ���� ���̺��̴�.

//class Monster
//{
//private:
//	std::string mName;
//	int mLevel;
//	int mHp;
//	int mMp;
//};

//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <sstream>
//class Monster
//{
//private:
//	std::string mName;
//	int mLevel;
//	int mHP;
//	int mMP;
//
//public:
//	Monster(std::string name, int level, int hp, int mp) :
//		mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp }
//	{
//
//	}
//};
//bool CreateFromFile(const char* filename, std::vector<Monster>& vector)
//{
//	std::ifstream ist;
//	ist.exceptions(std::ifstream::badbit);
//	try
//	{
//		ist.open(filename);
//		std::string buffer;
//		std::vector<std::string> argVector;
//
//		std::getline(ist, buffer);
//		while (!ist.eof())
//		{
//			std::getline(ist, buffer);
//			if (std::count(buffer.begin(), buffer.end(), ',') == 3)	// _Val ���� ã��, �� ������ 3���� ���
//			{
//				std::stringstream ss(buffer);
//				for (int i = 0; i < 4; i++)
//				{
//					std::string token;
//
//					std::getline(ss, token, ',');
//					argVector.push_back(token);
//				}
//				vector.push_back(Monster{
//					argVector[0],
//					std::stoi(argVector[1]),
//					std::stoi(argVector[2]),
//					std::stoi(argVector[3])
//					});
//				argVector.clear();
//			}
//			else
//			{
//				if (buffer.length() != 0)
//				{
//					std::cerr << "���� ������ ����� �߸��Ǿ���.\n";
//				}
//			}
//		}
//		ist.close();
//	}
//	catch (std::istream::failure e)
//	{
//		std::cerr << "���� ���� ���� ���ܰ� �߻��ߴ�.\n" << e.what() << '\n';
//		ist.close();
//		return false;
//	}
//	return true;
//}
//int main()
//{
//	std::vector<Monster> monsterList;
//	CreateFromFile("Data/SimpleData.txt", monsterList);
//}

/* ����� ���� ������ */

//#include <iostream>
//#include <vector>
//
//#include <fstream>
///*
//<fstream> ��� ������ ���� �����(File In/Out) ���� ����� �����Ѵ�.
//ifstream( ���� �Է� ��Ʈ�� ), ofstream( ���� ��� ��Ʈ�� ), �׸��� fstream( ���� ����� ��Ʈ�� )�� �ִ�.
//������ ���� �ݰ�, ���Ϸκ��� �����͸� �а� ���� ���� ���� ���� �۾��� ������ �� ���ȴ�.
//*/
//
//#include <sstream>
///*
//<sstream> ��� ������ ���ڿ� ��Ʈ���� �ٷ�� ����� �����Ѵ�.
//istringstream( �Է� ���ڿ� ��Ʈ�� ), ostringstream( ��� ���ڿ� ��Ʈ�� ), �׸��� stringstream( ����� ���ڿ� ��Ʈ�� )�� �ִ�.
//���ڿ��� ��Ʈ������ ��ȯ�ϰų�, ��Ʈ������ ���ڿ��� �����ϴ� ���� ���ڿ� ó�� �۾��� ���ȴ�.
//�Ϲ������� ���ڿ��� �Ľ��ϰų� Ư�� �������� �����ϴ� �� ���ȴ�.
//*/
//
//class Monster	// Monster ��ü�� ȿ�������� �����ϰ� ���� ����¿��� ����ϱ� ���� ������� Class
//{
//private:
//	std::string mName;
//	int mLevel;
//	int mHP;
//	int mMP;
//public:
//	Monster() : mName{}, mLevel{}, mHP{}, mMP{} {}
//	Monster(std::string name, int level, int hp, int mp) :
//		mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp } {}
//	// ���𿡼��� friend Ű���带 ����Ͽ� ģ�� �Լ��� ������ ���.
//	friend std::istream& operator >>(std::istream& inputStream, Monster& monster);
//	friend std::ostream& operator <<(std::ostream& ostream, Monster& monster);
//// Ŭ������ Ư���� ������ ����, ���� ��� CSV ����, �ؽ�Ʈ ����, �Ǵ� ����� ���� ���Ŀ� ���� 
//// �����͸� ó���ϵ��� ����� �� �ִ�. �� Ŭ������ ����ϸ� �����͸� �а� ���� �� �ϰ��� ������ ������ �� �ִ�.
//};
//std::istream& operator >>(std::istream& inputStream, Monster& monster)
//{
//	std::string buffer;
//	try
//	{	// ��Ʈ������ ���ڿ��� ','�� �����Ͽ� �о�ͼ� �� ��� ������ �Ҵ��Ѵ�.
//
//		// 1. ���� �̸��� ��Ʈ������ �о�´�.
//		std::getline(inputStream, buffer, ',');
//		monster.mName = buffer;
//		// 2. ���� ������ ��Ʈ������ �о�´�.
//		std::getline(inputStream, buffer, ',');
//		monster.mLevel = std::stoi(buffer);
//		// 3. ���� ü���� ��Ʈ������ �о�´�.
//		std::getline(inputStream, buffer, ',');
//		monster.mHP = std::stoi(buffer);
//		// 4. ���� ������ ��Ʈ������ �о�´�.
//		std::getline(inputStream, buffer);
//		monster.mMP = std::stoi(buffer);
//	}
//	catch (std::exception e)
//	{
//		std::cerr << "������ ������ �߸� �Ǿ���.\n";
//	}
//
//	// ��Ʈ���� ��ȯ�Ѵ�. �̷��� ���ӵ� �Է� �۾��� �����ϴ�.
//	return inputStream;
//}
//std::ostream& operator <<(std::ostream& ostream, Monster& monster)
//{
//	try
//	{	// �� ����� ��Ʈ������ �����鼭 ��ǥ�� �����ָ� �ȴ�.
//		ostream << monster.mName << ','
//			<< monster.mLevel << ','
//			<< monster.mHP << ','
//			<< monster.mMP << '\n';
//		// �̷� �����͸� ��ǥ�� ���еǾ� �ִٰ� �Ͽ� CSV( Comma Seperated Values )��� �ϸ�, ��ȹ�ڵ��� ģ�� ��������
//		// �����͸� �ű�� ���� ���� ����̴�. ���� �뷱�� ���̺��̳� ������ ���̺��� �� �θ��� ���̺� �����͵��� csv��
//		// ó���ϸ� ���� ���� �����ϰ� ó���� �� �ִ�.
//	}
//	catch (std::exception e)
//	{
//		std::cerr << "��Ʈ���� �� �� ������ �߻��߽��ϴ�.\n";
//	}
//	return ostream;
//}
//bool CreateFromFile(const char* filename, std::vector<Monster>& vector)
//{
//	std::ifstream ist;
//	ist.exceptions(std::ifstream::badbit);
//	try
//	{
//		ist.open(filename);
//		std::string buffer;
//		std::vector<std::string> argVector;
//		getline(ist, buffer);
//		while (!ist.eof())
//		{	// ��Ʈ������ getline() �� �ؼ� �ƹ��� ���ڸ� �� �о� ���� ���ܰ� �߻��Ѵ�.
//			// peek() ��� �Լ��� ������ ��Ʈ������ ���� ���������� �����鼭 ��¦ ������ ������ �Ѵ�.
//			// ���� �ϳ��� ���� �� �� ���ڰ� EOF( end of file )�̸� �ƹ��� �����Ͱ� ���ٴ� ���̴� �����ϸ� �ȴ�.
//			if (ist.peek() == EOF)
//			{
//				break;
//			}
//
//			Monster monster;
//			ist >> monster;
//			vector.push_back(monster);
//		}
//		ist.close();
//	}
//	catch (std::ifstream::failure e)
//	{
//		std::cerr << "���� ���� ���� ���ܰ� �߻��߽��ϴ�.\n" << e.what() << '\n';
//		ist.close();
//		return false;
//	}
//	return true;
//}
//int main()
//{
//	std::vector<Monster> monsterList;
//	CreateFromFile("Data/SimpleData.txt", monsterList);
//}

/* ----- < ���̳ʸ� ������ > ----- */

// ���ȿ��� ���� ���� ó���ϴ� ���� ���̳ʸ� �������̴�. �� �����ʹ� ��ǻ�� �޸𸮿� ����Ǿ� �ִ� �״�� ���Ϸ� ����ϴ� ���̸�
// �̷��� ����� ���̳ʸ� ����̴�. ������ ����� ��� ��Ʈ�� ��ü�� ���� �� ��带 binary�� ������ �ָ� �ȴ�.

/* ���̳ʸ� ������ �б�/���� */

// ���̳ʸ� �����͸� �аų� ���� ���ؼ��� char* �� ��ȯ�� �ϴ� ���� �⺻�̴�. ��, �����͸� char �迭�� ����� ����Ʈ�� �������� ����ϴ� ���̴�.

/*
���̳ʸ� �����Ϳ� ���� ��� �Լ�

ostream& ostream::write( char* s, streamsize n ); s�� ����Ű�� ���� �迭�� n���� ��Ʈ���� ����Ѵ�.
istream& istream::read( char* s, streamsize n ); s�� ����Ű�� ���� �迭�� ��Ʈ������ n���� ���� �о� �´�.

���̳ʸ� ��忡�� �۾��� ���� �����ؾ� �� ���� �ִ�.
������ �� ���͸� ���� �� ������ ������ �����̶�� ���� ��Ȯ�� �� �� �ִ�. ������ ���̳ʸ� �����ʹ� �ܼ��� ���̳ʸ� �������θ�
�Ǿ� �ֱ� ������ ������ ������ ��� �������� �� �� ����. �� ���տ� ���� �����ڷ� Ư���� ��ȣ�� ����� ���� �ְ�����,
�׸��� �������� �翬�� �δ��� �ȴ�.
���� ���� ���� �պκп� ���� �����Ͱ� �� ������ ������ �δ� ���� ����. �̷��� �͵��� ���� ���� �����Ͷ�� �ؼ� header���
���� �θ���. ���� ����� �ַ� ������ ����, �ش� ������ ������ ���� ������ ����ϴ� ���� �Ϲ����̴�.
*/

/*
���̳ʸ� ���ڿ� ����/�б�

JELLY �� 5���������� WOLF �� 4���� �̴�. �ؽ�Ʈ�� ��ǥ�� ���еǾ� ���� �� �־����� ���̳ʸ��� �����ڰ� ����. ���� ���ڿ���
������ ���� ���ڿ��� ���̸� ���� �����ϴ� ���� �Ϲ����̴�.
*/

//struct Header
//{
//	int version{ 1 };
//	int itemCount{};
//};

// �̷��� ���� ������ ������ POD( Plain Old Data )�� �ϸ�, ��ü�� �ƴ� �ܼ��� ���� �������� �� ������ �����̴�.
// ���� ���� ���´� �޸� �󿡼� �������� ����Ʈ �迭�� ǥ���� �� �ֱ� ������ �� ����( chunk )���� ������� �����ϴ�.

/*
POD�� Ư��

ǥ�� ���̾ƿ� Ÿ�� : ��ü ������ Ư���� ������ �ʴ´�.
	�������� �ƴϴ�. ( ���� �Լ� �� ���� ��� Ŭ���� )
	������ ����� ����.
	����� ������ ���� �����ڸ� ������.
������ Ÿ�� : ��Ʈ ���� ������ ������ �ܼ��� Ÿ���̴�.
	������ �⺻ ������/�Ҹ���
	������ ����/�̵� ����

�ܼ��� struct �� ���ǻ� ������ ������ ���Ǵ� Ÿ���̶� ���� �ȴ�.
*/

//#include <iostream>
//#include <vector>
//#include <fstream>
//#include "Monster.h"
//struct Header
//{
//	int version{ 1 };
//	int itemCount{};
//};
//bool SaveToFile(const char* filename, std::vector<Monster>& monsters)	// ��ü���� ���͸� ���� ���Ͽ� ����
//{
//	std::ofstream ostream;
//	ostream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
//	try
//	{
//		// ���� ���� ������ ����. �� �ɼ��� ����ϸ� ���Ͽ��� �����͸� ���� �������� �аų� �� �� �ִ�.
//		ostream.open(filename, std::ofstream::binary);
//
//		// Header �����ʹ� POD �̹Ƿ� �� ���� �б�/���Ⱑ �����ϴ�. write�� read�� char* �� �Ű������� �޾Ƶ��̱� ������,
//		// &header �� header ����ü�� �ּҸ� char* �� �����ϴ� ���̴�.
//		Header header{ 1,static_cast<int>(monsters.size()) };
//		// reinterpret_cast�� ����Ͽ� Header ����ü�� �����͸� char* �����ͷ� ����ȯ 
//		// �̷��� �ϸ� ����ü�� �޸� ���̾ƿ��� �״�� ���� �����ͷ� �� �� �ִ�.
//		// ���̳ʸ� �����͸� ���� �Ǵ� ��Ʈ���� �� �� ���Ǵ� �Լ�
//		ostream.write(reinterpret_cast<char*>(&header), sizeof(Header));
//
//		for (auto item : monsters)
//		{
//			ostream << item;
//		}
//		ostream.close();
//	}
//	catch (std::ofstream::failure e)
//	{
//		std::cerr << "���� ���� �߿� ���ܰ� �߻��߽��ϴ�\n" <<
//			e.what() << '\n';
//		ostream.close();
//		return false;
//	}
//	return true;
//}
//bool LoadFromFile(const char* filename, std::vector<Monster>& monsters)	// ���� ���Ͽ��� �����͸� �о�� Monster ��ü���� std::vector�� �ε�
//{
//	std::ifstream istream;
//	istream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//	try
//	{
//		// ������ ����(binary) ���� ����. �̷��� ���� ������ ������ ���̳ʸ� �����ͷ� �ٷ��, 
//		// �ؽ�Ʈ �����ͳ� Ư�� ���ڸ� �ٷ� �� �ڵ����� ��ȯ���� �ʴ´�. 
//		// ���� ���� ������ �� �� �����͸� ��Ȯ�� �״�� �а� ���� �ȴ�.
//		istream.open(filename, std::ifstream::binary);
//
//		// ���̳ʸ� ���Ϸκ��� �����͸� �о�´�. �̶� Header ����ü�� ũ��(sizeof(Header))��ŭ �����͸� �о�´�.
//		// �о�� ���� �����͸� Header ����ü �������� �ؼ�, ���Ͽ��� ���� �����͸� Header ��ü�� �����Ѵ�.
//		Header header;
//		istream.read(reinterpret_cast<char*>(&header), sizeof(Header));
//
//		for (int i = 0; i < header.itemCount; i++)
//		{
//			Monster monster;
//			istream >> monster;
//			monsters.push_back(monster);
//		}
//		istream.close();
//	}
//	catch (std::ifstream::failure e)
//	{
//		std::cerr << "���� ���� �߿� ���ܰ� �߻��߽��ϴ�.\n" << e.what() << '\n';
//		istream.close();
//		return false;
//	}
//	return true;
//}
//int main()
//{
//	std::vector<Monster> monsterList;
//	monsterList.push_back(Monster{ "JELLY",1,1,1 });
//	monsterList.push_back(Monster{ "WOLF",5,5,5 });
//	monsterList.push_back(Monster{ "DEMON",10,10,10 });
//	SaveToFile("Data/SimpleData.dat", monsterList);
//	monsterList.clear();
//	LoadFromFile("Data/SimpleData.dat", monsterList);
//}

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <regex>
//#include <vector>	// ���� �����, ���ڿ�, ���� �����̳ʸ� ���� ����� ����
//
//// ���ڿ� �Ľ����� ������ �ļ�( Parser )�� ������ ����
//// "<sprite"�� �����ϴ� element �� �����ͷ� �����.
//
//class Sprite
//{
//public:
//	std::string n;
//	int			x;
//	int			y;
//	int			w;
//	int			h;
//// ������ ������ �����ϱ� ���� Sprite Ŭ����
//};

/*
std::regex_iterator
	���� ǥ���� Ž�� ������� ���Ҹ� Ž���� ���ͷ������̴�. Ž�� ����� ����, ���ڿ�, �����ڵ忡 ���� ������ ���� �̸��� ����Ѵ�.
	char : regex_iterator
	std::string : sregex_iterator
	std::wstring : wsregex_iterator
�����ڸ� ���� �˻��� �����̳�( ����, ���� ) �� ������ �Ѱܼ� �˻� ����� ���� ù ��° ���ͷ����͸� ������ �� �ִ�.
ã�ƿ� ���( ���ͷ����� )�� [0]�� ���� ���ڿ�, [1]���� ���Ͽ� �´� ���ڿ��� ��� �ִ�.
*/

/*
�ڵ��� �帧

	���� ����

	���� ����( std::regex )

	���� ������ �ݺ�
		�� �� �о����
		�������� ���ͷ����͸� ����( std::regex_iterator )
		���ͷ����͸� ������Ű�鼭 Ž��
			�Ӽ��� ó��
*/

//void LoadXML(const char* filename, std::vector<Sprite>& sprites)
//{
//	// 1. ���͸� �ʱ�ȭ �Ͽ� ���� �����͸� ��� ���� �Ѵ�.
//	sprites.clear();
//
//	// 2. filename ��ο� �ִ� ������ ���̳ʸ� ���� �б� ���� std::ifstream ��ü�� ����
//	std::ifstream file(filename, std::ifstream::binary);
//	// 3. ���Ͽ��� �� �پ� �о�� ���ڿ� line�� ����
//	std::string line;
//	// 4. "<sprite" ���ڿ��� ã�� ���� ���� ǥ���� ������ ����, 
//	//		=> �� ������ <sprite ������ ������� �Ӽ����� ����
//	std::regex pattern("\"([^\"]*)\"");
//
//	// 5. ������ ���� ���� ������ �ݺ�
//	while (!file.eof())
//	{
//		// 6. ���Ͽ��� �� ���� �о line ���ڿ��� ����
//		std::getline(file, line);
//		// 7. ���� ���� ��( line )���� <sprite ���ڿ��� �ִ��� �˻��ϰ�, ��ġ�� result�� ����
//		auto result = line.find("<sprite");
//		// 8. <sprite ���ڿ��� �߰ߵǸ� �Ʒ� �ڵ� ����� ����ȴ�.
//		if (result != std::string::npos)
//		{
//			// 9. ���� ��( line )���� ���� ǥ���� ���Ͽ� �´� �κ��� ã�� ���� ���ͷ����� current�� ����
//			//		=> pattern�� <sprite ������ ������� �Ӽ����� ã�� ����
//			std::sregex_iterator current(line.begin(), line.end(), pattern);
//			// 10. ���ͷ������� ���� ��Ÿ���� end�� ����
//			std::sregex_iterator end;
//			// 11. ���� ó�� ���� �Ӽ��� �ε����� ��Ÿ���� ���� index
//			int index{ 0 };
//			// 12. �����͸� ������ Sprite ��ü ����
//			Sprite sprite;
//
//			// 13. ���� ǥ���Ŀ� �´� �����͸� ã�� ����
//			while (current != end)
//			{
//				// 14. ���� ���ͷ����� current�� ����Ű�� ���� ǥ���� ���Ͽ� �´� ���ڿ��� �����Ͽ� token�� ���� 
//				//		=> [1]�� ���� ǥ���Ŀ��� ù ��° ĸó �׷��� �ǹ�, �̰��� ���Ͽ��� "( )" ������ ���ڿ��� ����
//				std::string token = (*current)[1];
//				switch (index)
//				{
//				case 0:
//					// "n = �̸�"
//					sprite.n = token;
//					break;
//				case 1:
//					// "x = ��ġX"
//					sprite.x = std::stoi(token);
//					break;
//				case 2:
//					//"y = ��ġY"
//					sprite.y = std::stoi(token);
//					break;
//				case 3:
//					// "w = �ʺ�"
//					sprite.w = std::stoi(token);
//					break;
//				case 4:
//					// "h = ����"
//					sprite.h = std::stoi(token);
//					break;
//				}
//				// 15. �Ӽ� �ε����� ����, ���ͷ����͸� �������� �̵�
//				index++;
//				current++;
//			}
//			// 16. <sprite> ��Ұ� ��� �Ӽ��� �����ϰ� �ִٸ� index�� 4
//			if (index > 4)
//			{
//				// 17. <sprite> ����� ��� �Ӽ��� sprite ��ü�� ������ ��, �� ��ü�� sprites ���Ϳ� �߰�
//				sprites.push_back(sprite);
//			}
//		}
//	}
//}
//int main()
//{
//	std::vector<Sprite> mySprites;
//
//	LoadXML("mydata.xml", mySprites);
//
//	for (auto e : mySprites)
//	{
//		std::cout <<
//			e.n << " : " <<
//			e.x << ", " << e.y << ", " <<
//			e.w << ", " << e.h << '\n';
//	}
//}