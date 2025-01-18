#include <stdio.h>

int recursive(int n,char s[]){
	if(n==0){
		printf("%c\n",s[n]);
		return 0;
	}
	printf("%c",s[n]);
	n--;
	return recursive(n,s);
	
}

int main(){
char s[16] ="stringa di prova";
recursive(sizeof(s)-1,s);



return 0;	
}

