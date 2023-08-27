#pragma once
#include "Container_Master.h"

/*
* ���� ���� ť �Դϴ�.
* 
* ������� ���� ���Ҹ� Pop�ϰ� �Ǹ� �� �ڸ��� NULL�� ä��ϴ�
*/

template <typename Data>
class MyQueue_DynamicCircle : public Container_Master<Data>
{

public:
	MyQueue_DynamicCircle()
	{
		//my_base�� nullptr����
		//������� ĳ�۽�Ƽ�� 0�̹Ƿ� ���Ҹ� �߰��Ҷ� Reserve()�Լ����� �Ҵ��� �̷����ϴ�
		this->my_base = nullptr;
		this->my_capacity = this->my_size = 0;
	}
	MyQueue_DynamicCircle(std::initializer_list<Data> list)
	{
		this->my_capacity = this->my_size = 0;
		this->Reserve(list.size());

		for (auto& element : list)
		{
			this->my_base[this->my_size++] = element;
		}
	}
	~MyQueue_DynamicCircle()
	{
		if (this->my_base)
		{
			delete[] this->my_base;
		}
	}

	void Reserve(size_t capacity) override
	{
		//���� ĳ�۽�Ƽ�� �� ũ�ٸ� ���Ҵ��� ���� �ʽ��ϴ�
		if (this->my_capacity >= capacity)
			return;

		Data* temp = new Data[capacity];

		//Debug
		for (size_t i = 0; i < capacity; ++i)
		{
			temp[i] = NULL;
		}

		//0��° �ε������� rear���� ���� �Ҵ��� �迭�� �����մϴ�
		for (size_t i = 0; i < _rear; ++i)
		{
			temp[i] = this->my_base[i];
		}

		//�����̳ʿ� ���Ұ� �ִٸ� ���� �Ҵ��� �ּҷ� �Ű��ݴϴ�
		if (this->my_capacity > 0 &&
			this->my_size > 0 &&
			_rear <= _front)
		{
			//front���� �������ε������� ���� �Ҵ��� �迭�� �����մϴ�
			for (size_t i = 0; i < this->my_capacity - _front; ++i)
			{
				temp[capacity - i - 1] = this->my_base[this->my_capacity - i - 1];
			}
			_front += capacity - this->my_capacity;

			delete[] this->my_base;
		}

		
		this->my_capacity = capacity;
		this->my_base = temp;
	}

	//������ ��ġ�� ���Ҹ� �߰��մϴ�
	//Enqueue()
	void PushBack(const Data& data)
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
			//ť�� ��á���� ���Ҵ��մϴ�
			if (this->my_size > 0)
			{
				this->Reserve(this->my_capacity + this->additive_capacity);
			}
		}

		//�߰��մϴ�
		this->my_base[_rear++] = data;
		++this->my_size;
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