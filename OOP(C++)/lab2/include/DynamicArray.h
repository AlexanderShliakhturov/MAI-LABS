#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <string>
#include <initializer_list>

class DynamicArray
{
private:
    unsigned char *data;
    int size;
    int capacity;

public:
    DynamicArray();
    DynamicArray(const std::string &a);
    DynamicArray(const std::initializer_list<unsigned char> &t);
    DynamicArray(const size_t &n, unsigned char t = 0);
    DynamicArray(const DynamicArray &other);
    ~DynamicArray();
    void push_front(unsigned char value);
    void del_front();
    void push_back(unsigned char value);
    int get_size();
    unsigned char &operator[](int index);
    bool operator==(const DynamicArray& other) const;
    unsigned char *begin();
    unsigned char *end();
};

#endif // DYNAMICARRAY_H
