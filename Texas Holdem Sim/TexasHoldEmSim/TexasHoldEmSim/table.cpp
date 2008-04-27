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
	InitPositions();
	NewRound();	
}

void Table::InitPositions()
{	
    // This always works because dealer is always 0 when 
    // starting the game.

    iter = playerList.begin();
    iter->SetJob(DEALER);
    
    iter++;
    iter->SetJob(SMALLBLIND);
    
    if(numPlayers > 2)
    {
        iter++;
        iter->SetJob(BIGBLIND);
    }
} // InitPositions()

void Table::ChangePositions()
{
    
    FindJob(DEALER);
    
    int maxJobs = 3;    //if more than 2 players there are 3 jobs (Dealer, SB, BB)
    if(numPlayers == 2) //if 2 players (Dealer, SB)
        maxJobs = 2;
    
    for(int k=1; k!=maxJobs; k++, iter++)   //loop through number of jobs (2,3)
    {
        if(iter==playerList.end() )  //loop back to beginning if reached end
            iter = playerList.begin();
        if(numPlayers == 2)
        {
            iter->SetJob(k);   //set job based off of enum jobs
        }
    }
}

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
	limitRaise1 = false;

	//resets players variables, except money and position
	for(iter = playerList.begin(); iter != playerList.end();iter++)
	{		
		iter->Reset();
	}
	
	//recalculates preFlopOdds table based on new number of players
	OddsTable(numPlayers);
	
	//creates and shuffles deck
	deck1.ShuffleCard();
	
	//Init/Update the blind amounts based off of 1st round or random num of 2 out of (1-10)
	ChangeBlinds();

	//starts game
	NextAction();
	
	ChangePositions();
}

void Table::DealCards(int type)
{
    FindJob(SMALLBLIND);
    switch(type)
    {	        
        case HOLECARDS:
            for(int i = 1; i < 3; i++)
                DealCardHelper(HOLECARDS);       
            break;
            
        case FLOP:
		    for(int i = 1; i < 4; i++)
                DealCardHelper(FLOP);
            break;
            
        case TURN:
            DealCardHelper(TURN);
            break;
            
        case RIVER:
            DealCardHelper(RIVER);
            break;                                
    }
} // DealCard

void Table::DealCardHelper(int type)
{   
    for(int k=0; k!=numPlayers; k++, iter++)
    {   
        if(iter == playerList.end())
            iter = playerList.begin();
	    
	    card c = deck1.deck.back();
	    iter->AddCard(c,type);
	    deck1.deck.pop_back();  
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
	
	//deal turn and then whoever is left continues
	DealCards(TURN);
	Eligible();
	NextActionHelper(highBet, false);

	//deal river and whoever is left continues
	DealCards(RIVER);
	Eligible();
	NextActionHelper(highBet, false);
	
	//searches each players hand and determines the best hand of all players
	
	hand bestHand;
    vector<Player>::iterator currentWinner;
    currentWinner = playerList.begin();
    
	for(iter = playerList.begin(); iter != playerList.end();iter++)
	{	
		hand hand1 = iter->ShowHand();
		if(hand1.beats(bestHand))
		{
			bestHand = hand1;
			currentWinner = iter;
		}
	}
	
	iter=currentWinner;
	
	DeclareWinner();
} 

void Table::NextActionHelper(double theHighBet, bool isHole)
{   

    // Get SmallBlind == the first person to "bet" (even if it is forced)
    FindJob(SMALLBLIND);
    
    bool isFirstIter = true;
    
    for(int k=1; k!=10000; k++, iter++)   //loop through number of jobs (2,3)
    {
        if(iter == playerList.end())
			iter = playerList.begin();
			
        if(isFirstIter == false && CheckAllBets(theHighBet) == true)
        {
            break;
        }
        
        if(k == numPlayers)
            isFirstIter = false;
            
		if(iter->DidFold())
		{
			continue; //skip them, they don't get an action			
		}
		else
		{
		    GetHighBet();
		    
			double addToPot = iter->Action((limitRaise1 || limitRaise2), highBet, isHole, isFirstIter);
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

	numRaises = 0;
	limitRaise2 = false;
} //NextActionHelper

bool Table::CheckAllBets(double theHighBet)
{
    bool rval = false;    
    
	vector<Player>::iterator iter; 
	for(iter = playerList.begin(); iter!=playerList.end(); iter++)
	{
		if(iter->GetBet() != theHighBet)
			rval =  false;
		else
			rval = true;
	}
	
	return rval;
	
}//CheckAllBets

void Table::DeclareWinner() 
{  
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
    FindJob(SMALLBLIND);

	for(int k=0; k!=numPlayers; k++, iter++)
	{		
	    if(iter==playerList.end())
		    iter=playerList.begin();
		if(iter->DidBust())
		{
			playerList.erase(iter); //if they are busted erase them from the list of players (they can't play again this game)
			numPlayers--;
		}
		else if(iter->DidAllIn())
			limitRaise1 = true; //if someone goes all in, players can't raise 
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
	double currBet = 0.0;
	for(iter = playerList.begin(); iter != playerList.end(); iter++)
	{	
		currBet = iter->GetBet();
		if(currBet > highBet)
		    highBet = currBet;
	}
	
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
      
}
