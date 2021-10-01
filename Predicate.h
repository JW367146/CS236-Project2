//
// Created by Joseph Wilson on 10/2/2021.
//

#ifndef CS236_PROJECT1_PREDICATE_H
#define CS236_PROJECT1_PREDICATE_H



#include "Parameter.h"


class Predicate {
private:
    std::string id;
    std::vector<Parameter*> myPredicate;
public:
    Predicate(){
        this->id = "";
        //this->myPredicate = nullptr;
    }
    //I'm going to overload the Predicate constructor to make a predicate when parsing.
    Predicate(std::vector<std::string> IDs){
        this->id = IDs[0];
        for(int i = 1; i < IDs.size(); i++){
            Parameter* param = new Parameter(IDs[i]);
            myPredicate.push_back(param);

        }
    }



    void setID(std::string idy){
        this->id = idy;
    }


};


#endif //CS236_PROJECT1_PREDICATE_H
