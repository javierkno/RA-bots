#include "OR.h"

OR::OR(SetRange* varSet1, SetRange* varSet2) : Rule()
{
    this->varSet1 = varSet1;
    this->varSet2 = varSet2;
}

double OR::GetDOM()
{
    double v1 = varSet1->GetDOM();
    double v2 = varSet2->GetDOM();

    std::cout << "Regla OR, valor izq: " << v1 << " valor der: " << v2 << std::endl;

    if (v1 > v2)
        return v1;

    return v2;
}

void OR::ClearDOMofSets()
{
    varSet1->ClearDOM();
    varSet2->ClearDOM();
}
