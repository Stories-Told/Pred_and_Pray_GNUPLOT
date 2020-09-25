#ifndef Utils
#define Utils

using namespace std;

void RunMenu();
void CreateCommandFile(fstream &foutCommand);
void GraphPredAndPray(fstream &foutPositions, fstream &foutCommand);
void RunGnuPlot();

double ElkMasterRandomGenerator();
double ElkHerdRandomGenerator();
double WolfRandomGenerator();

#endif // Utils
