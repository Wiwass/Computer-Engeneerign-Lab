#include <stdio.h>
int main(){
	FILE *file = fopen("tester.txt","r");

	if(file == NULL)
		return 1;
		
	int length = 32;
	char buffer[length];
	
	int result[26];
	
	for (int i=0;i<26;i++){
		result[i]=0;
	}
	
	int temp=0;

	while(fscan(file,"%s",buffer)!=EOF){
			if(sizeof(buffer)>=8){
					for(int i=0;i<sizeof(buffer);i++){
							temp=atoi(buffer[i]);
							if (temp>96 && temp<122)
								result[temp-97]++;
					}
		}	
				
			}
		}
	for(int i=0;i<26,i++){
		printf('There are %d occurrences of the character %c',result[i],(97+i));
	}
}
		
		
	//97-122
