#include "ui.h"
#include "errors.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "AdaptiveSequence.h"
#include "BitSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>

using namespace std;

int InputInt(const wstring& prompt) {
    int value;
    wcout << prompt;
    wcin >> value;
    return value;
}

int* InputArray(int& size) {
    wcout << L"Введите количество элементов: ";
    wcin >> size;
    if (size <= 0) {
        size = 0;
        return nullptr;
    }
    
    int* arr = new int[size];
    wcout << L"Введите элементы через пробел: ";
    for (int i = 0; i < size; ++i) {
        wcin >> arr[i];
    }
    return arr;
}

template <class T>
void WorkWithSequence(Sequence<T>*& seq, bool isMutable) {
    if (seq == nullptr) return;
    
    int choice = 0;
    
    while (choice != 11) {
        bool isAdaptive = (dynamic_cast<AdaptiveSequence<T>*>(seq) != nullptr);
        
        wcout << L"\nОПЕРАЦИИ\n";
        wcout << L"1. Получить значение (Get)\n";
        wcout << L"2. Задать значение (Set)\n";
        wcout << L"3. Добавить в конец (Append)\n";
        wcout << L"4. Добавить в начало (Prepend)\n";
        wcout << L"5. Вставить на позицию (InsertAt)\n";
        wcout << L"6. Показать содержимое\n";
        wcout << L"7. Применить функцию к каждому (Map)\n";
        wcout << L"8. Отфильтровать (Where)\n";
        wcout << L"9. Свернуть в одно значение (Reduce)\n";
        
        if (isAdaptive) {
            wcout << L"10. Переключить режим (Array <=> List)\n";
            wcout << L"11. Завершить\n";
        } else {
            wcout << L"10. Завершить\n";
        }
        
        wcout << L"Ваш выбор: ";
        wcin >> choice;
        
        try {
            switch (choice) {
                case 1: {
                    int userIndex = InputInt(L"Введите индекс: ");
                    int realIndex = userIndex - 1;
                    wcout << L"Значение: " << seq->Get(realIndex) << endl;
                    break;
                }
                case 2: {
                    int userIndex = InputInt(L"Введите индекс: ");
                    int realIndex = userIndex - 1;
                    T value = InputInt(L"Введите новое значение: ");
                    seq->Set(realIndex, value);
                    wcout << L"Готово\n";
                    break;
                }
                case 3: {
                    T value = InputInt(L"Введите значение: ");
                    if (isMutable) {
                        seq->Append(value);
                        wcout << L"Готово\n";
                    } else {
                        Sequence<T>* newSeq = nullptr;
                        if (auto* arrSeq = dynamic_cast<ImmutableArraySequence<T>*>(seq)) {
                            newSeq = arrSeq->AppendImmutable(value);
                        } else if (auto* listSeq = dynamic_cast<ImmutableListSequence<T>*>(seq)) {
                            newSeq = listSeq->AppendImmutable(value);
                        }
                        if (newSeq) {
                            delete seq;
                            seq = newSeq;
                            wcout << L"Готово\n";
                        }
                    }
                    break;
                }
                case 4: {
                    T value = InputInt(L"Введите значение: ");
                    if (isMutable) {
                        seq->Prepend(value);
                        wcout << L"Готово\n";
                    } else {
                        Sequence<T>* newSeq = nullptr;
                        if (auto* arrSeq = dynamic_cast<ImmutableArraySequence<T>*>(seq)) {
                            newSeq = arrSeq->PrependImmutable(value);
                        } else if (auto* listSeq = dynamic_cast<ImmutableListSequence<T>*>(seq)) {
                            newSeq = listSeq->PrependImmutable(value);
                        }
                        if (newSeq) {
                            delete seq;
                            seq = newSeq;
                            wcout << L"Готово\n";
                        }
                    }
                    break;
                }
                case 5: {
                    int userIndex = InputInt(L"Введите позицию: ");
                    int realIndex = userIndex - 1;
                    T value = InputInt(L"Введите значение: ");
                    if (isMutable) {
                        seq->InsertAt(value, realIndex);
                        wcout << L"Готово\n";
                    } else {
                        Sequence<T>* newSeq = nullptr;
                        if (auto* arrSeq = dynamic_cast<ImmutableArraySequence<T>*>(seq)) {
                            newSeq = arrSeq->InsertAtImmutable(value, realIndex);
                        } else if (auto* listSeq = dynamic_cast<ImmutableListSequence<T>*>(seq)) {
                            newSeq = listSeq->InsertAtImmutable(value, realIndex);
                        }
                        if (newSeq) {
                            delete seq;
                            seq = newSeq;
                            wcout << L"Готово\n";
                        }
                    }
                    break;
                }
                case 6: {
                    wcout << L"Содержимое: [";
                    for (int i = 0; i < seq->GetLength(); ++i) {
                        wcout << seq->Get(i);
                        if (i != seq->GetLength() - 1) wcout << L", ";
                    }
                    wcout << L"]\nРазмер: " << seq->GetLength() << endl;
                    
                    if (isAdaptive) {
                        auto* adapt = dynamic_cast<AdaptiveSequence<T>*>(seq);
                        if (adapt) {
                            wcout << L"Текущий режим: " 
                                  << (adapt->GetCurrentMode() == StorageMode::ARRAY ? L"Массив" : L"Список") << endl;
                        }
                    }
                    break;
                }
                case 7: {
                        wcout << L"Введите множитель: ";
                    int multiplier;
                    wcin >> multiplier;
                    
                    int len = seq->GetLength();
                    int* temp = new int[len];
                    for (int i = 0; i < len; ++i) {
                        temp[i] = seq->Get(i) * multiplier;
                    }
                    
                    Sequence<int>* newSeq = nullptr;
                                    
                    if (dynamic_cast<ArraySequence<int>*>(seq)) {
                        newSeq = new ArraySequence<int>(temp, len);
                    } else if (dynamic_cast<ListSequence<int>*>(seq)) {
                        newSeq = new ListSequence<int>(temp, len);
                    } else if (dynamic_cast<ImmutableArraySequence<int>*>(seq)) {
                        newSeq = new ImmutableArraySequence<int>(temp, len);
                    } else if (dynamic_cast<ImmutableListSequence<int>*>(seq)) {
                        newSeq = new ImmutableListSequence<int>(temp, len);
                    } else if (dynamic_cast<AdaptiveSequence<int>*>(seq)) {
                        AdaptiveSequence<int>* adaptSeq = new AdaptiveSequence<int>();
                        for (int i = 0; i < len; ++i) {
                            adaptSeq->Append(temp[i]);
                        }
                        newSeq = adaptSeq;
                    }
                    
                    delete[] temp;
                    
                    if (newSeq) {
                        delete seq;
                        seq = newSeq;
                        wcout << L"Результат: ";
                        for (int i = 0; i < seq->GetLength(); ++i) {
                            wcout << seq->Get(i) << L" ";
                        }
                        wcout << endl;
                    }
                    break;
                }
                case 8: {
                    wcout << L"Значение фильтра: ";
                                    int threshold;
                    wcin >> threshold;

                    int len = seq->GetLength();
                    int* temp = new int[len];
                    int count = 0;
                    for (int i = 0; i < len; ++i) {
                        int val = seq->Get(i);
                        if (val > threshold) {
                            temp[count] = val;
                            ++count;
                        }
                    }
                    
                    Sequence<int>* newSeq = nullptr;
                    
                    if (dynamic_cast<ArraySequence<int>*>(seq)) {
                        newSeq = new ArraySequence<int>(temp, count);
                    } else if (dynamic_cast<ListSequence<int>*>(seq)) {
                        newSeq = new ListSequence<int>(temp, count);
                    } else if (dynamic_cast<ImmutableArraySequence<int>*>(seq)) {
                        newSeq = new ImmutableArraySequence<int>(temp, count);
                    } else if (dynamic_cast<ImmutableListSequence<int>*>(seq)) {
                        newSeq = new ImmutableListSequence<int>(temp, count);
                    } else if (dynamic_cast<AdaptiveSequence<int>*>(seq)) {
                        AdaptiveSequence<int>* adaptSeq = new AdaptiveSequence<int>();
                        for (int i = 0; i < count; ++i) {
                            adaptSeq->Append(temp[i]);
                        }
                        newSeq = adaptSeq;
                    }
                    
                    delete[] temp;
                    
                    if (newSeq) {
                        delete seq;
                        seq = newSeq;
                        wcout << L"Результат: ";
                        for (int i = 0; i < seq->GetLength(); ++i) {
                            wcout << seq->Get(i) << L" ";
                        }
                        wcout << endl;
                    }
                    break;
                }
                case 9: {
                    wcout << L"Выберите операцию:\n";
                    wcout << L"1. Сумма\n";
                    wcout << L"2. Произведение\n";
                    int op;
                    wcin >> op;
                    if (op == 1) {
                        auto sum = [](T a, T b) { return a + b; };
                        T result = seq->Reduce(sum, 0);
                        wcout << L"Сумма: " << result << endl;
                    } else if (op == 2) {
                        auto prod = [](T a, T b) { return a * b; };
                        T result = seq->Reduce(prod, 1);
                        wcout << L"Произведение: " << result << endl;
                    } else {
                        wcout << L"Неверный выбор\n";
                    }
                    break;
                }
                case 10: {
                    if (isAdaptive) {
                        auto* adapt = dynamic_cast<AdaptiveSequence<T>*>(seq);
                        if (adapt) {
                            adapt->SwitchMode();
                            wcout << L"Режим переключён! Текущий: "
                                  << (adapt->GetCurrentMode() == StorageMode::ARRAY ? L"Массив" : L"Список") << endl;
                        }
                    } else {
                        wcout << L"Завершение работы\n";
                        return;
                    }
                    break;
                }
                default:
                    wcout << L"Неверный выбор\n";
            }
        }
        catch (ErrorCode e) {
            switch (e) {
                case ErrorCode::INDEX_OUT_OF_RANGE:
                    wcout << L"Ошибка: Индекс вне диапазона\n";
                    break;
                case ErrorCode::EMPTY_CONTAINER:
                    wcout << L"Ошибка: Последовательность пуста\n";
                    break;
                case ErrorCode::OPERATION_NOT_ALLOWED:
                    wcout << L"Ошибка: Операция запрещена для Immutable\n";
                    break;
                default:
                    wcout << L"Неизвестная ошибка\n";
            }
        }
        catch (...) {
            wcout << L"Неизвестное исключение\n";
        }
    }
}

void WorkWithBitSequence(BitSequence*& seq) {
    if (seq == nullptr) return;
    
    int choice = 0;
    while (choice != 8) {
        wcout << L"\nОперации с BitSequence\n";
        wcout << L"1. Получить бит (Get)\n";
        wcout << L"2. Установить бит (Set)\n";
        wcout << L"3. Добавить бит в конец (Append)\n";
        wcout << L"4. Добавить бит в начало (Prepend)\n";
        wcout << L"5. Вставить бит на позицию (InsertAt)\n";
        wcout << L"6. Показать всё\n";
        wcout << L"7. Побитовые операции (AND, OR, XOR, NOT)\n";
        wcout << L"8. Завершить\n";
        wcout << L"Ваш выбор: ";
        wcin >> choice;
        
        try {
            switch (choice) {
                case 1: {
                    int userIndex = InputInt(L"Введите индекс (с 1): ");
                    int realIndex = userIndex - 1;
                    wcout << L"Бит: " << (seq->Get(realIndex) ? L"1" : L"0") << endl;
                    break;
                }
                case 2: {
                    int userIndex = InputInt(L"Введите индекс: ");
                    int realIndex = userIndex - 1;
                    int bitVal = InputInt(L"Введите значение (0 или 1): ");
                    seq->Set(realIndex, bitVal != 0);
                    wcout << L"Готово\n";
                    break;
                }
                case 3: {
                    int bitVal = InputInt(L"Введите значение (0 или 1): ");
                    seq->Append(bitVal != 0);
                    wcout << L"Готово\n";
                    break;
                }
                case 4: {
                    int bitVal = InputInt(L"Введите значение (0 или 1): ");
                    seq->Prepend(bitVal != 0);
                    wcout << L"Готово\n";
                    break;
                }
                case 5: {
                    int userIndex = InputInt(L"Введите позицию: ");
                    int realIndex = userIndex - 1;
                    int bitVal = InputInt(L"Введите значение (0 или 1): ");
                    seq->InsertAt(bitVal != 0, realIndex);
                    wcout << L"Готово\n";
                    break;
                }
                case 6: {
                    wcout << L"Содержимое: ";
                    for (int i = 0; i < seq->GetLength(); ++i) {
                        wcout << (seq->Get(i) ? L"1" : L"0");
                    }
                    wcout << L"\nДлина: " << seq->GetLength() << endl;
                    break;
                }
                case 7: {
                    wcout << L"Введите вторую битовую строку: ";
                    wstring bitStr;
                    wcin >> bitStr;
                    
                    char* cstr = new char[bitStr.length() + 1];
                    for (size_t i = 0; i < bitStr.length(); ++i) {
                        cstr[i] = (char)(bitStr[i] == L'0' ? '0' : '1');
                    }
                    cstr[bitStr.length()] = '\0';
                    
                    BitSequence other(cstr);
                    delete[] cstr;
                    
                    wcout << L"Выберите операцию:\n";
                    wcout << L"1. AND\n2. OR\n3. XOR\n4. NOT\n";
                    int op;
                    wcin >> op;
                    
                    BitSequence result;
                    switch (op) {
                        case 1: result = seq->And(other); break;
                        case 2: result = seq->Or(other); break;
                        case 3: result = seq->Xor(other); break;
                        case 4: result = seq->Not(); break;
                        default: wcout << L"Неверный выбор\n"; continue;
                    }
                    
                    wcout << L"Результат: ";
                    for (int i = 0; i < result.GetLength(); ++i) {
                        wcout << (result.Get(i) ? L"1" : L"0");
                    }
                    wcout << endl;
                    break;
                }
                case 8:
                    wcout << L"Завершение работы с BitSequence\n";
                    break;
                default:
                    wcout << L"Неверный выбор\n";
            }
        }
        catch (ErrorCode e) {
            switch (e) {
                case ErrorCode::INDEX_OUT_OF_RANGE:
                    wcout << L"Ошибка: Индекс вне диапазона\n";
                    break;
                case ErrorCode::EMPTY_CONTAINER:
                    wcout << L"Ошибка: Последовательность пуста\n";
                    break;
                case ErrorCode::INVALID_INPUT:
                    wcout << L"Ошибка: Неверный ввод\n";
                    break;
                default:
                    wcout << L"Неизвестная ошибка\n";
            }
        }
        catch (...) {
            wcout << L"Неизвестное исключение\n";
        }
    }
}

void CreateAndWork() {
    wcout << L"\nСОЗДАНИЕ ПОСЛЕДОВАТЕЛЬНОСТИ\n";
    wcout << L"Тип контейнера:\n";
    wcout << L"1. ArraySequence\n";
    wcout << L"2. ListSequence\n";
    wcout << L"3. AdaptiveSequence\n";
    wcout << L"4. BitSequence\n";
    wcout << L"Ваш выбор: ";
    
    int containerType;
    wcin >> containerType;
    
    if (containerType == 4) {
        wcout << L"Введите битовую строку (прим. только 0 и 1): ";
        wstring bitStr;
        wcin >> bitStr;
        
        char* cstr = new char[bitStr.length() + 1];
        for (size_t i = 0; i < bitStr.length(); ++i) {
            cstr[i] = (char)(bitStr[i] == L'0' ? '0' : '1');
        }
        cstr[bitStr.length()] = '\0';
        
        BitSequence* bitSeq = new BitSequence(cstr);
        delete[] cstr;
        
        wcout << L"Начальное содержимое: ";
        for (int i = 0; i < bitSeq->GetLength(); ++i) {
            wcout << (bitSeq->Get(i) ? L"1" : L"0");
        }
        wcout << endl;
        
        WorkWithBitSequence(bitSeq);
        delete bitSeq;
        return;
    }
    
    wcout << L"Вариант:\n";
    wcout << L"1. Mutable\n2. Immutable\n";
    int variantType;
    wcin >> variantType;
    
    bool isMutable = (variantType == 1);
    
    int size;
    int* data = InputArray(size);
    
    Sequence<int>* seq = nullptr;
    
    try {
        if (containerType == 1) {
            if (isMutable) seq = new ArraySequence<int>(data, size);
            else seq = new ImmutableArraySequence<int>(data, size);
        }
        else if (containerType == 2) {
            if (isMutable) seq = new ListSequence<int>(data, size);
            else seq = new ImmutableListSequence<int>(data, size);
        }
        else if (containerType == 3) {
            wcout << L"Начальный режим (1-массив, 2-список): ";
            int mode;
            wcin >> mode;
            auto* adaptSeq = new AdaptiveSequence<int>(data, size);
            if (mode == 2) adaptSeq->SwitchMode();
            seq = adaptSeq;
            wcout << L"Создана AdaptiveSequence. Текущий режим: " 
                  << (adaptSeq->GetCurrentMode() == StorageMode::ARRAY ? L"Массив" : L"Список") << endl;
        }
        
        if (seq) {
            wcout << L"Начальное содержимое: [";
            for (int i = 0; i < seq->GetLength(); ++i) {
                wcout << seq->Get(i);
                if (i != seq->GetLength() - 1) wcout << L", ";
            }
            wcout << L"]\n";
            
            WorkWithSequence(seq, isMutable);
            delete seq;
        }
    }
    catch (ErrorCode e) {
        wcout << L"Ошибка при создании последовательности!\n";
    }
    
    delete[] data;
}

void runProgram() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    
    int choice = 0;
    while (choice != 2) {
        wcout << L"\nГЛАВНОЕ МЕНЮ\n";
        wcout << L"1. Создать последовательность\n";
        wcout << L"2. Выйти\n";
        wcout << L"Ваш выбор: ";
        wcin >> choice;
        
        if (choice == 1) {
            CreateAndWork();
        }
    }
    
    wcout << L"До свидания!\n";
}