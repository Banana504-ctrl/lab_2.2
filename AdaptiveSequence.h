#ifndef ADAPTIVE_SEQUENCE_H
#define ADAPTIVE_SEQUENCE_H

#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "errors.h"

enum class StorageMode {
    ARRAY,
    LIST
};

template <class T>
class AdaptiveSequence : public Sequence<T> {
private:
    Sequence<T>* data;
    StorageMode mode;
    
    void SwitchToArray();
    void SwitchToList();
    
public:
    AdaptiveSequence();
    AdaptiveSequence(T* items, int count);
    AdaptiveSequence(const AdaptiveSequence<T>& other);
    ~AdaptiveSequence();
    
    StorageMode GetCurrentMode() const;
    void SwitchMode();

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    void Set(int index, T value) override;
    
    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    
    Sequence<T>* Map(T (*func)(T)) const override;
    Sequence<T>* Where(bool (*predicate)(T)) const override;
    T Reduce(T (*func)(T, T), T initialValue) const override;
    
    AdaptiveSequence<T>& operator=(const AdaptiveSequence<T>& other);
};

#include "AdaptiveSequence.cpp"
#endif