#include <stdio.h>
#include <stdlib.h>

//This is the help function that reads y86 binary code from a file
unsigned int loadBinFromFile(const char *filename, unsigned char memory[], unsigned int memsize);

int main(int argc, char **argv)
{
  unsigned int MAX_MEMSIZE = 4096;
  unsigned char memory[MAX_MEMSIZE]; //This array represents the 4KB memory space
  unsigned int PC = 0;               //This is the initial program counter address

  if (argc < 2)
  {
    printf("Usage: please specify a y86 binary program file in the argument.\n");
    return -1;
  }

  unsigned int program_size = loadBinFromFile(argv[1], memory, MAX_MEMSIZE);

  if (program_size == 0)
    return 0;

  //TODO: Implement your disassembler from here
  //At the moment, it simply display each byte from the memory.
  while (PC < program_size)
  {
    if (memory[PC] == 0x10) {
    printf("nop \n");    //Instruction with no operand
    PC+=1;
    }
    else if(memory[PC] == 0x90) {
      printf("ret \n");     //Instruction with no operand
      PC+=1;
    }
    else if(memory[PC] == 0x60) {
      printf("addl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
      printf("%s, %s\n");
     PC+=2;
      } 
    else if(memory[PC] == 0x62) {
      printf("andl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
      printf("%s, %s\n");
      PC+=2;}
     else if(memory[PC] == 0x61) {
      printf("subl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
        printf("%s, %s\n");
       PC+=2;}
       else if(memory[PC] == 0x63) {
      printf("xorl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
        printf("%s, %s\n");
        PC+=2; }
        else if(memory[PC] == 0x20) {
      printf("rrmovl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
          {
          printf("%s, %s\n");
          PC +=2;
          }
          }
    else if(memory[PC] == 0x21) {
          printf("cmovle ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
     // printf("%d,%d\n",operandA,operandB);
        printf("%s, %s\n");
            PC+=2;
            }
            else if(memory[PC] == 0x23) {
      printf("cmove ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
        printf("%s, %s\n");
          PC+=2;  }
              else if(memory[PC] == 0x22) {
      printf("cmovl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
      printf("%s, %s\n");
           PC+=2;     }
        else if(memory[PC] == 0x24) {
      printf("cmovne ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
        printf("%s, %s\n");
         PC+=2; }
          else if(memory[PC] == 0x26) {
      printf("cmovg ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
     printf("%s, %s\n");
          PC+=2;  }
            else if(memory[PC] == 0x25) {
      printf("cmovge ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
      int operandB = memory[PC+1]%0x10;
        printf("%s, %s\n");       //Only operand A
            PC+=2;  }
    
          else if(memory[PC] == 0xA0) {
      printf("pushl ");    //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC+1]>>4;
        printf("%s \n");            //Only operand A
          PC+=2;  }
          else if(memory[PC] == 0xB0) {
      printf("popl ");  //Instruction with register operands
       //Check the remaining bytes
      int operandA = memory[PC]>>4;
        printf("%s \n");            //Only operand A
           PC+=2;
            }
    else if (memory[PC] == 0x30) {
      printf("irmovl ");
      // instruction[0]=30
      // instruction[1]=82
      // instruction[2]=CD
      // instruction[3]=AB
      int operandB = memory[PC+1] % 0x10; // register ID
      // 30 82 CD AB == AB CD 82 30
      int dest = memory[PC+2] + (memory[PC+3] << 8) +
                  (memory[PC+4] << 16) + (memory[PC+5] << 24);
      {
        printf("$%d",dest);
        printf(", %s\n");
        PC+=6;
      }
    } else if (memory[PC] == 0x50) {
      printf("mrmovl ");
      // instruction[0]=50
      // instruction[1]=15
      // instruction[2]=F4
      // instruction[3]=FF
      int operandA = memory[PC+1] / 0x10;
      int operandB = memory[PC+1] % 0x10; // register ID
      // 50 15 F4 FF == FF F4 15 50
      int dest = memory[2] + (memory[3] << 8) +
                  (memory[4] << 16) + (memory[5] << 24);
 {
        printf("%d", dest);
        printf("(%s), %s\n");
      PC+=6;}
    } else if (memory[PC] == 0x40) {
      printf("rmmovl ");
      // instruction[0]=40
      // instruction[1]=64
      // instruction[2]=1C
      // instruction[3]=04
      int operandA = memory[PC+1] / 0x10; // register ID
      int operandB = memory[PC+1] % 0x10; // register ID
      // 40 64 1C 04 == 04 1C 64 40
      int dest = memory[2] + (memory[3] << 8) +
                  (memory[4] << 16) + (memory[5] << 24);
      {
        printf("%s, %d(%s)\n",dest);
        PC+=6;
      }
    } else if (memory[PC] == 0x74) {
      printf("jne ");
      // instruction[0]=74
      // instruction[1]=57
      // instruction[2]=C0
      // instruction[3]=00
      
      // 74 57 C0 00 == 00 C0 57 74
      int dest = memory[1] + (memory[2] << 8) +
                  (memory[3] << 16) + (memory[4] << 24);
      {
        printf("%d\n", dest);
        PC+=5;      }
    } else if (memory[PC] == 0x73) {
      printf("je ");
      // instruction[0]=73
      // instruction[1]=74
      // instruction[2]=50
      // instruction[3]=00
      
      // 73 74 50 00 == 00 50 74 73
     int dest = memory[1] + (memory[2] << 8) +
                  (memory[3] << 16) + (memory[4] << 24);
      {
        printf("%d\n", dest);
        PC+=5;
      }
    } else if (memory[PC] == 0x80) {
      printf("call");
      // instruction[0]=80
      // instruction[1]=3A
      // instruction[2]=00
      // instruction[3]=00
      
      // 80 3A 00 00 == 00 00 3A 80
     unsigned int dest = memory[1] + (memory[2] << 8) +
                  (memory[3] << 16) + (memory[4] << 24);
      {
        printf("%u\n", dest);
        PC+=5;
      }
    } else if (memory[PC] == 0x70) {
      printf("jmp ");
      // instruction[0]=70
      // instruction[1]=74
      // instruction[2]=00
      // instruction[3]=00
      
      // 70 74 00 00 == 00 00 74 70
      unsigned int dest = memory[1] + (memory[2] << 8) +
                  (memory[3] << 16) + (memory[4] << 24);
      {
        printf("%u\n", dest);
        PC+=5;
      }
    } else if (memory[PC] == 0x30) {
      printf("irmovl ");
      // instruction[0]=30
      // instruction[1]=83
      // instruction[2]=FF
      // instruction[3]=FF
      int operandA = memory[PC+1] / 0x10; // register ID
      int operandB = memory[PC+1] % 0x10; // register ID
      // 30 83 FF FF == FF FF 83 30
      int dest = memory[2] + (memory[3] << 8) +
                  (memory[4] << 16) + (memory[5] << 24);
      {
        printf("%d\n", dest);
        PC+=6;
      }
    } else if (memory[PC] == 0x75) {
      printf("jge ");
      // instruction[0]=75
      // instruction[1]=70
      // instruction[2]=A0
      // instruction[3]=00
      
      // 75 70 A0 00 == 00 A0 70 75
      unsigned int dest = memory[1] + (memory[2] << 8) +
                  (memory[3] << 16) + (memory[4] << 24);
      {
        printf("%u\n", dest);
        PC+=5;
      }
    } else if (memory[PC] == 0x72) {
      printf("jl ");
      // instruction[0]=72
      // instruction[1]=74
      // instruction[2]=00
      // instruction[3]=00
      
      // 72 74 00 00 == 00 00 74 72
      unsigned int dest = memory[1] + (memory[2] << 8) +
                  (memory[3] << 16) + (memory[4] << 24);
      {
        printf("%u\n", dest);
        PC+=5;
      }
    } else if (memory[PC] == 0x71) {
      printf("jle ");
      // instruction[0]=71
      // instruction[1]=80
      // instruction[2]=00
      // instruction[3]=00
    
      // 71 80 00 00 == 00 00 80 71
     unsigned int dest = memory[1] + (memory[2] << 8) +
                  (memory[3] << 16) + (memory[4] << 24);
      {
        printf("%u\n", dest);
        PC+=5;
      }
    } else if (memory[PC] == 0x76) {
      printf("jg ");
      // instruction[0]=76
      // instruction[1]=10
      // instruction[2]=A0
      // instruction[3]=00
      
      // 76 10 A0 00 == 00 A0 10 76
     unsigned int dest = memory[1] + (memory[2] << 8) +
                  (memory[3] << 16) + (memory[4] << 24);
      {
        printf("%u\n", dest);
        PC+=5;
      }
    } else if (memory[PC] == 0x00) {
      printf("halt\n");
      PC+=1; 
      // instruction[0]=00
      // instruction[1]=00
      // instruction[2]=00
      // instruction[3]=00
    }
  }
  }

  return 0; 


/****************************************************************************
N.B. You do not need to modify or work in this function.
Description:
This function reads in a y86 machine bytecode from file and
store them in an unsigned char array.
******************************************************************************/
unsigned int loadBinFromFile(const char *filename, unsigned char memory[], unsigned int memsize)
{
  unsigned int bytes_read = 0;

  unsigned int file_size = 0;

  FILE *pfile = fopen(filename, "rb");

  if (!pfile)
  {
    printf("Unable to load file %s, please check if the path and name are correct.\n", filename);
    return 0;
  }

  fseek(pfile, 0, SEEK_END);
  file_size = ftell(pfile);
  rewind(pfile);

  if (file_size > memsize)
  {
    printf("Program size exceeds memory size of %d.\n", memsize);
    return 0;
  }

  bytes_read = fread(memory, 1, file_size, pfile);

  if (bytes_read != file_size)
  {
    printf("Bytes read does not match the file size.\n");
    return 0;
  }

  fclose(pfile);

  return bytes_read;
}
