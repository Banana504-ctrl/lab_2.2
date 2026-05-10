#include "test_utils.h"
#include "../BitSequence.h"

void testBitSequenceConstructorFromString() {
    BitSequence bs("10110");
    
    TEST_ASSERT(bs.GetLength() == 5, "BitSequence::BitSequence(const char*)", "BitSequence.cpp",
                "Ожидаемая длина 5, получена " + std::to_string(bs.GetLength()));
    
    bool expected[] = {1, 0, 1, 1, 0};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(bs.Get(i) == expected[i], "BitSequence::BitSequence(const char*)", "BitSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(bs.Get(i)));
    }
    
    TEST_PASS("BitSequence::BitSequence(const char*)", "BitSequence.cpp");
}

void testBitSequenceConstructorEmpty() {
    BitSequence bs;
    
    TEST_ASSERT(bs.GetLength() == 0, "BitSequence::BitSequence()", "BitSequence.cpp",
                "Ожидаемая длина 0, получена " + std::to_string(bs.GetLength()));
    
    TEST_PASS("BitSequence::BitSequence()", "BitSequence.cpp");
}

void testBitSequenceGet() {
    BitSequence bs("10110010");
    
    bool expected[] = {1, 0, 1, 1, 0, 0, 1, 0};
    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT(bs.Get(i) == expected[i], "BitSequence::Get", "BitSequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(bs.Get(i)));
    }
    
    try {
        bs.Get(8);
        TEST_ASSERT(false, "BitSequence::Get", "BitSequence.cpp",
                    "Get(8) не вывело INDEX_OUT_OF_RANGE");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::INDEX_OUT_OF_RANGE, "BitSequence::Get", "BitSequence.cpp",
                    "Get(8) вывел неверное имя ошибки");
    }
    
    TEST_PASS("BitSequence::Get", "BitSequence.cpp");
}

void testBitSequenceSet() {
    BitSequence bs("0000");
    
    bs.Set(0, true);
    bs.Set(2, true);
    
    bool expected[] = {1, 0, 1, 0};
    for (int i = 0; i < 4; ++i) {
        TEST_ASSERT(bs.Get(i) == expected[i], "BitSequence::Set", "BitSequence.cpp",
                    "После Set, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(bs.Get(i)));
    }
    
    TEST_PASS("BitSequence::Set", "BitSequence.cpp");
}

void testBitSequenceAppend() {
    BitSequence bs("101");
    
    bs.Append(true);
    bs.Append(false);
    bs.Append(true);
    
    TEST_ASSERT(bs.GetLength() == 6, "BitSequence::Append", "BitSequence.cpp",
                "После Appends, ожидаемая длина 6, получена " + std::to_string(bs.GetLength()));
    
    bool expected[] = {1, 0, 1, 1, 0, 1};
    for (int i = 0; i < 6; ++i) {
        TEST_ASSERT(bs.Get(i) == expected[i], "BitSequence::Append", "BitSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(bs.Get(i)));
    }
    
    TEST_PASS("BitSequence::Append", "BitSequence.cpp");
}

void testBitSequencePrepend() {
    BitSequence bs("101");
    
    bs.Prepend(true);
    bs.Prepend(false);
    
    TEST_ASSERT(bs.GetLength() == 5, "BitSequence::Prepend", "BitSequence.cpp",
                "После Prepends, ожидаемая длина 5, получена " + std::to_string(bs.GetLength()));
    
    bool expected[] = {0, 1, 1, 0, 1};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(bs.Get(i) == expected[i], "BitSequence::Prepend", "BitSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(bs.Get(i)));
    }
    
    TEST_PASS("BitSequence::Prepend", "BitSequence.cpp");
}

void testBitSequenceAnd() {
    BitSequence a("10110010");
    BitSequence b("11001100");
    
    BitSequence result = a.And(b);
    
    TEST_ASSERT(result.GetLength() == 8, "BitSequence::And", "BitSequence.cpp",
                "После And ожидаемая длина 8, получена " + std::to_string(result.GetLength()));
    
    bool expected[] = {1, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT(result.Get(i) == expected[i], "BitSequence::And", "BitSequence.cpp",
                    "Результат And по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result.Get(i)));
    }
    
    TEST_PASS("BitSequence::And", "BitSequence.cpp");
}

void testBitSequenceOr() {
    BitSequence a("10110010");
    BitSequence b("11001100");
    
    BitSequence result = a.Or(b);
    
    bool expected[] = {1, 1, 1, 1, 1, 1, 1, 0};
    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT(result.Get(i) == expected[i], "BitSequence::Or", "BitSequence.cpp",
                    "Результат Or по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result.Get(i)));
    }
    
    TEST_PASS("BitSequence::Or", "BitSequence.cpp");
}

void testBitSequenceXor() {
    BitSequence a("10110010");
    BitSequence b("11001100");
    
    BitSequence result = a.Xor(b);
    
    bool expected[] = {0, 1, 1, 1, 1, 1, 1, 0};
    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT(result.Get(i) == expected[i], "BitSequence::Xor", "BitSequence.cpp",
                    "Результат Xor по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result.Get(i)));
    }
    
    TEST_PASS("BitSequence::Xor", "BitSequence.cpp");
}

void testBitSequenceNot() {
    BitSequence a("10110010");
    
    BitSequence result = a.Not();
    
    bool expected[] = {0, 1, 0, 0, 1, 1, 0, 1};
    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT(result.Get(i) == expected[i], "BitSequence::Not", "BitSequence.cpp",
                    "Результат Not по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result.Get(i)));
    }
    
    TEST_PASS("BitSequence::Not", "BitSequence.cpp");
}