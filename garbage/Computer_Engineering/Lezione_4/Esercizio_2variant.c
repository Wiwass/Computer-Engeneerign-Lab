#include <stdio.h>

void recursive(int l,int r,char *s[]){
	if(r<l){
		return;
	}
	char temp=s[l];
	s[l]=s[r];
	s[r]=temp;
	r--;
	l++;
	return recursive(l,r,s);
	
}

int main(){
char s[16] ="stringa di prova";
char *pointer[] = &s;
recursive(0,sizeof(s)-1,pointer);



return 0;	
}
