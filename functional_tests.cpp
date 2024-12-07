#include "functional_tests.h"
#include <iostream>
#include <vector>
#include "sortings.h"
#include "people.h"
#include "dynamic_array.h"
#include "sequence.h"
#include "comparings.h"


std::vector<People> CreateTestPeople()
{
    return
    {
            People("Ivan", "Ivanov", "Ivanovich", "1990-05-21", 5000),
            People("Petr", "Petrov", "Petrovich", "1985-03-14", 10000),
            People("Anna", "Sidorova", "Vladimirovna", "2000-07-01", 7500),
            People("Olga", "Kuznetsova", "Sergeevna", "1995-01-12", 3000),
            People("Sergey", "Smirnov", "Andreevich", "1988-11-23", 9000)
    };
}

void TestSorters()
{
    Sorter<People> sorter;

    int (*comparators[])(const People&, const People&) = {
            CompareByFirstName,
            CompareByLastName,
            CompareByPatronymic,
            CompareByBirthDate,
            CompareByAccountBalance
    };

    const char* comparatorNames[] = {
            "First Name", "Last Name", "Patronymic", "Birth Date", "Account Balance"
    };

    void (Sorter<People>::*sortFunctions[])(Sequence<People>*, int (*)(const People&, const People&)) = {
            &Sorter<People>::QuickSort,
            &Sorter<People>::HeapSort,
            &Sorter<People>::MergeSort,
            &Sorter<People>::ShakerSort,
            &Sorter<People>::BubbleSort
    };

    const char* sortNames[] = {
            "QuickSort", "HeapSort", "MergeSort", "ShakerSort", "BubbleSort"
    };

    for (int c = 0; c < 5; c++) {
        std::cout << "Testing comparator: " << comparatorNames[c] << std::endl;

        for (int s = 0; s < 5; s++)
        {
            std::vector<People> testData = CreateTestPeople();

            DynamicArray<People> array(testData.size());
            for (size_t i = 0; i < testData.size(); i++)
            {
                array.Set(i, testData[i]);
            }

            Sequence<People>* sequence = new DynamicArray<People>(array);

            std::cout << "  Running " << sortNames[s] << "... ";
            (sorter.*sortFunctions[s])(sequence, comparators[c]);

            if (IsSorted(sequence, comparators[c]))
            {
                std::cout << "PASSED" << std::endl;
            }
            else
            {
                std::cout << "FAILED" << std::endl;

                std::cout << "  Sequence after sorting:" << std::endl;
                for (int i = 0; i < sequence->GetLength(); i++)
                {
                    std::cout << sequence->GetElement(i) << std::endl;
                }
            }

            delete sequence;
        }
    }
}