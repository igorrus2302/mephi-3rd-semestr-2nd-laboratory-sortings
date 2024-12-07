#include "file_generator.h"
#include "people.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void GenerateRandomFile(int count, string& fileName)
{
    ofstream file(fileName);
    if (!file)
    {
        cerr << "Error opening the file!" << endl;
        return;
    }

    for (int i = 0; i < count; ++i)
    {
        People people = People();

        file << people.GetLastName() << " "
             << people.GetFirstName() << " "
             << people.GetPatronymic() << " "
             << people.GetBirthDate() << " "
             << people.GetAccountBalance() << "\n";
    }

    cout << "The data have been successfully written to the file " << fileName <<  "\n\n" << endl;

    file.close();
}

void Generator()
{
    int countNumbers;
    string fileName;

    cout << "Write file name\n";
    cin >> fileName;
    cout << "Write count data in file\n";
    cin >> countNumbers;

    GenerateRandomFile(countNumbers, fileName);
}