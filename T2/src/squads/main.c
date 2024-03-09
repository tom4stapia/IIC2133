#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/utils.h"
#include "hash/hash.h"
#define TABLE_SIZE 100


bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}


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
    int largo;
    char input[256];
    HashItem **table = calloc(100, sizeof(HashItem*));

    while (true) {
        fscanf(input_file, "%s", input);
        if (string_equals(input, "q")) {
            break; 
        }
        if (string_equals(input, "?")) {
            fscanf(input_file, "%d", &largo);
            char escuadron[largo][2];
            for (int i = 0; i < largo; i++) {
                fscanf(input_file, "%s", escuadron[i]);
            }
            char cadenaCompleta[256] = "";
            for (int i = 0; i < largo; i++) {
                strcat(cadenaCompleta, &escuadron[i][0]);
            }
            int suma = calcularSumaEscuadron(escuadron, largo);
            char* letras = encontrarLetrasMasRepetidas(cadenaCompleta, largo);
            int suma_letras = 0;

            for (int i = 0; i < strlen(letras); i++) {
                suma_letras += letras[i];
            }
            free(letras);
            int cantidad = fetch_value(table, suma*largo, suma_letras, TABLE_SIZE);
            printf("%d \n", cantidad);
            fprintf(output_file, "%d\n", cantidad);


        } else if (string_equals(input, "+")) {
            fscanf(input_file, "%d", &largo);
            char escuadron[largo][2];
            for (int i = 0; i < largo; i++) {
                fscanf(input_file, "%s", escuadron[i]);
            }
            char cadenaCompleta[256] = "";
            for (int i = 0; i < largo; i++) {
                strcat(cadenaCompleta, &escuadron[i][0]);
            }
            int suma = calcularSumaEscuadron(escuadron, largo);
            char* letras = encontrarLetrasMasRepetidas(cadenaCompleta, largo);
            int suma_letras = 0;

            for (int i = 0; i < strlen(letras); i++) {
                suma_letras += letras[i];
            }

            free(letras);
            insert_or_update(table, suma*largo, suma_letras, TABLE_SIZE);
        }
    }
    liberarTabla(table, TABLE_SIZE);
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}

