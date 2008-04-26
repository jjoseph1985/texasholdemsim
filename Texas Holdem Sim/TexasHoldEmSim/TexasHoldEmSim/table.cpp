// table.cpp

#include "table.h"

Table::Table(double m, int num)
{
	numPlayers=num;
	Player player1(m);
	Player player2(m);
	Player player3(m);
	Player player4(m);
	Player player5(m);
	Player player6(m);
	Player player7(m);
	Player player8(m);
	Player player9(m);
	Player player10(m);
	playerList.push_back(player1);
	playerList.push_back(player2);
	playerList.push_back(player3);
	playerList.push_back(player4);
	playerList.push_back(player5);
	playerList.push_back(player6);
	playerList.push_back(player7);
	playerList.push_back(player8);
	playerList.push_back(player9);
}

void Table::Init()
{
	InitPositions();
	NewRound();
	
}

void Table::InitPositions()
{
	//sets an iterator to traverse the playerList vector
	vector<Player>::iterator iter;
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

void Table::OddsTable()
{
	ifstream file;
	file.open("odds.txt");
	string hole, tmp;
	double weight;
	string a, b;

	odds.clear();

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
			odds[tmp] = weight;
			cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'h' + b + 's';
			odds[tmp] = weight;
			cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'h' + b + 'd';
			odds[tmp] = weight;    
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'c' + b + 'h';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";			
			
			tmp = a + 'c' + b + 's';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";			
			
			tmp = a + 'c' + b + 'd';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 's' + b + 'h';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 's' + b + 'c';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 's' + b + 'd';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'd' + b + 'h';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'd' + b + 'c';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'd' + b + 's';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
		}
		else
		{ // suited cards
			tmp = a + 'h' + b + 'h';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'c' + b + 'c';
			odds[tmp] = weight;
			cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 's' + b + 's';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'd' + b + 'd';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";			
		}
	}
	
	file.close();

} // OddsTable()

void Table::NewRound()
{
    pot = 0.0;
	limitAction = false;
	deck1.ShuffleCard();
}

void Table::DealCards( int whatRound )
{

} // DealCard

void Table::NextAction()
{      
	bool flags = Table::Eligible(); 
	//pot += playerx.Action(limitAction);
} 

void Table::DetDealer()
{
    int pos = 0; //= playerx.GetPos();
	if (pos == 0)
		dealerPosition = pos;
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



