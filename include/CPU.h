#ifndef CPU_H
#define CPU_H

#include <string>

using namespace std;

class CPU{
    private:
    int registers[6]; 
    bool halted;
    unsigned char memory[100];
    
    public:

    CPU();

    bool isHalted() const;
    bool is_register(const string& str);
    void printRegisters() const;
    void printMemory() const;
    void execute(const string &command, const string& op1, const string& op2, int &PC, int commandcount);

    void executeMOV(const string& op1, const string& op2);
    void executeADD(const string& op1, const string& op2);
    void executeSUB(const string& op1, const string& op2);
    void executeJMP(const string& op1, const string& op2, int &PC, int commandcount);
    void executeJPN(const string& op1, const string& op2, int &PC, int commandcount);
    void executePRN(const string& op1);
    void executeINP(const string& op1);

    bool is_address(const string& str);

    static int stringToInt(const string& str);
    static int addressToInt(const string& str);

    int getRegisterIndex(const string& op1);

    int readOperand(const string& operand);
    void writeOperand(const string& operand, int value);
};

#endif
