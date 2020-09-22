#pragma once

#ifndef Utils
#define Utils
using namespace std;

void CreateCommandFile(fstream &foutCommand);
void GraphPredAndPray(fstream &foutPositions, fstream &foutCommand);
void RunGnuPlot();

#endif // Utils
