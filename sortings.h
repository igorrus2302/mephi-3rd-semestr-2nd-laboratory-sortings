#pragma once

#include "isorter.h"
#include "sequence.h"
#include "dynamic_array.h"

template <typename T>
class Sorter : public ISorter<T> {

private:

    // QuickSort
    void QuickSort(int low, int high, Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        if (low < high)
        {
            int pivot = Partition(low, high, sequence, cmp);
            QuickSort(low, pivot - 1, sequence, cmp);
            QuickSort(pivot + 1, high, sequence, cmp);
        }
    }

    int Partition(int low, int high, Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        T pivot = sequence->GetElement(high);
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (cmp(sequence->GetElement(j), pivot) < 0)
            {
                i++;
                sequence->Swap(i, j);
            }
        }

        i++;
        sequence->Swap(i, high);
        return i;
    }

    // HeapSort
    void SiftDown(int n, int i, Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && cmp(sequence->GetElement(left), sequence->GetElement(largest)) > 0)
        {
            largest = left;
        }
        if (right < n && cmp(sequence->GetElement(right), sequence->GetElement(largest)) > 0)
        {
            largest = right;
        }
        if (largest != i)
        {
            sequence->Swap(i, largest);
            SiftDown(n, largest, sequence, cmp);
        }
    }

    // MergeSort
    void MergeSort(int low, int high, Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        if (low < high)
        {
            int middle = low + (high - low) / 2;
            MergeSort(low, middle, sequence, cmp);
            MergeSort(middle + 1, high, sequence, cmp);
            Merge(low, middle, high, sequence, cmp);
        }
    }

    void Merge(int low, int middle, int high, Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        int size1 = middle - low + 1;
        int size2 = high - middle;

        DynamicArray<T> left(size1);
        DynamicArray<T> right(size2);

        for (int i = 0; i < size1; i++)
            left.Set(i, sequence->GetElement(low + i));
        for (int i = 0; i < size2; i++)
            right.Set(i, sequence->GetElement(middle + 1 + i));

        int i = 0, j = 0, k = low;

        while (i < size1 && j < size2)
        {
            if (cmp(left.GetElement(i), right.GetElement(j)) <= 0)
            {
                sequence->Set(k, left.GetElement(i));
                i++;
            }
            else
            {
                sequence->Set(k, right.GetElement(j));
                j++;
            }
            k++;
        }

        while (i < size1)
        {
            sequence->Set(k, left.GetElement(i));
            i++;
            k++;
        }
        while (j < size2)
        {
            sequence->Set(k, right.GetElement(j));
            j++;
            k++;
        }
    }

    // ShakerSort
    void ShakerSorting(Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        int n = sequence->GetLength();
        bool swapped = true;
        int start = 0, end = n - 1;

        while (swapped)
        {
            swapped = false;

            for (int i = start; i < end; ++i)
            {
                if (cmp(sequence->GetElement(i), sequence->GetElement(i + 1)) > 0)
                {
                    sequence->Swap(i, i + 1);
                    swapped = true;
                }
            }

            if (!swapped) break;

            --end;
            swapped = false;

            for (int i = end - 1; i >= start; --i)
            {
                if (cmp(sequence->GetElement(i), sequence->GetElement(i + 1)) > 0)
                {
                    sequence->Swap(i, i + 1);
                    swapped = true;
                }
            }

            ++start;
        }
    }

    // BubbleSort
    void BubbleSorting(Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        int n = sequence->GetLength();
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = 0; j < n - i - 1; ++j)
            {
                if (cmp(sequence->GetElement(j), sequence->GetElement(j + 1)) > 0)
                {
                    sequence->Swap(j, j + 1);
                }
            }
        }
    }

public:

    void QuickSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) override
    {
        QuickSort(0, sequence->GetLength() - 1, sequence, cmp);
    }

    void HeapSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) override
    {
        int n = sequence->GetLength();

        for (int i = n / 2 - 1; i >= 0; i--)
            SiftDown(n, i, sequence, cmp);
        for (int i = n - 1; i > 0; i--)
        {
            sequence->Swap(0, i);
            SiftDown(i, 0, sequence, cmp);
        }
    }

    void MergeSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) override
    {
        MergeSort(0, sequence->GetLength() - 1, sequence, cmp);
    }

    void ShakerSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) override
    {
        ShakerSorting(sequence, cmp);
    }

    void BubbleSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) override
    {
        BubbleSorting(sequence, cmp);
    }
};
