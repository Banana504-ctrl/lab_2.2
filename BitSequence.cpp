#include "BitSequence.h"
#include <cstring>

BitSequence::BitSequence() {
    bits = new ArraySequence<bool>();
}

BitSequence::BitSequence(const char* bitString) {
    if (bitString == nullptr) throw ErrorCode::INVALID_INPUT;
    
    bits = new ArraySequence<bool>();
    int len = (int)strlen(bitString);
    
    for (int i = 0; i < len; ++i) {
        char c = bitString[i];
        if (c == '1') {
            bits->Append(true);
        } else if (c == '0') {
            bits->Append(false);
        } else {
            delete bits;
            throw ErrorCode::INVALID_INPUT;
        }
    }
}

BitSequence::BitSequence(const BitSequence& other) {
    bits = new ArraySequence<bool>(*(other.bits));
}

BitSequence::~BitSequence() {
    delete bits;
}


bool BitSequence::GetFirst() const {
    return bits->GetFirst();
}

bool BitSequence::GetLast() const {
    return bits->GetLast();
}

bool BitSequence::Get(int index) const {
    return bits->Get(index);
}

int BitSequence::GetLength() const {
    return bits->GetLength();
}

void BitSequence::Set(int index, bool value) {
    bits->Set(index, value);
}


void BitSequence::Append(bool item) {
    bits->Append(item);
}

void BitSequence::Prepend(bool item) {
    bits->Prepend(item);
}

void BitSequence::InsertAt(bool item, int index) {
    bits->InsertAt(item, index);
}

BitSequence BitSequence::And(const BitSequence& other) const {
    int len = (GetLength() < other.GetLength()) ? GetLength() : other.GetLength();
    BitSequence result;
    
    for (int i = 0; i < len; ++i) {
        result.Append(Get(i) && other.Get(i));
    }
    return result;
}

BitSequence BitSequence::Or(const BitSequence& other) const {
    int len = (GetLength() < other.GetLength()) ? GetLength() : other.GetLength();
    BitSequence result;
    
    for (int i = 0; i < len; ++i) {
        result.Append(Get(i) || other.Get(i));
    }
    return result;
}

BitSequence BitSequence::Xor(const BitSequence& other) const {
    int len = (GetLength() < other.GetLength()) ? GetLength() : other.GetLength();
    BitSequence result;
    
    for (int i = 0; i < len; ++i) {
        result.Append(Get(i) != other.Get(i));
    }
    return result;
}

BitSequence BitSequence::Not() const {
    BitSequence result;
    
    for (int i = 0; i < GetLength(); ++i) {
        result.Append(!Get(i));
    }
    return result;
}

BitSequence& BitSequence::operator=(const BitSequence& other) {
    if (this == &other) return *this;
    
    delete bits;
    bits = new ArraySequence<bool>(*(other.bits));
    
    return *this;
}

Sequence<bool>* BitSequence::Map(bool (*func)(bool)) const {
    int len = GetLength();
    bool* temp = new bool[len];
    
    for (int i = 0; i < len; ++i) {
        temp[i] = func(Get(i));
    }
    
    Sequence<bool>* result = new BitSequence();
    for (int i = 0; i < len; ++i) {
        result->Append(temp[i]);
    }
    
    delete[] temp;
    return result;
}

Sequence<bool>* BitSequence::Where(bool (*predicate)(bool)) const {
    int len = GetLength();
    bool* temp = new bool[len];
    int count = 0;
    
    for (int i = 0; i < len; ++i) {
        bool value = Get(i);
        if (predicate(value)) {
            temp[count] = value;
            ++count;
        }
    }
    
    Sequence<bool>* result = new BitSequence();
    for (int i = 0; i < count; ++i) {
        result->Append(temp[i]);
    }
    
    delete[] temp;
    return result;
}

bool BitSequence::Reduce(bool (*func)(bool, bool), bool initialValue) const {
    bool result = initialValue;
    int len = GetLength();
    
    for (int i = 0; i < len; ++i) {
        result = func(result, Get(i));
    }
    return result;
}