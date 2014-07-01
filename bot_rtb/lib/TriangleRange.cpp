#include "TriangleRange.h"

TriangleRange::TriangleRange(double leftPoint, double peak, double rightPoint) : SetRange(peak)
{
    m_peakValue = peak;
    m_leftPoint = leftPoint;
    m_rightPoint = rightPoint;
}

double TriangleRange::CalculateDOM(double val) const
{
    std::cout << " OffSet Values -> " << m_leftPoint << " " << m_peakValue << " " << m_rightPoint << std::endl;

    if (((m_rightPoint == 0.0) && (m_peakValue == val)) || ((m_leftPoint == 0.0) && (m_peakValue == val)))
    {
        return 1.0;
    }
    else if ( (val > m_peakValue) && (val < (m_peakValue + m_rightPoint)) )
    {
        double grad = 1.0 / -m_rightPoint;

        return grad * (val - m_peakValue) + 1.0;
    }
    else if ( (val >= (m_peakValue - m_leftPoint)) && (val <= m_peakValue) )
    {
        double grad = 1.0 / m_leftPoint;

        return grad * (val - (m_peakValue - m_leftPoint));
    }
    else
    {
        return 0.0;
    }
}
