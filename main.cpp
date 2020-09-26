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

    // Runs function from Utils .cpp to
    // Display the menu of the application
    // allows user to set grid size,
    // set elk herd amount, and set amount of wolves
    Utils::RunMenu();

    // Runs function from Utils .cpp to create
    // the command.txt file, which gnuplot
    // will read to create the graphic output
    Utils::CreateCommandFile(foutCommand);

    // Runs function from Utils .cpp to graph the
    // dots for Elk Master, Herd, and Wolves
    // runs functions from Animals class to move the herd
    // and wolves. Deletes the linked lists after finishing
    Utils::GraphPredAndPray(foutPositions, foutCommand);

    // Runs gnuplot
    Utils::RunGnuPlot();

    return 0;
}
