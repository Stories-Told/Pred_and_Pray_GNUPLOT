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

// Creates a menu and allows user to set grid size, herd amount, and wolf amount
void RunMenu()
{
    for(int i = 0; i < 1; i++)
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

// Creates the command.txt file that creates the basic x,y graph
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
    // Calls function from Grid class to set the x and y size of grid
    getGrid.OutputGridToCommand(foutCommand);
    foutCommand << "set terminal png" << endl;
}

// Creates the Elk and Wolves, moves the elk and wolves, and deletes the linked lists for
// the elk and wolves
void GraphPredAndPray(fstream &foutPositions, fstream &foutCommand)
{
    // Class accessor
    // allows for accessing Animals class functions
    Animals animals;

    // String Variables to hold values for writing out to files
    string pngfile;
    string fileName;
    string index;

    // Create the elk master, herd, and wolves
    animals.CreateElkHerd();
    animals.CreateWolves();

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

        // Moves the Elk Master, Elk Herd, and Wolves
        // After moving it, it writes out the new positioning data to
        // the .dat file and then checks to see if any wolves killed a elk
        animals.MoveElkHerd();
        animals.MoveWolves();
        // Takes the newly updated elk and wolf move positions and writes it out to
        // the .dat file(foutPositions)
        animals.WriteOutPositionData(i, foutPositions);
        animals.DoesWolfKillHerd();

        // Close positioning file
        // So that a new one is created next loop
        foutPositions.close();

        //***BEGIN WRITING TO COMMAND.TXT FOR GRAPHING THE DOTS TO GNUPLOT******
        foutCommand << "set output \'" << pngfile << "\'" << endl;
        foutCommand << "plot \'" << fileName
                    << "\' with circles linecolor rgb \"#9ACD32\" fill solid noborder"
                    << endl;
    }

    // Delete the link lists
    animals.DeleteAllLinkList();

    // Pauses gnuplot until user hits enter
    foutCommand << "pause -1" << endl;
    //****END WRITING TO COMMAND.TXT*******

    // Close gnuplot command file
    foutCommand.close();
}

// Calls system to run gnuplot
void RunGnuPlot()
{
    system("\"C:\\Program Files\\gnuplot\\bin\\wgnuplot.exe\" command.txt");
}

// Generates random number based off elk's class variable speed
double ElkMasterRandomGenerator()
{
    // Sets elk master speed
    Animals elkMaster;
    normal_distribution<double> emdist(0, elkMaster.hGetSpeed()); // Elk master speed (5.0)

    return emdist(rGen);
}

// Generates random number based off elk's class variable speed
double ElkHerdRandomGenerator()
{
    // Sets elk herd speed
    Animals elkHerd;
    normal_distribution<double> edist(0, elkHerd.hGetSpeed()); // Elk herd speed (1.5)

    return edist(rGen);
}

// Generates random number based off wolf's class variable speed
double WolfRandomGenerator()
{
    // Sets wolves speed
    Animals wolf;
    normal_distribution<double> wdist(0, wolf.wGetSpeed()); // Wolf speed(5.0)

    return wdist(rGen);
}

// Generates random number for elk health, Based off elk's class variable health
double ElkHerdHealthRandomGenerator()
{
    Animals herd;
    uniform_real_distribution<double> edist(0, herd.hGetHealth());

    return edist(rGen);
}

// Generates random number for elk age, Based off elk's class variable age
double ElkHerdAgeRandomGenerator()
{
    Animals herd;
    uniform_real_distribution<double> edist(0, herd.hGetAge());

    return edist(rGen);
}

// Generates random number for wolves attack strength
double WolfAttackStrengthRandomGenerator()
{
    Animals wolf;
    uniform_real_distribution<double> wdist(0, wolf.wGetAttackStrength());

    return wdist(rGen);
}





