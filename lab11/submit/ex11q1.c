#include "ex11q1.h"

// ############################################################################
// Vector
// ############################################################################

// Function to create a new vector
Vec *vec_create(void){
    Vec *vec = (Vec*) malloc(sizeof(Vec));
    // TODO: vec -> length = (*vec).length = (*&a).length = Vec.length 

    vec ->length = 0; // The current number of elements that are actually stored
    vec ->capacity = 2; // The size of the array
    vec ->storage = (int *) malloc(sizeof(int) * 2); // Pointer to the actual array

    return vec;
}

// Function to insert an item at a specified index in the vector
void vec_insert_at(Vec *vec, int at, int item){
    if (vec->length == vec->capacity) {
        int new_capacity = vec->capacity * 2; // Double the capacity

        int* new_storage = (int*)realloc(vec->storage, sizeof(int) * new_capacity);

        vec->storage = new_storage;
        vec->capacity = new_capacity;
    }

    // Shift elements to the right
    for (int i = vec->length - 1; i >= at; i--) {
        vec->storage[i + 1] = vec->storage[i];
    }

    // Insert the new item
    vec->storage[at] = item;
    vec->length++;
}


void vec_print(Vec *vec){
 if (vec == NULL || vec->length == 0) {
        printf("[]\n");

    } else {
        printf("[");
        for (int i = 0; i < vec->length; i++) {
            printf("%d", vec->storage[i]);

            if (i < vec->length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

}

void vec_free(Vec* vec){
    free(vec->storage); // Free the storage
    free(vec); // Free the vector structure itself
}

// ############################################################################
// Linked List
// ############################################################################

// Function to create a new node
LinkedListNode *list_node_create(int item){
    LinkedListNode *newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    newNode->item = item;
    newNode->next = NULL;
    return newNode;

}

// Function to create a new linked list
LinkedList *list_create(void){
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));

    list->length = 0;
    list->start = NULL;
    return list;

}

// Function to insert an item at a specified index in the linked list
void list_insert_at(LinkedList *list, int at, int item){

    LinkedListNode *newNode = list_node_create(item);

    if (at == 0) {
        // Insertion at the start of the list
        newNode->next = list->start;
        list->start = newNode;

    } else {
        // Insertion at a specific position
        LinkedListNode *current = list->start;
        for (int i = 0; i < at - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->length++;
}

// Function to print the linked list
void list_print(LinkedList *list){
    if (list == NULL || list->start == NULL) {
        printf("[]\n");
        return;
    }

    LinkedListNode *current = list->start; // Point to the first node
    printf("[");
    while (current != NULL) {
        printf("%d", current->item);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next; // Current will hold the memory address
    }
    printf("]\n");

}

// Function to free the memory allocated for the linked list
void list_free(LinkedList *list){
    LinkedListNode *current = list->start; 
    while (current != NULL) {
        LinkedListNode *next = current->next;
        free(current);
        current = next;
    }

    free(list);

}


// ############################################################################
// Doubly Linked List
// ############################################################################

// Function to create a new node
DoublyLinkedListNode* dlist_node_create(int item){
    DoublyLinkedListNode* newNode = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));

    newNode->item = item;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new doubly linked list
DoublyLinkedList* dlist_create(void){
    DoublyLinkedList* l = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));

    l->length = 0;
    l->start = NULL;
    l->end = NULL;
    return l;
}

// Function to insert an item at a specified index in the doubly linked list
void dlist_insert_at(DoublyLinkedList* l, int at, int item){

    DoublyLinkedListNode* newNode = dlist_node_create(item);

    if (at == 0) {
        // Insertion at the start of the list
        newNode->next = l->start;
        if (l->start != NULL) {
            l->start->prev = newNode;
        } else {
            l->end = newNode; // List was empty
        }
        l->start = newNode;

    } else if (at == l->length) {
        // Insertion at the end of the list
        newNode->prev = l->end;
        if (l->end != NULL) {
            l->end->next = newNode;
        }
        l->end = newNode;
        if (l->start == NULL) {
            l->start = newNode; // List was empty
        }

    } else {
        DoublyLinkedListNode* current;
        // Determine whether to start from the beginning or the end
        if (at < l->length / 2) {
            // Start from the beginning
            current = l->start;
            for (int i = 0; i < at; i++) {
                current = current->next;
            }
        } else {
            // Start from the end
            current = l->end;
            for (int i = l->length; i > at; i--) {
                current = current->prev;
            }
        }
        newNode->next = current;
        newNode->prev = current->prev;
        
        if (current->prev != NULL) {
            current->prev->next = newNode;
        }
        current->prev = newNode;
    }

    l->length++;

}


void dlist_print(DoublyLinkedList* l){
    if (l == NULL || l->start == NULL) {
            printf("[]\n");
            return;
        }

    DoublyLinkedListNode* current = l->start;

    printf("[");
    while (current != NULL) {
        printf("%d", current->item);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");

}


void dlist_free(DoublyLinkedList* l){
    DoublyLinkedListNode* current = l->start;

    while (current != NULL) {
        DoublyLinkedListNode* next = current->next;
        free(current);
        current = next;
    }
    
    free(l);

}



// ############################################################################
// Main
// ############################################################################
int main(void) {
    char line[1000];
    // Uncomment each for loop as you implement that part

    clock_t begin_vec = clock();
    Vec* v = vec_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           vec_insert_at(v, b, a);
       } else {
           scanf("%s\n", line);
           vec_print(v);
       }
    }

    vec_free(v);
    clock_t end_vec = clock();

    clock_t begin_list = clock();
    LinkedList* l = list_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           list_insert_at(l, b, a);
       } else {
           scanf("%s\n", line);
           list_print(l);
       }
    }

    list_free(l);
    clock_t end_list = clock();

    clock_t begin_dlist = clock();
    DoublyLinkedList* dlist = dlist_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           dlist_insert_at(dlist, b, a);
       } else {
           scanf("%s\n", line);
           dlist_print(dlist);
       }
    }

    dlist_free(dlist);
    clock_t end_dlist = clock();

    fprintf(stderr, "Vector: %gs\n", (double)(end_vec - begin_vec) / CLOCKS_PER_SEC);
    fprintf(stderr, "Linked List: %gs\n", (double)(end_list - begin_list) / CLOCKS_PER_SEC);
    fprintf(stderr, "Doubly Linked List: %gs\n", (double)(end_dlist - begin_dlist) / CLOCKS_PER_SEC);
}
