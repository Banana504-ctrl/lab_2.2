#include "test_utils.h"
#include "../ListSequence.h"

void testListSequenceConstructorEmpty() {
    ListSequence<int> seq;
    
    TEST_ASSERT(seq.GetLength() == 0, "ListSequence::ListSequence()", "ListSequence.cpp",
                "GetLength() ожидалось 0, получено " + std::to_string(seq.GetLength()));
    
    TEST_PASS("ListSequence::ListSequence()", "ListSequence.cpp");
}

void testListSequenceConstructorFromArray() {
    int arr[] = {5, 10, 15, 20, 25, 30};
    ListSequence<int> seq(arr, 6);
    
    TEST_ASSERT(seq.GetLength() == 6, "ListSequence::ListSequence(T*, int)", "ListSequence.cpp",
                "GetLength() ожидалось 6, получено " + std::to_string(seq.GetLength()));
    
    for (int i = 0; i < 6; ++i) {
        TEST_ASSERT(seq.Get(i) == arr[i], "ListSequence::ListSequence(T*, int)", "ListSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::ListSequence(T*, int)", "ListSequence.cpp");
}

void testListSequenceGetFirst() {
    int arr[] = {100, 200, 300};
    ListSequence<int> seq(arr, 3);
    
    TEST_ASSERT(seq.GetFirst() == 100, "ListSequence::GetFirst", "ListSequence.cpp",
                "GetFirst() ожидалось 100, получено " + std::to_string(seq.GetFirst()));
    
    ListSequence<int> emptySeq;
    try {
        emptySeq.GetFirst();
        TEST_ASSERT(false, "ListSequence::GetFirst", "ListSequence.cpp",
                    "GetFirst() не вывел для пустой последовательности EMPTY_CONTAINER");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::EMPTY_CONTAINER, "ListSequence::GetFirst", "ListSequence.cpp",
                    "GetFirst() вывел неверной имя ошибки");
    }
    
    TEST_PASS("ListSequence::GetFirst", "ListSequence.cpp");
}

void testListSequenceGetLast() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    ListSequence<int> seq(arr, 6);
    
    TEST_ASSERT(seq.GetLast() == 6, "ListSequence::GetLast", "ListSequence.cpp",
                "GetLast() ожидалось 6, получено " + std::to_string(seq.GetLast()));
    
    TEST_PASS("ListSequence::GetLast", "ListSequence.cpp");
}

void testListSequenceGet() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    ListSequence<int> seq(arr, 9);
    
    for (int i = 0; i < 9; ++i) {
        TEST_ASSERT(seq.Get(i) == arr[i], "ListSequence::Get", "ListSequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    try {
        seq.Get(9);
        TEST_ASSERT(false, "ListSequence::Get", "ListSequence.cpp",
                    "Get(9) не вывел INDEX_OUT_OF_RANGE");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::INDEX_OUT_OF_RANGE, "ListSequence::Get", "ListSequence.cpp",
                    "Get(9) вывел неверное имя ошибки");
    }
    
    TEST_PASS("ListSequence::Get", "ListSequence.cpp");
}

void testListSequenceSet() {
    int arr[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(arr, 5);
    
    seq.Set(0, 100);
    seq.Set(2, 300);
    seq.Set(4, 500);
    
    int expected[] = {100, 2, 300, 4, 500};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ListSequence::Set", "ListSequence.cpp",
                    "После Set, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::Set", "ListSequence.cpp");
}

void testListSequenceAppend() {
    ListSequence<int> seq;
    
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);
    seq.Append(5);
    
    TEST_ASSERT(seq.GetLength() == 5, "ListSequence::Append", "ListSequence.cpp",
                "После 5 Appends, GetLength() ожидалось 5, получено " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ListSequence::Append", "ListSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::Append", "ListSequence.cpp");
}

void testListSequencePrepend() {
    ListSequence<int> seq;
    
    seq.Prepend(3);
    seq.Prepend(2);
    seq.Prepend(1);
    
    TEST_ASSERT(seq.GetLength() == 3, "ListSequence::Prepend", "ListSequence.cpp",
                "После 3 Prepends, GetLength() ожидалось 3, получено " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ListSequence::Prepend", "ListSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::Prepend", "ListSequence.cpp");
}

void testListSequenceInsertAt() {
    int arr[] = {1, 2, 4, 5};
    ListSequence<int> seq(arr, 4);
    
    seq.InsertAt(3, 2);
    
    TEST_ASSERT(seq.GetLength() == 5, "ListSequence::InsertAt", "ListSequence.cpp",
                "После InsertAt, GetLength() ожидалось 5, получено " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ListSequence::InsertAt", "ListSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::InsertAt", "ListSequence.cpp");
}

void testListSequenceMap() {
    int arr[] = {2, 4, 6, 8, 10};
    ListSequence<int> seq(arr, 5);
    
    auto divideBy2 = [](int x) { return x / 2; };
    
    Sequence<int>* result = seq.Map(divideBy2);
    
    TEST_ASSERT(result->GetLength() == 5, "ListSequence::Map", "ListSequence.cpp",
                "После Map ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "ListSequence::Map", "ListSequence.cpp",
                    "Результат Map по индексу" + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("ListSequence::Map", "ListSequence.cpp");
}

void testListSequenceWhere() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ListSequence<int> seq(arr, 10);
    
    auto isOdd = [](int x) { return x % 2 == 1; };
    
    Sequence<int>* result = seq.Where(isOdd);
    
    TEST_ASSERT(result->GetLength() == 5, "ListSequence::Where", "ListSequence.cpp",
                "После Where ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {1, 3, 5, 7, 9};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "ListSequence::Where", "ListSequence.cpp",
                    "Результат Where по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("ListSequence::Where", "ListSequence.cpp");
}

void testListSequenceReduce() {
    int arr[] = {1, 2, 3, 4};
    ListSequence<int> seq(arr, 4);
    
    auto sum = [](int acc, int x) { return acc + x; };
    auto max = [](int acc, int x) { return (acc > x) ? acc : x; };
    
    int sumResult = seq.Reduce(sum, 0);
    int maxResult = seq.Reduce(max, 0);
    
    TEST_ASSERT(sumResult == 10, "ListSequence::Reduce", "ListSequence.cpp",
                "Reduce(sum) ожидалось 10, получено " + std::to_string(sumResult));
    
    TEST_ASSERT(maxResult == 4, "ListSequence::Reduce", "ListSequence.cpp",
                "Reduce(max) ожидалось 4, получено " + std::to_string(maxResult));
    
    TEST_PASS("ListSequence::Reduce", "ListSequence.cpp");
}