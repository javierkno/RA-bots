#ifndef TRIANGLERANGE_H
#define TRIANGLERANGE_H

#include "SetRange.h"

class TriangleRange : public SetRange
{
    public:
                TriangleRange(double,double,double);

        // Calcula el valor de "membership" (DOM = degree of membershit), del valor pasado por parametro
        double  CalculateDOM(double)const;

    private:

        // Valores que sirven para determinar el DOM, en funcion del tipo de rango (triangle, left o right)
        double  m_peakValue;
        double  m_rightPoint;
        double  m_leftPoint;

};
#endif // TRIANGLERANGE_H
