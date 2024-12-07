#include <iostream>
#include <fstream>

#include "dynamic_array.h"
#include "people.h"

//утечка памяти

void WriteSequenceToFile(std::string& fileName, Sequence<People>* sequence)
{
    std::ofstream file(fileName);
    if (!file)
    {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    auto it = sequence->ToBegin();
    auto end = sequence->ToEnd();

    while (!(*it == *end))
    {
        People& person = **it;
        file << person.GetLastName() << " "
             << person.GetFirstName() << " "
             << person.GetPatronymic() << " "
             << person.GetBirthDate() << " "
             << person.GetAccountBalance() << "\n";
        ++(*it);
    }

    std::cout << "The data have been successfully written to the file " << fileName << std::endl;

    file.close();
}

