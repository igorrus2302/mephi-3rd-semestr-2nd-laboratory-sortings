#pragma once

#include "file_reader.h"
#include "file_generator.h"
#include "sorting_methods.h"
#include "people.h"
#include "dynamic_array.h"
#include "graph_builder.h"

#include <iostream>
#include <string>

using namespace std;

void Functions();

void LoadBubbleSort();
void LoadShakerSort();
void LoadMergeSort();
void LoadHeapSort();
void LoadQuickSort();
void LoadAllMethods();

void GraphForBubbleSort();
void GraphForShakerSort();
void GraphForMergeSort();
void GraphForHeapSort();
void GraphForQuickSort();

template <typename SortFunc>
void LoadSort(SortFunc sortFunction, const std::string& sortName)
{
    std::string fileNameIn;
    std::string fileNameOut;
    const std::string declineWord = "no";
    DynamicArray<People> dynamicArray;
    double duration = 0;

    std::cout << "Write file name to sort\n";
    std::cin >> fileNameIn;

    std::cout << "Write file name to save the result (type no to don't save the result)\n";
    std::cin >> fileNameOut;

    std::cout << "Read data from the file " << fileNameIn << std::endl;
    ReadDynamicArrayFromFile(fileNameIn, &dynamicArray);

    Sequence<People>* sequence = &dynamicArray;

    std::cout << "Starting " << sortName << "..." << std::endl;
    sortFunction(sequence, &duration);

    std::cout << "Sorting spend " << duration << " seconds\n";

    TryWriteToFile(fileNameOut, declineWord, &dynamicArray);
}

template <typename SortFunc>
void BuildSortGraph(SortFunc sortFunction, const std::string& sortName)
{
    std::cout << "Initializing variables\n";

    const int max = 50000;
    const int step = 10000;

    int iteration = 1;

    DynamicArray<double> x(0);
    DynamicArray<double> y(0);

    std::cout << "Calculating points for graph\n";

    for (int i = step; i < max; i += step)
    {
        std::cout << "Create data\n";
        DynamicArray<People> peoples(i);

        std::cout << "Fill data\n";
        for (int j = 0; j < i; j++)
        {
            People people = People();
            peoples[j] = people;
        }

        double duration;

        std::cout << "Sorting\n";
        sortFunction(&peoples, &duration);

        std::cout << "Append point to array\n";
        x.Append(i);
        y.Append(duration);

        std::cout << iteration << ") Sorting " << i << " elements spend " << duration << " seconds\n";

        iteration++;
    }

    std::cout << "Plot Graph\n";

    BuildGraph(x, y, sortName);
}
