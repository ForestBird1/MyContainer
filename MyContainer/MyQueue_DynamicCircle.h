#pragma once
#include "Container_Master.h"

/*
* 동적 원형 큐 입니다.
* 
* 디버깅을 위해 원소를 Pop하게 되면 그 자리를 NULL로 채웁니다
*/

template <typename Data>
class MyQueue_DynamicCircle : public Container_Master<Data>
{

public:
	MyQueue_DynamicCircle()
	{
		//my_base가 nullptr지만
		//사이즈및 캐퍼시티가 0이므로 원소를 추가할때 Reserve()함수에서 할당이 이뤄집니다
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
		//기존 캐퍼시티가 더 크다면 재할당을 하지 않습니다
		if (this->my_capacity >= capacity)
			return;

		Data* temp = new Data[capacity];

		//Debug
		for (size_t i = 0; i < capacity; ++i)
		{
			temp[i] = NULL;
		}

		//0번째 인덱스부터 rear까지 새로 할당한 배열에 복사합니다
		for (size_t i = 0; i < _rear; ++i)
		{
			temp[i] = this->my_base[i];
		}

		//컨테이너에 원소가 있다면 새로 할당한 주소로 옮겨줍니다
		if (this->my_capacity > 0 &&
			this->my_size > 0 &&
			_rear <= _front)
		{
			//front부터 마지막인덱스까지 새로 할당한 배열에 복사합니다
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

	//마지막 위치에 원소를 추가합니다
	//Enqueue()
	void PushBack(const Data& data)
	{
		//rear의 위치가 배열의 최대 크기를 넘었는지 확인
		if (_rear >= this->my_capacity)
		{
			_rear = 0;
		}

		//컨테이너에 비어있는 자리가 있는지 확인
		//rear와 front가 동일한 인덱스를 가리키면 큐가 꽉찼거나 비어있음을 의미합니다
		if (_rear == _front)
		{
			//큐가 꽉찼으면 재할당합니다
			if (this->my_size > 0)
			{
				this->Reserve(this->my_capacity + this->additive_capacity);
			}
		}

		//추가합니다
		this->my_base[_rear++] = data;
		++this->my_size;
	}

	//가장 처음으로 들어온 원소를 반환합니다
	//디버깅을 위해 bool로 반환의 실패여부를 체크합니다
	//Dequeue
	const bool PopFront(Data& out_data)
	{
		//rear와 front가 동일한 인덱스를 가리키면 큐가 꽉찼거나 비어있음을 의미합니다
		if (_rear == _front)
		{
			//큐가 비어있으면 Pop을 하지 않습니다
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
		//데이터를 반환합니다
		//디버그하기 위해 만든 함수로, 인덱스가 유효한지 확인하지 않습니다
		return this->my_base[index];
	}

	const size_t GetFront() const { return _front; }
	const size_t GetRear() const { return _rear; }
private:
	//데이터를 꺼낼 공간을 가리키고 있습니다. 데이터가 없을 수도 있습니다.
	size_t _front = 0;
	//데이터를 넣을 빈 공간을 가리키고 있습니다
	size_t _rear = 0;
};