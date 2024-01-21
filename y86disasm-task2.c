#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is an array of register mnemonics in y86
const char *register_names[] = {"%eax", // Register 0
                                "%ecx", // Register 1
                                "%edx", // Register 2
                                "%ebx", // Register 3
                                "%esp", // Register 4
                                "%ebp", // Register 5
                                "%esi", // Register 6
                                "%edi", // Register 7
                                "UNKNOWN_REGSITER"};

int convertStrToByteCode(const char *str, unsigned char inst[], int size);

int main(int argc, char **argv) {
  FILE *pFile = NULL;

  char buffer[15];

  if (argc < 2) {
    pFile = fopen("./test2.txt", "r");
  } else {
    pFile = fopen(argv[1], "r");
  }

  if (pFile == NULL) {
    printf("Error open test file, please make sure they exist.\n");

    return 0;
  }

  while (fgets(buffer, 15, pFile) && strlen(buffer) > 1) {
    // This unsigned char array stores an instruction read from the file
    // As the largest y86 instruction is 6 bytes, there are 6 unsigned char in
    // the array where each represents a byte.
    unsigned char instruction[6] = {0, 0, 0, 0, 0, 0};
    convertStrToByteCode(buffer, instruction, 6);

    // y86 opcode and operands can be disassembled. Any undisassembled opcode
    // should display as "TODO: undisassembled opcode and operands"
  
    ////DECODING/FLIPPING SMALL ENDIAN TO BIG ENDIAN FORMAT////
   if(instruction[0] == 0x10) {
    printf("nop \n");    //Instruction with no operand
    }
    else if(instruction[0] == 0x90) {
      printf("ret \n");     //Instruction with no operand
    }
    else if(instruction[0] == 0x60) {
      printf("addl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
      printf("%s, %s\n",register_names[operandA],register_names[operandB]);
      } 
    else if(instruction[0] == 0x62) {
      printf("andl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
      printf("%s, %s\n",register_names[operandA],register_names[operandB]);
      }
     else if(instruction[0] == 0x61) {
      printf("subl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
        printf("%s, %s\n",register_names[operandA],register_names[operandB]);
       }
       else if(instruction[0] == 0x63) {
      printf("xorl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
        printf("%s, %s\n",register_names[operandA],register_names[operandB]);
         }
        else if(instruction[0] == 0x20) {
      printf("rrmovl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
     // printf("%d,%d\n",operandA,operandB);
        printf("%s, %s\n",register_names[operandA],register_names[operandB]);
          }
          else if(instruction[0] == 0x21) {
      printf("cmovle ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
     // printf("%d,%d\n",operandA,operandB);
        printf("%s, %s\n",register_names[operandA],register_names[operandB]);
            }
            else if(instruction[0] == 0x23) {
      printf("cmove ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
        printf("%s, %s\n",register_names[operandA],register_names[operandB]);
              }
              else if(instruction[0] == 0x22) {
      printf("cmovl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
    
        printf("%s, %s\n",register_names[operandA],register_names[operandB]);
                }
        else if(instruction[0] == 0x24) {
      printf("cmovne ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
        printf("%s, %s\n",register_names[operandA],register_names[operandB]);
          }
          else if(instruction[0] == 0x26) {
      printf("cmovg ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
     printf("%s, %s\n",register_names[operandA],register_names[operandB]);
            }
            else if(instruction[0] == 0x25) {
      printf("cmovge ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
      int operandB = instruction[1]%0x10;
        printf("%s, %s\n",register_names[operandA],register_names[operandB]);       //Only operand A
              }
    
          else if(instruction[0] == 0xA0) {
      printf("pushl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
        printf("%s \n",register_names[operandA]);            //Only operand A
            }
          else if(instruction[0] == 0xB0) {
      printf("popl ");  //Instruction with register operands
       //Check the remaining bytes
      int operandA = instruction[1]>>4;
        printf("%s \n",register_names[operandA]);            //Only operand A
            }
    else if (instruction[0] == 0x30) {
      printf("irmovl ");
      // instruction[0]=30
      // instruction[1]=82
      // instruction[2]=CD
      // instruction[3]=AB
      int operandB = instruction[1] % 0x10; // register ID
      // 30 82 CD AB == AB CD 82 30
      int value = instruction[2] + (instruction[3] << 8) +
                  (instruction[4] << 16) + (instruction[5] << 24);
      {
        printf("$%d",  value);
        printf(", %s\n", register_names[operandB]);
      }
    } else if (instruction[0] == 0x50) {
      printf("mrmovl ");
      // instruction[0]=50
      // instruction[1]=15
      // instruction[2]=F4
      // instruction[3]=FF
      int operandA = instruction[1] / 0x10;
      int operandB = instruction[1] % 0x10; // register ID
      // 50 15 F4 FF == FF F4 15 50
      int value = instruction[2] + (instruction[3] << 8) +
                  (instruction[4] << 16) + (instruction[5] << 24);
 {
        printf("%d", value);
        printf("(%s), %s\n",register_names[operandB], register_names[operandA]);
      }
    } else if (instruction[0] == 0x40) {
      printf("rmmovl ");
      // instruction[0]=40
      // instruction[1]=64
      // instruction[2]=1C
      // instruction[3]=04
      int operandA = instruction[1] / 0x10; // register ID
      int operandB = instruction[1] % 0x10; // register ID
      // 40 64 1C 04 == 04 1C 64 40
      int value = instruction[2] + (instruction[3] << 8) +
                  (instruction[4] << 16) + (instruction[5] << 24);
      {
        printf("%s, %d(%s)\n", register_names[operandA], value, register_names[operandB]);
        
      }
    } else if (instruction[0] == 0x74) {
      printf("jne ");
      // instruction[0]=74
      // instruction[1]=57
      // instruction[2]=C0
      // instruction[3]=00
      
      // 74 57 C0 00 == 00 C0 57 74
      int dest = instruction[1] + (instruction[2] << 8) +
                  (instruction[3] << 16) + (instruction[4] << 24);
      {
        printf("%d\n", dest);
      }
    } else if (instruction[0] == 0x73) {
      printf("je ");
      // instruction[0]=73
      // instruction[1]=74
      // instruction[2]=50
      // instruction[3]=00
      
      // 73 74 50 00 == 00 50 74 73
     int dest = instruction[1] + (instruction[2] << 8) +
                  (instruction[3] << 16) + (instruction[4] << 24);
      {
        printf("%d\n", dest);
        
      }
    } else if (instruction[0] == 0x80) {
      printf("call ");
      // instruction[0]=80
      // instruction[1]=3A
      // instruction[2]=00
      // instruction[3]=00
      
      // 80 3A 00 00 == 00 00 3A 80
     unsigned int dest = instruction[1] + (instruction[2] << 8) +
                  (instruction[3] << 16) + (instruction[4] << 24);
      {
        printf("%u\n", dest);
      }
    } else if (instruction[0] == 0x70) {
      printf("jmp ");
      // instruction[0]=70
      // instruction[1]=74
      // instruction[2]=00
      // instruction[3]=00
      
      // 70 74 00 00 == 00 00 74 70
      unsigned int dest = instruction[1] + (instruction[2] << 8) +
                  (instruction[3] << 16) + (instruction[4] << 24);
      {
        printf("%u\n", dest);
      }
    } else if (instruction[0] == 0x30) {
      printf("irmovl ");
      // instruction[0]=30
      // instruction[1]=83
      // instruction[2]=FF
      // instruction[3]=FF
      int operandA = instruction[1] / 0x10; // register ID
      int operandB = instruction[1] % 0x10; // register ID
      // 30 83 FF FF == FF FF 83 30
      int value = instruction[2] + (instruction[3] << 8) +
                  (instruction[4] << 16) + (instruction[5] << 24);
      {
        printf("%d\n", value);
      }
    } else if (instruction[0] == 0x75) {
      printf("jge ");
      // instruction[0]=75
      // instruction[1]=70
      // instruction[2]=A0
      // instruction[3]=00
      
      // 75 70 A0 00 == 00 A0 70 75
      unsigned int dest = instruction[1] + (instruction[2] << 8) +
                  (instruction[3] << 16) + (instruction[4] << 24);
      {
        printf("%u\n", dest);
      }
    } else if (instruction[0] == 0x72) {
      printf("jl ");
      // instruction[0]=72
      // instruction[1]=74
      // instruction[2]=00
      // instruction[3]=00
      
      // 72 74 00 00 == 00 00 74 72
      unsigned int dest = instruction[1] + (instruction[2] << 8) +
                  (instruction[3] << 16) + (instruction[4] << 24);
      {
        printf("%u\n", dest);
      }
    } else if (instruction[0] == 0x71) {
      printf("jle ");
      // instruction[0]=71
      // instruction[1]=80
      // instruction[2]=00
      // instruction[3]=00
    
      // 71 80 00 00 == 00 00 80 71
     unsigned int dest = instruction[1] + (instruction[2] << 8) +
                  (instruction[3] << 16) + (instruction[4] << 24);
      {
        printf("%u\n", dest);
      }
    } else if (instruction[0] == 0x76) {
      printf("jg ");
      // instruction[0]=76
      // instruction[1]=10
      // instruction[2]=A0
      // instruction[3]=00
      
      // 76 10 A0 00 == 00 A0 10 76
     unsigned int dest = instruction[1] + (instruction[2] << 8) +
                  (instruction[3] << 16) + (instruction[4] << 24);
      {
        printf("%u\n", dest);
      }
    } else if (instruction[0] == 0x00) {
      printf("halt\n");
      // instruction[0]=00
      // instruction[1]=00
      // instruction[2]=00
      // instruction[3]=00
    }
  }
  fclose(pFile);

  return 0;
}

// This function converts a line of machine code read from the text file
// into machine byte code.
// The machine code is stored in an unsigned char array.
int convertStrToByteCode(const char *str, unsigned char inst[], int size) {
  int numHexDigits = 0;
  char *endstr;
  // Each instruction should consist of at most 12 hex digits
  numHexDigits = strlen(str) - 1;
  // Convert the string to integer, N.B. this integer is in decimal
  long long value = strtol(str, &endstr, 16);

  int numBytes = numHexDigits >> 1;
  int byteCount = numHexDigits >> 1;

  while (byteCount > 0) {
    unsigned long long mask = 0xFF;
    unsigned long shift = (numBytes - byteCount) << 3;

    inst[byteCount - 1] = (value & (mask << shift)) >> shift;
    byteCount--;
  }

  // Return the size of the instruction in bytes
  return numHexDigits >> 1;
}
