//
// Created by Joseph Wilson on 10/2/2021.
//

#ifndef CS236_PROJECT1_PARAMETER_H
#define CS236_PROJECT1_PARAMETER_H


class Parameter {
private:
    std::string param;

public:
    Parameter(){}
    Parameter(std::string param){
        this->param = param;
    }
    ~Parameter(){}
    std::string getParam(){
        return param;
    }



};


#endif //CS236_PROJECT1_PARAMETER_H
