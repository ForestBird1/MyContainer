#include <string>
#include <cstring>
#include <iostream>
#include <vector>

#include "MyVector.h"
#include "MyStack.h"

using namespace std;

void PrintMyVector(MyVector<int>& vector)
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
	* ������ �Լ����� Add,Num,Max�� �𸮾����� TArray�� �����ؼ� ��������ϴ�
	* 
	* Add(): ��������ġ�� �����߰�
	* Num(): �迭�� ������
	* Max(): �迭�� ĳ�۽�Ƽ������
	* 
	* �� �ڼ��� ������ MyVector.h�� �����ϼ���
	*/

	cout << "MyVector �׽�Ʈ" << endl;

	cout << endl << "���ͻ���" << endl;
	MyVector<int> my_vector;
	PrintMyVector(my_vector);

	//size_t�� unsigned int�� '���'�մϴ�
	//https://forestbird0.tistory.com/37
	const size_t vector_size = 10;
	my_vector.Reserve(vector_size);
	cout << endl << "���� capacity  �Ҵ�. �Ҵ� ������: " + to_string(vector_size) << endl;
	PrintMyVector(my_vector);

	my_vector.Add(0); //index: 0
	my_vector.Add(1); //index: 1
	my_vector.Add(3); //index: 2
	my_vector.Add(4); //index: 3
	my_vector.Add(5); //index: 4
	cout << endl << "���Ϳ� ������ �߰�" << endl;
	PrintMyVector(my_vector);

	cout << endl << "�ε����� ������ �迭�� �����մϴ�" << endl;
	cout << to_string(my_vector[0]) << endl;
	cout << to_string(my_vector[3]) << endl;

	cout << endl << "������ ĳ�۽�Ƽ�� �ʰ��ؼ� ���Ҹ� �߰��մϴ�. �ʰ��� 32���� ĳ�۽�Ƽ�� �ڵ����� �߰��˴ϴ�" << endl;
	for (size_t i = 0, i_len = my_vector.Max() - my_vector.Num() + 1; i < i_len; ++i)
	{
		my_vector.Add(my_vector[my_vector.Num() - 1] + 1);
	}
	PrintMyVector(my_vector);

	size_t insert_index = 2;
	int insert_element = 2;
	cout << endl << "�迭�߰��� ���ο� ���� �߰��մϴ�. ������ġ�ε���: " + to_string(insert_index) + " ���԰�: " + to_string(insert_element) << endl;
	my_vector.Insert(2, 2);
	PrintMyVector(my_vector);

	cout << endl << "�迭���Ҹ� �����մϴ�" << endl;
	my_vector.RemoveAt(my_vector.Num() - 1);
	PrintMyVector(my_vector);
	my_vector.RemoveAt(2);
	PrintMyVector(my_vector);
	my_vector.RemoveAt(0);
	PrintMyVector(my_vector);

	cout << endl << "������ ������� ������ �ӵ��� ���� �迭���� ��������Դϴ�" << endl;
	my_vector.RemoveAtSwap(0);
	PrintMyVector(my_vector);

	cout << endl << "������Popó�� ���� ������ ���Ҹ� ��ȯ�ϰ� �����մϴ�" << endl;
	int pop_element = my_vector.PopBack();
	cout << "Pop element: " + to_string(pop_element) << endl;
	PrintMyVector(my_vector);

	cout << endl << "�迭�� ���Ҹ� �߰������ʰ� ���ϴ� ������ �����մϴ�" << endl;
	my_vector = { 4,3,2,1 };
	PrintMyVector(my_vector);

	cout << endl << "�ٸ� �迭�� ������մϴ� operator=" << endl;
	MyVector<int> new_vector({ 1, 2, 3, 4 });
	my_vector = new_vector;
	PrintMyVector(my_vector);
}

void PrintMyStack(MyStack<int>& stack)
{
	cout << "[";
	for (size_t i = 0; i < stack.Num(); ++i)
	{
		const int element = stack[i];
		cout << to_string(element) + ",";
	}
	cout << "] Stack Size: " + to_string(stack.Num()) + " Capacity: " + to_string(stack.Max()) << endl;
}
void TestMyStack()
{
	cout << "MyStack �׽�Ʈ" << endl;

	cout << endl << "���û���" << endl;
	MyStack<int> my_stack;
	PrintMyStack(my_stack);

	//size_t�� unsigned int�� '���'�մϴ�
	//https://forestbird0.tistory.com/37
	const size_t stack_size = 10;
	my_stack.Reserve(stack_size);
	cout << endl << "���� capacity  �Ҵ�. �Ҵ� ������: " + to_string(stack_size) << endl;
	PrintMyStack(my_stack);

	my_stack.PushBack(0); //index: 0
	my_stack.PushBack(1); //index: 1
	my_stack.PushBack(2); //index: 2
	my_stack.PushBack(3); //index: 3
	my_stack.PushBack(4); //index: 4
	cout << endl << "���ÿ� ������ �߰�" << endl;
	PrintMyStack(my_stack);

	cout << endl << "������ ĳ�۽�Ƽ�� �ʰ��ؼ� ���Ҹ� �߰��մϴ�. �ʰ��� 32���� ĳ�۽�Ƽ�� �ڵ����� �߰��˴ϴ�" << endl;
	for (size_t i = 0, i_len = my_stack.Max() - my_stack.Num() + 1; i < i_len; ++i)
	{
		my_stack.PushBack(9);
	}
	PrintMyStack(my_stack);

	cout << endl << "������ ������ ���� �������� �߰��� ����: " + to_string(my_stack.Top()) << endl;
	PrintMyStack(my_stack);

	cout << endl << "������ ������ ���� �������� �߰��� ���Ҹ� ������ ��ȯ(PopBack): " + to_string(my_stack.PopBack()) << endl;
	PrintMyStack(my_stack);

	cout << endl << "������ ��� ���� Pop"<< endl;
	for (size_t i = 0, i_len = my_stack.Num(); i < i_len; ++i)
	{
		my_stack.PopBack();
		PrintMyStack(my_stack);
	}
}


int main()
{
	//TestMyVector();
	TestMyStack();
}
