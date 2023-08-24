#include <string>
#include <cstring>
#include <iostream>
#include <vector>

#include "MyVector.h"

using namespace std;

void PrintVectorElement(MyVector<int>& vector)
{
	cout << "[";
	for (auto it = vector.begin(); it != vector.end(); ++it)
	{
		cout << to_string(*it) + ",";
	}
	cout << "] Vector Size: " + to_string(vector.Num()) + " Capacity: " + to_string(vector.Max()) << endl;
}
void TestMyVector()
{
	/*
	* 벡터의 함수명인 Add,Num,Max은 언리얼엔진의 TArray를 참고해서 만들었습니다
	* 
	* Add(): 마지막위치에 원소추가
	* Num(): 배열의 사이즈
	* Max(): 배열의 캐퍼시티사이즈
	* 
	* 더 자세한 내용은 MyVector.h를 참고하세요
	*/

	cout << "MyVector 테스트" << endl;

	cout << endl << "벡터생성" << endl;
	MyVector<int> my_vector;
	PrintVectorElement(my_vector);

	//size_t는 unsigned int와 '비슷'합니다
	//https://forestbird0.tistory.com/37
	const size_t vector_size = 10;
	my_vector.Reserve(vector_size);
	cout << endl << "백터 capacity  할당. 할당 사이즈: " + to_string(vector_size) << endl;
	PrintVectorElement(my_vector);

	my_vector.Add(0); //index: 0
	my_vector.Add(1); //index: 1
	my_vector.Add(3); //index: 2
	my_vector.Add(4); //index: 3
	my_vector.Add(5); //index: 4
	cout << endl << "벡터에 데이터 추가" << endl;
	PrintVectorElement(my_vector);

	cout << endl << "인덱스로 빠르게 배열에 접근합니다" << endl;
	cout << to_string(my_vector[0]) << endl;
	cout << to_string(my_vector[3]) << endl;

	cout << endl << "벡터의 캐퍼시티를 초과해서 원소를 추가합니다. 초과시 32개의 캐퍼시티가 자동으로 추가됩니다" << endl;
	for (size_t i = 0, i_len = my_vector.Max() - my_vector.Num() + 1; i < i_len; ++i)
	{
		my_vector.Add(my_vector[my_vector.Num() - 1] + 1);
	}
	PrintVectorElement(my_vector);

	size_t insert_index = 2;
	int insert_element = 2;
	cout << endl << "배열중간에 새로운 값을 추가합니다. 삽입위치인덱스: " + to_string(insert_index) + " 삽입값: " + to_string(insert_element) << endl;
	my_vector.Insert(2, 2);
	PrintVectorElement(my_vector);

	cout << endl << "배열원소를 삭제합니다" << endl;
	my_vector.RemoveAt(my_vector.Num() - 1);
	PrintVectorElement(my_vector);
	my_vector.RemoveAt(2);
	PrintVectorElement(my_vector);
	my_vector.RemoveAt(0);
	PrintVectorElement(my_vector);

	cout << endl << "순서가 보장되진 않지만 속도가 빠른 배열원소 삭제방법입니다" << endl;
	my_vector.RemoveAtSwap(0);
	PrintVectorElement(my_vector);

	cout << endl << "스택의Pop처럼 가장 마지막 원소를 반환하고 삭제합니다" << endl;
	int pop_element = my_vector.PopBack();
	cout << "Pop element: " + to_string(pop_element) << endl;
	PrintVectorElement(my_vector);

	cout << endl << "배열의 원소를 추가하지않고 원하는 값으로 변경합니다" << endl;
	my_vector = { 4,3,2,1 };
	PrintVectorElement(my_vector);

	cout << endl << "다른 배열을 덮어쓰기합니다 operator=" << endl;
	MyVector<int> new_vector({ 1, 2, 3, 4 });
	my_vector = new_vector;
	PrintVectorElement(my_vector);
}

int main()
{
	TestMyVector();
}
