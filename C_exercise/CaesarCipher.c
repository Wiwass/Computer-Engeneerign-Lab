/* CaesarCipher.c
Given a string, transform it in a new string, in which every character is located OFFSET positions further in the alphabet
The alphabet considered is:
ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
The alphabet is cyclical: after the 'z' there is the 'A'
Two arguments are passed: argv[1] is the string to ve converted, argv[2] is the offset
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
	short int curr, cnew;
	short int offset = 0;
	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	short int length = (short int)strlen(alphabet);
	//printf("Alphabet length: %d\n", length);
	if (argc != 3)
	{
		printf("Error: usage %s string_to_convert offset\n", argv[0]);
		exit(1);
	}
	printf("String to be converted: %s\n", argv[1]);
	offset = (short int)strtol(argv[2], NULL, 10);
	printf("offset:%d\n", offset);
	printf("String length:%d\n", (int)strlen(argv[1]));
	//test offset value
	if (offset < (-length) || offset > length)
	{
		printf("Error: offset shall be between -%d and %d\n", length, length);
		exit(2);
	}
	bool found = false;
	for (int i = 0; i < strlen(argv[1]); i++)
	{
		found = false;
		curr = argv[1][i];
		for (int k = 0; k < length; k++)
		{
			if (alphabet[k] == curr)
			{
				k += offset;
				if (k >= length)
					k -= length;
				else if (k < 0)
					k += length;
				cnew = alphabet[k];
				printf("%c", cnew);
				found = true;
				break;
			}
		}
		if (!found)
			printf("%c", curr);
	}
	printf("\n");
	exit(0);
}

