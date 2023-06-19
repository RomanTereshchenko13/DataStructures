#ifndef _LINKEDLIST_
#define _LINKEDLIST_

template<typename LinkedList>
class BaseListIterator
{
public:
	using ValueType = typename LinkedList::ValueType;
	using NodePtr = typename LinkedList::NodePtr;
	using ReferenceType = ValueType&;
public:
	BaseListIterator() noexcept : m_current(nullptr) {}
	explicit BaseListIterator(NodePtr ptr) noexcept : m_current(ptr) {}
	bool operator==(const BaseListIterator& other) const noexcept { return m_current == other.m_current; }
	bool operator!=(const BaseListIterator& other) const noexcept { return m_current != other.m_current; }
	ReferenceType Value() const noexcept { return m_current->data; }
protected:
	NodePtr m_current;
};

template<typename LinkedList>
class ListConstIterator : public BaseListIterator<LinkedList>
{
public:
	using BaseIterator = BaseListIterator<LinkedList>;
	using ValueType = typename LinkedList::ValueType;
	using NodePtr = typename LinkedList::NodePtr;
	using ReferenceType = const ValueType&;
public:
	ListConstIterator() noexcept : BaseIterator() {}
	explicit ListConstIterator(NodePtr ptr) noexcept : BaseIterator(ptr) {}
	ReferenceType operator*() const noexcept { return this->m_current->data; }
	ListConstIterator& operator++() noexcept { this->m_current = this->m_current->next; return *this; }
	ListConstIterator operator++(int) noexcept { NodePtr tempNode{ *this }; this->m_current = this->m_current->next; return tempNode; }
	ListConstIterator& operator--() noexcept { this->m_current = this->m_current->previous; return *this; }
	ListConstIterator operator--(int) noexcept { NodePtr tempNode{ *this }; this->m_current = this->m_current->previous; return tempNode; }
};

template<typename LinkedList>
class ListIterator : public BaseListIterator<LinkedList>
{
public:
	using BaseIterator = BaseListIterator<LinkedList>;
	using ValueType = typename LinkedList::ValueType;
	using NodePtr = typename LinkedList::NodePtr;
	using ReferenceType = ValueType&;
public:
	ListIterator() noexcept : BaseIterator() {}
	explicit ListIterator(NodePtr ptr) noexcept : BaseIterator(ptr) {}
	ReferenceType operator*() noexcept { return this->m_current->data; }
	ListIterator& operator++() noexcept 
	{ 
		this->m_current = this->m_current->next; 
		return *this; 
	}
	ListIterator operator++(int) noexcept 
	{ 
		ListIterator iterator = *this;
		++(*this);
		return iterator;
	}
	ListIterator& operator--() noexcept 
	{ 
		this->m_current = this->m_current->previous; 
		return *this; 
	}
	ListIterator operator--(int) noexcept 
	{ 
		ListIterator iterator = *this;
		--(*this);
		return iterator;
	}
};

template<typename LinkedList>
class ListReverseIterator : public BaseListIterator<LinkedList>
{
public:
	using BaseIterator = BaseListIterator<LinkedList>;
	using ValueType = typename LinkedList::ValueType;
	using NodePtr = typename LinkedList::NodePtr;
	using ReferenceType = ValueType&;
public:
	ListReverseIterator() noexcept : BaseIterator() {}
	explicit ListReverseIterator(NodePtr ptr) noexcept : BaseIterator(ptr) {}
	ReferenceType operator*() noexcept { return this->m_current->data; }
	ListReverseIterator& operator++() noexcept
	{
		this->m_current = this->m_current->previous;
		return *this;
	}
	ListReverseIterator operator++(int) noexcept
	{
		ListReverseIterator iterator = *this;
		++(*this);
		return iterator;
	}
	ListReverseIterator& operator--() noexcept
	{
		this->m_current = this->m_current->next;
		return *this;
	}
	ListReverseIterator operator--(int) noexcept
	{
		ListReverseIterator iterator = *this;
		--(*this);
		return iterator;
	}
};

template<typename T>
class LinkedList
{
private:
	struct Node {
		Node() : data{ 0 }, next{ nullptr }, previous{ nullptr } {}
		Node(const T& value) : data{ value }, next{ nullptr }, previous{ nullptr } {}
		T data;
		Node* next;
		Node* previous;
	};

public:
	using ValueType = T;
	using NodePtr = Node*;
	using Iterator = ListIterator<LinkedList<T>>;
	using ConstIterator = ListConstIterator<LinkedList<T>>;
	using ReverseIterator = ListReverseIterator<LinkedList<T>>;
public:
	//Constructors
	LinkedList()
		: m_head(nullptr), m_tail(nullptr), m_size(0) {}

	LinkedList(size_t count, const T& value) : LinkedList()
	{
		while (count > 0) {
			PushBack(value);
			--count;
		}
	}

	LinkedList(std::initializer_list<T> list) : LinkedList()
	{
		for (const auto& element : list)
			PushBack(element);
	}

	~LinkedList()
	{
		Clear();
	}

	LinkedList(const LinkedList& other) : LinkedList()
	{
		for (ConstIterator it = other.cbegin(); it != other.cend(); ++it) {
			PushBack(*it);
		}
	}

	LinkedList(LinkedList&& other) noexcept
		: m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size)
	{
		other.m_head = nullptr;
		other.m_tail = nullptr;
		other.m_size = 0;
	}

	//Modifiers
	void PushBack(const T& value)
	{
		NodePtr tempNode{ m_tail };
		m_tail = new Node{ value };
		++m_size;
		if (tempNode) {
			tempNode->next = m_tail;
			m_tail->previous = tempNode;
		}
		else {
			m_head = m_tail;
		}
	}

	void PushFront(const T& value)
	{
		NodePtr tempNode{ m_head };
		m_head = new Node{ value };
		++m_size;

		if (tempNode) {
			tempNode->previous = m_head;
			m_head->next = tempNode;
		}
		else {
			m_tail = m_head;
		}
	}

	template<typename... Args>
	void EmplaceBack(Args&&... args)
	{
		NodePtr tempNode{ m_tail };
		m_tail = new Node(std::forward<Args>(args)...);
		++m_size;
		if (tempNode) {
			tempNode->next = m_tail;
			m_tail->previous = tempNode;
		}
		else {
			m_head = m_tail;
		}
	}

	template<typename... Args>
	void EmplaceFront(Args&&... args)
	{
		NodePtr tempNode{ m_head };
		m_head = new Node(std::forward<Args>(args)...);
		++m_size;

		if (tempNode) {
			tempNode->previous = m_head;
			m_head->next = tempNode;
		}
		else {
			m_tail = m_head;
		}
	}

	void PopBack()
	{
		NodePtr tempNode{ m_tail };
		if (tempNode == m_head) {
			m_tail = m_head = nullptr;
		}
		else {
			m_tail = tempNode->previous;
			m_tail->next = nullptr;
		}
		delete tempNode;
		--m_size;
	}

	void PopFront()
	{
		NodePtr tempNode{ m_head };
		if (tempNode == m_tail) {
			m_head = m_tail = nullptr;
		}
		else {
			m_head = tempNode->next;
			m_head->previous = nullptr;
		}
		delete tempNode;
		--m_size;
	}

	void Clear()
	{
		while (!Empty()) PopFront();
	}

	void Swap(LinkedList& other) noexcept
	{
		std::swap(m_head, other.m_head);
		std::swap(m_tail, other.m_tail);
		std::swap(m_size, other.m_size);
	}

	//Element access
	T& Front() const
	{
		return m_head->data;
	}

	T& Back() const
	{
		return m_tail->data;
	}

	bool Find(const T& value)
	{
		for (const auto& element : *this) {
			if (element == value)
				return true;
		}
		return false;
	}

	//Capacity
	size_t Size() const noexcept
	{
		return m_size;
	}

	bool Empty() const noexcept
	{
		return m_size == 0;
	}

	//Operators
	LinkedList& operator=(const LinkedList& other)
	{
		if (*this == other)
			return *this;

		LinkedList(other).Swap(*this);
		return *this;
	}

	LinkedList& operator=(LinkedList&& other) noexcept
	{
		m_head = other.m_head;
		m_tail = other.m_tail;
		m_size = other.m_size;

		other.m_head = nullptr;
		other.m_tail = nullptr;
		other.m_size = 0;

		return *this;
	}

	bool operator==(const LinkedList& other) const
	{
		if (m_size != other.m_size)
			return false;

		Node* currentNode = m_head;
		Node* otherCurrentNode = other.m_head;

		while (currentNode != nullptr && otherCurrentNode != nullptr) {
			if (currentNode->data != otherCurrentNode->data)
				return false;
			currentNode = currentNode->next;
			otherCurrentNode = otherCurrentNode->next;
		}
		return(currentNode == nullptr && otherCurrentNode == nullptr);
	}

	bool operator!=(const LinkedList& other) const
	{
		return !(*this == other);
	}

	//Iterators
	Iterator begin() { return Iterator(m_head); };
	Iterator end() { return Iterator(m_tail->next); };
	ConstIterator cbegin() const { return ConstIterator(m_head); };
	ConstIterator cend() const { return ConstIterator(m_tail->next); };
	ReverseIterator rbegin() { return ReverseIterator(m_tail); };
	ReverseIterator rend() { return ReverseIterator(m_head->previous); };

private:
	size_t m_size;
	NodePtr m_head;
	NodePtr m_tail;
};

#endif //_LINKEDLIST_