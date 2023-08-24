#pragma once
#include "Container_Master.h"

template <typename Data>
class MyStack : public Container_Master<Data>
{

public:
	MyStack()
	{
		//my_base�� nullptr����
		//������� ĳ�۽�Ƽ�� 0�̹Ƿ� ���Ҹ� �߰��Ҷ� Reserve()�Լ����� �Ҵ��� �̷����ϴ�
		this->my_base = nullptr;
		this->my_capacity = this->my_size = 0;
	}
	MyStack(std::initializer_list<Data> list)
	{
		this->my_capacity = this->my_size = 0;
		this->Reserve(list.size());

		for (auto& element : list)
		{
			this->my_base[this->my_size++] = element;
		}
	}
	~MyStack()
	{
		if (this->my_base)
		{
			delete[] this->my_base;
		}
	}

	//������ ��ġ�� ���Ҹ� �߰��մϴ�
	void PushBack(const Data& data)
	{
		//�����̳ʿ� ����ִ� �ڸ��� �ִ��� Ȯ��
		if (this->my_size == this->my_capacity)
		{
			//���ڸ� ����. ���Ҵ��� �õ��մϴ�
			this->Reserve(this->my_capacity + this->additive_capacity);
		}

		//�߰��մϴ�
		this->my_base[this->my_size++] = data;
	}

	Data& PopBack()
	{
		this->CheckValidIndex(this->my_size - 1);
		return this->my_base[this->my_size-- - 1];
	}

	Data& Top()
	{
		this->CheckValidIndex(this->my_size - 1);
		return this->my_base[this->my_size - 1];
	}


	//Debug
	Data& operator[] (const size_t index)
	{
		//�ε����� ��ȿ�ϸ� �ε��� ��ġ�� ������ �ڷḦ ��ȯ�ϼ���.
		this->CheckValidIndex(index);

		//�����͸� ��ȯ�մϴ�
		//��ȯ ������ ���� �������� �����ϼ���.
		return this->my_base[index];
	}
};