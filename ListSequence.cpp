#include "ListSequence.h"

template <class T>
ListSequence<T>::ListSequence() {   
    items = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    this->items = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T>& linkedList) {
    items = new LinkedList<T>(linkedList);
}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) {
    items = new LinkedList<T>(*(other.items));
}

template <class T>
ListSequence<T>::~ListSequence() {
    delete items;
}

template <class T>
T ListSequence<T>::GetFirst() const {
    return items->GetFirst();
}

template <class T>
T ListSequence<T>::GetLast() const {
    return items->GetLast();
}

template <class T>
T ListSequence<T>::Get(int index) const {
    return items->Get(index);
}

template <class T>
int ListSequence<T>::GetLength() const {
    return items->GetLength();
}

template <class T>
void ListSequence<T>::Append(T item) {
    items->Append(item);
}

template <class T>
void ListSequence<T>::Prepend(T item) {
    items->Prepend(item);
}

template <class T>
void ListSequence<T>::InsertAt(T item, int index) {
    items->InsertAt(item, index);
}

template <class T>
ListSequence<T>& ListSequence<T>::operator=(const ListSequence<T>& other) {
    if (this == &other) return *this;
    
    delete items;
    items = new LinkedList<T>(*(other.items));
    
    return *this;
}

template <class T>
Sequence<T>* ListSequence<T>::Map(T (*func)(T)) const {
    int len = GetLength();
    T* resultData = new T[len];
    
    for (int i = 0; i < len; ++i) {
        resultData[i] = func(Get(i));
    }
    
    Sequence<T>* result = new ListSequence<T>(resultData, len);
    delete[] resultData;
    return result;
}

template <class T>
Sequence<T>* ListSequence<T>::Where(bool (*predicate)(T)) const {
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
    
    Sequence<T>* result = new ListSequence<T>(temp, count);
    delete[] temp;
    return result;
}

template <class T>
T ListSequence<T>::Reduce(T (*func)(T, T), T initialValue) const {
    T result = initialValue;
    int len = GetLength();
    
    for (int i = 0; i < len; ++i) {
        result = func(result, Get(i));
    }
    
    return result;
}

template <class T>
void ListSequence<T>::Set(int index, T value) {
    items->Set(index, value);
}