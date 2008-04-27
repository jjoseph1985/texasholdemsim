// table.cpp

#include "table.h"

Table::Table(double m, int num, double sbAmnt): numPlayers(num), smallBlind(sbAmnt), bigBlind(sbAmnt * 2), numOfRoundsPlayed(0)
{
	Player player1(m,preFlopOdds, "player1");
	Player player2(m,preFlopOdds, "player2");
	Player player3(m,preFlopOdds, "player3");
	Player player4(m,preFlopOdds, "player4");
	Player player5(m,preFlopOdds, "player5");
	Player player6(m,preFlopOdds, "player6");
	Player player7(m,preFlopOdds, "player7");
	Player player8(m,preFlopOdds, "player8");
	Player player9(m,preFlopOdds, "player9");
	Player player10(m,preFlopOdds, "player10");
	tempList10Players.push_back(player1);
	tempList10Players.push_back(player2);
	tempList10Players.push_back(player3);
	tempList10Players.push_back(player4);
	tempList10Players.push_back(player5);
	tempList10Players.push_back(player6);
	tempList10Players.push_back(player7);
	tempList10Players.push_back(player8);
	tempList10Players.push_back(player9);
	tempList10Players.push_back(player10);
	
	vector<Player>::iterator iter = tempList10Players.begin();
    for(; iter!=tempList10Players.end(); iter++)
	{
		playerList.push_back(*iter);
	}
}

void Table::Init()
{
	InitPositions();
	NewRound();	
}

void Table::InitPositions()
{	
	//sets iter to beginning of vector
	iter = playerList.begin();
	int i = 0;
	
	//positions setup: 0->Dealer,1->small blinds,2->big blinds,3->early,4->middle,5->late
	
	//cases for each number of players
	switch(numPlayers)
	{
		//if 2 players, 1st player is dealer and small blind, 2nd player is Early
	    case 2:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i+=3;
			}
	        break;
	    
	    case 3:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i++;
			}
	        break;
	        
	    case 4:
		    for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i++;
			}
	        break;
	    
	    case 5:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i++;
			}
	        break;
	        
	    case 6:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i++;
			}
	        break;
	    
	    case 7:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i++;
			}
	        break;	        	        
	
	    case 8:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i++;
			}
	        break;
	    
	    case 9:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i++;
			}
			break;

		case 10:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i++;
			}
			break;

	} 
} // InitPositions()

void Table::OddsTable(int numPlayers)
{   
    string cardStr = "";
    string w;
    double weight = 0;

    /*
    ofstream outFile;
    outFile.open("temp.txt");
    */

    ifstream inFile;
    inFile.open("preflopodds.txt", ifstream::in);
    if(!inFile.good())
    {
        cout << "Error opening preflopodds.txt. Exiting Program...\n";
    }
    
    for(int i=0; i < 169; i++)
    {
        char temp[256];
            
        inFile.getline(temp, 256);
        string lineOfFile(temp);
        
        StringTokenizer strtok(lineOfFile, " ");
        
        cardStr = strtok.nextToken();
        
        // Pop off unwanted values
        for(int i=2; i < numPlayers; i++)
        {
            string tmp = strtok.nextToken();
            //cout << "Temp: " << tmp << "\n";
        }
        
        w = strtok.nextToken();
        weight = strtod(w.c_str(), NULL);
        
        AddToMap(cardStr, weight);
    }

/*
    // Print out the map
    map<string,double>::iterator iter;

    for( iter = preFlopOdds.begin(); iter != preFlopOdds.end(); iter++ )
        outFile << (*iter).first << " => " << (*iter).second << endl;
*/    

    inFile.close();
}

void Table::AddToMap(string cardStr, double weight)
{
    string theCard;
    
    string cardNum1;
    cardNum1 = cardStr[0];
    
    string cardNum2; 
    cardNum2 = cardStr[1];
        
    if( cardStr.length() == 2 )
	{
		theCard = cardNum1 + "h" + cardNum2 + "c";
		preFlopOdds[theCard] = weight;
	    
		theCard = cardNum1 + "h" + cardNum2 + "s";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "h" + cardNum2 + "d";
		preFlopOdds[theCard] = weight;
	    
		theCard = cardNum1 + "c" + cardNum2 + "h";
		preFlopOdds[theCard] = weight;
		
		theCard = cardNum1 + "c" + cardNum2 + "s";
		preFlopOdds[theCard] = weight;
		
		theCard = cardNum1 + "c" + cardNum2 + "d";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "s" + cardNum2 + "h";
		preFlopOdds[theCard] = weight;

		theCard = cardNum1 + "s" + cardNum2 + "c";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "s" + cardNum2 + "d";
		preFlopOdds[theCard] = weight;	
		
		theCard = cardNum1 + "d" + cardNum2 + "h";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "d" + cardNum2 + "c";
		preFlopOdds[theCard] = weight;	
		
		theCard = cardNum1 + "d" + cardNum2 + "s";
		preFlopOdds[theCard] = weight;	

	}
	else if(cardStr.length() == 3) // suited cards
	{ 
		theCard = cardNum1 + "h" + cardNum2 + "h";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "c" + cardNum2 + "c";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "s" + cardNum2 + "s";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "d" + cardNum2 + "d";
		preFlopOdds[theCard] = weight;			
	}       
} // preFlopOddsTable()

void Table::NewRound()
{
	int p = 0;

	//reset pot and flags
    pot = 0.0;
	limitRaise = false;
	highBet = bigBlind;

	//resets players variables, except money and position
	iter = playerList.begin();
	for(;iter != playerList.end();iter++)
	{		
		iter->Reset();
	}
	
	//recalculates preFlopOdds table based on new number of players
	OddsTable(numPlayers);
	
	//creates and shuffles deck
	deck1.ShuffleCard();

	//determines where the dealer is to move positions
	DetDealer();
	
	//moves position of dealer
	iter = playerList.begin() + (dealerPosition + 1);
	for(;iter != playerList.end();iter++)
	{
		iter->SetPos(p);
		p++;
	}
	iter = playerList.begin();
	for(;iter != (playerList.begin() + (dealerPosition + 1));iter++)
	{
		iter->SetPos(p);
		p++;
	}

	//update dealer
	DetDealer();
	
	//Init/Update the blind amounts based off of 1st round or random num of 2 out of (1-10)
	ChangeBlinds();

	//starts game
	NextAction();
}

void Table::DealCards(int type)
{
    int g = 1;

    switch(type)
    {
        case HOLECARDS:
            while(g < 3)
		    {
		        iter = playerList.begin() + (dealerPosition + 1);
                DealCardHelper();
			    g++;
		    }            
            break;
            
        case FLOP:
		    g = 1;
		    while(g < 4)
		    {
                DealCardHelper();
			    g++;
		    }            
            break;
            
        case TURN:
            DealCardHelper();
            break;
            
        case RIVER:
            DealCardHelper();
            break;                                
    }
} // DealCard

void Table::DealCardHelper()
{
    for(;iter != playerList.end();iter++)
    {
	    card c = deck1.deck.back();
	    iter->AddCard(c,FLOP);
    }
    for(iter = playerList.begin(); iter != playerList.begin() + (dealerPosition + 1);iter++)
    {
	    card c = deck1.deck.back();
	    iter->AddCard(c,FLOP);
    }
    deck1.deck.pop_back();    
}

void Table::NextAction()
{     
	//deal holecards, start actions based on holecards only
	DealCards(HOLECARDS);
	Eligible();
	iter = playerList.begin() + (dealerPosition + 1);
	for(;iter != playerList.end();iter++)
	{	
		if(iter->DidFold())
			continue; //skip them, they don't get an action			
		else
		{
			pot += iter->Action(limitRaise, highBet);
			GetHighBet(); //determines the highest bet to pass to the next player
		}
	}
	iter = playerList.begin();
	for(;iter != playerList.begin() + (dealerPosition +1);iter++)
	{		
		if(iter->DidFold())
			continue; //skip them, they don't get an action			
		else
		{
			pot += iter->Action(limitRaise, highBet);
			GetHighBet();
		}
	}
	
	//deal flop and than whoever is left continues to make actions
	DealCards(FLOP);
	Eligible();
	iter = playerList.begin() + (dealerPosition + 1);
	for(;iter != playerList.end();iter++)
	{	
		if(iter->DidFold())
			continue; //skip them, they don't get an action			
		else
		{
			pot += iter->Action(limitRaise, highBet);
			GetHighBet();
		}
	}
	iter = playerList.begin();
	for(;iter != playerList.begin() + (dealerPosition +1);iter++)
	{		
		if(iter->DidFold())
			continue; //skip them, they don't get an action			
		else
		{
			pot += iter->Action(limitRaise, highBet);
			GetHighBet();
		}
	}
	
	//deal turn and then whoever is left continues
	DealCards(TURN);
	Eligible();
	iter = playerList.begin() + (dealerPosition + 1);
	for(;iter != playerList.end();iter++)
	{	
		if(iter->DidFold())
			continue; //skip them, they don't get an action			
		else
		{
			pot += iter->Action(limitRaise, highBet);
			GetHighBet();
		}
	}
	iter = playerList.begin();
	for(;iter != playerList.begin() + (dealerPosition +1);iter++)
	{		
		if(iter->DidFold())
			continue; //skip them, they don't get an action			
		else
		{
			pot += iter->Action(limitRaise, highBet);
			GetHighBet();
		}
	}

	//deal river and whoever is left continues
	DealCards(RIVER);
	Eligible();
	iter = playerList.begin() + (dealerPosition + 1);
	for(;iter != playerList.end();iter++)
	{	
		if(iter->DidFold())
			continue; //skip them, they don't get an action			
		else
		{
			pot += iter->Action(limitRaise, highBet);
			GetHighBet();
		}
	}
	iter = playerList.begin();
	for(;iter != playerList.begin() + (dealerPosition +1);iter++)
	{		
		if(iter->DidFold())
			continue; //skip them, they don't get an action			
		else
		{
			pot += iter->Action(limitRaise, highBet);
			GetHighBet();
		}
	}
	
	//searches each players hand and determines the best hand of all players
	iter = playerList.begin();
	hand bestHand;
	for(;iter != playerList.end();iter++)
	{	
		hand hand1 = iter->ShowHand();
		if(hand1.beats(bestHand))
		{
			bestHand = hand1;
			winner = iter->GetPos();
		}
	}
	
	//searches for playerwho was at the winner position and sends it to DeclareWinner
	iter = playerList.begin();
	int loc = 0;
	for(;iter != playerList.end();iter++)
	{	
		int playPos = iter->GetPos();
		if(winner == playPos)
			DeclareWinner(loc);
		loc++;
	}
} 

void Table::DetDealer()
{
	//determines current position of dealer so we can move positions of all players
	iter = playerList.begin();
	int i = 0;
	for(;iter != playerList.end();iter++)
	{		
		int currPos = iter->GetPos();
		if (currPos == 0)
		{
		    dealerPosition = i;
		}
		i++;
	}
} // DetDealer()

void Table::DeclareWinner(int winner) 
{  
	//set iter to element containing the winner
	iter = playerList.begin() + winner;

	//gives the winner the money in the pot
	iter->AddMoney(pot);
	
	//determines if the game is over
	Eligible();
	if(playerList.size() == 1)
	{
		EndGame(); //ends the game if there is only one elegible player left
	}
	else
		NewRound(); //starts the next round
	
}

void Table::Eligible()
{
	iter = playerList.begin() + (dealerPosition + 1);
	for(;iter != playerList.end();iter++)
	{		
		if(iter->DidBust())
			playerList.erase(iter); //if they are busted erase them from the list of players (they can't play again this game)
		else if(iter->DidAllIn())
			limitRaise = true; //if someone goes all in, players can't raise
	}
	iter = playerList.begin();
	for(;iter != playerList.begin() + (dealerPosition +1);iter++)
	{		
		if(iter->DidBust())
			playerList.erase(iter);
		else if(iter->DidAllIn())
			limitRaise = true;
	}
}

void Table::ChangeBlinds()
{
	numOfRoundsPlayed++;

	int randNum = (rand()%10)+1;

	if(randNum==2)
	{
		if(smallBlind >= 200)
		{
			randNum = 0;
		}else
		{
			smallBlind *= 2;
			bigBlind *= 2;
		}
	}

	if(numOfRoundsPlayed==1 || randNum==2)
	{
		vector<Player>::iterator iter = playerList.begin();
		for(; iter!=playerList.end(); iter++)
		{
			iter->SetSB(smallBlind);
			iter->SetBB(bigBlind);
		}
	}
}

void Table::EndGame()
{
	vector<Player>::iterator iter;
	iter = playerList.begin(); //sets iter to that winning player
	cout << "Game Over!\n\n";
	cout << iter->GetName() << " is the winner!\n";
}

void Table::GetHighBet()
{
	vector<Player>::iterator iter;
	iter = playerList.begin() + (dealerPosition + 1);
	for(;iter != playerList.end(); iter++)
	{	
		double currBet = iter->GetBet();
		if(currBet > highBet)
			highBet = currBet;
	}
	iter = playerList.begin();
	for(;iter != playerList.begin() + (dealerPosition +1);iter++)
	{		
		double currBet = iter->GetBet();
		if(currBet > highBet)
			highBet = currBet;
	}
}

