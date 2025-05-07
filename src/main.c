#include <stdio.h>
#include <stdbool.h>

typedef enum {
  PSH, // --psh val           :: Push <val> to stack
  ADD, // --add               :: Pops two values on top of the stack, add them, then push to stack
  POP, // --pop               :: Pops the value on the stack, the print
  SET, // --set reg, val      :: Sets register to value
  HLT // --hlt                :: Stops the program
} InstructionSet;

// Test Program
const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  SET, 1, 5,
  POP,
  HLT
};

// Registers
// NUM_OF_REGISTERS as last member to get the actual size of the registers
typedef enum {
  A, B, C, D, E, F,
  PC, // Program Counter
  SP, // Stack Pointer
  NUM_OF_REGISTERS
} Registers;

const char* register_names[] = {
  "A", "B", "C", "D", "E", "F", "PC", "SP"
};

int stack[256];
int registers[NUM_OF_REGISTERS];

// Get PC and SP
#define sp (registers[SP])
#define pc (registers[PC])

// To determine HLT
bool running = true;

// Fetch current instruction
int fetch() {
  return program[pc];
}

// Evaluating instruction
void eval(int instruction) {
  switch (instruction) {
  case HLT:
    running = false;
    printf("Halt.");
    break;
  case PSH:
    printf("Before PSH: SP is now %d \n", sp);
    // stack pointer now points to the stack above
    sp = sp + 1;
    pc = pc + 1;

    // example:
    // program = [ PSH, 5, PSH, 6 ]
    // PSH has an argument eg: 5, hence pc++ to identify the argument.
    stack[sp] = program[pc];
    // Now top of stack has the new value.
    printf("After PSH: SP is now %d \n", stack[sp]);
    break;
  case POP:
    // store value from the stack at a variable first!!!

    int val = stack[sp--];

    printf("POP: Value Popped: %d \n", val);
    break;
  case ADD:
    // Pop the top of stack and store
    int val1 = stack[sp--];
    // Pop and store again
    int val2 = stack[sp--];

    int result = val1 + val2;

    // New stack level for the result
    sp = sp + 1;

    // store the result in new stack level
    stack[sp] = result;

    printf("ADD value %d & %d. Result: %d\n", val1, val2, result);

    break;
  case SET:
    // SET has 2 arguments,
    // to assign a value to a register.
    // eg: SET A 0
    // Assign value 0 to register A.

    registers[program[pc + 1]] = program[pc + 2];
    printf("SET: Register %s: %d\n", register_names[program[pc - 1]],registers[B]);
    pc += 2;
    break;
  }
}

int main() {

  pc = 0;
  sp = -1;

  while (running) {
    eval(fetch());
    pc++; // Increment program counter on every iter
    }

  return 0;
  }