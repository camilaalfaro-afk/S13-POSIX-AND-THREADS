#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/resource.h>

typedef struct {
    int id;
    char *mensaje;
} HiloDatos;
void* imprimir_mensaje(void* arg) {
    HiloDatos* datos = (HiloDatos*)arg;
    for (int i = 0; i < 5; i++) {
        printf("Hilo ID %d: %s (Iteracion %d)\n", datos->id, datos->mensaje, i+1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[2];
    struct timespec inicio, fin;
    struct rusage uso;
    HiloDatos datos[2] = {
        {1, "Hola - Primer hilo"},
        {2, "Saludos - Segundo hilo"}
    };
    clock_gettime(CLOCK_MONOTONIC, &inicio); 
    for (int i = 0; i < 2; i++) {
        pthread_create(&hilos[i], NULL, imprimir_mensaje, (void*)&datos[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(hilos[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &fin); 
    getrusage(RUSAGE_SELF, &uso);
    double tiempo_total = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("\nMétricas de Rendimiento\n");
    printf("Tiempo total de ejecución: %f segundos\n", tiempo_total);
    printf("Memoria máxima residente (RSS): %ld KB\n", uso.ru_maxrss);
    printf("Tiempo CPU en modo usuario: %ld.%06ld s\n", uso.ru_utime.tv_sec, uso.ru_utime.tv_usec);
    printf("Tiempo CPU en modo sistema: %ld.%06ld s\n", uso.ru_stime.tv_sec, uso.ru_stime.tv_usec);

    return 0;
}
