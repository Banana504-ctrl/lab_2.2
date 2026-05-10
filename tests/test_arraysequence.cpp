#include "test_utils.h"
#include "../ArraySequence.h"

void testArraySequenceConstructorEmpty() {
    ArraySequence<int> seq;
    
    TEST_ASSERT(seq.GetLength() == 0, "ArraySequence::ArraySequence()", "ArraySequence.cpp",
                "GetLength() ожидалось 0, получено " + std::to_string(seq.GetLength()));
    
    TEST_PASS("ArraySequence::ArraySequence()", "ArraySequence.cpp");
}

void testArraySequenceConstructorFromArray() {
    int arr[] = {5, 10, 15, 20, 25};
    ArraySequence<int> seq(arr, 5);
    
    TEST_ASSERT(seq.GetLength() == 5, "ArraySequence::ArraySequence(T*, int)", "ArraySequence.cpp",
                "GetLength() ожидалось 5, получено " + std::to_string(seq.GetLength()));
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == arr[i], "ArraySequence::ArraySequence(T*, int)", "ArraySequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ArraySequence::ArraySequence(T*, int)", "ArraySequence.cpp");
}

void testArraySequenceGetFirst() {
    int arr[] = {10, 20, 30};
    ArraySequence<int> seq(arr, 3);
    
    TEST_ASSERT(seq.GetFirst() == 10, "ArraySequence::GetFirst", "ArraySequence.cpp",
                "GetFirst() ожидалось 10, получено " + std::to_string(seq.GetFirst()));
    
    ArraySequence<int> emptySeq;
    try {
        emptySeq.GetFirst();
        TEST_ASSERT(false, "ArraySequence::GetFirst", "ArraySequence.cpp",
                    "GetFirst() не вывел EMPTY_CONTAINER для пустой последовательности");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::EMPTY_CONTAINER, "ArraySequence::GetFirst", "ArraySequence.cpp",
                    "GetFirst() вывел неверное имя ошибки");
    }
    
    TEST_PASS("ArraySequence::GetFirst", "ArraySequence.cpp");
}

void testArraySequenceGetLast() {
    int arr[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(arr, 5);
    
    TEST_ASSERT(seq.GetLast() == 5, "ArraySequence::GetLast", "ArraySequence.cpp",
                "GetLast() ожидалось 5, получено " + std::to_string(seq.GetLast()));
    
    TEST_PASS("ArraySequence::GetLast", "ArraySequence.cpp");
}

void testArraySequenceGet() {
    int arr[] = {100, 200, 300, 400, 500, 600, 700, 800};
    ArraySequence<int> seq(arr, 8);
    
    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT(seq.Get(i) == arr[i], "ArraySequence::Get", "ArraySequence.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    try {
        seq.Get(8);
        TEST_ASSERT(false, "ArraySequence::Get", "ArraySequence.cpp",
                    "Get(8) не вывел INDEX_OUT_OF_RANGE");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::INDEX_OUT_OF_RANGE, "ArraySequence::Get", "ArraySequence.cpp",
                    "Get(8) вывел неверное имя ошибки");
    }
    
    TEST_PASS("ArraySequence::Get", "ArraySequence.cpp");
}

void testArraySequenceSet() {
    int arr[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(arr, 5);
    
    seq.Set(0, 10);
    seq.Set(2, 30);
    seq.Set(4, 50);
    
    int expected[] = {10, 2, 30, 4, 50};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ArraySequence::Set", "ArraySequence.cpp",
                    "После Set, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ArraySequence::Set", "ArraySequence.cpp");
}

void testArraySequenceAppend() {
    ArraySequence<int> seq;
    
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);
    seq.Append(5);
    
    TEST_ASSERT(seq.GetLength() == 5, "ArraySequence::Append", "ArraySequence.cpp",
                "После 5 Appends, для GetLength() ожидалось 5, получено " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ArraySequence::Append", "ArraySequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ArraySequence::Append", "ArraySequence.cpp");
}

void testArraySequencePrepend() {
    ArraySequence<int> seq;
    
    seq.Prepend(3);
    seq.Prepend(2);
    seq.Prepend(1);
    
    TEST_ASSERT(seq.GetLength() == 3, "ArraySequence::Prepend", "ArraySequence.cpp",
                "После 3 Prepends, в GetLength() ожидалось 3, получено " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ArraySequence::Prepend", "ArraySequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ArraySequence::Prepend", "ArraySequence.cpp");
}

void testArraySequenceInsertAt() {
    int arr[] = {1, 2, 4, 5};
    ArraySequence<int> seq(arr, 4);
    
    seq.InsertAt(3, 2);
    
    TEST_ASSERT(seq.GetLength() == 5, "ArraySequence::InsertAt", "ArraySequence.cpp",
                "После InsertAt, для GetLength() ожидалось 5, получено " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ArraySequence::InsertAt", "ArraySequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    seq.InsertAt(0, 0);
    int expected2[] = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < 6; ++i) {
        TEST_ASSERT(seq.Get(i) == expected2[i], "ArraySequence::InsertAt", "ArraySequence.cpp",
                    "После InsertAt(0,0), по индексу " + std::to_string(i) + " ожидплось " + std::to_string(expected2[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ArraySequence::InsertAt", "ArraySequence.cpp");
}

void testArraySequenceMap() {
    int arr[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(arr, 5);
    
    auto multiplyBy2 = [](int x) { return x * 2; };
    
    Sequence<int>* result = seq.Map(multiplyBy2);
    
    TEST_ASSERT(result->GetLength() == 5, "ArraySequence::Map", "ArraySequence.cpp",
                "После Map ожидаемая длина 5, получено " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "ArraySequence::Map", "ArraySequence.cpp",
                    "Зачение после Map по индексу" + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(result->Get(i)));
    }
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == arr[i], "ArraySequence::Map", "ArraySequence.cpp",
                    "Для неизменяемой последовательности по индексу " + std::to_string(i) + 
                    " ожидалось " + std::to_string(arr[i]) + ", получено " + std::to_string(seq.Get(i)));
    }
    
    delete result;
    TEST_PASS("ArraySequence::Map", "ArraySequence.cpp");
}

void testArraySequenceWhere() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ArraySequence<int> seq(arr, 10);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    
    Sequence<int>* result = seq.Where(isEven);
    
    TEST_ASSERT(result->GetLength() == 5, "ArraySequence::Where", "ArraySequence.cpp",
                "Ожидаемая длина после Where составляет 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "ArraySequence::Where", "ArraySequence.cpp",
                    "Результат Where по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("ArraySequence::Where", "ArraySequence.cpp");
}

void testArraySequenceReduce() {
    int arr[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(arr, 5);
    
    auto sum = [](int acc, int x) { return acc + x; };
    auto product = [](int acc, int x) { return acc * x; };
    
    int sumResult = seq.Reduce(sum, 0);
    int productResult = seq.Reduce(product, 1);
    
    TEST_ASSERT(sumResult == 15, "ArraySequence::Reduce", "ArraySequence.cpp",
                "Результатом Reduce(sum) ожидалось 15, получено " + std::to_string(sumResult));
    
    TEST_ASSERT(productResult == 120, "ArraySequence::Reduce", "ArraySequence.cpp",
                "Результатом Reduce(product) ожидалось 120, получено " + std::to_string(productResult));
    
    TEST_PASS("ArraySequence::Reduce", "ArraySequence.cpp");
}