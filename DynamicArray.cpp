#include "DynamicArray.h"

template <class T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0) {}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (count == 0) {
        data = nullptr;
        size = 0;
        capacity = 0;
        return;
    }
    
    size = count;
    capacity = count;
    data = new T[capacity];
    for (int i = 0; i < count; ++i) {
        data[i] = items[i];
    }
}

template <class T>
DynamicArray<T>::DynamicArray(int capacity) {
    if (capacity < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    this->capacity = capacity;
    this->size = 0;
    
    if (capacity == 0) {
        data = nullptr;
    } else {
        data = new T[capacity];
    }
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) 
    : size(other.size), capacity(other.capacity) 
{
    if (capacity == 0) {
        data = nullptr;
        return;
    }
    
    data = new T[capacity];
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
int DynamicArray<T>::GetCapacity() const {
    return capacity;
}

template <class T>
void DynamicArray<T>::Set(int index, T value) {
    if (index < 0 || index >= size) {
        throw ErrorCode::INDEX_OUT_OF_RANGE;
    }
    data[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(int newCapacity) {
    if (newCapacity < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (newCapacity == 0) {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
        return;
    }
    
    T* newData = new T[newCapacity];
    int elementsToCopy = (newCapacity < size) ? newCapacity : size;
    
    for (int i = 0; i < elementsToCopy; ++i) {
        newData[i] = data[i];
    }
    
    delete[] data;
    data = newData;
    capacity = newCapacity;
    
    if (newCapacity < size) {
        size = newCapacity;
    }
}

template <class T>
void DynamicArray<T>::Append(T item) {
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Resize(newCapacity);
    }
    
    data[size] = item;
    ++size;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this == &other) return *this;
    
    delete[] data;
    
    size = other.size;
    capacity = other.capacity;
    
    if (capacity == 0) {
        data = nullptr;
        return *this;
    }
    
    data = new T[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
    
    return *this;
}