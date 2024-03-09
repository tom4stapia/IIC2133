#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma once

typedef struct hashitem_t {
    int key;
    int value;
    int mas_repetida;
    struct hashitem_t *next;
} HashItem;

int hash_function(int key, int range);
void insert_or_update(HashItem **table, int key, int letra, int table_size);
int fetch_value(HashItem **table, int key, int letra, int table_size);
void liberarTabla(HashItem **table, int table_size);
