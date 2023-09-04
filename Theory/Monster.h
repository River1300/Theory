#pragma once
#include <fstream>
#include <string>

class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;

public:
	Monster() : mName{}, mLevel{}, mHP{}, mMP{} {}
	Monster(std::string name, int level, int hp, int mp) :
		mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp } {}

	std::ifstream& ReadBinary(std::ifstream& istream);
	std::ofstream& WriteBinary(std::ofstream& ostream);
};

std::ifstream& Monster::ReadBinary(std::ifstream& istream)
{
	int strLen{};
	// ���ڿ� ���̸� ���� ��, �ش� ���̸�ŭ ���ڿ� ũ�⸦ �����Ѵ�.
	// mName �� std::string �̹Ƿ� �迭 ÷��[0]�� ����� char* ���·� ��ȯ�Ѵ�.
	// ���� �� c_str() ��� �Լ��� const ���̹Ƿ� ����� �� ����.
	istream.read(reinterpret_cast<char*>(&strLen), sizeof(int));
	mName.resize(strLen);
	istream.read(&mName[0], strLen);
	istream.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
	istream.read(reinterpret_cast<char*>(&mHP), sizeof(int));
	istream.read(reinterpret_cast<char*>(&mMP), sizeof(int));
	return istream;
}

std::ofstream& Monster::WriteBinary(std::ofstream& ostream)
{
	// ���ڿ��� ���̳ʸ��� �����ϱ� ���ؼ��� ���̸� ���� ������ �� ���ڿ��� �� ���� ��ŭ �����Ѵ�.
	int strLen = static_cast<int>(mName.size());
	// ������ ����� �ٷ� ����ȭ �� �����Ѵ�.
	ostream.write(reinterpret_cast<char*>(&strLen), sizeof(int));
	ostream.write(mName.c_str(), strLen);
	ostream.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ostream.write(reinterpret_cast<char*>(&mHP), sizeof(int));
	ostream.write(reinterpret_cast<char*>(&mMP), sizeof(int));
	return ostream;
}

std::ifstream& operator>>(std::ifstream& istream, Monster& monster)
{
	return monster.ReadBinary(istream);
}
std::ofstream& operator<<(std::ofstream& ostream, Monster& monster)
{
	return monster.WriteBinary(ostream);
}