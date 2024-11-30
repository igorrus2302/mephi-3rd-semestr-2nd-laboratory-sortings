#include <iostream>

#include "file_generator.h"
#include "menu_functions.h"

using namespace std;


void Menu()
{
    Functions();

    bool isOpen = true;

    int function;

    while (isOpen)
    {
        cin >> function;

        if ((function < 0) || (function > 13))
        {
            cout << "Wrong number input, please, try again.\n";
            Functions();
        }
        else
        {
            switch (function)
            {
                case (0):
                    exit(0);

                case (1):
                    //LoadFunctionalTests();
                    Functions();
                    break;

                case (2):
                    Generator();
                    Functions();
                    break;

                case (3):
                    LoadBubbleSort();
                    Functions();
                    break;

                case (4):
                    LoadShakerSort();
                    Functions();
                    break;

                case (5):
                    LoadMergeSort();
                    Functions();
                    break;

                case (6):
                    LoadHeapSort();
                    Functions();
                    break;

                case (7):
                    LoadQuickSort();
                    Functions();
                    break;

                case(8):
                    LoadAllMethods();
                    Functions();
                    break;

                case (9):
                    GraphForBubbleSort();
                    Functions();
                    break;

                case (10):
                    GraphForShakerSort();
                    Functions();
                    break;

                case (11):
                    GraphForMergeSort();
                    Functions();
                    break;

                case (12):
                    GraphForHeapSort();
                    Functions();
                    break;

                case (13):
                    GraphForQuickSort();
                    Functions();
                    break;
            }
        }
    }
}
