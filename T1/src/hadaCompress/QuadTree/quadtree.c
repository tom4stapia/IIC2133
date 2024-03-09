#include "../../imagelib/imagelib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "quadtree.h"

QuadTreeNode* createQuadTreeNode(int width, int height){
    QuadTreeNode* nodo = (QuadTreeNode*)calloc(1, sizeof(QuadTreeNode));
    nodo -> width = width;
    nodo -> height = height;
    nodo -> esHoja = false;
    return nodo;
}

void completarQuadTree(QuadTreeNode* nodo, Image* img){
    if(nodo -> width != 1){
        nodo -> northwest = createQuadTreeNode(nodo -> width/2, nodo -> height/2);
        nodo -> northwest -> x = nodo -> x;
        nodo -> northwest -> y = nodo -> y;
        completarQuadTree(nodo -> northwest, img);
        nodo -> northeast = createQuadTreeNode(nodo -> width/2, nodo -> height/2);
        nodo -> northeast -> x = nodo -> x + nodo -> width/2;
        nodo -> northeast -> y = nodo -> y;
        completarQuadTree(nodo -> northeast, img);
        nodo -> southwest = createQuadTreeNode(nodo -> width/2, nodo -> height/2);
        nodo ->southwest -> x = nodo -> x;
        nodo ->southwest -> y = nodo -> y + nodo -> height/2;
        completarQuadTree(nodo -> southwest, img);
        nodo -> southeast = createQuadTreeNode(nodo -> width/2, nodo -> height/2);
        nodo -> southeast -> x = nodo -> x + nodo -> width/2;
        nodo -> southeast -> y = nodo -> y + nodo -> height/2;
        completarQuadTree(nodo -> southeast, img);
    } else {
        nodo -> esHoja = true;
        nodo -> L = img -> pixels[nodo->x][nodo->y].L;
        nodo -> meanL = img -> pixels[nodo->x][nodo->y].L;
        nodo -> a = img -> pixels[nodo->x][nodo->y].a;
        nodo -> meanA = img -> pixels[nodo->x][nodo->y].a;
        nodo -> b = img -> pixels[nodo->x][nodo->y].b;
        nodo -> meanB = img -> pixels[nodo->x][nodo->y].b;
        nodo -> cuadradoL = pow(nodo -> L, 2);
        nodo -> cuadradoA = pow(nodo -> a, 2);
        nodo -> cuadradoB = pow(nodo -> b, 2);
        nodo -> dsL = 0.0;
        nodo -> dsA = 0.0;
        nodo -> dsB = 0.0;
    }
}

void freeQuadTree(QuadTreeNode* nodo){
    if (nodo -> esHoja == true) {
        free(nodo);
    } else {
        freeQuadTree(nodo -> northwest);
        freeQuadTree(nodo -> northeast);
        freeQuadTree(nodo -> southeast);
        freeQuadTree(nodo -> southwest);
        free(nodo);
    }  
}

void media(QuadTreeNode* nodo){
    if (nodo -> esHoja == false){
        media(nodo -> northwest);
        media(nodo -> northeast);
        media(nodo -> southwest);
        media(nodo -> southeast);
        nodo -> meanL = (nodo ->northwest-> meanL + nodo -> northeast -> meanL + nodo -> southwest -> meanL + nodo -> southeast -> meanL)/4;
        nodo -> meanA = (nodo ->northwest-> meanA + nodo -> northeast -> meanA + nodo -> southwest -> meanA + nodo -> southeast -> meanA)/4;
        nodo -> meanB = (nodo ->northwest-> meanB + nodo -> northeast -> meanB + nodo -> southwest -> meanB + nodo -> southeast -> meanB)/4;
    }
}

void cuadrado(QuadTreeNode* nodo){
    if (nodo->esHoja == false) {
        cuadrado(nodo -> northwest);
        cuadrado(nodo -> northeast);
        cuadrado(nodo -> southwest);
        cuadrado(nodo -> southeast);
        nodo -> cuadradoL = nodo -> northwest -> cuadradoL + nodo -> northeast -> cuadradoL + nodo -> southwest -> cuadradoL + nodo -> southeast -> cuadradoL;
        nodo -> cuadradoA = nodo -> northwest -> cuadradoA + nodo -> northeast -> cuadradoA + nodo -> southwest -> cuadradoA + nodo -> southeast -> cuadradoA;
        nodo -> cuadradoB = nodo -> northwest -> cuadradoB + nodo -> northeast -> cuadradoB + nodo -> southwest -> cuadradoB + nodo -> southeast -> cuadradoB;    
    }
}

void ds(QuadTreeNode* nodo){
    if (nodo->esHoja == false){
        ds(nodo -> northwest);
        ds(nodo -> northeast);
        ds(nodo -> southwest);
        ds(nodo -> southeast);
        nodo -> dsL = sqrt((nodo -> cuadradoL/pow(nodo -> height,2) - pow((nodo -> meanL),2)));
        nodo -> dsA = sqrt((nodo -> cuadradoA/pow(nodo -> height,2) - pow((nodo -> meanA),2)));
        nodo -> dsB = sqrt((nodo -> cuadradoB/pow(nodo -> height,2) - pow((nodo -> meanB),2)));
        nodo -> gamma = (nodo -> dsL + nodo -> dsA + nodo -> dsB)/3;
    } 
}

void filtroAlpha(QuadTreeNode* root, Image* image, int alpha) {
    if (root->gamma <= alpha) {
        img_square_paint(
            image, 
            root->x, 
            root->y, 
            root->height, 
            (Color) {.L = root->meanL, .a = root->meanA, .b = root->meanB});
    } else {
        filtroAlpha(root->northwest, image, alpha);
        filtroAlpha(root->northeast, image, alpha);
        filtroAlpha(root->southwest, image, alpha);
        filtroAlpha(root->southeast, image, alpha);
    }
}

int contar_hojas(QuadTreeNode* root, int alpha) {
    if (root->gamma <= alpha) {
        return 1;
    } else if (root->esHoja) {
        return 1;
    } else {
        return contar_hojas(root->northwest, alpha) + contar_hojas(root->northeast, alpha) + contar_hojas(root->southwest, alpha) + contar_hojas(root->southeast, alpha);
    }   
}

int compresion(QuadTreeNode* root, int h, int alpha, int min, int max) {
    int cantidad = contar_hojas(root, alpha);
    if (cantidad == h) {
        return alpha;
    } else if (cantidad > h) {
        return compresion(root, h, alpha + ((alpha - min)/2), alpha, max);
    } else {
        cantidad = contar_hojas(root, alpha - 1);
        if (h < cantidad) {
            return alpha;
        } else {
            return compresion(root, h, alpha - ((alpha - min)/2), min, alpha);
        }
    }       
}

QuadTree* createQuadTree(Image* img){
    QuadTree* quadTree = (QuadTree*)calloc(1, sizeof(QuadTree));
    quadTree -> root = createQuadTreeNode(img -> width, img -> height);
    quadTree-> root -> x = 0;
    quadTree-> root -> y = 0;
    completarQuadTree(quadTree->root, img);
    media(quadTree -> root);
    cuadrado(quadTree->root);
    ds(quadTree -> root);
    return quadTree;
}