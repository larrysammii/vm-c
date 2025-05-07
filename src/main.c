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


int stack[256];
int registers[NUM_OF_REGISTERS];

// Instruction Array
int *instructions;

// Number of instructions to do
int instruction_count = 0;

// Get PC and SP
#define SP (registers[SP])
#define PC (registers[PC])

// To determine HLT
bool running = true;

// Evaluating instruction
void eval(int instruction) {
  switch (instruction) {
  case HLT:
    running = false;
    break;
  case PSH:
    // stack pointer now points to the stack above
    SP++;
    // example:
    // program = [ PSH, 5, PSH, 6 ]
    // PSH has an argument eg: 5, hence pc++ to identify the argument.
    stack[SP] = program[PC++];
    // Now top of stack has the new value.
    break;
  case POP:
    // store value from the stack at a variable first!!!
    int val = stack[SP--];

    printf("Value Popped %d\n :", val);
    break;
  case ADD:
    // Pop the top of stack and store
    int val1 = stack[SP--];
    // Pop and store again
    int val2 = stack[SP--];

    int result = val1 + val2;

    // New stack level for the result
    SP++;

    // store the result in new stack level
    stack[SP] = result;

    break;
  case SET:
    // SET has 2 arguments,
    // to assign a value to a register.
    // eg: SET A 0
    // Assign value 0 to register A.
    registers[instructions[PC + 1]] = instructions[PC + 2];
    PC += 2;
    break;
  }
}

// Fetch current instruction
int fetch() {
  return program[PC];
}

int main() {
  while (running) {
    eval(fetch());
    PC++; // Increment program counter on every iter
    }
  }