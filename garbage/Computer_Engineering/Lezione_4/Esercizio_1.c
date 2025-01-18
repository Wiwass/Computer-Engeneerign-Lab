#include <stdio.h>

int recursive(int n){
	if(n==0){
		
		return 0;
	
	}
	else{
		
		return n%10+recursive(n/10);
	
	}
	
}

int main(){
int x = recursive(10);
printf("x is %d",x);


return 0;	
}



