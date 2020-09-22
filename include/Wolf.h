#ifndef WOLF_H
#define WOLF_H

#include "ElkMaster.h"

class Wolf
{
    public:
        Wolf();
        virtual ~Wolf();

        double Getspeed() { return speed; }
        void Setspeed(double val) { speed = val; }

        double GetpositionX() { return positionX; }
        void SetpositionX(double val) { positionX = val; }

        double GetpositionY() { return positionY; }
        void SetpositionY(double val) { positionY = val; }

        // Linked list
        Wolf *GetNext() { return next; }
        void SetNext (Wolf *n) { next = n;}

        void CreateWolves(double dx, double dy, int i, std::fstream &foutPositions,
                          ElkMaster  eMaster);

    private:
        double speed;
        double positionX;
        double positionY;
        // Linked list
        Wolf *next;
};

#endif // WOLF_H
