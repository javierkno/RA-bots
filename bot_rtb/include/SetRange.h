#ifndef SETRANGE_H
#define SETRANGE_H
#include <iostream>

class SetRange
{
    public:
        // El constructor recibe por parametro un valor "pico" representativo en fucion del rango creado (triangle, left o right)
        //  Estos rangos en su constructor llamaran a SetRange pasandole un "pico" distinto
        // Si es un TriangleRange le pasará como parametro el valor "pico" de ese triangulo
        // En caso de ser un rango left o right, el valor "pico" será la mitad de la parte superior llana del rango

                        SetRange(double);

        virtual double  CalculateDOM(double val)const = 0;
        void            SetDOM(double val);
        void            ClearDOM();
        double          GetDOM(){return m_dom;};


        // Obtiene el mejor degree of membership (dom), es decir el más alto en ese momento.
        // Es llamada a la hora de defuzificar, al procesar las reglas...

        void            BestDOM(double val);


        double          GetPickValues(){return m_peakValue;};



    protected:
        double m_dom;

        // valor representativo para el momento de realizar el calculo de defuzificacion
        double m_peakValue;

};

#endif // SETRANGE_H
