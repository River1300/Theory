#pragma once
#include <string>
#include <vector>

struct Status
{
	int mLevel{};
	int mHP{};
	int mMP{};
};
struct Item
{
	std::string mName{};
	int mGold{};
};
class Monster
{
private:
	std::string mName{};
	Status mStatus{};
	std::vector<Item> mDropItems{};

public:
	void SetName(const char* name) { mName = name; }
	void SetStatus(const Status& status) { mStatus = status; }
	void AddDropItem(const Item& item) { mDropItems.push_back(item); }
	std::string& GetName() { return mName; }
	Status& GetStatus() { return mStatus; }
	std::vector<Item>& GetDropItems() { return mDropItems; }

	//std::ifstream& ReadBinary(std::ifstream& istream);
	//std::ofstream& WriteBinary(std::ofstream& ostream);
};

//std::ifstream& Monster::ReadBinary(std::ifstream& istream)
//{
//	int strLen{};
//	// 문자열 길이를 읽은 후, 해당 길이만큼 문자열 크기를 조절한다.
//	// mName 은 std::string 이므로 배열 첨자[0]를 사용해 char* 형태로 변환한다.
//	// 읽을 때 c_str() 멤버 함수는 const 형이므로 사용할 수 없다.
//	istream.read(reinterpret_cast<char*>(&strLen), sizeof(int));
//	mName.resize(strLen);
//	istream.read(&mName[0], strLen);
//	istream.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
//	istream.read(reinterpret_cast<char*>(&mHP), sizeof(int));
//	istream.read(reinterpret_cast<char*>(&mMP), sizeof(int));
//	return istream;
//}
//
//std::ofstream& Monster::WriteBinary(std::ofstream& ostream)
//{
//	// 문자열을 바이너리로 저장하기 위해서는 길이를 먼저 저장한 후 문자열을 그 길이 만큼 저장한다.
//	int strLen = static_cast<int>(mName.size());
//	// 정수형 멤버는 바로 형변화 후 저장한다.
//	ostream.write(reinterpret_cast<char*>(&strLen), sizeof(int));
//	ostream.write(mName.c_str(), strLen);
//	ostream.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
//	ostream.write(reinterpret_cast<char*>(&mHP), sizeof(int));
//	ostream.write(reinterpret_cast<char*>(&mMP), sizeof(int));
//	return ostream;
//}
//
//std::ifstream& operator>>(std::ifstream& istream, Monster& monster)
//{
//	return monster.ReadBinary(istream);
//}
//std::ofstream& operator<<(std::ofstream& ostream, Monster& monster)
//{
//	return monster.WriteBinary(ostream);
//}
