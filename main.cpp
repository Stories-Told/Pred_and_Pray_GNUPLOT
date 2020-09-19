#include <ctime>
#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <sstream>
#include "wolf.h"
#include "ElkMaster.h"
#include "ElkHerd.h"

using namespace std;

int main()
{
    // Creates the random number generator
    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));

    // Create variable that holds random number
    normal_distribution<double> edist(0, 1.0);
    normal_distribution<double> wdist(0, 1.0);

    // Variables for creating .txt files to hold the data
    fstream foutCommand; // Set up gnuplot
    fstream foutPositions; // Elk data

    string pngfile;
    string fileName;
    string index;

    // Makes the command file for gnuplot to read
    foutCommand.open("command.txt",ios::out);

    foutCommand << "set xlabel \"X\"" << endl;
    foutCommand << "set ylabel \"Y\"" << endl;
    foutCommand << "set xrange [-5:30]" << endl;
    foutCommand << "set yrange [-5:30]" << endl;
    foutCommand << "set terminal png" << endl;
    // End making the command file

    // Variables for elk master, elk herd, and wolves
    double dx, dy; // Random positions for x and y
    ElkMaster eMaster;
    ElkHerd eHerd;
    Wolf predator;

    // Creates the .dat files for gnuplot to plot the coordinates
    // does all the graphing
    for(int i = 0; i < 20; i++)
    {
        index = to_string(i); // converts numbered values to strings

        fileName = "outputE" + index + ".dat";   // creates the name for the file and makes it a .dat
        foutPositions.open(fileName.c_str(), ios::out); // creates all of the .dat files with names going up in value

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

        pngfile = "output" + index + ".png";  // creates png file names for the graphs to be saved to
        foutCommand << "set output \'" << pngfile << "\'" << endl; // line code for gnuplot to save .png file
        foutCommand << "plot \'" << fileName << "\' with circles linecolor rgb \"#9ACD32\" fill solid noborder" << endl; // line code for gnuplot to save .txt file
    }
    // Pauses gnuplot until user hits enter
    foutCommand << "pause -1" << endl;

    //****END WRITING TO COMMAND.TXT*******

    // Close gnuplot file
    foutCommand.close();
///_______________________

    // Runs gnuplot
    system("\"C:\\Program Files\\gnuplot\\bin\\wgnuplot.exe\" command.txt");
    return 0;
}
