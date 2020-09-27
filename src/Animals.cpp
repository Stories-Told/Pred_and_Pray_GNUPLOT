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
Animals *previous = NULL;
//WOLF POINTERS
Animals *wHead = NULL;
Animals *wCurrent = NULL;

// TODO TESTING (Move out of global scope later)
// Variables to save the elk masters position
double elkMastersXPosition;
double elkMastersYPosition;

Animals::Animals()
{
    // Start elk herd
    isElkMaster = false;
    hHealth = 100.0;
    hSpeed = 1.5;
    hPositionX = 0.0;
    hPositionY = 0.0;
    hAge = 50.0;
    hID = 0;
    numberOfHerdAlive = 10;
    hNext = NULL;

    // Start wolves
    wSpeed = 1.5; // TODO reset to 5.0 after testing
    wPositionX = 0.0;
    wPositionY = 0.0;
    wAttackStrength = 60.0;
    wID = 0;
    numberOfWolvesAlive = 5;
    wNext = NULL;

    // Start Misc
    noMoreKillsPossible = false;
}

Animals::~Animals()
{
    //dtor
}

// Creates a linked list of elk. Elk master = the first one created
// User selection at menu allows for creating more than the default value of elk
void Animals::CreateElkHerd()
{
    // Variable for the Elk Herd Link list
    Animals *eHerd = NULL;

    // Variable to keep track of when to exit while loop
    // For creating amount of elk herd
    int countHerdAmount = 0;

    // Elk herd while loop
    // Create elk herd data in a link list
    while (countHerdAmount < animals.hGetNumberOfHerdAlive())
    {
        // Create a new eHerd each loop
        // and store it into the next link list location
        eHerd = new Animals;

        // First object created will be the elk master and
        // set the isElkMaster to true marking them as the master
        if (countHerdAmount == 0 )
        {
            eHerd->hSetID(countHerdAmount);
            eHerd->hSetIsElkMaster(true);
        }
        // Creates the elk herd after the master
        else
        {
            // Stores the x,y position and ID in the current eHerd
            eHerd->hSetID(countHerdAmount);
            eHerd->hSetHealth(Utils::ElkHerdHealthRandomGenerator());
            eHerd->hSetAge(Utils::ElkHerdAgeRandomGenerator());
        }

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

// Moves the elk in the link list, elk herd follows the movement of elk master
void Animals::MoveElkHerd()
{
    double dx, dy;

    hCurrent = hHead;
    while (hCurrent != NULL)
    {
        if (hCurrent->hGetIsElkMaster() == true)
        {
            elkMastersXPosition = Utils::ElkMasterRandomGenerator();
            elkMastersYPosition = Utils::ElkMasterRandomGenerator();

            hCurrent->hSetPositionX(elkMastersXPosition);
            hCurrent->hSetPositionY(elkMastersYPosition);
        }
        else
        {
            dx = Utils::ElkHerdRandomGenerator();
            dy = Utils::ElkHerdRandomGenerator();

            hCurrent->hSetPositionX(elkMastersXPosition - dx);
            hCurrent->hSetPositionY(elkMastersYPosition - dy);
        }


        hCurrent = hCurrent->hGetNext();
    }
}

// Creates a linked list of wolves. User selection at menu allows for creating
// more than the default value.
void Animals::CreateWolves()
{
    // Variables for Wolf linked list
    Animals *wPredator = NULL;

    // Variable to keep track of when to exit while loop
    // For creating amount of wolves
    int countWolfAmount = 0;
    // Variable to hold a random number for wolves attack strength
    double wolfStrength;

    while (countWolfAmount < animals.numberOfWolvesAlive)
    {
        // Create a new wolf each loop
        // and store it in the link list
        wPredator = new Animals;

        wolfStrength = Utils::WolfAttackStrengthRandomGenerator();

        // Set the wolves ID's
        wPredator->wSetID(countWolfAmount);
        wPredator->wSetAttackStrength(wolfStrength);

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

// Moves the wolves in the link list, TODO change wolves to follow elk herd, not master
void Animals::MoveWolves()
{
    // Variables to hold position data
    double dx, dy;

    wCurrent = wHead;
    while (wCurrent != NULL)
    {
        dx = Utils::WolfRandomGenerator();
        dy = Utils::WolfRandomGenerator();

        wCurrent->wSetPositionX(elkMastersXPosition - dx);
        wCurrent->wSetPositionY((elkMastersYPosition + 10) - dy);

        wCurrent = wCurrent->wGetNext();
    }
}

// Writes out to the .dat files (foutPositions) the newly updated positioning
// data for the elk and wolves
void Animals::WriteOutPositionData(int i, fstream &foutPositions)
{
    // -----------------ELK HERD------------------------------
    // Write out the elk herd data to the .dat files
    hCurrent = hHead;
    while(hCurrent != NULL)
    {

        //TODO delete after testing
        cout << "HERD: " << hCurrent->hGetID() << " HEALTH: " << hCurrent->hGetHealth()
             << " IS MASTER?: " << hCurrent->hGetIsElkMaster()
             << " AGE: " << hCurrent->hGetAge() << endl;


        if (hCurrent->hGetIsElkMaster() == true)
        {
            foutPositions << i + hCurrent->hGetPositionX() << " "
                          << i + hCurrent->hGetPositionY() << " "
                          << ".5" << endl; // ".15" size of dot
        }

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
        cout << "WOLF: " << wCurrent->wGetID()
             << " ATTACK STRENGTH: " << wCurrent->wGetAttackStrength() << endl;


        foutPositions << i + wCurrent->wGetPositionX() << " "
                      << i + wCurrent->wGetPositionY() << " "
                      << ".1" << endl; //".1" = size of dot

        wCurrent = wCurrent->wGetNext();
    }

}

// Checks to see if a wolf will kill a elk, if so then delete that elk
// from the linked list. If there are no more kills possible this function
// will not run (unless the animals.noMoreKillsPossible is updated back to false)
void Animals::DoesWolfKillHerd()
{
    // Variable to keep track of the amount of no kills recorded per loop
    // if the amount of no kills = the amount of wolves, then
    // there are no more kills possible and exits the function
    int countNoKills = 0;
    if (animals.noMoreKillsPossible == true) { return; }

    // Start of the comparing loop
    // sets herd's current and wolf's current to the head node
    // to begin the iteration through the linked lists
    hCurrent = hHead;
    wCurrent = wHead;
    while (wCurrent != NULL)
    {
        // While loop to compare all the herd(amount of elk) to one wolf
        // at at time(current wolf)
        while (hCurrent != NULL)
        {
            // Compares the wolf's random generated strength to
            // the elks random generated health. If the strength
            // is greater than the elks health, the wolf will
            // kill the elk and causes to break out of the elk's while loop,
            // delete the elk, and then move to the next wolf in the list
            if (wCurrent->wGetAttackStrength() > hCurrent->hGetHealth())
            {
                break;
            }
            // If the wolf's strength is not greater than the elk's health
            // it outputs to the console which wolf id it is, his strength,
            // the elk's id and his health. Then moves to the next herd
            // in the link list to compare against the current wolf
            else
            {
                cout << "WOLF " << wCurrent->wGetID() << " STRENGTH " << wCurrent->wGetAttackStrength()
                     << " is less than ELK " << hCurrent->hGetID() << " HEALTH " << hCurrent->hGetHealth()
                     << endl;

                previous = hCurrent;
                hCurrent = hCurrent->hGetNext();
            }
        }

        // Either after breaking from the compare while loop or upon exit
        // the following if, else if, else, will conduct the correct linked
        // list deletion.
        // if = no possible kill
        // (if countNoKills = amount of wolves, then sets noMoreKillsPossible to true)
        if (hCurrent == NULL)
        {
            cout << "NO KILL..." << endl;

            countNoKills++;
            if(countNoKills == animals.numberOfWolvesAlive) { animals.noMoreKillsPossible = true; }
        }
        // else if = the current elk is the the head elk
        // makes current the head, then sets the head to the next one
        // in the list, and then deletes current(old head link value)
        else if(hCurrent == hHead)
        {
            cout << "HEAD " << hCurrent->hGetID() << " KILLED BY WOLF " << wCurrent->wGetID() << endl;
            hCurrent = hHead;
            hHead = hHead->hNext;
            delete hCurrent;
        }
        // else = current elk anywhere else in the list
        // sets previous's pointer to the node in front
        // of the current elk node, and then deletes the current elk
        else
        {
            cout << "Wolf " << wCurrent->wGetID() << " Kills elk " << hCurrent->hGetID() << endl;
            previous->hNext = hCurrent->hNext;

            delete hCurrent;
        }

        // Resets the herd back to the first one in the list
        // for the next compare iteration for the next wolf
        // and goes to the next wolf in the wolf linked list
        hCurrent = hHead;
        wCurrent= wCurrent->wGetNext();
    }
}

// Deletes all the elk and wolves link lists to free up memory
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

// Called in the menu, changes the amount of elk that are created for simulation
void Animals::ChangeElkHerdAmount()
{
    int userHerdAmount;

    cout << "ENTER HERD AMOUNT: ";
    cin >> userHerdAmount;
    cout << endl;

    animals.hSetNumberOfHerdAlive(userHerdAmount);
}

// Called in the menu, changes the amount of wolves that are create for simulation
void Animals::ChangeWolvesAmount()
{
    int userWolvesAmount;

    cout << "ENTER WOLVES AMOUNT: ";
    cin >> userWolvesAmount;
    cout << endl;

    animals.wSetNumberOfWolvesAlive(userWolvesAmount);
}
