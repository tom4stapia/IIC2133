#pragma once
#include "../../imagelib/imagelib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct quadTreeN {
    int height;
    int width;
    int x;
    int y;
    bool esHoja;
    struct quadTreeN* northwest;
    struct quadTreeN* northeast;
    struct quadTreeN* southwest;
    struct quadTreeN* southeast;
    
    double L;
    double dsL;
    double meanL;
    double cuadradoL;

    double a;
    double dsA;
    double meanA;
    double cuadradoA;

    double b;
    double dsB;
    double meanB;
    double cuadradoB;

    double gamma;
} QuadTreeNode;


typedef struct quadtree
{
    QuadTreeNode* root;
} QuadTree;

QuadTree* createQuadTree(Image* img);
QuadTreeNode* createQuadTreeNode(int width, int height);
void freeQuadTree(QuadTreeNode* nodo);
void media(QuadTreeNode* nodo);
void cuadrado(QuadTreeNode* nodo);
void ds(QuadTreeNode* nodo);
void completarQuadTree(QuadTreeNode* nodo, Image* img);
void filtroAlpha(QuadTreeNode* root, Image* image, int alpha);
int contar_hojas(QuadTreeNode* root, int alpha);
int compresion(QuadTreeNode* root, int h, int alpha, int min, int max);
