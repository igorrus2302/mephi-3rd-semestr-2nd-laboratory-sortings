#include <iostream>
#include <chrono>

#include "file_generator.h"
#include "file_reader.h"
#include "file_writer.h"
#include "sequence.h"
#include "dynamic_array.h"
#include "unique_pointer.h"
#include "people.h"
#include "comparings.h"
#include "isorter.h"
#include "graph_builder.h"
#include "functional_tests.h"

using namespace std;

int Functions()
{
    cout << "Menu:\n\n";
    cout << "0. Exit\n";
    cout << "1. Generate people file\n";
    cout << "2. Sort by one attribute\n";
    cout << "3. Sort by two attributes\n";
    cout << "4. Build graph\n";
    cout << "5. Build all graphs on one page\n";
    cout << "6. Run functional tests\n\n";
    cout << "Insert number of function:";

    int function;

    cin >> function;

    return function;
}

int ChooseSorting()
{
    cout << "List of available sortings:\n\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Shaker Sort\n";
    cout << "3. Heap Sort\n";
    cout << "4. Merge Sort\n";
    cout << "5. Quick Sort\n\n";
    cout << "Insert number of sorting:";

    int sorting;

    cin >> sorting;

    cout << "\n";

    return sorting;
}

int ChooseAttribute()
{
    cout << "List of attributes:\n\n";
    cout << "1. Name\n";
    cout << "2. Last name\n";
    cout << "3. Patronymic\n";
    cout << "4. Birth date\n";
    cout << "5. Account balance\n\n";
    cout << "Insert number of attribute: ";

    int attribute;

    cin >> attribute;

    cout << "\n";

    return attribute;
}

void Menu()
{
    bool isOpen = true;

    int sortingChoice;
    int attributesChoice;

    int firstAttributeChoice;
    int secondAttributeChoice;

    int (*firstCompareFunc)(const People&, const People&) = nullptr;
    int (*secondCompareFunc)(const People&, const People&) = nullptr;
    int (*compareFunc)(const People&, const People&) = nullptr;

    chrono::duration<double> duration;
    chrono::time_point<chrono::high_resolution_clock> start, end;

    string fileNameIn;
    string fileNameOut;

    DynamicArray<People> dynamicArray;

    Sequence<People> *sequence = &dynamicArray;

    while (isOpen)
    {
        int function = Functions();

        switch(function)
        {
            default:
                cout << "Wrong number function input\n\n";
                continue;

            case (0):
                exit(0);

            case (1):
                Generator();
                break;

            case (2):
            {
                cout << "Write file name to sort\n";
                cin >> fileNameIn;

                cout << "Write file name to save the result\n";
                cin >> fileNameOut;

                cout << "Read data from the file " << fileNameIn << std::endl;
                cout << "\n\n";

                ReadDynamicArrayFromFile(fileNameIn, &dynamicArray);

                int (*compareFunction)(const People &, const People &) = nullptr;

                sortingChoice = ChooseSorting();

                attributesChoice = ChooseAttribute();

                if (attributesChoice == 1)
                {
                    compareFunction = CompareByFirstName;
                }
                else if (attributesChoice == 2)
                {
                    compareFunction = CompareByLastName;
                }
                else if (attributesChoice == 3)
                {
                    compareFunction = CompareByPatronymic;
                }
                else if (attributesChoice == 4)
                {
                    compareFunction = CompareByBirthDate;
                }
                else if (attributesChoice == 5)
                {
                    compareFunction = CompareByAccountBalance;
                }
                else
                {
                    cout << "Wrong attribute number input, please, try again\n\n";
                    break;
                }

                start = chrono::high_resolution_clock::now();

                unique_ptr<ISorter<People>> sorter;

                if (sortingChoice == 1)
                {
                    sorter = make_unique<BubbleSorter<People>>();
                }
                else if (sortingChoice == 2)
                {
                    sorter = make_unique<ShakerSorter<People>>();
                }
                else if (sortingChoice == 3)
                {
                    sorter = make_unique<HeapSorter<People>>();
                }
                else if (sortingChoice == 4)
                {
                    sorter = make_unique<MergeSorter<People>>();
                }
                else if (sortingChoice == 5)
                {
                    sorter = make_unique<QuickSorter<People>>();
                }
                else
                {
                    cout << "Wrong sorting number input, please, try again\n\n";
                    break;
                }

                sorter->Sort(sequence, compareFunction);

                end = chrono::high_resolution_clock::now();
                duration = end - start;

                cout << "Sorting completed in " << duration.count() << " seconds.\n\n";

                WriteSequenceToFile(fileNameOut, sequence);

                break;
            }

            case (3):
            {
                cout << "Write file name to sort\n";
                cin >> fileNameIn;

                cout << "Write file name to save the result\n";
                cin >> fileNameOut;

                cout << "Read data from the file " << fileNameIn << std::endl;
                cout << "\n\n";

                ReadDynamicArrayFromFile(fileNameIn, &dynamicArray);

                sortingChoice = ChooseSorting();

                firstAttributeChoice = ChooseAttribute();
                secondAttributeChoice = ChooseAttribute();

                if (firstAttributeChoice == 1 && (secondAttributeChoice == 2 || secondAttributeChoice == 3 || secondAttributeChoice == 4))
                {
                    compareFunc = CompareByTwoAttributesWrapper;
                }
                else if (firstAttributeChoice == 1 && secondAttributeChoice == 5)
                {
                    compareFunc = CompareByStringAndIntWrapper;
                }
                else if (firstAttributeChoice == 2 && (secondAttributeChoice == 1 || secondAttributeChoice == 3 || secondAttributeChoice == 4))
                {
                    compareFunc = CompareByTwoAttributesWrapper;
                }
                else if (firstAttributeChoice == 2 && secondAttributeChoice == 5)
                {
                    compareFunc = CompareByStringAndIntWrapper;
                }
                else if (firstAttributeChoice == 3 && (secondAttributeChoice == 1 || secondAttributeChoice == 2 || secondAttributeChoice == 4))
                {
                    compareFunc = CompareByTwoAttributesWrapper;
                }
                else if (firstAttributeChoice == 3 && secondAttributeChoice == 5)
                {
                    compareFunc = CompareByStringAndIntWrapper;
                }
                else if (firstAttributeChoice == 4 && (secondAttributeChoice == 1 || secondAttributeChoice == 2 || secondAttributeChoice == 3))
                {
                    compareFunc = CompareByTwoAttributesWrapper;
                }
                else if (firstAttributeChoice == 4 && secondAttributeChoice == 5)
                {
                    compareFunc = CompareByStringAndIntWrapper;
                }
                else if (firstAttributeChoice == 5 && (secondAttributeChoice == 1 || secondAttributeChoice == 2 || secondAttributeChoice == 3 || secondAttributeChoice == 4)) {
                    compareFunc = CompareByIntAndStringWrapper;
                }
                else
                {
                    cout << "Invalid attribute combination selected. Please try again.\n\n";
                    break;
                }

                unique_ptr<ISorter<People>> sorter;

                if (sortingChoice == 1)
                {
                    sorter = make_unique<BubbleSorter<People>>();
                }
                else if (sortingChoice == 2)
                {
                    sorter = make_unique<ShakerSorter<People>>();
                }
                else if (sortingChoice == 3)
                {
                    sorter = make_unique<HeapSorter<People>>();
                }
                else if (sortingChoice == 4)
                {
                    sorter = make_unique<MergeSorter<People>>();
                }
                else if (sortingChoice == 5)
                {
                    sorter = make_unique<QuickSorter<People>>();
                }
                else
                {
                    cout << "Wrong sorting number input, please, try again\n\n";
                    break;
                }

                sorter->Sort(sequence, compareFunc);

                end = chrono::high_resolution_clock::now();
                duration = end - start;

                cout << "Sorting completed in " << duration.count() << " seconds.\n\n";

                WriteSequenceToFile(fileNameOut, sequence);

                break;
            }

            case (4):
            {
                sortingChoice = ChooseSorting();

                string name;

                const int max = 100'000;
                const int step = 1000;
                int iteration = 1;

                DynamicArray<double> x(0);  // X - size
                DynamicArray<double> y(0);  // Y - time

                for (int i = step; i <= max; i += step)
                {
                    UniquePointer<DynamicArray<People>> peoples(new DynamicArray<People>(i));

                    for (int j = 0; j < i; j++)
                    {
                        (*peoples)[j] = People();
                    }

                    cout << "Sorting\n";
                    start = chrono::high_resolution_clock::now();

                    unique_ptr<ISorter<People>> sorter;

                    if (sortingChoice == 1)
                    {
                        sorter = make_unique<BubbleSorter<People>>();
                        name = "Bubble Sort";
                    }
                    else if (sortingChoice == 2)
                    {
                        sorter = make_unique<ShakerSorter<People>>();
                        name = "Shaker Sort";
                    }
                    else if (sortingChoice == 3)
                    {
                        sorter = make_unique<HeapSorter<People>>();
                        name = "Heap Sort";
                    }
                    else if (sortingChoice == 4)
                    {
                        sorter = make_unique<MergeSorter<People>>();
                        name = "Merge Sort";
                    }
                    else if (sortingChoice == 5)
                    {
                        sorter = make_unique<QuickSorter<People>>();
                        name = "Quick Sort";
                    }
                    else
                    {
                        cout << "Wrong sorting number input, please, try again.\n\n";
                        break;
                    }

                    sorter->Sort(sequence, CompareByAccountBalance);

                    end = chrono::high_resolution_clock::now();
                    duration = end - start;

                    x.Append(i);
                    y.Append(duration.count());

                    cout << iteration << ") Sorting " << i << " elements took " << duration.count() << " seconds.\n\n";

                    iteration++;
                }

                cout << "Plotting Graph\n\n";
                cout << "Graph has been successfully built!\n\n";

                BuildGraph(x, y, name);

                break;
            }

            case (5):
            {
                const int max = 10000;
                const int step = 1000;
                int iteration = 1;

                DynamicArray<double> x(0);
                DynamicArray<DynamicArray<double>> results(5);

                std::vector<std::pair<int, std::string>> sortingOptions = {
                        {1, "Bubble Sort"},
                        {2, "Shaker Sort"},
                        {3, "Heap Sort"},
                        {4, "Merge Sort"},
                        {5, "Quick Sort"}
                };

                for (int i = step; i <= max; i += step)
                {
                    UniquePointer<DynamicArray<People>> peoples(new DynamicArray<People>(i));

                    for (int j = 0; j < i; j++)
                    {
                        (*peoples)[j] = People();
                    }

                    x.Append(i);

                    for (const auto& [choice, name] : sortingOptions)
                    {
                        cout << "Sorting with " << name << "\n";

                        DynamicArray<People> temp = *peoples;

                        auto start = chrono::high_resolution_clock::now();

                        unique_ptr<ISorter<People>> sorter;

                        if (choice == 1)
                            sorter = make_unique<BubbleSorter<People>>();
                        else if (choice == 2)
                            sorter = make_unique<ShakerSorter<People>>();
                        else if (choice == 3)
                            sorter = make_unique<HeapSorter<People>>();
                        else if (choice == 4)
                            sorter = make_unique<MergeSorter<People>>();
                        else if (choice == 5)
                            sorter = make_unique<QuickSorter<People>>();
                        else
                            continue;

                        sorter->Sort(&temp, CompareByAccountBalance);

                        auto end = chrono::high_resolution_clock::now();
                        chrono::duration<double> duration = end - start;

                        if (results[choice - 1].GetLength() == 0)
                        {
                            results[choice - 1] = DynamicArray<double>(0);
                        }

                        results[choice - 1].Append(duration.count());

                        cout << iteration << ") " << name << ": Sorting " << i << " elements took "
                             << duration.count() << " seconds.\n\n";
                    }

                    iteration++;
                }

                cout << "Plotting Graph\n\n";

                BuildComparisonGraph(x, results);

                cout << "Graph has been successfully built!\n\n";
                break;
            }
            case (6):

                TestComparators();

                TestSortingAlgorithms();
                cout << "\n";

                {
                    QuickSorter<int> quickSorter;
                    TestQuadraticBehavior(quickSorter);
                }
                cout << "\n";

                {
                    std::cout << "Testing QuickSort:" << std::endl;
                    QuickSorter<int> quickSorter;
                    TestSortingEdgeCases(quickSorter);
                    cout << "\n";

                    std::cout << "Testing HeapSort:" << std::endl;
                    HeapSorter<int> heapSorter;
                    TestSortingEdgeCases(heapSorter);
                    cout << "\n";

                    std::cout << "Testing MergeSort:" << std::endl;
                    MergeSorter<int> mergeSorter;
                    TestSortingEdgeCases(mergeSorter);
                    cout << "\n";

                    std::cout << "Testing ShakerSort:" << std::endl;
                    ShakerSorter<int> shakerSorter;
                    TestSortingEdgeCases(shakerSorter);
                    cout << "\n";

                    std::cout << "Testing BubbleSort:" << std::endl;
                    BubbleSorter<int> bubbleSorter;
                    TestSortingEdgeCases(bubbleSorter);
                }

                cout << "\n\n";
                break;
        }
    }
}
