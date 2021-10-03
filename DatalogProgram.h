
#ifndef CS236_PROJECT1_DATALOGPROGRAM_H
#define CS236_PROJECT1_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <set>

class DatalogProgram
{

private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::set<std::string > domain;


public:
    DatalogProgram(){}
    DatalogProgram(std::vector<Predicate*> schemes,
                  std::vector<Predicate*> facts,
                  std::vector<Predicate*> queries,
                  std::vector<Rule*> rules,
                  std::set<std::string> domain){

        this->schemes = schemes;
        this->facts = facts;
        this->queries = queries;
        this->rules = rules;
        this->domain = domain;
    }
    ~DatalogProgram(){}


public:

    std::string toString(){
        std::stringstream outy;
        outy<< "Schemes("<<schemes.size() << "):\n";
        outy<< schemesString();
        outy<< "Facts(" << facts.size() << "):\n";
        outy<< factsString();
        outy << "Rules("<< rules.size() << "):\n";
        outy << rulesString();
        outy << "Queries("<< queries.size()<<"):\n";
        outy<< queriesString();
        outy<< "Domain(" << domain.size() <<"):\n";
        outy<< domainString();


        return outy.str();
    }

    std::string schemesString(){
        //I wrote this tostring before I wrote a general predicate tostring
        std::stringstream out;
        for(int i = 0; i < schemes.size(); i++){
            out<<"  "<<schemes[i]->getID()<<"(";
            for (int j =0; j < schemes[i]->getNumParam(); j++){
                out<<schemes[i]->getParamAtI(j);
                if (j<schemes[i]->getNumParam()-1){
                    out <<",";
                }
            }
            out<< ")\n";
        }
        return out.str();
    }
    std::string  factsString(){
        std::stringstream out;
        for(int i = 0; i< facts.size();i++){
            out<<"  "<<facts[i]->toString()<<".\n";
        }
        return out.str();
    }
    std::string rulesString(){
        std::stringstream out;
        for(int i = 0; i< rules.size();i++){
            out<<"  "<<rules[i]->toString() <<".\n";
        }
        return out.str();
    }
    std::string queriesString(){
        std::stringstream out;
        for(int i = 0; i< queries.size();i++){
            out<<"  "<< queries[i]->toString()<<"?\n";
        }
        return out.str();
    }
    std::string domainString(){
        std::stringstream out;
        for( auto it = domain.begin();it != domain.end();++it){
            out<< "  "<<*it <<"\n";
        }
        return out.str();
    }


};


#endif //CS236_PROJECT1_DATALOGPROGRAM_H
