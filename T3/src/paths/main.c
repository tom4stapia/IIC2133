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

typedef struct nodo {
    int pos_x;
    int pos_y;
} Nodo;

typedef struct arista {
    int inicio;
    int final;
    int costo;
} Arista;

int calcularCosto(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// CITADO Y ADAPTADO DE https://www.geeksforgeeks.org/merge-sort/.

void merge(Arista* aristas, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Arista* L = (Arista*) malloc(n1 * sizeof(Arista));
    Arista* R = (Arista*) malloc(n2 * sizeof(Arista));
    for (i = 0; i < n1; i++)
        L[i] = aristas[left + i];
    for (j = 0; j < n2; j++)
        R[j] = aristas[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i].costo <= R[j].costo) {
            aristas[k] = L[i];
            i++;
        } else {
            aristas[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        aristas[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        aristas[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(Arista* aristas, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(aristas, left, mid);
        mergeSort(aristas, mid + 1, right);

        merge(aristas, left, mid, right);
    }
}

// FIN CITADO

int find(int* padres, int nodo) {
    if (padres[nodo] != nodo) {
        padres[nodo] = find(padres, padres[nodo]);
    }
    return padres[nodo];
}

void unionFind(int* padres, int* rango, int nodo1, int nodo2) {
    int padre1 = find(padres, nodo1);
    int padre2 = find(padres, nodo2);
    if (rango[padre1] > rango[padre2]) {
        padres[padre2] = padre1;
    } else if (rango[padre1] < rango[padre2]) {
        padres[padre1] = padre2;
    } else {
        padres[padre2] = padre1;
        rango[padre1]++;
    }
}

void kruskal(Nodo* nodos, int cantidadNodos, FILE* output_file) {
    int cantidadAristas = cantidadNodos * (cantidadNodos - 1) / 2; // Cantidad de aristas en un grafo completo por combinatoria
    Arista* aristas = calloc(cantidadAristas, sizeof(Arista));
    int indiceAristas = 0;
    for (int i = 0; i < cantidadNodos; i++) {
        for (int j = i + 1; j < cantidadNodos; j++) {
            aristas[indiceAristas].inicio = i;
            aristas[indiceAristas].final = j;
            aristas[indiceAristas].costo = calcularCosto(nodos[i].pos_x, nodos[i].pos_y, nodos[j].pos_x, nodos[j].pos_y);
            indiceAristas++;
        }
    }
    mergeSort(aristas, 0, cantidadAristas - 1);
    int* padres = calloc(cantidadNodos, sizeof(int));
    int* rango = calloc(cantidadNodos, sizeof(int));
    for (int i = 0; i < cantidadNodos; i++) {
        padres[i] = i;
    }
    Arista* MST = calloc(cantidadNodos - 1, sizeof(Arista));
    int indiceMST = 0;
    for (int i = 0; i < cantidadAristas; i++) {
        if (find(padres, aristas[i].inicio) != find(padres, aristas[i].final)) {
            MST[indiceMST] = aristas[i];
            indiceMST++;
            unionFind(padres, rango, aristas[i].inicio, aristas[i].final);
        }
    }
    int costoTotal = 0;
    for (int i = 0; i < cantidadNodos - 1; i++) {
        costoTotal += MST[i].costo;
    }
    fprintf(output_file, "%d\n", costoTotal);
    for (int i = 0; i < cantidadNodos - 1; i++) {
        fprintf(output_file, "%d %d %d %d\n", nodos[MST[i].inicio].pos_x, nodos[MST[i].inicio].pos_y, nodos[MST[i].final].pos_x, nodos[MST[i].final].pos_y);
    }
    free(aristas);
    free(padres);
    free(rango);
    free(MST);
}

int main(int argc, char **argv) {
    if (!check_arguments(argc, argv)) return 1;

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    int cantidadNodos;
    fscanf(input_file, "%d", &cantidadNodos);
    Nodo* nodos = calloc(cantidadNodos, sizeof(Nodo));
    for (int i = 0; i < cantidadNodos; i++) {
        fscanf(input_file, "%d %d", &nodos[i].pos_x, &nodos[i].pos_y);
    }
    kruskal(nodos, cantidadNodos, output_file);
    free(nodos);    

    fclose(input_file);
    fclose(output_file);

    return 0;
}
