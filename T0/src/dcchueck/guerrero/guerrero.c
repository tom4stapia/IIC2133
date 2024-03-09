#include "guerrero.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../escuadron/escuadron.h"

Guerrero* guerrero_init(int id, int vida, int danoBase, int faccion, int largoArsenal) {
    Guerrero* guerrero = calloc(1, sizeof(Guerrero));
    guerrero->id = id;
    guerrero->vida = vida;
    guerrero->danoBase = danoBase;
    guerrero->faccion = faccion;
    guerrero->largoArsenal = largoArsenal;
    guerrero->arsenal = calloc(largoArsenal, sizeof(int));
    return guerrero;
}

