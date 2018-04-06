#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE *fp;
	fp = fopen ( "entrada1.txt", "r" );


    if (fp==NULL)
    {
        fputs ("File error",stderr); exit (1);
    }

    while(feof(fp) == 0)
    {
        char buffer[10];
        fgets(buffer,10,fp);
        printf("%c",buffer[0]);
    }

    fclose ( fp );

	return 0;
}
