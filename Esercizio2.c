#include <stdio.h>
#include <stdlib.h>
int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
int main(int argc, char* argv[]) 
{
    int x[argc];
    for(int i=0;i<argc;i++){
        x[i]=//funzione di traduzione da char a int dell'argv[i]
    }

    qsort (x, sizeof(x)/sizeof(*x), sizeof(*x), comp);
    
    printf("%d\n",x[0]);
    printf("%d\n",x[argc-1]);
    
    for (int i = 0 ; i < 10 ; i++)
        printf ("%d ", x[i]);

    return 0;
}