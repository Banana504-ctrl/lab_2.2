#include "DynamicArray.h"

template <class T>
void DynamicArray<T>::copyFrom(const DynamicArray<T>& other) {
    size = other.size;
    data = new T[size];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
}

template <class T>
void DynamicArray<T>::free() {
    delete[] data;
}

template <class T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0) {}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    size = count;
    if (size == 0) {
        data = nullptr;
        return;
    }
    
    data = new T[size];
    for (int i = 0; i < size; ++i)
        data[i] = items[i];
}

template <class T>
DynamicArray<T>::DynamicArray(int size) : size(size) {
    if (size < 0) throw ErrorCode::NEGATIVE_SIZE;
    data = (size == 0) ? nullptr : new T[size]();
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) {
    copyFrom(other);
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    free();
}

template <class T>
T DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= size)
        throw ErrorCode::INDEX_OUT_OF_RANGE;
    return data[index];
}

template <class T>
int DynamicArray<T>::GetSize() const {
    return size;
}

template <class T>
void DynamicArray<T>::Set(int index, T value) {
    if (index < 0 || index >= size)
        throw ErrorCode::INDEX_OUT_OF_RANGE;
    data[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0) throw ErrorCode::NEGATIVE_SIZE;
    
    if (newSize == 0) {
        free();
        data = nullptr;
        size = 0;
        return;
    }
    
    T* newData = new T[newSize]();
    int copyCount = (newSize < size) ? newSize : size;
    for (int i = 0; i < copyCount; ++i)
        newData[i] = data[i];
    
    free();
    data = newData;
    size = newSize;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}