#include "node.h"

Node* node_init(int value) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->value = value;
  return node;
}

int free_node(Node* node) {
  if (!node) {
    return 0;
  }
  free_node(node->left_child);
  free_node(node->right_child);
  free(node);
  return 0;
}

void insert_node(Node* root, Node* node) {
  Node* actual_node = root;
  bool is_node_inserted = false;
  while(!is_node_inserted){
    if (actual_node->value > node->value){
      if (actual_node->left_child){
        actual_node = actual_node->left_child;
      } else {
        actual_node->left_child = node;
        is_node_inserted = true;
      }
    } else {
      if (actual_node->right_child){
        actual_node = actual_node->right_child;
      } else {
        actual_node->right_child = node;
        is_node_inserted = true;
      }
    }
  }
}
    
void encontrar_path(Node* node, int value, bool cambio, FILE* output_file) { 
  Node* actual_node = node;
  if (!actual_node) {
    fprintf(output_file, "X\n");
    return;
  } else {
    if (!cambio) {
      if (actual_node->value > value) {
        fprintf(output_file, "%d ", actual_node->value);
        encontrar_path(actual_node->left_child, value, cambio, output_file);
      } else if (actual_node->value < value){
        fprintf(output_file, "%d ", actual_node->value);
        encontrar_path(actual_node->right_child, value, cambio, output_file);
      } else {
        fprintf(output_file, "%d \n", actual_node->value);
        return;           
      }
    } else {
      if (actual_node->value > value) {
        fprintf(output_file, "%d ", actual_node->value);
        encontrar_path(actual_node->right_child, value, cambio, output_file);
      } else if (actual_node->value < value){
        fprintf(output_file, "%d ", actual_node->value);
        encontrar_path(actual_node->left_child, value, cambio, output_file);
      } else {
        fprintf(output_file, "%d \n", actual_node->value);
        return;           
      }
    }
  }
}

int encontrar_deep(Node* node, int value, bool cambio, int nivel) {
  Node* actual_node = node;
  if (!actual_node) {
    return -1;
  } else {
    if (!cambio) {
      if (actual_node->value > value) {
        return encontrar_deep(actual_node->left_child, value, cambio, nivel + 1);
    } else if (actual_node->value < value){
        return encontrar_deep(actual_node->right_child, value, cambio, nivel + 1);
    } else {
        return nivel;
      }
    } else {
      if (actual_node->value > value) {
        return encontrar_deep(actual_node->right_child, value, cambio, nivel + 1);
      } else if (actual_node->value < value){
        return encontrar_deep(actual_node->left_child, value, cambio, nivel + 1);
      } else {
        return nivel;
      }
    }
  }
}

int order(Node* node, bool cambio, FILE* output_file) {
	Node* actual_node = node;
	if (!actual_node) {
	  return 0;
	}
    if (!cambio) {
      order(node->left_child, cambio, output_file);
	    fprintf(output_file, "%d ", node->value);
	    order(node->right_child, cambio, output_file);  
    } else {
      order(node->right_child, cambio, output_file);
	    fprintf(output_file, "%d ", node->value);
	    order(node->left_child, cambio, output_file);  
    }
    return 0;
}

int deepOrder(Node* root, int node_count, bool cambio, FILE* output_file) {
  if (!root) {
    return 0;
  }
  Node* queue[node_count];
  int principio = 0;
  int final = 0;
  queue[final++] = root;
  while (principio < final) {
    Node* current = queue[principio++];
    fprintf(output_file, "%d ", current->value);
    if (!cambio) {
      if (current->left_child) {
        queue[final++] = current->left_child;
      }
      if (current->right_child) {
        queue[final++] = current->right_child;
      }
    } else {
      if (current->right_child) {
        queue[final++] = current->right_child;
      }
      if (current->left_child) {
        queue[final++] = current->left_child;
      }
    }
  }
  fprintf(output_file, "\n");
  return 0;
}


void invert(Node* node) {
  if (!node) {
    return;
  } else {
    Node* temporal = node->left_child;
    node->left_child = node->right_child;
    node->right_child = temporal;
    invert(node->left_child);
    invert(node->right_child);
  }
}