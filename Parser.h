
#ifndef CS236_PROJECT1_PARSE_H
#define CS236_PROJECT1_PARSE_H



#include "Token.h"
#include "DatalogProgram.h"

class Parser
{
private:
    std::vector<Token*> tokens;
    int tokenIndex;
    Token* currentToken;

public:
    Parser(std::vector<Token*> tokens){
        this->tokens = tokens;
        tokenIndex = 0;
        currentToken = nullptr;
    }
    ~Parser(){}





    //Now we parse the input. If we get an error we'll throw it
    void parse(){
        try{
            //start the calls
            parseDatalogprogram();

        }catch(Token* error){
        std::cout << "Failure " << error->toString();
        }
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
    void parseScheme(){
        parseID();
        parseLEFT_PAREN();
        parseID();
        parseIDlist();
        parseRIGHT_PAREN();
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
        }
        //Follow(Factlist) = RULES
        if(currentToken->getType()== TokenType::RULES){
            //We go on.
        }else throw currentToken;

    }
    void parseRULES();
    void parseRulelist();
    void parseQUIRIES();
    //void parseCOLON();
    void parseQuery();
    void parseQuerylist();






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
    void parseFact(){
        currentToken = tokens[tokenIndex];
        parseID();
        parseLEFT_PAREN();
        parseSTRING();
        parseRIGHT_PAREN();
        parsePERIOD();
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
