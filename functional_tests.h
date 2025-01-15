#pragma once

#include <iostream>
#include <vector>
#include "sortings.h"
#include "isorter.h"
#include "people.h"
#include "dynamic_array.h"
#include "sequence.h"

void TestComparators();
void TestSortingAlgorithms();
void TestQuadraticBehavior(ISorter<int>& sorter);
void TestSortingEdgeCases(ISorter<int>& sorter);

template <typename T>
bool IsSorted1(Sequence<T>* sequence, int (*cmp)(const T&, const T&)) {
    for (int i = 1; i < sequence->GetLength(); i++) {
        if (cmp(sequence->GetElement(i - 1), sequence->GetElement(i)) > 0) {
            return false;
        }
    }
    return true;
}




