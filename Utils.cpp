#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <sstream>
#include "Wolf.h"
#include "ElkMaster.h"
#include "ElkHerd.h"
#include "Utils.h"

using namespace std;

// GLOBAL SEED FOR RANDOM GENERATOR
const unsigned int seed = time(0);
// RANDOM NUMBER GENERATOR
mt19937_64 emGPTR(seed);
// RANDOM NUMBER DISTRIBUTORS FOR THE ELK MASTER
normal_distribution<double> emdist(0, 5.0); // Elk master speed (5.0)

void CreateCommandFile(std::fstream &foutCommand)
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
    // Classes
    ElkMaster eMaster;
    ElkHerd eHerd;
    Wolf wPredator;

    // String Variables to hold values for writing out to files
    string pngfile;
    string fileName;
    string index;

    // Variables for elk master, elk herd, and wolves
    double dx = 0.0, dy =  0.0; // Random positions for x and y

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

        // Creates the Master, Herd, and Wolves
        // Write the herd masters positions
        dx = emdist(emGPTR); // sets a random number to dx
        dy = emdist(emGPTR); // sets a random number to dy

        // Herd masters location
        eMaster.SetpositionX(dx);
        eMaster.SetpositionY(dy);
        // saves the destination data into the files for elk master
        foutPositions << i + eMaster.GetpositionX() << " "
                      << i + eMaster.GetpositionY() << " "
                      << ".3" << endl; // ".3" size of dot


        eHerd.CreateElkHerd(dx, dy, i, foutPositions, eMaster);
        wPredator.CreateWolves(dx, dy, i, foutPositions, eMaster);

        // Close positioning file
        foutPositions.close();

        //***BEGIN WRITING TO COMMAND.TXT FOR GRAPHIC THE DOTS TO GNUPLOT******
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

