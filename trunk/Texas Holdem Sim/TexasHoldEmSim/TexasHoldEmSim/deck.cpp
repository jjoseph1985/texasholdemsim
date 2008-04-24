#include "deck.h"

void Deck::Deck(){}

void Deck::ShuffleCard()
{
    srand ( time(NULL) );


    // vector<string>deck; // Intializes the vector card

    deck.push_back("As"); //populate the vector with cards of spade
    deck.push_back("Ks");
    deck.push_back("Qs");
    deck.push_back("Js");
    deck.push_back("Ts");
    deck.push_back("9s");
    deck.push_back("8s");
    deck.push_back("7s");
    deck.push_back("6s");
    deck.push_back("5s");
    deck.push_back("4s");
    deck.push_back("3s");
    deck.push_back("2s");		
     
    deck.push_back("Ah"); // populate the vector with cards of heart
    deck.push_back("Kh");
    deck.push_back("Qh");
    deck.push_back("Jh");
    deck.push_back("Th");
    deck.push_back("9h");
    deck.push_back("8h");
    deck.push_back("7h");
    deck.push_back("6h");
    deck.push_back("5h");
    deck.push_back("4h");
    deck.push_back("3h");
    deck.push_back("2h");	

    deck.push_back("Ac"); // populate the vector with cards of club
    deck.push_back("Kc");
    deck.push_back("Qc");
    deck.push_back("Jc");
    deck.push_back("Tc");
    deck.push_back("9c");
    deck.push_back("8c");
    deck.push_back("7c");
    deck.push_back("6c");
    deck.push_back("5c");
    deck.push_back("4c");
    deck.push_back("3c");
    deck.push_back("2c");	

    deck.push_back("Ad"); //populate the vector with cards of diamond 
    deck.push_back("Kd");
    deck.push_back("Qd");
    deck.push_back("Jd");
    deck.push_back("Td");
    deck.push_back("9d");
    deck.push_back("8d");
    deck.push_back("7d");
    deck.push_back("6d");
    deck.push_back("5d");
    deck.push_back("4d");
    deck.push_back("3d");
    deck.push_back("2d");	
     
  //  cout<<"Card are not Shuffle"<<endl;
   // for( int card=0; card<52; card++)
    //{
     //  cout<< deck[card]<<endl;

    //}

    random_shuffle(deck.begin(), deck.end());

    //cout<<"Card are Shuffle randomly"<<endl;
    //for( int card=0; card<52; card++)
    //{
      // cout<< deck[card]<<endl;

    //}
}