#include "test_utils.h"
#include "../AdaptiveSequence.h"

void testAdaptiveSequenceConstructorEmpty() {
    AdaptiveSequence<int> seq;
    
    TEST_ASSERT(seq.GetLength() == 0, "AdaptiveSequence::AdaptiveSequence()", "AdaptiveSequence.cpp",
                "GetLength() ожидалось 0, получено " + std::to_string(seq.GetLength()));
    TEST_ASSERT(seq.GetCurrentMode() == StorageMode::ARRAY, "AdaptiveSequence::AdaptiveSequence()", "AdaptiveSequence.cpp",
                "Режим по умлочанию должен быть ARRAY");
    
    TEST_PASS("AdaptiveSequence::AdaptiveSequence()", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceConstructorFromArray() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    AdaptiveSequence<int> seq(arr, 10);
    
    TEST_ASSERT(seq.GetLength() == 10, "AdaptiveSequence::AdaptiveSequence(T*, int)", "AdaptiveSequence.cpp",
                "GetLength() ожидалось 10, получено " + std::to_string(seq.GetLength()));
    
    for (int i = 0; i < 10; ++i) {
        TEST_ASSERT(seq.Get(i) == arr[i], "AdaptiveSequence::AdaptiveSequence(T*, int)", "AdaptiveSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::AdaptiveSequence(T*, int)", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceSwitchModeEvenOdd() {
    int arr[] = {1, 2, 3, 4, 5};
    AdaptiveSequence<int> seq(arr, 5);
    
    int switchCount = 0;

    TEST_ASSERT(seq.GetCurrentMode() == StorageMode::ARRAY, "AdaptiveSequence::SwitchMode", "AdaptiveSequence.cpp",
                "При чётном переключении, начиная с нулевого, режим должен быть ARRAY");
    
    for (int i = 1; i <= 5; ++i) {
        seq.SwitchMode();
        switchCount++;
        
        if (switchCount % 2 == 1) {
            TEST_ASSERT(seq.GetCurrentMode() == StorageMode::LIST, "AdaptiveSequence::SwitchMode", "AdaptiveSequence.cpp",
                        "При " + std::to_string(switchCount) + " нечётном переключении режим должен быть LIST");
        } else {
            TEST_ASSERT(seq.GetCurrentMode() == StorageMode::ARRAY, "AdaptiveSequence::SwitchMode", "AdaptiveSequence.cpp",
                        "При " + std::to_string(switchCount) + " чётном переключении режим должен быть ARRAY");
        }
    }
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == arr[i], "AdaptiveSequence::SwitchMode", "AdaptiveSequence.cpp",
                    "После " + std::to_string(switchCount) + " переключений, по индексу " + std::to_string(i) + 
                    " ожидалось " + std::to_string(arr[i]) + ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::SwitchMode", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceAppend() {
    AdaptiveSequence<int> seq;
    
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);
    seq.Append(5);
    
    TEST_ASSERT(seq.GetLength() == 5, "AdaptiveSequence::Append", "AdaptiveSequence.cpp",
                "После 5 Appends, ожидаемая длина 5, получена " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "AdaptiveSequence::Append", "AdaptiveSequence.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::Append", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceAppendAfterSwitch() {
    AdaptiveSequence<int> seq;
    
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    
    seq.SwitchMode();
    
    seq.Append(4);
    seq.Append(5);
    
    TEST_ASSERT(seq.GetLength() == 5, "AdaptiveSequence::Append", "AdaptiveSequence.cpp",
                "После Append в режиме LIST, ожидаемая длина 5, получена " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "AdaptiveSequence::Append", "AdaptiveSequence.cpp",
                    "После смены режима и Append по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::Append", "AdaptiveSequence.cpp");
}

void testAdaptiveSequencePrepend() {
    AdaptiveSequence<int> seq;
    
    seq.Prepend(3);
    seq.Prepend(2);
    seq.Prepend(1);
    
    TEST_ASSERT(seq.GetLength() == 3, "AdaptiveSequence::Prepend", "AdaptiveSequence.cpp",
                "После 3 Prepends, ожидаемая длина 3, получена " + std::to_string(seq.GetLength()));
    
    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "AdaptiveSequence::Prepend", "AdaptiveSequence.cpp",
                    "По индексу " + std::to_string(i) + " получено " + std::to_string(expected[i]) + 
                    ", ожидалось " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::Prepend", "AdaptiveSequence.cpp");
}

void testAdaptiveSequencePrependAfterSwitch() {
    AdaptiveSequence<int> seq;
    
    seq.Append(3);
    seq.Append(4);
    seq.Append(5);
    
    seq.SwitchMode();
    
    seq.Prepend(2);
    seq.Prepend(1);
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "AdaptiveSequence::Prepend", "AdaptiveSequence.cpp",
                    "После смены режима и Prepend, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", got " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::Prepend", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceInsertAt() {
    int arr[] = {1, 2, 4, 5};
    AdaptiveSequence<int> seq(arr, 4);
    
    seq.InsertAt(3, 2);
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "AdaptiveSequence::InsertAt", "AdaptiveSequence.cpp",
                    "После InsertAt, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::InsertAt", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceInsertAtAfterSwitch() {
    int arr[] = {1, 2, 4, 5};
    AdaptiveSequence<int> seq(arr, 4);
    
    seq.SwitchMode();
    seq.InsertAt(3, 2);
    
    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "AdaptiveSequence::InsertAt", "AdaptiveSequence.cpp",
                    "После смены режима и InsertAt, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::InsertAt", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceGetFirst() {
    int arr[] = {100, 200, 300};
    AdaptiveSequence<int> seq(arr, 3);
    
    TEST_ASSERT(seq.GetFirst() == 100, "AdaptiveSequence::GetFirst", "AdaptiveSequence.cpp",
                "GetFirst() ожидалось 100, получено " + std::to_string(seq.GetFirst()));
    
    seq.SwitchMode();
    TEST_ASSERT(seq.GetFirst() == 100, "AdaptiveSequence::GetFirst", "AdaptiveSequence.cpp",
                "После смены режима в GetFirst() ожилалось 100, получено " + std::to_string(seq.GetFirst()));
    
    TEST_PASS("AdaptiveSequence::GetFirst", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceGetLast() {
    int arr[] = {1, 2, 3, 4, 5};
    AdaptiveSequence<int> seq(arr, 5);
    
    TEST_ASSERT(seq.GetLast() == 5, "AdaptiveSequence::GetLast", "AdaptiveSequence.cpp",
                "GetLast() ожидалось 5, получено " + std::to_string(seq.GetLast()));
    
    seq.SwitchMode();
    TEST_ASSERT(seq.GetLast() == 5, "AdaptiveSequence::GetLast", "AdaptiveSequence.cpp",
                "После смены режима в GetLast() ожидалось 5, получено " + std::to_string(seq.GetLast()));
    
    TEST_PASS("AdaptiveSequence::GetLast", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceSet() {
    int arr[] = {1, 2, 3, 4, 5};
    AdaptiveSequence<int> seq(arr, 5);
    
    seq.Set(0, 10);
    seq.Set(2, 30);
    seq.Set(4, 50);
    
    int expected[] = {10, 2, 30, 4, 50};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected[i], "AdaptiveSequence::Set", "AdaptiveSequence.cpp",
                    "После Set в режиме ARRAY, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    seq.SwitchMode();
    seq.Set(1, 20);
    seq.Set(3, 40);
    
    int expected2[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq.Get(i) == expected2[i], "AdaptiveSequence::Set", "AdaptiveSequence.cpp",
                    "После Set в режиме LIST, по индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected2[i]) + 
                    ", получено " + std::to_string(seq.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::Set", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceMap() {
    int arr[] = {1, 2, 3, 4, 5};
    AdaptiveSequence<int> seq(arr, 5);
    
    auto multiplyBy3 = [](int x) { return x * 3; };
    
    Sequence<int>* result = seq.Map(multiplyBy3);
    
    TEST_ASSERT(result->GetLength() == 5, "AdaptiveSequence::Map", "AdaptiveSequence.cpp",
                "После Map ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {3, 6, 9, 12, 15};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "AdaptiveSequence::Map", "AdaptiveSequence.cpp",
                    "Резльтат Map по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("AdaptiveSequence::Map", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceMapAfterSwitch() {
    int arr[] = {1, 2, 3, 4, 5};
    AdaptiveSequence<int> seq(arr, 5);
    
    seq.SwitchMode();
    
    auto multiplyBy2 = [](int x) { return x * 2; };
    
    Sequence<int>* result = seq.Map(multiplyBy2);
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "AdaptiveSequence::Map", "AdaptiveSequence.cpp",
                    "Результат Map после смены режима по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("AdaptiveSequence::Map", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceWhere() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    AdaptiveSequence<int> seq(arr, 10);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    
    Sequence<int>* result = seq.Where(isEven);
    
    TEST_ASSERT(result->GetLength() == 5, "AdaptiveSequence::Where", "AdaptiveSequence.cpp",
                "После Where ожидаемая длина 5, получена " + std::to_string(result->GetLength()));
    
    int expected[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(result->Get(i) == expected[i], "AdaptiveSequence::Where", "AdaptiveSequence.cpp",
                    "Результат Where по индексу " + std::to_string(i) + " ожидался " + std::to_string(expected[i]) + 
                    ", получен " + std::to_string(result->Get(i)));
    }
    
    delete result;
    TEST_PASS("AdaptiveSequence::Where", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceReduce() {
    int arr[] = {1, 2, 3, 4, 5};
    AdaptiveSequence<int> seq(arr, 5);
    
    auto sum = [](int acc, int x) { return acc + x; };
    
    int result = seq.Reduce(sum, 0);
    
    TEST_ASSERT(result == 15, "AdaptiveSequence::Reduce", "AdaptiveSequence.cpp",
                "Reduce(sum) ожидалось 15, получено " + std::to_string(result));
    
    seq.SwitchMode();
    result = seq.Reduce(sum, 0);
    
    TEST_ASSERT(result == 15, "AdaptiveSequence::Reduce", "AdaptiveSequence.cpp",
                "После смены режима Reduce(sum) ожидалось 15, получено " + std::to_string(result));
    
    TEST_PASS("AdaptiveSequence::Reduce", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceCopyConstructor() {
    int arr[] = {1, 2, 3, 4, 5};
    AdaptiveSequence<int> seq1(arr, 5);
    seq1.SwitchMode();
    
    AdaptiveSequence<int> seq2(seq1);
    
    TEST_ASSERT(seq2.GetLength() == 5, "AdaptiveSequence::AdaptiveSequence(const AdaptiveSequence&)", "AdaptiveSequence.cpp",
                "После копирования ожидаемая длина 5, получена " + std::to_string(seq2.GetLength()));
    TEST_ASSERT(seq2.GetCurrentMode() == StorageMode::LIST, "AdaptiveSequence::AdaptiveSequence(const AdaptiveSequence&)", "AdaptiveSequence.cpp",
                "Ожидаемый режим копии LIST");
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq2.Get(i) == arr[i], "AdaptiveSequence::AdaptiveSequence(const AdaptiveSequence&)", "AdaptiveSequence.cpp",
                    "В копии по индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(seq2.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::AdaptiveSequence(const AdaptiveSequence&)", "AdaptiveSequence.cpp");
}

void testAdaptiveSequenceAssignment() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30, 40, 50, 60};
    AdaptiveSequence<int> seq1(arr1, 5);
    AdaptiveSequence<int> seq2(arr2, 6);
    
    seq1.SwitchMode();
    seq2 = seq1;
    
    TEST_ASSERT(seq2.GetLength() == 5, "AdaptiveSequence::operator=", "AdaptiveSequence.cpp",
                "После присваивания ожидаемая длина 5, получена " + std::to_string(seq2.GetLength()));
    TEST_ASSERT(seq2.GetCurrentMode() == StorageMode::LIST, "AdaptiveSequence::operator=", "AdaptiveSequence.cpp",
                "После присваивания ожидаемый режим LIST");
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(seq2.Get(i) == arr1[i], "AdaptiveSequence::operator=", "AdaptiveSequence.cpp",
                    "После присваивания по индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr1[i]) + 
                    ", получено " + std::to_string(seq2.Get(i)));
    }
    
    TEST_PASS("AdaptiveSequence::operator=", "AdaptiveSequence.cpp");
}