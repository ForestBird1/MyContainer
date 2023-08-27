#pragma once
#include "Container_Master.h"

/*
* ���� ���� ť �Դϴ�.
*
* ��������ť�� �ѹ� ����� �����Ǹ� �� ����� ���� �� �� �����ϴ�.
* 
* ������� ���� ���Ҹ� Pop�ϰ� �Ǹ� �� �ڸ��� NULL�� ä��ϴ�
*/

template <typename Data>
class MyQueue_FixedCircle : public Container_Master<Data>
{

public:
	MyQueue_FixedCircle(size_t i_init_size)
	{
		//my_base�� nullptr����
		//������� ĳ�۽�Ƽ�� 0�̹Ƿ� ���Ҹ� �߰��Ҷ� Reserve()�Լ����� �Ҵ��� �̷����ϴ�
		this->my_size = 0;
		this->my_capacity = i_init_size;

		Data* temp = new Data[this->my_capacity];

		this->my_base = temp;

		//Debug
		for (size_t i = 0; i < this->my_capacity; ++i)
			this->my_base[i] = NULL;
	}
	~MyQueue_FixedCircle()
	{
		if (this->my_base)
		{
			delete[] this->my_base;
		}
	}

	void Reserve(size_t capacity) override
	{
		/*��������ť�� �ʱ�ȭ�� �� ������ ����� ������ �� �����ϴ�*/
	}

	//������ ��ġ�� ���Ҹ� �߰��մϴ�
	//Enqueue()
	const bool PushBack(const Data& data)
	{
		//rear�� ��ġ�� �迭�� �ִ� ũ�⸦ �Ѿ����� Ȯ��
		if (_rear >= this->my_capacity)
		{
			_rear = 0;
		}

		//�����̳ʿ� ����ִ� �ڸ��� �ִ��� Ȯ��
		//rear�� front�� ������ �ε����� ����Ű�� ť�� ��á�ų� ��������� �ǹ��մϴ�
		if (_rear == _front)
		{
			//ť�� ��á���� �����͸� ä�� �� �����ϴ�
			if (this->my_size > 0)
			{
				return false;
			}
		}

		//�߰��մϴ�
		this->my_base[_rear++] = data;
		++this->my_size;
		return true;
	}

	//���� ó������ ���� ���Ҹ� ��ȯ�մϴ�
	//������� ���� bool�� ��ȯ�� ���п��θ� üũ�մϴ�
	//Dequeue
	const bool PopFront(Data& out_data)
	{
		//rear�� front�� ������ �ε����� ����Ű�� ť�� ��á�ų� ��������� �ǹ��մϴ�
		if (_rear == _front)
		{
			//ť�� ��������� Pop�� ���� �ʽ��ϴ�
			if (this->my_size <= 0)
			{
				return false;
			}
		}

		if (_front >= this->my_capacity)
		{
			_front = 0;
		}

		--this->my_size;

		//return this->my_base[_front++];

		//Debug
		Data& data = this->my_base[_front++];
		Data data_new = data;
		out_data = data_new;
		data = NULL;

		return true;
	}

	//Debug
	Data& operator[] (const size_t index)
	{
		//�����͸� ��ȯ�մϴ�
		//������ϱ� ���� ���� �Լ���, �ε����� ��ȿ���� Ȯ������ �ʽ��ϴ�
		return this->my_base[index];
	}

	const size_t GetFront() const { return _front; }
	const size_t GetRear() const { return _rear; }
private:
	//�����͸� ���� ������ ����Ű�� �ֽ��ϴ�. �����Ͱ� ���� ���� �ֽ��ϴ�.
	size_t _front = 0;
	//�����͸� ���� �� ������ ����Ű�� �ֽ��ϴ�
	size_t _rear = 0;
};