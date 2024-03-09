#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct guerrero {
    int id;
    int vida;
    int danoBase;
    int largoArsenal;
    int *arsenal;
    int faccion;
    struct guerrero *siguiente;
} Guerrero;

Guerrero* guerrero_init(int id, int vida, int danoBase, int faccion, int largoArsenal);
