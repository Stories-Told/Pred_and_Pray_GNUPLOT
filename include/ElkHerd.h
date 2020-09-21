#ifndef ELKHERD_H
#define ELKHERD_H


class ElkHerd
{
    public:
        ElkHerd();
        virtual ~ElkHerd();

        double Gethealth() { return health; }
        void Sethealth(double val) { health = val; }

        double Getspeed() { return speed; }
        void Setspeed(double val) { speed = val; }

        double GetpositionX() { return positionX; }
        void SetpositionX(double val) { positionX = val; }

        double GetpositionY() { return positionY; }
        void SetpositionY(double val) { positionY = val; }

        int Getage() { return age; }
        void Setage(int val) { age = val; }

        int Getid() { return id; }
        void Setid(int val) {id = val;}

    protected:

    private:
        double health;
        double speed;
        double positionX;
        double positionY;
        int age;
        int id;
};

#endif // ELKHERD_H
