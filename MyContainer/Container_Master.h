#pragma once

template <typename Data>
class Container_Master
{
protected:
	Data* my_base = nullptr;
	size_t my_capacity = 0;
	size_t my_size = 0;

	//ĳ�۽�Ƽ�� �ø� �� ������ ���� ���ٸ� �ش� ����ŭ �ø��ϴ�
	const size_t additive_capacity = 4;
public:
	//�����̳��� ������ ���� �����մϴ�
	virtual void Reserve(size_t capacity)
	{
		//���� ĳ�۽�Ƽ�� �� ũ�ٸ� ���Ҵ��� ���� �ʽ��ϴ�
		if (my_capacity >= capacity)
			return;

		Data* temp = new Data[capacity];
		my_capacity = capacity;

		//�����̳ʿ� ���Ұ� �ִٸ� ���� �Ҵ��� �ּҷ� �Ű��ݴϴ�
		if (my_size >= 1)
		{
			for (size_t i = 0; i < my_size; ++i)
			{
				temp[i] = my_base[i];
			}
			delete[] my_base;

		}

		my_base = temp;
	}

	//�迭�� ���Ҹ� ���������ʰ�
	//����� 0���� ����ϴ�
	//Clear()�Լ��Ŀ� ���ҷ� �߰��ϸ� ������ �ִ� ���Ҹ� �����ϴ�
	void Clear()
	{
		my_size = 0;
	}

	//�����̳��� ���Ұ����Դϴ�
	size_t Num()
	{
		return my_size;
	}

	//�����̳��� ĳ�۽�Ƽ�����Դϴ�
	size_t Max()
	{
		return my_capacity;
	}
protected:
	
	//�ε��� ��ȿ���˻縦 �մϴ�
	//��ȿ���� ������ throw
	bool CheckValidIndex(const size_t index)
	{
		if ((index >= 0) && (index < this->my_size))
		{
			return true;
		}
		else
		{
			throw printf("������ ��� �ε����� ����Ͽ����ϴ�. �����Ϸ��� �ε���: %d, �迭ũ��: %d", index, this->Num());
		}
	}
};