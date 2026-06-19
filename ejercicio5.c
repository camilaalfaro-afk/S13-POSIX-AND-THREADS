#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>

int main() {
    struct timespec inicio_total, fin_total;
    struct rusage uso;

    clock_gettime(CLOCK_MONOTONIC, &inicio_total);

    for(int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if(pid < 0) {
            perror("Error"); 
            exit(1);
        } else if(pid == 0) {
            printf("Hijo %d, PID %d, PID del padre %d\n", i+1, getpid(), getppid());
            sleep(2); 
            exit(0);
        }
    }
    for (int i = 0; i < 3; i++) {
        wait(NULL); 
    }
printf("Padre: Todos se han ejecutado.\n");

    clock_gettime(CLOCK_MONOTONIC, &fin_total);
    getrusage(RUSAGE_CHILDREN, &uso);

    double tiempo_total = (fin_total.tv_sec - inicio_total.tv_sec) + 
                          (fin_total.tv_nsec - inicio_total.tv_nsec) / 1e9;

    printf("\nMétricas de Rendimiento\n");
    printf("Tiempo total de ejecución: %f segundos\n", tiempo_total);
    printf("Memoria máxima residente de hijos: %ld KB\n", uso.ru_maxrss);
    printf("Tiempo CPU en modo usuario: %ld.%06ld s\n", uso.ru_utime.tv_sec, uso.ru_utime.tv_usec);
    printf("Tiempo CPU en modo sistema: %ld.%06ld s\n", uso.ru_stime.tv_sec, uso.ru_stime.tv_usec);

    return 0;
}
