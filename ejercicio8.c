#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *calcular_factorial(void *arg){
int n = *((int*)arg);
long long *resultado = malloc(sizeof(long long));
*resultado = 1;
for(int i=1;i<=n;i++){*resultado *=i;}
pthread_exit((void*)resultado);
}

int main(){
pthread_t hilos[4];
int numeros[4]={3,5,7,10};
for(int i=0;i<4;i++){
pthread_create(&hilos[i],NULL,calcular_factorial,(void*)&numeros[i]);}
for(int i=0;i<4;i++){
void *retorno;
pthread_join(hilos[i],&retorno);
long long res =* ((long long*)retorno);
printf("Factorial de %d es: %lld\n",numeros[i],res);
free(retorno);}
return 0;
}
