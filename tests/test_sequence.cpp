#include "test_utils.h"
#include "../ArraySequence.h"
#include "../ListSequence.h"
#include "../ImmutableArraySequence.h"
#include "../ImmutableListSequence.h"
#include "../AdaptiveSequence.h"

void testSequencePolymorphismWithArraySequence() {
    int arr[] = {10, 20, 30, 40, 50};
    Sequence<int>* seq = new ArraySequence<int>(arr, 5);
    
    TEST_ASSERT(seq->GetLength() == 5, "Sequence::GetLength через ArraySequence", "ArraySequence.cpp",
                "GetLength() ожидалось 5, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence::Get через ArraySequence", "ArraySequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    TEST_ASSERT(seq->GetFirst() == 10, "Sequence::GetFirst через ArraySequence", "ArraySequence.cpp",
                "GetFirst() ожидалось 10, получено " + std::to_string(seq->GetFirst()));
    TEST_ASSERT(seq->GetLast() == 50, "Sequence::GetLast через ArraySequence", "ArraySequence.cpp",
                "GetLast() ожидалось 50, получено " + std::to_string(seq->GetLast()));
    
    seq->Set(2, 999);
    TEST_ASSERT(seq->Get(2) == 999, "Sequence::Set через ArraySequence", "ArraySequence.cpp",
                "После Set(2,999), Get(2) ожидалось 999, получено " + std::to_string(seq->Get(2)));
    
    seq->Append(60);
    TEST_ASSERT(seq->GetLength() == 6, "Sequence::Append через ArraySequence", "ArraySequence.cpp",
                "После Append, ожидаемая длина 6, получена " + std::to_string(seq->GetLength()));
    TEST_ASSERT(seq->Get(5) == 60, "Sequence::Append через ArraySequence", "ArraySequence.cpp",
                "После Append, Get(5) ожидалось 60, получено " + std::to_string(seq->Get(5)));
    
    delete seq;
    TEST_PASS("Полиморфизм Sequence с ArraySequence", "ArraySequence.cpp");
}

void testSequencePolymorphismWithListSequence() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Sequence<int>* seq = new ListSequence<int>(arr, 10);
    
    TEST_ASSERT(seq->GetLength() == 10, "Sequence::GetLength через ListSequence", "ListSequence.cpp",
                "GetLength() ожидалось 10, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 10; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence::Get через ListSequence", "ListSequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    TEST_ASSERT(seq->GetFirst() == 1, "Sequence::GetFirst через ListSequence", "ListSequence.cpp",
                "GetFirst() ожидалось 1, получено " + std::to_string(seq->GetFirst()));
    TEST_ASSERT(seq->GetLast() == 10, "Sequence::GetLast через ListSequence", "ListSequence.cpp",
                "GetLast() ожидалось 10, получено " + std::to_string(seq->GetLast()));
    
    seq->Prepend(0);
    TEST_ASSERT(seq->GetLength() == 11, "Sequence::Prepend через ListSequence", "ListSequence.cpp",
                "После Prepend, ожидаемая длина 11, получена " + std::to_string(seq->GetLength()));
    TEST_ASSERT(seq->Get(0) == 0, "Sequence::Prepend через ListSequence", "ListSequence.cpp",
                "После Prepend, Get(0) ожидалось 0, получено " + std::to_string(seq->Get(0)));
    
    delete seq;
    TEST_PASS("Полиморфизм Sequence с ListSequence", "ListSequence.cpp");
}

void testSequencePolymorphismWithImmutableArraySequence() {
    int arr[] = {5, 10, 15, 20};
    Sequence<int>* seq = new ImmutableArraySequence<int>(arr, 4);
    
    TEST_ASSERT(seq->GetLength() == 4, "Sequence::GetLength через ImmutableArraySequence", "ImmutableArraySequence.cpp",
                "GetLength() ожидалось 4, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 4; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence::Get через ImmutableArraySequence", "ImmutableArraySequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    try {
        seq->Append(25);
        TEST_ASSERT(false, "Sequence::Append через ImmutableArraySequence", "ImmutableArraySequence.cpp",
                    "Append для Immutable не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "Sequence::Append через ImmutableArraySequence", "ImmutableArraySequence.cpp",
                    "Append вывел неверное имя ошибки");
    }
    
    try {
        seq->Set(1, 99);
        TEST_ASSERT(false, "Sequence::Set через ImmutableArraySequence", "ImmutableArraySequence.cpp",
                    "Set для Immutable не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "Sequence::Set через ImmutableArraySequence", "ImmutableArraySequence.cpp",
                    "Set вывел неверное имя ошибки");
    }
    
    delete seq;
    TEST_PASS("Полиморфизм Sequence с ImmutableArraySequence", "ImmutableArraySequence.cpp");
}

void testSequencePolymorphismWithImmutableListSequence() {
    int arr[] = {100, 200, 300};
    Sequence<int>* seq = new ImmutableListSequence<int>(arr, 3);
    
    TEST_ASSERT(seq->GetLength() == 3, "Sequence::GetLength через ImmutableListSequence", "ImmutableListSequence.cpp",
                "GetLength() ожидалось 3, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence::Get через ImmutableListSequence", "ImmutableListSequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    try {
        seq->Prepend(50);
        TEST_ASSERT(false, "Sequence::Prepend через ImmutableListSequence", "ImmutableListSequence.cpp",
                    "Prepend для Immutable не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "Sequence::Prepend через ImmutableListSequence", "ImmutableListSequence.cpp",
                    "Prepend вывел неверное имя ошибки");
    }
    
    try {
        seq->InsertAt(999, 1);
        TEST_ASSERT(false, "Sequence::InsertAt через ImmutableListSequence", "ImmutableListSequence.cpp",
                    "InsertAt для Immutable не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "Sequence::InsertAt через ImmutableListSequence", "ImmutableListSequence.cpp",
                    "InsertAt вывел неверное имя ошибки");
    }
    
    delete seq;
    TEST_PASS("Полиморфизм Sequence с ImmutableListSequence", "ImmutableListSequence.cpp");
}

void testSequencePolymorphismWithAdaptiveSequence() {
    int arr[] = {1, 2, 3};
    Sequence<int>* seq = new AdaptiveSequence<int>(arr, 3);
    
    TEST_ASSERT(seq->GetLength() == 3, "Sequence::GetLength через AdaptiveSequence", "AdaptiveSequence.cpp",
                "GetLength() ожидалось 3, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence::Get через AdaptiveSequence", "AdaptiveSequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    seq->Append(4);
    seq->Append(5);
    
    TEST_ASSERT(seq->GetLength() == 5, "Sequence::Append через AdaptiveSequence", "AdaptiveSequence.cpp",
                "После Append, ожидаемая длина 5, получена " + std::to_string(seq->GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq->Get(i) == expected[i], "Sequence::Get через AdaptiveSequence", "AdaptiveSequence.cpp",
                    "После Append, Get(" + std::to_string(i) + ") ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    delete seq;
    TEST_PASS("Полиморфизм Sequence с AdaptiveSequence", "AdaptiveSequence.cpp");
}

void testSequenceMapViaBasePointer() {
    int arr[] = {1, 2, 3, 4, 5};
    Sequence<int>* seq = new ArraySequence<int>(arr, 5);
    
    auto multiplyBy2 = [](int x) { return x * 2; };
    
    Sequence<int>* result = seq->Map(multiplyBy2);
    
    TEST_ASSERT(result->GetLength() == 5, "Sequence::Map через ArraySequence", "ArraySequence.cpp",
                "После Map ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "Sequence::Map через ArraySequence", "ArraySequence.cpp",
                    "Результат Map по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete seq;
    delete result;
    TEST_PASS("Sequence::Map через указатель на Sequence", "ArraySequence.cpp");
}

void testSequenceWhereViaBasePointer() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Sequence<int>* seq = new ListSequence<int>(arr, 10);
    
    auto isGreaterThan5 = [](int x) { return x > 5; };
    
    Sequence<int>* result = seq->Where(isGreaterThan5);
    
    TEST_ASSERT(result->GetLength() == 5, "Sequence::Where через ListSequence", "ListSequence.cpp",
                "После Where ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {6, 7, 8, 9, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "Sequence::Where через ListSequence", "ListSequence.cpp",
                    "Результат Where по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete seq;
    delete result;
    TEST_PASS("Sequence::Where через указатель на Sequence", "ListSequence.cpp");
}

void testSequenceReduceViaBasePointer() {
    int arr[] = {1, 2, 3, 4, 5};
    Sequence<int>* seq = new ArraySequence<int>(arr, 5);
    
    auto sum = [](int acc, int x) { return acc + x; };
    
    int result = seq->Reduce(sum, 0);
    
    TEST_ASSERT(result == 15, "Sequence::Reduce через ArraySequence", "ArraySequence.cpp",
                "Reduce(sum) ожидалась 15, получена " + std::to_string(result));
    
    delete seq;
    TEST_PASS("Sequence::Reduce через указатель на Sequence", "ArraySequence.cpp");
}