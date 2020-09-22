#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <sstream>
#include "ElkMaster.h"
#include "ElkHerd.h"
#include "Wolf.h"

using namespace std;

// GLOBAL SEED FOR RANDOM GENERATORS
const unsigned int seed = time(0);
// RANDOM NUMBER GENERATORS
mt19937_64 eGPTR(seed);
// RANDOM NUMBER DISTRIBUTORS FOR THE HERD
normal_distribution<double> edist(0, 1.5); // Elk herd speed (1.5)

ElkHerd::ElkHerd()
{
    health = 100.0;
    speed = 3.5;
    positionX = 0.0;
    positionY = 0.0;
    age = 0;
    id = 0;
    next = NULL;
}

ElkHerd::~ElkHerd()
{
    //dtor
}

void ElkHerd::CreateElkHerd(double dx, double dy, int i, std::fstream &foutPositions,
                            ElkMaster eMaster)
{
    // Variables for the Elk Herd Link list
    ElkHerd *head = NULL;
    ElkHerd *current = NULL;
    ElkHerd *eHerd = NULL;
    int countHerdAmount = 0;

    // Elk herd for loop
    // Create elk herd data in a link list
    while (countHerdAmount < 10)
    {
        // Create a new eHerd each loop
        // and store it into the next link list location
        eHerd = new ElkHerd;

        // Sets the Elk Herd's ID number
        eHerd->Setid(countHerdAmount);

        // Generates random number used for position data
        dx = edist(eGPTR);
        dy = edist(eGPTR);

        // Stores the x and y position in the current eHerd
        eHerd->SetpositionX(eMaster.GetpositionX() - dx);
        eHerd->SetpositionY(eMaster.GetpositionY() - dy);

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
            eHerd->SetNext(head);
            head = eHerd;
        }
        // Keeps track of counting in order to exit the
        // while loop at the value determined
        countHerdAmount++;
    }
    // Reset the counter for the while loop
    countHerdAmount = 0;


    // Write out the elk herd data
    current = head;
    while(current != NULL)
    {
        if(current != head)
        {
            foutPositions << endl;
        }

        foutPositions << i + current->GetpositionX() << " "
                      << i + current->GetpositionY() << " "
                      << ".15" << endl; // ".15" size of dot

        // Move down the list
        current = current->GetNext();
    }

    // Delete the linked list
    current = head;
    while (current != NULL)
    {
        head = current->GetNext();
        delete current;
        current = head;
    }
    delete head;
}