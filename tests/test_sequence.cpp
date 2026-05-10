#include "test_utils.h"
#include "../ArraySequence.h"
#include "../ListSequence.h"
#include "../ImmutableArraySequence.h"
#include "../ImmutableListSequence.h"
#include "../AdaptiveSequence.h"

//Полиморфизм Sequence с ArraySequence

void testSequencePolymorphismWithArraySequence() {
    int arr[] = {10, 20, 30, 40, 50};
    Sequence<int>* seq = new ArraySequence<int>(arr, 5);
    
    TEST_ASSERT(seq->GetLength() == 5, "Sequence (ArraySequence)", "ArraySequence.cpp",
                "GetLength() ожидалось 5, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence (ArraySequence)", "ArraySequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    TEST_ASSERT(seq->GetFirst() == 10, "Sequence (ArraySequence)", "ArraySequence.cpp",
                "GetFirst() ожидалось 10, получено " + std::to_string(seq->GetFirst()));
    TEST_ASSERT(seq->GetLast() == 50, "Sequence (ArraySequence)", "ArraySequence.cpp",
                "GetLast() ожидалось 50, получено " + std::to_string(seq->GetLast()));
    
    seq->Set(2, 999);
    TEST_ASSERT(seq->Get(2) == 999, "Sequence (ArraySequence)", "ArraySequence.cpp",
                "После Set(2,999), Get(2) ожидалось 999, получено " + std::to_string(seq->Get(2)));
    
    seq->Append(60);
    TEST_ASSERT(seq->GetLength() == 6, "Sequence (ArraySequence)", "ArraySequence.cpp",
                "После Append, ожидаемая длина 6, получена " + std::to_string(seq->GetLength()));
    TEST_ASSERT(seq->Get(5) == 60, "Sequence (ArraySequence)", "ArraySequence.cpp",
                "После Append, Get(5) ожидалось 60, получено " + std::to_string(seq->Get(5)));
    
    delete seq;
    TEST_PASS("Sequence polymorphism with ArraySequence", "ArraySequence.cpp");
}

//Полиморфизм Sequence с ListSequence

void testSequencePolymorphismWithListSequence() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Sequence<int>* seq = new ListSequence<int>(arr, 10);
    
    TEST_ASSERT(seq->GetLength() == 10, "Sequence (ListSequence)", "ListSequence.cpp",
                "GetLength() ожидалось 10, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 10; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence (ListSequence)", "ListSequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    TEST_ASSERT(seq->GetFirst() == 1, "Sequence (ListSequence)", "ListSequence.cpp",
                "GetFirst() ожидалось 1, получено " + std::to_string(seq->GetFirst()));
    TEST_ASSERT(seq->GetLast() == 10, "Sequence (ListSequence)", "ListSequence.cpp",
                "GetLast() ожидалось 10, получено " + std::to_string(seq->GetLast()));
    
    seq->Prepend(0);
    TEST_ASSERT(seq->GetLength() == 11, "Sequence (ListSequence)", "ListSequence.cpp",
                "После Prepend, ожидаемая длина 11, получена " + std::to_string(seq->GetLength()));
    TEST_ASSERT(seq->Get(0) == 0, "Sequence (ListSequence)", "ListSequence.cpp",
                "После Prepend, Get(0) ожидалось 0, получено " + std::to_string(seq->Get(0)));
    
    delete seq;
    TEST_PASS("Sequence polymorphism with ListSequence", "ListSequence.cpp");
}

//Полиморфизм Sequence с ImmutableArraySequence

void testSequencePolymorphismWithImmutableArraySequence() {
    int arr[] = {5, 10, 15, 20};
    Sequence<int>* seq = new ImmutableArraySequence<int>(arr, 4);
    
    TEST_ASSERT(seq->GetLength() == 4, "Sequence (ImmutableArraySequence)", "ImmutableArraySequence.cpp",
                "GetLength() ожидалось 4, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 4; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence (ImmutableArraySequence)", "ImmutableArraySequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    // Проверка на вывод исключений для Immutable
    try {
        seq->Append(25);
        TEST_ASSERT(false, "Sequence (ImmutableArraySequence)", "ImmutableArraySequence.cpp",
                    "Append для Immutable не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "Sequence (ImmutableArraySequence)", "ImmutableArraySequence.cpp",
                    "Append вывел неверное имя ошибки");
    }
    
    try {
        seq->Set(1, 99);
        TEST_ASSERT(false, "Sequence (ImmutableArraySequence)", "ImmutableArraySequence.cpp",
                    "Set для Immutable не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "Sequence (ImmutableArraySequence)", "ImmutableArraySequence.cpp",
                    "Set вывел неверное имя ошибки");
    }
    
    delete seq;
    TEST_PASS("Sequence polymorphism with ImmutableArraySequence", "ImmutableArraySequence.cpp");
}

//Полиморфизм Sequence с ImmutableListSequence

void testSequencePolymorphismWithImmutableListSequence() {
    int arr[] = {100, 200, 300};
    Sequence<int>* seq = new ImmutableListSequence<int>(arr, 3);
    
    TEST_ASSERT(seq->GetLength() == 3, "Sequence (ImmutableListSequence)", "ImmutableListSequence.cpp",
                "GetLength() ожидалось 3, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence (ImmutableListSequence)", "ImmutableListSequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    try {
        seq->Prepend(50);
        TEST_ASSERT(false, "Sequence (ImmutableListSequence)", "ImmutableListSequence.cpp",
                    "Prepend для Immutable не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "Sequence (ImmutableListSequence)", "ImmutableListSequence.cpp",
                    "Prepend вывел неверное имя ошибки");
    }
    
    try {
        seq->InsertAt(999, 1);
        TEST_ASSERT(false, "Sequence (ImmutableListSequence)", "ImmutableListSequence.cpp",
                    "InsertAt для Immutable не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "Sequence (ImmutableListSequence)", "ImmutableListSequence.cpp",
                    "InsertAt вывел неверное имя ошибки");
    }
    
    delete seq;
    TEST_PASS("Sequence polymorphism with ImmutableListSequence", "ImmutableListSequence.cpp");
}

//Полиморфизм Sequence с AdaptiveSequence

void testSequencePolymorphismWithAdaptiveSequence() {
    int arr[] = {1, 2, 3};
    Sequence<int>* seq = new AdaptiveSequence<int>(arr, 3);
    
    TEST_ASSERT(seq->GetLength() == 3, "Sequence (AdaptiveSequence)", "AdaptiveSequence.cpp",
                "GetLength() ожидалось 3, получено " + std::to_string(seq->GetLength()));
    
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq->Get(i) == arr[i], "Sequence (AdaptiveSequence)", "AdaptiveSequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    seq->Append(4);
    seq->Append(5);
    
    TEST_ASSERT(seq->GetLength() == 5, "Sequence (AdaptiveSequence)", "AdaptiveSequence.cpp",
                "После Append, ожидаемая длина 5, получена " + std::to_string(seq->GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq->Get(i) == expected[i], "Sequence (AdaptiveSequence)", "AdaptiveSequence.cpp",
                    "После Append, Get(" + std::to_string(i) + ") ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq->Get(i)));
    }
    
    delete seq;
    TEST_PASS("Sequence polymorphism with AdaptiveSequence", "AdaptiveSequence.cpp");
}

// Sequence Map через указатель на базовый класс

void testSequenceMapViaBasePointer() {
    int arr[] = {1, 2, 3, 4, 5};
    Sequence<int>* seq = new ArraySequence<int>(arr, 5);
    
    auto multiplyBy2 = [](int x) { return x * 2; };
    
    Sequence<int>* result = seq->Map(multiplyBy2);
    
    TEST_ASSERT(result->GetLength() == 5, "Sequence::Map via pointer", "ArraySequence.cpp",
                "После Map ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "Sequence::Map via pointer", "ArraySequence.cpp",
                    "Результат Map по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete seq;
    delete result;
    TEST_PASS("Sequence::Map via base pointer", "ArraySequence.cpp");
}

//Sequence Where через указатель на базовый класс

void testSequenceWhereViaBasePointer() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Sequence<int>* seq = new ListSequence<int>(arr, 10);
    
    auto isGreaterThan5 = [](int x) { return x > 5; };
    
    Sequence<int>* result = seq->Where(isGreaterThan5);
    
    TEST_ASSERT(result->GetLength() == 5, "Sequence::Where via pointer", "ListSequence.cpp",
                "После Where ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {6, 7, 8, 9, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "Sequence::Where via pointer", "ListSequence.cpp",
                    "Результат Where по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete seq;
    delete result;
    TEST_PASS("Sequence::Where via base pointer", "ListSequence.cpp");
}

//Sequence Reduce через указатель на базовый класс

void testSequenceReduceViaBasePointer() {
    int arr[] = {1, 2, 3, 4, 5};
    Sequence<int>* seq = new ArraySequence<int>(arr, 5);
    
    auto sum = [](int acc, int x) { return acc + x; };
    
    int result = seq->Reduce(sum, 0);
    
    TEST_ASSERT(result == 15, "Sequence::Reduce via pointer", "ArraySequence.cpp",
                "Reduce(sum) ожидалась 15, получена " + std::to_string(result));
    
    delete seq;
    TEST_PASS("Sequence::Reduce via base pointer", "ArraySequence.cpp");
}