#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "functions.h"

#define REGISTERSNUMBER 26

void removeSpaces(char *str)
{
    // To keep track of non-space character count
    int count = 0;

    // Traverse the given string. If current character
    // is not space, then place it at index 'count++'
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; // here count is
                       // incremented
    str[count] = '\0';
}

char*** readData(char* fp_name)
{
	FILE *fp = NULL;
	int size = 0;
	int count = 0;
	int linesNumber = 0;
	int lineLen = 1;
	char* dataFileChar = NULL;
	char* temp = NULL;
	char* token = NULL;
	char** lines = NULL;
	char* token2 = NULL;
	char* temp2 = NULL;

	fp = fopen (fp_name, "r" );

    if (fp==NULL)
    {
        fputs ("File error",stderr); exit (1);
    }

	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	rewind(fp);

	dataFileChar = malloc(sizeof(char)*(size+1));
	fread(dataFileChar,sizeof(char), size, fp);
	fclose(fp);
    dataFileChar[size] = '\0';
	//Se recorre el char* para encontrar la cantidad de palabras
	for (int i = 0; i < size ; ++i)
	{
		if(dataFileChar[i] == '\n' || dataFileChar[i] == '\0')
		{
			linesNumber++;
		}
	}

	//Se asigna memoria para cada linea dentro del arreglo
	lines = (char**)malloc(sizeof(char*)*(linesNumber+1));

	//Se asigna memoria para cada linea dentro del arreglo
	linesNumber = 0;
	for (int i = 0; i <= size; ++i)
	 {
	 	if(dataFileChar[i] == '\n' || dataFileChar[i] == '\0')
		{
			lines[linesNumber] = malloc(sizeof(char)*(lineLen));
			linesNumber++;
			lineLen = 1;
		}

		else if(dataFileChar[i] != '\n')
		{
			lineLen++;;
		}
	}

	//Se separan las palabras por \n
	temp = malloc(sizeof(char)*(size+1));
	strcpy(temp,dataFileChar);
	token = strtok(temp, "\n");

	while(token != NULL)
	{
		lines[count] = token;
        lines[count][strlen(token)-1] = '\0';
		token = strtok(NULL, "\n");
		count++;
	}

	char*** registers = malloc(sizeof(char**)*(linesNumber+1));
	char** reg = NULL;
    count = 1;
    char* linesNumberStr = malloc(sizeof(char)*5);
    sprintf(linesNumberStr, "%d", linesNumber);
    linesNumberStr[strlen(linesNumberStr)] = '\0';

    char** linesNumberStrArray = malloc(sizeof(char*)*1);
    linesNumberStrArray[0] = linesNumberStr;
    registers[0] = linesNumberStrArray;
	for (int i = 0; i < linesNumber; i++)
	{
		temp2 = malloc(sizeof(char)*(size+1));
		strcpy(temp2,lines[i]);
        token2 = strtok(temp2, " ");
        reg = malloc(sizeof(char*)*(strlen(lines[i])));

        int count2 = 0;
		while(token2 != NULL)
		{
            if (token2 == NULL) {
                break;
            }
            char * variable = malloc(sizeof(char)*(strlen(token2)));
            removeSpaces(token2);
            strcpy(variable,token2);
            variable[strlen(variable)] = '\0';
            reg[count2] = variable;
			token2 = strtok(NULL, ",");
            count2++;
		}

		registers[count] = reg;
        count++;
	}

    return registers;
}

char* populateControlLinesMemory(char* fp_name)
{
    char*** controlLines = NULL;
    controlLines = readData(fp_name);
    char* controlLinesMemory = malloc(sizeof(char)*9);
    for (int i = 1; i < atoi(controlLines[0][0])+1; i++)
    {
        if (strcmp(controlLines[i][0],"Regdst") == 0 || strcmp(controlLines[i][0],"regdst") == 0)
        {
            controlLinesMemory[0] = controlLines[i][1][0];
        }

        else if (strcmp(controlLines[i][0],"Jump") == 0 || strcmp(controlLines[i][0],"jump") == 0)
        {
            controlLinesMemory[1] = controlLines[i][1][0];
        }

        else if (strcmp(controlLines[i][0],"Branch") == 0 || strcmp(controlLines[i][0],"branch") == 0)
        {
            controlLinesMemory[2] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Memread") == 0 || strcmp(controlLines[i][0],"memread") == 0)
        {
            controlLinesMemory[3] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Memtoreg") == 0 || strcmp(controlLines[i][0],"memtoreg") == 0)
        {
            controlLinesMemory[4] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Aluop") == 0 || strcmp(controlLines[i][0],"aluop") == 0)
        {
            controlLinesMemory[5] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Memwrite") == 0 || strcmp(controlLines[i][0],"memwrite") == 0)
        {
            controlLinesMemory[6] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Alusrc") == 0 || strcmp(controlLines[i][0],"alusrc") == 0)
        {
            controlLinesMemory[7] =controlLines[i][1][0];
        }

        else if (strcmp(controlLines[i][0],"Regwrite") == 0 || strcmp(controlLines[i][0],"regwrite") == 0)
        {
            controlLinesMemory[8] = controlLines[i][1][0];
        }
    }

    return controlLinesMemory;
}

void writeInstructions(char ** instruction, char* error)
{
    FILE *fp;
    fp=fopen("salida_1.txt", "a");
    if(fp == NULL)
    {
        fputs ("File error",stderr);
        exit (1);
    }

    if (strcmp(error,"") == 0)
    {
        if (strcmp(instruction[0],"j") == 0 || strcmp(instruction[0],"J") == 0 )
        {
            fprintf(fp,"%s %s\n", instruction[0], instruction[1]);
        }
    }

    else
    {
        printf("%s\n",error);
        fprintf(fp, "%s\n", error);
        exit(1);
    }

    fclose(fp);
}

reg** populateRegisters()
{
    reg ** registers = malloc(sizeof(reg*)*27);

    reg * $sp = malloc(sizeof(reg));
    $sp->value = 0;
    $sp->name = malloc(sizeof(char)*7);
    strcpy($sp->name,"$sp\0");
    registers[0] = $sp;

    reg * $at = malloc(sizeof(reg));
    $at->value = 0;
    $at->name = malloc(sizeof(char)*7);
    strcpy($at->name,"$at\0");
    registers[1] = $at;

    reg * $zero = malloc(sizeof(reg));
    $zero->value = 0;
    $zero->name = malloc(sizeof(char)*7);
    strcpy($zero->name,"$zero\0");
    registers[2] = $zero;

    reg * $v0 = malloc(sizeof(reg));
    $v0->value = 0;
    $v0->name = malloc(sizeof(char)*7);
    strcpy($v0->name,"$v0\0");
    registers[3] = $v0;

    reg * $v1 = malloc(sizeof(reg));
    $v1->value = 0;
    $v1->name = malloc(sizeof(char)*7);
    strcpy($v1->name,"$v1\0");
    registers[4] = $v1;

    reg * $a0 = malloc(sizeof(reg));
    $a0->value = 0;
    $a0->name = malloc(sizeof(char)*7);
    strcpy($a0->name,"$a0\0");
    registers[5] = $a0;

    reg * $a1 = malloc(sizeof(reg));
    $a1->value = 0;
    $a1->name = malloc(sizeof(char)*7);
    strcpy($a1->name,"$a1\0");
    registers[6] = $a1;

    reg * $a2 = malloc(sizeof(reg));
    $a2->value = 0;
    $a2->name = malloc(sizeof(char)*7);
    strcpy($a2->name,"$a2\0");
    registers[7] = $a2;

    reg * $a3 = malloc(sizeof(reg));
    $a3->value = 0;
    $a3->name = malloc(sizeof(char)*7);
    strcpy($a3->name,"$a3\0");
    registers[8] = $a3;

    reg * $t0 = malloc(sizeof(reg));
    $t0->value = 0;
    $t0->name = malloc(sizeof(char)*7);
    strcpy($t0->name,"$t0\0");
    registers[9] = $t0;

    reg * $t1 = malloc(sizeof(reg));
    $t1->value = 0;
    $t1->name = malloc(sizeof(char)*7);
    strcpy($t1->name,"$t1\0");
    registers[10] = $t1;

    reg * $t2 = malloc(sizeof(reg));
    $t2->value = 0;
    $t2->name = malloc(sizeof(char)*7);
    strcpy($t2->name,"$t2\0");
    registers[11] = $t2;

    reg * $t3 = malloc(sizeof(reg));
    $t3->value = 0;
    $t3->name = malloc(sizeof(char)*7);
    strcpy($t3->name,"$t3\0");
    registers[12] = $t3;

    reg * $t4 = malloc(sizeof(reg));
    $t4->value = 0;
    $t4->name = malloc(sizeof(char)*7);
    strcpy($t4->name,"$t4\0");
    registers[13] = $t4;

    reg * $t5 = malloc(sizeof(reg));
    $t5->value = 0;
    $t5->name = malloc(sizeof(char)*7);
    strcpy($t5->name,"$t5\0");
    registers[14] = $t5;

    reg * $t6 = malloc(sizeof(reg));
    $t6->value = 0;
    $t6->name = malloc(sizeof(char)*7);
    strcpy($t6->name,"$t6\0");
    registers[15] = $t6;

    reg * $t7 = malloc(sizeof(reg));
    $t7->value = 0;
    $t7->name = malloc(sizeof(char)*7);
    strcpy($t7->name,"$t7\0");
    registers[16] = $t7;

    reg * $t8 = malloc(sizeof(reg));
    $t8->value = 0;
    $t8->name = malloc(sizeof(char)*7);
    strcpy($t8->name,"$t8\0");
    registers[17] = $t8;

    reg * $t9 = malloc(sizeof(reg));
    $t9->value = 0;
    $t9->name = malloc(sizeof(char)*7);
    strcpy($t9->name,"$t9\0");
    registers[18] = $t9;

    reg * $s0 = malloc(sizeof(reg));
    $s0->value = 0;
    $s0->name = malloc(sizeof(char)*7);
    strcpy($s0->name,"$s0\0");
    registers[19] = $s0;

    reg * $s1 = malloc(sizeof(reg));
    $s1->value = 0;
    $s1->name = malloc(sizeof(char)*7);
    strcpy($s1->name,"$s1\0");
    registers[20] = $s1;

    reg * $s2 = malloc(sizeof(reg));
    $s2->value = 0;
    $s2->name = malloc(sizeof(char)*7);
    strcpy($s2->name,"$s2\0");
    registers[21] = $s2;

    reg * $s3 = malloc(sizeof(reg));
    $s3->value = 0;
    $s3->name = malloc(sizeof(char)*7);
    strcpy($s3->name,"$s3\0");
    registers[22] = $s3;

    reg * $s4 = malloc(sizeof(reg));
    $s4->value = 0;
    $s4->name = malloc(sizeof(char)*7);
    strcpy($s4->name,"$s4\0");
    registers[23] = $s4;

    reg * $s5 = malloc(sizeof(reg));
    $s5->value = 0;
    $s5->name = malloc(sizeof(char)*7);
    strcpy($s5->name,"$s5\0");
    registers[24] = $s5;

    reg * $s6 = malloc(sizeof(reg));
    $s6->value = 0;
    $s6->name = malloc(sizeof(char)*7);
    strcpy($s6->name,"$s6\0");
    registers[25] = $s6;

    reg * $s7 = malloc(sizeof(reg));
    $s7->value = 0;
    $s7->name = malloc(sizeof(char)*7);
    strcpy($s7->name,"$s7\0");
    registers[26] = $s7;

    return registers;

}

void writeRegisters(reg ** registersMemory, char ** instruction)
{
    FILE *fp;
    fp=fopen("salida_2.txt", "r");
    if(fp == NULL)
    {
        fp=fopen("salida_2.txt", "a");
        fprintf(fp, "Instrucciones         $sp $at $zero $v0 $v1 $a0 $a1 $a2 $a3 $t0 $t1 $t2 $t3 $t4 $t5 $t6 $t7 $t8 $t9 $s0 $s1 $s2 $s3 $s4 $s5 $s6 $s7");
    }

    else
    {
        fclose(fp);
        fp=fopen("salida_2.txt", "a");

        if (strcmp(instruction[0],"j") == 0 || strcmp(instruction[0],"J") == 0 )
        {
            //Do nothing;
        }


    }

    fclose(fp);
}

int main(int argc, char** argv)
{
    char* controlLinesMemory;
    //regdst,jump,branch,memread,memtoreg,aluop,memwrite,alusrc,regwrite;
    reg ** registersMemory;
    //$sp,$at,$zero,$v0,$v1,$a0,$a1,$a2,$a3,$t0,$t1,$t2,$t3,$t4,$t5,$t6,$t7,$t8,$t9,$s0,$s1,$s2,$s3,$s4,$s5,$s6,$s7;
    char*** instructions = NULL;
    int* virtualMemory = NULL;
	instructions = readData("entrada1.txt");
    virtualMemory = calloc(1025,sizeof(int));
    registersMemory = malloc(sizeof(reg*)*27);
    char* error = malloc(sizeof(char)*50);
    strcpy(error,"");
    registersMemory = populateRegisters();
    controlLinesMemory = populateControlLinesMemory("entrada2.txt");

    for (int i = 1; i < atoi(instructions[0][0]); i++)
    {
        if (strcmp(instructions[i][0],"j") == 0 || strcmp(instructions[i][0],"J") == 0)
        {
            if (controlLinesMemory[1] == 'x')
            {
                char * label = malloc(sizeof(char)*(strlen(instructions[i][1])+2));
                strcat(label,instructions[i][1]);
                strcat(label, ":");
                int j;
                for (j = 0; j < atoi(instructions[0][0]); j++)
                {
                    if (strcmp(instructions[j][0],label) == 0)
                    {
                        break;
                    }
                }

                if (j == atoi(instructions[0][0]))
                {
                    strcpy(error,"No existe la etiqueta ");
                    strcat(error,instructions[i][1]);
                    writeInstructions(instructions[i], error);
                    writeRegisters(registersMemory,instructions[i]);
                }
                writeInstructions(instructions[i], error);
                writeRegisters(registersMemory,instructions[i]);
                i = j;
            }

            else if (controlLinesMemory[1] == '0')
            {
                continue;
            }
        }

        else if (strcmp(instructions[i][0],"subi") == 0)
        {
            int variable_1 = 0;
            int variable_2 = 0;
            int result = 0;
            printf("%d\n",registersMemory[11]->value);
            int j;
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                if (strcmp(instructions[i][2],registersMemory[j]->name) == 0)
                {
                    break;
                }
            }
            if (j == REGISTERSNUMBER)
            {
                strcpy(error,"No existe la variable ");
                strcat(error,instructions[i][2]);
                writeInstructions(instructions[i], error);
                writeRegisters(registersMemory,instructions[i]);
            }

            variable_1 = registersMemory[j]->value;
            variable_2 = atoi(instructions[i][3]);
            result = variable_1 - variable_2;

            for (int j = 0; j < REGISTERSNUMBER; j++)
            {
                //printf("%d, j: %d\n",result,j);
                // printf("%d\n", strcmp(instructions[i][1],registersMemory[j]->name));
                // printf("%s\n",instructions[i][1]);
                // printf("%s\n",registersMemory[j]->name);
                 printf("%d\n",j );
                // // printf("%s\n\n","/////////////////////END" );
                printf("%s\n", instructions[i][1]);
                printf("%s\n", registersMemory[j]->name );
                 printf("%s\n\n","/////////////////////END" );

                if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
                {
                    //printf("%d\n",result);
                    registersMemory[j] = result;
                    break;
                }
            }

            writeInstructions(instructions[i], error);
            writeRegisters(registersMemory,instructions[i]);
        }
        //printf("%d\n",i );
        //printf("%s\n", instructions[i][0]);
    }

    return 0;


}
