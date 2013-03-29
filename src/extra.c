#include <R.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>



void mycpyd(a,len,b)

double *a,*b;
int *len;
{
int i;

/* Rprintf("i (mycpyd):"); */
for(i=0;i<*len;i++){
/* Rprintf("%d ",i);*/
*(b+i)=*(a+i);
}
/* Rprintf("\n"); */

}

void mycpyi(a,len,b)

int *a,*b;
int *len;
{
int i;

/* Rprintf("i (mycpyi):"); */
for(i=0;i<*len;i++){
/* Rprintf("%d ",i); */
*(b+i)=*(a+i);
}
/* Rprintf("\n"); */


}
