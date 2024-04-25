template <typename K, typename V>
struct ListNode
{
	K key;
	V val;
	ListNode<K, V>* next = nullptr;

	ListNode(const K& Key, const V& Val);
};

template <typename K, typename V>
ListNode<K, V>::ListNode(const K& Key, const V& Val)
	: key(Key), val(Val), next(nullptr)
{}

template <typename K, typename V>
struct List
{
	ListNode<K, V>* root = nullptr;
	size_t size = 0;

	void append(const K& Key, const V& Val);
	void remove(const K& Key);
	void clear();
	size_t length();
	ListNode<K, V>* search(const K& Key);
	List<K, V>& operator=(const List<K, V>& other);
	ListNode<K, V>* last();
	void print();
};

template<typename K, typename V>
List<K, V>& List<K, V>::operator=(const List<K, V>& other)
{
	clear();

	if (other.root != nullptr)
	{
		ListNode<K, V>* node = other.root;
		ListNode<K, V>* prev = nullptr;

		while (node != nullptr)
		{
			ListNode<K, V>* new_node = new ListNode<K, V>(node->key, node->val);

			if (prev == nullptr)
				root = new_node;
			else
				prev->next = new_node;

			prev = new_node;
			node = node->next;
		}
	}

	return *this;
}

template<typename K, typename V>
size_t List<K, V>::length()
{
	return size;
}

template<typename K, typename V>
void List<K, V>::clear()
{
	if (root != nullptr)
	{
		ListNode<K, V>* node = root;

		while (node != nullptr)
		{
			ListNode<K, V>* tmp = node;

			node = node->next;
			delete tmp;
		}
	}

	root = nullptr;

	size = 0;
}

template<typename K, typename V>
void List<K, V>::append(const K& Key, const V& Val)
{
	ListNode<K, V>* new_node = new ListNode<K, V>(Key, Val);

	if (root == nullptr)
	{
		root = new_node;
	}
	else
	{
		ListNode<K, V>* node = root;

		while (node->next != nullptr)
			node = node->next;

		node->next = new_node;
	}

	size++;
}

template<typename K, typename V>
void List<K, V>::remove(const K& Key)
{
	if (root != nullptr)
	{
		ListNode<K, V>* node = root;
		ListNode<K, V>* prev = nullptr;

		while (node != nullptr)
		{
			if (node->key == Key)
			{
				if (prev == nullptr)
					root = node->next;
				else if (node->next != nullptr)
					prev->next = node->next;
				else
					prev->next = nullptr;

				delete node;
				size--;

				return;
			}

			prev = node;
			node = node->next;
		}
	}
}

template<typename K, typename V>
ListNode<K, V>* List<K, V>::search(const K& Key)
{
	if (root != nullptr)
	{
		ListNode<K, V>* node = root;

		while (node != nullptr)
		{
			if (node->key == Key)
				return node;

			node = node->next;
		}
	}

	return nullptr;
}

template<typename K, typename V>
ListNode<K, V>* List<K, V>::last()
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		ListNode<K, V>* node = root;

		while (node->next != nullptr)
			node = node->next;

		return node;
	}
}

template<typename K, typename V>
void List<K, V>::print()
{
	if (root != nullptr)
	{
		ListNode<K, V>* node = root;

		while (node != nullptr)
		{
			std::cout << node->key << ": " << node->val << "\n";

			node = node->next;
		}
	}
}
