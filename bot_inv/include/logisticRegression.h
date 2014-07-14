#ifndef LOGISTICREGRESSION_H
#define	LOGISTICREGRESSION_H

#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <lbfgs.h>
#include <cstdio>

namespace ra
{

class LogisticRegression {

public:    
    
    typedef std::pair<double*,char> TDSample;    
    
    enum EMinAlgorithm {
        GRADIENT_DES,
        LBFGS
    } ;
    
    
    
public:
    
    explicit            LogisticRegression(unsigned dimension);
    explicit            LogisticRegression(unsigned dimension, bool debug);
                        ~LogisticRegression(){};
    
    inline void         updateTraining(double* data, char Y);
    inline void         releaseTraining();
    
    void                execute();
    inline bool         predictWith(double* X);
    
    
    double*             getTheta(){ return m_theta; }
    unsigned            getDim() { return m_dimensions; }
    
    std::vector<TDSample> getTraining() { return m_training; }
    
    double              sigmoid(double* X);
    
    inline void         setDim(unsigned dim);
  
    void                setMinAlgorithm(EMinAlgorithm t) { m_typeMinimize = t; }
    
    
    
private:
    
                        LogisticRegression(const LogisticRegression& orig){};
    
    inline void         setTraining(const TDSample& smpl);
    
    
    void                initTheta();
    
    void                doLBFGS();
    void                doGradientDes();
    
    
private:    
    
    std::vector<TDSample> m_training;
    
    unsigned    m_dimensions;
    double*     m_theta;
    bool        m_activeDebug;
    
    // LBFGS POR DEFECTO
    EMinAlgorithm m_typeMinimize;

};


inline void
LogisticRegression::setDim(unsigned dim) {
    m_dimensions = dim;
    //if (m_theta != NULL) delete[] m_theta;
    m_theta = new double[dim+1];
}

inline void
LogisticRegression::setTraining(const TDSample& smpl) {
    m_training.push_back(smpl);
}

///////////////////////////////////////////////////////////////////////////
/// Devuelve cierto si está clasificado con valores próximos a 1        
///////////////////////////////////////////////////////////////////////////
inline bool
LogisticRegression::predictWith(double* X) {
    double* x = new double[m_dimensions+1];
    double res = 0.0;
    
    x[0] = 1;
    for (int i=1; i<= m_dimensions; ++i)
        x[i] = X[i-1];
    
    res = sigmoid(x);
    
    return (res < 0.5);
}


inline void 
LogisticRegression::updateTraining(double* data, char Y) {
    
    TDSample s(data,Y);
    setTraining(s);
};

inline void
LogisticRegression::releaseTraining() {
    m_training.clear();
}
}
    
#endif

