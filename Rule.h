//
// Created by Joseph Wilson on 10/2/2021.
//

#ifndef CS236_PROJECT1_RULE_H
#define CS236_PROJECT1_RULE_H

#include "Predicate.h"
#include <sstream>
#include <string>


class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;


public:
    Rule(){}
    Rule(Predicate* head, std::vector<Predicate*> body){
        this->headPredicate = head;
        this->bodyPredicates = body;
    }

    std::string toString(){
        std::stringstream out;
        out << headPredicate->toString() <<" :- ";
        for(unsigned int i = 0; i < bodyPredicates.size() ; i++){
            out<< bodyPredicates[i]->toString();
            if (i<bodyPredicates.size()-1){
                out<<",";
            }
        }
        return out.str();
    }

};


#endif //CS236_PROJECT1_RULE_H
