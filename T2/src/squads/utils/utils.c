#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

char* encontrarLetrasMasRepetidas(char *cadena, int longitud) {
    int contador[26] = {0};
    int maxCount = 0;
    int numLetrasRepetidas = 0;
    for (int i = 0; i < longitud; i++) {
        char letra = cadena[i];
        if (letra >= 'A' && letra <= 'Z') {
            int indice = letra - 'A';
            contador[indice]++;
            if (contador[indice] > maxCount) {
                maxCount = contador[indice];
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        if (contador[i] == maxCount) {
            numLetrasRepetidas++;
        }
    }
    char* letrasRepetidas = (char*)malloc(numLetrasRepetidas + 1);
    letrasRepetidas[numLetrasRepetidas] = '\0';

    int indiceActual = 0;
    for (int i = 0; i < 26; i++) {
        if (contador[i] == maxCount) {
            letrasRepetidas[indiceActual++] = 'A' + i;
        }
    }
    return letrasRepetidas;
}

int calcularSumaEscuadron(char escuadron[][2], int largo) {
    int suma = 0;
    for (int i = 0; i < largo; i++) {
        char letra = escuadron[i][0];
        suma += letra - 'A' + 1;
    }
    return suma;
}