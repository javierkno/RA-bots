#include "SetRange.h"

SetRange::SetRange(double repval)
{
    m_dom = 0.0;
    m_peakValue = repval;
}

void SetRange::SetDOM(double val)
{
    m_dom = val;
}

void SetRange::BestDOM(double val)
{
    if (val > m_dom)
        m_dom = val;
}

void SetRange::ClearDOM()
{
    m_dom=0.0;
}
