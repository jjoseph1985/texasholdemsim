// table.cpp

#include "table.h"

Table::Table(double m, int num)
{
	numPlayers=num;
	Player player1(m,preFlopOdds);
	Player player2(m,preFlopOdds);
	Player player3(m,preFlopOdds);
	Player player4(m,preFlopOdds);
	Player player5(m,preFlopOdds);
	Player player6(m,preFlopOdds);
	Player player7(m,preFlopOdds);
	Player player8(m,preFlopOdds);
	Player player9(m,preFlopOdds);
	Player player10(m,preFlopOdds);
	playerList.push_back(player1);
	playerList.push_back(player2);
	playerList.push_back(player3);
	playerList.push_back(player4);
	playerList.push_back(player5);
	playerList.push_back(player6);
	playerList.push_back(player7);
	playerList.push_back(player8);
	playerList.push_back(player9);
	playerList.push_back(player10);
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
		//if 2 players, 1st player is dealer and small blind, 2 player is Early
	    case 2:
			for(;iter != playerList.end(); iter++)
			{			
				
				iter->SetPos(i);
				
				i+=2;
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
	ifstream file;
	file.open("odds.txt");
	string hole, tmp;
	double weight;
	string a, b;

	preFlopOdds.clear();

	for (int i = 0; i < 169; i++)
	{
		file >> hole;
		file >> weight;
		weight = weight / 31.5;

		a = hole[0];		
		b = hole[1];
		
		cout << "\nhole[0]: " << a << "\nhole[1]: " << b;

		if( hole.length() == 2 )
		{
			tmp = a + 'h' + b + 'c';
			preFlopOdds[tmp] = weight;
			cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'h' + b + 's';
			preFlopOdds[tmp] = weight;
			cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'h' + b + 'd';
			preFlopOdds[tmp] = weight;    
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'c' + b + 'h';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";			
			
			tmp = a + 'c' + b + 's';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";			
			
			tmp = a + 'c' + b + 'd';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 's' + b + 'h';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 's' + b + 'c';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 's' + b + 'd';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'd' + b + 'h';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'd' + b + 'c';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'd' + b + 's';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";
		}
		else
		{ // suited cards
			tmp = a + 'h' + b + 'h';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'c' + b + 'c';
			preFlopOdds[tmp] = weight;
			cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 's' + b + 's';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'd' + b + 'd';
			preFlopOdds[tmp] = weight;
            cout << "\npreFlopOdds[ " << tmp << "] = " << weight << "\n";			
		}
	}
	
	file.close();

} // preFlopOddsTable()

void Table::NewRound()
{
	int p = 0;

	//reset pot and flags
    pot = 0.0;
	limitAction = false;
	didAllIn = false;

	//recalculates preFlopOdds table based on new number of players
	OddsTable(numPlayers);
	
	//recreates and shuffles deck
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

	//starts game
	NextAction();
}

void Table::DealCards(int i )
{

} // DealCard

void Table::NextAction()
{      
	DealCards(HOLECARDS);
	bool flags = Eligible(); 
	//pot += playerx.Action(limitAction);
} 

void Table::DetDealer()
{
	//determines current position of dealer so we can move positions of all players
	iter = playerList.begin();
	for(;iter != playerList.end();iter++)
	{
		int i = 0;
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
	//playerx.AddMoney(pot);
}

bool Table::Eligible()
{
    return true;
}

void CheckTime()
{

}



