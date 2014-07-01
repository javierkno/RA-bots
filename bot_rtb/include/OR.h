#ifndef OR_H
#define OR_H

#include "Rule.h"


class OR : public Rule
{
    public:
                OR(SetRange* set1 ,SetRange* set2);
        double  GetDOM();
        void    ClearDOMofSets();

        SetRange* varSet1;
        SetRange* varSet2;

};

#endif // OR_H
