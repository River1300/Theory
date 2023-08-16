/* ----- < 구조체 메모리 정렬 문제 > ----- */

//#include <iostream>
//struct OneByte
//{
//	char myChar;	// char TYPE : 1 BYTE
//};
//#pragma pack(push, 1)
//struct FiveByte	// #. 생각하기로는 5 BYTE를 차지하는 것이 정상이지만 8 BYTE를 차지한다.
//{
//	char myChar;	// char TYPE : 1 BYTE
//	int myInt;		// int TYPE : 4 BYTE
////		=> 컴파일러가 효율적으로 메모리를 관리하기 위해 구조체 멤버들의 크기를 조절
////		=> myChar 1 BYTE, 3 BYTE Padding, myInt 4 BYTE
////		=> 4바이트 단위로 주소를 관리하면 편하기 때문에 1바이트 뒤에 3바이트의 패딩을 추가한다.
////		=> 그래서 구조체의 실제 크기는 8바이트가 된다.
//};
//#pragma pack(pop)
////	=> 구조체의 바이트를 관리하는 pack(), 1 바이트 단위로 패킹
//int main()
//{
//	std::cout << sizeof(OneByte) << '\n';
//	std::cout << sizeof(FiveByte) << '\n';
//}

/* ----- < 울타리 말뚝 오류 > ----- */

// Off-By-One Error (OBOE), Off-By-One Bug(OBOB), OB1 Error
// 경계선 문제로 발생하는 것으로, 배열과 같이 크기가 정해져 있는 자료 구조에 허용값을 하나 넘어가는 경우를 일컫는 오류이다.

/* 반복문의 조건에서 부등호 실수 */

/*
for(index = 0; index < 5; index++)
{	0 ~ 4까지 5번 반복한다. 만약 5를 실행시키고자 한다면 index <= 5라고 명시해야 한다.
	loop statements
}
*/

/* 인덱스는 0에서 시작하는 것을 오해 */

// FencePost error, Telegraph pole, Lamp-post, Picket Fence Error등 다양한 이름이 있는데 모두 말뚝과 관련된 표현이다.
// 10미터의 울타리가 있는데, 여기에 2미터 간격으로 말뚝을 설치하려면 몇 개가 필요하나? 10 / 2 = 5 라고 생각하기 쉬운데 틀렸다.
// 시작은 0 부터 시작하기 때문에 0 지점에 1개 ~ 2, 4, 6, 8, 10 총 6개가 필요하다.
// N개의 배열은 인덱스 0에서 시작하므로 N - 1이 가장 마지막 값이다.