#pragma once

#include "isorted.h"
#include "sequence.h"

template <class T>
class Sorter : public ISorted<T> {

private:

    int Separation(int low, int high, Sequence<T>* sequence)
    {
        T pivot = sequence->GetElement(high);
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (sequence->GetElement(j) <= pivot)
            {
                i++;
                sequence->Swap(sequence->GetElement(i), sequence->GetElement(j));
            }
        }

        i += 1;

        sequence->Swap(sequence->GetElement(i), sequence->GetElement(high));

        return i;
    }

    void SiftDown(int n, int i, Sequence<T>* sequence)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && sequence->GetElement(left) > sequence->GetElement(largest))
        {
            largest = left;
        }

        if (right < n && sequence->GetElement(right) > sequence->GetElement(largest))
        {
            largest = right;
        }

        if (largest != i)
        {
            sequence->Swap(sequence->GetElement(i), sequence->GetElement(largest));
            SiftDown(n, largest, sequence);
        }
    }

    void Merge(int low, int middle, int high, Sequence<T>* sequence)
    {
        int size1 = middle - low + 1;
        int size2 = high - middle;

        DynamicArray<T> array1(size1);
        DynamicArray<T> array2(size2);

        for (int i = 0; i < size1; i++)
        {
            array1[i] = sequence->GetElement(low + i);
        }
        for (int i = 0; i < size2; i++)
        {
            array2[i] = sequence->GetElement(middle + 1 + i);
        }

        int i = 0, j = 0, k = low;

        while (i < size1 && j < size2) {
            if (array1.GetElement(i) <= array2.GetElement(j))
            {
                sequence->Set(k, array1.GetElement(i));
                i++;
            }
            else
            {
                sequence->Set(k, array2.GetElement(j));
                j++;
            }

            k++;
        }

        while (i < size1)
        {
            sequence->Set(k, array1.GetElement(i));
            i++;
            k++;
        }

        while (j < size2)
        {
            sequence->Set(k, array2.GetElement(j));
            j++;
            k++;
        }
    }

    void QuickSort(int low, int high, Sequence<T>* sequence)
    {
        if (low < high)
        {
            int pivot = Separation(low, high, sequence);

            QuickSort(low, pivot - 1, sequence);
            QuickSort(pivot + 1, high, sequence);
        }
    }

    void MergeSort(int low, int high, Sequence<T>* sequence)
    {
        if (low < high)
        {
            int middle = low + (high - low) / 2;

            MergeSort(low, middle, sequence);
            MergeSort(middle + 1, high, sequence);

            Merge(low, middle, high, sequence);
        }
    }

    void PerformShakerSort(Sequence<T>* sequence)
    {
        int n = sequence->GetLength();
        bool swapped = true;
        int start = 0;
        int end = n - 1;

        while (swapped)
        {
            swapped = false;

            // Проход слева направо
            for (int i = start; i < end; ++i)
            {
                if (sequence->GetElement(i) > sequence->GetElement(i + 1))
                {
                    sequence->Swap(sequence->GetElement(i), sequence->GetElement(i + 1));
                    swapped = true;
                }
            }

            // Если не было обменов, массив отсортирован
            if (!swapped)
                break;

            // Уменьшаем зону сортировки
            --end;
            swapped = false;

            // Проход справа налево
            for (int i = end - 1; i >= start; --i)
            {
                if (sequence->GetElement(i) > sequence->GetElement(i + 1))
                {
                    sequence->Swap(sequence->GetElement(i), sequence->GetElement(i + 1));
                    swapped = true;
                }
            }

            // Увеличиваем начало зоны сортировки
            ++start;
        }
    }

    void PerformBubbleSort(Sequence<T>* sequence)
    {
        int n = sequence->GetLength();

        for (int i = 0; i < n - 1; ++i)
        {
            bool swapped = false;

            for (int j = 0; j < n - i - 1; ++j)
            {
                if (sequence->GetElement(j) > sequence->GetElement(j + 1))
                {
                    sequence->Swap(sequence->GetElement(j), sequence->GetElement(j + 1));
                    swapped = true;
                }
            }

            if (!swapped) break;
        }
    }

public:

    void QuickSort(Sequence<T>* sequence) override
    {
        QuickSort(0, sequence->GetLength() - 1, sequence);
    }

    void HeapSort(Sequence<T>* sequence) override
    {
        int n = sequence->GetLength();

        for (int i = n / 2 - 1; i >= 0; i--)
        {
            SiftDown(n, i, sequence);
        }

        for (int i = n - 1; i > 0; i--)
        {
            sequence->Swap(sequence->GetElement(0), sequence->GetElement(i));

            SiftDown(i, 0, sequence);
        }
    }

    void MergeSort(Sequence<T>* sequence) override
    {
        MergeSort(0, sequence->GetLength() - 1, sequence);
    }

    void ShakerSort(Sequence<T>* sequence) override
    {
        PerformShakerSort(sequence);
    }

    void BubbleSort(Sequence<T>* sequence) override
    {
        PerformBubbleSort(sequence);
    }
};
