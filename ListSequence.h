#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T>* items;
    
public:
    ListSequence();
    ListSequence(T* items, int count);
    ListSequence(const LinkedList<T>& linkedList);
    ListSequence(const ListSequence<T>& other);
    ~ListSequence();
    
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    
    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    void Set(int index, T value) override;
    
    Sequence<T>* Map(T (*func)(T)) const override;
    Sequence<T>* Where(bool (*predicate)(T)) const override;
    T Reduce(T (*func)(T, T), T initialValue) const override;
    
    ListSequence<T>& operator=(const ListSequence<T>& other);
};

#include "ListSequence.cpp"
#endif