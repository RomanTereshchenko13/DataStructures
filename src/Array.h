#ifndef _ARRAY_
#define _ARRAY_

#include<stdexcept>
#include<string>
#include<utility>

template<typename Array>
class BaseArrayIterator
{
public:
	using ValueType = typename Array::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	BaseArrayIterator() noexcept : m_current(nullptr), m_size(0) {}
	explicit BaseArrayIterator(PointerType ptr, size_t size = 0) noexcept : m_current(ptr + size), m_size(size) {}

	PointerType operator->() const noexcept { return m_current; }
	ReferenceType operator*() const noexcept { return *m_current; }

	bool operator==(const BaseArrayIterator& other) const noexcept { return m_current == other.m_current; }
	bool operator!=(const BaseArrayIterator& other) const noexcept { return m_current != other.m_current; }

	ReferenceType operator[](int index) const noexcept { return m_current[index]; }

protected:
	PointerType m_current;
	size_t m_size;
};

template<typename Array>
class ArrayIterator : public BaseArrayIterator<Array>
{
public:
	using BaseIterator = BaseArrayIterator<Array>;
	using ValueType = typename Array::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	ArrayIterator() noexcept :BaseIterator() {}
	explicit ArrayIterator(PointerType ptr, size_t size = 0) noexcept : BaseIterator(ptr, size) {}

	ArrayIterator& operator++() noexcept { ++this->m_current; return *this; }
	ArrayIterator operator++(int) noexcept
	{
		ArrayIterator iterator = *this;
		++(*this);
		return iterator;
	}
	ArrayIterator& operator--() noexcept { --this->m_current; return *this; }
	ArrayIterator operator--(int) noexcept
	{
		ArrayIterator iterator = *this;
		--(*this);
		return iterator;
	}
};

template<typename Array>
class ArrayReverseIterator : public BaseArrayIterator<Array>
{
public:
	using BaseIterator = BaseArrayIterator<Array>;
	using ValueType = typename Array::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	ArrayReverseIterator() noexcept : BaseIterator() {}
	explicit ArrayReverseIterator(PointerType ptr, size_t size = 0) noexcept : BaseIterator(ptr, size) {}

	ArrayReverseIterator& operator++() noexcept { --this->m_current; return *this; }
	ArrayReverseIterator operator++(int) noexcept
	{
		ArrayReverseIterator iterator = *this;
		--(*this);
		return iterator;
	}
	ArrayReverseIterator& operator--() noexcept { ++this->m_current; return *this; }
	ArrayReverseIterator operator--(int) noexcept
	{
		ArrayReverseIterator iterator = *this;
		++(*this);
		return iterator;
	}
};

template<typename T, size_t size>
class Array
{
public:
	using ValueType = T;
	using Iterator = ArrayIterator<Array<T, size>>;
	using ReverseIterator = ArrayReverseIterator<Array<T, size>>;
public:
	//Constructors
	Array()
	{
		for (size_t i = 0; i < size; ++i)
			m_data[i] = 0;
	}

	Array(std::initializer_list<T> list) : Array()
	{
		if (list.size() > size)
			throw std::out_of_range("Too many elements in initializer_list");

		auto it = list.begin();
		for (size_t i = 0; i < list.size(); ++i) {
			m_data[i] = *it;
			++it;
		}
	}

	// Element access
	const T& operator[](size_t index) const
	{
		if (index >= size)
			throw std::out_of_range{ "Index out of range: " + std::to_string(index) };
		return m_data[index];
	};

	T& operator[](size_t index)
	{
		return const_cast<T&>(std::as_const(*this)[index]);
	};

	T* Data() noexcept
	{
		return m_data;
	}

	const T* Data() const noexcept
	{
		return m_data;
	}

	//Capacity
	size_t Size() const noexcept
	{
		return size;
	};

	bool Empty() const noexcept
	{
		return size == 0;
	};

	//Operations
	void Fill(const T& value)
	{
		for (size_t i = 0; i < size; ++i) {
			m_data[i] = value;
		}
	}

	void Swap(Array& other) noexcept
	{
		std::swap(m_data, other.m_data);
	}

	//Iterators
	Iterator begin() { return Iterator(m_data); };
	Iterator end() { return Iterator(m_data, size); }
	ReverseIterator rbegin() { return ReverseIterator(m_data, size - 1); }
	ReverseIterator rend() { return ReverseIterator(m_data - 1); }

private:
	T m_data[size];
};

#endif //_ARRAY_
