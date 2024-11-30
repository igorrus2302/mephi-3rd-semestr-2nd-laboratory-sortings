#include <iostream>
#include <fstream>

#include "dynamic_array.h"
#include "people.h"

void WriteSequenceToFile(std::string& fileName, Sequence<People>* sequence)
{
    std::ofstream file(fileName);
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    auto begin = sequence->ToBegin();
    auto end = sequence->ToEnd();

    while (*begin != *end)
    {
        file << (**begin).GetLastName() << " "
             << (**begin).GetFirstName() << " "
             << (**begin).GetPatronymic() << " "
             << (**begin).GetBirthDate() << " "
             << (**begin).GetAccountBalance() << "\n";
        ++(*begin);
    }

    std::cout << "The data have been successfully written to the file " << fileName << std::endl;

    file.close();
}