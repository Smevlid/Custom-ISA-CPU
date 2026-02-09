#include "Computer.h"
#include "CPU.h"
#include <iostream>

using namespace std;

int main(int argc,char** argv)
{
    if(argc != 3)
    {
        cout << "Error in command line: you should have 3 argument";
        return 1;
    }

    Computer myComputer(argv[1],CPU::stringToInt(argv[2]));

    if(myComputer.getOption() < 0 || myComputer.getOption() > 2 )
    {
        cout << "Option must be 0,1 or 2";
        return 1;
    }

    myComputer.run();
}
