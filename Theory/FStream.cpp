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
//public:
//	Monster() : mName{}, mLevel{}, mHP{}, mMP{} {}
//	Monster(std::string name, int level, int hp, int mp) :
//		mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp } {}
//	// 선언에서는 friend 키워드를 사용하여 친구 함수로 선언해 줬다.
//	friend std::istream& operator >>(std::istream& inputStream, Monster& monster);
//	friend std::ostream& operator <<(std::ostream& ostream, Monster& monster);
//};
//std::istream& operator >>(std::istream& inputStream, Monster& monster)
//{
//	std::string buffer;
//	try
//	{	// 각 멤버들을 하나씩 가져온다.
//		std::getline(inputStream, buffer, ',');
//		monster.mName = buffer;
//		std::getline(inputStream, buffer, ',');
//		monster.mLevel = std::stoi(buffer);
//		std::getline(inputStream, buffer, ',');
//		monster.mHP = std::stoi(buffer);
//		std::getline(inputStream, buffer);
//		monster.mMP = std::stoi(buffer);
//	}
//	catch (std::exception e)
//	{
//		std::cerr << "데이터 형식이 잘못 되었다.\n";
//	}
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

