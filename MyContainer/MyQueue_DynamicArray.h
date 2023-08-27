#pragma once
#include "Container_Master.h"

/*
* ���� �迭 ť �Դϴ�.
*
* ������� ���� ���Ҹ� Pop�ϰ� �Ǹ� �� �ڸ��� NULL�� ä��ϴ�
*/

template <typename Data>
class MyQueue_DynamicArray : public Container_Master<Data>
{

public:
	MyQueue_DynamicArray()
	{
		//my_base�� nullptr����
		//������� ĳ�۽�Ƽ�� 0�̹Ƿ� ���Ҹ� �߰��Ҷ� Reserve()�Լ����� �Ҵ��� �̷����ϴ�
		this->my_base = nullptr;
		this->my_capacity = this->my_size = 0;
	}
	MyQueue_DynamicArray(std::initializer_list<Data> list)
	{
		this->my_capacity = this->my_size = 0;
		this->Reserve(list.size());

		for (auto& element : list)
		{
			this->my_base[this->my_size++] = element;
		}
	}
	~MyQueue_DynamicArray()
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
		this->my_capacity = capacity;

		//Debug
		for (size_t i = 0; i < capacity; ++i)
		{
			temp[i] = NULL;
		}

		//�����̳ʿ� ���Ұ� �ִٸ� ���� �Ҵ��� �ּҷ� �Ű��ݴϴ�
		if (this->my_size >= 1)
		{
			for (size_t i = _front; i < _rear; ++i)
			{
				temp[i] = this->my_base[i];
			}
			delete[] this->my_base;

		}

		this->my_base = temp;
	}

	//������ ��ġ�� ���Ҹ� �߰��մϴ�
	//Enqueue()
	void PushBack(const Data& data)
	{
		//rear�� ��ġ�� �迭�� �ִ� ũ�⸦ �Ѿ����� Ȯ��
		if (_rear >= this->my_capacity)
		{
			this->Reserve(this->my_capacity + this->additive_capacity);
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
		//ť�� ��������� Pop�� ���� �ʽ��ϴ�
		if (this->my_size <= 0)
		{
			return false;
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

	//���ʿ� ����ִ� �迭�ڸ��� ���� ���ҵ�� ä��ϴ�.
	//���Ҵ��ϴ� ����� ������, ���⼱ �� ������ NULL(0)�� ǥ���߽��ϴ�
	void SortQueue()
	{
		//���Ҹ� ������ �̵���ŵ�ϴ�
		size_t i = 0;
		for (i = _front; i < _rear; ++i)
		{
			this->my_base[i - _front] = this->my_base[i];			
		}

		//�̵��� ���Ҹ� NULL�� ä��ϴ�
		for (i -= _front; i < _rear; ++i)
		{
			std::cout << std::to_string(i) << std::endl;
			this->my_base[i] = NULL;
		}

		_rear -= _front;
		_front = 0;
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