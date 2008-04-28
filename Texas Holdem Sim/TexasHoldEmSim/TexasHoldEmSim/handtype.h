// handtype.h

#ifndef HANDTYPE_H
#define HANDTYPE_H

#include <iostream>
#include <vector>
#include <string>
#include <iostream>

#include "shared.h"

class handType
{
    public:
        handType();
        
        void setType( enum typeName tn, int a = 0, int b = 0, int c = 0, int d = 0, int e = 0 );
        enum typeName getType() {return label;};         
        bool beats( handType& );
        bool ties( handType& );
        void clear();

    private:
        enum typeName label;
        int kick1;
        int kick2;
        int kick3;
        int kick4;
        int kick5;
}; // handType

#endif