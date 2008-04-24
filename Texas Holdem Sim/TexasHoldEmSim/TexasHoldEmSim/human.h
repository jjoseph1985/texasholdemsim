// human.h

#ifndef HUMAN_H
#define HUMAH_H

#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "holecards.h"

using namespace std;

class humanPlayer
{
    public:
        humanPlayer();
        humanPlayer(int);
        void addMoney(int);
        void pointToTable( map<string, double>* mptr );
        double aggressiveness();
        double tightness();

        void fold();
        void betRaise(double);
        void checkCall(double);
        void busted();
        double getMoney();
        void unfold();
        bool checkBust();
        bool checkFold();

        map<string, double>* getWeights();
        double getWgt( holeCards );
        void updateWeights();
        void wonHand( double n );
        void addFlopSeen(); 
        void foldBeforeFlop();

    private:
        //void initTable( map<string, double>& );
        map<string, double>* weightTable;
        double chipCount;
        int handsPlayed;
        int handswon;
        int flopsSeen;
        int raises;
        bool out;
        bool bust;
}; // humanPlayer


#endif
