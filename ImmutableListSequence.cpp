#include "ImmutableListSequence.h"

template <class T>
ImmutableListSequence<T>::ImmutableListSequence() {
    items = new LinkedList<T>();
}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(T* items, int count) {
    if (count < 0) throw ErrorCode::NEGATIVE_SIZE;
    this->items = new LinkedList<T>(items, count);
}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const LinkedList<T>& linkedList) {
    items = new LinkedList<T>(linkedList);
}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T>& other) {
    items = new LinkedList<T>(*(other.items));
}

template <class T>
ImmutableListSequence<T>::~ImmutableListSequence() {
    delete items;
}

template <class T>
T ImmutableListSequence<T>::GetFirst() const {
    return items->GetFirst();
}

template <class T>
T ImmutableListSequence<T>::GetLast() const {
    return items->GetLast();
}

template <class T>
T ImmutableListSequence<T>::Get(int index) const {
    return items->Get(index);
}

template <class T>
int ImmutableListSequence<T>::GetLength() const {
    return items->GetLength();
}

template <class T>
void ImmutableListSequence<T>::Set(int index, T value) {
    (void)index;
    (void)value;
    throw ErrorCode::OPERATION_NOT_ALLOWED;
}

template <class T>
ImmutableListSequence<T>* ImmutableListSequence<T>::AppendImmutable(T item) const {
    LinkedList<T>* newItems = new LinkedList<T>(*items);
    newItems->Append(item);
    ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*newItems);
    delete newItems;
    return result;
}

template <class T>
ImmutableListSequence<T>* ImmutableListSequence<T>::PrependImmutable(T item) const {
    LinkedList<T>* newItems = new LinkedList<T>(*items);
    newItems->Prepend(item);
    ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*newItems);
    delete newItems;
    return result;
}

template <class T>
ImmutableListSequence<T>* ImmutableListSequence<T>::InsertAtImmutable(T item, int index) const {
    LinkedList<T>* newItems = new LinkedList<T>(*items);
    newItems->InsertAt(item, index);
    ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*newItems);
    delete newItems;
    return result;
}

template <class T>
Sequence<T>* ImmutableListSequence<T>::Map(T (*func)(T)) const {
    int len = GetLength();
    T* temp = new T[len];
    for (int i = 0; i < len; ++i) {
        temp[i] = func(Get(i));
    }
    Sequence<T>* result = new ImmutableListSequence<T>(temp, len);
    delete[] temp;
    return result;
}

template <class T>
Sequence<T>* ImmutableListSequence<T>::Where(bool (*predicate)(T)) const {
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
    Sequence<T>* result = new ImmutableListSequence<T>(temp, count);
    delete[] temp;
    return result;
}

template <class T>
T ImmutableListSequence<T>::Reduce(T (*func)(T, T), T initialValue) const {
    T result = initialValue;
    for (int i = 0; i < GetLength(); ++i) {
        result = func(result, Get(i));
    }
    return result;
}

template <class T>
ImmutableListSequence<T>& ImmutableListSequence<T>::operator=(const ImmutableListSequence<T>& other) {
    if (this == &other) return *this;
    delete items;
    items = new LinkedList<T>(*(other.items));
    return *this;
}