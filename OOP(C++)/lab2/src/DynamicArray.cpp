#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <cstring>

#include "DynamicArray.h"


DynamicArray::DynamicArray() : data(nullptr), size(0), capacity(0) {}

DynamicArray::DynamicArray(const std::string &a) : data(nullptr), size(0), capacity(0)
{
    for (int i = 0; i < a.length(); i++)
    {
        this->push_back(a[i]);
    }
}

DynamicArray::DynamicArray(const std::initializer_list<unsigned char> &t) : data(nullptr), size(t.size()), capacity(t.size())
{
    for (const unsigned char &value : t)
    {
        this->push_back(value);
    }
}

DynamicArray::DynamicArray(const size_t &n, unsigned char t) : data(nullptr), size(n), capacity(n)
{
    for (int i = 0; i < n; i++)
    {
        this->push_back(t);
    }
}

DynamicArray::DynamicArray(const DynamicArray &other) : data(nullptr), size(other.size), capacity(other.capacity)
{
    data = new unsigned char[capacity];
    for (int i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

DynamicArray::~DynamicArray()
{
    
}

void DynamicArray::push_front(unsigned char value)
{
    if (capacity == size)
    {
        capacity += 1;
    }

    unsigned char *newData = new unsigned char[capacity + 1];

    for (int i = 0; i < size; i++)
    {
        newData[i + 1] = data[i];
    }

    newData[0] = value;

    delete[] data;
    data = newData;
    size++;
}

void DynamicArray::del_front()
{
    if (size <= 0)
    {
        return;
    }

    unsigned char *newData = new unsigned char[capacity];

    for (int i = 1; i < size; i++)
    {
        newData[i - 1] = data[i];
    }

    delete[] data;
    data = newData;
    size--;
}

void DynamicArray::push_back(unsigned char value)
{
    if (capacity == size)
    {
        capacity += 1;
    }

    unsigned char *newData = new unsigned char[capacity];

    for (int i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    data[size++] = value;
}

int DynamicArray::get_size()
{
    return size;
}

unsigned char &DynamicArray::operator[](int index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

bool DynamicArray::operator==(const DynamicArray& other) const
{
    if (size != other.size)
        return false;

    for (int i = 0; i < size; i++)
    {
        if (data[i] != other.data[i])
            return false;
    }

    return true;
}

unsigned char *DynamicArray::begin()
{
    return data;
}

unsigned char *DynamicArray::end()
{
    return data + size;
}
