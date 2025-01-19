// FileEncrypt.cpp : 
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAX_OFFSET 94
#define MIN_OFFSET -94
#define MIN_CHAR 32
#define MAX_CHAR 126
int main(int argc, char* argv[])
{
	char curr, cnew;
	int offset = 0;
	int newchar = 0;
	// check how many arguments have been passed to the program
	if (argc != 3)
	{
		printf("Error: usage %s filename_to_convert offset\n", argv[0]);
		exit(1);
	}
	printf("Filename to be converted: %s\noffset:%s\n", argv[1], argv[2]);
	// compute how many positions the characters in the string shall be moved
	offset = (int)strtol(argv[2], NULL, 10);
	FILE* fi = fopen(argv[1], "r");
	if (fi == NULL)
	{
		perror("Error opening input file");
		exit(2);
	}
	char buffer[100];
	if (tmpnam(buffer) == NULL)
	{
		perror("Error creating unique output filename\n");
		exit(3);
	}
	printf("Output file: %s\n\n", buffer);
	FILE* fo = fopen(buffer, "w");
	if (fo == NULL)
	{
		perror("Error opening output file\n");
		exit(4);
	}
	printf("String after conversion:\n");
	while (!feof(fi))
	{
		curr = fgetc(fi);
		if (curr != EOF)
		{
			newchar = curr + offset;
			if (newchar < MIN_CHAR) // check if the new value is below the acceptable range
			{
				newchar += (MAX_CHAR - MIN_CHAR + 1); // bring the new value back within the acceptable range
			}
			else if (newchar > MAX_CHAR) // check if the new value is above the acceptable range
			{
				newchar -= (MAX_CHAR - MIN_CHAR + 1); // bring the new value back within the acceptable range
			}
			cnew = (char)newchar; // put the new value in a char variable
			printf("%c", cnew); // prints the new value
			if (fputc(cnew, fo) == EOF)
			{
				perror("Error writing to output file\n");
				break;
			}
		}
		else
			break;
	}
	fclose(fi);
	fclose(fo);
	printf("\n");
	exit(0);
}