// handtype.cpp

#include "handtype.h"
#include "hand.h"

handType::handType(): label(BLANK), kick1(0),  kick2(0), kick3(0),  kick4(0),  kick5(0)
{

}

void handType::setType( enum typeName tn, int a, int b, int c, int d, int e )
{
    label = tn;
    kick1 = a;
    kick2 = b;
    kick3 = c;
    kick4 = d;
    kick5 = e;
}

bool handType::beats( handType& other )
{
    if( label > other.label )
    {
        return true;
    } 
    else if( label == other.label )
    {
        if( kick1 > other.kick1 )
        {
            return true;
        }
        else if( kick1 == other.kick1 )
        {
            if( kick2 > other.kick2 )
            {
                return true;
            } 
            else if( kick2 == other.kick2 )
            {
                if( kick3 > other.kick3 )
                {
                    return true;
                }
                else if( kick3 == other.kick3 )
                {
                    if( kick4 > other.kick4 )
                    {
                        return true;
                    } 
                    else if( kick4 == other.kick4 )
                    {
                        if( kick5 > other.kick5 )
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        } // kick5
                    } 
                    else
                    {
                        return false;
                    } // kick4 
                } 
                else
                {
                    return false;
                } // kick3 
            } 
            else
            {
                return false;
            } // kick2 
        } 
        else
        {
            return false;
        } // kick1 
    } 
    else
    {
        return false;
    } 
}

bool handType::ties( handType& other )
{
    bool rval = false;
    
    if( label == other.label && kick1 == other.kick1 && kick2 == other.kick2 
        && kick3 == other.kick3 && kick4 == other.kick4 && kick5 == other.kick5 )
    {
        rval = true;
    }
    
    return rval;
} // ties

void handType::clear()
{
    label = BLANK;
    kick1 = 0;
    kick2 = 0;
    kick3 = 0;
    kick4 = 0;
    kick5 = 0;
} // clear()

ostream& operator<< (ostream& output, hand &printHand) 
{ 
	vector<card>::iterator printer;
	for(printer=printHand.cards.begin(); printer!=printHand.cards.end(); ++printer)
	{
		output << *printer << " ";
	}

	handType& printType = printHand.getType();

	output << printType.getType();
	return output;
} 