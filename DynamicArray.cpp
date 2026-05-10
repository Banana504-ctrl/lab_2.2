#include "DynamicArray.h"

template <class T>
DynamicArray<T>::DynamicArray() : data(nullptr), capacity(0), size(0) {}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (count == 0) {
        data = nullptr;
        capacity = 0;
        size = 0;
        return;
    }
    
    data = new T[count];
    for (int i = 0; i < count; ++i) {
        data[i] = items[i];
    }
    capacity = count;
    size = count;
}

template <class T>
DynamicArray<T>::DynamicArray(int size) {
    if (size < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (size == 0) {
        data = nullptr;
        capacity = 0;
        this->size = 0;
        return;
    }
    
    data = new T[size];
    capacity = size;
    this->size = size;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) 
    : capacity(other.capacity), size(other.size) 
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
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (newSize == 0) {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
        return;
    }
    
    if (newSize > capacity) {
        int newCapacity = capacity;
        if (newCapacity == 0) newCapacity = 1;
        while (newCapacity < newSize) {
            newCapacity *= 2;
        }
        
        T* newData = new T[newCapacity];
        
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        
        for (int i = size; i < newCapacity; ++i) {
            newData[i] = T(); 
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    

    if (newSize > size) {
        for (int i = size; i < newSize; ++i) {
            data[i] = T();  // значение по умолчанию
        }
    }
    
    size = newSize;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this == &other) return *this;
    
    delete[] data;
    
    capacity = other.capacity;
    size = other.size;
    
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