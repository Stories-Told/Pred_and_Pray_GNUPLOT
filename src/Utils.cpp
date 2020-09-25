#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <sstream>
#include <windows.h>
#include "Animals.h"
#include "Grid.h"
#include "Utils.h"

using namespace std;


// GLOBAL SEED FOR RANDOM GENERATOR
const unsigned int seed = time(0);
// RANDOM NUMBER GENERATORS
mt19937_64 rGen(seed);

void RunMenu()
{
    for(int i = 0; i < 3; i++)
    {
        // Artists unknown(ascii.co.uk/art/elk)
        cout << "                                          _.--\"\"\"--,"   << endl;
        cout << "                                        .'          `\\" << endl;
        cout << "      .-\"\"\"\"\"\"-.                      .'              |" << endl;
        cout << "     /          '.                   /            .-._/" << endl;
        cout << "    |             `.                |             |"   << endl;
        cout << "     \\             \\          .-._ |          _   \\" << endl;
        cout << "      `""'-.          \\_.-.     \\   `          ( \\__/"  << endl;
        cout << "            |             )     '=.       .,   \\  " << endl;
        cout << "           /             (         \\     /  \\  /"   << endl;
        cout << "         /`               `\\       |    /    `'"    << endl;
        cout << "         '..-`        _.-. `\\ _.__/    .=."  << endl;
        cout << "              |  _    / \\  '.-`    `-.'  /"  << endl;
        cout << "              \\_/ |  |   './ _     _  \\.'"   << endl;
        cout << "                   '-'    | /       \\ |  "   << endl;
        cout << "                          |  .-. .-.  |"     << endl;
        cout << "                          \\ / o| |o \\ /"     << endl;
        cout << "                           |   / \\   |"      << endl;
        cout << "                          / `\"`   `\"` \\"    << endl;
        cout << "                         /             \\"   << endl;
        cout << "                        | '._.'         \\"  << endl;
        cout << "                        |  /             |"  << endl;
        cout << "                         \\ |             |"  << endl;
        cout << "                          ||    _    _   /"  << endl;
        cout << "                         /|\\  (_\\ /_) /"   << endl;
        cout << "                         \\ \\'._  ` '_.'"    << endl;
        cout << "                           `\"\"` `\"\"\"`"      << endl;

        Sleep(500);
        system("cls");
        Sleep(500);
    }

    // Variable to hold users menu choice
    int userSelection;

    cout << "---WELCOME TO THE ELK SIMULATOR!---" << endl;
    cout << "|    --------MAIN MENU-------     |" << endl;
    cout << "|    |                      |     |" << endl;
    cout << "|    | 1.) SET GRID SIZE    |     |" << endl;
    cout << "|    | 2.) SET HERD AMOUNT  |     |" << endl;
    cout << "|    | 3.) SET WOLF AMOUNT  |     |" << endl;
    cout << "|    |                      |     |" << endl;
    cout << "|    | TYPE 'RUN' TO LAUNCH |     |" << endl;
    cout << "|    ------------------------     |" << endl;
    cout << "-----------------------------------" << endl;

    // Stores user choice to be used in switch statement
    cin >> userSelection;

    // Selects the mmenu choice based off user input
    switch(userSelection)
    {
    case 1:
        // 1.) set grid size
        {
            // Call function from Grid class to change
            // grid (x,y) size
            Grid changeGridSize;
            changeGridSize.ChangeGridSize();
        }
        break;
    case 2:
        // 2.) set herd amount
        {
            // Calls function from Animals class to change
            // elk herd amount
            Animals setElkAmount;
            setElkAmount.ChangeElkHerdAmount();
        }
        break;
    case 3:
        // 3.) set wolf amount
        {
            // Calls function from Animals class to change
            // wolf amount
            Animals setWolvesAmount;
            setWolvesAmount.ChangeWolvesAmount();
        }
        break;
    }
}

void CreateCommandFile(fstream &foutCommand)
{
    // Class accessor
    // allows for accessing function from
    // Grid class to write out to command file
    // to set the grid size
    Grid getGrid;

    // Makes the command file for gnuplot to read
    foutCommand.open("command.txt",ios::out);
    foutCommand << "set xlabel \"X\"" << endl;
    foutCommand << "set ylabel \"Y\"" << endl;
    // Sets the x and y amount for the grid
    getGrid.OutputGridToCommand(foutCommand);
    foutCommand << "set terminal png" << endl;
}

void GraphPredAndPray(fstream &foutPositions, fstream &foutCommand)
{
    // Class accessor
    // allows for accessing Animals class functions
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
        // deletes all the link lists at the end
        animals.CreateElkMaster();
        animals.CreateElkHerd();
        animals.CreateWolves();
        animals.WriteOutPositionData(i, foutPositions);
        animals.DoesWolfKillHerd();
        animals.DeleteAllLinkList();

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
