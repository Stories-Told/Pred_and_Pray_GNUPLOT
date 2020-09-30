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

    // while loop that keeps running the menu in order to allow the user
    // to enter as many options as they want until they enter 4 to
    // run the simulatation
    while (userSelection != 4)
    {
        cout << "---WELCOME TO THE ELK SIMULATOR!---" << endl;
        cout << "|    --------MAIN MENU-------     |" << endl;
        cout << "|    |                      |     |" << endl;
        cout << "|    | 1.) SET GRID SIZE    |     |" << endl;
        cout << "|    | 2.) SET HERD AMOUNT  |     |" << endl;
        cout << "|    | 3.) SET WOLF AMOUNT  |     |" << endl;
        cout << "|    | 4.) RUN              |     |" << endl;
        cout << "|    | DEFAULT ANSWER = RUN |     |" << endl;
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
            // 2.) Set herd amount
        {
            // Calls function from Animals class to change
            // elk herd amount
            Animals setElkAmount;
            setElkAmount.ChangeElkHerdAmount();
        }
        break;
        case 3:
            // 3.) Set wolf amount
        {
            // Calls function from Animals class to change
            // wolf amount
            Animals setWolvesAmount;
            setWolvesAmount.ChangeWolvesAmount();
        }
        break;
        case 4:
            // 4.) Run
        {
            cout << "RUNNING" << endl;
        }
        break;
        default:
            // Runs simulation
        {
            cout << "INVAILD SELECTION..." << endl;
            userSelection = 4;
        }
        }

        // Clear the console screen after each option
        system("cls");
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

// Creates random destination point, the Elk, and the Wolves,
// moves the elk and wolves, and deletes the linked lists
// after everything is plotted
void GraphPredAndPray(fstream &foutPositions, fstream &foutCommand)
{
    // Class accessor
    // allows for accessing Animals class functions
    Animals animals;

    // String Variables to hold values for writing out to files
    string pngfile;
    string fileName;
    string index;

    // Determine the End Destination point
    animals.CreateEndDestinationPoint();
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

// Generates a random 0 or 1 for deciding elk healthy status
bool ElkHerdHealthyStatusRandomGenerator()
{
    uniform_int_distribution<int> edist(0,1); // Generate random 0 or 1
    int rolledNumber; // Store the random number
    int numberOfZeroes = 0; // Counter for number of 0's rolled
    int numberOfOnes = 0; // Counter for number of 1's rolled
    bool healthyStatus; // Variable to return true or false

    // For loop to roll 3 times
    // Counts the amount of 0's and 1's rolled
    for(int i = 0; i < 3; i++)
    {
        rolledNumber = edist(rGen);

        if(rolledNumber == 0)
        {
            numberOfZeroes++;
        }
        else
        {
            numberOfOnes++;
        }
    }

    // If number of 0's rolled > number of 1's rolled, elk is not healthy
    // else number of 1's rolled > number of 0's rolled, elk is healthy
    if (numberOfZeroes > numberOfOnes)
    {
        healthyStatus = false;
    }
    else
    {
        healthyStatus = true;
    }

    return healthyStatus;
}

// Create a dynamic function to create elk health based on
// healthy status and age.
// if age == 1 = negative impact on health (-25% health debuff)
// if healthyStatus is false = negative impact on health (-60% health debuff)
double CreateElkHerdHealth(Animals *eHerd)
{
    Animals herd;
    uniform_real_distribution<double> edist(0, herd.hGetHealth());

    double elkHealth;

    elkHealth = edist(rGen);

    if(eHerd->hGetAge() == 1)
    {
        elkHealth = elkHealth - (elkHealth * 0.25);

        if(eHerd->hGetIsHealthy() == false)
        {
            elkHealth = elkHealth - (elkHealth * 0.60);
        }
    }
    else if(eHerd->hGetIsHealthy() == false)
    {
        elkHealth = elkHealth - (elkHealth * 0.60);
    }

    return elkHealth; // Return health
}

// Generates random number for elk age, Based off elk's class variable age
int ElkHerdAgeRandomGenerator()
{
    Animals herd;
    uniform_int_distribution<int> edist(1, herd.hGetAge());

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

// Generates random number for wolves attack strength
double WolfAttackStrengthRandomGenerator()
{
    Animals wolf;
    uniform_real_distribution<double> wdist(0, wolf.wGetAttackStrength());

    return wdist(rGen);
}

// Called when a wolf is attempting a kill, Randomly generates a number between 0 - 20,
// saved throw is a number >=12
// critical save throw is roll of 20 = automatic save from kill
// critical roll of 0 = automatic successful kill
bool SavingThrowsGenerator()
{
    uniform_int_distribution<int> ranRolls(0, 20); // Generate random between 0-20
    int numberRolled = 0; // Stores the random number generated
    int successfulSave = 0; // Counts the amount of saved throws
    int unsuccessfulSave = 0; // Counts the amount of unsuccessful throws
    bool savedThrow = false; // Stores whether saved or not and then is returned

    // TODO Delete after testing or move to the kill function
    cout << "ATTEMPTING KILL..." << endl;

    for(int i = 0; i < 5;  i++)
    {
        numberRolled = ranRolls(rGen);

        if(numberRolled == 20)
        {
            cout << "ROLLED A CRITICAL SAVE " << numberRolled << endl;
            return true;
        }
        else if(numberRolled == 0)
        {
            cout << "ROLLED A CRITICAL " << numberRolled << endl;
            return false;
        }
        else if(numberRolled >= 12)
        {
            cout << "SAVED THROW " << numberRolled << endl;
            successfulSave++;
        }
        else if(numberRolled < 12 )
        {
            cout << "UNSAVED THROW " << numberRolled << endl;
            unsuccessfulSave++;
        }
    }

    if (unsuccessfulSave > successfulSave)
    {
        savedThrow = false;
    }
    else
    {
        savedThrow = true;
    }

    return savedThrow;
}

// Generates a random number to determine the end destination point
int EndDestinationPointRandomGenerator()
{
    uniform_int_distribution<int> dest(15, 50);

    return dest(rGen);
}

