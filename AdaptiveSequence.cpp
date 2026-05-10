#include "AdaptiveSequence.h"

template <class T>
AdaptiveSequence<T>::AdaptiveSequence() 
    : mode(StorageMode::ARRAY) {
    data = new ArraySequence<T>();
}

template <class T>
AdaptiveSequence<T>::AdaptiveSequence(T* items, int count) 
    : mode(StorageMode::ARRAY) {
    data = new ArraySequence<T>(items, count);
}

template <class T>
AdaptiveSequence<T>::AdaptiveSequence(const AdaptiveSequence<T>& other) 
    : mode(other.mode) {
    if (mode == StorageMode::ARRAY) {
        data = new ArraySequence<T>(*(dynamic_cast<ArraySequence<T>*>(other.data)));
    } else {
        data = new ListSequence<T>(*(dynamic_cast<ListSequence<T>*>(other.data)));
    }
}

template <class T>
AdaptiveSequence<T>::~AdaptiveSequence() {
    delete data;
}

template <class T>
void AdaptiveSequence<T>::SwitchToArray() {
    if (mode == StorageMode::ARRAY) return;
    
    int len = data->GetLength();
    T* temp = new T[len];
    for (int i = 0; i < len; ++i) {
        temp[i] = data->Get(i);
    }
    
    delete data;
    data = new ArraySequence<T>(temp, len);
    mode = StorageMode::ARRAY;
    
    delete[] temp;
}

template <class T>
void AdaptiveSequence<T>::SwitchToList() {
    if (mode == StorageMode::LIST) return;
    
    int len = data->GetLength();
    T* temp = new T[len];
    for (int i = 0; i < len; ++i) {
        temp[i] = data->Get(i);
    }
    
    delete data;
    data = new ListSequence<T>(temp, len);
    mode = StorageMode::LIST;
    
    delete[] temp;
}

template <class T>
StorageMode AdaptiveSequence<T>::GetCurrentMode() const {
    return mode;
}

template <class T>
void AdaptiveSequence<T>::SwitchMode() {
    if (mode == StorageMode::ARRAY) {
        SwitchToList();
    } else {
        SwitchToArray();
    }
}

template <class T>
T AdaptiveSequence<T>::GetFirst() const {
    return data->GetFirst();
}

template <class T>
T AdaptiveSequence<T>::GetLast() const {
    return data->GetLast();
}

template <class T>
T AdaptiveSequence<T>::Get(int index) const {
    return data->Get(index);
}

template <class T>
int AdaptiveSequence<T>::GetLength() const {
    return data->GetLength();
}

template <class T>
void AdaptiveSequence<T>::Set(int index, T value) {
    data->Set(index, value);
}

template <class T>
void AdaptiveSequence<T>::Append(T item) {
    data->Append(item);
}

template <class T>
void AdaptiveSequence<T>::Prepend(T item) {
    data->Prepend(item);
}

template <class T>
void AdaptiveSequence<T>::InsertAt(T item, int index) {
    data->InsertAt(item, index);
}

template <class T>
Sequence<T>* AdaptiveSequence<T>::Map(T (*func)(T)) const {
    Sequence<T>* mappedData = data->Map(func);
    
    AdaptiveSequence<T>* result = new AdaptiveSequence<T>();
    
    if (mode == StorageMode::ARRAY) {
        ArraySequence<T>* arrMapped = dynamic_cast<ArraySequence<T>*>(mappedData);
        if (arrMapped) {
            delete result->data;
            result->data = new ArraySequence<T>(*arrMapped);
            result->mode = StorageMode::ARRAY;
        }
    } else {
        ListSequence<T>* listMapped = dynamic_cast<ListSequence<T>*>(mappedData);
        if (listMapped) {
            delete result->data;
            result->data = new ListSequence<T>(*listMapped);
            result->mode = StorageMode::LIST;
        }
    }
    
    delete mappedData;
    return result;
}

template <class T>
Sequence<T>* AdaptiveSequence<T>::Where(bool (*predicate)(T)) const {
    Sequence<T>* filteredData = data->Where(predicate);
    
    AdaptiveSequence<T>* result = new AdaptiveSequence<T>();
    
    if (mode == StorageMode::ARRAY) {
        ArraySequence<T>* arrFiltered = dynamic_cast<ArraySequence<T>*>(filteredData);
        if (arrFiltered) {
            delete result->data;
            result->data = new ArraySequence<T>(*arrFiltered);
            result->mode = StorageMode::ARRAY;
        }
    } else {
        ListSequence<T>* listFiltered = dynamic_cast<ListSequence<T>*>(filteredData);
        if (listFiltered) {
            delete result->data;
            result->data = new ListSequence<T>(*listFiltered);
            result->mode = StorageMode::LIST;
        }
    }
    
    delete filteredData;
    return result;
}

template <class T>
T AdaptiveSequence<T>::Reduce(T (*func)(T, T), T initialValue) const {
    return data->Reduce(func, initialValue);
}

template <class T>
AdaptiveSequence<T>& AdaptiveSequence<T>::operator=(const AdaptiveSequence<T>& other) {
    if (this == &other) return *this;
    
    delete data;
    mode = other.mode;
    
    if (mode == StorageMode::ARRAY) {
        data = new ArraySequence<T>(*(dynamic_cast<ArraySequence<T>*>(other.data)));
    } else {
        data = new ListSequence<T>(*(dynamic_cast<ListSequence<T>*>(other.data)));
    }
    
    return *this;
}