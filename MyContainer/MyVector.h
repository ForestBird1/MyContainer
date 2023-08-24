#pragma once
#include "Container_Master.h"

template <typename Data>
class MyVector : public Container_Master<Data>
{

public:

	class iterator
	{
	private:
		Data* pos = nullptr;
	public:
		iterator(Data* pos = 0)
		{
			this->pos = pos;
		}
		Data& operator* ()const
		{
			return *pos;
		}

		int operator-(const iterator& iter)const
		{
			return pos - iter.pos;
		}

		bool operator!=(const iterator& iter)const
		{
			return pos != iter.pos;
		}
		bool operator==(const iterator& iter)const
		{
			return pos == iter.pos;
		}

		//����
		iterator& operator++()
		{
			++pos;
			return (*this);
		}

		//����
		const iterator operator++(int)
		{
			iterator re(*this);
			pos++;
			return re;
		}
	};
	typedef
		iterator const_iterator;

public:
	MyVector()
	{
		//my_base�� nullptr����
		//������� ĳ�۽�Ƽ�� 0�̹Ƿ� ���Ҹ� �߰��Ҷ� Reserve()�Լ����� �Ҵ��� �̷����ϴ�
		this->my_base = nullptr;
		this->my_capacity = this->my_size = 0;
	}
	MyVector(std::initializer_list<Data> list)
	{
		this->my_capacity = this->my_size = 0;
		this->Reserve(list.size());

		for (auto& element : list)
		{
			this->my_base[this->my_size++] = element;
		}
	}
	~MyVector()
	{
		if (this->my_base)
		{
			delete[] this->my_base;
		}
	}

	//������ ��ġ�� ���Ҹ� �߰��մϴ�
	void Add(const Data& data)
	{
		Insert(this->Num(), data);
	}
	
	//������ ��ġ�� ���Ҹ� �߰��մϴ�
	//���� ���Խ� ���� ��ġ�� ���Һ��� ���������ұ��� ���� �ε����� +1�� �и��� ������
	//���Ұ� ���� 0�� �������ġ�� ���Եɼ��� ������ �� �ֽ��ϴ�
	void Insert(const size_t insert_index, const Data& data)
	{
		//�����̳ʿ� ����ִ� �ڸ��� �ִ��� Ȯ��
		if (this->my_size == this->my_capacity)
		{
			//���ڸ� ����. ���Ҵ��� �õ��մϴ�
			this->Reserve(this->my_capacity + this->additive_capacity);
		}


		//�����̳� �߰��� ���Ұ� ���ٸ� ���Ҹ� �ش� �������� ��ĭ�� �ڷ� �̵���ŵ�ϴ�.
		for (size_t i = this->my_size; i > insert_index; --i)
		{
			this->my_base[i] = this->my_base[i - 1];
		}
		

		//�߰��մϴ�
		this->my_base[insert_index] = data;
		++this->my_size;
	}

	//�ش� ��ġ�� ���Ҹ� �����մϴ�
	void RemoveAt(const size_t index)
	{
		this->CheckValidIndex(index);

		--this->my_size;
		for (size_t i = index; i < this->my_size; ++i)
		{
			this->my_base[i] = this->my_base[i + 1];
		}
	}

	//�����̵��� ���ϸ� ���̱� ���� ������ ���ҿ� ������ ������ ��ġ�� �����ϰ� �����մϴ�
	//������ ���Ұ� ������ ������ ��ġ�� ���� ������ ������ ������ ������� �ʽ��ϴ�
	void RemoveAtSwap(const size_t index)
	{
		--this->my_size;
		this->my_base[index] = this->my_base[this->my_size];
	}

	//������ Popó�� ������ ���Ҹ� ��ȯ�ϸ� �����մϴ�
	Data& PopBack()
	{
		const size_t last_index = this->Num() - 1;
		this->CheckValidIndex(last_index);

		Data& data = this->my_base[last_index];

		RemoveAt(last_index);

		return data;
	}

	Data& operator[] (const size_t index)
	{
		//�ε����� ��ȿ�ϸ� �ε��� ��ġ�� ������ �ڷḦ ��ȯ�ϼ���.
		this->CheckValidIndex(index);

		//�����͸� ��ȯ�մϴ�
		//��ȯ ������ ���� �������� �����ϼ���.
		return this->my_base[index];
	}

	void operator= (std::initializer_list<Data> list)
	{
		//�����迭�� size�� 0���� �����մϴ�
		this->Clear();

		//ĳ�۽�Ƽ�� �����ϸ� �߰��մϴ�
		this->Reserve(list.size());

		for (auto& element : list)
		{
			this->my_base[this->my_size++] = element;
		}
	}
	void operator= (MyVector<Data>& list)
	{
		//�����迭�� size�� 0���� �����մϴ�
		this->Clear();

		//ĳ�۽�Ƽ�� �����ϸ� �߰��մϴ�
		this->Reserve(list.Num());

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			this->my_base[this->my_size++] = *it;
		}
	}

	iterator begin()
	{
		iterator iter(this->my_base);
		return iter;
	}
	iterator end()
	{
		iterator iter(this->my_base + this->my_size);
		return iter;
	}
};