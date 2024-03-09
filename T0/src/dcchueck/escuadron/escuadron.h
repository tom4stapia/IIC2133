#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../guerrero/guerrero.h"

typedef struct escuadron {
    int id;
    int cantidad;
    Guerrero *primerGuerrero;
    Guerrero *ultimoGuerrero;
} Escuadron;

Escuadron* escuadron_init(int id);
void insertGuerrero (Escuadron* escuadron, Guerrero* guerrero);
void freeEscuadron(Escuadron* escuadron);
void printOrdenEscuadron(int matrizEscuadrones[][2], int largo, FILE* output_file);
void traicionar(Escuadron* escuadronEnemigo, Escuadron* escuadronOriginal, Guerrero* guerrero);
void traicionarAlta(Escuadron* escuadronEnemigo, Escuadron* escuadronOriginal, Guerrero* guerrero, int largo);
int largoListaLigada (Guerrero* guerrero, Escuadron* escuadron);
Guerrero* buscarGuerrero(int id, Escuadron* escuadron);
Guerrero* buscarGuerreroAnterior(int id, Escuadron* escuadron);
void eliminarGuerrero (Escuadron* escuadron, Guerrero* guerrero);
void moverGuerreroUltimo(Escuadron* escuadronAtacante, Guerrero* guerreroAtacante);
