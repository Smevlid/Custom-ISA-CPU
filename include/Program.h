#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>

using namespace std;

class Program{
    private:
    vector<string> commands;
    string line, command, op1, op2;

    public:
    string getProcessedLine();
    string getcommand();
    string getop1(); 
    string getop2();

    void saveCommands(string fileName);
    const vector<string>& getCommands() const;
    bool parseline(const string& rawline);
};

#endif
