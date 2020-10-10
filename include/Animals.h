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

        double hGetAddedX() { return hAddedX; }
        void hSetAddedX(double val) { hAddedX = val; }

        double hGetPositionY() { return hPositionY; }
        void hSetPositionY(double val) { hPositionY = val; }

        double hGetAddedY() { return hAddedY; }
        void hSetAddedY(double val) { hAddedY = val; }

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
        double GetEndPointX() { return endPointX; }
        void SetEndPointX(double val) { endPointX = val; }

        double GetEndPointY() { return endPointY; }
        void SetEndPointY(double val) { endPointY = val; }

        //---------------------------------------------------------

        void CreateEndDestinationPoint();
        void MovementEvaluator();
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
        double hAddedX;
        double hPositionY;
        double hAddedY;
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
        double endPointX;
        double endPointY;
};

#endif // ANIMALS_H
