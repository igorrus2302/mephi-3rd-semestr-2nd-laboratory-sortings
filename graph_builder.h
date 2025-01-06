#pragma once

#include <string>
#include <iostream>

#include "dynamic_array.h"

void BuildGraph(DynamicArray<double>& x, DynamicArray<double>& y, std::string name);
void BuildComparisonGraph(DynamicArray<double>& x, DynamicArray<DynamicArray<double>>& results);
