#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) 
{
    int max_position=0;
    int min_position=0;
    
    if(argc==1)
        return 0;
    int x[argc-1];
    for(int i=0;i<argc-1;i++){
    	
        x[i]=atoi(argv[i+1]); // uso atoi al posto di strol perchè non ha senso complicarsi la vita e non so esattamente come vengano passati sull'argv gli argomenti
        
        if ( x[i] > x[max_position] )
            max_position=i;

        if ( x[i] < x[min_position] )
            min_position=i;
 
	}
    
    int temp;
    for(int i=0;i<argc-1;i++){
        for(int j=i; j<argc-1;j++){
            if(x[i]>x[j]){
                temp=x[j];
                x[j]=x[i];
                x[i]=temp;
            }
        }
    }
    
    printf("%d\n",max_position);
    printf("%d\n",min_position);
    
    for (int i = 0 ; i < argc-1 ; i++)
        printf ("%d ", x[i]);

    return 0;
}
