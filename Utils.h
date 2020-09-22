#pragma once

#ifndef Utils
#define Utils

#include "ElkMaster.h"

void CreateCommandFile(std::fstream &foutCommand);
void GraphPredAndPray(std::fstream &foutPositions, std::fstream &foutCommand);
void RunGnuPlot();

#endif // Utils
