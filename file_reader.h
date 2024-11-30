#pragma once

#include "dynamic_array.h"
#include "people.h"

void ReadDynamicArrayFromFile(std::string& fileName, DynamicArray<People>* numbers);
Sequence<People>& ReadSequenceFromFile(std::string& fileName, Sequence<People>* numbers);
