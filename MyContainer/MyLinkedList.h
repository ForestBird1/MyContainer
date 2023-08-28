#pragma once
#include <iostream>

/*
* 이중연결리스트입니다.
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
		//모든 노드 삭제
		RemoveAll();

		delete head;
		delete tail;
	}

	//데이터를 추가합니다
	void AddFront(const Data& data)
	{
		Add(head->next, data);
	}
	void AddBack(const Data& data)
	{
		Add(tail, data);
	}

	//가장 앞, 뒤의 데이터를 삭제합니다
	const bool RemoveFront()
	{
		return Remove(head->next);
	}
	const bool RemoveBack()
	{
		return Remove(tail->prev);
	}
	
	//원하는 데이터를 찾아서 삭제합니다
	const bool RemoveData(const Data& data)
	{
		if (size <= 0) return false;

		for (Node* nd = head->next; nd != tail; nd = nd->next)
		{
			if (nd->data == data)
			{
				//삭제할 데이터를 찾았습니다. 삭제합니다
				return Remove(nd);
			}
		}

		//삭제할 데이터를 찾지 못했습니다
		return false;
	}

	//모든 데이터를 삭제합니다
	void RemoveAll()
	{
		while (RemoveFront()) {}
	}

	//데이터를 반환합니다
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
	//데이터를 추가합니다.
	void Add(Node* nd_next, const Data& data)
	{
		//노드를 새로생성합니다
		Node* nd = new Node;
		nd->data = data;

		//생성한 노드의 앞, 뒤 노드를 연결합니다.
		nd->next = nd_next;
		nd->prev = nd_next->prev;

		//앞, 뒤 노드도 생성한 노드에 연결합니다
		nd_next->prev->next = nd;
		nd_next->prev = nd;

		++size;
	}

	//데이터를 찾아서 삭제합니다
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