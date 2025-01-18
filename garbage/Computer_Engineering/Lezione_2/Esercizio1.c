#include <stdio.h>
int main()
{	
	int result[30];
	result[0]=1;
	result[1]=1;
	result[2]=1;
	for(int i=3;i<30;i++){
		result[i]=result[i-1]+result[i-3];

	}
	for(int i=0;i<30;i++){
		printf("%d\n",result[i]);	
	}
}
