#include "CPU.h"
#include <iostream>
#include <cctype>

using namespace std;

CPU::CPU():halted(false)
{
    for(int i=0; i < 6; i++){
        registers[i] = 0;
    }
    for(int i=0; i < 100; i++){
        memory[i] = 0;
    }
}

bool CPU::isHalted() const { return halted; }

bool CPU::is_register(const string& str){
    if(str.size() != 2) return false;

    if(str[0] != 'R') return false;

    if(str[1] < '1' || str[1] > '6') return false;

    return true;
}

bool CPU::is_address(const string& str){
    if(str.empty() || str[0] != '#') return false;

    if(str.length() >= 4) return false;

    for(int i=1; i < str.length(); i++){
        if(!isdigit(str[i])) return false;
    }

    return true;
}

void CPU::printRegisters() const{ //for option 1
    for(int i = 0; i < 6; i++){

        cout << "R" << i+1 << "=" << registers[i];

        if(i != 5){
        cout << ", ";
            }
    }
    cout << endl;
}

void CPU::execute(const string &command, const string& op1, const string& op2, int &PC, int commandcount) { 

    if (command == "MOV") {
        executeMOV(op1, op2);
    } else if (command == "ADD") {
        executeADD(op1, op2);
    } else if (command == "SUB") {
        executeSUB(op1, op2);
    } else if (command == "JMP") {
        executeJMP(op1, op2, PC, commandcount);
    } else if (command == "JPN") { 
        executeJPN(op1, op2, PC, commandcount); 
    } else if (command == "PRN") {
        executePRN(op1);
    } else if (command == "INP") {
        executeINP(op1);
    } else if (command == "HLT") {
        halted = true; 
    } else {
        cerr << "Command not found"<< endl;
        exit(-1);
    }
}

int CPU::readOperand(const string& operand){

    if(is_register(operand)){
        return registers[getRegisterIndex(operand)];

    }else if(is_address(operand)){
        return static_cast<int> (memory[addressToInt(operand)]);

    }else{
        return stringToInt(operand);
    }
}

void CPU::writeOperand(const string& operand,int value){

    if(is_register(operand)){
        registers[getRegisterIndex(operand)] = value;

    }else if(is_address(operand)){
        memory[addressToInt(operand)] = static_cast<unsigned char> (value);

    }else{
        cerr << "can not be constant value" << endl;
        exit(-1);
    }

}

void CPU::executeMOV(const string& op1, const string& op2){
    if(op1.empty() || op2.empty()){
        cerr << "MOV must have 2 operands" << endl;
        exit(-1);
    }

    writeOperand(op1,readOperand(op2));
    
}

void CPU::executeADD(const string& op1, const string& op2){
    if(op1.empty() || op2.empty()){
        cerr << "ADD must have 2 operands" << endl;
        exit(-1);
    }

    if(!is_register(op1)){
        cerr << "ADD must have reg1" << endl;
        exit(-1);
    }

    registers[getRegisterIndex(op1)] += readOperand(op2);

}
void CPU::executeSUB(const string& op1, const string& op2){
    if(op1.empty() || op2.empty()){
        cerr << "SUB must have 2 operands" << endl;
        exit(-1);
    }

    if(!is_register(op1)){
        cerr << "SUB must have reg1" << endl;
        exit(-1);
    }

    registers[getRegisterIndex(op1)] -= readOperand(op2);
}
void CPU::executeJMP(const string& op1, const string& op2, int &PC, int commandcount){

    // JMP reg, lineAddress - jump if register is zero
    if(is_register(op1) && !op2.empty()){

        int reg = getRegisterIndex(op1);

        if(registers[reg] == 0){

            int newline = stringToInt(op2);

            if(newline <= commandcount && newline > 0){
                PC = newline - 2;
            } else {
                cerr << "JMP: line number out of range" << endl;
                exit(-1);
            }
        }

    }else if(!op1.empty() && op2.empty()){ // JMP lineAddress - unconditional jump

        int newline = stringToInt(op1);

        if(newline <= commandcount && newline > 0){
            PC = newline - 2;
        } else {
            cerr << "JMP: line number out of range"<< endl;
            exit(-1);
        }
    }
    else{
        cerr << "JMP: invalid operands" << endl;
        exit(-1);
    }
}

void CPU::executeJPN(const string& op1, const string& op2, int &PC, int commandcount){

   // JPN reg, lineAddress - jump if register is zero or negative
    if(!is_register(op1) || op2.empty()){
        cerr << "JPN requires register and line address" << endl;
        exit(-1);
    }
    
    int reg = getRegisterIndex(op1);

    if(registers[reg] <= 0){

        int newline = stringToInt(op2);

        if(newline <= commandcount && newline > 0){
            PC = newline - 2;
        } else {
            cerr << "JPN: line number out of range" << endl;
            exit(-1);
        }
    }
}
void CPU::executePRN(const string& op1){
    if(op1.empty()){
        cerr << "PRN requires an operand" << endl;
        exit(-1);
    }

    cout << readOperand(op1) << endl;
}
void CPU::executeINP(const string& op1){
    if(op1.empty() || !is_register(op1)){
        cerr << "PRN requires an operand" << endl;
        exit(-1);
    }

    char inputchar;

    int reg = getRegisterIndex(op1);

    cout << "Enter a character" << endl;
    cin >> inputchar;

    registers[reg] = inputchar;

}

int CPU::stringToInt(const string& str){
    int result = 0;
    int i = 0;
    bool negative = false;

    if(str.empty()){
        cerr << "empty string to integer" << endl;
        exit(-1);
    }

    if(str[0] == '-'){
        negative = true;
        i = 1;
        if(str.length() == 1){
            cerr << "invalid input" << endl;
            exit(-1);
        }

    }
    for(; i < str.length(); i++){

        if(str[i] >= '0' && str[i] <= '9'){
            result = result*10 + (str[i] - '0');

        }else{
            cerr << "invalid input" << endl;
            exit(-1);
        } 
    }
    if(negative){
        return -result;
    }else{
        return result;

    }
}

int CPU::addressToInt(const string& str){
    
    int addressValue = stringToInt(str.substr(1));

    if(addressValue < 100 && addressValue >= 0){
        return addressValue;

    }else{
        cerr << "Wrong address" << endl;
        exit(-1);
    }
}

int CPU::getRegisterIndex(const string& op1) {
    
    if (!is_register(op1)) { 
        cerr << "Invalid register "<< endl;
        exit(-1);
    }

    return op1[1] - '1'; 
}

void CPU::printMemory() const {

    cout << "Memory:" << endl;

    for(int i = 0; i < 100; ++i) {

        cout << static_cast<int>(memory[i]) << " "; 

        if ((i + 1) % 10 == 0) { 
            cout << endl;
        }

    }
    cout << endl;
}
