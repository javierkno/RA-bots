#include "FuzzyControl.h"

FuzzyControl::~FuzzyControl()
{

    for (VariablesMap::iterator itr = m_variables.begin(); itr != m_variables.end(); ++itr)
        delete itr->second;


    for (RulesVector::iterator itr1 = m_rules.begin(); itr1 != m_rules.end(); ++itr1)
        delete *itr1;
}

Variable& FuzzyControl::AddVariable(const std::string& name)
{
    m_variables[name] = new Variable();
    return *m_variables[name];
}

void FuzzyControl::AddRule(Rule* rule, SetRange* varSet)
{
    m_rules.push_back(new Rule(rule,varSet));
}

void FuzzyControl::Fuzzify(const std::string& nameVariable, double val)
{
    std::cout << "Variable name --- " << nameVariable << " --- " << val << " <-- " << std::endl;

    if (m_variables.find(nameVariable) != m_variables.end())
        m_variables[nameVariable]->Fuzzify(val);
}

double FuzzyControl::Defuzzify(const std::string& nameVariable)
{
    if (m_variables.find(nameVariable) != m_variables.end())
    {

        for (RulesVector::iterator rule = m_rules.begin(); rule != m_rules.end(); ++rule)
        {
            (*rule)->ClearDOMofConsequent();
        }

        for (RulesVector::iterator rule = m_rules.begin(); rule != m_rules.end(); ++rule)
        {
            (*rule)->ProcessRule();
        }

        return m_variables[nameVariable]->DeFuzzifyMax();
    }
    return 0.0;
}
