// handtype.cpp

#include "handtype.h"

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

void handType::clear()
{
    label = BLANK;
    kick1 = 0;
    kick2 = 0;
    kick3 = 0;
    kick4 = 0;
    kick5 = 0;
} // clear()

bool operator> (handType& handType1, handType& handType2)   
{  
    if( handType1.label > handType2.label )
    {
        return true;
    } 
    else if( handType1.label == handType2.label )
    {
        if( handType1.kick1 > handType2.kick1 )
        {
            return true;
        }
        else if( handType1.kick1 == handType2.kick1 )
        {
            if( handType1.kick2 > handType2.kick2 )
            {
                return true;
            } 
            else if( handType1.kick2 == handType2.kick2 )
            {
                if( handType1.kick3 > handType2.kick3 )
                {
                    return true;
                }
                else if( handType1.kick3 == handType2.kick3 )
                {
                    if( handType1.kick4 > handType2.kick4 )
                    {
                        return true;
                    } 
                    else if( handType1.kick4 == handType2.kick4 )
                    {
                        if( handType1.kick5 > handType2.kick5 )
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
bool operator== (handType& handType1, handType& handType2)  
{ 
	bool rval = false;
    
    if( handType1.label == handType2.label && handType1.kick1 == handType2.kick1 && handType1.kick2 == handType2.kick2 
        && handType1.kick3 == handType2.kick3 && handType1.kick4 == handType2.kick4 && handType1.kick5 == handType2.kick5 )
    {
        rval = true;
    }
    
    return rval;
} 