#ifndef ANIMALS_H
#define ANIMALS_H

using namespace std;

class Animals
{
    public:
        Animals();
        virtual ~Animals();

        // START ELK HERD
        bool hGetIsElkMaster() { return isElkMaster; }
        void hSetIsElkMaster(bool val) { isElkMaster = val; }

        bool hGetIsHealthy() { return isHealthy; }
        void hSetIsHealthy(bool val) { isHealthy = val; }

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

        int hGetNumberOfHerdAlive() { return numberOfHerdAlive; }
        void hSetNumberOfHerdAlive(int val) { numberOfHerdAlive = val; }

        void CreateElkHerd();
        void MoveElkHerd();

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

        double wGetAttackStrength() { return wAttackStrength; }
        void wSetAttackStrength(double val) { wAttackStrength = val; }

        int wGetID() { return wID; }
        void wSetID(double val) { wID = val; }

        int wGetNumberOfWolvesAlive() { return numberOfWolvesAlive; }
        void wSetNumberOfWolvesAlive(int val) { numberOfWolvesAlive = val; }

        // Linked list Wolves
        Animals *wGetNext() { return wNext; }
        void wSetNext(Animals *w) { wNext = w; }

        void CreateWolves();
        void MoveWolves();

        // Start Misc
        bool GetNoKillsPossible() {return noMoreKillsPossible;}
        void SetNoKillsPossible(bool val) { noMoreKillsPossible = val; }

        //---------------------------------------------------------

        void WriteOutPositionData(int i, fstream &foutPositions);
        void DoesWolfKillHerd();
        void DeleteAllLinkList();

        void ChangeElkHerdAmount();
        void ChangeWolvesAmount();

    private:

        // Start elk herd
        bool isElkMaster;
        bool isHealthy;
        double hHealth;
        double hSpeed;
        double hPositionX;
        double hPositionY;
        int hAge;
        int hID;
        int numberOfHerdAlive;
        // Herd linked list
        Animals *hNext;

        // Start wolves
        double wSpeed;
        double wPositionX;
        double wPositionY;
        double wAttackStrength;
        bool wNoKillPossible;
        int wID;
        int numberOfWolvesAlive;
        // Wolf linked list
        Animals *wNext;

        // Misc
        bool noMoreKillsPossible;
};

#endif // ANIMALS_H
