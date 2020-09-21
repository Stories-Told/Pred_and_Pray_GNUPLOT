#include <ctime>
#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <sstream>
#include "Wolf.h"
#include "ElkMaster.h"
#include "ElkHerd.h"
#include "Utils.h"

using namespace std;

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
    // Creates the random number generator
    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));

    // Create variable that holds random number
    normal_distribution<double> edist(0, 1.0);
    normal_distribution<double> wdist(0, 1.0);

    // String Variables to hold values for writing out to files
    string pngfile;
    string fileName;
    string index;

    // Variables for the linked list
    ElkHerd* head = NULL;
    ElkHerd* second = NULL;
    ElkHerd* third = NULL;

    // Variables for elk master, elk herd, and wolves
    double dx, dy; // Random positions for x and y
    ElkMaster eMaster;
    ElkHerd eHerd;
    Wolf predator;

    // Creates the .dat files for gnuplot to plot the coordinates
    // does all the graphing
    for(int i = 0; i < 20; i++)
    {
        index = to_string(i); // converts numbered values to strings each loop

        // creates png file names for the graphs to be saved to each loop
        pngfile = "output" + index + ".png";
        // creates the name for the file and makes it a .dat each loop
        fileName = "outputE" + index + ".dat";

        // creates the .dat files with names going up in value
        foutPositions.open(fileName.c_str(), ios::out);

        // Write the herd masters positions
        dx = edist(*gptr); // sets a random number to dx
        dy = edist(*gptr); // sets a random number to dy

        // Herd masters location
        eMaster.SetpositionX(dx);
        eMaster.SetpositionY(dy);
        // saves the destination data into the files for elk master
        foutPositions <<i + eMaster.GetpositionX() << " " << i + eMaster.GetpositionY() << " " << ".3" << endl; // ".3" size of dot

        // Elk herd for loop
        for (int e = 0; e < 5; e++) // e = elk herd
        {
            dx = edist(*gptr);
            dy = edist(*gptr);

            eHerd.SetpositionX(dx - eMaster.GetpositionX());
            eHerd.SetpositionY(dy - eMaster.GetpositionY());

            foutPositions << i + eHerd.GetpositionX() << " " << i + eHerd.GetpositionY() << " " << ".15" << endl; // ".15" size of dot
        }

        // Wolves for loop
        for (int w  = 0; w < 5; w++) // w = wolf
        {
            dx = wdist(*gptr);
            dy = wdist(*gptr);

            predator.SetpositionX((eHerd.GetpositionX()) + w);
            predator.SetpositionY(dy + 10);
            foutPositions << i + predator.GetpositionX() << " " << i + predator.GetpositionY() << " " << ".1" << endl; // ".1" size of dot
        }

        // Close elk file
        foutPositions.close();

        //***BEGIN WRITING TO COMMAND.TXT FOR GRAPHIC THE DOTS TO GNUPLOT******
        foutCommand << "set output \'" << pngfile << "\'" << endl;
        foutCommand << "plot \'" << fileName << "\' with circles linecolor rgb \"#9ACD32\" fill solid noborder" << endl;
    }

    // Pauses gnuplot until user hits enter
    foutCommand << "pause -1" << endl;
    //****END WRITING TO COMMAND.TXT*******

    // Close gnuplot file
    foutCommand.close();
}

void RunGnuPlot()
{
    system("\"C:\\Program Files\\gnuplot\\bin\\wgnuplot.exe\" command.txt");
}