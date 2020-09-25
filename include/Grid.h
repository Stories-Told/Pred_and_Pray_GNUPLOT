#ifndef GRID_H
#define GRID_H

using namespace std;

class Grid
{
    public:
        Grid();
        virtual ~Grid();

        int GetxSize() { return xSize; }
        void SetxSize(int val) { xSize = val; }

        int GetySize() { return ySize; }
        void SetySize(int val) { ySize = val; }

        void ChangeGridSize();
        void OutputGridToCommand(fstream &foutCommand);

    private:
        int xSize;
        int ySize;
};

#endif // GRID_H
