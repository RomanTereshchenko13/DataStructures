#ifndef _BINARYTREE_
#define _BINARYTREE_

template<typename BinaryTree>
class BaseTreeIterator
{
public:
	using ValueType = typename BinaryTree::ValueType;
	using NodePtr = typename BinaryTree::NodePtr;
	using ReferenceType = ValueType&;
	using PointerType = ValueType*;
public:
	// Constructors
	BaseTreeIterator() noexcept : m_ptr(nullptr) {}
	explicit BaseTreeIterator(NodePtr ptr) noexcept : m_ptr(ptr) {}

	// Dereference operator
	ReferenceType operator*() const noexcept { return m_ptr->data; }

	// Member access operator
	PointerType operator->() const noexcept { return &(m_ptr->data); }

	// Equality operators
	bool operator==(const BaseTreeIterator& other) const noexcept { return m_ptr == other.m_ptr; }
	bool operator!=(const BaseTreeIterator& other) const noexcept { return !(*this == other); }
protected:
	NodePtr m_ptr;
};

template<typename BinaryTree>
class TreeIterator : public BaseTreeIterator<BinaryTree>
{
public:
	using BaseIterator = BaseTreeIterator<BinaryTree>;
	using ValueType = typename BinaryTree::ValueType;
	using NodePtr = typename BinaryTree::NodePtr;
	using ReferenceType = ValueType&;
	using PointerType = ValueType*;
public:
	// Constructors
	TreeIterator() noexcept :BaseIterator() {}
	explicit TreeIterator(NodePtr ptr) noexcept : BaseIterator(ptr) {}

	// Increment operators
	TreeIterator& operator++() noexcept
	{
		if (this->m_ptr->right != nullptr) {
			// If there is a right subtree, find the minimum element in it
			this->m_ptr = BinaryTree::FindMin(this->m_ptr->right);
		}
		else {
			// Otherwise, go up to the nearest ancestor whose left child is also an ancestor of the current node
			NodePtr prevNode = this->m_ptr;
			this->m_ptr = this->m_ptr->parent;
			//this->m_ptr = this->m_ptr->parent;
			while (this->m_ptr != nullptr && this->m_ptr->right == prevNode) {
				prevNode = this->m_ptr;
				this->m_ptr = this->m_ptr->parent;
			}
		}

		return *this;
	}

	TreeIterator operator++(int) noexcept
	{
		TreeIterator iterator = *this;
		++(*this);
		return iterator;
	}

	TreeIterator& operator--()
	{
		if (this->m_ptr == nullptr) {
			// If the iterator is already at the end, move it to the maximum element in the tree
			this->m_ptr = BinaryTree::FindMax(this->m_ptr);
		}
		else if (this->m_ptr->left != nullptr) {
			// If there is a left subtree, find the maximum element in it
			this->m_ptr = BinaryTree::FindMax(this->m_ptr->left);
		}
		else {
			// Otherwise, go up to the nearest ancestor whose left child is also an ancestor of the current node
			NodePtr prev = this->m_ptr;
			this->m_ptr = this->m_ptr->parent;
			while (this->m_ptr != nullptr && this->m_ptr->left == prev) {
				prev = this->m_ptr;
				this->m_ptr = this->m_ptr->parent;
			}
		}

		return *this;
	}

	TreeIterator operator--(int) noexcept
	{
		TreeIterator iterator = *this;
		--(*this);
		return iterator;
	}
};

template<typename BinaryTree>
class TreeReverseIterator : public BaseTreeIterator<BinaryTree>
{
public:
	using BaseIterator = BaseTreeIterator<BinaryTree>;
	using ValueType = typename BinaryTree::ValueType;
	using NodePtr = typename BinaryTree::NodePtr;
	using ReferenceType = ValueType&;
	using PointerType = ValueType*;
public:
	// Constructors
	TreeReverseIterator() noexcept :BaseIterator() {}
	explicit TreeReverseIterator(NodePtr ptr) noexcept : BaseIterator(ptr) {}

	// Increment operators
	TreeReverseIterator& operator++() noexcept {
		if (this->m_ptr->left != nullptr) {
			this->m_ptr = BinaryTree::FindMax(this->m_ptr->left);
		}
		else {
			NodePtr prev = this->m_ptr;
			this->m_ptr = this->m_ptr->parent;
			while (this->m_ptr != nullptr && this->m_ptr->left == prev) {
				prev = this->m_ptr;
				this->m_ptr = this->m_ptr->parent;
			}
		}
		return *this;
	}

	TreeReverseIterator operator++(int) noexcept {
		TreeReverseIterator iterator = *this;
		++(*this);
		return iterator;
	}

	TreeReverseIterator& operator--() {
		if (this->m_ptr == nullptr) {
			this->m_ptr = BinaryTree::FindMin(this->m_ptr->right);
		}
		else if (this->m_ptr->right != nullptr) {
			this->m_ptr = BinaryTree::FindMin(this->m_ptr->right);
		}
		else {
			NodePtr prev = this->m_ptr;
			this->m_ptr = this->m_ptr->parent;
			while (this->m_ptr != nullptr && this->m_ptr->right == prev) {
				prev = this->m_ptr;
				this->m_ptr = this->m_ptr->parent;
			}
		}
		return *this;
	}

	TreeReverseIterator operator--(int) noexcept {
		TreeReverseIterator iterator = *this;
		--(*this);
		return iterator;
	}
};

template<typename T>
class BinaryTree
{
private:
	struct Node
	{
		Node() : data{ 0 }, left{ nullptr }, right{ nullptr }, parent{ nullptr } {}
		Node(const T& value) : data{ value }, left{ nullptr }, right{ nullptr }, parent{ nullptr } {}
		T data;
		Node* left;
		Node* right;
		Node* parent;
	};

public:
	using ValueType = T;
	using NodePtr = Node*;
	using Iterator = TreeIterator<BinaryTree<T>>;
	using ReverseIterator = TreeReverseIterator<BinaryTree<T>>;
public:
	//Constructors
	BinaryTree() = default;

	BinaryTree(std::initializer_list<T> list)
	{
		for (const T& value : list)
			Insert(value);
	}

	BinaryTree(const BinaryTree& other)
	{
		Copy(root, other.root);
	}

	BinaryTree(BinaryTree&& other) noexcept :root(other.root)
	{
		other.root = nullptr;
	}

	~BinaryTree()
	{
		Clear();
	}

	//Operators
	BinaryTree& operator=(const BinaryTree& other)
	{
		if (this != &other) {
			Clear();
			Copy(root, other.root);
		}
		return *this;
	}

	BinaryTree operator=(BinaryTree&& other) noexcept
	{
		if (this != &other) {
			Clear();
			root = other.root;
			other.root = nullptr;
		}
		return *this;
	}

	bool operator==(const BinaryTree& other) const
	{
		return IsEqual(root, other.root);
	}

	bool operator!=(const BinaryTree& other) const
	{
		return !(*this == other);
	}

	//Modifiers
	bool Find(const T& value)
	{
		if (root == nullptr)
			return false;

		if (root->data == value)
			return true;

		Node* node = root;

		while (node != nullptr)
		{
			if (node->data == value)
				return true;
			else if (node->data > value) {
				node = node->left;
			}
			else {
				node = node->right;
			}
		}

		return false;
	}

	void Delete(const T& value)
	{
		root = Delete(root, value);
	}

	void Clear()
	{
		if (root != nullptr)
		{
			RemoveSubTree(root);
			root = nullptr;
		}
	}

	bool Insert(const T& value)
	{
		Node* newNode = new Node(value);

		if (root == nullptr)
		{
			root = newNode;
			return true;
		}

		Node* currentNode = root;
		Node* parentNode = nullptr;

		while (currentNode != nullptr)
		{
			parentNode = currentNode;

			if (currentNode->data == value)
			{
				return false;
			}
			else if (currentNode->data > value)
			{
				if (currentNode->left == nullptr)
				{
					currentNode->left = newNode;
					newNode->parent = parentNode;
					return true;
				}
				currentNode = currentNode->left;
			}
			else
			{
				if (currentNode->right == nullptr)
				{
					currentNode->right = newNode;
					newNode->parent = parentNode;
					return true;
				}
				currentNode = currentNode->right;
			}
		}

		return false;
	}


	//Capacity
	size_t Size() const noexcept
	{
		if (root == nullptr)
			return 0;
		return Size(root);
	}

	bool IsEmpty() const noexcept
	{
		return root == nullptr;
	}

	NodePtr GetRoot() const noexcept { return root; }

	Iterator begin() { return Iterator(FindMin(root)); }
	Iterator end() { return Iterator(nullptr); };
	ReverseIterator rbegin() { return ReverseIterator(FindMax(root)); }
	ReverseIterator rend() { return ReverseIterator(nullptr); };

	static NodePtr FindMin(NodePtr node) noexcept
	{
		if (node == nullptr)
			return nullptr;

		while (node->left != nullptr)
			node = node->left;

		return node;
	}

	static NodePtr FindMax(NodePtr node) noexcept
	{
		if (node == nullptr)
			return nullptr;

		while (node->right != nullptr)
			node = node->right;

		return node;
	}

private:
	void RemoveSubTree(Node* node)
	{
		if (node->left != nullptr)
		{
			RemoveSubTree(node->left);
		}

		if (node->right != nullptr)
		{
			RemoveSubTree(node->right);
		}

		delete node;
	}

	Node* Delete(Node* node, const T& value)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (value < node->data)
		{
			node->left = Delete(node->left, value);
		}
		else if (value > node->data)
		{
			node->right = Delete(node->right, value);
		}
		else
		{
			if (node->left == nullptr && node->right == nullptr)
			{
				delete node;
				node = nullptr;
			}
			else if (node->left == nullptr)
			{
				Node* temp = node->right;
				delete node;
				node = temp;
			}
			else if (node->right == nullptr)
			{
				Node* temp = node->left;
				delete node;
				node = temp;
			}
			else
			{
				Node* temp = FindMin(node->right);
				node->data = temp->data;
				node->right = Delete(node->right, temp->data);
			}
		}
		return node;
	}

	size_t Size(const Node* node) const
	{
		return node == nullptr ? 0 : Size(node->left) + 1 + Size(node->right);
	}

	void Copy(Node*& tree1, Node* const& tree2, Node* parent = nullptr)
	{
		if (tree2 == nullptr)
		{
			return;
		}
		tree1 = new Node{ tree2->data };
		tree1->parent = parent;
		Copy(tree1->left, tree2->left, tree1);
		Copy(tree1->right, tree2->right, tree1);
	}

	bool IsEqual(const Node* tree1, const Node* tree2) const
	{
		if (tree1 == nullptr && tree2 == nullptr)
			return true;

		if (tree1 == nullptr || tree2 == nullptr)
			return false;

		if (tree1->data != tree2->data)
			return false;

		return IsEqual(tree1->left, tree2->left) && IsEqual(tree1->right, tree2->right);
	}

private:
	Node* root = nullptr;
};



#endif //_BINARYTREE_