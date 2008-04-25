// table.cpp

#include "table.h"

Table::Table() 
{
	Player player1(25);
	Player player2(25);
	Player player3(25);
	Player player4(25);
	Player player5(25);
	Player player6(25);
	Player player7(25);
	Player player8(25);
	Player player9(25);
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
	numPlayers = playerList.size();
	SetPos(numPlayers);	
}

//needs to be rewritten, doesn't actually assign position
void Table::SetPos(int numPlayers)
{
	//vector<Player>iterator it;
	//it.begin();
	//if( numPlayers == 9 )
 //   {
	//	for(;it!= it.end();it++)
	//	{
	//		if(it==0)
	//			playerList[0].SetPos(0);
	//			
	//	}
	//	/* if( posAtTable == 1 || posAtTable == 2 )
 //           position = EARLY;
 //       else if( posAtTable == 3 || posAtTable == 4 || posAtTable == 5 )
 //           position = MIDDLE;
 //       else if( posAtTable == 6 || posAtTable == 7 )
 //           position = LATE;
 //       else if( posAtTable == 8 || posAtTable == 9 )
 //           position = BLINDS;*/
 //   }
    //else if( numPlayers == 8 )
    //{
    //    if( posAtTable == 1 || posAtTable == 2 )
    //        position = EARLY;
    //    else if( posAtTable == 3 || posAtTable == 4 )
    //        position = MIDDLE;
    //    else if( posAtTable == 5 || posAtTable == 6 )
    //        position = LATE;
    //    else if( posAtTable == 7 || posAtTable == 8 )
    //        position = BLINDS;
    //}
    //else if( numPlayers == 7 )
    //{
    //    if( posAtTable == 1 || posAtTable == 2 )
    //        position = EARLY;
    //    else if( posAtTable == 3 || posAtTable == 4 )
    //        position = MIDDLE;
    //    else if( posAtTable == 5 )
    //        position = LATE;
    //    else if( posAtTable == 6 || posAtTable == 7 )
    //        position = BLINDS;
    //}
    //else if( numPlayers == 6 )
    //{
    //    if( posAtTable == 1 )
    //        position = EARLY;
    //    else if( posAtTable == 2 || posAtTable == 3 )
    //        position = MIDDLE;
    //    else if( posAtTable == 4 )
    //        position = LATE;
    //    else if( posAtTable == 5 || posAtTable == 6 )
    //        position = BLINDS;
    //}
    //else if( numPlayers == 5 )
    //{
    //    if( posAtTable == 1 )
    //        position = EARLY;
    //    else if( posAtTable == 2 )
    //        position = MIDDLE;
    //    
    //    if( posAtTable == 3 )
    //        position = LATE;
    //    if( posAtTable == 4 || posAtTable == 5 )
    //        position = BLINDS;
    //} 
    //else if( numPlayers == 4 ) 
    //{
    //    if( posAtTable == 1 )
    //        position = EARLY;
    //    else if( posAtTable == 2 )
    //        position = MIDDLE;
    //    if( posAtTable == 3 || posAtTable == 4 )
    //        position = BLINDS;
    //} 
    //else if( numPlayers == 3 )
    //{
    //    if( posAtTable == 1 )
    //        position = EARLY;
    //    if( posAtTable == 2 || posAtTable == 3 )
    //        position = BLINDS;
    //}
    //else
    //{ // if( numPlayers == 2 )
    //    if( posAtTable == 1 )
    //        position = EARLY;
    //    if( posAtTable == 2 )
    //        position = BLINDS;
    //}

  //return position;
  
} // SetPos()

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
}

void Table::DealCard( int whatRound )
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



