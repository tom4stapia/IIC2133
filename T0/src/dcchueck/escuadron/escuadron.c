#include "escuadron.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../guerrero/guerrero.h"
#include "../orden/mergesort.h"

Guerrero* buscarGuerrero(int id, Escuadron* escuadron) {
    Guerrero* guerrero = escuadron->primerGuerrero;
    while (guerrero != NULL) {
        if (guerrero->id == id) {
        return guerrero;
        }
        guerrero = guerrero->siguiente;
    }
    return NULL; 
}

Guerrero* buscarGuerreroAnterior(int id, Escuadron* escuadron) {
    Guerrero* guerrero = escuadron ->primerGuerrero;
    while (guerrero->siguiente->id != id && guerrero->siguiente != NULL) {
        guerrero = guerrero->siguiente;
    }
    return guerrero;
}

void eliminarGuerrero (Escuadron* escuadron, Guerrero* guerrero) {
    if (escuadron->primerGuerrero == escuadron->ultimoGuerrero) {
        escuadron->primerGuerrero = NULL;
        escuadron->ultimoGuerrero = NULL;
    } else if (escuadron->primerGuerrero == guerrero) {
        escuadron->primerGuerrero = guerrero->siguiente;
    } else {
        Guerrero* antecesor = escuadron->primerGuerrero;
        while (antecesor->siguiente !=guerrero) {
        antecesor = antecesor->siguiente;
        }
        antecesor->siguiente = guerrero->siguiente;
        if (antecesor->siguiente == NULL) {
        escuadron->ultimoGuerrero = antecesor;
        } else if (guerrero->siguiente == NULL) {
        escuadron->ultimoGuerrero = antecesor;
        }
    }
    escuadron->cantidad--;
    free(guerrero->arsenal);
    free(guerrero);
}

void moverGuerreroUltimo(Escuadron* escuadronAtacante, Guerrero* guerreroAtacante) {
    if (escuadronAtacante->primerGuerrero == escuadronAtacante->ultimoGuerrero) {
        /*Nada*/
    } else {
        escuadronAtacante->primerGuerrero = guerreroAtacante->siguiente;
        Guerrero* guerreroUltimo = escuadronAtacante->ultimoGuerrero;
        guerreroUltimo->siguiente = guerreroAtacante;
        guerreroAtacante->siguiente = NULL;
        escuadronAtacante->ultimoGuerrero = guerreroAtacante;
    };
}

Escuadron* escuadron_init(int id) {
    Escuadron* escuadron = calloc(1, sizeof(Escuadron));
    escuadron-> id = id;
    return escuadron;
}

void insertGuerrero (Escuadron* escuadron, Guerrero* guerrero) {
    if (escuadron->primerGuerrero == NULL) {
        escuadron->primerGuerrero = guerrero;
        escuadron->ultimoGuerrero = guerrero;
    } else {
        escuadron->ultimoGuerrero->siguiente = guerrero;
        escuadron->ultimoGuerrero = guerrero;
    }
    escuadron->cantidad++;
} 

void freeEscuadron(Escuadron* escuadron) {
    Guerrero* guerrero = escuadron->primerGuerrero;
    while (guerrero != NULL) {
        Guerrero* guerreroSiguiente = guerrero->siguiente;
        free(guerrero->arsenal);
        free(guerrero);
        guerrero = guerreroSiguiente;
    }
    free(escuadron);
}

void printOrdenEscuadron(int matrizEscuadrones[][2], int largo, FILE* output_file) {
    mergeSort(matrizEscuadrones, 0, largo-1);
    for (int i = 0; i < largo; i++) {
        if (i == largo-1){
        fprintf(output_file, "ESCUADRON %d %d\n", matrizEscuadrones[i][0], matrizEscuadrones[i][1]);
        } else {
        fprintf(output_file, "ESCUADRON %d %d\n\t", matrizEscuadrones[i][0], matrizEscuadrones[i][1]);
        }
    }
}

void traicionar(Escuadron* escuadronEnemigo, Escuadron* escuadronOriginal, Guerrero* guerrero) {
    if (escuadronOriginal->primerGuerrero == guerrero) {
        escuadronOriginal->primerGuerrero = guerrero->siguiente;
        guerrero->siguiente = NULL;
        escuadronOriginal->cantidad--;
        insertGuerrero(escuadronEnemigo, guerrero);
    } else if (escuadronOriginal->ultimoGuerrero == guerrero) {
        Guerrero* guerreroAnterior = buscarGuerreroAnterior(guerrero->id, escuadronOriginal);
        escuadronOriginal->ultimoGuerrero = guerreroAnterior;
        guerreroAnterior->siguiente = NULL;
        escuadronOriginal->cantidad--;
        insertGuerrero(escuadronEnemigo, guerrero);
    } else {
        Guerrero* guerreroAnterior = buscarGuerreroAnterior(guerrero->id, escuadronOriginal);
        guerreroAnterior->siguiente = guerrero->siguiente;
        guerrero->siguiente = NULL;
        escuadronOriginal->cantidad--;
        insertGuerrero(escuadronEnemigo, guerrero);
    }
}

void traicionarAlta(Escuadron* escuadronEnemigo, Escuadron* escuadronOriginal, Guerrero* guerrero, int largo) {
    if (escuadronOriginal->primerGuerrero == guerrero) {
        escuadronEnemigo->ultimoGuerrero->siguiente = guerrero;
        escuadronEnemigo->ultimoGuerrero = escuadronOriginal->ultimoGuerrero;
        escuadronEnemigo->cantidad += escuadronOriginal->cantidad;
        escuadronOriginal->cantidad = 0;
        escuadronOriginal->primerGuerrero = NULL;
        escuadronOriginal->ultimoGuerrero = NULL;
    } else if (escuadronOriginal->ultimoGuerrero == guerrero) {
        Guerrero* guerreroAnterior = buscarGuerreroAnterior(guerrero->id, escuadronOriginal);
        escuadronOriginal->ultimoGuerrero = guerreroAnterior;
        guerreroAnterior->siguiente = NULL;
        escuadronOriginal->cantidad--;
        insertGuerrero(escuadronEnemigo, guerrero);
    } else {
        Guerrero* guerreroAnterior = buscarGuerreroAnterior(guerrero->id, escuadronOriginal);
        guerreroAnterior->siguiente = NULL;
        escuadronEnemigo->ultimoGuerrero->siguiente = guerrero;
        escuadronEnemigo->ultimoGuerrero = escuadronOriginal->ultimoGuerrero;
        escuadronOriginal->ultimoGuerrero = guerreroAnterior;
        escuadronOriginal->cantidad -= largo;
        escuadronEnemigo->cantidad += largo;
    }
}


int largoListaLigada (Guerrero* guerrero, Escuadron* escuadron) {
    int largo = 1;
    if (guerrero == escuadron->ultimoGuerrero) {
        return largo;
    } else {
        while (guerrero->siguiente != NULL) {
        largo++;
        guerrero = guerrero->siguiente;
        }
    }
    return largo;
}