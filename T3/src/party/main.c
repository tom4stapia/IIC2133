#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_arguments(int argc, char **argv) {
    if (argc != 3) {
        printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
        printf("Donde:\n");
        printf("\tINPUT es la ruta del archivo de input\n");
        printf("\tOUTPUT es la ruta del archivo de output\n");
      
        return false;
    }

    return true;
}

unsigned long max(unsigned long a, unsigned long b) {
    return a >= b ? a : b;
}

unsigned long maximo_oro(unsigned long* pueblos, int pueblo, unsigned long* soluciones) {
    if (pueblo < 0) {
        return 0;
    }
    if (soluciones[pueblo] != 0) {
        return soluciones[pueblo];
    }
    soluciones[pueblo] = max(maximo_oro(pueblos, pueblo - 1, soluciones), maximo_oro(pueblos, pueblo - 3, soluciones) + pueblos[pueblo]);
    return soluciones[pueblo];
}

int main(int argc, char **argv) {
    if (!check_arguments(argc, argv)) return 1;

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");
    int cantidadPueblos;
    fscanf(input_file, "%d", &cantidadPueblos);
    unsigned long *pueblos = calloc(cantidadPueblos, sizeof(unsigned long));
    unsigned long *soluciones = calloc(cantidadPueblos, sizeof(unsigned long));
    for (int i = 0; i < cantidadPueblos; i++) {
        fscanf(input_file, "%ld ", &pueblos[i]);
    }
    fprintf(output_file, "%ld", maximo_oro(pueblos, cantidadPueblos - 1, soluciones));
    free(pueblos);
    free(soluciones);
    fclose(input_file);
    fclose(output_file);

    return 0;
}
