#ifndef _QUEUE_
#define _QUEUE_

#include"LinkedList.h"

template<typename T>
class Queue : private LinkedList<T>
{
public:
	using Iterator = LinkedList<T>::Iterator;
public:
	Queue() = default;
	Queue(std::initializer_list<T> list) : LinkedList<T>(list) {}

	void Push(const T& value) { LinkedList<T>::PushBack(value); }
	void Pop() { LinkedList<T>::PopFront(); };
	void Swap(Queue& other) { LinkedList<T>::Swap(other); }
	bool Find(const T& value) { return LinkedList<T>::Find(value); }
	bool Empty() const { return LinkedList<T>::Empty(); };
	size_t Size() const { return LinkedList<T>::Size(); };
	T& Front() const { return LinkedList<T>::Front(); };
	T& Back() const { return LinkedList<T>::Back(); };

	Iterator begin() { return LinkedList<T>::begin(); }
	Iterator end() { return LinkedList<T>::end(); }
};

#endif //_STACK_