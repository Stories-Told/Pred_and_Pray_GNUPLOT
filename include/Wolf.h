#ifndef WOLF_H
#define WOLF_H


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


    protected:

    private:
        double speed;
        double positionX;
        double positionY;
};

#endif // WOLF_H
