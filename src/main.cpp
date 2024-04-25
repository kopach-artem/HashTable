#include <string>
#include <iostream>

#include "Hash_Table.h"

#include "gtest_lite.h"

template <class T>
inline T _rotl(T x, uint8_t r) {
      asm("roll %1,%0" : "+r" (x) : "c" (r));
      return x;
}

size_t hashFunc1(const std::string& s)
{
    size_t length = s.length();
    unsigned int h = 0;

    for (size_t i = 0; i < length; i++)
    {
        h = _rotl(h, 1) ^ s[i];
    }
    return h;
}

int main()
{
    SeparateChainingHashTable<std::string, std::string> h(3, hashFunc1);
    SeparateChainingHashTable<std::string, std::string> h2(7, hashFunc1);

    std::cout << "size = " << h.size() << '\n';

    h.insert("John Smith", "521-1234");
    h.insert("Ted Baker", "123-1234");
    h.insert("Sam Doe", "456-1234");
    h.insert("Lisa Smith", "789-1234");
    h.insert("Sandra Doe", "012-1234");
    std::cout << "size = " << h.size() << '\n';
    TEST(HashTableTest, SizeAfterInsert) {
        EXPECT_EQ(h.size(), 5);
    } ENDM
    TEST(HashTableTest, InsertAndAt) {
        EXPECT_EQ(h["John Smith"], "521-1234");
        EXPECT_EQ(h["Ted Baker"], "123-1234");
        EXPECT_EQ(h["Sam Doe"], "456-1234");
        EXPECT_EQ(h["Lisa Smith"], "789-1234");
        EXPECT_EQ(h["Sandra Doe"], "012-1234");
    } ENDM
    std::cout << h["John Smith"] << '\n';
    std::cout << h["Ted Baker"] << '\n';
    std::cout << h["Sam Doe"] << '\n';
    std::cout << h["Lisa Smith"] << '\n';
    std::cout << h["Sandra Doe"] << '\n';

    h["Sandra Doe"] = "1234";
    TEST(HashTableTest, Rewrite) {
        EXPECT_EQ(h["Sandra Doe"], "1234");
    } ENDM

    std::cout << h["Sandra Doe"] << '\n';

    try
    {
        std::cout << h["Ted Doe"] << '\n';
    }
    catch (const char* msg)
    {
        std::cout << msg << '\n';
    }

    std::cout << "h:\n";
    h.print();
    h2 = h;
    std::cout << "h2:\n";
    h2.print();

    h.remove("Sam Doe");

    std::cout << '\n';
    h.print();

    h.remove("Sam Doe");
    h.remove("John Smith");
    h.remove("Sandra Doe");

    TEST(HashTableTest, Size2) {
        EXPECT_EQ(h.size(), 2);
    } ENDM

    std::cout << '\n';
    h.print();
    std::cout << '\n';

    for (decltype(h)::iterator it = h.begin(); it != h.end(); it++)
    {
        std::cout << *it << '\n';
    }
}
