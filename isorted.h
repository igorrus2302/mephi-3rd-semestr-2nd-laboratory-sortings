#pragma once

template <class T>
class ISorted {

public:

    virtual void QuickSort(Sequence<T>* sequence) = 0;
    virtual void HeapSort(Sequence<T>* sequence) = 0;
    virtual void MergeSort(Sequence<T>* sequence) = 0;
    virtual void ShakerSort(Sequence<T>* sequence) = 0;
    virtual void BubbleSort(Sequence<T>* sequence) = 0;

    virtual ~ISorted() {}
};

