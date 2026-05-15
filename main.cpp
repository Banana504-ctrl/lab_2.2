#include "ui.h"
#include "DynamicArray.h"
#include <iostream>

int main() {
    //runProgram();


    int data[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr(data, 5);
    std::cout << sizeof(arr) << std::endl;
    std::cout << sizeof(&arr) << std::endl;

    return 0;
}

//написать самим односвязный линейный список