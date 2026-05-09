#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "errors.h"

template <class T>
class Sequence {
public:
    virtual ~Sequence() {}
    
    virtual T GetFirst() const = 0; /*получить первый эл в списке*/
    virtual T GetLast() const = 0; /*последний*/
    virtual T Get(int index) const = 0; /*получ эл по индексу*/
    virtual int GetLength() const = 0; /*получ длину списка*/
    
    virtual void Append(T item) = 0; /*+эл в конец*/
    virtual void Prepend(T item) = 0; /*+эл в начало*/
    virtual void InsertAt(T item, int index) = 0; /*+эл в заданную ползицию*/
    virtual void Set(int index, T value) = 0;

    virtual Sequence<T>* Map(T (*func)(T)) const = 0;
    virtual Sequence<T>* Where(bool (*predicate)(T)) const = 0;
    virtual T Reduce(T (*func)(T, T), T initialValue) const = 0;

};

#endif