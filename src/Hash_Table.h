#include <iostream>

#include "list.h"

template <typename K, typename V>
class HashTable
{
public:
    virtual V& operator[](const K& key) = 0;
    virtual V& at(const K& key) = 0;
    virtual HashTable<K, V>& operator=(const HashTable<K, V>& other) = 0;
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual void insert(const K& key, const V& value) = 0;
    virtual void remove(const K& key) = 0;
};

template <typename K, typename V>
class SeparateChainingHashTable : public HashTable<K, V>
{
    List<K, V> *buckets = nullptr;
    size_t num_buckets = 0;
    size_t (* hashFunc)(const K& key);

public:
    SeparateChainingHashTable(size_t num_buckets, size_t (*hashFunc)(const K& key))
        : num_buckets(num_buckets), hashFunc(hashFunc)
    {
        buckets = new List<K, V>[num_buckets];
    }

    ~SeparateChainingHashTable()
    {
        for (size_t i = 0; i < num_buckets; i++)
            buckets[i].clear();

        delete[] buckets;
    }

    V& operator[](const K& key)
    {
        return this->at(key);
    }

    V& at(const K& key)
    {
        ListNode<K, V>* node = buckets[hashFunc(key) % num_buckets].search(key);

        if (node == nullptr)
        {
            throw "Invalid key!";
        }
        else
        {
            return node->val;
        }
    }

    SeparateChainingHashTable<K, V>& operator=(const SeparateChainingHashTable<K, V>& other)
    {
        if (&other == this)
            return *this;

        num_buckets = other.num_buckets;
        hashFunc = other.hashFunc;

        delete[] buckets;
        buckets = new List<K, V>[num_buckets];

        for (size_t i = 0; i < num_buckets; i++)
            buckets[i] = other.buckets[i];

        return *this;
    }

    HashTable<K, V>& operator=(const HashTable<K, V>& other)
    {
        const SeparateChainingHashTable<K, V>* _other =
            dynamic_cast<const SeparateChainingHashTable<K, V>*>(&other);

        *this = *_other;

        return *this;
    }

    class iterator
    {
        SeparateChainingHashTable<K, V>* p;
        ListNode<K, V>* node;
        size_t idx;

    public:
        iterator(SeparateChainingHashTable* p, ListNode<K, V>* n, size_t idx)
            : p(p), node(n), idx(idx) {}

        iterator& operator++() {
            if (node->next != nullptr)
                node = node->next;
            else
            {
                idx++;

                while (idx != p->num_buckets && p->buckets[idx].length() == 0)
                    idx++;

                if (idx == p->num_buckets)
                    node = nullptr;
                else
                    node = p->buckets[idx].root;
            }

            return *this;
        }

        iterator operator++(int)
        {
            iterator i = *this;

            ++(*this);

            return i;
        }

        bool operator!=(const iterator& i) const
        {
            return (p != i.p) || (node != i.node) || (idx != i.idx);
        }

        bool operator==(const iterator& i) const
        {
            return (p == i.p) && (node == i.node) && (idx == i.idx);
        }

        V& operator*() const
        {
            return node->val;
        }

        V* operator->() const
        {
            return &node->val;
        }
    };

    iterator begin()
    {
        size_t idx = 0;

        while (idx != num_buckets && buckets[idx].length() == 0)
            idx++;

        iterator i(this, buckets[idx].root, idx);

        return i;
    }

    iterator end()
    {
        iterator i(this, nullptr, num_buckets);

        return i;
    }

    size_t size()
    {
        size_t size = 0;

        for (size_t i = 0; i < num_buckets; i++)
            size += buckets[i].length();

        return size;
    }

    bool empty()
    {
        return size() == 0;
    }

    void insert(const K& key, const V& value)
    {
        buckets[hashFunc(key) % num_buckets].append(key, value);
    }

    void remove(const K& key)
    {
        buckets[hashFunc(key) % num_buckets].remove(key);
    }

    void print()
    {
        for (size_t i = 0; i < num_buckets; i++)
        {
            std::cout << "Bucket #" << i << ":\n";
            buckets[i].print();
        }
    }
};
