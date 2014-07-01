#include "Rule.h"

Rule::Rule(Rule* rule, SetRange* varSet)
{

    m_antecedent = rule;
    m_consequence = varSet;
}

void Rule::ProcessRule()
{
    m_consequence->BestDOM( m_antecedent->GetDOM() );
}

void Rule::ClearDOMofConsequent()
{
    m_consequence->ClearDOM();
}

double Rule::GetDOM()
{
    return 0;
}

