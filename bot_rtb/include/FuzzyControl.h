#ifndef FUZZYCONTROL_H
#define FUZZYCONTROL_H

#include<string>
#include<map>
#include<vector>

#include "Variable.h"
#include "Rule.h"
#include "AND.h"
#include "OR.h"

class FuzzyControl
{
    private:

        typedef std::map<std::string, Variable*>    VariablesMap;
        typedef std::vector<Rule*>                  RulesVector;


    public:
                    ~FuzzyControl();

        Variable&   AddVariable(const std::string&);
        void        AddRule(Rule*,SetRange*);
        void        Fuzzify(const std::string&,double val);
        double      Defuzzify(const std::string&);


    private:

        VariablesMap    m_variables;
        RulesVector     m_rules;


};

#endif // FUZZYCONTROL_H
