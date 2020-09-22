#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <sstream>
#include "Animals.h"

using namespace std;


// TODO add random generator to the Utils.h
// GLOBAL SEED FOR RANDOM GENERATORS
const unsigned int seed = time(0);
// RANDOM NUMBER GENERATORS
mt19937_64 emGPTR(seed);
mt19937_64 eGPTR(seed);
mt19937_64 wGPTR(seed);
// RANDOM NUMBER DISTRIBUTORS FOR THE HERD
normal_distribution<double> emdist(0, 5.0); // Elk master speed (5.0)
normal_distribution<double> edist(0, 1.5); // Elk herd speed (1.5)
normal_distribution<double> wdist(0, 1.0); // Wolf speed(5.0) //TODO set wolf speed to 5

// GLOBAL CLASS
Animals animals;

Animals::Animals()
{
    // Start elk master
    mHealth = 100.0;
    mSpeed = 5.0;
    mPositionX = 1.0;
    mPositionY = 5.0;
    // Start elk herd
    hHealth = 100.0;
    hSpeed = 1.5;
    hPositionX = 0.0;
    hPositionY = 0.0;
    hAge = 0;
    hID = 0;
    hNext = NULL;
    // Start wolves
    wSpeed = 5.0;
    wPositionX = 0.0;
    wPositionY = 0.0;
    wNext = NULL;
}

Animals::~Animals()
{
    //dtor
}

// ELK MASTER
void Animals::CreateElkMaster(double dx, double dy, int i, fstream &foutPositions)
{
    // Creates the Master, Herd, and Wolves
    // Write the herd masters positions
    dx = emdist(emGPTR); // sets a random number to dx
    dy = emdist(emGPTR); // sets a random number to dy

    // Herd masters location
    animals.mSetPositionX(dx);
    animals.mSetPositionY(dy);
    // saves the destination data into the files for elk master
    foutPositions << i + animals.mGetPositionX() << " "
                  << i + animals.mGetPositionY() << " "
                  << ".3" << endl; // ".3" size of dot
}

// ELK HERD
void Animals::CreateElkHerd(double dx, double dy, int i, fstream &foutPositions)
{
    // Variables for the Elk Herd Link list
    Animals *head = NULL;
    Animals *current = NULL;
    Animals *eHerd = NULL;
    int countHerdAmount = 0;

    // Elk herd for loop
    // Create elk herd data in a link list
    while (countHerdAmount < 10)
    {
        // Create a new eHerd each loop
        // and store it into the next link list location
        eHerd = new Animals;

        // Generates random number used for position data
        dx = edist(eGPTR);
        dy = edist(eGPTR);

        // Stores the x and y position in the current eHerd
        eHerd->hSetPositionX(animals.mGetPositionX() - dx);
        eHerd->hSetPositionY(animals.mGetPositionY() - dy);

        // Sets the Elk Herd's ID number
        eHerd->hSetID(countHerdAmount);

        // if statement to check if head is NULL
        // meaning if it is NULL then that is the first spot
        // in the linked list and store the first eHerd there
        if(head == NULL)
        {
            head = eHerd;
        }
        // After the first loop this else statement will execute
        // where it will move forward to the next link list spot
        else
        {
            eHerd->hSetNext(head);
            head = eHerd;
        }
        // Keeps track of counting in order to exit the
        // while loop at the value determined
        countHerdAmount++;
    }
    // Reset the counter for the while loop
    countHerdAmount = 0;

    // Write out the elk herd data to the .dat files
    current = head;
    while(current != NULL)
    {
        if(current != head)
        {
            foutPositions << endl;
        }

        foutPositions << i + current->hGetPositionX() << " "
                      << i + current->hGetPositionY() << " "
                      << ".15" << endl; // ".15" size of dot

        // Move down the list
        current = current->hGetNext();
    }

    // Delete the linked list
    current = head;
    while (current != NULL)
    {
        head = current->hGetNext();
        delete current;
        current = head;
    }
    delete head;
}


// WOLVES
void Animals::CreateWolves(double dx, double dy, int i, fstream &foutPositions)
{
    // Variables for Wolf linked list
    Animals *head = NULL;
    Animals *current = NULL;
    Animals *wPredator = NULL;
    int countWolfAmount = 0;

    while (countWolfAmount < 5)
    {
        // Create a new wolf each loop
        // and store it in the link list
        wPredator = new Animals;

        //TODO set wolves id (first I need to make the gets and sets in the class)

        // Generate the wolf random x and y position data
        dx = wdist(wGPTR);
        dy = wdist(wGPTR);

        // Stores the x and y postion data in the current wPredator
        // TODO change to wolves follow the herd instead of master
        wPredator->wSetPositionX(animals.mGetPositionX() - dx);
        wPredator->wSetPositionY((animals.mGetPositionY() + 10) - dy);

        // if statement to check if head is NULL
        // meaning if it is NULL then that is the first spot
        // in the linked list and store the first wPredator there
        if (head == NULL)
        {
            head = wPredator;
        }
        // After the first loop this else statement will execute
        // where it will move forward to the next link list spot
        else
        {
            wPredator->wSetNext(head);
            head = wPredator;
        }
        // Keeps track of counting in order to exit the
        // while loop at the value determined
        countWolfAmount++;
    }
    // Reset the count for the while loop
    countWolfAmount = 0;

    // Write out the wolves data to the .dat files
    current = head;
    while (current != NULL)
    {
        if (current != head)
        {
            foutPositions << endl;
        }

        foutPositions << i + current->wGetPositionX() << " "
                      << i + current->wGetPositionY() << " "
                      << ".1" << endl; //".1" = size of dot

        current = current->wGetNext();
    }

    // Delete the linked list
    current = head;
    while(current != NULL)
    {
        head = current->wGetNext();
        delete current;
        current = head;
    }
    delete head;
}