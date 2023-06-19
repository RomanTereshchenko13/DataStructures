#ifndef _HASHTABLE_
#define _HASHTABLE_

template<typename HashTable>
class HashIterator
{
public:
	using ValueType = typename HashTable::ValueType;
	using KeyType = typename HashTable::KeyType;
	using NodePtr = typename HashTable::NodePtr;
	using Table = typename HashTable::Table;
	using ReferenceType = ValueType&;
	using PointerType = ValueType*;

public:
	explicit HashIterator(NodePtr ptr, Table t, size_t s) noexcept
		: m_current(ptr), table(t), size(s), index(0)
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (table[i] != nullptr) {
				index = i;
				break;
			}
		}
	}

	ReferenceType operator*() const noexcept { return m_current->value; }

	const ReferenceType Value() const noexcept { return m_current->value; }
	const KeyType& Key() const noexcept { return m_current->key; }
	PointerType operator->() const noexcept { return &(m_current->value); }
	bool operator==(const HashIterator& other) const noexcept
	{
		return m_current == other.m_current;
	}
	bool operator!=(const HashIterator& other) const noexcept { return m_current != other.m_current; }
	HashIterator& operator++() noexcept {
		if (m_current->next != nullptr)
			m_current = m_current->next;
		else {
			index++;
			while (table[index] == nullptr)
				index++;
			m_current = (index == size) ? nullptr : table[index];
		}

		return *this;
	}
	HashIterator operator++(int) noexcept { NodePtr tempNode{ *this }; m_current = m_current->next; return tempNode; }
private:
	NodePtr m_current;
	Table table;
	size_t size;
	size_t index;
};

template<typename Key, typename Value>
class HashTable
{
private:
	struct Node
	{
		Node() : key{ 0 }, value{ 0 }, next{ nullptr } {}
		Node(Key k, Value v, Node* n = nullptr) : key{ k }, value{ v }, next{ n } {}
		Key key;
		Value value;
		Node* next;
	};

public:
	using ValueType = Value;
	using KeyType = Key;
	using NodePtr = Node*;
	using Table = Node**;
	using Iterator = HashIterator <HashTable<Key, Value>>;
public:
	//Constructors
	HashTable(size_t size = 10) : m_size(size), m_table(new Node* [size] {}) {}

	HashTable(const HashTable& other) : HashTable(other.m_size)
	{
		for (size_t i = 0; i < m_size; ++i) {
			if (other.m_table[i] != nullptr) {
				m_table[i] = new Node(other.m_table[i]->key, other.m_table[i]->value);
				Node* current = m_table[i];
				Node* otherCurrent = other.m_table[i]->next;
				while (otherCurrent) {
					current->next = otherCurrent;
					otherCurrent = otherCurrent->next;
				}
			}
		}
	}

	HashTable(HashTable&& other) noexcept
		: m_size(other.m_size), m_table(other.m_table)
	{
		other.m_size = 0;
		other.m_table = nullptr;
	}

	~HashTable()
	{
		Clear();
		delete[] m_table;
	}

	//Operators
	HashTable& operator=(const HashTable& other)
	{
		if (*this == other)
			return *this;

		HashTable(other).Swap(*this);
		return *this;
	}

	HashTable& operator=(HashTable&& other) noexcept
	{
		Clear();
		m_size = other.m_size;
		m_table = other.m_table;

		other.m_size = 0;
		other.m_table = nullptr;

		return *this;
	}

	bool operator==(const HashTable& other) const
	{
		if (m_size != other.m_size)
			return false;

		for (size_t i = 0; i < m_size; ++i) {
			Node* currentNode = m_table[i];
			Node* otherCurrentNode = other.m_table[i];

			while (currentNode != nullptr && otherCurrentNode != nullptr) {
				if (currentNode->key != otherCurrentNode->key || currentNode->value != otherCurrentNode->value)
					return false;
				currentNode = currentNode->next;
				otherCurrentNode = otherCurrentNode->next;
			}

			// If one list has more elements than the other
			if (currentNode != nullptr || otherCurrentNode != nullptr)
				return false;
		}

		return true;
	}

	bool operator!=(const HashTable& other) const
	{
		return !(*this == other);
	}

	Value& operator[](const Key& key)
	{
		size_t index = HashFunction(key);
		Node*& current = m_table[index];
		while (current != nullptr) {
			if (current->key == key)
				return current->value;
			current = current->next;
		}

		Node* newNode = new Node{ key, Value{} };
		m_table[index] = newNode;

		return newNode->value;
	}

	//Capacity
	size_t Size() const noexcept
	{
		return m_size;
	}

	bool IsEmpty() const noexcept
	{
		for (size_t index = 0; index < m_size; ++index) {
			Node* current = m_table[index];
			if (current != nullptr)
				return false;
		}
		return true;
	}

	size_t HashFunction(const Key& key) const
	{
		return std::hash<Key>()(key) % m_size;
	}

	//Modifiers
	void Clear()
	{
		for (size_t i = 0; i < m_size; ++i) {
			Node* current = m_table[i];
			while (current != nullptr) {
				Node* next = current->next;
				delete current;
				current = next;
				next = nullptr;
			}
			m_table[i] = nullptr;
		}
	}

	void Insert(const Key& key, const Value& value)
	{
		size_t index = HashFunction(key);
		Node* current = m_table[index];

		while (current != nullptr) {
			if (current->key == key) {
				current->value = value;
				return;
			}
			current = current->next;
		}

		Node* newNode = new Node{ key, value };

		if (m_table[index] == nullptr) {
			m_table[index] = newNode;
		}
		else {
			Node* last = m_table[index];
			while (last->next != nullptr) {
				last = last->next;
			}
			last->next = newNode;
		}
	}

	void Swap(HashTable& other) noexcept
	{
		std::swap(m_size, other.m_size);
		std::swap(m_table, other.m_table);
	}

	//Iterators
	Iterator begin()
	{
		for (size_t i = 0; i < m_size; ++i) {
			if (m_table[i] != nullptr)
				return Iterator(m_table[i], m_table, m_size);
		}
		return Iterator(nullptr, m_table, m_size);
	}

	Iterator end()
	{
		return Iterator(nullptr, m_table + m_size, m_size);
	}

private:
	Node** m_table;
	size_t m_size;
};

#endif //_HASHTABLE__