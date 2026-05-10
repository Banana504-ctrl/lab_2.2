#include "test_utils.h"
#include "../LinkedList.h"

void testLinkedListConstructorEmpty() {
    LinkedList<int> ll;
    
    TEST_ASSERT(ll.GetLength() == 0, "LinkedList::LinkedList()", "LinkedList.cpp",
                "GetLength() ожидалось 0, получено " + std::to_string(ll.GetLength()));
    
    TEST_PASS("LinkedList::LinkedList()", "LinkedList.cpp");
}

void testLinkedListConstructorFromArray() {
    int arr[] = {5, 10, 15, 20, 25, 30};
    LinkedList<int> ll(arr, 6);
    
    TEST_ASSERT(ll.GetLength() == 6, "LinkedList::LinkedList(T*, int)", "LinkedList.cpp",
                "GetLength() ожидалось 6, получено " + std::to_string(ll.GetLength()));
    
    for (int i = 0; i < 6; ++i) {
        TEST_ASSERT(ll.Get(i) == arr[i], "LinkedList::LinkedList(T*, int)", "LinkedList.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(ll.Get(i)));
    }
    
    TEST_PASS("LinkedList::LinkedList(T*, int)", "LinkedList.cpp");
}

void testLinkedListGetFirst() {
    int arr[] = {100, 200, 300};
    LinkedList<int> ll(arr, 3);
    
    TEST_ASSERT(ll.GetFirst() == 100, "LinkedList::GetFirst", "LinkedList.cpp",
                "GetFirst() ожидалось 100, получено " + std::to_string(ll.GetFirst()));
    
    LinkedList<int> llEmpty;
    try {
        llEmpty.GetFirst();
        TEST_ASSERT(false, "LinkedList::GetFirst", "LinkedList.cpp",
                    "GetFirst() не вывел на пустом списке EMPTY_CONTAINER");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::EMPTY_CONTAINER, "LinkedList::GetFirst", "LinkedList.cpp",
                    "GetFirst() выведел неверное имя ошибки");
    }
    
    TEST_PASS("LinkedList::GetFirst", "LinkedList.cpp");
}

void testLinkedListGetLast() {
    int arr[] = {10, 20, 30, 40, 50};
    LinkedList<int> ll(arr, 5);
    
    TEST_ASSERT(ll.GetLast() == 50, "LinkedList::GetLast", "LinkedList.cpp",
                "GetLast() ожидалось 50, получено " + std::to_string(ll.GetLast()));
    
    LinkedList<int> llEmpty;
    try {
        llEmpty.GetLast();
        TEST_ASSERT(false, "LinkedList::GetLast", "LinkedList.cpp",
                    "GetLast() не вывел на пустом списке EMPTY_CONTAINER");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::EMPTY_CONTAINER, "LinkedList::GetLast", "LinkedList.cpp",
                    "GetLast() вывел неверное имя ошибки");
    }
    
    TEST_PASS("LinkedList::GetLast", "LinkedList.cpp");
}

void testLinkedListGet() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    LinkedList<int> ll(arr, 8);
    
    for (int i = 0; i < 8; ++i) {
        TEST_ASSERT(ll.Get(i) == arr[i], "LinkedList::Get", "LinkedList.cpp",
                    "Get(" + std::to_string(i) + ") ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(ll.Get(i)));
    }
    
    try {
        ll.Get(8);
        TEST_ASSERT(false, "LinkedList::Get", "LinkedList.cpp",
                    "Get(8) не вывел INDEX_OUT_OF_RANGE при выходе за пределы диапазона");
    } catch (ErrorCode e) {
        TEST_ASSERT(e == ErrorCode::INDEX_OUT_OF_RANGE, "LinkedList::Get", "LinkedList.cpp",
                    "Get(8) вывел неверное имя ошибки");
    }
    
    TEST_PASS("LinkedList::Get", "LinkedList.cpp");
}

void testLinkedListAppend() {
    LinkedList<int> ll;
    
    ll.Append(10);
    ll.Append(20);
    ll.Append(30);
    ll.Append(40);
    ll.Append(50);
    
    TEST_ASSERT(ll.GetLength() == 5, "LinkedList::Append", "LinkedList.cpp",
                "После 5 Appends GetLength() ожидал 5, получено " + std::to_string(ll.GetLength()));
    
    int expected[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(ll.Get(i) == expected[i], "LinkedList::Append", "LinkedList.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(ll.Get(i)));
    }
    
    TEST_PASS("LinkedList::Append", "LinkedList.cpp");
}

void testLinkedListPrepend() {
    LinkedList<int> ll;
    
    ll.Prepend(30);
    ll.Prepend(20);
    ll.Prepend(10);
    
    TEST_ASSERT(ll.GetLength() == 3, "LinkedList::Prepend", "LinkedList.cpp",
                "После 3 Prepends GetLength() ожидал 3, получено " + std::to_string(ll.GetLength()));
    
    int expected[] = {10, 20, 30};
    for (int i = 0; i < 3; ++i) {
        TEST_ASSERT(ll.Get(i) == expected[i], "LinkedList::Prepend", "LinkedList.cpp",
                    "По индексу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(ll.Get(i)));
    }
    
    TEST_PASS("LinkedList::Prepend", "LinkedList.cpp");
}

void testLinkedListInsertAt() {
    int arr1[] = {1, 2, 4, 5};
    LinkedList<int> ll1(arr1, 4);
    
    ll1.InsertAt(3, 2);
    
    TEST_ASSERT(ll1.GetLength() == 5, "LinkedList::InsertAt", "LinkedList.cpp",
                "После InsertAt в середину, длина ожидалась 5, получено " + std::to_string(ll1.GetLength()));
    
    int expected1[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(ll1.Get(i) == expected1[i], "LinkedList::InsertAt", "LinkedList.cpp",
                    "Вставка в середину: по индексу " + std::to_string(i) + 
                    " ожидалось " + std::to_string(expected1[i]) + 
                    ", получено " + std::to_string(ll1.Get(i)));
    }
    
    LinkedList<int> ll2;
    ll2.Append(2);
    ll2.Append(3);
    ll2.InsertAt(1, 0); 
    
    TEST_ASSERT(ll2.GetLength() == 3, "LinkedList::InsertAt", "LinkedList.cpp",
                "После InsertAt в начало, длина ожидалась 3, получено " + std::to_string(ll2.GetLength()));
    
    TEST_ASSERT(ll2.Get(0) == 1, "LinkedList::InsertAt", "LinkedList.cpp",
                "После InsertAt(1,0), Get(0) ожидалось 1, получено " + std::to_string(ll2.Get(0)));
    TEST_ASSERT(ll2.Get(1) == 2, "LinkedList::InsertAt", "LinkedList.cpp",
                "После InsertAt(1,0), Get(1) ожидалось 2, получено " + std::to_string(ll2.Get(1)));
    TEST_ASSERT(ll2.Get(2) == 3, "LinkedList::InsertAt", "LinkedList.cpp",
                "После InsertAt(1,0), Get(2) ожидалось 3, получено " + std::to_string(ll2.Get(2)));

    LinkedList<int> ll3;
    ll3.Append(1);
    ll3.Append(2);
    ll3.InsertAt(3, 2); 
    
    TEST_ASSERT(ll3.GetLength() == 3, "LinkedList::InsertAt", "LinkedList.cpp",
                "После InsertAt в конец, длина ожидалась 3, получено " + std::to_string(ll3.GetLength()));
    TEST_ASSERT(ll3.Get(2) == 3, "LinkedList::InsertAt", "LinkedList.cpp",
                "После InsertAt(3,2), Get(2) ожидалось 3, получено " + std::to_string(ll3.Get(2)));
    
    LinkedList<int> ll4;
    bool exceptionThrown = false;
    try {
        ll4.InsertAt(1, 1); 
    } catch (ErrorCode e) {
        exceptionThrown = (e == ErrorCode::INDEX_OUT_OF_RANGE);
    }
    TEST_ASSERT(exceptionThrown, "LinkedList::InsertAt", "LinkedList.cpp",
                "InsertAt с индексом > длины должен выбросить INDEX_OUT_OF_RANGE");
    
    TEST_PASS("LinkedList::InsertAt", "LinkedList.cpp");
}

void testLinkedListConcat() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6, 7};
    LinkedList<int> ll1(arr1, 3);
    LinkedList<int> ll2(arr2, 4);
    
    LinkedList<int> result = ll1.Concat(&ll2);
    
    TEST_ASSERT(result.GetLength() == 7, "LinkedList::Concat", "LinkedList.cpp",
                "Ожидаемый результат длины после сложения строк 7, получено " + std::to_string(result.GetLength()));
    
    int expected[] = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < 7; ++i) {
        TEST_ASSERT(result.Get(i) == expected[i], "LinkedList::Concat", "LinkedList.cpp",
                    "По инедксу " + std::to_string(i) + " ожидалось " + std::to_string(expected[i]) + 
                    ", получено " + std::to_string(result.Get(i)));
    }
    
    TEST_ASSERT(ll1.GetLength() == 3, "LinkedList::Concat", "LinkedList.cpp",
                "Исходный первый список должен был измениться, ожидаемая длина 3, получена " + std::to_string(ll1.GetLength()));
    
    TEST_ASSERT(ll2.GetLength() == 4, "LinkedList::Concat", "LinkedList.cpp",
                "Исходный второй список должен был измениться, ожидаемая длина 4, получена " + std::to_string(ll2.GetLength()));
    
    TEST_PASS("LinkedList::Concat", "LinkedList.cpp");
}

void testLinkedListCopyConstructor() {
    int arr[] = {100, 200, 300, 400, 500};
    LinkedList<int> ll1(arr, 5);
    LinkedList<int> ll2(ll1);
    
    TEST_ASSERT(ll2.GetLength() == 5, "LinkedList::LinkedList(const LinkedList&)", "LinkedList.cpp",
                "Ожидаемая длина копии 5, получена " + std::to_string(ll2.GetLength()));
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(ll2.Get(i) == arr[i], "LinkedList::LinkedList(const LinkedList&)", "LinkedList.cpp",
                    "При копировании по индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(ll2.Get(i)));
    }
    
    ll1.Set(0, 999);
    ll1.Set(4, 888);
    
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT(ll2.Get(i) == arr[i], "LinkedList::LinkedList(const LinkedList&)", "LinkedList.cpp",
                    "После изменения оригинала в копии по индексу " + std::to_string(i) + " ожидалось " + std::to_string(arr[i]) + 
                    ", получено " + std::to_string(ll2.Get(i)));
    }
    
    TEST_PASS("LinkedList::LinkedList(const LinkedList&)", "LinkedList.cpp");
}