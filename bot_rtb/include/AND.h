#ifndef AND_H
#define AND_H

#include "Rule.h"


class AND : public Rule
{
    public:

                AND(SetRange* set1 ,SetRange* set2);
        double  GetDOM();
        void    ClearDOMofSets();

        SetRange* varSet1;
        SetRange* varSet2;

    protected:
    private:
};

#endif // AND_H
