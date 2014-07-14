#include "logisticRegression.h"

namespace ra
{

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////// PARA EL USO DE LA OPTIMIZACON LBFGS //////////////////////
//////////////////////////////////////////////////////////////////////////////

int dim=0;
int trainingSize=0;
int iter=0;
std::vector<LogisticRegression::TDSample> training;
std::vector<double> vecCost;

double
sigmoid(double* X, const lbfgsfloatval_t* theta) {

    double res = 0.0;
    double z = 0.0;
    
    // Producto (oT*x)
    for (int i=0; i<= dim; ++i) {
        z += theta[i] * X[i];
    }

    res = ( 1 / (1 + exp(-z) ));
    
    return res;
}

static lbfgsfloatval_t evaluate(
    void *instance,
    const lbfgsfloatval_t *x,
    lbfgsfloatval_t *g,
    const int n,
    const lbfgsfloatval_t step
    )
{
    lbfgsfloatval_t fx = 0.0;
    
    int Y=0;
    
    for (int i =0; i < trainingSize; ++i) {

        double* X = new double[ dim+1 ];

        X[0] = 1;
        for (int j=1; j<= dim; ++j)
            X[j] = training[i].first[j-1];

        Y = (training[i].second == '1' ? 1 : 0);

        double h = sigmoid(X,x);

        if (h == 0) h = 0.0001;
        else if (h == 1) h = 0.9999;

        fx += ( ( Y * log(h)) + ((1 - Y) * log(1 - h)) );

        for (int j=0; j<= dim; ++j)
            g[j] += ((h - Y) * X[j]);


        delete[] X;
    }

    fx = -1 * (fx / trainingSize) ;

    for (int i=0; i<= dim; ++i)
        g[i] = g[i] / trainingSize ;

    
    return fx;
}

static int progress(
    void *instance,
    const lbfgsfloatval_t *x,
    const lbfgsfloatval_t *g,
    const lbfgsfloatval_t fx,
    const lbfgsfloatval_t xnorm,
    const lbfgsfloatval_t gnorm,
    const lbfgsfloatval_t step,
    int n,
    int k,
    int ls
    )
{
    //printf("Iteration %d:\n", k);
    //printf("  fx = %f, x[0] = %f, x[1] = %f\n", fx, x[0], x[1]);
    //printf("  xnorm = %f, gnorm = %f, step = %f\n", xnorm, gnorm, step);
    //printf("\n");
    vecCost.push_back(fx);
    iter = k;
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


LogisticRegression::LogisticRegression(unsigned dimension)
        : m_dimensions(dimension), m_typeMinimize(LBFGS), m_activeDebug(false) {

    m_theta = new double[dimension+1];
};

LogisticRegression::LogisticRegression(unsigned dimension, bool debug)
        : m_dimensions(dimension), m_typeMinimize(LBFGS), m_activeDebug(debug) {

    m_theta = new double[dimension+1];
    
    //if (debug)  m_debugger = new Debugger(600,600);
};

double
LogisticRegression::sigmoid(double* X) {

    double res = 0.0;
    double z = 0.0;
    
    // Producto (oT*x)
    for (int i=0; i<= m_dimensions; ++i)
        z += m_theta[i] * X[i];
    
    res = ( 1 / (1 + exp(-z) ));
    
    return res;
}

void
LogisticRegression::initTheta() {
    for (int i=0; i<= m_dimensions; ++i)
        m_theta[i]=0;
}
/*
void
LogisticRegression::updateDebugger() {
    
    if (m_activeDebug) {
        double d[2];
        for (int i=0; i< iter; ++i) {
            d[0] = (double)i*20;
            d[1] = vecCost[i]*10000;
            
            m_debugger->PaintData2(d,0);
        }
        m_debugger->Show();
    }
    
    vecCost.clear();
    iter = 0;
}*/

void
LogisticRegression::execute() {
    
    switch (m_typeMinimize) {
        
        case LBFGS:
            doLBFGS();
            break;
        case GRADIENT_DES:
            doGradientDes();
            break;
            
    }   
    
    //updateDebugger();
}

void
LogisticRegression::doLBFGS() {
    lbfgsfloatval_t fx;
    lbfgsfloatval_t *x = lbfgs_malloc( m_dimensions+1 );
    lbfgs_parameter_t param;
    int ret = 0;


    int Y = 0;
    int m = m_training.size();

    if (m == 0)
        return;

    initTheta();

    x = m_theta;

    
    lbfgs_parameter_init(&param);

    dim = m_dimensions;
    trainingSize = m;
    training = m_training;

    ret = lbfgs(m_dimensions+1, x, &fx, evaluate, progress, NULL, &param);

    /* Report the result. */
    //printf("L-BFGS optimization terminated with status code = %d\n", ret);
    //printf("  fx = %f, x[0] = %f, x[1] = %f\n", fx, x[0], x[1]);

    //std::cin.ignore();
   
    m_theta = x;

    //lbfgs_free(x);
}

void
LogisticRegression::doGradientDes() {
    
    int Y = 0;
    int m = m_training.size();

    if (m == 0)
        return;

    initTheta();
    
    double costJ, last_costJ;

    costJ = INT_MAX-1;
    last_costJ = INT_MAX;

    
    while (costJ < last_costJ) {
        
        last_costJ = costJ;
        costJ = 0.0;
        
        double* deriv_costJ = new double[ m_dimensions+1 ];
   
                
        for (int i =0; i < m; ++i) {

            double* X = new double[ m_dimensions+1 ];
            
            X[0] = 1;
            for (int j=1; j<= m_dimensions; ++j)
                X[j] = m_training[i].first[j-1];

            Y = (m_training[i].second == '1' ? 1 : 0);

            double h = sigmoid(X);

            if (h == 0) h = 0.0001;
            else if (h == 1) h = 0.9999;
          
            costJ += ( ( Y * log(h)) + ((1 - Y) * log(1 - h)) );

            // Vector de gradientes de J 
            for (int j=0; j<= m_dimensions; ++j)
                deriv_costJ[j] += ((h - Y) * X[j]);

           
            delete[] X;

        }

        costJ = -1 * (costJ / m) ;

        for (int i=0; i<= m_dimensions; ++i)
            deriv_costJ[i] = deriv_costJ[i] / m ;
    
      
        double learningRate = 0.1;
       
        double* aux = new double[m_dimensions+1];

        for (int i=0; i<= m_dimensions; ++i)
            aux[i] = m_theta[i] - (learningRate * deriv_costJ[i]);

        m_theta = aux;
        

        iter++;
        vecCost.push_back(costJ);
        
        delete[] deriv_costJ;
    }
    
}

}
