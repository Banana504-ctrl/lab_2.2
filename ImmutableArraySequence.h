#ifndef IMMUTABLE_ARRAY_SEQUENCE_H
#define IMMUTABLE_ARRAY_SEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ImmutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* items;
    
public:
    ImmutableArraySequence();
    ImmutableArraySequence(T* items, int count);
    ImmutableArraySequence(const DynamicArray<T>& dynamicArray);
    ImmutableArraySequence(const ImmutableArraySequence<T>& other);
    ~ImmutableArraySequence();
    
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    void Set(int index, T value) override;

    ImmutableArraySequence<T>* AppendImmutable(T item) const;
    ImmutableArraySequence<T>* PrependImmutable(T item) const;
    ImmutableArraySequence<T>* InsertAtImmutable(T item, int index) const;

    void Append(T item) override { throw ErrorCode::OPERATION_NOT_ALLOWED; }
    void Prepend(T item) override { throw ErrorCode::OPERATION_NOT_ALLOWED; }
    void InsertAt(T item, int index) override { throw ErrorCode::OPERATION_NOT_ALLOWED; }
    
    Sequence<T>* Map(T (*func)(T)) const override;
    Sequence<T>* Where(bool (*predicate)(T)) const override;
    T Reduce(T (*func)(T, T), T initialValue) const override;
    
    ImmutableArraySequence<T>& operator=(const ImmutableArraySequence<T>& other);
};

#include "ImmutableArraySequence.cpp"
#endif