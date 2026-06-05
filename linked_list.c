#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Node {
    void* value;
    size_t value_size;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* first;
    Node* last;
    unsigned int size;
} LinkedList;

Node* node_create(size_t value_size) {
    Node* new_node = calloc(1, sizeof(Node));
    new_node->value_size = value_size;
    new_node->value = malloc(value_size);
    return new_node;
}

void node_destroy(Node* n) {
    free(n->value);
    free(n);
}

// Cria a lista
LinkedList* list_create() {
    LinkedList* list = calloc(1, sizeof(LinkedList));
    return list;
}

// Percorre a lista e destrói cada nó
void list_destroy(LinkedList* list) {
    Node* this = list->first;
    Node* next = list->first->next;
    while (this != NULL) {
        next = this->next;
        node_destroy(this);
        this = next;
    }
    free(list);
}

// Insere na frente
void list_push_front(LinkedList* list, void* value, unsigned int value_size) {
    // Initialize new node
    Node* new_node = calloc(1, sizeof(Node));
    new_node->value_size = value_size;
    memcpy(new_node->value, value, value_size);

    // If list is empty
    if (list->size == 0) {
        list->first = new_node;
        list->last = new_node;
        list->size += 1;
        return;
    }
    new_node->next = list->first;
    list->first = new_node;
}

// Insere atrás
void list_push_back(LinkedList* list, void* value, size_t value_size) {
    // Initialize new node
    Node* new_node = node_create(value_size);
    memcpy(new_node->value, value, value_size);

    // If list is empty
    if (list->size == 0) {
        list->first = new_node;
        list->last = new_node;
        list->size += 1;
        return;
    }
    Node* aux = list->last;
    list->last = new_node;
    aux->next = list->last;
}



int main() {
    int tmp = 10;
    LinkedList* my_list = list_create();

    list_push_back(my_list, &tmp, sizeof(tmp));
    list_push_back(my_list, &tmp, sizeof(tmp));
    list_push_back(my_list, &tmp, sizeof(tmp));

    Node* n = my_list->first;
    while (n != NULL) {
        printf("%d\n", *(int*) n->value);
        n = n->next;
    }

    list_destroy(my_list);
    return 0;
}
