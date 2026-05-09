#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* items;
    
public:

    ArraySequence();
    ArraySequence(T* items, int count);
    ArraySequence(const DynamicArray<T>& dynamicArray);
    ArraySequence(const ArraySequence<T>& other);
    
    ~ArraySequence();
    
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    
    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    void Set(int index, T value) override;
    
    ArraySequence<T>& operator=(const ArraySequence<T>& other);

    Sequence<T>* Map(T (*func)(T)) const override;
    Sequence<T>* Where(bool (*predicate)(T)) const override;
    T Reduce(T (*func)(T, T), T initialValue) const override;
};

#include "ArraySequence.cpp"
#endif