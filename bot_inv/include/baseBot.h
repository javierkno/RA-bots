#ifndef BASEBOT_H
#define	BASEBOT_H

#include "logisticRegression.h"
#include "perceptron.h"
#include <string.h>
#include <cstdlib>

namespace ra 
{
    
const std::string kMSGS[] = {"INITIALIZE","REGISTRATION_OK","START","NEXTCANDLE","BOUGHT","SOLD","NOT_UNDERSTOOD","END"};
const std::string kMSGB[] = {"REGISTER","BUY","SELL"};    

class Bot {

private:
    ra::Perceptron* pt;
    ra::LogisticRegression* lr;
    int maxLearn;
    int actualLearn;
    unsigned dimension;
    bool learned;
    std::string nameBot;
    
    double actual;
    double next;
    
    void init();
    
public:
    Bot();
    Bot(int, unsigned, std::string);
    ~Bot();
    Bot(const Bot& orig);
    
    void registrar();
    void addData(std::string);
    void classify(TVecDouble, double*);
    void setLearnNum(int);
    int getAcualLearn();
    std::vector<std::string> split(std::string);
};
}
#endif


