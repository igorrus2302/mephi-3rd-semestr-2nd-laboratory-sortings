#pragma once

#include "sequence.h"

template <typename T>
class ISorter {
public:

    virtual void Sort(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) = 0;

    virtual ~ISorter() = default;
};
