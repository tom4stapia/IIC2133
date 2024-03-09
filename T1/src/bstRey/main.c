#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "node/node.h"

/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
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

  int node_count;
  int query_count;

  fscanf(input_file, "%d", &node_count);

  /* leemos Cada nodo */
  int k;
  fscanf(input_file, "%d", &k);
  printf("%d", k);
  Node* root;
  root = node_init(k);

  Node* node;
  for(int i=1; i<node_count; i++) {

    fscanf(input_file, "%d", &k);
    printf("%d", k);
    node = node_init(k);
    insert_node(root, node);
  
  }
  
  fscanf(input_file, "%d", &query_count);
  
  /* leemos las consultas */
  char command[32];
  int value;
  bool cambio = false;
  
  for(int i=0; i<query_count; i++) {
    printf(cambio ? "true" : "false");
    fscanf(input_file, "%s %d", command, &value);
    printf("%s %d\n", command, value);
    /* completar la revision de comando y ejecucion de los mismos */
    if (string_equals(command, "PATH")) {

      encontrar_path(root, value, cambio, output_file);
    
    } else if (string_equals(command, "DEEP")) {

      int deep = encontrar_deep(root, value, cambio, 0);
      fprintf(output_file, "%d\n", deep);
    
    } else if (string_equals(command, "ORDER")) {

      order(root, cambio, output_file);
      fprintf(output_file, "\n");
    
    } else if (string_equals(command, "DEEP-ORDER")) {
      
      deepOrder(root, node_count, cambio, output_file);
    
    } else if (string_equals(command, "INVERT")) {

      invert(root);
      deepOrder(root, node_count, false, output_file);
      cambio = !cambio;
      
    }
  }
  
  free_node(root);
  fclose(input_file);
  fclose(output_file);
  return 0;
}