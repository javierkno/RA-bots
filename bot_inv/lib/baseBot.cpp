#include "baseBot.h"

namespace ra {
   

Bot::Bot() {
    init();
}

//
//Constructor con las dimensiones de la muestra y el numero de muestras a aprender
//
Bot::Bot(int dim, unsigned numtr, std::string name) {
    init();
    maxLearn = numtr;
    dimension = dim;
    nameBot = name;
    
    lr = new ra::LogisticRegression(dimension);
}

Bot::Bot(const Bot& orig) {
    
}

Bot::~Bot() {
    
}

void
Bot::setLearnNum(int num) {
    maxLearn = num;
}

int
Bot::getAcualLearn() {
    return actualLearn;
}

//
//Añade los datos de training al perceptrón y la regesión logística
//
void 
Bot::addData(std::string s) {
    double* data = new double[dimension];
    TVecDouble inputs;
    
    std::vector<std::string> tokens = Utils::split(s);
    
    if(tokens.size() > 0 && !strcmp(tokens.front().c_str(), "NEXTCANDLE")) {
        
        for(unsigned i=0; i<dimension; ++i) {
            data[i] = atof(tokens.back().c_str());
            tokens.pop_back();
            inputs.push_back(data[i]);
        }
        

        actual=next;
        next=data[2];
        actualLearn++;


        //std::cerr << "N = "<< actualLearn <<std::endl;   


        //El Bot está aprendiendo
        if(actualLearn < maxLearn) {

            lr->updateTraining(data, ((actual-next)<0 ? '0' : '1'));
            pt->add(inputs, ((actual-next)<0 ? false : true));

        }
        else { //El Bot ya ha aprendido
            if(!learned) {
                lr->execute();
                pt->learn();

                learned = true;
            }
            else {
                classify(inputs, data);
            }
        }
    }
}

//
//
//
void 
Bot::classify(TVecDouble inputs, double* data) {
    
    /*if(pt->h(inputs)==-1.0) {
        std::cerr<<"VENDE"<<std::endl;
    }
    else {
        std::cerr<<"COMPRA"<<std::endl;
    }*/

    if(lr->predictWith(data)) {
        std::cout << kMSGB[1] << " " << 1 << std::endl;
    }
    else {
        std::cout << kMSGB[2] << " " << 1 << std::endl;
    }
}


void
Bot::registrar() {
    std::cout << kMSGB[0] << " " << nameBot << std::endl;
}

void
Bot::init() {
    maxLearn = 40;
    actualLearn = 0;
    learned = false;
    dimension = 5;
    actual = 0;
    next = 0;
    
    lr = new ra::LogisticRegression(dimension);
    pt = new ra::Perceptron();
}

}

