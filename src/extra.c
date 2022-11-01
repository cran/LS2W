



void mycpyd(double* a,int* len,double* b)
{
int i;

for(i=0;i<*len;i++){

*(b+i)=*(a+i);
}


}

void mycpyi(int* a,int* len,int* b)
{
int i;
for(i=0;i<*len;i++){

*(b+i)=*(a+i);
}



}
