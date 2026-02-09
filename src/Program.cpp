#include "Program.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

string Program::getProcessedLine(){ return line; }
string Program::getcommand(){ return command; }
string Program::getop1(){ return op1; } 
string Program::getop2(){ return op2; }

const vector<string>& Program::getCommands() const { return commands;}

void Program::saveCommands(string fileName){ //read all commands and save them to an string vector

    ifstream file(fileName);
    
    if(!file.is_open()){
        cerr << "File can not be opened" << endl;
        exit(-1);
    }

    string line;

    while(getline(file,line)){    
        this->commands.push_back(line);

        if(commands.size() > 500){
            cerr << "Program exceeds maximum 500 instructions" << endl;
            file.close();
            exit(-1);
        }
    }
    file.close();
}

bool Program::parseline(const string& rawline){

    line = rawline;
        
    line = line.substr(0,line.find(';'));
    // find the ';' if it is exist and make substr from 0.position to it,if it is not exist take all str 
        
    stringstream linestream(line);
        
    command = op1 = op2 = ""; 
        
    linestream >> command;
    linestream >> op1;
    linestream >> op2;

    if(command.empty()){ //comment lines or spaces
     return false;
    }    

    //if op1 has also a comma with itself
    if(!op1.empty() && op1.back() == ','){ //empty returns bool wheter string is empty or not and back returns last char

     op1.pop_back();

    }
    return true;
}
