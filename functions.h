#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"

void removeSpaces(char *str);
char*** readData(char* fp_source_name_1);
char* populateControlLinesMemory(char* fp_source_name_2);
void writeInstructions(char ** instruction, char* error, bool* created_1, char* fp_output_name_1);
void writeRegisters(reg ** registersMemory, char ** instruction, bool* created_2, char* fp_output_name_2);
reg** populateRegisters();





#endif
