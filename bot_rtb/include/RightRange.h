#ifndef RIGHTRANGE_H
#define RIGHTRANGE_H

#include "SetRange.h"

class RightRange : public SetRange
{
    public:
                RightRange(double, double, double);

        // Valores que sirven para determinar el DOM, en funcion del tipo de rango (triangle, left o right)
        double  CalculateDOM(double)const;

    private:

        // Valores que sirven para determinar el DOM, en funcion del tipo de rango (triangle, left o right)
        double  m_peakValue;
        double  m_rightPoint;
        double  m_leftPoint;
};

#endif // RIGHTRANGE_H
