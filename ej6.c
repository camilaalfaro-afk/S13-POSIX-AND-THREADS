#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define ITER 10000

int main() {
    struct timespec inicio, fin;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

#ifdef USE_PRINTF
    FILE *f = fopen("salida_printf.txt", "w");
    for(int i = 0; i < ITER; i++) {
        fprintf(f, "Iteracion %d: Datos de prueba\n", i);
    }
    fclose(f);
#else
    int fd = open("salida_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buf[64];
    for(int i = 0; i < ITER; i++) {
        int len = sprintf(buf, "Iteracion %d: Datos de prueba\n", i);
        write(fd, buf, len);
    }
    close(fd);
#endif

    clock_gettime(CLOCK_MONOTONIC, &fin);
    printf("%f\n", (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9);
    return 0;
}
