#include "test_utils.h"
#include "../ArraySequence.h"
#include "../ListSequence.h"
#include "../ImmutableArraySequence.h"
#include "../ImmutableListSequence.h"

/*Mutable ArraySequence*/

void testMutableArraySequenceAppend() {
    ArraySequence<int> seq;
    
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    
    TEST_ASSERT(seq.GetLength() == 3, "ArraySequence::Append (mutable)", "ArraySequence.cpp",
                "Ожидаемая длина 3, полученная " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ArraySequence::Append (mutable)", "ArraySequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ArraySequence::Append (mutable)", "ArraySequence.cpp");
}

void testMutableArraySequencePrepend() {
    ArraySequence<int> seq;
    
    seq.Prepend(3);
    seq.Prepend(2);
    seq.Prepend(1);
    
    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ArraySequence::Prepend (mutable)", "ArraySequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ArraySequence::Prepend (mutable)", "ArraySequence.cpp");
}

void testMutableArraySequenceSet() {
    int arr[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(arr, 5);
    
    seq.Set(0, 100);
    seq.Set(2, 300);
    seq.Set(4, 500);
    
    int expected[] = {100, 2, 300, 4, 500};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ArraySequence::Set (mutable)", "ArraySequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ArraySequence::Set (mutable)", "ArraySequence.cpp");
}

/*Immutable ArraySequence*/

void testImmutableArraySequenceDoesNotModifyOriginal() {
    int arr[] = {1, 2, 3};
    ImmutableArraySequence<int> seq1(arr, 3);
    
    ImmutableArraySequence<int>* seq2 = seq1.AppendImmutable(4);
    
    TEST_ASSERT(seq1.GetLength() == 3, "ImmutableArraySequence::AppendImmutable", "ImmutableArraySequence.cpp",
                "Исходная длина должна остаться 3, получена " + std::to_string(seq1.GetLength()));
    TEST_ASSERT(seq2->GetLength() == 4, "ImmutableArraySequence::AppendImmutable", "ImmutableArraySequence.cpp",
                "Длина новой последовательности должна быть 4, получена " + std::to_string(seq2->GetLength()));
    
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq1.Get(i) == arr[i], "ImmutableArraySequence::AppendImmutable", "ImmutableArraySequence.cpp",
                    "Исходник по индексу " + std::to_string(i) + " ожидался " + std::to_string(arr[i]) + 
                    ", получен " + std::to_string(seq1.Get(i)));
    }
    
    delete seq2;
    TEST_PASS("ImmutableArraySequence::AppendImmutable", "ImmutableArraySequence.cpp");
}

void testImmutableArraySequenceAppendImmutable() {
    int arr[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(arr, 3);
    
    ImmutableArraySequence<int>* seq2 = seq.AppendImmutable(4);
    ImmutableArraySequence<int>* seq3 = seq2->AppendImmutable(5);
    
    int expected1[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq.Get(i) == expected1[i], "ImmutableArraySequence::AppendImmutable", "ImmutableArraySequence.cpp",
                    "Исходник по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected1[i]) + 
                    ", получен " + std::to_string(seq.Get(i)));
    }
    
    int expected2[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; ++i) {
        TEST_ASSERT(seq2->Get(i) == expected2[i], "ImmutableArraySequence::AppendImmutable", "ImmutableArraySequence.cpp",
                    "После первого Append, по индексу ожидалось" + std::to_string(i) + " expected " + std::to_string(expected2[i]) + 
                    ", got " + std::to_string(seq2->Get(i)));
    }
    
    int expected3[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq3->Get(i) == expected3[i], "ImmutableArraySequence::AppendImmutable", "ImmutableArraySequence.cpp",
                    "После второго Append по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected3[i]) + 
                    ", получено " + std::to_string(seq3->Get(i)));
    }
    
    delete seq2;
    delete seq3;
    TEST_PASS("ImmutableArraySequence::AppendImmutable", "ImmutableArraySequence.cpp");
}

void testImmutableArraySequencePrependImmutable() {
    int arr[] = {3, 4, 5};
    ImmutableArraySequence<int> seq(arr, 3);
    
    ImmutableArraySequence<int>* seq2 = seq.PrependImmutable(2);
    ImmutableArraySequence<int>* seq3 = seq2->PrependImmutable(1);
    
    int expected3[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq3->Get(i) == expected3[i], "ImmutableArraySequence::PrependImmutable", "ImmutableArraySequence.cpp",
                    "После Prepends, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected3[i]) + 
                    ", получено " + std::to_string(seq3->Get(i)));
    }
    
    delete seq2;
    delete seq3;
    TEST_PASS("ImmutableArraySequence::PrependImmutable", "ImmutableArraySequence.cpp");
}

void testImmutableArraySequenceInsertAtImmutable() {
    int arr[] = {1, 2, 4, 5};
    ImmutableArraySequence<int> seq(arr, 4);
    
    ImmutableArraySequence<int>* seq2 = seq.InsertAtImmutable(3, 2);
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq2->Get(i) == expected[i], "ImmutableArraySequence::InsertAtImmutable", "ImmutableArraySequence.cpp",
                    "После InsertAt по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", поулчено " + std::to_string(seq2->Get(i)));
    }
    
    TEST_ASSERT(seq.GetLength() == 4, "ImmutableArraySequence::InsertAtImmutable", "ImmutableArraySequence.cpp",
                "Исходная длина должна оставаться 4, получена " + std::to_string(seq.GetLength()));
    
    delete seq2;
    TEST_PASS("ImmutableArraySequence::InsertAtImmutable", "ImmutableArraySequence.cpp");
}

void testImmutableArraySequenceMutableMethodsThrow() {
    int arr[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(arr, 3);
    
    try {
        seq.Append(4);
        TEST_ASSERT(false, "ImmutableArraySequence::Append", "ImmutableArraySequence.cpp",
                    "Append не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "ImmutableArraySequence::Append", "ImmutableArraySequence.cpp",
                    "Append вывел неверное имя ошибки");
    }
    
    try {
        seq.Prepend(0);
        TEST_ASSERT(false, "ImmutableArraySequence::Prepend", "ImmutableArraySequence.cpp",
                    "Prepend не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "ImmutableArraySequence::Prepend", "ImmutableArraySequence.cpp",
                    "Prepend вывел неверное имя ошибки");
    }
    
    try {
        seq.Set(1, 999);
        TEST_ASSERT(false, "ImmutableArraySequence::Set", "ImmutableArraySequence.cpp",
                    "Set не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "ImmutableArraySequence::Set", "ImmutableArraySequence.cpp",
                    "Set вывел неверное имя ошибки");
    }
    
    TEST_PASS("ImmutableArraySequence mutable methods", "ImmutableArraySequence.cpp");
}

/*Mutable ListSequence*/
void testMutableListSequenceAppend() {
    ListSequence<int> seq;
    
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);
    seq.Append(5);
    
    TEST_ASSERT(seq.GetLength() == 5, "ListSequence::Append (mutable)", "ListSequence.cpp",
                "Ожидаемая длина 5, получена " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ListSequence::Append (mutable)", "ListSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::Append (mutable)", "ListSequence.cpp");
}

void testMutableListSequencePrepend() {
    ListSequence<int> seq;
    
    seq.Prepend(5);
    seq.Prepend(4);
    seq.Prepend(3);
    seq.Prepend(2);
    seq.Prepend(1);
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ListSequence::Prepend (mutable)", "ListSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::Prepend (mutable)", "ListSequence.cpp");
}

void testMutableListSequenceInsertAt() {
    int arr[] = {1, 2, 4, 5};
    ListSequence<int> seq(arr, 4);
    
    seq.InsertAt(3, 2);
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ListSequence::InsertAt (mutable)", "ListSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    seq.InsertAt(0, 0);
    int expected2[] = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < 6; ++i) {
        TEST_ASSERT(seq.Get(i) == expected2[i], "ListSequence::InsertAt (mutable)", "ListSequence.cpp",
                    "После добавления в начало по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected2[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::InsertAt (mutable)", "ListSequence.cpp");
}

void testMutableListSequenceSet() {
    int arr[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(arr, 5);
    
    seq.Set(0, 100);
    seq.Set(2, 300);
    seq.Set(4, 500);
    
    int expected[] = {100, 2, 300, 4, 500};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "ListSequence::Set (mutable)", "ListSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("ListSequence::Set (mutable)", "ListSequence.cpp");
}

void testMutableListSequenceMap() {
    int arr[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(arr, 5);
    
    auto multiplyBy2 = [](int x) { return x * 2; };
    
    Sequence<int>* result = seq.Map(multiplyBy2);
    
    TEST_ASSERT(result->GetLength() == 5, "ListSequence::Map (mutable)", "ListSequence.cpp",
                "После Map ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "ListSequence::Map (mutable)", "ListSequence.cpp",
                    "Результат Map по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    // Исходник не должен измениться
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == arr[i], "ListSequence::Map (mutable)", "ListSequence.cpp",
                    "Исходник по индексу " + std::to_string(i) + " ожидался " + std::to_string(arr[i]) + 
                    ", получен " + std::to_string(seq.Get(i)));
    }
    
    delete result;
    TEST_PASS("ListSequence::Map (mutable)", "ListSequence.cpp");
}

void testMutableListSequenceWhere() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ListSequence<int> seq(arr, 10);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    
    Sequence<int>* result = seq.Where(isEven);
    
    TEST_ASSERT(result->GetLength() == 5, "ListSequence::Where (mutable)", "ListSequence.cpp",
                "После Where ожидалась длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "ListSequence::Where (mutable)", "ListSequence.cpp",
                    "Результат Where по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("ListSequence::Where (mutable)", "ListSequence.cpp");
}

void testMutableListSequenceReduce() {
    int arr[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(arr, 5);
    
    auto sum = [](int acc, int x) { return acc + x; };
    auto product = [](int acc, int x) { return acc * x; };
    
    int sumResult = seq.Reduce(sum, 0);
    int productResult = seq.Reduce(product, 1);
    
    TEST_ASSERT(sumResult == 15, "ListSequence::Reduce (mutable)", "ListSequence.cpp",
                "Reduce(sum) ожидалось 15, получено " + std::to_string(sumResult));
    
    TEST_ASSERT(productResult == 120, "ListSequence::Reduce (mutable)", "ListSequence.cpp",
                "Reduce(product) ожидалось 120, получено " + std::to_string(productResult));
    
    TEST_PASS("ListSequence::Reduce (mutable)", "ListSequence.cpp");
}

/*Immutable ListSequence*/

void testImmutableListSequenceDoesNotModifyOriginal() {
    int arr[] = {1, 2, 3};
    ImmutableListSequence<int> seq1(arr, 3);
    
    ImmutableListSequence<int>* seq2 = seq1.AppendImmutable(4);
    
    TEST_ASSERT(seq1.GetLength() == 3, "ImmutableListSequence::AppendImmutable", "ImmutableListSequence.cpp",
                "Длина исходной последовательности должна оставаться 3, получена " + std::to_string(seq1.GetLength()));
    TEST_ASSERT(seq2->GetLength() == 4, "ImmutableListSequence::AppendImmutable", "ImmutableListSequence.cpp",
                "Длина новой последовательности должна быть 4, получена " + std::to_string(seq2->GetLength()));
    
    delete seq2;
    TEST_PASS("ImmutableListSequence::AppendImmutable", "ImmutableListSequence.cpp");
}

void testImmutableListSequenceAppendImmutable() {
    int arr[] = {1, 2, 3};
    ImmutableListSequence<int> seq(arr, 3);
    
    ImmutableListSequence<int>* seq2 = seq.AppendImmutable(4);
    ImmutableListSequence<int>* seq3 = seq2->AppendImmutable(5);
    
    int expected3[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq3->Get(i) == expected3[i], "ImmutableListSequence::AppendImmutable", "ImmutableListSequence.cpp",
                    "После Appends, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected3[i]) + 
                    ", получено " + std::to_string(seq3->Get(i)));
    }
    
    delete seq2;
    delete seq3;
    TEST_PASS("ImmutableListSequence::AppendImmutable", "ImmutableListSequence.cpp");
}

void testImmutableListSequencePrependImmutable() {
    int arr[] = {3, 4, 5};
    ImmutableListSequence<int> seq(arr, 3);
    
    ImmutableListSequence<int>* seq2 = seq.PrependImmutable(2);
    ImmutableListSequence<int>* seq3 = seq2->PrependImmutable(1);
    
    int expected3[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq3->Get(i) == expected3[i], "ImmutableListSequence::PrependImmutable", "ImmutableListSequence.cpp",
                    "После Prepends, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected3[i]) + 
                    ", получено " + std::to_string(seq3->Get(i)));
    }
    
    delete seq2;
    delete seq3;
    TEST_PASS("ImmutableListSequence::PrependImmutable", "ImmutableListSequence.cpp");
}

void testImmutableListSequenceInsertAtImmutable() {
    int arr[] = {1, 2, 4, 5};
    ImmutableListSequence<int> seq(arr, 4);
    
    ImmutableListSequence<int>* seq2 = seq.InsertAtImmutable(3, 2);
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq2->Get(i) == expected[i], "ImmutableListSequence::InsertAtImmutable", "ImmutableListSequence.cpp",
                    "После InsertAt, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq2->Get(i)));
    }
    
    delete seq2;
    TEST_PASS("ImmutableListSequence::InsertAtImmutable", "ImmutableListSequence.cpp");
}

void testImmutableListSequenceMutableMethodsThrow() {
    int arr[] = {1, 2, 3};
    ImmutableListSequence<int> seq(arr, 3);
    
    try {
        seq.Append(4);
        TEST_ASSERT(false, "ImmutableListSequence::Append", "ImmutableListSequence.cpp",
                    "Append не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "ImmutableListSequence::Append", "ImmutableListSequence.cpp",
                    "Append вывел неверное имя ошибки");
    }
    
    try {
        seq.Prepend(0);
        TEST_ASSERT(false, "ImmutableListSequence::Prepend", "ImmutableListSequence.cpp",
                    "Prepend не вывел OPERATION_NOT_ALLOWED");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::OPERATION_NOT_ALLOWED, "ImmutableListSequence::Prepend", "ImmutableListSequence.cpp",
                    "Prepend вывел неверное имя ошибки");
    }
    
    TEST_PASS("ImmutableListSequence mutable methods", "ImmutableListSequence.cpp");
}

void testImmutableListSequenceMap() {
    int arr[] = {1, 2, 3, 4, 5};
    ImmutableListSequence<int> seq(arr, 5);
    
    auto multiplyBy2 = [](int x) { return x * 2; };
    
    Sequence<int>* result = seq.Map(multiplyBy2);
    
    TEST_ASSERT(result->GetLength() == 5, "ImmutableListSequence::Map", "ImmutableListSequence.cpp",
                "После Map ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "ImmutableListSequence::Map", "ImmutableListSequence.cpp",
                    "Результат Map по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("ImmutableListSequence::Map", "ImmutableListSequence.cpp");
}

void testImmutableListSequenceWhere() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ImmutableListSequence<int> seq(arr, 10);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    
    Sequence<int>* result = seq.Where(isEven);
    
    TEST_ASSERT(result->GetLength() == 5, "ImmutableListSequence::Where", "ImmutableListSequence.cpp",
                "После Where ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "ImmutableListSequence::Where", "ImmutableListSequence.cpp",
                    "Результат Where по индексу" + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("ImmutableListSequence::Where", "ImmutableListSequence.cpp");
}

void testImmutableListSequenceReduce() {
    int arr[] = {1, 2, 3, 4, 5};
    ImmutableListSequence<int> seq(arr, 5);
    
    auto sum = [](int acc, int x) { return acc + x; };
    
    int result = seq.Reduce(sum, 0);
    
    TEST_ASSERT(result == 15, "ImmutableListSequence::Reduce", "ImmutableListSequence.cpp",
                "Reduce(sum) ожидалось 15, получено " + std::to_string(result));
    
    TEST_PASS("ImmutableListSequence::Reduce", "ImmutableListSequence.cpp");
}