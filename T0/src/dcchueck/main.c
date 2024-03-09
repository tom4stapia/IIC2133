#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "orden/mergesort.h"
#include "guerrero/guerrero.h"
#include "escuadron/escuadron.h"

/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
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


int main(int argc, char **argv) {
  /* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv)) {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");

  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");

  /* Leemos la cantidad de escuadrones en el primer ejercito */
  int S_SQUADRON_COUNT;
  fscanf(input_file, "%d", &S_SQUADRON_COUNT);

  /* Leemos la cantidad de escuadrones en el segundo ejercito */
  int F_SQUADRON_COUNT;
  fscanf(input_file, "%d", &F_SQUADRON_COUNT);

  /*  [Por implementar] Debes crear una estructura para almacenar los ejercitos y escuadrones */
  Escuadron** ejercitoS = calloc(S_SQUADRON_COUNT, sizeof(Escuadron*));
  Escuadron** ejercitoF = calloc(F_SQUADRON_COUNT, sizeof(Escuadron*));

  /* Leemos la cantidad de eventos */
  int N_EVENTS;
  fscanf(input_file, "%d", &N_EVENTS);

  /* String para guardar la instrucción actual*/
  char command[32];

  for (int i = 0; i < S_SQUADRON_COUNT; i++) {
    ejercitoS[i] = escuadron_init(i);
  }
  for (int i = 0; i < F_SQUADRON_COUNT; i++) {
    ejercitoF[i] = escuadron_init(i);
  }


  for (int event = 0; event < N_EVENTS; event++) {
    /* Leemos el evento */
    fscanf(input_file, "%s", command);
    /* [Por implementar] A continuación debes implementar cada evento */
    if (string_equals(command, "ENLISTAR")) {
      /* [Por implementar] */
      int ejercitoID, escuadronID, guerreroID, vidaBase, danoBase, faccion, largoArsenal;
      fscanf(input_file, "%d %d %d %d %d %d %d", &ejercitoID, &escuadronID, &guerreroID, &vidaBase, &danoBase, &faccion, &largoArsenal);
      if (ejercitoID == 0) {
        Escuadron* escuadron = ejercitoS[escuadronID];
        Guerrero* guerrero = guerrero_init(guerreroID, vidaBase, danoBase, faccion, largoArsenal);
        insertGuerrero(escuadron, guerrero);
        fprintf(output_file, "ENLISTADO %d %d\n", guerrero->id, escuadronID);
      } else {
        Escuadron* escuadron = ejercitoF[escuadronID];
        Guerrero* guerrero = guerrero_init(guerreroID, vidaBase, danoBase, faccion, largoArsenal);
        insertGuerrero(escuadron, guerrero);
        fprintf(output_file, "ENLISTADO %d %d\n", guerrero->id, escuadronID);
      }   
    }
    else if (string_equals(command, "EQUIPAR")) {
      /* [Por implementar] */
      int bonusArtefacto, ejercitoID, escuadronID, guerreroID, posicion;
      fscanf(input_file, "%d %d %d %d", &bonusArtefacto, &ejercitoID, &escuadronID, &guerreroID);
      int lleno = 1;
      Guerrero* guerrero;
      if (ejercitoID == 0){
        Escuadron* escuadron = ejercitoS[escuadronID];
        guerrero = buscarGuerrero(guerreroID, escuadron);
      } else {
        Escuadron* escuadron = ejercitoF[escuadronID];
        guerrero = buscarGuerrero(guerreroID, escuadron);
      }
      for (int i = 0; i < guerrero->largoArsenal; i++) {
       if (guerrero->arsenal[i] == 0 && lleno == 1) {
        lleno = 0;
        posicion = i;
       } 
      }
      if (lleno == 0) {
        guerrero->arsenal[posicion] = bonusArtefacto;
        fprintf(output_file, "ARTEFACTO %d ASIGNADO A %d\n", bonusArtefacto, guerrero->id);
      } else {
        fprintf(output_file, "ARSENAL LLENO %d\n", guerrero->id);
      }
    }
    else if (string_equals(command, "CONTEO-CAMPAL")) {
      /* [Por implementar] */
      int cantidadFaccion0S = 0;
      int cantidadFaccion1S = 0;
      int cantidadFaccion2S = 0;
      int cantidadFaccion0F = 0;
      int cantidadFaccion1F = 0;
      int cantidadFaccion2F = 0;
      int cantidadGuerreros = 0;
      for (int i = 0; i < S_SQUADRON_COUNT; i++) {
        Escuadron* escuadron = ejercitoS[i];
        Guerrero* guerrero = escuadron->primerGuerrero;
        while (guerrero != NULL) {
          if (guerrero->faccion == 0) {
            cantidadFaccion0S++;
          } else if (guerrero->faccion == 1) {
            cantidadFaccion1S++;
          } else {
            cantidadFaccion2S++;
          }
          guerrero = guerrero->siguiente;
        }
        cantidadGuerreros += escuadron->cantidad;
      }
      for (int i = 0; i < F_SQUADRON_COUNT; i++) {
        Escuadron* escuadron = ejercitoF[i];
        Guerrero* guerrero = escuadron->primerGuerrero;
        while (guerrero != NULL) {
          if (guerrero->faccion == 0) {
            cantidadFaccion0F++;
          } else if (guerrero->faccion == 1) {
            cantidadFaccion1F++;
          } else {
            cantidadFaccion2F++;
          }
          guerrero = guerrero->siguiente;
        }
        cantidadGuerreros += escuadron->cantidad;
      }
      fprintf(output_file, "CONTEO-CAMPAL\n\t");
      fprintf(output_file, "EJERCITO 0\n\t\t");
      fprintf(output_file, "FACCION 0: %d\n\t\t", cantidadFaccion0S);
      fprintf(output_file, "FACCION 1: %d\n\t\t", cantidadFaccion1S);
      fprintf(output_file, "FACCION 2: %d\n\t", cantidadFaccion2S);
      fprintf(output_file, "EJERCITO 1\n\t\t");
      fprintf(output_file, "FACCION 0: %d\n\t\t", cantidadFaccion0F);
      fprintf(output_file, "FACCION 1: %d\n\t\t", cantidadFaccion1F);
      fprintf(output_file, "FACCION 2: %d\n", cantidadFaccion2F);
      fprintf(output_file, "TOTAL DE GUERREROS : %d\n", cantidadGuerreros);
    }
    else if (string_equals(command, "ORDEN-EJERCITO")) {
      /* [Por implementar] */
      int ejercitoID;
      fscanf(input_file, "%d", &ejercitoID);
      if (ejercitoID == 0) {
        fprintf(output_file, "EJERCITO 0\n\t");
        int matrizEscuadrones[S_SQUADRON_COUNT][2];
        for (int i = 0; i < S_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoS[i];
          matrizEscuadrones[i][0] = escuadron->id;
          matrizEscuadrones[i][1] = escuadron->cantidad;
        }
        printOrdenEscuadron(matrizEscuadrones, S_SQUADRON_COUNT, output_file);
      } else {
        fprintf(output_file, "EJERCITO 1\n\t");
        int matrizEscuadrones[F_SQUADRON_COUNT][2];
        for (int i = 0; i < F_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoF[i];
          matrizEscuadrones[i][0] = escuadron->id;
          matrizEscuadrones[i][1] = escuadron->cantidad;
        }
        printOrdenEscuadron(matrizEscuadrones, F_SQUADRON_COUNT, output_file);
      }

    }
    else if (string_equals(command, "DESERTAR")) {
      /* [Por implementar] */
      int ejercitoID, escuadronID, guerreroID;
      fscanf(input_file, "%d %d %d", &ejercitoID, &escuadronID, &guerreroID);
      if (ejercitoID == 0) {
        Escuadron* escuadron = ejercitoS[escuadronID];
        Guerrero* guerrero = buscarGuerrero(guerreroID, escuadron);
        eliminarGuerrero(escuadron, guerrero);
      } else {
        Escuadron* escuadron = ejercitoF[escuadronID];
        Guerrero* guerrero = buscarGuerrero(guerreroID, escuadron);
        eliminarGuerrero(escuadron, guerrero);
      }
      fprintf(output_file, "ABANDONA %d %d\n", guerreroID, ejercitoID);
    }
    else if (string_equals(command, "ATACA")) {
      /* [Por implementar] */
      int ejercitoID;
      fscanf(input_file, "%d", &ejercitoID);
      Escuadron* escuadronAtacante;
      Escuadron* escuadronDefensor;
      if (ejercitoID == 0) {
        int mayorDanoBase = 0;
        for (int i = 0; i < S_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoS[i];
          Guerrero* guerrero = escuadron->primerGuerrero;
          int danoBase = 0;
          while (guerrero != NULL) {
            danoBase += guerrero->danoBase;
            guerrero = guerrero->siguiente;
          }
          if (danoBase > mayorDanoBase) {
            mayorDanoBase = danoBase;
            escuadronAtacante = escuadron;
 
          }
        }
        int menorCantidad = 1000000;
        for (int i = 0; i < F_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoF[i];
          if (escuadron->cantidad < menorCantidad && escuadron->cantidad > 0) {
            menorCantidad = escuadron->cantidad;
            escuadronDefensor = escuadron;
          }
        }
      } else {
        int mayorDanoBase = 0;
        for (int i = 0; i < F_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoF[i];
          Guerrero* guerrero = escuadron->primerGuerrero;
          int danoBase = 0;
          while (guerrero != NULL) {
            danoBase += guerrero->danoBase;
            guerrero = guerrero->siguiente;
          }
          if (danoBase > mayorDanoBase) {
            mayorDanoBase = danoBase;
            escuadronAtacante = escuadron;
          }
        }
        int menorCantidad = 1000000;
        for (int i = 0; i < S_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoS[i];
          if (escuadron->cantidad < menorCantidad && escuadron->cantidad > 0) {
            menorCantidad = escuadron->cantidad;
            escuadronDefensor = escuadron;
          }
        }
      }
      Guerrero* guerreroAtacante = escuadronAtacante->primerGuerrero;
      Guerrero* guerreroDefensor = escuadronDefensor->primerGuerrero;
      int danoTotal = 0;
      int mayorArsenal = 0;
      int posArsenal = 0;
      for (int i = 0; i < guerreroAtacante->largoArsenal; i++) {
        if (guerreroAtacante->arsenal[i] > mayorArsenal) {
          mayorArsenal = guerreroAtacante->arsenal[i];
          posArsenal = i;
        }
      }
      danoTotal += guerreroAtacante->danoBase + mayorArsenal;
      guerreroAtacante->arsenal[posArsenal] = 0;
      if (guerreroAtacante->faccion == 0) {
        danoTotal += 5;
      } else if (guerreroAtacante->faccion == 1) {
        danoTotal += 10;
      } else {
        danoTotal += 15;
      }
      fprintf(output_file, "ATACA %d %d\n", guerreroAtacante->id, guerreroDefensor->id);
      if (guerreroDefensor->vida <= danoTotal) {
        eliminarGuerrero(escuadronDefensor, guerreroDefensor);
      } else {
        guerreroDefensor->vida -= danoTotal;
        }
      moverGuerreroUltimo(escuadronAtacante, guerreroAtacante);
    }
    else if (string_equals(command, "TRAICIONAR")) {
      /* [Por implementar] */
      int ejercitoID, escuadronID, guerreroID;
      Escuadron* escuadronOponente;
      Escuadron* escuadronOriginal;
      int mayorCantidad = 0;
      fscanf(input_file, "%d %d %d", &ejercitoID, &escuadronID, &guerreroID);
      if (ejercitoID == 0) {
        for (int i = 0; i < F_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoF[i];
          if (escuadron->cantidad > mayorCantidad) {
            mayorCantidad = escuadron->cantidad;
            escuadronOponente = escuadron;
          }
        }
        escuadronOriginal = ejercitoS[escuadronID];
      } else {
        for (int i = 0; i < S_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoS[i];
          if (escuadron->cantidad > mayorCantidad) {
            mayorCantidad = escuadron->cantidad;
            escuadronOponente = escuadron;
          }
        }
        escuadronOriginal = ejercitoF[escuadronID];
      }
    Guerrero* guerrero = buscarGuerrero(guerreroID, escuadronOriginal);
    traicionar(escuadronOponente, escuadronOriginal, guerrero);
    fprintf(output_file, "TRAICION %d\n", ejercitoID);
    }
    else if (string_equals(command, "ALTA-TRAICION")) {
      /* [Por implementar] */
      int ejercitoID, escuadronID, guerreroID;
      int mayorCantidad = 0;
      Escuadron* escuadronEnemigo;
      Escuadron* escuadronOriginal;
      Guerrero* guerrero;
      fscanf(input_file, "%d %d %d", &ejercitoID, &escuadronID, &guerreroID);
      if (ejercitoID == 0) {
        escuadronOriginal = ejercitoS[escuadronID];
        guerrero = buscarGuerrero(guerreroID, escuadronOriginal);
        for (int i = 0; i < F_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoF[i];
          if (escuadron->cantidad > mayorCantidad) {
            mayorCantidad = escuadron->cantidad;
            escuadronEnemigo = escuadron;
          }
        }     
      } else {
        escuadronOriginal = ejercitoF[escuadronID];
        guerrero = buscarGuerrero(guerreroID, escuadronOriginal);
        for (int i = 0; i < S_SQUADRON_COUNT; i++) {
          Escuadron* escuadron = ejercitoS[i];
          if (escuadron->cantidad > mayorCantidad) {
            mayorCantidad = escuadron->cantidad;
            escuadronEnemigo = escuadron;
          }
        }
      }
      int largo = largoListaLigada(guerrero, escuadronOriginal);
      traicionarAlta(escuadronEnemigo, escuadronOriginal, guerrero, largo);
      fprintf(output_file, "ALTA-TRAICION %d\n", ejercitoID);
    }
  }

  /*  [Por implementar] Liberamos nuestras estructuras */
  for (int i = 0; i < S_SQUADRON_COUNT; i++) {
    freeEscuadron(ejercitoS[i]);
  }
  for (int i = 0; i < F_SQUADRON_COUNT; i++) {
    freeEscuadron(ejercitoF[i]);
  }

  free(ejercitoS);
  free(ejercitoF);
  fclose(input_file);
  fclose(output_file);

  return 0;
}