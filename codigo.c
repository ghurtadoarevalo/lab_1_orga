#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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

	dataFileChar = malloc(sizeof(char)*(size+2));
	fread(dataFileChar,sizeof(char), size, fp);
	fclose(fp);

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
		lines[count] = token + '\0';
		token = strtok(NULL, "\n");
		count++;
	}

	char*** registers = malloc(sizeof(char**)*(linesNumber));
	char** reg = NULL;
    count = 1;
    char* linesNumberStr = malloc(sizeof(char)*5);
    sprintf(linesNumberStr, "%d", linesNumber);
    char** linesNumberStrArray = malloc(sizeof(char*)*1);
    linesNumberStrArray[0] = linesNumberStr;
    registers[0] = linesNumberStrArray;
	for (int i = 0; i < linesNumber-1; i++)
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
            reg[count2] = variable;
			token2 = strtok(NULL, ",");
            count2++;
		}

		registers[count] = reg;
        count++;
	}

    return registers;
}

int main(int argc, char** argv)
{
    char* regdst,jump,branch,memread,memtoreg,aluop,memwrite,alusrc,regwrite;
    int $sp,$at,$zero,$v0,$v1,$a0,$a1,$a2,$a3,$t0,$t1,$t2,$t3,$t4,$t5,$t6,$t7,$t8,$t9,$s0,$s1,$s2,$s3,$s4,$s5,$s6,$s7,$gp,$fp,$ra;
    char*** instructions = NULL;
    char*** controlLines = NULL;
    int * virtualMemory = NULL;
	instructions = readData("entrada1.txt");
    controlLines = readData("entrada2.txt");
    virtualMemory = malloc(sizeof(int)*1024);

    for (int i = 0; i < atoi(controlLines[0][0]); i++)
    {
        if (strcmp(controlLines[i][0],"Regdst") == 0 || strcmp(controlLines[i][0],"regdst") == 0)
        {
            regdst = malloc(sizeof(char)*3);
            strcpy(regdst,controlLines[i][1]);
        }

        else if (strcmp(controlLines[i][0],"Jump") == 0 || strcmp(controlLines[i][0],"jump") == 0)
        {
            jump = malloc(sizeof(char)*3);
            printf("%d\n",jump);
            printf("%s",controlLines[i][1]);

            strcpy(jump,controlLines[i][1]);
            printf("%s\n",jump);
        }

        else if (strcmp(controlLines[i][0],"Branch") == 0 || strcmp(controlLines[i][0],"branch") == 0)
        {
            branch = malloc(sizeof(char)*2);
            strcpy(branch,controlLines[i][1]);
        }

        else if (strcmp(controlLines[i][0],"Memread") == 0 || strcmp(controlLines[i][0],"memread") == 0)
        {
            memread = malloc(sizeof(char)*2);
            strcpy(memread,controlLines[i][1]);
        }

        else if (strcmp(controlLines[i][0],"Memtoreg") == 0 || strcmp(controlLines[i][0],"memtoreg") == 0)
        {
            memtoreg = malloc(sizeof(char)*2);
            strcpy(memtoreg,controlLines[i][1]);
        }

        else if (strcmp(controlLines[i][0],"Aluop") == 0 || strcmp(controlLines[i][0],"aluop") == 0)
        {
            aluop = malloc(sizeof(char)*2);
            strcpy(aluop,controlLines[i][1]);
        }

        else if (strcmp(controlLines[i][0],"Memwrite") == 0 || strcmp(controlLines[i][0],"memwrite") == 0)
        {
            memwrite = malloc(sizeof(char)*2);
            strcpy(memwrite,controlLines[i][1]);
        }

        else if (strcmp(controlLines[i][0],"Alusrc") == 0 || strcmp(controlLines[i][0],"alusrc") == 0)
        {
            alusrc = malloc(sizeof(char)*2);
            strcpy(alusrc,controlLines[i][1]);
        }

        else if (strcmp(controlLines[i][0],"Regwrite") == 0 || strcmp(controlLines[i][0],"regwrite") == 0)
        {
            regwrite = malloc(sizeof(char)*2);
            strcpy(regwrite,controlLines[i][1]);
        }
    }

    printf("%s\n","holaaa" );
    printf("%s\n",regwrite);
    printf("%s\n",alusrc);

    return 0;


}
