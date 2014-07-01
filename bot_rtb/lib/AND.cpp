#include "AND.h"

AND::AND(SetRange* varSet1, SetRange* varSet2) : Rule()
{
    this->varSet1 = varSet1;
    this->varSet2 = varSet2;
}

double AND::GetDOM()
{
    double v1 = varSet1->GetDOM();
    double v2 = varSet2->GetDOM();

    std::cout << "Regla AND, valor izq: " << v1 << " valor der: " << v2 << std::endl;

    if (v1 < v2)
        return v1;

    return v2;
}

void AND::ClearDOMofSets()
{
    varSet1->ClearDOM();
    varSet2->ClearDOM();
}
