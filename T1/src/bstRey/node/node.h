#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma once

typedef struct node_t {
  int value;
  struct node_t *left_child;
  struct node_t *right_child; 
} Node;

Node* node_init(int value);
int free_node(Node* node);
void insert_node(Node* root, Node* node);
void encontrar_path(Node* node, int value, bool cambio, FILE* output_file);
int encontrar_deep(Node* node, int value, bool cambio, int nivel);
int order(Node* node, bool cambio, FILE* output_file);
int deepOrder(Node* root, int node_count, bool cambio, FILE* output_file);
void invert(Node* node);