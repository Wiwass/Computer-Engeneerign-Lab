#include <stdio.h>
int main()
{
int celsius=0;
float prova=20;
//i rappresents farh
for(int i=1;i<=100;i++){
	celsius= 5 * (i-32) / 9;
	printf("%df\t%dc\t%10.10fp\n", i, celsius,prova/i);
}
}
