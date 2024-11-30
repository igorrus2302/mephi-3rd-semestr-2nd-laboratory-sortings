#pragma once

#include <string>
#include <iostream>

#include "dynamic_array.h"

void BuildGraph(DynamicArray<double>& x, DynamicArray<double>& y, std::string name);

template<typename T>
void TryWriteToFile(std::string fileNameOut, std::string declineWord, DynamicArray<T>* array)
{
    if (fileNameOut != declineWord)
    {
        std::cout << "Writing data to the file " << fileNameOut << std::endl;
        WriteSequenceToFile(fileNameOut, array);
    }
}
