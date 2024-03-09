#include <stdio.h>

void merge(int arreglo[][2], int izq, int med, int der) {
    int n1 = med - izq + 1;
    int n2 = der - med;
    int I [n1][2], D[n2][2];
    for (int i = 0; i < n1; i++) {
        I[i][0] = arreglo[izq + i][0];
        I[i][1] = arreglo[izq + i][1];
    }
    for (int j = 0; j < n2; j++) {
        D[j][0] = arreglo[med + 1 + j][0];
        D[j][1] = arreglo[med + 1 + j][1];
    }
    int i = 0, j = 0, k = izq;
    while (i < n1 && j < n2) {
        if (I[i][1] >= D[j][1]) {
            arreglo[k][0] = I[i][0];
            arreglo[k][1] = I[i][1];
            i++;
        } else {
            arreglo[k][0] = D[j][0];
            arreglo[k][1] = D[j][1];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arreglo[k][0] = I[i][0];
        arreglo[k][1] = I[i][1];
        i++;
        k++;
    }
    while (j < n2) {
        arreglo[k][0] = D[j][0];
        arreglo[k][1] = D[j][1];
        j++;
        k++;
    }
}

void mergeSort(int arreglo[][2], int izq, int der) {
    if (izq < der) {
        int med = izq + (der - izq) / 2;
        mergeSort(arreglo, izq, med);
        mergeSort(arreglo, med + 1, der);
        merge(arreglo, izq, med, der);
    }
}
