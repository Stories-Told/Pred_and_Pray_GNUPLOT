#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <sstream>
#include "Animals.h"
#include "Utils.h"

using namespace std;

int main()
{
    // Variables for creating .txt files to hold the data
    fstream foutCommand; // Set up gnuplot
    fstream foutPositions; // positioning data

    // Runs function from Utils .cpp to create
    // the command.txt file, which gnuplot
    // will read to create the graphic output
    Utils::CreateCommandFile(foutCommand);

    // Runs function from Utils .cpp to graph the
    // dots for Elk Master, Herd, and Wolves
    // Calls the 3 functions inside Animals class
    // to create the graphing data
    Utils::GraphPredAndPray(foutPositions, foutCommand);

    // Runs gnuplot
    Utils::RunGnuPlot();

    return 0;
}
