#ifndef ELKMASTER_H
#define ELKMASTER_H

using namespace std;

class ElkMaster
{
    public:
        ElkMaster();
        virtual ~ElkMaster();

        double Gethealth() { return health; }
        void Sethealth(double val) { health = val; }

        double Getspeed() { return speed; }
        void Setspeed(double val) { speed = val; }

        double GetpositionX() { return positionX; }
        void SetpositionX(double val) { positionX = val; }

        double GetpositionY() { return positionY; }
        void SetpositionY(double val) { positionY = val; }

    private:
        double health;
        double speed;
        double positionX;
        double positionY;
};

#endif // ELKMASTER_H
