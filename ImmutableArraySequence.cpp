#include "ImmutableArraySequence.h"

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence() {
    items = new DynamicArray<T>();
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    this->items = new DynamicArray<T>(items, count);
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const DynamicArray<T>& dynamicArray) {
    items = new DynamicArray<T>(dynamicArray);
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& other) {
    items = new DynamicArray<T>(*(other.items));
}

template <class T>
ImmutableArraySequence<T>::~ImmutableArraySequence() {
    delete items;
}

template <class T>
T ImmutableArraySequence<T>::GetFirst() const {
    if (GetLength() == 0) throw ErrorCode::EMPTY_CONTAINER;
    return items->Get(0);
}

template <class T>
T ImmutableArraySequence<T>::GetLast() const {
    if (GetLength() == 0) throw ErrorCode::EMPTY_CONTAINER;
    return items->Get(GetLength() - 1);
}

template <class T>
T ImmutableArraySequence<T>::Get(int index) const {
    return items->Get(index);
}

template <class T>
int ImmutableArraySequence<T>::GetLength() const {
    return items->GetSize();
}

template <class T>
void ImmutableArraySequence<T>::Set(int index, T value) {
    (void)index;
    (void)value;
    throw ErrorCode::OPERATION_NOT_ALLOWED;
}

template <class T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::AppendImmutable(T item) const {
    int oldSize = GetLength();
    DynamicArray<T>* newItems = new DynamicArray<T>(*items);
    newItems->Resize(oldSize + 1);
    newItems->Set(oldSize, item);
    
    ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*newItems);
    delete newItems;
    return result;
}

template <class T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::PrependImmutable(T item) const {
    int oldSize = GetLength();
    DynamicArray<T>* newItems = new DynamicArray<T>(oldSize + 1);
    newItems->Set(0, item);
    
    for (int i = 0; i < oldSize; ++i) {
        newItems->Set(i + 1, items->Get(i));
    }
    
    ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*newItems);
    delete newItems;
    return result;
}

template <class T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::InsertAtImmutable(T item, int index) const {
    if (index < 0 || index > GetLength()) throw ErrorCode::INDEX_OUT_OF_RANGE;
    
    int oldSize = GetLength();
    DynamicArray<T>* newItems = new DynamicArray<T>(oldSize + 1);
    
    for (int i = 0; i < index; ++i) {
        newItems->Set(i, items->Get(i));
    }
    newItems->Set(index, item);
    for (int i = index; i < oldSize; ++i) {
        newItems->Set(i + 1, items->Get(i));
    }
    
    ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*newItems);
    delete newItems;
    return result;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::Map(T (*func)(T)) const {
    int len = GetLength();
    T* temp = new T[len];
    for (int i = 0; i < len; ++i) {
        temp[i] = func(Get(i));
    }
    Sequence<T>* result = new ImmutableArraySequence<T>(temp, len);
    delete[] temp;
    return result;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::Where(bool (*predicate)(T)) const {
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
    Sequence<T>* result = new ImmutableArraySequence<T>(temp, count);
    delete[] temp;
    return result;
}

template <class T>
T ImmutableArraySequence<T>::Reduce(T (*func)(T, T), T initialValue) const {
    T result = initialValue;
    for (int i = 0; i < GetLength(); ++i) {
        result = func(result, Get(i));
    }
    return result;
}

template <class T>
ImmutableArraySequence<T>& ImmutableArraySequence<T>::operator=(const ImmutableArraySequence<T>& other) {
    if (this == &other) return *this;
    delete items;
    items = new DynamicArray<T>(*(other.items));
    return *this;
}