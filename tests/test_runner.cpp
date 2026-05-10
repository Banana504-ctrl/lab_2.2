#include "test_runner.h"
#include "test_utils.h"
#include <iostream>
#include <vector>

std::vector<TestResult> testResults;

#include "test_dynamicarray.cpp"
#include "test_linkedlist.cpp"
#include "test_arraysequence.cpp"
#include "test_listsequence.cpp"
#include "test_sequence.cpp"
#include "test_adaptivesequence.cpp"
#include "test_bitsequence.cpp"
#include "test_mutable_immutable.cpp"
#ifdef _WIN32
#include <windows.h>
#endif


int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    testDynamicArrayConstructorFromArray();
    testDynamicArrayConstructorEmpty();
    testDynamicArrayConstructorSize();
    testDynamicArrayConstructorNegativeSize();
    testDynamicArrayGet();
    testDynamicArraySet();
    testDynamicArrayResizeIncrease();
    testDynamicArrayResizeDecrease();
    testDynamicArrayResizeZero();
    testDynamicArrayCopyConstructor();
    testDynamicArrayAssignment();
    testLinkedListConstructorEmpty();
    testLinkedListConstructorFromArray();
    testLinkedListGetFirst();
    testLinkedListGetLast();
    testLinkedListGet();
    testLinkedListAppend();
    testLinkedListPrepend();
    testLinkedListInsertAt();
    testLinkedListConcat();
    testLinkedListCopyConstructor();
    testArraySequenceConstructorEmpty();
    testArraySequenceConstructorFromArray();
    testArraySequenceGetFirst();
    testArraySequenceGetLast();
    testArraySequenceGet();
    testArraySequenceSet();
    testArraySequenceAppend();
    testArraySequencePrepend();
    testArraySequenceInsertAt();
    testArraySequenceMap();
    testArraySequenceWhere();
    testArraySequenceReduce();
    testMutableListSequenceAppend();
    testMutableListSequencePrepend();
    testMutableListSequenceInsertAt();
    testMutableListSequenceSet();
    testMutableListSequenceMap();
    testMutableListSequenceWhere();
    testMutableListSequenceReduce();
    testSequencePolymorphismWithArraySequence();
    testSequencePolymorphismWithListSequence();
    testSequencePolymorphismWithImmutableArraySequence();
    testSequencePolymorphismWithImmutableListSequence();
    testSequencePolymorphismWithAdaptiveSequence();
    testSequenceMapViaBasePointer();
    testSequenceWhereViaBasePointer();
    testSequenceReduceViaBasePointer();
    testAdaptiveSequenceConstructorEmpty();
    testAdaptiveSequenceConstructorFromArray();
    testAdaptiveSequenceSwitchModeEvenOdd();
    testAdaptiveSequenceAppend();
    testAdaptiveSequenceAppendAfterSwitch();
    testAdaptiveSequencePrepend();
    testAdaptiveSequencePrependAfterSwitch();
    testAdaptiveSequenceInsertAt();
    testAdaptiveSequenceInsertAtAfterSwitch();
    testAdaptiveSequenceGetFirst();
    testAdaptiveSequenceGetLast();
    testAdaptiveSequenceSet();
    testAdaptiveSequenceMap();
    testAdaptiveSequenceMapAfterSwitch();
    testAdaptiveSequenceWhere();
    testAdaptiveSequenceReduce();
    testAdaptiveSequenceCopyConstructor();
    testAdaptiveSequenceAssignment();
    testBitSequenceConstructorFromString();
    testBitSequenceConstructorEmpty();
    testBitSequenceGet();
    testBitSequenceSet();
    testBitSequenceAppend();
    testBitSequencePrepend();
    testBitSequenceAnd();
    testBitSequenceOr();
    testBitSequenceXor();
    testBitSequenceNot();
    testImmutableListSequenceDoesNotModifyOriginal();
    testImmutableListSequenceAppendImmutable();
    testImmutableListSequencePrependImmutable();
    testImmutableListSequenceInsertAtImmutable();
    testImmutableListSequenceMutableMethodsThrow();
    testImmutableListSequenceMap();
    testImmutableListSequenceWhere();
    testImmutableListSequenceReduce();
    testImmutableArraySequenceDoesNotModifyOriginal();
    testImmutableArraySequenceAppendImmutable();
    testImmutableArraySequencePrependImmutable();
    testImmutableArraySequenceInsertAtImmutable();
    testImmutableArraySequenceMutableMethodsThrow();

    int passed = 0;
    int failed = 0;
    
    for (const auto& res : testResults) {
        if (res.passed) {
            SetGreen();
            std::cout << "[ПРОЙДЕНО] ";
            SetWhite();
            std::cout << res.functionName << " (" << res.fileName << ")\n";
            passed++;
        } else {
            SetRed();
            std::cout << "[ПРОВАЛЕНО] ";
            SetWhite();
            std::cout << res.functionName << " (" << res.fileName << ")\n";
            failed++;
        }
    }
    
    std::cout << "ИТОГ: " << passed << " пройдено, " << failed << " провалено\n";

    if (failed > 0) {
        std::cout << "\nПОДРОБНОСТИ:\n";
        for (const auto& res : testResults) {
            if (!res.passed) {
                std::cout << "\nФункция: " << res.functionName << "\n";
                std::cout << "Файл: " << res.fileName << "\n";
                std::cout << "Ошибка: " << res.errorMessage << "\n";
            }
        }
    }
    
    return (failed > 0) ? 1 : 0;
}