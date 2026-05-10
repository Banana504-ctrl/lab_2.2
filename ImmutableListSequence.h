#ifndef IMMUTABLE_LIST_SEQUENCE_H
#define IMMUTABLE_LIST_SEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class ImmutableListSequence : public Sequence<T> {
private:
    LinkedList<T>* items;
    
public:
    ImmutableListSequence();
    ImmutableListSequence(T* items, int count);
    ImmutableListSequence(const LinkedList<T>& linkedList);
    ImmutableListSequence(const ImmutableListSequence<T>& other);
    ~ImmutableListSequence();
    
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    void Set(int index, T value) override;

    void Append(T item) override { 
        (void)item;
        throw ErrorCode::OPERATION_NOT_ALLOWED; 
    }
    void Prepend(T item) override { 
        (void)item;
        throw ErrorCode::OPERATION_NOT_ALLOWED; 
    }
    void InsertAt(T item, int index) override { 
        (void)item;
        (void)index;
        throw ErrorCode::OPERATION_NOT_ALLOWED; 
    }

    ImmutableListSequence<T>* AppendImmutable(T item) const;
    ImmutableListSequence<T>* PrependImmutable(T item) const;
    ImmutableListSequence<T>* InsertAtImmutable(T item, int index) const;
    
    Sequence<T>* Map(T (*func)(T)) const override;
    Sequence<T>* Where(bool (*predicate)(T)) const override;
    T Reduce(T (*func)(T, T), T initialValue) const override;
    
    ImmutableListSequence<T>& operator=(const ImmutableListSequence<T>& other);
};

#include "ImmutableListSequence.cpp"
#endif