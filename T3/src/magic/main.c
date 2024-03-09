#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NODOS 40

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

typedef struct node {
    int id;
    struct node *neighbors[MAX_NODOS];
    bool visited;
} Nodo;

void dfs(Nodo *nodo, Nodo *ignorar_nodo) {
    if (!nodo->visited && nodo->id != ignorar_nodo->id) {
        nodo->visited = true;
        for (int i = 0; i < MAX_NODOS; i++) {
            if (nodo->neighbors[i] && nodo->neighbors[i]->id != ignorar_nodo->id) {
                dfs(nodo->neighbors[i], ignorar_nodo);
            }
        }
    }
}

void desvisitar_nodos(Nodo *nodos, int n) {
    for (int i = 0; i < n; i++) {
        nodos[i].visited = false;
    }
}

bool hay_algun_nodo(Nodo *nodos, int n, Nodo *ignorar_nodo, Nodo **nodo_1) {
    for (int i = 0; i < n; i++) {
        if (!nodos[i].visited && nodos[i].id != ignorar_nodo->id) {
            *nodo_1 = &nodos[i];
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (!check_arguments(argc, argv)) return 1;

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    int cantidadNodos;
    int cantidadAristas;
    fscanf(input_file, "%d", &cantidadNodos);
    fscanf(input_file, "%d", &cantidadAristas);
    Nodo *nodos = calloc(cantidadNodos, sizeof(Nodo));
    for (int i = 0; i < cantidadNodos; i++) {
        nodos[i].id = i;
        nodos[i].visited = false;
        for (int j = 0; j < MAX_NODOS; j++) {
            nodos[i].neighbors[j] = NULL;
        }
    }

    for (int i = 0; i < cantidadAristas; i++) {
        int nodo1;
        int nodo2;
        fscanf(input_file, "%d %d", &nodo1, &nodo2);
        nodos[nodo1 - 1].neighbors[nodo2 - 1] = &nodos[nodo2 - 1];
        nodos[nodo2 - 1].neighbors[nodo1 - 1] = &nodos[nodo1 - 1];
    }
    int cantidadComponentes = 0;
    int matriz[MAX_NODOS][2];
    for (int i = 0; i < MAX_NODOS; i++) {
        matriz[i][0] = -1;
        matriz[i][1] = -1;
    }

    for (int i = 0; i < cantidadNodos; i++) {
        Nodo *ignorar_nodo = &nodos[i];
        int contador = 0;
        Nodo *nodo_1;
        while (hay_algun_nodo(nodos, cantidadNodos, ignorar_nodo, &nodo_1)) {
            contador++;
            dfs(nodo_1, ignorar_nodo);
        }
        if (contador > 1) {
            matriz[i][0] = ignorar_nodo->id;
            matriz[i][1] = contador;
            cantidadComponentes++;
        }
        desvisitar_nodos(nodos, cantidadNodos);
    }

    fprintf(output_file, "%d\n", cantidadComponentes);
    for (int i = 0; i < MAX_NODOS; i++) {
        if (matriz[i][0] != -1) {
            fprintf(output_file, "%d %d\n", matriz[i][0], matriz[i][1]);
        }
    }

    free(nodos);


    fclose(input_file);
    fclose(output_file);

    return 0;
}
