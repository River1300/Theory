/* ----- < 입출력 스트림 > ----- */

// 컴퓨터는 입력 -> 계산 -> 출력 으로 작업한다.

/*
스트림의 필요성

가령 출력이 한 번에 처리할 수 있는 것이 초당 1 바이트라고 가정해 보자. 그런데 한 번에 입력이 100 바이트 들어왔다면?
그럼 다음 입력을 처리하기 위해 100 초 동안은 출력만 하고 있어야 한다.
최악의 경우에는 1초에 입력받은 100 바이트를 출력하는 100 초 동안 프로그램이 멈춰 있을 수 있다.

이러한 증상을 병목현상( BottleNeck )이라 부른다.
*/

// 스트리밍( 또는 버퍼링 )은 이러한 병목현상을 완화하기 위한 아이디어로, 최소한 프로그램이 멈추는 것을 피하자는 해결책이다.

/*
'a'
"Mu Data"  => Stream => buffer => 출력
123
*/

// 많은 데이터가 몰리면, 해당 데이터들은 스트림에서 버퍼로 조금씩 꺼내지고 출력으로 전달되는 방식이다.
// 그러면 입력은 값이 누적되지 않고 안정적으로 받을 수 있게 되고 출력도 막힘없이 꺼내 갈 수 있다.
// 그러나, 당연하게 버퍼는 커지게 된다.

/*
							ios_base

							  ios
				ostream					istream
	ostringstream	ofstream	ostringstream	ofstream

ios 와 ios_base 는 모든 입출력 스트림의 기초가 되는 클래스로 중요한 !, bool 연산자를 포함해 데이터 타입과 상관없이 기본적인 처리를
담당하고 있다. 이를 상속 받아 각각 입력/출력으로 구분되며, 다시 문자열/파일 로 구분되어 파생되어 있다.
이런 구조적인 설계로 인해 cout, cin 을 사용하듯 모든 스트림에 적용 가능하다는 장점이 있다.
*/

/* ----- < 파일처리 > ----- */

// 일반적으로 컴퓨터의 메모리( 1차 기억장치 )는 용량이 적기 때문에, 더 큰 데이터들은 메모리 보다 용량이 큰 보조 기억 장치에 저장한다.
// 하드 디스크( HDD )가 이에 속하며, 다음과 같은 특징을 가지고 있다.
//		1. 비 휘발성 : 전원을 꺼도 데이터가 남아 있다.
//		2. 순차접근 : 처음부터 순서대로 데이터에 접근

// 순차접근의 특성으로 인해 파일을 디스크에 저장하면 바이트의 배열처럼 할당된다.
// 메모리에 할당된 바이트 공간과 마찬가지로 이러한 파일을 해석하려면 어떠한 형시인지가 중요하다.
// 가령 텍스트 형식이면 각 바이트는 한 글자의 문자가 되며, 이진 파일 형태라면 4바이트가 정수값 하나를 나타내는 것이 된다.

/*
파일을 읽어서 화면에 출력

1. 프로젝트 생성
2. 읽을 파일이 하나 필요하니 메모장에 다음과 같이 작성한다.
	{
		--- MONSTER DATA ---
		JELLY,1,1,1
		WOLF,5,5,5
		DEMON,10,10,10
	}
3. 새로 만든 프로젝트에 Data 라는 폴더를 만들고 그 안에 텍스트 파일을 저장한다.
4. main.cpp 를 생성한다.

크게 파일 스트림을 사용하는 과정은 다음과 같다.
	1. 파일 스트림 객체 생성
		읽기/쓰기 모드를 지정하여 객체를 생성한다.
		생성자에서 파일을 지정하거나, 빈 객체를 생성한 후 open() 멤버 함수로 열 수 있다.
	2. 파일 작업
		스트림 객체에서 데이터를 꺼내오거나 집어 넣는다.
	3. 파일 닫기
		close() 멤버 함수를 호출한다. 파일을 닫아두지 않으면 해당 파일을 다시 열 수 없다.
*/

//#include <iostream>
//#include <fstream>	// 파일과 관련된 입출력스트림은 fstream에 정의 되어 있다.
//bool LoadFile(const char* filename)
//{
//	std::ifstream ist(filename); // ifstream 인스턴스를 생성한다.
//	if (!ist)
//	{
//		std::cerr << filename << " 파일을 찾을 수 없습니다.\n";
//		return false;
//	}
//	// 정상적으로 스트립 객체를 생성하고 나면 해당 파일을 열어 두고, 내부에서 위치를 파일 가장 처음으로 맞추고 읽을 준비를 한다.
//	// 문자를 하나씩 꺼내온다.
//	// >> 연산자 : 각 객체의 타입에 맞게 자동으로 데이터를 가져온다.
//	// get() 멤버함수 : 입력으로 부터 가공하지 않은 데이터를 가져온다.
//	char ch;
//	while (ist >> ch)
//	{
//		std::cout << ch;
//	}
//
//	ist.close();	// 모든 작업이 끝나면 close 를 통해 파일을 닫아 준다.
//	return true;
//}
//int main()
//{
//	// 파일 경로는 C:/dir1/dir2 와 같은 방식으로 드라이브 부터 출발한다.
//	// 다만, 생략할 경우 디렉터리에서 부터 검색한다. 현재 디렉터리라고 하는 것은 실행파일이 실행되는 위치를 의미하는 것을로
//	// 개발 중에는 프로젝트 파일이 존재하는 디렉터리가 현재 디렉터리가 된다.
//	LoadFile("Data/SimpleData.txt");
//}

/* 에러 체크 */

// 파일 스트림 객체는 마지막으로 수행한 파일 처리에 대한 결과를 항상 내부에서 오류 상태 플래그( error state flag )로 기록해 둔다.
// 이러한 상태 플래그는 다음과 같은 멤버 함수로 확인 가능하다.

/*
good() : 연산 성공
fail() : 예상치 못한 처리( 정수를 기대했으나 문자가 온다던가 )
eof() : 파일의 끝에 도착. 정확하게는 오류가 아닌 것으로 볼 수 있다.
bad() : 심각한 오류( 파일 손상 등 )
rdstate() : read error state flag 의 약자로 오류 상태 플래그 모두 가져 온다.
*/

//#include <iostream>
//#include <fstream>
//bool LoadFile(const char* filename)
//{
//	std::ifstream ist(filename);
//	if (!ist)
//	{
//		std::cerr << filename << " 파일을 찾을 수 없습니다.\n";
//		return false;
//	}
//	char ch;
//	while (ist.get(ch))
//	{
//		if (!ist.bad())
//		{
//			std::cerr << "파일이 손상되었습니다.\n";
//			ist.close();
//			return false;
//		}
//		if (!ist.fail())
//		{
//			std::cerr << "잘못된 파일 포멧입니다.\n";
//			ist.close();
//			return false;
//		}
//		std::cout << ch;
//	}
//	ist.close();
//	return true;
//}

// 위와 같이 처음 파일을 연 후, 파일로 연산을 수행한 후 오류를 검사하는 것이 가장 일반적이다.
// iostream 에서는 exceptions() 라는 멤버 함수를 통해 조금 더 일반화된 예외처리를 수행할 수 있다.

//#include <iostream>
//#include <fstream>
//bool LoadFile(const char* filename)
//{
//	std::ifstream ist;
//	// exceptions 멤버 함수에 에러 상태 비트를 지정해 놓으면, 해당 에러가 발생했을 때 자동적으로 예외를 발생시켜 준다.
//	// 기존 소스와 다른 차이점은 예외 탐지를 위해 생성자는 기본 생성자를 사용했으며, open() 멤버 함수를 통해 직접 파일을 불러 줬다.
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
//		std::cerr << "파일 연산 도중 예외가 발생했습니다.\n" << e.what() << '\n';
//		ist.close();
//		return false;
//	}
//	return true;
//}

/* 파일 데이터 가공 */

// 파일 구조는 프로그래머가 직접 지정하는 경우가 대부분이다. 위 샘플데이터는 다음과 같은 몬스터 클래스를 기준으로 다양한 몬스터를 만들기 위한 테이블이다.

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
//			if (std::count(buffer.begin(), buffer.end(), ',') == 3)	// _Val 값을 찾아, 그 갯수가 3개일 경우
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
//					std::cerr << "몬스터 데이터 양식이 잘못되었다.\n";
//				}
//			}
//		}
//		ist.close();
//	}
//	catch (std::istream::failure e)
//	{
//		std::cerr << "파일 연산 도중 예외가 발생했다.\n" << e.what() << '\n';
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

/* 사용자 정의 연산자 */

//#include <iostream>
//#include <vector>
//
//#include <fstream>
///*
//<fstream> 헤더 파일은 파일 입출력(File In/Out) 관련 기능을 제공한다.
//ifstream( 파일 입력 스트림 ), ofstream( 파일 출력 스트림 ), 그리고 fstream( 파일 입출력 스트림 )이 있다.
//파일을 열고 닫고, 파일로부터 데이터를 읽고 쓰는 등의 파일 관련 작업을 수행할 때 사용된다.
//*/
//
//#include <sstream>
///*
//<sstream> 헤더 파일은 문자열 스트림을 다루는 기능을 제공한다.
//istringstream( 입력 문자열 스트림 ), ostringstream( 출력 문자열 스트림 ), 그리고 stringstream( 입출력 문자열 스트림 )이 있다.
//문자열을 스트림으로 변환하거나, 스트림에서 문자열을 추출하는 등의 문자열 처리 작업에 사용된다.
//일반적으로 문자열을 파싱하거나 특정 형식으로 포맷하는 데 사용된다.
//*/
//
//class Monster	// Monster 객체를 효과적으로 생성하고 파일 입출력에서 사용하기 위해 만들어진 Class
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
//	// 선언에서는 friend 키워드를 사용하여 친구 함수로 선언해 줬다.
//	friend std::istream& operator >>(std::istream& inputStream, Monster& monster);
//	friend std::ostream& operator <<(std::ostream& ostream, Monster& monster);
//// 클래스는 특별한 데이터 형식, 예를 들어 CSV 형식, 텍스트 형식, 또는 사용자 지정 형식에 대한 
//// 데이터를 처리하도록 설계될 수 있다. 이 클래스를 사용하면 데이터를 읽고 쓰는 데 일관된 형식을 적용할 수 있다.
//};
//std::istream& operator >>(std::istream& inputStream, Monster& monster)
//{
//	std::string buffer;
//	try
//	{	// 스트림에서 문자열을 ','로 구분하여 읽어와서 각 멤버 변수에 할당한다.
//
//		// 1. 몬스터 이름을 스트림에서 읽어온다.
//		std::getline(inputStream, buffer, ',');
//		monster.mName = buffer;
//		// 2. 몬스터 레벨을 스트림에서 읽어온다.
//		std::getline(inputStream, buffer, ',');
//		monster.mLevel = std::stoi(buffer);
//		// 3. 몬스터 체력을 스트림에서 읽어온다.
//		std::getline(inputStream, buffer, ',');
//		monster.mHP = std::stoi(buffer);
//		// 4. 몬스터 마나를 스트림에서 읽어온다.
//		std::getline(inputStream, buffer);
//		monster.mMP = std::stoi(buffer);
//	}
//	catch (std::exception e)
//	{
//		std::cerr << "데이터 형식이 잘못 되었다.\n";
//	}
//
//	// 스트림을 반환한다. 이러면 연속된 입력 작업이 가능하다.
//	return inputStream;
//}
//std::ostream& operator <<(std::ostream& ostream, Monster& monster)
//{
//	try
//	{	// 각 멤버를 스트림으로 보내면서 쉼표를 끼워주면 된다.
//		ostream << monster.mName << ','
//			<< monster.mLevel << ','
//			<< monster.mHP << ','
//			<< monster.mMP << '\n';
//		// 이런 데이터를 쉼표로 구분되어 있다고 하여 CSV( Comma Seperated Values )라고 하며, 기획자들의 친구 엑셀에서
//		// 데이터를 옮기는 가장 쉬운 방법이다. 따라서 밸런스 테이블이나 아이템 테이블이 라 부르는 테이블 데이터들은 csv로
//		// 처리하면 아주 쉽고 간단하게 처리할 수 있다.
//	}
//	catch (std::exception e)
//	{
//		std::cerr << "스트림에 쓸 때 오류가 발생했습니다.\n";
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
//		{	// 스트림에서 getline() 을 해서 아무런 문자를 못 읽어 오면 예외가 발생한다.
//			// peek() 멤버 함수는 실제로 스트림에서 값을 가져오지는 않으면서 살짝 옅보는 역할을 한다.
//			// 문자 하나를 옅본 후 그 문자가 EOF( end of file )이면 아무런 데이터가 없다는 것이니 무시하면 된다.
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
//		std::cerr << "파일 연산 도중 예외가 발생했습니다.\n" << e.what() << '\n';
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

/* ----- < 바이너리 데이터 > ----- */

// 보안에서 가장 쉽게 처리하는 것이 바이너리 데이터이다. 이 데이터는 컴퓨터 메모리에 저장되어 있는 그대로 파일로 기록하는 것이며
// 이러한 방식이 바이너리 모드이다. 위에서 언급한 대로 스트림 객체를 만들 때 모드를 binary로 지정해 주면 된다.

/* 바이너리 데이터 읽기/쓰기 */

// 바이너리 데이터를 읽거나 쓰기 위해서는 char* 로 변환을 하는 것이 기본이다. 즉, 데이터를 char 배열로 만들어 바이트의 집합으로 사용하는 것이다.

/*
바이너리 데이터에 대한 멤버 함수

ostream& ostream::write( char* s, streamsize n ); s가 가르키는 문자 배열의 n개를 스트림에 기록한다.
istream& istream::read( char* s, streamsize n ); s가 가르키는 문자 배열에 스트림에서 n개의 값을 읽어 온다.

바이너리 모드에서 작업할 때는 주의해야 할 것이 있다.
마지막 줄 엔터를 만날 때 까지가 데이터 집합이라는 것을 명확히 알 수 있다. 하지만 바이너리 데이터는 단순히 바이너리 집합으로만
되어 있기 때문에 데이터 집합이 어디 까지인지 알 수 없다. 각 집합에 대한 구분자로 특별한 기호를 사용할 수는 있겠지만,
항목이 많아지면 당연히 부담이 된다.
따라서 파일 가장 앞부분에 현재 데이터가 몇 개인지 저장해 두는 것이 좋다. 이러한 것들을 가장 앞의 데이터라고 해서 header라고
많이 부른다. 파일 헤더는 주로 원소의 개수, 해당 파일의 관리를 위해 버전을 명시하는 것이 일반적이다.
*/

/*
바이너리 문자열 저장/읽기

JELLY 는 5글자이지만 WOLF 는 4글자 이다. 텍스트는 쉼표로 구분되어 읽을 수 있었지만 바이너리는 구분자가 없다. 따라서 문자열을
저장할 때는 문자열의 길이를 같이 저장하는 것이 일반적이다.
*/

//struct Header
//{
//	int version{ 1 };
//	int itemCount{};
//};

// 이러한 것을 데이터 구조상 POD( Plain Old Data )라 하며, 객체가 아닌 단순한 값의 집합으로 된 데이터 구조이다.
// 위와 같은 형태는 메모리 상에서 연속적인 바이트 배열로 표기할 수 있기 때문에 한 묶음( chunk )으로 입출력이 가능하다.

/*
POD의 특성

표준 레이아웃 타입 : 객체 지향의 특성을 가지지 않는다.
	다형성이 아니다. ( 가상 함수 및 가상 기반 클래스 )
	참조형 멤버가 없다.
	멤버가 동일한 접근 제어자를 가진다.
간단한 타입 : 비트 단위 연산이 가능한 단순한 타입이다.
	간단한 기본 생성자/소멸자
	간단한 복사/이동 연산

단순히 struct 에 편의상 생성자 정도만 허용되는 타입이라 보면 된다.
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
//bool SaveToFile(const char* filename, std::vector<Monster>& monsters)	// 객체들의 벡터를 이진 파일에 저장
//{
//	std::ofstream ostream;
//	ostream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
//	try
//	{
//		// 이진 모드로 파일을 연다. 이 옵션을 사용하면 파일에서 데이터를 이진 형식으로 읽거나 쓸 수 있다.
//		ostream.open(filename, std::ofstream::binary);
//
//		// Header 데이터는 POD 이므로 한 번에 읽기/쓰기가 가능하다. write나 read는 char* 를 매개변수로 받아들이기 때문에,
//		// &header 즉 header 구조체의 주소를 char* 로 변경하는 것이다.
//		Header header{ 1,static_cast<int>(monsters.size()) };
//		// reinterpret_cast를 사용하여 Header 구조체의 포인터를 char* 포인터로 형변환 
//		// 이렇게 하면 구조체의 메모리 레이아웃을 그대로 이진 데이터로 쓸 수 있다.
//		// 바이너리 데이터를 파일 또는 스트림에 쓸 때 사용되는 함수
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
//		std::cerr << "파일 저장 중에 예외가 발생했습니다\n" <<
//			e.what() << '\n';
//		ostream.close();
//		return false;
//	}
//	return true;
//}
//bool LoadFromFile(const char* filename, std::vector<Monster>& monsters)	// 이진 파일에서 데이터를 읽어와 Monster 객체들을 std::vector에 로드
//{
//	std::ifstream istream;
//	istream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//	try
//	{
//		// 파일을 이진(binary) 모드로 연다. 이렇게 열면 파일의 내용을 바이너리 데이터로 다루며, 
//		// 텍스트 데이터나 특수 문자를 다룰 때 자동으로 변환하지 않는다. 
//		// 이진 모드로 파일을 열 때 데이터를 정확히 그대로 읽고 쓰게 된다.
//		istream.open(filename, std::ifstream::binary);
//
//		// 바이너리 파일로부터 데이터를 읽어온다. 이때 Header 구조체의 크기(sizeof(Header))만큼 데이터를 읽어온다.
//		// 읽어온 이진 데이터를 Header 구조체 형식으로 해석, 파일에서 읽은 데이터를 Header 객체에 저장한다.
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
//		std::cerr << "파일 저장 중에 예외가 발생했습니다.\n" << e.what() << '\n';
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
//#include <vector>	// 파일 입출력, 문자열, 벡터 컨테이너를 위한 헤더를 포함
//
//// 문자열 파싱으로 간단한 파서( Parser )를 제작해 보자
//// "<sprite"로 시작하는 element 를 데이터로 만든다.
//
//class Sprite
//{
//public:
//	std::string n;
//	int			x;
//	int			y;
//	int			w;
//	int			h;
//// 데이터 구조를 저장하기 위한 Sprite 클래스
//};

/*
std::regex_iterator
	정규 표현식 탐색 결과들의 원소를 탐색할 이터레이터이다. 탐색 결과가 문자, 문자열, 유니코드에 따라 다음과 같은 이름을 사용한다.
	char : regex_iterator
	std::string : sregex_iterator
	std::wstring : wsregex_iterator
생성자를 통해 검색할 컨테이너( 시작, 종료 ) 와 패턴을 넘겨서 검색 결과에 대한 첫 번째 이터레이터를 가져올 수 있다.
찾아온 결과( 이터레이터 )는 [0]에 원본 문자열, [1]에는 패턴에 맞는 문자열이 들어 있다.
*/

/*
코드의 흐름

	파일 열기

	패턴 생성( std::regex )

	파일 끝까지 반복
		한 줄 읽어오기
		패턴으로 이터레이터를 생성( std::regex_iterator )
		이터레이터를 증가시키면서 탐색
			속성값 처리
*/

//void LoadXML(const char* filename, std::vector<Sprite>& sprites)
//{
//	// 1. 벡터를 초기화 하여 기존 데이터를 모두 제거 한다.
//	sprites.clear();
//
//	// 2. filename 경로에 있는 파일을 바이너리 모드로 읽기 위해 std::ifstream 객체를 생성
//	std::ifstream file(filename, std::ifstream::binary);
//	// 3. 파일에서 한 줄씩 읽어올 문자열 line을 선언
//	std::string line;
//	// 4. "<sprite" 문자열을 찾기 위한 정규 표현식 패턴을 정의, 
//	//		=> 이 패턴은 <sprite 다음에 따라오는 속성값을 추출
//	std::regex pattern("\"([^\"]*)\"");
//
//	// 5. 파일을 끝을 읽을 때까지 반복
//	while (!file.eof())
//	{
//		// 6. 파일에서 한 줄을 읽어서 line 문자열에 저장
//		std::getline(file, line);
//		// 7. 현재 읽은 줄( line )에서 <sprite 문자열이 있는지 검사하고, 위치를 result에 저장
//		auto result = line.find("<sprite");
//		// 8. <sprite 문자열이 발견되면 아래 코드 블록이 실행된다.
//		if (result != std::string::npos)
//		{
//			// 9. 현재 줄( line )에서 정규 표현식 패턴에 맞는 부분을 찾기 위한 이터레이터 current를 생성
//			//		=> pattern은 <sprite 다음에 따라오는 속성값을 찾는 패턴
//			std::sregex_iterator current(line.begin(), line.end(), pattern);
//			// 10. 이터레이터의 끝을 나타내는 end를 생성
//			std::sregex_iterator end;
//			// 11. 현재 처리 중인 속성의 인덱스를 나타내는 변수 index
//			int index{ 0 };
//			// 12. 데이터를 저장할 Sprite 객체 생성
//			Sprite sprite;
//
//			// 13. 정규 표현식에 맞는 데이터를 찾는 동안
//			while (current != end)
//			{
//				// 14. 현재 이터레이터 current가 가리키는 정규 표현식 패턴에 맞는 문자열을 추출하여 token에 저장 
//				//		=> [1]은 정규 표현식에서 첫 번째 캡처 그룹을 의미, 이것은 패턴에서 "( )" 사이의 문자열을 추출
//				std::string token = (*current)[1];
//				switch (index)
//				{
//				case 0:
//					// "n = 이름"
//					sprite.n = token;
//					break;
//				case 1:
//					// "x = 위치X"
//					sprite.x = std::stoi(token);
//					break;
//				case 2:
//					//"y = 위치Y"
//					sprite.y = std::stoi(token);
//					break;
//				case 3:
//					// "w = 너비"
//					sprite.w = std::stoi(token);
//					break;
//				case 4:
//					// "h = 높이"
//					sprite.h = std::stoi(token);
//					break;
//				}
//				// 15. 속성 인덱스를 증가, 이터레이터를 다음으로 이동
//				index++;
//				current++;
//			}
//			// 16. <sprite> 요소가 모든 속성을 포함하고 있다면 index는 4
//			if (index > 4)
//			{
//				// 17. <sprite> 요소의 모든 속성을 sprite 객체에 저장한 후, 이 객체를 sprites 벡터에 추가
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

//#include "Monster.h"
//#include "tinyxml2.h"
//
//using namespace tinyxml2;
//
//bool SaveToXML(const char* filename, const std::vector<Monster>& monsters);
//bool LoadFromXML(const char* filename, std::vector<Monster>& monsters);
//
//int main()
//{
//	std::vector<Monster> monsters;
//
//	Monster monster;
//	monster.SetName("슬라임");
//	monster.SetStatus(Status{ 1,1,1 });
//	monster.AddDropItem(Item{ "끈적한 젤리", 1 });
//	monsters.push_back(monster);
//	monster.GetDropItems().clear();
//
//	monster.SetName("늑대인간");
//	monster.SetStatus(Status{ 5,5,5 });
//	monster.AddDropItem(Item{ "발톱", 2 });
//	monster.AddDropItem(Item{ "늑대가죽", 5 });
//	monsters.push_back(monster);
//	monster.GetDropItems().clear();
//
//	monster.SetName("악마");
//	monster.SetStatus(Status{ 10,10,10 });
//	monster.AddDropItem(Item{ "날개", 10 });
//	monster.AddDropItem(Item{ "손톱", 5 });
//	monsters.push_back(monster);
//
//	SaveToXML("Data/monsters.xml", monsters);
//	monsters.clear();
//	LoadFromXML("Data/monsters.xml", monsters);
//}
//
//bool SaveToXML(const char* filename, const std::vector<Monster>& monsters)
//{
//	// 1. XML 문서를 관리하는 인스턴스 Document 를 생성
//	XMLDocument doc;
//
//	// 2. 선언부를 만든다.
//	//	=> 주의할 점은 인코딩을 EUC-KR 로 지정해야 한다.
//	XMLDeclaration* decl = doc.NewDeclaration(
//		R"(xml version="1.0" encoding="EUC-KR")"
//	);
//	// 3. 선언부를 doc( 문서 관리자 )에 붙인다.
//	//	=> 이런 식으로 만들어진 항목들은 doc 에 붙여 줘야 XML 형식을 갖추게 된다.
//	doc.LinkEndChild(decl);
//
//	// 4. monster는 monster -> monster -> status -> item 구조로 되어 있다.
//	//	=> 가장 최산단 노드( 루트 )는 monsters 이다.
//	//	=> 새로운 원소는 무조건 Document 를 통해서만 생성이 가능하다.
//	XMLElement* pRootNode = doc.NewElement("monsters");
//
//	for (auto monster : monsters)
//	{
//		// 5. monster 노드를 생성하고 속성값을 만든다. 
//		//	=> SetAttribute 멤버 함수는 속성의 이름과 const char*, int, bool, float 등 다양한 타입의 값을 매개변수로 처리할 수 있다.
//		//	=> 부모/자식 관계를 고려해서 노드를 생성하고 속성을 지정한다.
//		auto pMonsterNode = doc.NewElement("monster");
//		pMonsterNode->SetAttribute("name", monster.GetName().c_str());
//
//		auto pStatusNode = doc.NewElement("status");
//		Status status = monster.GetStatus();
//		pStatusNode->SetAttribute("level", status.mLevel);
//		pStatusNode->SetAttribute("hp", status.mHP);
//		pStatusNode->SetAttribute("mp", status.mMP);
//		pMonsterNode->LinkEndChild(pStatusNode);
//
//		auto pItemsNode = doc.NewElement("items");
//		for (auto item : monster.GetDropItems())
//		{
//			auto pItemNode = doc.NewElement("item");
//			pItemNode->SetAttribute("name", item.mName.c_str());
//			pItemNode->SetAttribute("gold", item.mGold);
//			pItemNode->LinkEndChild(pItemNode);
//		}
//		pMonsterNode->LinkEndChild(pItemsNode);
//		pRootNode->LinkEndChild(pMonsterNode);
//	}
//	doc.LinkEndChild(pRootNode);
//	// 6. Document 의 멤버 함수 SaveFile 을 사용하면 파일로 저장할 수 있다.
//	//	=> 파일 처리 중에 예외가 발생하면 반환값으로 알려 준다. 
//	//	=> 잘못된 속성 값 등 XML 포멧에 대한 오류 및 파일 오류까지 모두 반환한다.
//	return (doc.SaveFile(filename) == XML_SUCCESS);
//}
//bool LoadFromXML(const char* filename, std::vector<Monster>& monsters)
//{
//	XMLDocument doc;
//
//	// 1. XML 파일을 불러온다. SaveFile 과 마찬가지로 성공하면 XML_SUCCESS 를 반환한다.
//	if (doc.LoadFile(filename) != XML_SUCCESS)
//	{
//		return false;
//	}
//
//	// 2. Document 에서 tag 가 "monsters" 인 가장 첫번째 자식 원소를 찾아 온다.
//	auto pRootNode = doc.FirstChildElement("monsters");
//	// 3. 현재 노드의 모든 자식 노드를 탐색
//	for (auto pMonsterNode = pRootNode->FirstChildElement();
//		pMonsterNode;
//		pMonsterNode = pMonsterNode->NextSiblingElement())
//	{
//		Monster monster;
//
//		monster.SetName(pMonsterNode->Attribute("name"));
//
//		auto pStatusNode = pMonsterNode->FirstChildElement("status");
//		Status status;
//		status.mLevel = pStatusNode->IntAttribute("level");
//		status.mHP = pStatusNode->IntAttribute("hp");
//		status.mMP = pStatusNode->IntAttribute("mp");
//		monster.SetStatus(status);
//
//		auto pItemsNode = pMonsterNode->FirstChildElement("items");
//		for (auto pItemNode = pItemsNode->FirstChildElement();
//			pItemNode;
//			pItemNode = pItemNode->NextSiblingElement())
//		{
//			Item item;
//			item.mName = pItemNode->Attribute("name");
//			item.mGold = pItemNode->IntAttribute("gold");
//			monster.AddDropItem(item);
//		}
//		monsters.push_back(monster);
//	}
//	return true;
//}

//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "Monster.h"
//#include <rapidjson/document.h>
//#include <rapidjson/prettywriter.h>
//
//using namespace rapidjson;
//
//bool SaveToJson(const char* filename, const std::vector<Monster>& monsters);
//bool LoadFromJson(const char* filename, std::vector<Monster>& monsters);
//
//int main()
//{
//	std::vector<Monster> monsters;
//
//	Monster monster;
//	monster.SetName("슬라임");
//	monster.SetStatus(Status{ 1,1,1 });
//	monster.AddDropItem(Item{ "끈적한 젤리", 1 });
//	monsters.push_back(monster);
//	monster.GetDropItems().clear();
//
//	monster.SetName("늑대인간");
//	monster.SetStatus(Status{ 5,5,5 });
//	monster.AddDropItem(Item{ "발톱", 2 });
//	monster.AddDropItem(Item{ "늑대가죽", 5 });
//	monsters.push_back(monster);
//	monster.GetDropItems().clear();
//
//	monster.SetName("악마");
//	monster.SetStatus(Status{ 10,10,10 });
//	monster.AddDropItem(Item{ "날개", 10 });
//	monster.AddDropItem(Item{ "손톱", 5 });
//	monsters.push_back(monster);
//
//	SaveToJson("Data/monsters.json", monsters);
//	monsters.clear();
//	LoadFromJson("Data/monsters.json", monsters);
//}
//
//bool SaveToJson(const char* filename, const std::vector<Monster>& monsters)
//{
//	// 1. StringBuffer 는 rapidjson 에서 사용하는 독자적인 스트링 클래스다. JSON은 문자열 처리가 대부분이므로 최적화된 성능을
//	//	=> 발위하기 위해 C++의 string 이 아닌 자체 방식을 사용한다.
//	StringBuffer sb;
//	// 2. PrettyWriter 는 JSON 표기를 예쁘게 해주는 것으로 일반 Writer 는 단순히 한줄로 모두 나영하는 반면, PrettyWriter 는
//	//	=> 줄바꿈, 들여쓰기 표기를 해준다. 보통 네트워크로 전송하거나 할 때는 일반 Writer로 데이터양을 줄여서 사용하고,
//	//	=> 파일로 저장할 때는 PrettyWriter 를 사용한다.
//	//	=> Writer 계열은 스트림 방식으로 StringBuffer, FileReadStream, FileWriteStream 등을 템플릿 매개 변수로 받아서 처리한다.
//	//	=> 역시 최적화를 위해 C++의 iostream 은 사용을 피하고 있다.
//	PrettyWriter<StringBuffer> writer(sb);
//
//	// 3. 오브젝트의 시작과 끝을 기록한다. JSON 표기상 스트림에 각각 {,}기호를 출력한다고 보면 된다.
//	writer.StartObject();
//	// 4. 현재 오브젝트에 키를 기록한다. JSON 표기상 "monsters": 를 기록한다고 보면 된다.
//	//	=> 키 다음에는 Value( 값 )을 기록하면 되는데 Int(), String(), Double() 등의 일반 타입의 값이나 Object, Array 타입을 기록할 수 있다.
//	writer.Key("monsters");
//	writer.StartArray();
//	for (auto monster : monsters)
//	{
//		writer.StartObject();
//		{
//			writer.Key("name"); writer.String(monster.GetName().c_str());
//			writer.Key("status");
//			writer.StartObject();
//			{
//				Status status = monster.GetStatus();
//				writer.Key("level"); writer.Int(status.mLevel);
//				writer.Key("hp"); writer.Int(status.mHP);
//				writer.Key("mp"); writer.Int(status.mMP);
//			}
//			writer.EndObject();
//
//			writer.Key("items");
//			writer.StartArray();
//			{
//				for (auto item : monster.GetDropItems())
//				{
//					writer.StartObject();
//					{
//						writer.Key("name"); writer.String(item.mName.c_str());
//						writer.Key("gold"); writer.Int(item.mGold);
//						writer.EndObject();
//					}
//				}
//			}
//			writer.EndArray();
//		}
//		writer.EndObject();
//	}
//	writer.EndArray();
//	writer.EndObject();
//
//	std::ofstream ofs;
//	ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
//
//	try
//	{
//		ofs.open(filename);
//		// 5. StringBuffer 의 GetString() 멤버 함수를 사용하여 JSON 문자열의 C-Style 문자열 포인터를 가져와 스트림으로 보낸다.
//		ofs << sb.GetString();
//
//		ofs.close();
//	}
//	catch (std::ofstream::failure e)
//	{
//		std::cerr << "파일 저장 중에 예외가 발생했습니다.\n";
//		std::cerr << e.what();
//
//		ofs.close();
//
//		return false;
//	}
//
//	return true;
//}
//bool LoadFromJson(const char* filename, std::vector<Monster>& monsters)
//{
//	// 1. JSON 파일을 std::ifstream 문자열을 이용하여 std::stringstream 타입으로 읽어 온다.
//	//		=> rapidjson 에도 StringBuffer 나 StringStream 등이 존재하긴 하지만, 속도를 위해 매우 제한적인 기능만을
//	//		=> 제공하는 형태라서 C++ 의 iostream 과 같이 사용할 수 없다.
//	std::ifstream ifs;
//	ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//	std::stringstream ss;
//
//	try
//	{
//		ifs.open(filename);
//		ss << ifs.rdbuf();
//		ifs.close();
//	}
//	catch (std::ifstream::failure e)
//	{
//		std::cerr << "파일을 읽는 도중 예외가 발생했습니다.\n";
//		std::cerr << e.what();
//		ifs.close();
//		return false;
//	}
//
//	// 2. 읽어온 문자열을 사용해 Document( DOM 객체 )로 해석( Parse )한다.
//	//		=> Parse 멤버 함수는 인자로 C-Style 문자열을 받는다.
//	Document d;
//	d.Parse(ss.str().c_str());
//
//	// 3. 반복문으로 배열의 원소에 접근한다.
//	//		=> DOM 객체는 배열 첨자 표기법으로 원소를 직접 가져올 수 있다.
//	for (auto& e : d["monsters"].GetArray())
//	{
//		Monster monster;
//		monster.SetName(e["name"].GetString());
//		Status status;
//		status.mLevel = e["status"].GetObject()["level"].GetInt();
//		status.mHP = e["status"].GetObject()["hp"].GetInt();
//		status.mMP = e["status"].GetObject()["mp"].GetInt();
//		monster.SetStatus(status);
//
//		for (auto& e2 : e["items"].GetArray())
//		{
//			Item item;
//			item.mName = e2["name"].GetString();
//			item.mGold = e2["gold"].GetInt();
//			monster.AddDropItem(item);
//		}
//		monsters.push_back(monster);
//	}
//	return true;
//}