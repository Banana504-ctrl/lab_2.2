#include "DynamicArray.h"

template <class T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0) {}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (count == 0) {
        data = nullptr;
        size = 0;
        return;
    }
    
    data = new T[count];
    for (int i = 0; i < count; ++i) {
        data[i] = items[i];
    }
    size = count;
}

template <class T>
DynamicArray<T>::DynamicArray(int size) {
    if (size < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (size == 0) {
        data = nullptr;
        this->size = 0;
        return;
    }
    
    data = new T[size];
    this->size = size;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) 
    : size(other.size) 
{
    if (size == 0) {
        data = nullptr;
        return;
    }
    
    data = new T[size];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <class T>
T DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= size) {
        throw ErrorCode::INDEX_OUT_OF_RANGE;
    }
    return data[index];
}


template <class T>
int DynamicArray<T>::GetSize() const {
    return size;
}

template <class T>
void DynamicArray<T>::Set(int index, T value) {
    if (index < 0 || index >= size) {
        throw ErrorCode::INDEX_OUT_OF_RANGE;
    }
    data[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (newSize == 0) {
        delete[] data;
        data = nullptr;
        size = 0;
        return;
    }
    
    T* newData = new T[newSize];
    int elementsToCopy = (newSize < size) ? newSize : size;
    
    for (int i = 0; i < elementsToCopy; ++i) {
        newData[i] = data[i];
    }
    
    delete[] data;
    data = newData;
    size = newSize;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this == &other) return *this;
    
    delete[] data;
    
    size = other.size;
    
    if (size == 0) {
        data = nullptr;
        return *this;
    }
    
    data = new T[size];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
    
    return *this;
}