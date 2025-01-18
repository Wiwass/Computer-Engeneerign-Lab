#include <stdio.h>
int main()
{	
	char result[4]="AaZz";

	for(int i=0;i<sizeof(result);i++){
		if(87<=result[i]<=90){
			result[i]=97+90-result[i]+3;  
			printf("%c",result[i]);	
			continue;
		}
		if(119<=result[i]<=122){
			result[i]=65+122-result[i]+3;
			printf("%c",result[i]);
			continue;
		}
		
		result[i]=result[i]+3;
		printf("%c",result[i]);	
	}
	printf("\n");
}
