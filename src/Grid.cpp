#include <iostream>
#include <fstream>
#include "Grid.h"

using namespace std;

// GLOBAL CLASS ACCESSOR
Grid grid;

Grid::Grid()
{
    xSize = 50;
    ySize = 50;
}

Grid::~Grid()
{
    //dtor
}

void Grid::ChangeGridSize()
{
    int userGridSizeX;
    int userGridSizeY;

    cout << "ENTER SIZE(X): ";
    cin >> userGridSizeX;
    cout << endl;

    cout << "ENTER SIZE(Y): ";
    cin >> userGridSizeY;
    cout << endl;

    grid.SetxSize(userGridSizeX);
    grid.SetySize(userGridSizeY);
}

void Grid::OutputGridToCommand(fstream &foutCommand)
{
    foutCommand << "set xrange [-5:" << grid.GetxSize() << "]" << endl;
    foutCommand << "set yrange [-5:" << grid.GetySize() << "]" << endl;
}
