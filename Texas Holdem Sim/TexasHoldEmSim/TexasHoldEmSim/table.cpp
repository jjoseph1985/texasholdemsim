// table.cpp

#include "table.h"

Table::Table(): 
{

}

void Table::Init()
{
	numPlayers = playerList.Size();

}

//needs to be rewritten, doesn't actually assign position
enum posType Table::setPos( numPlayers )
{
    enum posType position;

    if( numPlayers == 9 )
    {
        if( posAtTable == 1 || posAtTable == 2 )
            position = EARLY;
        else if( posAtTable == 3 || posAtTable == 4 || posAtTable == 5 )
            position = MIDDLE;
        else if( posAtTable == 6 || posAtTable == 7 )
            position = LATE;
        else if( posAtTable == 8 || posAtTable == 9 )
            position = BLINDS;
    }
    else if( numPlayers == 8 )
    {
        if( posAtTable == 1 || posAtTable == 2 )
            position = EARLY;
        else if( posAtTable == 3 || posAtTable == 4 )
            position = MIDDLE;
        else if( posAtTable == 5 || posAtTable == 6 )
            position = LATE;
        else if( posAtTable == 7 || posAtTable == 8 )
            position = BLINDS;
    }
    else if( numPlayers == 7 )
    {
        if( posAtTable == 1 || posAtTable == 2 )
            position = EARLY;
        else if( posAtTable == 3 || posAtTable == 4 )
            position = MIDDLE;
        else if( posAtTable == 5 )
            position = LATE;
        else if( posAtTable == 6 || posAtTable == 7 )
            position = BLINDS;
    }
    else if( numPlayers == 6 )
    {
        if( posAtTable == 1 )
            position = EARLY;
        else if( posAtTable == 2 || posAtTable == 3 )
            position = MIDDLE;
        else if( posAtTable == 4 )
            position = LATE;
        else if( posAtTable == 5 || posAtTable == 6 )
            position = BLINDS;
    }
    else if( numPlayers == 5 )
    {
        if( posAtTable == 1 )
            position = EARLY;
        else if( posAtTable == 2 )
            position = MIDDLE;
        
        if( posAtTable == 3 )
            position = LATE;
        if( posAtTable == 4 || posAtTable == 5 )
            position = BLINDS;
    } 
    else if( numPlayers == 4 ) 
    {
        if( posAtTable == 1 )
            position = EARLY;
        else if( posAtTable == 2 )
            position = MIDDLE;
        if( posAtTable == 3 || posAtTable == 4 )
            position = BLINDS;
    } 
    else if( numPlayers == 3 )
    {
        if( posAtTable == 1 )
            position = EARLY;
        if( posAtTable == 2 || posAtTable == 3 )
            position = BLINDS;
    }
    else
    { // if( numPlayers == 2 )
        if( posAtTable == 1 )
            position = EARLY;
        if( posAtTable == 2 )
            position = BLINDS;
    }

  return position;
  
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
	deck1.ShuffleCard();
}

void Table::DealCard( enum round whatRound )
{
    card c;
    c.setVal( s[0], s[1] );
    table.push_back( c );
} // DealCard

void Table::NextAction()
{      
	bool flags = Table::Eligible(); 
	pot += playerx.Action(limitAction);
} 

void Table::DetDealer()
{
    int pos = playerx.GetPos();
	if (pos == 0)
		dealerPosition = pos;
} // DetDealer()

void Table::DeclareWinner(int winner) 
{  
	playerx.AddMoney(pot);
}

bool Table::Eligible()
{

}

void CheckTime()
{

}



