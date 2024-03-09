#include "hash.h"

int hash_function(int key, int range) {
    return key % range;
}

void insert_or_update(HashItem **table, int key, int letra, int table_size){
    int table_index = hash_function(key, table_size);
    HashItem *item = table[table_index];
    if (item == NULL) {
        item = calloc(1, sizeof(HashItem));
        item->key = key;
        item->mas_repetida = letra;
        item->value = 1;
        item->next = NULL;
        table[table_index] = item;
    } else {
        while (item->next != NULL) {
            if (item->key == key && item->mas_repetida == letra) {
                item->value += 1;
                return;
            }
            item = item->next;
        }
        if (item->key == key && item->mas_repetida == letra) {
            item->value += 1;
            return;
        }
        item->next = calloc(1, sizeof(HashItem));
        item->next->key = key;
        item->next->value = 1;
        item->next->mas_repetida = letra;
        item->next->next = NULL;
    }
}

int fetch_value(HashItem **table, int key, int letra, int table_size) {
    int table_index = hash_function(key, table_size);
    HashItem *item = table[table_index];
    while (item != NULL) {
        if (item->key == key && item->mas_repetida == letra) {
            return item->value;
        }
        item = item->next;
    }
    return 0;
}

void liberarTabla(HashItem **table, int table_size) {
    for (int i = 0; i < table_size; i++) {
        HashItem *current = table[i];
        while (current != NULL) {
            HashItem *next = current->next;
            free(current);
            current = next;
        }
    }
    free(table);
}
