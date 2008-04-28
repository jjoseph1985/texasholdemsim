// table.cpp

#include "table.h"

Table::Table(double m, int num, double sbAmnt):
 numPlayers(num), smallBlind(sbAmnt),bigBlind(sbAmnt * 2), numOfRoundsPlayed(0),
 limitRaise1(false), limitRaise2(false), numRaises(0), highBet(0), pot(0), winner(0)
{
	Player player0(m,preFlopOdds, "player0");
	Player player1(m,preFlopOdds, "player1");
	Player player2(m,preFlopOdds, "player2");
	Player player3(m,preFlopOdds, "player3");
	Player player4(m,preFlopOdds, "player4");
	Player player5(m,preFlopOdds, "player5");
	Player player6(m,preFlopOdds, "player6");
	Player player7(m,preFlopOdds, "player7");
	Player player8(m,preFlopOdds, "player8");
	Player player9(m,preFlopOdds, "player9");

    tempList10Players.push_back(player0);
	tempList10Players.push_back(player1);
	tempList10Players.push_back(player2);
	tempList10Players.push_back(player3);
	tempList10Players.push_back(player4);
	tempList10Players.push_back(player5);
	tempList10Players.push_back(player6);
	tempList10Players.push_back(player7);
	tempList10Players.push_back(player8);
	tempList10Players.push_back(player9);
	
	vector<Player>::iterator it = tempList10Players.begin();
    
    for(int i=0; i!=numPlayers; i++, it++) //it!=tempList10Players.end(); it++)
	{
		playerList.push_back(*it);
	}
	
}

void Table::Init()
{
    cout << "Initializing table.";
	InitPositions();
	NewRound();	
}

void Table::InitPositions()
{	
    // This always works because dealer is always 0 when 
    // starting the game.
    
    cout << "Initializing positions.\n";    

    iter = playerList.begin();
    iter->SetJob(DEALER);
    cout << iter->GetName() << " is now the DEALER.\n";
    
    iter++;
    iter->SetJob(SMALLBLIND);
    cout << iter->GetName() << " is now the SMALLBLIND.\n";
    
    if(numPlayers > 2)
    {
        iter++;
        iter->SetJob(BIGBLIND);
        cout << iter->GetName() << " is now the BIGBLIND.\n";
    }
} // InitPositions()

void Table::ChangePositions()
{
    cout << "Updating remaining players jobs.\n";
    FindJob(DEALER);
    
    int maxJobs = 3;    //if more than 2 players there are 3 jobs (Dealer, SB, BB)
    if(numPlayers == 2) //if 2 players (Dealer, SB)
    {
        cout << "Only 2 jobs. DEALER and SB.\n";
        maxJobs = 2;
        
    }
    
    for(int k=0; k!=maxJobs; k++)   //loop through number of jobs (2,3)
    {
		iter++;
        if(iter==playerList.end() )  //loop back to beginning if reached end
            iter = playerList.begin();
       
		iter->SetJob(k);   //set job based off of enum jobs
        cout << iter->GetName() << " is now the " << k << ". (DEALER=0 SB=1 BB=2)\n";

    }
}

void Table::OddsTable()
{   
    string cardStr = "";
    string w;
    double weight = 0;

    
    //ofstream outFile;
    //outFile.open("temp.txt");
    

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
		theCard = cardNum1 + "H" + cardNum2 + "C";
		preFlopOdds[theCard] = weight;
	    
		theCard = cardNum1 + "H" + cardNum2 + "S";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "H" + cardNum2 + "D";
		preFlopOdds[theCard] = weight;
	    
		theCard = cardNum1 + "C" + cardNum2 + "H";
		preFlopOdds[theCard] = weight;
		
		theCard = cardNum1 + "C" + cardNum2 + "S";
		preFlopOdds[theCard] = weight;
		
		theCard = cardNum1 + "C" + cardNum2 + "D";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "S" + cardNum2 + "H";
		preFlopOdds[theCard] = weight;

		theCard = cardNum1 + "S" + cardNum2 + "C";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "S" + cardNum2 + "D";
		preFlopOdds[theCard] = weight;	
		
		theCard = cardNum1 + "D" + cardNum2 + "H";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "D" + cardNum2 + "C";
		preFlopOdds[theCard] = weight;	
		
		theCard = cardNum1 + "D" + cardNum2 + "S";
		preFlopOdds[theCard] = weight;	

	}
	else if(cardStr.length() == 3) // suited cards
	{ 
		theCard = cardNum1 + "H" + cardNum2 + "H";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "C" + cardNum2 + "C";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "S" + cardNum2 + "S";
		preFlopOdds[theCard] = weight;	

		theCard = cardNum1 + "D" + cardNum2 + "D";
		preFlopOdds[theCard] = weight;			
	}       
} // preFlopOddsTable()

void Table::NewRound()
{
    cout << "Beginning a new round.\n";
    
	int p = 0;
	OddsTable();
    UpdatePlayerOddsTable();

	//reset pot and flags
    pot = 0.0;
	limitRaise1 = false;

	//resets players variables, except money and position
	for(iter = playerList.begin(); iter != playerList.end();iter++)
	{
	    cout << iter->GetName() << "'s flags have been reset.\n";
		iter->Reset();
	}
	
	//recalculates preFlopOdds table based on new number of players
	OddsTable();
	
	//creates and shuffles deck
	deck1.ShuffleCard();
	
	//Init/Update the blind amounts based off of 1st round or random num of 2 out of (1-10)
	ChangeBlinds();

	//starts game
	NextAction();
	
	DetermineWinner();
}

void Table::DealCards(int type)
{
    FindJob(SMALLBLIND);
 
    vector<Player>::iterator sorter;
 
    switch(type)
    {	        
        case HOLECARDS:
            for(int i = 1; i < 3; i++)
                DealCardHelper(HOLECARDS);
            
            // Put hole cards in order low-high so can find them in map
            for(sorter=playerList.begin(); sorter!=playerList.end(); sorter++)
            {
                sorter->SortHoleCards();
            }
            cout << "Dealt HOLECARDS.\n";            
            break;
            
        case FLOP:
		    for(int i = 1; i < 4; i++)
                DealCardHelper(FLOP);
                
            cout << "Dealt FLOP.\n";
            break;
            
        case TURN:
            DealCardHelper(TURN);
            cout << "Dealt TURN.\n";
            break;
            
        case RIVER:
            DealCardHelper(RIVER);
			for(iter=playerList.begin(); iter!=playerList.end(); iter++)
			{
				iter->MakeHand();
			}
            cout << "Dealt RIVER.\n";            
            break;                                
    }

	
} // DealCard

void Table::DealCardHelper(int type)
{   
	card c = deck1.deck.back();
	deck1.deck.pop_back(); 

    for(int k=0; k!=numPlayers; k++, iter++)
    {   
        if(iter == playerList.end())
            iter = playerList.begin();
	    
		iter->AddCard(c,type);
		if(type == HOLECARDS)
		{	//if it's the whole cards being dealt keep getting a new one
			c = deck1.deck.back();
			deck1.deck.pop_back();
		}
    }
}

void Table::NextAction()
{     
	//deal holecards, start actions based on holecards only
	DealCards(HOLECARDS);
	
	Eligible();
	
	NextActionHelper(highBet, true);
	
	//deal flop and than whoever is left continues to make actions
	DealCards(FLOP);
	
	Eligible();
	NextActionHelper(highBet, false);
	
	//deal turn and then whoever is left contfinues
	DealCards(TURN);
	Eligible();
	NextActionHelper(highBet, false);

	//deal river and whoever is left continues
	DealCards(RIVER);
	Eligible();
	NextActionHelper(highBet, false);
} 

void Table::NextActionHelper(double theHighBet, bool thisIsHole)
{   

    // Get SmallBlind == the first person to "bet" (even if it is forced)
    FindJob(SMALLBLIND);
    
    bool isFirstIter = true;
    
    for(int k=1; k!=-1; k++, iter++)   //loop through number of jobs (2,3)
    {
        if(iter == playerList.end())
			iter = playerList.begin();
		
		GetHighBet();

        if(isFirstIter == false && CheckAllBets(highBet) == true)
        {
            break;
        }
        
        if(k == numPlayers)
            isFirstIter = false;
            
		if(iter->DidFold())
		{
		    cout << iter->GetName() << " has already folded, and is sitting out this round.\n";
			continue; //skip them, they don't get an action			
		}
		else
		{
		    
			double addToPot = iter->Action((limitRaise1 || limitRaise2), highBet, thisIsHole, isFirstIter, numPlayers);
			pot += addToPot;
			if(iter->DidRaised())
			{
				numRaises++;
			    iter->ResetRaised();	
			}
			if(numRaises == 2)
				limitRaise2 = true;
		}
	}

	//reset all player bet amounts
	highBet = 0.0;
	for(iter=playerList.begin(); iter!=playerList.end(); iter++)
	{
		iter->ResetMyBet();
	}

	//print out the pot
	cout << "POT: " << pot << "\n";

	numRaises = 0;
	limitRaise2 = false;
} //NextActionHelper

bool Table::CheckAllBets(double theHighBet)
{  
	vector<Player>::iterator iter; 
	
	for(iter = playerList.begin(); iter!=playerList.end(); iter++)
	{
		if(iter->GetBet() != theHighBet && iter->DidFold() == false && iter->GetMoney() > 0)
		{
		    cout << iter->GetName() << " has not bet enough money yet.\n";
			return false;
		}
	}
	
	cout << "Betting for round is over.\n";
	return true;
}//CheckAllBets

void Table::DetermineWinner() 
{  
	//searches each players hand and determines the best hand of all players
	hand bestHand;
	hand curHand;
	int howManyWinners=0;
    
	//finds the players' highest hand and how many ppl had that same hand (for ties)
	for(iter = playerList.begin(); iter != playerList.end();iter++)
	{	
		if(iter->DidFold() || iter->DidBust())	//if they fold or bust, they can't win
			continue;

		curHand = iter->GetHand();
		if(curHand > bestHand)
		{
			bestHand = curHand;
			howManyWinners = 1;
		}else if(curHand == bestHand)
		{
			howManyWinners++;
		}
		cout << iter->GetName() << "'s hand: " << curHand << "\n";
	}
	
	cout << "Best hand was: " << bestHand << "\n";
	double winnings = pot / howManyWinners;	//divide pot to multiple players

	//loops through players to award winnings (mainly for ties)
	for(iter = playerList.begin(); iter != playerList.end();iter++)
	{	
		if(iter->DidFold() || iter->DidBust())	//if they fold or bust, they can't win
			continue;
		
		curHand = iter->GetHand();
		if(curHand == bestHand)
		{
			iter->AddMoney(winnings);
			cout << iter->GetName() << " won " << winnings << "\n";
		}
	}

	//checks to see if any players have busted and sets their busted flag
	vector<Player>::iterator bustedI = playerList.begin();
	for(int k=0; k!=numPlayers; k++,bustedI++)
	{
		if(bustedI->GetMoney() <= 0)
		{
			bustedI->SetBusted();
			cout << bustedI->GetName() << " has BUSTED.\n";
		}
	}

	//determines if the game is over
	Eligible();
	if(playerList.size() == 1)
	{
		EndGame(); //ends the game if there is only one elegible player left
	}
	else
	{
		ChangePositions();
		NewRound(); //starts the next round
	}
}//DetermineWinner

void Table::Eligible()
{

	for(iter=playerList.begin(); iter!=playerList.end();)
	{		
		if(iter->DidBust())
		{
			cout << iter->GetName() << " has been REMOVED from the game.\n";
			playerList.erase(iter); //if they are busted erase them from the list of players (they can't play again this game)
			iter=playerList.begin();
			numPlayers--;
		}
		else if(iter->DidAllIn())
		{
			if(!limitRaise1)	//don't print out twice please
				cout << "Raising has been disabled. LimitRaise1 is enabled.\n";
			limitRaise1 = true; //if someone goes all in, players can't raise 
			iter++;
			
		}
		else
		{
			iter++;
		}
	}
}

void Table::ChangeBlinds()
{
	numOfRoundsPlayed++;
	cout << numOfRoundsPlayed << " rounds have been played.\n";

	int randNum = (rand()%10)+1;

	if(randNum==2)
	{
		if(smallBlind >= 200)
		{
			randNum = 0;
            cout << "Can't raise blinds. Table limit reached.\n";
		}else
		{
			smallBlind *= 2;
			bigBlind *= 2;
            cout << "Raising small blind to " << smallBlind;			
		}
	}

	if(numOfRoundsPlayed==1 || randNum==2)
	{
		vector<Player>::iterator iter = playerList.begin();
		for(; iter!=playerList.end(); iter++)
		{
			iter->SetSB(smallBlind);
			iter->SetBB(bigBlind);
			cout << iter->GetName() << "'s blinds have been updated.\n";
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
	
	double currBet = 0.0;
	for(iter = playerList.begin(); iter != playerList.end(); iter++)
	{	
		currBet = iter->GetBet();
		if(currBet > highBet)
		{
		    highBet = currBet;
		}
	}
	cout << "High bet " << highBet << "\n";
}

void Table::FindJob(int desiredJob)
{
    for(iter=playerList.begin(); iter!=playerList.end(); iter++)
    {
        if((iter)->GetJob() == desiredJob)
        {
            break;
        }
    } 

	//if the dealer bust we have no way of finding his position
	//for the ChangePositions() function, therefor we are just going
	//to do this so that the dealer will change to player1, keeping track
	//will be waaaay too messy
	if(desiredJob == DEALER)
	{
		iter=playerList.begin();
	}
      
}
