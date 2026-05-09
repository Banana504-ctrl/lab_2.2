#ifndef BIT_SEQUENCE_H
#define BIT_SEQUENCE_H

#include "Sequence.h"
#include "ArraySequence.h"

class BitSequence : public Sequence<bool> {
private:
    ArraySequence<bool>* bits;
    
public:
    BitSequence();
    BitSequence(const char* bitString);
    BitSequence(const BitSequence& other);
    ~BitSequence();
    
    bool GetFirst() const override;
    bool GetLast() const override;
    bool Get(int index) const override;
    int GetLength() const override;
    void Set(int index, bool value) override;
    
    void Append(bool item) override;
    void Prepend(bool item) override;
    void InsertAt(bool item, int index) override;
    
    Sequence<bool>* Map(bool (*func)(bool)) const override;
    Sequence<bool>* Where(bool (*predicate)(bool)) const override;
    bool Reduce(bool (*func)(bool, bool), bool initialValue) const override;
    
    BitSequence And(const BitSequence& other) const;
    BitSequence Or(const BitSequence& other) const;
    BitSequence Xor(const BitSequence& other) const;
    BitSequence Not() const;
    
    BitSequence& operator=(const BitSequence& other);
};

#include "BitSequence.cpp"
#endif