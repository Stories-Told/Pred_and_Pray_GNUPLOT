#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <sstream>
#include "Animals.h"
#include "Utils.h"

using namespace std;

// GLOBAL CLASS
Animals animals;
//ELK HERD POINTERS
Animals *hHead = NULL;
Animals *hCurrent = NULL;
//WOLF POINTERS
Animals *wHead = NULL;
Animals *wCurrent = NULL;

Animals::Animals()
{
    // Start elk master
    mHealth = 100.0;
    mSpeed = 1.5; // TODO reset to 5.0 after testing
    mPositionX = 1.0;
    mPositionY = 5.0;

    // Start elk herd
    hHealth = 100.0;
    hSpeed = 1.5;
    hPositionX = 0.0;
    hPositionY = 0.0;
    hAge = 0;
    hID = 0;
    numberOfHerdAlive = 10;
    hNext = NULL;

    // Start wolves
    wSpeed = 1.5; // TODO reset to 5.0 after testing
    wPositionX = 0.0;
    wPositionY = 0.0;
    wID = 0;
    wNext = NULL;
}

Animals::~Animals()
{
    //dtor
}

void Animals::CreateElkMaster()
{
    // Variables to hold position values
    double dx = 0.0, dy =  0.0;

    // Generate the Elk Master's postion values
    dx = Utils::ElkMasterRandomGenerator(); // sets a random number to dx
    dy = Utils::ElkMasterRandomGenerator(); // sets a random number to dy

    // Herd masters location
    animals.mSetPositionX(dx);
    animals.mSetPositionY(dy);
}

void Animals::CreateElkHerd()
{
    // Variable for the Elk Herd Link list
    Animals *eHerd = NULL;

    // Variable to keep track of when to exit while loop
    // For creating amount of elk herd
    int countHerdAmount = 0;

    // Variables to hold position values
    double dx = 0.0, dy =  0.0;

    // Elk herd while loop
    // Create elk herd data in a link list
    while (countHerdAmount < animals.GetNumberOfHerdAlive())
    {
        // Create a new eHerd each loop
        // and store it into the next link list location
        eHerd = new Animals;

        // Generates random number used for position data
        dx = Utils::ElkHerdRandomGenerator();
        dy = Utils::ElkHerdRandomGenerator();

        // Stores the x and y position in the current eHerd
        eHerd->hSetPositionX(animals.mGetPositionX() - dx);
        eHerd->hSetPositionY(animals.mGetPositionY() - dy);

        // Sets the Elk Herd's ID number
        eHerd->hSetID(countHerdAmount);

        // if statement to check if head is NULL
        // meaning if it is NULL then that is the first spot
        // in the linked list and store the first eHerd there
        if(hHead == NULL)
        {
            hHead = eHerd;
        }
        // After the first loop this else statement will execute
        // where it will move forward to the next link list spot
        else
        {
            eHerd->hSetNext(hHead);
            hHead = eHerd;
        }
        // Keeps track of counting in order to exit the
        // while loop at the value determined
        countHerdAmount++;
    }
    // Reset the counter for the while loop
    countHerdAmount = 0;
}

void Animals::CreateWolves()
{
    // Variables for Wolf linked list
    Animals *wPredator = NULL;

    // Variable to keep track of when to exit while loop
    // For creating amount of wolves
    int countWolfAmount = 0;
    // Variables to hold position values
    double dx = 0.0, dy =  0.0;

    while (countWolfAmount < 5)
    {
        // Create a new wolf each loop
        // and store it in the link list
        wPredator = new Animals;

        // Generate the wolf random x and y position data
        dx = Utils::WolfRandomGenerator();
        dy = Utils::WolfRandomGenerator();

        // Stores the x and y postion data in the current wPredator
        // TODO change to wolves follow the herd instead of master
        wPredator->wSetPositionX(animals.mGetPositionX() - dx);
        wPredator->wSetPositionY((animals.mGetPositionY() + 10) - dy);

        // Set the wolves ID's
        wPredator->wSetID(countWolfAmount);

        // if statement to check if head is NULL
        // meaning if it is NULL then that is the first spot
        // in the linked list and store the first wPredator there
        if (wHead == NULL)
        {
            wHead = wPredator;
        }
        // After the first loop this else statement will execute
        // where it will move forward to the next link list spot
        else
        {
            wPredator->wSetNext(wHead);
            wHead = wPredator;
        }
        // Keeps track of counting in order to exit the
        // while loop at the value determined
        countWolfAmount++;
    }
    // Reset the count for the while loop
    countWolfAmount = 0;
}

void Animals::WriteOutPositionData(int i, fstream &foutPositions)
{
    // ------------------ELK MASTER---------------------------
    // saves the elk master position data into the files for
    foutPositions << i + animals.mGetPositionX() << " "
                  << i + animals.mGetPositionY() << " "
                  << ".3" << endl; // ".3" size of dot

    // -----------------ELK HERD------------------------------
    // Write out the elk herd data to the .dat files
    hCurrent = hHead;
    while(hCurrent != NULL)
    {
        //TODO delete after testing
        cout << "HERD: " << hCurrent->hGetID() << endl;

        foutPositions << i + hCurrent->hGetPositionX() << " "
                      << i + hCurrent->hGetPositionY() << " "
                      << ".15" << endl; // ".15" size of dot

        // Move down the list
        hCurrent = hCurrent->hGetNext();
    }

    // -----------------WOLVES----------------------------------
    // Write out the wolves data to the .dat files
    wCurrent = wHead;
    while (wCurrent != NULL)
    {
        //TODO delete after testing
        cout << "WOLF: " << wCurrent->wGetID() << endl;
        foutPositions << i + wCurrent->wGetPositionX() << " "
                      << i + wCurrent->wGetPositionY() << " "
                      << ".1" << endl; //".1" = size of dot

        wCurrent = wCurrent->wGetNext();
    }

}


void Animals::DoesWolfKillHerd()
{
    //TODO Write function to compare wolves to elk herd based off their age
    // and health. If the conditions are met then the wolves will kill it

    if(animals.GetNumberOfHerdAlive() > 1)
    {
        animals.SetNumberOfHerdAlive(animals.GetNumberOfHerdAlive() - 1);
    }
}

void Animals::DeleteAllLinkList()
{
    hCurrent = hHead;
    while (hCurrent != NULL)
    {
        hHead = hCurrent->hGetNext();
        delete hCurrent;
        hCurrent = hHead;
    }
    delete hHead;

    wCurrent = wHead;
    while(wCurrent != NULL)
    {
        wHead = wCurrent->wGetNext();
        delete wCurrent;
        wCurrent = wHead;
    }
    delete wHead;
}
