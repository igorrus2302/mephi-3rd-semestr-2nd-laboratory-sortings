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

    int Partition(int lowIndex, int highIndex, Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        T pivotValue = sequence->GetElement(highIndex);
        int partitionIndex = lowIndex - 1;

        for (int currentIndex = lowIndex; currentIndex < highIndex; currentIndex++)
        {
            if (cmp(sequence->GetElement(currentIndex), pivotValue) < 0)
            {
                partitionIndex++;
                sequence->Swap(partitionIndex, currentIndex);
            }
        }

        partitionIndex++;
        sequence->Swap(partitionIndex, highIndex);
        return partitionIndex;
    }

    // HeapSort
    void SiftDown(int heapSize, int parentIndex, Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        int largestIndex = parentIndex;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex = 2 * parentIndex + 2;

        if (leftChildIndex < heapSize && cmp(sequence->GetElement(leftChildIndex), sequence->GetElement(largestIndex)) > 0)
        {
            largestIndex = leftChildIndex;
        }
        if (rightChildIndex < heapSize && cmp(sequence->GetElement(rightChildIndex), sequence->GetElement(largestIndex)) > 0)
        {
            largestIndex = rightChildIndex;
        }
        if (largestIndex != parentIndex)
        {
            sequence->Swap(parentIndex, largestIndex);
            SiftDown(heapSize, largestIndex, sequence, cmp);
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

    void Merge(int startIndex, int midIndex, int endIndex, Sequence<T>* sequence, int (*cmp)(const T&, const T&))
    {
        int leftSize = midIndex - startIndex + 1;
        int rightSize = endIndex - midIndex;

        DynamicArray<T> leftSubsequence(leftSize);
        DynamicArray<T> rightSubsequence(rightSize);

        for (int leftIndex = 0; leftIndex < leftSize; leftIndex++)
            leftSubsequence.Set(leftIndex, sequence->GetElement(startIndex + leftIndex));
        for (int rightIndex = 0; rightIndex < rightSize; rightIndex++)
            rightSubsequence.Set(rightIndex, sequence->GetElement(midIndex + 1 + rightIndex));

        int leftIndex = 0, rightIndex = 0, mergedIndex = startIndex;

        while (leftIndex < leftSize && rightIndex < rightSize)
        {
            if (cmp(leftSubsequence.GetElement(leftIndex), rightSubsequence.GetElement(rightIndex)) <= 0)
            {
                sequence->Set(mergedIndex, leftSubsequence.GetElement(leftIndex));
                leftIndex++;
            }
            else
            {
                sequence->Set(mergedIndex, rightSubsequence.GetElement(rightIndex));
                rightIndex++;
            }
            mergedIndex++;
        }

        while (leftIndex < leftSize)
        {
            sequence->Set(mergedIndex, leftSubsequence.GetElement(leftIndex));
            leftIndex++;
            mergedIndex++;
        }
        while (rightIndex < rightSize)
        {
            sequence->Set(mergedIndex, rightSubsequence.GetElement(rightIndex));
            rightIndex++;
            mergedIndex++;
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
        int sequenceSize = sequence->GetLength();
        for (int passIndex = 0; passIndex < sequenceSize - 1; ++passIndex)
        {
            for (int currentIndex = 0; currentIndex < sequenceSize - passIndex - 1; ++currentIndex)
            {
                if (cmp(sequence->GetElement(currentIndex), sequence->GetElement(currentIndex + 1)) > 0)
                {
                    sequence->Swap(currentIndex, currentIndex + 1);
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
