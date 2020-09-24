#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <sstream>
#include "Animals.h"
#include "Utils.h"

using namespace std;

// GLOBAL SEED FOR RANDOM GENERATORS
const unsigned int seed = time(0);
// RANDOM NUMBER GENERATORS
mt19937_64 rGen(seed);

void CreateCommandFile(fstream &foutCommand)
{
    // Makes the command file for gnuplot to read
    foutCommand.open("command.txt",ios::out);
    foutCommand << "set xlabel \"X\"" << endl;
    foutCommand << "set ylabel \"Y\"" << endl;
    foutCommand << "set xrange [-5:30]" << endl;
    foutCommand << "set yrange [-5:30]" << endl;
    foutCommand << "set terminal png" << endl;
}

void GraphPredAndPray(fstream &foutPositions, fstream &foutCommand)
{
    // Class accessor
    Animals animals;

    // String Variables to hold values for writing out to files
    string pngfile;
    string fileName;
    string index;

    // Creates the .dat files for gnuplot to plot the coordinates
    // does all the graphing. '< 20' = the amount of .pngs that get made
    for(int i = 0; i < 20; i++)
    {
        index = to_string(i); // converts numbered values to strings each loop
        // creates png file names for the graphs to be saved to each loop
        pngfile = "output" + index + ".png";
        // creates the name for the file and makes it a .dat each loop
        fileName = "outputE" + index + ".dat";

        // creates the .dat files with names going up in value
        foutPositions.open(fileName.c_str(), ios::out);

        // Creates the elk master, elk herd, and wolves data
        // and writes their positions to the foutPositions .dat files
        animals.CreateElkMaster(i, foutPositions);
        animals.CreateElkHerd(i, foutPositions);
        animals.CreateWolves(i, foutPositions);

        // Close positioning file
        // So that a new one is created next loop
        foutPositions.close();

        //***BEGIN WRITING TO COMMAND.TXT FOR GRAPHING THE DOTS TO GNUPLOT******
        foutCommand << "set output \'" << pngfile << "\'" << endl;
        foutCommand << "plot \'" << fileName
                    << "\' with circles linecolor rgb \"#9ACD32\" fill solid noborder"
                    << endl;
    }

    // Pauses gnuplot until user hits enter
    foutCommand << "pause -1" << endl;
    //****END WRITING TO COMMAND.TXT*******

    // Close gnuplot command file
    foutCommand.close();
}

void RunGnuPlot()
{
    system("\"C:\\Program Files\\gnuplot\\bin\\wgnuplot.exe\" command.txt");
}


double ElkMasterRandomGenerator()
{
    Animals elkMaster;
    normal_distribution<double> emdist(0, elkMaster.mGetSpeed()); // Elk master speed (5.0)

    return emdist(rGen);
}

double ElkHerdRandomGenerator()
{
    Animals elkHerd;
    normal_distribution<double> edist(0, elkHerd.hGetSpeed()); // Elk herd speed (1.5)

    return edist(rGen);
}

double WolfRandomGenerator()
{
    Animals wolf;
    normal_distribution<double> wdist(0, wolf.wGetSpeed()); // Wolf speed(5.0)

    return wdist(rGen);
}
