#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
inline void SetGreen() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); }
inline void SetRed()   { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); }
inline void SetWhite() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); }
#else
inline void SetGreen() { std::cout << "\033[32m"; }
inline void SetRed()   { std::cout << "\033[31m"; }
inline void SetWhite() { std::cout << "\033[37m"; }
#endif

struct TestResult {
    std::string functionName;
    std::string fileName;
    std::string errorMessage;
    bool passed;
};

extern std::vector<TestResult> testResults;

#define TEST_ASSERT(condition, funcName, fileName, msg) \
    do { \
        if (!(condition)) { \
            testResults.push_back({funcName, fileName, msg, false}); \
            return; \
        } \
    } while(0)

#define TEST_PASS(funcName, fileName) \
    testResults.push_back({funcName, fileName, "", true})

#endif