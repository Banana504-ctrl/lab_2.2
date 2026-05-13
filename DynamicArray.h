#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "errors.h"

template <class T>
class DynamicArray {
private:
    T* data;
    int size;

    void copyFrom(const DynamicArray<T>& other);
    void free();

public:
    DynamicArray();
    DynamicArray(T* items, int count);
    explicit DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& other);
    ~DynamicArray();

    T Get(int index) const;
    int GetSize() const;
    void Set(int index, T value);
    void Resize(int newSize);

    DynamicArray<T>& operator=(const DynamicArray<T>& other);
};

#include "DynamicArray.cpp"
#endif