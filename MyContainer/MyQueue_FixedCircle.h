#pragma once
#include "Container_Master.h"

/*
* 고정 원형 큐 입니다.
*
* 고정원형큐는 한번 사이즈가 결정되면 그 사이즈를 변경 할 수 없습니다.
* 
* 디버깅을 위해 원소를 Pop하게 되면 그 자리를 NULL로 채웁니다
*/

template <typename Data>
class MyQueue_FixedCircle : public Container_Master<Data>
{

public:
	MyQueue_FixedCircle(size_t i_init_size)
	{
		//my_base가 nullptr지만
		//사이즈및 캐퍼시티가 0이므로 원소를 추가할때 Reserve()함수에서 할당이 이뤄집니다
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
		/*고정원형큐는 초기화할 때 결정된 사이즈를 변경할 수 없습니다*/
	}

	//마지막 위치에 원소를 추가합니다
	//Enqueue()
	const bool PushBack(const Data& data)
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
			//큐가 꽉찼으면 데이터를 채울 수 없습니다
			if (this->my_size > 0)
			{
				return false;
			}
		}

		//추가합니다
		this->my_base[_rear++] = data;
		++this->my_size;
		return true;
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