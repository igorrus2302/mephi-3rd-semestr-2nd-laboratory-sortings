#include <cstdio>
#include <iostream>
#include <string>

#include "dynamic_array.h"


void BuildGraph(DynamicArray<double>& x, DynamicArray<double>& y, std::string name)
{
    FILE* gnuplotPipe = _popen("gnuplot -persistent", "w");

    if (!gnuplotPipe)
    {
        std::cerr << "Failed to launch Gnuplot." << std::endl;
        return;
    }

    std::string title = "set title '" + name + "'\n";

    fprintf(gnuplotPipe, "%s", title.c_str());
    fprintf(gnuplotPipe, "set xlabel 'capacity'\n");
    fprintf(gnuplotPipe, "set ylabel 'time'\n");

    fprintf(gnuplotPipe, "set grid\n");

    fprintf(gnuplotPipe, "plot '-' with lines lc rgb 'black' title 'Data', '-' with points pt 3 ps 1.5 lc rgb 'red' title 'Points'\n");

    for (size_t i = 0; i < x.GetLength(); i++)
    {
        fprintf(gnuplotPipe, "%f %f\n", x[i], y[i]);
    }

    fprintf(gnuplotPipe, "e\n");

    size_t step = x.GetLength() / 10;
    for (size_t i = 0; i < 10 && i * step < x.GetLength(); i++)  
    {
        fprintf(gnuplotPipe, "%f %f\n", x[i * step], y[i * step]);
    }

    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    _pclose(gnuplotPipe);
}
