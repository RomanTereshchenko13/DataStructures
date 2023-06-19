#ifndef _STACK_
#define _STACK_

#include"LinkedList.h"

template<typename T>
class Stack : private LinkedList<T>
{
public:
	using Iterator = LinkedList<T>::Iterator;
public:
	Stack() = default;
	Stack(std::initializer_list<T> list) : LinkedList<T>(list) {}

	void Push(const T& value) { LinkedList<T>::PushBack(value); }
	void Pop() { LinkedList<T>::PopBack(); }
	void Swap(Stack& other) { LinkedList<T>::Swap(other); }
	bool Find(const T& value) { return LinkedList<T>::Find(value); }
	size_t Size() const { return LinkedList<T>::Size(); }
	bool Empty() const { return LinkedList<T>::Empty(); }
	T& Top() const { return LinkedList<T>::Back(); }

	Iterator begin() { return LinkedList<T>::begin(); }
	Iterator end() { return LinkedList<T>::end(); }
};

#endif //_STACK_