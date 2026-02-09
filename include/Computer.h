#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "Program.h"
#include <string>

using namespace std;

class Computer{
    private:
    CPU myCPU;
    Program myProgram;
    int option;

    public:
    Computer(const string& fileName,int option);
    void setOption(int x);
    int getOption() const;
    void run();
};

#endif
