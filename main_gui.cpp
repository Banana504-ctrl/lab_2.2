#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include "ArraySequence.h"
#include "ListSequence.h"
#include "AdaptiveSequence.h"
#include "BitSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"

#define ID_BTN_ARRAY     101
#define ID_BTN_LIST      102
#define ID_BTN_ADAPTIVE  103
#define ID_BTN_BIT       104
#define ID_BTN_MUTABLE   105
#define ID_BTN_IMMUTABLE 106
#define ID_BTN_CREATE    107
#define ID_BTN_DELETE    108
#define ID_BTN_GET       109
#define ID_BTN_SET       110
#define ID_BTN_APPEND    111
#define ID_BTN_PREPEND   112
#define ID_BTN_INSERTAT  113
#define ID_BTN_MAP       114
#define ID_BTN_WHERE     115
#define ID_BTN_REDUCE    116
#define ID_BTN_AND       117
#define ID_BTN_OR        118
#define ID_BTN_XOR       119
#define ID_BTN_NOT       120
#define ID_BTN_EXECUTE   121
#define ID_EDIT_INPUT    122
#define ID_EDIT_INDEX    123
#define ID_EDIT_VALUE    124
#define ID_EDIT_RESULT   125
#define ID_STATIC_CURRENT 126
#define ID_STATIC_STATUS  127
#define ID_EDIT_SECOND   128
#define ID_BTN_SWITCH_MODE 129
#define ID_STATIC_MODE   130

Sequence<int>* currentSeqInt = nullptr;
BitSequence* currentBitSeq = nullptr;
AdaptiveSequence<int>* currentAdaptive = nullptr;
bool isBitMode = false;
bool isMutable = true;
int containerType = 1;
int lastOperation = ID_BTN_GET;

HWND hEditInput, hEditIndex, hEditValue, hEditResult, hStaticCurrent, hStaticStatus, hEditSecond;
HWND hBtnAnd, hBtnOr, hBtnXor, hBtnNot, hBtnSwitchMode, hStaticMode;
HWND hBtnArray, hBtnList, hBtnAdaptive, hBtnBit;
HWND hBtnMutable, hBtnImmutable;
HWND hBtnGet, hBtnSet, hBtnAppend, hBtnPrepend, hBtnInsertAt, hBtnMap, hBtnWhere, hBtnReduce;
HWND hWndMain;

void SetButtonStyle(HWND btn, bool selected) {
    SendMessage(btn, BM_SETCHECK, selected ? BST_CHECKED : BST_UNCHECKED, 0);
}

void UpdateModeDisplay() {
    if (containerType == 3 && currentAdaptive) {
        std::wstring modeText = (currentAdaptive->GetCurrentMode() == StorageMode::ARRAY) ? L"Текущий режим: Массив" : L"Текущий режим: Список";
        SetWindowTextW(hStaticMode, modeText.c_str());
        EnableWindow(hBtnSwitchMode, TRUE);
    } else {
        SetWindowTextW(hStaticMode, L"");
        EnableWindow(hBtnSwitchMode, FALSE);
    }
}

void UpdateCurrentDisplay() {
    std::wstring text = L"[]";
    if (isBitMode && currentBitSeq) {
        std::wstringstream ws;
        ws << L"[";
        for (int i = 0; i < currentBitSeq->GetLength(); ++i) {
            ws << (currentBitSeq->Get(i) ? L"1" : L"0");
            if (i < currentBitSeq->GetLength() - 1) ws << L", ";
        }
        ws << L"]";
        text = ws.str();
    } else if (!isBitMode && currentSeqInt) {
        std::wstringstream ws;
        ws << L"[";
        for (int i = 0; i < currentSeqInt->GetLength(); ++i) {
            ws << currentSeqInt->Get(i);
            if (i < currentSeqInt->GetLength() - 1) ws << L", ";
        }
        ws << L"]";
        text = ws.str();
    }
    SetWindowTextW(hStaticCurrent, text.c_str());
    UpdateModeDisplay();
}

void SetStatus(const std::wstring& msg, bool isError = false) {
    SetWindowTextW(hStaticStatus, msg.c_str());
    if (isError) MessageBeep(MB_ICONERROR);
}

void SetResult(const std::wstring& text) {
    SetWindowTextW(hEditResult, text.c_str());
}

void EnableBitOps(bool enable) {
    EnableWindow(hBtnAnd, enable);
    EnableWindow(hBtnOr, enable);
    EnableWindow(hBtnXor, enable);
    EnableWindow(hBtnNot, enable);
}

void ClearOperationSelections() {
    SetButtonStyle(hBtnGet, false);
    SetButtonStyle(hBtnSet, false);
    SetButtonStyle(hBtnAppend, false);
    SetButtonStyle(hBtnPrepend, false);
    SetButtonStyle(hBtnInsertAt, false);
    SetButtonStyle(hBtnMap, false);
    SetButtonStyle(hBtnWhere, false);
    SetButtonStyle(hBtnReduce, false);
    SetButtonStyle(hBtnAnd, false);
    SetButtonStyle(hBtnOr, false);
    SetButtonStyle(hBtnXor, false);
    SetButtonStyle(hBtnNot, false);
}

void EnableFieldsForOperation(int op) {
    bool idxActive = false, valActive = false, secondActive = false;
    switch (op) {
        case ID_BTN_GET: idxActive = true; break;
        case ID_BTN_SET: idxActive = true; valActive = true; break;
        case ID_BTN_APPEND: valActive = true; break;
        case ID_BTN_PREPEND: valActive = true; break;
        case ID_BTN_INSERTAT: idxActive = true; valActive = true; break;
        case ID_BTN_AND: secondActive = true; break;
        case ID_BTN_OR: secondActive = true; break;
        case ID_BTN_XOR: secondActive = true; break;
        default: break;
    }
    EnableWindow(hEditIndex, idxActive);
    EnableWindow(hEditValue, valActive);
    EnableWindow(hEditSecond, secondActive);
    if (!idxActive) SetWindowTextW(hEditIndex, L"");
    if (!valActive) SetWindowTextW(hEditValue, L"");
    if (!secondActive) SetWindowTextW(hEditSecond, L"");
}

void DeleteCurrentSequence() {
    if (isBitMode && currentBitSeq) {
        delete currentBitSeq;
        currentBitSeq = nullptr;
    } else if (!isBitMode && currentSeqInt) {
        delete currentSeqInt;
        currentSeqInt = nullptr;
    }
    
    // Очищаем все указатели
    currentAdaptive = nullptr;
    currentBitSeq = nullptr;
    currentSeqInt = nullptr;
    isBitMode = false;
    
    // Обновляем UI
    UpdateCurrentDisplay();
    SetResult(L"");
    SetStatus(L"Последовательность удалена");
    
    // Деактивируем элементы управления
    EnableBitOps(false);
    EnableWindow(hEditIndex, FALSE);
    EnableWindow(hEditValue, FALSE);
    EnableWindow(hEditSecond, FALSE);
    EnableWindow(hBtnSwitchMode, FALSE);
    SetWindowTextW(hStaticMode, L"");
    ClearOperationSelections();
}

template <class T>
Sequence<T>* CreateSequenceFromInput(bool immutable, const std::vector<T>& data) {
    if (immutable) {
        if (containerType == 1) return new ImmutableArraySequence<T>(const_cast<T*>(data.data()), (int)data.size());
        if (containerType == 2) return new ImmutableListSequence<T>(const_cast<T*>(data.data()), (int)data.size());
        if (containerType == 3) return new AdaptiveSequence<T>(const_cast<T*>(data.data()), (int)data.size());
    } else {
        if (containerType == 1) return new ArraySequence<T>(const_cast<T*>(data.data()), (int)data.size());
        if (containerType == 2) return new ListSequence<T>(const_cast<T*>(data.data()), (int)data.size());
        if (containerType == 3) return new AdaptiveSequence<T>(const_cast<T*>(data.data()), (int)data.size());
    }
    return nullptr;
}

void CreateSequence() {
    wchar_t buffer[4096];
    GetWindowTextW(hEditInput, buffer, 4096);
    std::wstring input(buffer);
    if (input.empty()) {
        SetStatus(L"Введите последовательность", true);
        return;
    }
    DeleteCurrentSequence();
    try {
        if (containerType == 4) {
            isBitMode = true;
            std::string bitStr;
            for (wchar_t c : input) {
                if (c == L'0') bitStr += '0';
                else if (c == L'1') bitStr += '1';
                else if (c != L' ' && c != L'\n' && c != L'\r') throw std::exception();
            }
            if (bitStr.empty()) throw std::exception();
            currentBitSeq = new BitSequence(bitStr.c_str());
            SetStatus(L"BitSequence создана успешно");
            EnableBitOps(true);
        } else {
            isBitMode = false;
            std::vector<int> data;
            std::wstringstream ws(input);
            int val;
            while (ws >> val) data.push_back(val);
            if (data.empty()) throw std::exception();
            currentSeqInt = CreateSequenceFromInput<int>(!isMutable, data);
            if (!currentSeqInt) throw std::exception();
            if (containerType == 3) {
                currentAdaptive = dynamic_cast<AdaptiveSequence<int>*>(currentSeqInt);
            }
            SetStatus(L"Последовательность создана успешно");
            EnableBitOps(false);
        }
        UpdateCurrentDisplay();
        SetResult(L"");
        ClearOperationSelections();
    } catch (...) {
        SetStatus(L"Ошибка: неверный формат ввода", true);
        isBitMode = false;
        currentSeqInt = nullptr;
        currentBitSeq = nullptr;
        currentAdaptive = nullptr;
        EnableBitOps(false);
        UpdateCurrentDisplay();
    }
}

void SwitchAdaptiveMode() {
    if (currentAdaptive) {
        currentAdaptive->SwitchMode();
        UpdateCurrentDisplay();
        SetStatus(L"Режим переключен");
    }
}

void ExecuteOperation() {
    if (isBitMode && !currentBitSeq) {
        SetStatus(L"Сначала создайте BitSequence", true);
        return;
    }
    if (!isBitMode && !currentSeqInt) {
        SetStatus(L"Сначала создайте последовательность", true);
        return;
    }
    wchar_t bufIdx[256], bufVal[256], bufSecond[4096];
    GetWindowTextW(hEditIndex, bufIdx, 256);
    GetWindowTextW(hEditValue, bufVal, 256);
    GetWindowTextW(hEditSecond, bufSecond, 4096);
    int index = _wtoi(bufIdx);
    int value = _wtoi(bufVal);
    std::wstring resultText;
    try {
        switch (lastOperation) {
            case ID_BTN_GET: {
                if (isBitMode) {
                    bool res = currentBitSeq->Get(index - 1);
                    resultText = res ? L"1" : L"0";
                } else {
                    int res = currentSeqInt->Get(index - 1);
                    resultText = std::to_wstring(res);
                }
                break;
            }
            case ID_BTN_SET: {
                if (isBitMode) currentBitSeq->Set(index - 1, value != 0);
                else currentSeqInt->Set(index - 1, value);
                UpdateCurrentDisplay();
                resultText = L"Значение установлено";
                break;
            }
            case ID_BTN_APPEND: {
                if (isBitMode) currentBitSeq->Append(value != 0);
                else currentSeqInt->Append(value);
                UpdateCurrentDisplay();
                resultText = L"Элемент добавлен в конец";
                break;
            }
            case ID_BTN_PREPEND: {
                if (isBitMode) currentBitSeq->Prepend(value != 0);
                else currentSeqInt->Prepend(value);
                UpdateCurrentDisplay();
                resultText = L"Элемент добавлен в начало";
                break;
            }
            case ID_BTN_INSERTAT: {
                if (isBitMode) currentBitSeq->InsertAt(value != 0, index - 1);
                else currentSeqInt->InsertAt(value, index - 1);
                UpdateCurrentDisplay();
                resultText = L"Элемент вставлен";
                break;
            }
            case ID_BTN_MAP: {
                auto func = [](int x) { return x * 2; };
                Sequence<int>* newSeq = currentSeqInt->Map(func);
                delete currentSeqInt;
                currentSeqInt = newSeq;
                if (containerType == 3) {
                    currentAdaptive = dynamic_cast<AdaptiveSequence<int>*>(currentSeqInt);
                }
                UpdateCurrentDisplay();
                resultText = L"Map (x2) выполнен";
                break;
            }
            case ID_BTN_WHERE: {
                auto pred = [](int x) { return x > 5; };
                Sequence<int>* newSeq = currentSeqInt->Where(pred);
                delete currentSeqInt;
                currentSeqInt = newSeq;
                if (containerType == 3) {
                    currentAdaptive = dynamic_cast<AdaptiveSequence<int>*>(currentSeqInt);
                }
                UpdateCurrentDisplay();
                resultText = L"Where (>5) выполнен";
                break;
            }
            case ID_BTN_REDUCE: {
                auto sum = [](int a, int b) { return a + b; };
                int res = currentSeqInt->Reduce(sum, 0);
                resultText = L"Сумма = " + std::to_wstring(res);
                break;
            }
            case ID_BTN_AND: {
                std::string bitStr;
                for (wchar_t c : std::wstring(bufSecond)) {
                    if (c == L'0') bitStr += '0';
                    else if (c == L'1') bitStr += '1';
                }
                BitSequence other(bitStr.c_str());
                BitSequence res = currentBitSeq->And(other);
                resultText = L"AND: ";
                for (int i = 0; i < res.GetLength(); ++i) resultText += (res.Get(i) ? L"1" : L"0");
                break;
            }
            case ID_BTN_OR: {
                std::string bitStr;
                for (wchar_t c : std::wstring(bufSecond)) {
                    if (c == L'0') bitStr += '0';
                    else if (c == L'1') bitStr += '1';
                }
                BitSequence other(bitStr.c_str());
                BitSequence res = currentBitSeq->Or(other);
                resultText = L"OR: ";
                for (int i = 0; i < res.GetLength(); ++i) resultText += (res.Get(i) ? L"1" : L"0");
                break;
            }
            case ID_BTN_XOR: {
                std::string bitStr;
                for (wchar_t c : std::wstring(bufSecond)) {
                    if (c == L'0') bitStr += '0';
                    else if (c == L'1') bitStr += '1';
                }
                BitSequence other(bitStr.c_str());
                BitSequence res = currentBitSeq->Xor(other);
                resultText = L"XOR: ";
                for (int i = 0; i < res.GetLength(); ++i) resultText += (res.Get(i) ? L"1" : L"0");
                break;
            }
            case ID_BTN_NOT: {
                BitSequence res = currentBitSeq->Not();
                resultText = L"NOT: ";
                for (int i = 0; i < res.GetLength(); ++i) resultText += (res.Get(i) ? L"1" : L"0");
                break;
            }
        }
        SetResult(resultText);
        SetStatus(L"Операция выполнена успешно");
    } catch (ErrorCode e) {
        std::wstring err;
        switch(e) {
            case ErrorCode::INDEX_OUT_OF_RANGE: err = L"Индекс вне диапазона"; break;
            case ErrorCode::EMPTY_CONTAINER: err = L"Контейнер пуст"; break;
            case ErrorCode::OPERATION_NOT_ALLOWED: err = L"Операция запрещена для Immutable"; break;
            default: err = L"Неизвестная ошибка";
        }
        SetStatus(err, true);
    } catch (...) {
        SetStatus(L"Ошибка выполнения операции", true);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            hWndMain = hWnd;
            
            // Инструкция
            CreateWindowW(L"STATIC", L"Тип контейенера->Изменяемость->Создать",
                WS_VISIBLE | WS_CHILD, 20, 15, 500, 25, hWnd, NULL, NULL, NULL);
            
            // Типы контейнеров
            hBtnArray = CreateWindowW(L"BUTTON", L"ArraySeq", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 50, 55, 110, 35, hWnd, (HMENU)ID_BTN_ARRAY, NULL, NULL);
            hBtnList = CreateWindowW(L"BUTTON", L"ListSeq", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 180, 55, 110, 35, hWnd, (HMENU)ID_BTN_LIST, NULL, NULL);
            hBtnAdaptive = CreateWindowW(L"BUTTON", L"Adaptive", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 310, 55, 110, 35, hWnd, (HMENU)ID_BTN_ADAPTIVE, NULL, NULL);
            hBtnBit = CreateWindowW(L"BUTTON", L"BitSeq", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 440, 55, 110, 35, hWnd, (HMENU)ID_BTN_BIT, NULL, NULL);
            SendMessage(hBtnArray, BM_SETCHECK, BST_CHECKED, 0);
            
            // Изменяемость
            hBtnMutable = CreateWindowW(L"BUTTON", L"Mutable", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 180, 105, 110, 35, hWnd, (HMENU)ID_BTN_MUTABLE, NULL, NULL);
            hBtnImmutable = CreateWindowW(L"BUTTON", L"Immutable", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 310, 105, 110, 35, hWnd, (HMENU)ID_BTN_IMMUTABLE, NULL, NULL);
            SendMessage(hBtnMutable, BM_SETCHECK, BST_CHECKED, 0);
            
            // Первая последовательность
            CreateWindowW(L"STATIC", L"Первая:", WS_VISIBLE | WS_CHILD, 30, 160, 50, 25, hWnd, NULL, NULL, NULL);
            hEditInput = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 90, 158, 420, 30, hWnd, (HMENU)ID_EDIT_INPUT, NULL, NULL);
            CreateWindowW(L"BUTTON", L"Создать", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 530, 158, 90, 30, hWnd, (HMENU)ID_BTN_CREATE, NULL, NULL);
            CreateWindowW(L"BUTTON", L"Удалить", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 630, 158, 90, 30, hWnd, (HMENU)ID_BTN_DELETE, NULL, NULL);
            
            // Вторая последовательность
            CreateWindowW(L"STATIC", L"Вторая:", WS_VISIBLE | WS_CHILD, 30, 205, 50, 25, hWnd, NULL, NULL, NULL);
            hEditSecond = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 90, 203, 420, 30, hWnd, (HMENU)ID_EDIT_SECOND, NULL, NULL);
            EnableWindow(hEditSecond, FALSE);
            
            // Текущая последовательность
            CreateWindowW(L"STATIC", L"Текущая:", WS_VISIBLE | WS_CHILD, 30, 255, 60, 25, hWnd, NULL, NULL, NULL);
            hStaticCurrent = CreateWindowW(L"STATIC", L"[]", WS_VISIBLE | WS_CHILD | SS_SUNKEN, 100, 253, 620, 35, hWnd, (HMENU)ID_STATIC_CURRENT, NULL, NULL);
            
            // Кнопка переключения режима для Adaptive
            hBtnSwitchMode = CreateWindowW(L"BUTTON", L"Переключить режим (Массив/Список)", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 305, 250, 35, hWnd, (HMENU)ID_BTN_SWITCH_MODE, NULL, NULL);
            EnableWindow(hBtnSwitchMode, FALSE);
            
            // Отображение текущего режима
            hStaticMode = CreateWindowW(L"STATIC", L"", WS_VISIBLE | WS_CHILD, 470, 312, 200, 25, hWnd, (HMENU)ID_STATIC_MODE, NULL, NULL);
            
            // Операции
            int leftX = 40;
            int rightX = 200;
            int yOps = 360;
            int opW = 130;
            int opH = 38;
            int step = 48;
            
            hBtnGet = CreateWindowW(L"BUTTON", L"Get", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, leftX, yOps, opW, opH, hWnd, (HMENU)ID_BTN_GET, NULL, NULL);
            hBtnSet = CreateWindowW(L"BUTTON", L"Set", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, leftX, yOps + step, opW, opH, hWnd, (HMENU)ID_BTN_SET, NULL, NULL);
            hBtnAppend = CreateWindowW(L"BUTTON", L"Append", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, leftX, yOps + step*2, opW, opH, hWnd, (HMENU)ID_BTN_APPEND, NULL, NULL);
            hBtnPrepend = CreateWindowW(L"BUTTON", L"Prepend", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, leftX, yOps + step*3, opW, opH, hWnd, (HMENU)ID_BTN_PREPEND, NULL, NULL);
            hBtnInsertAt = CreateWindowW(L"BUTTON", L"InsertAt", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, leftX, yOps + step*4, opW, opH, hWnd, (HMENU)ID_BTN_INSERTAT, NULL, NULL);
            
            hBtnMap = CreateWindowW(L"BUTTON", L"Map (x2)", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rightX, yOps, opW, opH, hWnd, (HMENU)ID_BTN_MAP, NULL, NULL);
            hBtnWhere = CreateWindowW(L"BUTTON", L"Where (>5)", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rightX, yOps + step, opW, opH, hWnd, (HMENU)ID_BTN_WHERE, NULL, NULL);
            hBtnReduce = CreateWindowW(L"BUTTON", L"Reduce (sum)", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rightX, yOps + step*2, opW, opH, hWnd, (HMENU)ID_BTN_REDUCE, NULL, NULL);
            hBtnAnd = CreateWindowW(L"BUTTON", L"AND", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rightX, yOps + step*3, opW, opH, hWnd, (HMENU)ID_BTN_AND, NULL, NULL);
            hBtnOr = CreateWindowW(L"BUTTON", L"OR", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rightX, yOps + step*4, opW, opH, hWnd, (HMENU)ID_BTN_OR, NULL, NULL);
            hBtnXor = CreateWindowW(L"BUTTON", L"XOR", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rightX, yOps + step*5, opW, opH, hWnd, (HMENU)ID_BTN_XOR, NULL, NULL);
            hBtnNot = CreateWindowW(L"BUTTON", L"NOT", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, rightX, yOps + step*6, opW, opH, hWnd, (HMENU)ID_BTN_NOT, NULL, NULL);
            
            // Параметры и результат
            int paramX = 420;
            CreateWindowW(L"STATIC", L"Индекс:", WS_VISIBLE | WS_CHILD, paramX, 370, 50, 25, hWnd, NULL, NULL, NULL);
            hEditIndex = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, paramX + 60, 368, 100, 30, hWnd, (HMENU)ID_EDIT_INDEX, NULL, NULL);
            
            CreateWindowW(L"STATIC", L"Значение:", WS_VISIBLE | WS_CHILD, paramX, 420, 60, 25, hWnd, NULL, NULL, NULL);
            hEditValue = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, paramX + 70, 418, 100, 30, hWnd, (HMENU)ID_EDIT_VALUE, NULL, NULL);
            
            CreateWindowW(L"BUTTON", L"Выполнить", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, paramX, 470, 130, 40, hWnd, (HMENU)ID_BTN_EXECUTE, NULL, NULL);
            
            CreateWindowW(L"STATIC", L"Результат:", WS_VISIBLE | WS_CHILD, paramX, 530, 70, 25, hWnd, NULL, NULL, NULL);
            hEditResult = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_MULTILINE, paramX, 560, 300, 100, hWnd, (HMENU)ID_EDIT_RESULT, NULL, NULL);
            EnableWindow(hEditResult, FALSE);
            
            // Статус
            hStaticStatus = CreateWindowW(L"STATIC", L"Готово", WS_VISIBLE | WS_CHILD | SS_SUNKEN, 30, 680, 700, 35, hWnd, (HMENU)ID_STATIC_STATUS, NULL, NULL);
            
            EnableBitOps(false);
            EnableWindow(hEditIndex, FALSE);
            EnableWindow(hEditValue, FALSE);
            break;
        }
              case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case ID_BTN_ARRAY:
                    containerType = 1;
                    SetButtonStyle(hBtnArray, true);
                    SetButtonStyle(hBtnList, false);
                    SetButtonStyle(hBtnAdaptive, false);
                    SetButtonStyle(hBtnBit, false);
                    SetStatus(L"Выбран ArraySeq");
                    UpdateModeDisplay();
                    break;
                case ID_BTN_LIST:
                    containerType = 2;
                    SetButtonStyle(hBtnArray, false);
                    SetButtonStyle(hBtnList, true);
                    SetButtonStyle(hBtnAdaptive, false);
                    SetButtonStyle(hBtnBit, false);
                    SetStatus(L"Выбран ListSeq");
                    UpdateModeDisplay();
                    break;
                case ID_BTN_ADAPTIVE:
                    containerType = 3;
                    SetButtonStyle(hBtnArray, false);
                    SetButtonStyle(hBtnList, false);
                    SetButtonStyle(hBtnAdaptive, true);
                    SetButtonStyle(hBtnBit, false);
                    SetStatus(L"Выбран Adaptive");
                    UpdateModeDisplay();
                    break;
                case ID_BTN_BIT:
                    containerType = 4;
                    SetButtonStyle(hBtnArray, false);
                    SetButtonStyle(hBtnList, false);
                    SetButtonStyle(hBtnAdaptive, false);
                    SetButtonStyle(hBtnBit, true);
                    SetStatus(L"Выбран BitSeq");
                    UpdateModeDisplay();
                    break;
                case ID_BTN_MUTABLE:
                    isMutable = true;
                    SetButtonStyle(hBtnMutable, true);
                    SetButtonStyle(hBtnImmutable, false);
                    SetStatus(L"Выбран Mutable");
                    break;
                case ID_BTN_IMMUTABLE:
                    isMutable = false;
                    SetButtonStyle(hBtnMutable, false);
                    SetButtonStyle(hBtnImmutable, true);
                    SetStatus(L"Выбран Immutable");
                    break;
                case ID_BTN_CREATE:
                    CreateSequence();
                    break;
                case ID_BTN_DELETE:
                    DeleteCurrentSequence();
                    break;
                case ID_BTN_EXECUTE:
                    ExecuteOperation();
                    break;
                case ID_BTN_SWITCH_MODE:
                    SwitchAdaptiveMode();
                    break;
                case ID_BTN_GET: case ID_BTN_SET: case ID_BTN_APPEND: case ID_BTN_PREPEND:
                case ID_BTN_INSERTAT: case ID_BTN_MAP: case ID_BTN_WHERE: case ID_BTN_REDUCE:
                case ID_BTN_AND: case ID_BTN_OR: case ID_BTN_XOR: case ID_BTN_NOT:
                    lastOperation = LOWORD(wParam);
                    ClearOperationSelections();
                    SetButtonStyle(GetDlgItem(hWnd, LOWORD(wParam)), true);
                    EnableFieldsForOperation(lastOperation);
                    SetStatus(L"Выбрана операция, задайте параметры и нажмите Выполнить");
                    break;
            }
            break;
        }
        case WM_DESTROY: {
            DeleteCurrentSequence();
            PostQuitMessage(0);
            break;
        }
        default: return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = L"SequenceGUI";
    RegisterClassW(&wc);
    
    hWndMain = CreateWindowW(L"SequenceGUI", L"lab_2", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 770, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hWndMain, nCmdShow);
    UpdateWindow(hWndMain);
    
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}