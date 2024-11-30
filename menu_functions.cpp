#include "menu_functions.h"
#include "file_reader.h"
#include "file_writer.h"
#include "sorting_methods.h"
#include "people.h"
#include "dynamic_array.h"
#include "graph_builder.h"

#include <iostream>
#include <string>


void Functions()
{
    cout << "   Function menu: \n\n";
    cout << " 0. Exit\n";
    cout << " 1. Load functional tests\n";
    cout << " 2. Generate people file\n";
    cout << " 3. Sort array by bubble sort\n";
    cout << " 4. Sort array by shaker sort\n";
    cout << " 5. Sort array by merge sort\n";
    cout << " 6. Sort array by heap sort\n";
    cout << " 7. Sort array by quick sort\n";
    cout << " 8. Sort array by all sorting methods\n";
    cout << "9. Build graph for bubble sort\n";
    cout << "10. Build graph for shaker sort\n";
    cout << "11. Build graph for merge sort\n";
    cout << "12. Build graph for heap sort\n";
    cout << "13. Build graph for quick sort\n";

    cout << "Insert number of function: ";
}

void LoadBubbleSort()
{
    LoadSort(SortSequenceByBubbleSort<People>, "Bubble Sort");
}

void LoadShakerSort()
{
    LoadSort(SortSequenceByShakerSort<People>, "Shaker Sort");
}

void LoadMergeSort()
{
    LoadSort(SortSequenceByMergeSort<People>, "Merge Sort");
}

void LoadHeapSort()
{
    LoadSort(SortSequenceByHeapSort<People>, "Heap Sort");
}

void LoadQuickSort()
{
    LoadSort(SortSequenceByQuickSort<People>, "Quick Sort");
}

void LoadAllMethods()
{
    string fileNameIn;
    string fileNameOut;
    string declineWord = "no";

    DynamicArray<People> array;

    double durationBubbleSort = 0;
    double durationShakerSort = 0;
    double durationQuickSort = 0;
    double durationHeapSort = 0;
    double durationMergeSort = 0;

    cout << "Write file name to sort\n";
    cin >> fileNameIn;

    cout << "Write file name to save the result (type no to don't save the result)\n";
    cin >> fileNameOut;

    std::cout << "Read data from the file " << fileNameIn << std::endl;
    ReadDynamicArrayFromFile(fileNameIn, &array);

    std::cout << "Starting sorting..." << std::endl;
    SortDynamicArrayByAllMethods(&array, &durationQuickSort,
                                 &durationHeapSort, &durationMergeSort,
                                 &durationShakerSort, &durationBubbleSort);

    cout << "Quick Sort spend " << durationQuickSort << " seconds\n";
    cout << "Heap Sort spend " << durationHeapSort << " seconds\n";
    cout << "Merge Sort spend " << durationMergeSort << " seconds\n";
    cout << "Shaker Sort spend " << durationShakerSort << " seconds\n";
    cout << "Bubble Sort spend " << durationBubbleSort << " seconds\n";

    TryWriteToFile(fileNameOut, declineWord, &array);
}

void GraphForBubbleSort()
{
    BuildSortGraph(SortSequenceByBubbleSort<People>, "Bubble Sort");
}

void GraphForShakerSort()
{
    BuildSortGraph(SortSequenceByShakerSort<People>, "Shaker Sort");
}

void GraphForMergeSort()
{
    BuildSortGraph(SortSequenceByMergeSort<People>, "Merge Sort");
}

void GraphForHeapSort()
{
    BuildSortGraph(SortSequenceByHeapSort<People>, "Heap Sort");
}

void GraphForQuickSort()
{
    BuildSortGraph(SortSequenceByQuickSort<People>, "Quick Sort");
}