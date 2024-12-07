#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

#include "dynamic_array.h"
#include "sequence.h"
#include "people.h"

using namespace std;

std::vector<std::string> SplitString(const std::string& str)
{
    istringstream iss(str);
    vector<std::string> tokens;
    string token;

    // Разделение строки по пробелам
    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

Sequence<People>& ReadSequenceFromFile(std::string& fileName, Sequence<People>* sequence)
{
    std::ifstream file(fileName);
    if (!file)
    {
        cout << "Error opening the file!" << std::endl;
        return *sequence;
    }

    string line;

    while (getline(file, line))
    {
        auto tokens = SplitString(line);

        if (tokens.size() < 4 || tokens.size() > 5)
        {
            std::cout << "Error: Invalid format in line: " << line << std::endl;
            continue;
        }

        string lastName;
        string firstName;
        string patronymic;
        string birthDate;
        int accountBalance;

        try {
            if (tokens.size() == 4)
            {
                lastName = tokens[0];
                firstName = "Unknown";
                patronymic = tokens[1];
                birthDate = tokens[2];
                accountBalance = std::stoi(tokens[3]);
            }
            else if (tokens.size() == 5)
            {
                lastName = tokens[0];
                firstName = tokens[1];
                patronymic = tokens[2];
                birthDate = tokens[3];
                accountBalance = std::stoi(tokens[4]);
            }
        } catch (const std::invalid_argument& e) {
            cout << "Error: Invalid data in line: " << line << std::endl;
            continue;
        }

        People person(firstName, lastName, patronymic, birthDate, accountBalance);
        sequence->Append(person);
    }

    file.close();
    return *sequence;
}

void ReadDynamicArrayFromFile(string& fileName, DynamicArray<People>* sequence)
{
    Sequence<People>& tempSequence = ReadSequenceFromFile(fileName, sequence);

    for (int i = 0; i < tempSequence.GetLength(); ++i)
    {
        People person = tempSequence.GetElement(i);
        bool exists = false;

        for (int j = 0; j < sequence->GetLength(); ++j)
        {
            if (sequence->GetElement(j) == person) {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            cout << "Appending new element: " << person << std::endl;
            sequence->Append(person);
        }
    }
}
