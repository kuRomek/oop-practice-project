#pragma once
#include <iostream>

template<class T>
class Container
{
public:
	struct Node
	{
		Node * previous;
		Node * next;
		T value;
	};

	Container() : head(nullptr), tail(nullptr), size(0) {}

	class Iterator
	{
	public:
		Iterator(Node * head) : node(head) {}

		Iterator operator ++ () { Iterator temp = *this; node = node->next; return temp; }

		Iterator operator -- () { Iterator temp = *this; node = node->previous; return temp; }

		bool operator != (Iterator const & other) const { return this->node != other.node; }

		T & operator * () { return node->value; }

	private:
		Node * node;
	};

	Iterator begin() const { return Iterator(head); }
	Iterator end() const { return Iterator(tail->next); }

	void PushTail(T const & value)
	{
		if (tail == nullptr)
		{
			tail = new Node;
			tail->value = value;
			tail->previous = tail->next = nullptr;
			head = tail;
		}
		else
		{
			Node * temp = tail;
			tail->next = new Node;
			tail = tail->next;
			tail->value = value;
			tail->next = nullptr;
			tail->previous = temp;
		}

		++size;
	}

	void PushHead(T const & value)
	{
		if (head == nullptr)
		{
			head = new Node;
			head->value = value;
			head->previous = head->next = nullptr;
			tail = head;
		}
		else
		{
			Node * temp = head;
			head->previous = new Node;
			head = head->previous;
			head->value = value;
			head->previous = nullptr;
			head->next = temp;
		}

		++size;
	}

	T PopTail()
	{
		if (tail == nullptr)
		{
			std::cout << "The container is empty.";
			return 0;
		}
		
		if (head == tail)
		{
			T popValue = tail->value;
			Clear();
			return popValue;
		}
		else
		{
			T popValue = tail->value;
			tail = tail->previous;
			delete tail->next;
			tail->next = nullptr;
			--size;
			return popValue;
		}
	}

	T PopHead()
	{
		if (head == nullptr)
		{
			std::cout << "The container is empty.";
			return 0;
		}

		if (head == tail)
		{
			T popValue = head->value;
			Clear();
			return popValue;
		}
		else
		{
			T popValue = head->value;
			head = head->next;
			delete head->previous;
			head->previous = nullptr;
			return popValue;
		}
	}

	T GetHead() const { return head->value; }

	T GetTail() const { return tail->value; }

	bool IsEmpty() const { return size == 0; }

	uint32_t GetSize() const { return size; }

	void Swap(Container<T> & other)
	{
		if (other.GetSize() > this->GetSize())
		{
			uint32_t sizeBeforeSwap = this->size;
			for (Iterator i = this->begin(), j = other.begin(); j != other.end(); ++j)
			{
				if (i != this->end())
				{
					std::swap(*i, *j);
					++i;
				}
				else this->PushTail(*j);
			}
			while (other.GetSize() != sizeBeforeSwap) other.PopTail();
		}
		else
		{
			uint32_t sizeBeforeSwap = other.GetSize();
			for (Iterator i = this->begin(), j = other.begin(); i != this->end(); ++i)
			{
				if (j != other.end())
				{
					std::swap(*i, *j);
					++j;
				}
				else other.PushTail(*i);
			}
			while (this->size != sizeBeforeSwap) this->PopTail();
		}
	}

	void Reverse()
	{
		Iterator i = begin(), j = Iterator(tail);
		for (uint32_t l = 0; l < GetSize() / 2; ++l, ++i, --j) std::swap(*i, *j);
	}

	void Print() const
	{
		std::cout << "[";
		for (Iterator i = this->begin(); i != this->end(); ++i)
		{
			if (i != Iterator(tail)) std::cout << *i << ", ";
			else std::cout << *i << "]" << std::endl;
		}
	}

	void Clear()
	{
		while (size != 0)
		{
			if (tail != head)
			{
				tail = tail->previous;
				delete tail->next;
			}
			else delete tail;

			head = tail = nullptr;

			--size;
		}
	}

	~Container() { Clear(); }


private:
	Node * head;
	Node * tail;
	uint32_t size;
};
