#include "test_utils.h"
#include "../DynamicArray.h"
#include <iostream>

void testDynamicArrayConstructorFromArray() {
    int arr[] = {1, 2, 3, 4, 5};
    DynamicArray<int> da(arr, 5);
    
    TEST_ASSERT(da.GetSize() == 5, "DynamicArray::DynamicArray(T*, int)", "DynamicArray.cpp",
                "GetSize() ожидалось 5, получено " + std::to_string(da.GetSize()));
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(da.Get(i) == arr[i], "DynamicArray::DynamicArray(T*, int)", "DynamicArray.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(da.Get(i)));
    }
    
    TEST_PASS("DynamicArray::DynamicArray(T*, int)", "DynamicArray.cpp");
}

void testDynamicArrayConstructorEmpty() {
    DynamicArray<int> da;
    
    TEST_ASSERT(da.GetSize() == 0, "DynamicArray::DynamicArray()", "DynamicArray.cpp",
                "GetSize() ожидалось 0, получено " + std::to_string(da.GetSize()));
    
    TEST_PASS("DynamicArray::DynamicArray()", "DynamicArray.cpp");
}

void testDynamicArrayConstructorSize() {
    DynamicArray<int> da(10);
    
    TEST_ASSERT(da.GetSize() == 10, "DynamicArray::DynamicArray(int)", "DynamicArray.cpp",
                "GetSize() ожидалось 10, получено " + std::to_string(da.GetSize()));
    
    TEST_PASS("DynamicArray::DynamicArray(int)", "DynamicArray.cpp");
}

void testDynamicArrayConstructorNegativeSize() {
    try {
        DynamicArray<int> da(-5);
        TEST_ASSERT(false, "DynamicArray::DynamicArray(int)", "DynamicArray.cpp",
                    "Констурктор для отрицательного размера не вывел NEGATIVE_SIZE");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::NEGATIVE_SIZE, "DynamicArray::DynamicArray(int)", "DynamicArray.cpp",
                    "Конструктор вывел неверное имя ошибки");
    }
    
    TEST_PASS("DynamicArray::DynamicArray(int)", "DynamicArray.cpp");
}

void testDynamicArrayGet() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    DynamicArray<int> da(arr, 10);
    
    for (int i = 0; i < 10; ++i) {
        TEST_ASSERT(da.Get(i) == arr[i], "DynamicArray::Get", "DynamicArray.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(da.Get(i)));
    }
    
    try {
        da.Get(10);
        TEST_ASSERT(false, "DynamicArray::Get", "DynamicArray.cpp",
                    "Get(10) не вывел INDEX_OUT_OF_RANGE при выходе за пределы диапазона");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::INDEX_OUT_OF_RANGE, "DynamicArray::Get", "DynamicArray.cpp",
                    "Get(10) вывел неверное имя ошбики");
    }
    
    try {
        da.Get(-1);
        TEST_ASSERT(false, "DynamicArray::Get", "DynamicArray.cpp",
                    "Get(-1) не вывел INDEX_OUT_OF_RANGE при выходе за пределы диапазона");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::INDEX_OUT_OF_RANGE, "DynamicArray::Get", "DynamicArray.cpp",
                    "Get(-1) вывел неверное имя ошибки");
    }
    
    TEST_PASS("DynamicArray::Get", "DynamicArray.cpp");
}

void testDynamicArraySet() {
    int arr[] = {1, 2, 3, 4, 5};
    DynamicArray<int> da(arr, 5);
    
    da.Set(0, 100);
    da.Set(2, 300);
    da.Set(4, 500);
    
    int expected[] = {100, 2, 300, 4, 500};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(da.Get(i) == expected[i], "DynamicArray::Set", "DynamicArray.cpp",
                    "После Set, для индекса " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(da.Get(i)));
    }
    
    try {
        da.Set(5, 999);
        TEST_ASSERT(false, "DynamicArray::Set", "DynamicArray.cpp",
                    "Set(5,999) не вывел INDEX_OUT_OF_RANGE");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::INDEX_OUT_OF_RANGE, "DynamicArray::Set", "DynamicArray.cpp",
                    "Set(5,999) вывел неверное имя ошибки");
    }
    
    TEST_PASS("DynamicArray::Set", "DynamicArray.cpp");
}

void testDynamicArrayResizeIncrease() {
    int arr[] = {1, 2, 3};
    DynamicArray<int> da(arr, 3);
    
    da.Resize(7);
    
    TEST_ASSERT(da.GetSize() == 7, "DynamicArray::Resize", "DynamicArray.cpp",
                "После Resize(7), GetSize() вывел 7, ожидалось " + std::to_string(da.GetSize()));
    
    int expected[] = {1, 2, 3, 0, 0, 0, 0};
    for (int i = 0; i < 7; ++i) {
        TEST_ASSERT(da.Get(i) == expected[i], "DynamicArray::Resize", "DynamicArray.cpp",
                    "После Resize(7), для индекса " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(da.Get(i)));
    }
    
    TEST_PASS("DynamicArray::Resize", "DynamicArray.cpp");
}

void testDynamicArrayResizeDecrease() {
    int arr[] = {10, 20, 30, 40, 50};
    DynamicArray<int> da(arr, 5);
    
    da.Resize(3);
    
    TEST_ASSERT(da.GetSize() == 3, "DynamicArray::Resize", "DynamicArray.cpp",
                "После Resize(3), GetSize() ожидалось 3, получено " + std::to_string(da.GetSize()));
    
    int expected[] = {10, 20, 30};
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(da.Get(i) == expected[i], "DynamicArray::Resize", "DynamicArray.cpp",
                    "После Resize(3), для индекса " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(da.Get(i)));
    }
    
    TEST_PASS("DynamicArray::Resize", "DynamicArray.cpp");
}

void testDynamicArrayResizeZero() {
    int arr[] = {1, 2, 3};
    DynamicArray<int> da(arr, 3);
    
    da.Resize(0);
    
    TEST_ASSERT(da.GetSize() == 0, "DynamicArray::Resize", "DynamicArray.cpp",
                "После Resize(0), GetSize() ожидалось 0, получено " + std::to_string(da.GetSize()));
    
    TEST_PASS("DynamicArray::Resize", "DynamicArray.cpp");
}

void testDynamicArrayCopyConstructor() {
    int arr[] = {5, 10, 15, 20, 25};
    DynamicArray<int> da1(arr, 5);
    DynamicArray<int> da2(da1);
    
    TEST_ASSERT(da2.GetSize() == 5, "DynamicArray::DynamicArray(const DynamicArray&)", "DynamicArray.cpp",
                "После копирования размера ожидалось 5, получено " + std::to_string(da2.GetSize()));
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(da2.Get(i) == arr[i], "DynamicArray::DynamicArray(const DynamicArray&)", "DynamicArray.cpp",
                    "После копирования по индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(da2.Get(i)));
    }
    
    da1.Set(0, 999);
    da1.Set(4, 888);
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(da2.Get(i) == arr[i], "DynamicArray::DynamicArray(const DynamicArray&)", "DynamicArray.cpp",
                    "После изменения оригинала и копирования по индексу " + std::to_string(i) + " считалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(da2.Get(i)));
    }
    
    TEST_PASS("DynamicArray::DynamicArray(const DynamicArray&)", "DynamicArray.cpp");
}

void testDynamicArrayAssignment() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30, 40, 50, 60, 70};
    DynamicArray<int> da1(arr1, 5);
    DynamicArray<int> da2(arr2, 7);
    
    da2 = da1;
    
    TEST_ASSERT(da2.GetSize() == 5, "DynamicArray::operator=", "DynamicArray.cpp",
                "После присваивания ожидаемый размер 5, полученный " + std::to_string(da2.GetSize()));
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(da2.Get(i) == arr1[i], "DynamicArray::operator=", "DynamicArray.cpp",
                    "После присваивания по индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr1[i]) + 
                    ", получено " + std::to_string(da2.Get(i)));
    }
    
    da1.Set(0, 999);
    da1.Set(4, 888);
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(da2.Get(i) == arr1[i], "DynamicArray::operator=", "DynamicArray.cpp",
                    "После изменения исходника и копирования данных по индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr1[i]) + 
                    ", получено " + std::to_string(da2.Get(i)));
    }
    
    TEST_PASS("DynamicArray::operator=", "DynamicArray.cpp");
}