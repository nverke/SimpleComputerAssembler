#include <stdio.h>
#include <stdlib.h>

int A, IP;
unsigned int Memory[300000000];
unsigned int Port[300000000];

int dispStatus() {
    printf("\nA = %x\nIP = %x\n", A, IP);
    return 1;
}

int execute(unsigned int OpCode, unsigned int Operand) { //hardcoded instruction set.
    if (OpCode == 0) {
        A = Memory[Operand];
        printf("Load Accumulator with memory location %x", Operand);
    } else if (OpCode == 1) {
        Memory[Operand] = A;
        printf("Store Accumulator at memory location %x", Operand);
    } else if (OpCode == 2) {
        A = Port[Operand];
        printf("Input Accumulator from port %x", Operand);
    } else if (OpCode == 3) {
        Port[Operand] = A;
        printf("Output Accumulator to port %x", Operand);
    } else if (OpCode == 4) {
        A = A + Memory[Operand];
        printf("Add Accumulator with memory location %x", Operand);
    } else if (OpCode == 5) {
        A = A - Memory[Operand];
        printf("Subtract Accumulator with memory location %x", Operand);
    } else if (OpCode == 6) {
        A = A * Memory[Operand];
        printf("Multiply Accumulator by memory location %x", Operand);
    } else if (OpCode == 7) {
        A = A / Memory[Operand];
        printf("Divide Accumulator by memory location %x", Operand);
    } else if (OpCode == 8) {
        A = A % Memory[Operand];
        printf("Modulus Accumulator by memory location %x", Operand);
    } else if (OpCode == 9) {
        A = A & Memory[Operand];
        printf("Bitwise AND Accumulator with memory location %x", Operand);
    } else if (OpCode == 10) {
        A = A | Memory[Operand];
        printf("Bitwise OR Accumulator with memory location %x", Operand);
    } else if (OpCode == 11) {
        A = A ^ Memory[Operand];
        printf("Bitwise XOR Accumulator with memory location %x", Operand);
    } else if (OpCode == 12) {
        IP = Operand - 1;
        printf("Jump to address %x", Operand);
    } else if (OpCode == 13) {
        if (A == 0) {
            IP = Operand - 1;
            printf("Jump to address %x since A == 0", Operand);
        } else {
            printf("Don't Jump to address %x since A != 0", Operand);
        }
    } else if (OpCode == 14) {
        if (A < 0) {
            IP = Operand - 1;
            printf("Jump to address %x since A < 0", Operand);
        } else {
            printf("Don't Jump to address %x since A !< 0", Operand);
        }
    } else if (OpCode == 15) {
        if (A > 0) {
            IP = Operand - 1;
            printf("Jump to address %x since A > 0", Operand);
        } else {
            printf("Don't Jump to address %x since A !> 0", Operand);
        }
    } else {
        return 0;
    }
    IP++;
    return 1;
}

int main(int argc, char* argv[]) {
    
    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            Port[i-2] = atoi(argv[i]);
        }
    }
    
    int i = -1; //counter
    int rv;
    FILE *fp;
    
    fp=fopen(argv[1], "r");
    
    if (fp==NULL){ //if fp returns null then no file
        printf("file doesnt exist?!\n");
        return 1;
    }
    
    while (rv >= 0) { //scan all lines of memory into Memory array
        i++;
        rv = fscanf(fp, "%x", &Memory[i]);
    }
    
    while (IP < i) {
        unsigned int OpCode = (Memory[IP] & 0xf0000000) >> 28; //find the opCode with a mask and some shifting
        unsigned int Operand = Memory[IP] & 0x0fffffff;  //find the operand with a mask
        execute(OpCode, Operand);
        dispStatus();
        getchar();
    }
    
    fclose(fp);
    
}

