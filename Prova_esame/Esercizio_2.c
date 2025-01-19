#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struttura del dizionario: [A,B,...,Z,a,b,...,z,#]

int main(int argc, char *argv[]){
	
	FILE* stream = fopen("example.txt", "r");
	
	if (stream == NULL)
	{
		perror("Error opening input file");
		exit(2);
	}
	
	//int debug=0;
	
	char curr;
	int index;
	int total_counter=0;
    int letters_and_numbers[53];
    for(int i=0;i<52;i++){letters_and_numbers[i]=0;}
    
    while (!feof(stream)){
		curr = fgetc(stream);
		//debug++;
		printf("%c",curr);
		if (curr != EOF)
		{
			index=curr;
			total_counter++;
			if(index>=65 && index<=90){
				index=curr-65;
				letters_and_numbers[index]++;
			}
			else if(index>=97 && index<=122){
					index=curr-97+26;
					letters_and_numbers[index]++;
			}
			else{
				letters_and_numbers[52]++;
			}
			
		}
		
	}
	fclose(stream);
}


