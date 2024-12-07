#pragma once

#include "sequence.h"

template <typename T>
class ISorter {
public:
    virtual void QuickSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) = 0;
    virtual void HeapSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) = 0;
    virtual void MergeSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) = 0;
    virtual void ShakerSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) = 0;
    virtual void BubbleSort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) = 0;
    virtual ~ISorter() = default;
};



