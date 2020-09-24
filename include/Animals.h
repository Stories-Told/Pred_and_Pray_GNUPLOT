#ifndef ANIMALS_H
#define ANIMALS_H

using namespace std;

class Animals
{
    public:
        Animals();
        virtual ~Animals();

        // START ELK MASTER
        double mGetHealth() { return mHealth; }
        void mSetHealth(double val) { mHealth = val; }

        double mGetSpeed() { return mSpeed; }
        void mSetSpeed(double val) { mSpeed = val; }

        double mGetPositionX() { return mPositionX; }
        void mSetPositionX(double val) { mPositionX = val; }

        double mGetPositionY() { return mPositionY; }
        void mSetPositionY(double val) { mPositionY = val; }

        void CreateElkMaster(int i, fstream &foutPositions);

        // START ELK HERD
        double hGetHealth() { return hHealth; }
        void hSetHealth(double val) { hHealth = val; }

        double hGetSpeed() { return hSpeed; }
        void hSetSpeed(double val) { hSpeed = val; }

        double hGetPositionX() { return hPositionX; }
        void hSetPositionX(double val) { hPositionX = val; }

        double hGetPositionY() { return hPositionY; }
        void hSetPositionY(double val) { hPositionY = val; }

        int hGetAge() { return hAge; }
        void hSetAge(int val) { hAge = val; }

        int hGetID() { return hID; }
        void hSetID(int val) { hID = val; }

        void CreateElkHerd(int i, fstream &foutPositions);

        // Linked list Elk Herd
        Animals *hGetNext() { return hNext; }
        void hSetNext( Animals *h) { hNext = h; }

        // START WOLVES
        double wGetSpeed() { return wSpeed; }
        void wSetSpeed(double val) { wSpeed = val; }

        double wGetPositionX() { return wPositionX; }
        void wSetPositionX(double val) { wPositionX = val; }

        double wGetPositionY() { return wPositionY; }
        void wSetPositionY(double val) { wPositionY = val; }

        int wGetID() { return wID; }
        void wSetID(double val) { wID = val; }

        // Linked list Wolves
        Animals *wGetNext() { return wNext; }
        void wSetNext(Animals *w) { wNext = w; }

        void CreateWolves(int i, fstream &foutPositions);

    private:
        // Start elk master
        double mHealth;
        double mSpeed;
        double mPositionX;
        double mPositionY;

        // Start elk herd
        double hHealth;
        double hSpeed;
        double hPositionX;
        double hPositionY;
        int hAge;
        int hID;
        // Herd linked list
        Animals *hNext;

        // Start wolves
        double wSpeed;
        double wPositionX;
        double wPositionY;
        int wID;
        // Wolf linked list
        Animals *wNext;
};

#endif // ANIMALS_H
