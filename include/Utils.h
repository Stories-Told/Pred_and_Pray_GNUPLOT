#ifndef Utils
#define Utils

using namespace std;

// Main Functions
void RunMenu();
void CreateCommandFile(fstream &foutCommand);
void GraphPredAndPray(fstream &foutPositions, fstream &foutCommand);
void RunGnuPlot();

// Start elk
double ElkMasterRandomGenerator();
double ElkHerdRandomGenerator();
bool ElkHerdHealthyStatusRandomGenerator();
double CreateElkHerdHealth(Animals *eHerd);
int ElkHerdAgeRandomGenerator();

// Start wolves
double WolfRandomGenerator();
double WolfAttackStrengthRandomGenerator();

// Start misc
bool SavingThrowsGenerator();

#endif // Utils
