// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>
#include <limits>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "card.h"
#include "table.h"
#include "hand.h"

using namespace std;

class Player
{
  public:
        Player::Player(double m)
       ~Player();
        
        void AddMoney(double amt);
      double GetMoney();
        
        hand ShowHand();
        void AddCard(card c, int loc);
        void ClearCards();
        
      double Action(bool limitAction);
        bool DidFold();
        bool DidBust();
        bool DidAllIn();
        void Reset();
        
        void SetPos(int pos);
        int  GetPos();
 
 
  private:
        vector<card> holeCards;
        vector<card> tableCards;
        hand myHand;
      
      double money;
        bool fold;
        bool bust;
        bool allIn;
        int  pos;

     /* Unimplemented AI Stuff
        enum actionNames makeDec();     
        enum actionNames preflopDec();
        enum actionNames simulate();
        double sim( Table& );
        double trial( Table& );
        double amtBet;

        map<string, bool> aDeck;
        map<int, string>  bDeck;
     */
};

#endif
