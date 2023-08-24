#pragma once

template <typename Data>
class Container_Master
{
protected:
	Data* my_base = nullptr;
	size_t my_capacity = 0;
	size_t my_size = 0;

	//캐퍼시티를 늘릴 때 지정된 값이 없다면 해당 값만큼 늘립니다
	const size_t additive_capacity = 32;
public:
	//컨테이너의 공간을 새로 생성합니다
	void Reserve(size_t capacity)
	{
		//기존 캐퍼시티가 더 크다면 재할당을 하지 않습니다
		if (my_capacity >= capacity)
			return;

		Data* temp = new Data[capacity];
		my_capacity = capacity;

		//컨테이너에 원소가 있다면 새로 할당한 주소로 옮겨줍니다
		if (my_size >= 1)
		{
			for (size_t i = 0; i < my_size; i++)
			{
				temp[i] = my_base[i];
			}
			delete[] my_base;

		}

		my_base = temp;
	}

	//배열의 원소를 삭제하지않고
	//사이즈를 0으로 만듭니다
	//Clear()함수후에 원소룰 추가하면 기존에 있던 원소를 덮어씌웁니다
	void Clear()
	{
		my_size = 0;
	}

	//컨테이너의 원소개수입니다
	size_t Num()
	{
		return my_size;
	}

	//컨테이너의 캐퍼시티개수입니다
	size_t Max()
	{
		return my_capacity;
	}
	
};