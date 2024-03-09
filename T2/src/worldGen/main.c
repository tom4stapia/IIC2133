#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tile {
  char arriba;
  char derecha;
  char abajo;
  char izquierda;
  int value;
} Tile;

typedef struct celda {
  int x;
  int y;
  Tile* tile;
  bool visited;
  bool inicial;
  bool queda;
} Celda;

void freeMatriz(Celda*** matriz, int columna, int fila) {
  for (int i = 0; i < fila; i++) {
    for (int j = 0; j < columna; j++) {
      matriz[i][j]->tile = NULL;
      free(matriz[i][j]->tile);
      free(matriz[i][j]);
    }
    free(matriz[i]);
  }
  free(matriz);
}

void freeTiles(Tile* tiles, int sizeSet) {
  free(tiles);
}

void printMatriz(Celda*** matriz, int columna, int fila) {
  printf("Matriz: \n");
  for (int i = 0; i < fila; i++) {
    printf("\t");
    for (int j = 0; j < columna; j++) {
      if (matriz[i][j]->tile == NULL) {
        printf("-1 ");
      } else {
        printf("%d ", matriz[i][j]->tile->value);
      }
    }
    printf("\n");
  }
}

void convertirInicial(Celda*** matriz, int columnas, int filas) {
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (matriz[i][j]->tile != NULL) {
        matriz[i][j]->inicial = true;
      }
    }
  }
}

bool encontrarEspacioVacio(Celda*** matriz, int filas, int columnas) {
  for(int i=0; i<filas; i++){
    for(int j=0; j<columnas; j++){
      if(matriz[i][j]->tile == NULL){
        return true;
      }
    }
  } return false;
}

bool checkTile(Celda*** matriz, int fila, int columna, Tile* tile, int alto, int ancho) {
  if (matriz[fila][columna] -> tile != NULL && matriz[fila][columna]->visited) {
    return false;
  }
  if (fila > 0) {
    Tile* tileArriba = matriz[fila - 1][columna]->tile;
    if (tileArriba == NULL || tile->arriba == tileArriba->abajo) {
    } else {
      return false; 
    }
  }
  if (fila < alto - 1) {
    Tile* tileAbajo = matriz[fila + 1][columna]->tile;
    if (tileAbajo == NULL || tile->abajo == tileAbajo->arriba) {
    } else {
      return false; 
    }
  }
  if (columna > 0) {
    Tile* tileIzquierda = matriz[fila][columna - 1]->tile;
    if (tileIzquierda == NULL || tile->izquierda == tileIzquierda->derecha) {
    } else {
      return false; 
    }
  }
  if (columna < ancho - 1) {
    Tile* tileDerecha = matriz[fila][columna + 1]->tile;
    if (tileDerecha == NULL || tile->derecha == tileDerecha->izquierda) {
      
    } else {
      return false; 
    }
  }

  return true; 
}

bool seguirCamino(Celda*** matriz, int fila, int columna, int alto, int ancho) {
  if (fila > 0) {
    if (matriz[fila - 1][columna]->tile == NULL) {
      return false;
    }
    if (matriz[fila][columna]->tile->arriba != matriz[fila - 1][columna]->tile->abajo) {
      return false;
    }
    }
  if (fila < alto - 1) {
    if (matriz[fila + 1][columna]->tile == NULL) {
      return false;
    }
    if (matriz[fila][columna]->tile->abajo != matriz[fila + 1][columna]->tile->arriba) {
      return false;
    }
  }
  if (columna > 0) {
    if (matriz[fila][columna - 1]->tile == NULL) {
      return false;
    }
    if (matriz[fila][columna]->tile->izquierda != matriz[fila][columna - 1]->tile->derecha) {
      return false;
    }
  }
  if (columna < ancho - 1) {
    if (matriz[fila][columna + 1]->tile == NULL) {
      return false;
    }
    if (matriz[fila][columna]->tile->derecha != matriz[fila][columna + 1]->tile->izquierda) {
      return false;
    }
  }
  return true;
} 


bool backtracking(Celda*** matriz, int fila, int columna, Tile* tiles, int sizeSet, int alto, int ancho){
  printMatriz(matriz, ancho, alto);
  if (!encontrarEspacioVacio(matriz, alto, ancho)){
    printMatriz(matriz, ancho, alto);
    return true;
  }
  if (matriz[fila][columna]->visited){
    return false;
  }
  matriz[fila][columna]->visited = true;
  if (fila < alto - 1) {
    for (int i = 0; i < sizeSet; i++){
      if (checkTile(matriz, fila + 1, columna, &tiles[i], alto, ancho) && !matriz[fila + 1][columna]->inicial){
        matriz[fila + 1][columna]->tile = &tiles[i];
        if (backtracking(matriz, fila + 1, columna, tiles, sizeSet, alto, ancho)){
          return true;
        }
        matriz[fila + 1][columna]->visited = false;
      }
    } 
  } 
  if (columna > 0) {
    for (int i = 0; i < sizeSet; i++){
      if (checkTile(matriz, fila, columna - 1, &tiles[i], alto, ancho) && !matriz[fila][columna - 1]->inicial){
        matriz[fila][columna - 1]->tile = &tiles[i];
        if (backtracking(matriz, fila, columna - 1, tiles, sizeSet, alto, ancho)){
          return true;
        }
        matriz[fila][columna - 1]->visited = false;
      }
    } 
  }
  if (fila > 0) {
    for (int i = 0; i < sizeSet; i++){
      if (checkTile(matriz, fila - 1, columna, &tiles[i], alto, ancho) && !matriz[fila - 1][columna]->inicial){
        matriz[fila - 1][columna]->tile = &tiles[i];
        if (backtracking(matriz, fila - 1, columna, tiles, sizeSet, alto, ancho)){
          return true;
        }
        matriz[fila - 1][columna]->visited = false;
      }
    } 
  }  
  if (columna < ancho - 1) {
    for (int i = 0; i < sizeSet; i++){
      if (checkTile(matriz, fila, columna + 1, &tiles[i], alto, ancho) && !matriz[fila][columna + 1]->inicial){
        matriz[fila][columna + 1]->tile = &tiles[i];
        if (backtracking(matriz, fila, columna + 1, tiles, sizeSet, alto, ancho)){
          return true;
        }
        matriz[fila][columna + 1]->visited = false;
      }
    } 
  } 
   
  
  if (!seguirCamino(matriz, fila, columna, alto, ancho)) {
        matriz[fila][columna]->tile = NULL;
    }
  matriz[fila][columna]->visited = false;
  return false;
}


bool string_equals(const char* string1, const char* string2) {
  return strcmp(string1, string2) == 0;
}

bool check_arguments(int argc, char **argv) {
  if (argc != 3) {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    exit(1);
  }

  return true;
}

int main(int argc, char** argv) {
  check_arguments(argc, argv);

  /* NO MODIFICAR */
  FILE* input_file = fopen(argv[1], "r");
  FILE* output_file = fopen(argv[2], "w");
  /* NO MODIFICAR */
  int columna;
  int fila;
  fscanf(input_file, "%d", &columna);
  fscanf(input_file, "%d", &fila);
  int sizeSet;
  fscanf(input_file, "%d", &sizeSet);
  Tile* tiles = (Tile*)calloc(sizeSet, sizeof(Tile));
  Celda*** matriz = (Celda***)calloc(fila, sizeof(Celda**));

  char arriba;
  char abajo;
  char derecha;
  char izquierda;
  fgetc(input_file);
  for (int i = 0; i < sizeSet; i++) {
    fscanf(input_file, " %c %c %c %c", &arriba, &derecha, &abajo, &izquierda);
    tiles[i].arriba = arriba;
    tiles[i].derecha = derecha;
    tiles[i].abajo = abajo;
    tiles[i].izquierda = izquierda;
    tiles[i].value = i;
  }

  for (int i = 0; i < fila; i++) {
    matriz[i] = (Celda**)calloc(columna, sizeof(Celda*));
    for (int j = 0; j < columna; j++) {
      matriz[i][j] = (Celda*)calloc(1, sizeof(Celda));
      matriz[i][j]->x = i;
      matriz[i][j]->y = j;
      matriz[i][j]->tile = NULL;  
      matriz[i][j]->visited = false;
      matriz[i][j]->inicial = false;
    }
  }

  int cantidad;
  fscanf(input_file, "%d", &cantidad);
  int x;
  int y;
  for (int i = 0; i < cantidad; i++) {
    int value;
    fscanf(input_file, "%d %d %d", &x, &y, &value);
    matriz[y][x]->tile = &tiles[value];
    matriz[y][x]->inicial = true;
  }

  bool completo = backtracking(matriz, y, x, tiles, sizeSet, fila, columna);
  printf("completo: %d\n", completo);
  printMatriz(matriz, columna, fila);
  if (completo) {
    for (int i = 0; i < fila; i++) {
      for (int j = 0; j < columna; j++) {
        if (matriz[i][j]->tile == NULL) {
        } else {
          fprintf(output_file, "%d ", matriz[i][j]->tile->value);
        }
      }
      fprintf(output_file, "\n");
    }
  
  }
  freeMatriz(matriz, columna, fila);
  free(tiles);

  fclose(input_file);
  fclose(output_file);

  return 0;
}