#ifndef _VECTOR_
#define _VECTOR_

#include<stdexcept>
#include<utility>

template<typename Vector>
class BaseVecIterator
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	BaseVecIterator() noexcept : m_current(nullptr) {}
	explicit BaseVecIterator(PointerType ptr) noexcept : m_current(ptr) {}

	PointerType operator->() const noexcept { return m_current; }
	ReferenceType operator*() const noexcept { return *m_current; }

	bool operator==(const BaseVecIterator& other) const noexcept { return m_current == other.m_current; }
	bool operator!=(const BaseVecIterator& other) const noexcept { return m_current != other.m_current; }

	ReferenceType operator[](int index) const noexcept { return *(m_current + index); }

protected:
	PointerType m_current;
};

template<typename Vector>
class VecIterator : public BaseVecIterator<Vector>
{
public:
	using BaseIterator = BaseVecIterator<Vector>;
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VecIterator() noexcept : BaseIterator() {}
	explicit VecIterator(PointerType ptr) noexcept : BaseIterator(ptr) {}

	VecIterator& operator++() noexcept { ++this->m_current; return *this; }
	VecIterator operator++(int) noexcept {
		VecIterator iterator = *this;
		++(*this);
		return iterator;
	}
	VecIterator& operator--() noexcept { --this->m_current; return *this; }
	VecIterator operator--(int) noexcept {
		VecIterator iterator = *this;
		--(*this);
		return iterator;
	}
};

template<typename Vector>
class VecReverseIterator : public BaseVecIterator<Vector>
{
public:
	using BaseIterator = BaseVecIterator<Vector>;
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VecReverseIterator() noexcept : BaseIterator() {}
	explicit VecReverseIterator(PointerType ptr) noexcept : BaseIterator(ptr) {}

	VecReverseIterator& operator++() noexcept { --this->m_current; return *this; }
	VecReverseIterator operator++(int) noexcept {
		VecReverseIterator iterator = *this;
		--(*this);
		return iterator;
	}
	VecReverseIterator& operator--() noexcept { ++this->m_current; return *this; }
	VecReverseIterator operator--(int) noexcept {
		VecReverseIterator iterator = *this;
		++(*this);
		return iterator;
	}
};

template<typename T>
class Vector
{
public:
	using ValueType = T;
	using Iterator = VecIterator<Vector<T>>;
	using ReverseIterator = VecReverseIterator<Vector<T>>;
public:
	//Constructors
	Vector()
		: m_data{ new T[1] }, m_size{ 0 }, m_capacity{ 1 } {};

	Vector(size_t size, const T& value)
		: m_data{ new T[size] {} }, m_size{ size }, m_capacity{ size * 2 }
	{
		for (size_t i = 0; i < m_size; ++i)
			m_data[i] = value;
	}

	Vector(std::initializer_list<T> list)
		: m_data{ new T[list.size()] }, m_size(list.size()), m_capacity(list.size() * 2)
	{
		size_t index = 0;
		for (const auto& element : list) {
			if (index < m_size)
				m_data[index++] = std::move(element);
			else
				throw std::runtime_error("Buffer overrun detected!");
		}
	}

	~Vector()
	{
		Clear();
	}

	//Copy Constructor
	Vector(const Vector& other) : Vector()
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		for (size_t i = 0; i < m_size; ++i)
			m_data[i] = other.m_data[i];
	}

	//Move Constructor
	Vector(Vector&& other) noexcept
		:m_size(other.m_size), m_data(other.m_data), m_capacity(other.m_capacity)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 1;
	}

	//Operators
	const T& operator[](size_t index) const
	{
		if (index >= m_size)
			throw std::out_of_range("index out of range");
		return m_data[index];
	}

	//Index operator using  "const-and-back-again" idiom
	T& operator[](size_t index)
	{
		return const_cast <T&>(std::as_const(*this)[index]);
	}

	//Copy assigment operator using "copy and swap" idiom
	Vector& operator=(const Vector& other)
	{
		Vector copy(other);
		Swap(copy);
		return *this;
	}
	//Move assigment operator using "move and swap" idiom
	Vector& operator=(Vector&& other) noexcept
	{
		Vector moved(std::move(other));
		Swap(moved);
		return *this;
	}

	bool operator==(const Vector& other) const
	{
		if (m_size != other.m_size)
			return false;

		for (size_t i = 0; i < m_size; ++i) {
			if (m_data[i] != other.m_data[i])
				return false;
		}

		return true;
	}

	bool operator!=(const Vector& other) const
	{
		return !(*this == other);
	}

	//Capacity
	constexpr bool Empty() const noexcept
	{
		return m_size == 0;
	}
	constexpr size_t Size() const noexcept
	{
		return m_size;
	}
	constexpr size_t Capacity() const noexcept
	{
		return m_capacity;
	}

	//Modifiers
	constexpr void PushBack(const T& value)
	{
		if (m_size >= m_capacity)
			Realloc(m_capacity + m_capacity / 2);

		m_data[m_size] = value;
		m_size++;
	}
	constexpr void PushBack(T&& value)
	{
		if (m_size >= m_capacity)
			Realloc(m_capacity * 2);

		m_data[m_size] = std::move(value);
		m_size++;
	}
	template<typename... Args>
	constexpr T& EmplaceBack(Args&&... args)
	{
		if (m_size >= m_capacity)
			Realloc(m_capacity * 2);
		new(&m_data[m_size]) T(std::forward<Args>(args)...);
		return m_data[m_size++];
	}
	constexpr void PopBack()
	{
		if (m_size > 0) {
			m_size--;
			m_data[m_size].~T();
		}
	}

	//Operations
	constexpr void Clear() noexcept
	{
		while (!Empty()) PopBack();
	}
	constexpr void Swap(Vector& other) noexcept
	{
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_data, other.m_data);
	}

	//Iterators
	Iterator begin() { return Iterator(m_data); };
	Iterator end() { return Iterator(m_data + m_size); };
	ReverseIterator rbegin() { return ReverseIterator(m_data + m_size - 1); };
	ReverseIterator rend() { return ReverseIterator(m_data - 1); };

private:
	void Realloc(size_t newCapacity)
	{
		T* newData = (T*)::operator new(newCapacity * sizeof(T));
		if (newCapacity < m_size)
			m_size = newCapacity;

		for (size_t i = 0; i < m_size; ++i)
			newData[i] = std::move(m_data[i]);

		for (size_t i = 0; i < m_size; ++i)
			m_data[i].~T();

		::operator delete (m_data, m_capacity * sizeof(T));
		m_data = newData;
		m_capacity = newCapacity;
	}

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
};

#endif //_VECTOR_