# C++ Hash Table Implementation
Welcome to the repository for a custom C++ hash table implementation. This project is dedicated to providing a high-performance, templated hash table for efficient key-value storage and retrieval.

## Features
- Templated Implementation: Create hash tables for any data type.
- Collision Resolution: Implements separate chaining to handle hash collisions gracefully.
- Custom Hash Functions: Supports user-defined hash functions to tailor performance based on specific data distributions.
- Iterator Support: Navigate through your hash table with standard C++ iterators.
- Performance Optimized: Built with performance and low memory footprint in mind.
- Exception Handling: Comprehensive error and exception management for reliability and ease of debugging

## Getting Started
To use the hash table in your project, simply clone the repository and include the Hash_Table.h file in your source code.

**git clone https://github.com/koapch-artem/HashTable.git**

***Here's a quick example to get you started:***

```
#include "Hash_Table.h"

int main() {
    HashTable<int, std::string> myHashTable;
    myHashTable.insert(1, "value1");
    myHashTable.insert(2, "value2");
    
    std::string value;
    if (myHashTable.find(1, value)) {
        std::cout << "Key 1 has value: " << value << std::endl;
    }

    return 0;
}
```

## Usage
***To create a hash table, simply define a HashTable object with the desired key and value types:***

```
HashTable<key_type, value_type> table;
```
You can then use the following member functions:

- insert: To insert a new key-value pair.
- remove: To delete a key-value pair by its key.
- find: To retrieve the value associated with a given key.
- clear: To remove all key-value pairs from the hash table.
- size: To get the number of stored key-value pairs.

## Contributing
We welcome contributions to this project! If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".

Don't forget to give the project a star! Thanks again!

- Fork the Project
- Create your Feature Branch (git checkout -b feature/AmazingFeature)
- Commit your Changes (git commit -m 'Add some AmazingFeature')
- Push to the Branch (git push origin feature/AmazingFeature)
- Open a Pull Request


## License
Distributed under the MIT License. See LICENSE for more information.

## Contact
Your Name – @kopach-artem – kopach.artem@edu.bme.hu

Project Link: https://github.com/kopach-artem/HashTable
