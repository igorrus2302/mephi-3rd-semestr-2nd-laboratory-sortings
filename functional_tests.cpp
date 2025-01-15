#include "functional_tests.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <cstring>
#include <chrono>
#include "sortings.h"
#include "isorter.h"
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

void TestComparators() {
    ISorter<People>* sorter; // Используем указатель на интерфейс

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

    const char* sortNames[] = {
            "QuickSort", "HeapSort", "MergeSort", "ShakerSort", "BubbleSort"
    };

    for (int c = 0; c < 5; c++) {
        std::cout << "Testing comparator: " << comparatorNames[c] << std::endl;

        for (int s = 0; s < 5; s++) {
            // В зависимости от имени сортировки создаем объект сортировки
            if (std::strcmp(sortNames[s], "QuickSort") == 0) {
                sorter = new QuickSorter<People>();
            } else if (std::strcmp(sortNames[s], "HeapSort") == 0) {
                sorter = new HeapSorter<People>();
            } else if (std::strcmp(sortNames[s], "MergeSort") == 0) {
                sorter = new MergeSorter<People>();
            } else if (std::strcmp(sortNames[s], "ShakerSort") == 0) {
                sorter = new ShakerSorter<People>();
            } else if (std::strcmp(sortNames[s], "BubbleSort") == 0) {
                sorter = new BubbleSorter<People>();
            } else {
                continue; // Неизвестный алгоритм сортировки
            }

            // Создаем тестовые данные
            std::vector<People> testData = CreateTestPeople();
            DynamicArray<People> array(testData.size());
            for (size_t i = 0; i < testData.size(); i++) {
                array.Set(i, testData[i]);
            }

            Sequence<People>* sequence = new DynamicArray<People>(array);

            std::cout << "  Running " << sortNames[s] << "... ";
            sorter->Sort(sequence, comparators[c]);

            if (IsSorted1(sequence, comparators[c])) {
                std::cout << "PASSED\n" << std::endl;
            } else {
                std::cout << "FAILED\n" << std::endl;

                std::cout << "  Sequence after sorting:" << std::endl;
                for (int i = 0; i < sequence->GetLength(); i++) {
                    std::cout << sequence->GetElement(i) << std::endl;
                }
            }

            delete sequence;
            delete sorter; // Удаляем сортировщик
        }
    }
}


int Compare(const int& a, const int& b)
{
    return a - b;
}

bool IsSorted(Sequence<int>* sequence)
{
    for (int i = 1; i < sequence->GetLength(); ++i)
    {
        if (sequence->GetElement(i - 1) > sequence->GetElement(i))
        {
            return false;
        }
    }
    return true;
}

void TestSortingAlgorithms()
{
    std::vector<int> testData = {1, 2, 3, 4, 5};

    std::random_device rd;
    std::default_random_engine rng(rd());

    ISorter<int>* sorter;  // Используем указатель на интерфейс

    const char* sortNames[] = {"QuickSort", "HeapSort", "MergeSort", "ShakerSort", "BubbleSort"};

    // Создание фабрики для создания сортировщиков
    for (int i = 0; i < 5; ++i)
    {
        std::shuffle(testData.begin(), testData.end(), rng);

        DynamicArray<int> array(testData.size());

        for (size_t j = 0; j < testData.size(); ++j)
        {
            array.Set(j, testData[j]);
        }

        Sequence<int>* sequence = new DynamicArray<int>(array);

        // В зависимости от сортировки создаем соответствующий сортировщик
        if (std::strcmp(sortNames[i], "QuickSort") == 0) {
            sorter = new QuickSorter<int>();
        } else if (std::strcmp(sortNames[i], "HeapSort") == 0) {
            sorter = new HeapSorter<int>();
        } else if (std::strcmp(sortNames[i], "MergeSort") == 0) {
            sorter = new MergeSorter<int>();
        } else if (std::strcmp(sortNames[i], "ShakerSort") == 0) {
            sorter = new ShakerSorter<int>();
        } else if (std::strcmp(sortNames[i], "BubbleSort") == 0) {
            sorter = new BubbleSorter<int>();
        } else {
            continue; // Неизвестная сортировка
        }

        std::cout << "Testing " << sortNames[i] << "...  ";

        sorter->Sort(sequence, Compare);  // Используем универсальный интерфейс

        if (IsSorted(sequence))
        {
            std::cout << sortNames[i] << " PASSED.\n";
        }
        else
        {
            std::cout << sortNames[i] << " FAILED.\n";
        }

        delete sequence;
        delete sorter;  // Удаляем сортировщик
    }
}

int CompareInt(const int& a, const int& b)
{
    return (a < b) ? -1 : (a > b);
}

Sequence<int>* GenerateReversedSequence(int size)
{
    auto* sequence = new DynamicArray<int>();

    for (int i = size; i > 0; --i)
    {
        sequence->Append(i);
    }
    return sequence;
}

Sequence<int>* GenerateAlmostSortedSequence(int size, int swaps)
{
    auto* sequence = new DynamicArray<int>();

    for (int i = 0; i < size; ++i)
    {
        sequence->Append(i);
    }

    for (int i = 0; i < swaps; ++i)
    {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        auto temp = sequence->GetElement(idx1);
        sequence->Set(idx1, sequence->GetElement(idx2));
        sequence->Set(idx2, temp);
    }
    return sequence;
}

void TestQuadraticBehavior(ISorter<int>& sorter)
{
    const int size = 10000;

    Sequence<int>* reversedSeq = GenerateReversedSequence(size);

    // Засекаем время на сортировку перевернутой последовательности
    auto start = std::chrono::high_resolution_clock::now();
    sorter.Sort(reversedSeq, CompareInt);  // Используем интерфейс сортировки
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Time on reversed sequence: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    delete reversedSeq;

    Sequence<int>* almostSortedSeq = GenerateAlmostSortedSequence(size, size / 100);

    // Засекаем время на сортировку почти отсортированной последовательности
    start = std::chrono::high_resolution_clock::now();
    sorter.Sort(almostSortedSeq, CompareInt);  // Используем интерфейс сортировки
    end = std::chrono::high_resolution_clock::now();

    std::cout << "Time on almost sorted sequence: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    delete almostSortedSeq;
}


void TestSortingEdgeCases(ISorter<int>& sorter) {
    auto compare = [](const int& a, const int& b) { return (a < b) ? -1 : (a > b); };

    // Тест для 0 элементов
    {
        auto* sequence = new DynamicArray<int>();
        sorter.Sort(sequence, compare);  // Используем универсальный метод Sort
        std::cout << "Test 0 elements: Passed" << std::endl;
        delete sequence;
    }

    // Тест для 1 элемента
    {
        auto* sequence = new DynamicArray<int>();
        sequence->Append(42);
        sorter.Sort(sequence, compare);  // Используем универсальный метод Sort

        if (sequence->GetLength() == 1 && sequence->GetElement(0) == 42)
        {
            std::cout << "Test 1 element: Passed" << std::endl;
        }
        else
        {
            std::cout << "Test 1 element: Failed" << std::endl;
        }
        delete sequence;
    }

    // Тест для 2 элементов
    {
        auto* sequence = new DynamicArray<int>();
        sequence->Append(42);
        sequence->Append(21);
        sorter.Sort(sequence, compare);  // Используем универсальный метод Sort

        if (sequence->GetLength() == 2 && sequence->GetElement(0) == 21 && sequence->GetElement(1) == 42)
        {
            std::cout << "Test 2 elements: Passed" << std::endl;
        }
        else
        {
            std::cout << "Test 2 elements: Failed" << std::endl;
        }
        delete sequence;
    }

    // Тест для 3 элементов
    {
        auto* sequence = new DynamicArray<int>();
        sequence->Append(30);
        sequence->Append(10);
        sequence->Append(20);
        sorter.Sort(sequence, compare);  // Используем универсальный метод Sort

        if (sequence->GetLength() == 3 &&
            sequence->GetElement(0) == 10 &&
            sequence->GetElement(1) == 20 &&
            sequence->GetElement(2) == 30) {
            std::cout << "Test 3 elements: Passed" << std::endl;
        }
        else
        {
            std::cout << "Test 3 elements: Failed" << std::endl;
        }
        delete sequence;
    }

    // Тест для большого числа элементов
    {
        const int size = 1000;
        auto* sequence = new DynamicArray<int>();

        for (int i = size; i > 0; --i)
        {
            sequence->Append(i);
        }

        sorter.Sort(sequence, compare);  // Используем универсальный метод Sort

        bool passed = true;
        for (int i = 0; i < size; ++i)
        {
            if (sequence->GetElement(i) != i + 1)
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            std::cout << "Test many elements: Passed" << std::endl;
        }
        else
        {
            std::cout << "Test many elements: Failed" << std::endl;
        }
        delete sequence;
    }
}
