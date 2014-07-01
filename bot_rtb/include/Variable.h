#ifndef VARIABLE_H
#define VARIABLE_H

#include<map>
#include<string>
#include <iostream>

#include "SetRange.h"

class Variable
{
    private:
        typedef std::map<std::string,SetRange*> SetsRangesMap;

    public:
                        ~Variable();

        SetRange*       SetLeftRange(const std::string& set_name, double minBound, double pick, double maxBound);
        SetRange*       SetTriangleRange(const std::string& set_name, double minBound, double pick, double maxBound);
        SetRange*       SetRightRange(const std::string& set_name, double minBound, double pick, double maxBound);

        void            AdjustRange(double minBound, double maxBound);

        void            Fuzzify(double);

        double          DeFuzzifyMax(); // OUTPUT = sum (maxima * DOM) / sum (DOMs)


    private:

        SetsRangesMap   m_sets;

        double          m_dMinRange;
        double          m_dMaxRange;
};

#endif // VARIABLE_H
