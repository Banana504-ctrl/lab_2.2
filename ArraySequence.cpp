#include "ArraySequence.h"

template <class T>
ArraySequence<T>::ArraySequence() {
    items = new DynamicArray<T>();
}

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    this->items = new DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& dynamicArray) {
    items = new DynamicArray<T>(dynamicArray);
}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) {
    items = new DynamicArray<T>(*(other.items));
}

template <class T>
ArraySequence<T>::~ArraySequence() {
    delete items;
}

template <class T>
T ArraySequence<T>::GetFirst() const {
    if (GetLength() == 0) throw ErrorCode::EMPTY_CONTAINER;
    return items->Get(0);
}

template <class T>
T ArraySequence<T>::GetLast() const {
    if (GetLength() == 0) throw ErrorCode::EMPTY_CONTAINER;
    return items->Get(GetLength() - 1);
}

template <class T>
T ArraySequence<T>::Get(int index) const {
    return items->Get(index);
}

template <class T>
int ArraySequence<T>::GetLength() const {
    return items->GetSize();
}

template <class T>
void ArraySequence<T>::Set(int index, T value) {
    items->Set(index, value);
}

template <class T>
void ArraySequence<T>::Append(T item) {
    int oldSize = items->GetSize();
    items->Resize(oldSize + 1);
    items->Set(oldSize, item);
}

template <class T>
void ArraySequence<T>::Prepend(T item) {
    int oldSize = items->GetSize();
    items->Resize(oldSize + 1);
    for (int i = oldSize; i > 0; --i) {
        items->Set(i, items->Get(i - 1));
    }
    items->Set(0, item);
}

template <class T>
void ArraySequence<T>::InsertAt(T item, int index) {
    if (index < 0 || index > GetLength()) throw ErrorCode::INDEX_OUT_OF_RANGE;
    
    int oldSize = items->GetSize();
    items->Resize(oldSize + 1);
    for (int i = oldSize; i > index; --i) {
        items->Set(i, items->Get(i - 1));
    }
    items->Set(index, item);
}

template <class T>
Sequence<T>* ArraySequence<T>::Map(T (*func)(T)) const {
    int len = GetLength();
    T* temp = new T[len];
    for (int i = 0; i < len; ++i) {
        temp[i] = func(Get(i));
    }
    Sequence<T>* result = new ArraySequence<T>(temp, len);
    delete[] temp;
    return result;
}

template <class T>
Sequence<T>* ArraySequence<T>::Where(bool (*predicate)(T)) const {
    int len = GetLength();
    T* temp = new T[len];
    int count = 0;
    for (int i = 0; i < len; ++i) {
        T value = Get(i);
        if (predicate(value)) {
            temp[count] = value;
            ++count;
        }
    }
    Sequence<T>* result = new ArraySequence<T>(temp, count);
    delete[] temp;
    return result;
}

template <class T>
T ArraySequence<T>::Reduce(T (*func)(T, T), T initialValue) const {
    T result = initialValue;
    for (int i = 0; i < GetLength(); ++i) {
        result = func(result, Get(i));
    }
    return result;
}

template <class T>
ArraySequence<T>& ArraySequence<T>::operator=(const ArraySequence<T>& other) {
    if (this == &other) return *this;
    delete items;
    items = new DynamicArray<T>(*(other.items));
    return *this;
}