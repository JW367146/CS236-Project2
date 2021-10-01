
#ifndef CS236_PROJECT1_PARSE_H
#define CS236_PROJECT1_PARSE_H

#include "Predicate.h"

#include "Token.h"
#include "DatalogProgram.h"

class Parser
{
private:
    std::vector<Token*> tokens;
    int tokenIndex;
    Token* currentToken;
    std::string exception;

    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;

    Predicate* currentPredicate;




    //This grabs all the IDs from a section of tokens.
    std::vector<std::string> grabIDs(int begin, int end){
        std::vector<std::string> output;
        for (int i = begin; i <end; i++){
            if(tokens[i]->getType() == TokenType::ID || tokens[i]->getType() == TokenType::STRING){
                output.push_back(tokens[i]->getDescription());
            }
        }
        return output;
    }

    ////This will make a predicate from a vector of IDs
    Predicate* makePredicate(std::vector<std::string> IDs){
        Predicate* output;
        int numIDs = IDs.size();
        std::string stringID = IDs[0];
        //The first ID will be the string id
        return output;
    }


public:
    Parser(std::vector<Token*> tokens){
        this->tokens = tokens;
        tokenIndex = 0;
        currentToken = nullptr;
        currentPredicate = nullptr;
    }
    ~Parser(){}

    std::string getException(){
        return exception;
    }



    //Now we parse the input. If we get an error we'll throw it
    bool parse(){
        try{
            //start the calls
            parseDatalogprogram();
        }catch(Token* error){
        exception = error->toString();
        return false;
        }
        return true;
    }



    //Recursive descent parsing.
    void parseDatalogprogram(){
        parseSCHEMES();
        parseCOLON();
        parseScheme();
        parseSchemelist();
        parseFACTS();
        parseCOLON();
        parseFactlist();
        parseRULES();
        parseCOLON();
        parseRulelist();
        parseQUERIES();
        parseCOLON();
        parseQuery();
        parseQuerylist();
        parseEOF();
    }
    void parseSCHEMES(){
        currentToken = tokens[tokenIndex];
        if(currentToken->getType() == TokenType::SCHEMES){
            //We go on with the parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parseCOLON(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::COLON){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    //parseScheme also pushes back on schemes
    void parseScheme(){
        //We also need to be forming the predicate data structure. We will just collect all the IDs out of the range in tokens that we want.
        int predBegin = tokenIndex;
        parseID();
        parseLEFT_PAREN();
        parseID();
        parseIDlist();
        parseRIGHT_PAREN();
        int predEnd = tokenIndex - 1;

        //Now we want to make a predicate
        std::vector<std::string> schemeIDs = grabIDs(predBegin,predEnd);
        Predicate* scheme = new Predicate(schemeIDs);
        //We successfully made a scheme predicate. Now we push it back on our vector of those
        schemes.push_back(scheme);
    }


    void parseSchemelist(){
        //There are two productions here. Let's look at the token and send it through scheme or lambda
        currentToken = tokens[tokenIndex];
        //FIRST(schemelist = ID)
        if(currentToken->getType() == TokenType::ID) {
        parseScheme();
        parseSchemelist();
        }
        //FOLLOW(schemelist = FACTS)
        else if(currentToken->getType() == TokenType::FACTS){
            //We go on to the FACTS
        }else throw currentToken;
    }
    void parseFACTS(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::FACTS){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    //void parseCOLON();
    void parseFactlist(){
        //There are multiple productions so lets see what we have
        currentToken = tokens[tokenIndex];
        //First(Factlist) = ID
        if(currentToken->getType() == TokenType::ID){
            parseFact();
            parseFactlist();
        }
        //Follow(Factlist) = RULES
        else if(currentToken->getType()== TokenType::RULES){
            //We go on.
        }else throw currentToken;
    }
    void parseRULES(){
        currentToken = tokens[tokenIndex];
        if(currentToken->getType() == TokenType::RULES){
            tokenIndex++;
        }else throw currentToken;
    }
    void parseRulelist(){
        currentToken = tokens[tokenIndex];
        //FIRST(rulelist) == ID
        if(currentToken->getType() ==TokenType::ID){
            parseRule();
            parseRulelist();
        }
        //FOLLOW(rulelist) == QUERIES
        else if(currentToken->getType() == TokenType::QUERIES){

        }else throw currentToken;
    }
    void parseQUERIES(){
        currentToken = tokens[tokenIndex];
        if(currentToken->getType() == TokenType::QUERIES){
            tokenIndex++;
        }else throw currentToken;
    }
    //void parseCOLON();
    void parseQuery(){
        //There is one production for Query
        //FIRST(QUERY) = ID
        currentToken = tokens[tokenIndex];
        if(currentToken->getType() == TokenType::ID){
            parsePredicate();
            parseQ_MARK();
        }else throw currentToken;
    }
    void parseQuerylist(){
        //THere are two productions for querylist
        currentToken = tokens[tokenIndex];
        //FIRST(querylist) = ID
        if(currentToken->getType() == TokenType::ID){
            parseQuery();
            parseQuerylist();
        }
        //FOLLOW(querylist) = EOF
        else if (currentToken->getType() == TokenType::eof){
            //Go on from here
        }else throw currentToken;
    }
    void parseEOF(){
        //There is just the end of file left
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::eof){
            //we are at the end, so we don't really need to increment tokenIndex
        }else throw currentToken;
    }





    ////Secondary parse calls
    void parseID(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::ID){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parseLEFT_PAREN(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::LEFT_PAREN){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parseRIGHT_PAREN(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::RIGHT_PAREN){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parseIDlist() {
        currentToken = tokens[tokenIndex];
        //There are multiple productions from idlist so we need to check if it's comma or lambda
        if(currentToken->getType() == TokenType::COMMA){
            parseCOMMA();
            parseID();
            parseIDlist();
        }else if(currentToken->getType()== TokenType::RIGHT_PAREN){
            //We don't parse RIGHT_PAREN yet
        }else throw currentToken;
    }
    //parseFact also pushes back on
    void parseFact(){
        currentToken = tokens[tokenIndex];
        int predBegin = tokenIndex;
        parseID();
        parseLEFT_PAREN();
        parseSTRING();
        parseStringlist();
        parseRIGHT_PAREN();
        parsePERIOD();
        int predEnd = tokenIndex-1;

        //Now we add it to facts
        std::vector<std::string> factIDs = grabIDs(predBegin,predEnd);
        Predicate* fact = new Predicate(factIDs);
        facts.push_back(fact);
    }
    void parseRule(){
        currentToken = tokens[tokenIndex];
        parseHeadPredicate();
        parseCOLON_DASH();
        parsePredicate();
        parsePredicatelist();
        parsePERIOD();
    }
    void parseQ_MARK(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::Q_MARK){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }





    ////Tertiary Parses
    void parseCOMMA(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::COMMA){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parseSTRING(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::STRING){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parsePERIOD(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::PERIOD){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parseStringlist(){
        currentToken = tokens[tokenIndex];
        //We have two productions so we need to see what to do
        //FIRST(stringlist) = COMMA
        if(currentToken->getType() == TokenType::COMMA){
            parseCOMMA();
            parseSTRING();
            parseStringlist();
        }
        //FOLLOW(stringlist) = RIGHT_PAREN
        else if(currentToken->getType() == TokenType::RIGHT_PAREN){
            //We continue parsing
        }else throw currentToken;
    }
    void parseHeadPredicate(){
        //There is just one production here
        parseID();
        parseLEFT_PAREN();
        parseID();
        parseIDlist();
        parseRIGHT_PAREN();
    }
    void parseCOLON_DASH(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::COLON_DASH){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parsePredicate(){
        currentToken=tokens[tokenIndex];
        //There is just one production for predicate
        parseID();
        parseLEFT_PAREN();
        parseParameter();
        parseParameterlist();
        parseRIGHT_PAREN();
    }
    void parsePredicatelist(){
        //There are two productions for predicatelist
        currentToken=tokens[tokenIndex];
        //FIRST(predicatelist) = COMMA
        if(currentToken->getType() == TokenType::COMMA){
            parseCOMMA();
            parsePredicate();
            parsePredicatelist();
        }
        //FOLOOW(predicatelist) = PERIOD
        else if(currentToken->getType()==TokenType::PERIOD){
            //Continue on to follow
        }else throw currentToken;
    }





    ////Quaternary parse calls
    void parseParameter(){
        ////There are three productions for parameter
        currentToken = tokens[tokenIndex];
        //FIRST(parameter) = {ID, STRING, expression->LEFT_PAREN}
        if(currentToken->getType()==TokenType::ID){
            parseID();
        }
        else if (currentToken->getType() == TokenType::STRING){
            parseSTRING();
        }
        else if (currentToken->getType() == TokenType::LEFT_PAREN){
            parseExpression();
        }else throw currentToken;
    }
    void parseParameterlist(){
        //THere are two productions for this
        currentToken = tokens[tokenIndex];
        //FIRST(parameterlist) = COMMA
        if(currentToken->getType() == TokenType::COMMA){
            parseCOMMA();
            parseParameter();
            parseParameterlist();
        }
        //FOLLOW(parameterlist) = RIGHT_PAREN
        else if(currentToken->getType() ==TokenType::RIGHT_PAREN){
            //We continue
        }else throw currentToken;
    }


    ////Pentenary parse Calls
    void parseExpression(){
        //There is only one production for expression
        parseLEFT_PAREN();
        parseParameter();
        parseOperator();
        parseParameter();
        parseRIGHT_PAREN();
    }




    ////Hexenary parse calls
    void parseOperator() {
        //There are two productions for this operator
        //FIRST(operator) = {ADD, MULTIPLY}
        currentToken = tokens[tokenIndex];
        if(currentToken->getType() == TokenType::ADD){
            parseADD();
        }
        else if(currentToken->getType() == TokenType::MULTIPLY){
            parseMULTIPLY();
        }else throw currentToken;
    }




    ////Heptenary parse calls
    void parseADD(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::ADD){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }
    void parseMULTIPLY(){
        currentToken=tokens[tokenIndex];
        if(currentToken->getType() == TokenType::MULTIPLY){
            //We go on parsing
            tokenIndex++;
        }else throw currentToken;
    }






//    //The order of calls
//    void parseDatalogprogram();
//    void parseSCHEMES();
//    void parseCOLON();
//    void parseScheme();
//    void parseSchemelist();
//    void parseFACTS();
//    //void parseCOLON();
//    void parseFACTLIST();
//    void parseRULES();
//    void parseRulelist();
//    void parseQUIRIES();
//    //void parseCOLON();
//    void parseQuery();
//    void parseQuerylist();









};





#endif //CS236_PROJECT1_PARSE_H
