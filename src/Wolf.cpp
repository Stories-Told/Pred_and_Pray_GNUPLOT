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
mt19937_64 wGPTR(seed);
// RANDOM NUMBER DISTRIBUTORS FOR THE WOLVES
normal_distribution<double> wdist(0, 1.0); // Wolf speed(5.0) //TODO set wolf speed to 5

Wolf::Wolf()
{
    speed = 5.0;
    positionX = 0.0;
    positionY = 0.0;
    next = NULL;
}

Wolf::~Wolf()
{
    //dtor
}

void Wolf::CreateWolves(double dx, double dy, int i, std::fstream &foutPositions,
                        ElkMaster eMaster)
{
    // Variables for Wolf linked list
    Wolf *head = NULL;
    Wolf *current = NULL;
    Wolf *wPredator = NULL;
    int countWolfAmount = 0;

    while (countWolfAmount < 5)
    {
        // Create a new wolf each loop
        // and store it in the link list
        wPredator = new Wolf;

        //TODO set wolves id (first I need to make the gets and sets in the class)

        // Generate the wolf random x and y position data
        dx = wdist(wGPTR);
        dy = wdist(wGPTR);

        // Stores the x and y postion data in the current wPredator
        // TODO change to wolves follow the herd instead of master
        wPredator->SetpositionX(eMaster.GetpositionX() - dx);
        wPredator->SetpositionY((eMaster.GetpositionY() + 10) - dy);

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
            wPredator->SetNext(head);
            head = wPredator;
        }
        // Keeps track of counting in order to exit the
        // while loop at the value determined
        countWolfAmount++;
    }
    // Reset the count for the while loop
    countWolfAmount = 0;

    // Write out the wolves data
    current = head;
    while (current != NULL)
    {
        if (current != head)
        {
            foutPositions << endl;
        }

        foutPositions << i + current->GetpositionX() << " "
                      << i + current->GetpositionY() << " "
                      << ".1" << endl; //".1" = size of dot

        current = current->GetNext();
    }

    // Delete the linked list
    current = head;
    while(current != NULL)
    {
        head = current->GetNext();
        delete current;
        current = head;
    }
    delete head;
}
