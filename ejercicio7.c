#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 10
#define ITERACIONES 100000
int cont_compartido=0;

void* incremento_sinproteccion(void *arg){
for(int i=0;i<ITERACIONES;i++){cont_compartido++;}
return NULL;}

int main(){
pthread_t hilos[NUM_HILOS];
for(int i =0;i<NUM_HILOS;i++){
pthread_create(&hilos[i],NULL,incremento_sinproteccion,NULL);}

for(int i=0;i<NUM_HILOS;i++){pthread_join(hilos[i],NULL);}
printf("Valor incial: %d\n",NUM_HILOS*ITERACIONES);
printf("Valor luego de race condition: %d\n",cont_compartido);
return 0;
}
