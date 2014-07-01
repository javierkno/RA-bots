#include "Variable.h"
#include "LeftRange.h"
#include "RightRange.h"
#include "TriangleRange.h"


Variable::~Variable()
{
    for (SetsRangesMap::iterator itr = m_sets.begin(); itr != m_sets.end(); ++itr)
        delete itr->second;
}

SetRange* Variable::SetLeftRange(const std::string& set_name, double minBound, double pick, double maxBound)
{
    m_sets[set_name] = new LeftRange(pick - minBound, pick, maxBound - pick);
    AdjustRange(minBound,maxBound);
    return m_sets[set_name];
}

SetRange* Variable::SetTriangleRange(const std::string& set_name, double minBound, double pick, double maxBound)
{
    m_sets[set_name] = new TriangleRange(pick - minBound, pick, maxBound - pick);
    AdjustRange(minBound,maxBound);
    return m_sets[set_name];
}

SetRange* Variable::SetRightRange(const std::string& set_name, double minBound, double pick, double maxBound)
{
    m_sets[set_name] = new RightRange(pick - minBound, pick, maxBound - pick);
    AdjustRange(minBound,maxBound);
    return m_sets[set_name];
}


void Variable::AdjustRange(double minBound, double maxBound)
{
  if (minBound < m_dMinRange) m_dMinRange = minBound;
  if (maxBound > m_dMaxRange) m_dMaxRange = maxBound;
}


void Variable::Fuzzify(double val)
{
    if (val >= m_dMinRange && val <= m_dMaxRange)
    {
        for (SetsRangesMap::const_iterator _set = m_sets.begin(); _set != m_sets.end(); ++_set)
        {
            std::cout << "--> Set __ " << _set->first << " __"<< std::endl;
            _set->second->SetDOM( _set->second->CalculateDOM(val) );
            std::cout << "  with DOM: " << _set->second->GetDOM() << std::endl << std::endl;
        }
    }
    else
        std::cout << "Valor fuera de rango: " << val << std::endl;
}

// OUTPUT = sum (maxima * DOM) / sum (DOMs)

double Variable::DeFuzzifyMax()
{
  double bottom = 0.0;
  double top    = 0.0;

  std::cout << std::endl;
  std::cout << "Defuzzificacion: " << std::endl;

  for (SetsRangesMap::iterator _set = m_sets.begin(); _set != m_sets.end(); ++_set)
  {
    std::cout << _set->first << ": " << _set->second->GetDOM() << " _ repr. value -> " << _set->second->GetPickValues() << std::endl;

    bottom += _set->second->GetDOM();
    top += _set->second->GetPickValues() * _set->second->GetDOM();
  }

  if (bottom == 0.0) return 0.0;

  return top / bottom;
}












