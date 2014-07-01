#ifndef RULE_H
#define RULE_H

#include "SetRange.h"

class Rule
{
    public:
                        Rule(){};
                        Rule(Rule*,SetRange*);

        void            ProcessRule();
        virtual void    ClearDOMofConsequent();

        virtual double  GetDOM();

        Rule*           m_antecedent;
        SetRange*       m_consequence;

};

#endif // RULE_H
