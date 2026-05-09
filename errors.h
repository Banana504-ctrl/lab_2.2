#ifndef ERRORS_H
#define ERRORS_H

enum class ErrorCode {
    OK = 0,
    INDEX_OUT_OF_RANGE, /*Указанный индекс за пределами созданного массива*/
    EMPTY_CONTAINER, /*Пустой контейнер*/
    NEGATIVE_SIZE, /*На случай, если пользователь введёт отрицательный размер массива*/
    ALLOCATION_FAILED, /*Ошибка выделения памяти*/
    CONCAT_NULL_POINTER, /*Если хотим прицепить нулевой список*/
    INVALID_INPUT, /*неверный ввод данных*/
    OPERATION_NOT_ALLOWED   /*в случае попытки изменить объект в immutable*/
 };

#endif