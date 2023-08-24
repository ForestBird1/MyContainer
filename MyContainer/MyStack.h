#pragma once
#include "Container_Master.h"

template <typename Data>
class MyStack : public Container_Master<Data>
{

public:
	MyStack()
	{
		//my_base가 nullptr지만
		//사이즈및 캐퍼시티가 0이므로 원소를 추가할때 Reserve()함수에서 할당이 이뤄집니다
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

	//마지막 위치에 원소를 추가합니다
	void PushBack(const Data& data)
	{
		//컨테이너에 비어있는 자리가 있는지 확인
		if (this->my_size == this->my_capacity)
		{
			//빈자리 없음. 재할당을 시도합니다
			this->Reserve(this->my_capacity + this->additive_capacity);
		}

		//추가합니다
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
		//인덱스가 유효하면 인덱스 위치에 보관한 자료를 반환하세요.
		this->CheckValidIndex(index);

		//데이터를 반환합니다
		//반환 형식이 참조 형식임을 주의하세요.
		return this->my_base[index];
	}
};