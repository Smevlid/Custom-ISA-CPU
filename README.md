# CPU Simulator 🖥️

A simple CPU simulator project. A virtual processor with registers and memory management that performs basic operations using assembly-like instructions.

## 📋 Features

- **6 registers** (R1–R6)
- **100 byte memory** area
- **8 different instruction** support
- **3 different execution modes**
- Load program from file
- Interactive user input

## 🚀 Installation

### Requirements

- C++ compiler (g++ recommended)
- Make (optional)

### Build

**Using Make (recommended):**

```bash
make
```

````

**Manual build:**

```bash
g++ -I include -Wall -Wextra -std=c++11 -o computer src/main.cpp src/Computer.cpp src/CPU.cpp src/Program.cpp
```

## 💻 Usage

```bash
./computer <program_file> <mode>
```

### Modes:

- **0** → Run program silently (no output)
- **1** → Show registers after each instruction
- **2** → Show registers + memory after each instruction

### Example:

```bash
./computer program.txt 1
```

## 📖 Supported Instructions

| Instruction | Description                      | Example                |
| ----------- | -------------------------------- | ---------------------- |
| `MOV`       | Move value                       | `MOV R1, 5`            |
| `ADD`       | Addition                         | `ADD R1, R2`           |
| `SUB`       | Subtraction                      | `SUB R1, 10`           |
| `JMP`       | Unconditional / conditional jump | `JMP 5` or `JMP R1, 5` |
| `JPN`       | Jump if ≤ 0 (negative or zero)   | `JPN R1, 3`            |
| `PRN`       | Print value                      | `PRN R1`               |
| `INP`       | Read input from user             | `INP R1`               |
| `HLT`       | Halt / stop execution            | `HLT`                  |

## 📝 Operand Types

- Register: `R1`, `R2`, …, `R6`
- Constant: `5`, `-10`, `100`
- Memory address: `#0`, `#15`, `#99`

## 📄 Program File Format

```text
; This is a comment
MOV R1, 10      ; R1 ← 10
MOV R2, 5       ; R2 ← 5
ADD R1, R2      ; R1 ← R1 + R2  → 15
PRN R1          ; print 15
HLT
```

## 🏗️ Project Structure

```
Custom-ISA-CPU/
├── src/
│   ├── main.cpp
│   ├── Computer.cpp
│   ├── CPU.cpp
│   └── Program.cpp
├── include/
│   ├── Computer.h
│   ├── CPU.h
│   └── Program.h
├── obj/                (generated)
├── Makefile
├── .gitignore
└── README.md
```

## 🎯 Example Programs

### 1. Simple Addition

```assembly
MOV R1, 10
MOV R2, 20
ADD R1, R2
PRN R1
HLT
```

**Expected output (mode 1):**

```
30
```

### 2. Counting Loop

```assembly
MOV R1, 1
MOV R2, 5
PRN R1
ADD R1, 1
SUB R2, 1
JPN R2, 3
HLT
```

### 3. Memory Example

```assembly
MOV R1, 42
MOV #0, R1
MOV #1, 100
MOV R2, #0
PRN R2          ; 42
MOV R3, #1
PRN R3          ; 100
HLT
```

## 🛠️ Make Commands

```bash
make              # build
make clean        # remove build files
make run ARGS='prog.txt 1'   # build + run
make debug        # run with gdb
make help         # show commands
```

## 🐛 Debugging

```bash
make clean
make
make debug
```

Then in gdb:

```
(gdb) run program.txt 1
(gdb) break CPU::execute
(gdb) run
```

**Bugs / suggestions →** open an issue.

```
````
