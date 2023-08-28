#pragma once
#include <iostream>

/*
* ���߿��Ḯ��Ʈ�Դϴ�.
*/

template <typename Data>
class MyLinkedList
{
private:
	struct Node
	{
		Data data = NULL;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

public:
	MyLinkedList()
	{
		head = new Node;
		tail = new Node;

		head->next = tail;
		tail->prev = head;
	}
	~MyLinkedList()
	{
		//��� ��� ����
		RemoveAll();

		delete head;
		delete tail;
	}

	//�����͸� �߰��մϴ�
	void AddFront(const Data& data)
	{
		Add(head->next, data);
	}
	void AddBack(const Data& data)
	{
		Add(tail, data);
	}

	//���� ��, ���� �����͸� �����մϴ�
	const bool RemoveFront()
	{
		return Remove(head->next);
	}
	const bool RemoveBack()
	{
		return Remove(tail->prev);
	}
	
	//���ϴ� �����͸� ã�Ƽ� �����մϴ�
	const bool RemoveData(const Data& data)
	{
		if (size <= 0) return false;

		for (Node* nd = head->next; nd != tail; nd = nd->next)
		{
			if (nd->data == data)
			{
				//������ �����͸� ã�ҽ��ϴ�. �����մϴ�
				return Remove(nd);
			}
		}

		//������ �����͸� ã�� ���߽��ϴ�
		return false;
	}

	//��� �����͸� �����մϴ�
	void RemoveAll()
	{
		while (RemoveFront()) {}
	}

	//�����͸� ��ȯ�մϴ�
	Data& GetDataFront()
	{
		return head->next->data;
	}
	Data& GetDataBack()
	{
		return tail->prev->data;
	}

	void PrintAllDataForward()
	{
		for (Node* nd = head->next; nd != tail; nd = nd->next)
		{
			std::cout << std::to_string(nd->data) + ",";
		}
		std::cout << std::endl;
	}
	void PrintAllDataBackward()
	{
		for (Node* nd = tail->prev; nd != head; nd = nd->prev)
		{
			std::cout << std::to_string(nd->data) + ",";
		}
		std::cout << std::endl;
	}
private:
	//�����͸� �߰��մϴ�.
	void Add(Node* nd_next, const Data& data)
	{
		//��带 ���λ����մϴ�
		Node* nd = new Node;
		nd->data = data;

		//������ ����� ��, �� ��带 �����մϴ�.
		nd->next = nd_next;
		nd->prev = nd_next->prev;

		//��, �� ��嵵 ������ ��忡 �����մϴ�
		nd_next->prev->next = nd;
		nd_next->prev = nd;

		++size;
	}

	//�����͸� ã�Ƽ� �����մϴ�
	const bool Remove(Node* nd_remove)
	{
		if (size <= 0) return false;

		nd_remove->prev->next = nd_remove->next;
		nd_remove->next->prev = nd_remove->prev;
		delete nd_remove;
		--size;
		return true;
	}
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};