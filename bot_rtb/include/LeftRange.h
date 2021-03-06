#ifndef LEFTRANGE_H
#define LEFTRANGE_H

#include "SetRange.h"

class LeftRange : public SetRange
{
    public:

                LeftRange(double, double, double);

        // Valores que sirven para determinar el DOM, en funcion del tipo de rango (triangle, left o right)
        double  CalculateDOM(double) const;

    private:

        // Valores que sirven para determinar el DOM, en funcion del tipo de rango (triangle, left o right)
        double  m_peakValue;
        double  m_rightPoint;
        double  m_leftPoint;
};

#endif // LEFTRANGE_H
