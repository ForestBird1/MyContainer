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

		//전위
		iterator& operator++()
		{
			++pos;
			return (*this);
		}

		//후위
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
		//my_base가 nullptr지만
		//사이즈및 캐퍼시티가 0이므로 원소를 추가할때 Reserve()함수에서 할당이 이뤄집니다
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

	//마지막 위치에 원소를 추가합니다
	void Add(const Data& data)
	{
		Insert(this->Num(), data);
	}
	
	//정해진 위치에 원소를 추가합니다
	//원소 삽입시 기존 위치의 원소부터 마지막원소까지 전부 인덱스가 +1씩 밀리기 때문에
	//원소가 많고 0의 가까운위치에 삽입될수록 느려질 수 있습니다
	void Insert(const size_t insert_index, const Data& data)
	{
		//컨테이너에 비어있는 자리가 있는지 확인
		if (this->my_size == this->my_capacity)
		{
			//빈자리 없음. 재할당을 시도합니다
			this->Reserve(this->my_capacity + this->additive_capacity);
		}


		//컨테이너 중간에 원소가 들어간다면 원소를 해당 지점부터 한칸씩 뒤로 이동시킵니다.
		for (size_t i = this->my_size; i > insert_index; --i)
		{
			this->my_base[i] = this->my_base[i - 1];
		}
		

		//추가합니다
		this->my_base[insert_index] = data;
		++this->my_size;
	}

	//해당 위치의 원소를 삭제합니다
	void RemoveAt(const size_t index)
	{
		this->CheckValidIndex(index);

		--this->my_size;
		for (size_t i = index; i < this->my_size; ++i)
		{
			this->my_base[i] = this->my_base[i + 1];
		}
	}

	//원소이동의 부하를 줄이기 위해 삭제될 원소와 마지막 원소의 위치만 변경하고 삭제합니다
	//마지막 원소가 삭제된 원소의 위치로 오기 때문에 원소의 순서는 보장되지 않습니다
	void RemoveAtSwap(const size_t index)
	{
		--this->my_size;
		this->my_base[index] = this->my_base[this->my_size];
	}

	//스택의 Pop처럼 마지막 원소를 반환하며 삭제합니다
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
		//인덱스가 유효하면 인덱스 위치에 보관한 자료를 반환하세요.
		this->CheckValidIndex(index);

		//데이터를 반환합니다
		//반환 형식이 참조 형식임을 주의하세요.
		return this->my_base[index];
	}

	void operator= (std::initializer_list<Data> list)
	{
		//기존배열의 size를 0으로 변경합니다
		this->Clear();

		//캐퍼시티가 부족하면 추가합니다
		this->Reserve(list.size());

		for (auto& element : list)
		{
			this->my_base[this->my_size++] = element;
		}
	}
	void operator= (MyVector<Data>& list)
	{
		//기존배열의 size를 0으로 변경합니다
		this->Clear();

		//캐퍼시티가 부족하면 추가합니다
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