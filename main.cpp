#include "Lexer.h"
#include "iostream"
#include "fstream"

using namespace std;

int main(int argc, char** argv) {


    //// Main Part 1
    // I need to make sure I have command line argus.
    string fileName;
    // I need to make sure I have a command line to run.
    if (argv[1]){
        fileName = argv[1];
    }
    else {
        cout << "Missing commandline argument\n\n";
        return 1;
    }








    //Well now I want my whole input file as a string that I will send to run on the lexer.
    ifstream myFile;
    myFile.open(fileName);
    string lines;
    while (!myFile.eof()){
        string newLine;
        getline(myFile, newLine);
        lines = lines + newLine + '\n';
    }
    //Now lines has all the whole input file as one string.




   // cout << lines;








//I'm making a lexer here and I will pass the input to it with Run.
    Lexer* lexer = new Lexer();
    lexer->Run(lines);

cout << lexer->toString();

    delete lexer;
    return 0;
}