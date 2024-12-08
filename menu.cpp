#include <iostream>
#include <chrono>

#include "file_generator.h"
#include "file_reader.h"
#include "file_writer.h"
#include "sequence.h"
#include "dynamic_array.h"
#include "people.h"
#include "comparings.h"
#include "sortings.h"
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
    cout << "5. Run functional tests\n\n";
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

    Sorter<People> sorter;

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

                if (sortingChoice == 1)
                {
                    sorter.BubbleSort(sequence, compareFunction);
                }
                else if (sortingChoice == 2)
                {
                    sorter.ShakerSort(sequence, compareFunction);
                }
                else if (sortingChoice == 3)
                {
                    sorter.HeapSort(sequence, compareFunction);
                }
                else if (sortingChoice == 4)
                {
                    sorter.MergeSort(sequence, compareFunction);
                }
                else if (sortingChoice == 5)
                {
                    sorter.QuickSort(sequence, compareFunction);
                }
                else
                {
                    cout << "Wrong sorting number input, please, try again\n\n";
                    break;
                }

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

                cout << sequence->GetLength() << "\n";


                if (sortingChoice == 1)
                {
                    sorter.BubbleSort(sequence, compareFunc);
                }
                else if (sortingChoice == 2)
                {
                    sorter.ShakerSort(sequence, compareFunc);
                }
                else if (sortingChoice == 3)
                {
                    sorter.HeapSort(sequence, compareFunc);
                }
                else if (sortingChoice == 4)
                {
                    sorter.MergeSort(sequence, compareFunc);
                }
                else if (sortingChoice == 5)
                {
                    sorter.QuickSort(sequence, compareFunc);
                }
                else
                {
                    cout << "Wrong sorting number input, please, try again.\n\n";
                    break;
                }

                end = chrono::high_resolution_clock::now();
                duration = end - start;

                cout << "Sorting completed in " << duration.count() << " seconds.\n\n";

                cout << sequence->GetLength() << "\n";

                WriteSequenceToFile(fileNameOut, sequence);

                break;
            }

            case (4):
            {
                sortingChoice = ChooseSorting();

                string name;

                const int max = 50000;
                const int step = 5000;

                int iteration = 1;

                DynamicArray<double> x(0);  // X - size
                DynamicArray<double> y(0);  // Y - time

                for (int i = step; i <= max; i += step)
                {
                    std::unique_ptr<DynamicArray<People>> peoples = std::make_unique<DynamicArray<People>>(i);

                    for (int j = 0; j < i; j++)
                    {
                        (*peoples)[j] = People();
                    }

                    cout << "Sorting\n";
                    start = chrono::high_resolution_clock::now();

                    if (sortingChoice == 1)
                    {
                        sorter.BubbleSort(peoples.get(), CompareByAccountBalance);
                        name = "Bubble Sort";
                    }
                    else if (sortingChoice == 2)
                    {
                        sorter.ShakerSort(peoples.get(), CompareByAccountBalance);
                        name = "Shaker Sort";
                    }
                    else if (sortingChoice == 3)
                    {
                        sorter.HeapSort(peoples.get(), CompareByAccountBalance);
                        name = "Heap Sort";
                    }
                    else if (sortingChoice == 4)
                    {
                        sorter.MergeSort(peoples.get(), CompareByAccountBalance);
                        name = "Merge Sort";
                    }
                    else if (sortingChoice == 5)
                    {
                        sorter.QuickSort(peoples.get(), CompareByAccountBalance);
                        name = "Quick Sort";
                    }
                    else
                    {
                        cout << "Wrong sorting number input, please, try again.\n\n";
                        break;
                    }

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

                TestSorters();

                cout << "\n\n";
                break;
        }
    }
}
