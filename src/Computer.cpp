#include "Computer.h"
#include <iostream>

using namespace std;

Computer::Computer(const string& fileName,int option):option(option){
    myProgram.saveCommands(fileName);
}

void Computer::setOption(int x){ option = x; }

int Computer::getOption() const { return option; }

void Computer::run(){
    const vector <string>& instructions = myProgram.getCommands();
    for(int i = 0; i < instructions.size(); i++){

        if(myProgram.parseline(instructions[i])){
            myCPU.execute(myProgram.getcommand(),myProgram.getop1(),myProgram.getop2(), i,instructions.size());
            if(myCPU.isHalted()){

                if(getOption() == 1)
                {
                    cout << myProgram.getProcessedLine() << " - ";
                    myCPU.printRegisters();
                
                } else if (option == 2) { 
                    cout << myProgram.getProcessedLine() << " - ";
                    myCPU.printRegisters();
                    myCPU.printMemory(); 
                }                 
                break;
                
            }else{
                if(getOption() == 1)
                {
                    cout << myProgram.getProcessedLine() << " - ";
                    myCPU.printRegisters();
                
                } else if (option == 2) { 
                    cout << myProgram.getProcessedLine() << " - ";
                    myCPU.printRegisters();
                    myCPU.printMemory(); 
                }

            }

        }

    }
}
