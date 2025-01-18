#include <stdio.h>

int gcd(int a, int b){
	if(b==0){
		return a;
	}
	else{
		return gcd(b,a%b);
	}
	
}

int main(){
int x=10;
int y=2;
printf("x is %d",gcd(x,y));


return 0;	
}

