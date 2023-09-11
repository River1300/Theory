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
//	// ���ڿ� ���̸� ���� ��, �ش� ���̸�ŭ ���ڿ� ũ�⸦ �����Ѵ�.
//	// mName �� std::string �̹Ƿ� �迭 ÷��[0]�� ����� char* ���·� ��ȯ�Ѵ�.
//	// ���� �� c_str() ��� �Լ��� const ���̹Ƿ� ����� �� ����.
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
//	// ���ڿ��� ���̳ʸ��� �����ϱ� ���ؼ��� ���̸� ���� ������ �� ���ڿ��� �� ���� ��ŭ �����Ѵ�.
//	int strLen = static_cast<int>(mName.size());
//	// ������ ����� �ٷ� ����ȭ �� �����Ѵ�.
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
