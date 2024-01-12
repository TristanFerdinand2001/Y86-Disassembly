#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertStrToByteCode(const char *str, unsigned char inst[], int size);

int main(int argc, char **argv) {
  FILE *pFile = NULL;

  char buffer[15];

  if (argc < 2) {
    pFile = fopen("./test1.txt", "r");
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

// y86 opcodes can be disassembled. 
if (instruction[0]==0x10)
{
  printf("nop\n");
}
    else if (instruction[0]==0x90)
{
  printf("ret\n");
}
    else if (instruction[0]==0x60)
{
  printf("addl\n");
}
   else if(instruction[0]==0x62)
{
  printf("andl\n");
  }
   else if(instruction[0]==0x61)
{
  printf("subl\n");
  }
    else if(instruction[0]==0x63)
{
  printf("xorl\n");
  }
     else if (instruction[0]==0x20)
{
  printf("rrmovl\n");
  }
     else if (instruction[0]==0x21)
{
  printf("cmovle\n");
  }
     else if (instruction[0]==0x23)
{
  printf("cmove\n");
  }
     else if (instruction[0]==0x22)
  {
  printf("cmovl\n");
  }
 else if (instruction[0]==0x24)
     {
  printf("cmovne\n");
       }
  else if (instruction[0]==0x26)
  {     
  printf("cmovg\n");
    }
  else if (instruction[0]==0x25)
  {
    printf("cmovge\n");
  }
  else if (instruction[0]==0xA0)
  {
    printf("pushl\n");
  }
  else if (instruction[0]==0xA0)
    {
    printf("popl\n");
  }
  else if (instruction[0]==0xB0)
  {
    printf("popl\n");
  }
  else if (instruction[0]==0x30)
  {
    printf("irmovl\n");
  }
  else if (instruction[0]==0x50)
  {
    printf("mrmovl\n");
  }
    else if (instruction[0]==0x40)
 {
    printf("rmmovl\n");
  }
   else if (instruction[0]==0x74)
  {
    printf("jne\n");
  }
    else if (instruction[0]==0x73)
  {
    printf("je\n");
  }
    else if (instruction[0]==0x80)
  {
    printf("call\n");
  }
     else if (instruction[0]==0x70)
  {
    printf("jmp\n");
  }
     else if (instruction[0]==0x30)
  {
    printf("irmovl\n");
  }
     else if (instruction[0]==0x75)
  {
    printf("jge\n");
  }
      else if (instruction[0]==0x72)
  {
    printf("jl\n");
  }
      else if (instruction[0]==0x71)
  {
    printf("jle\n");
  }
    else if (instruction[0]==0x76)
  {
    printf("jg\n");
  }
      else if (instruction[0]==0x00)
  {
    printf("halt\n");
  }
//Any undisassembled opcode should display as "TODO: undisassembled opcode"
    //printf("TODO: undisassembled opcode. The first byte of the instruction is "
 //          "0x%X\n",
 //     instruction[0]);
  
    }
  fclose(pFile);

  return 0;
}

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
