#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// ############################################################################
// Vector
// ############################################################################
typedef struct {
    int length;
    int capacity;
    int* storage;
} Vec;

Vec* vec_create(void);
void vec_insert_at(Vec* vec, int at, int item);
void vec_print(Vec* vec);
void vec_free(Vec* vec);

// ############################################################################
// Linked List
// ############################################################################
typedef struct LinkedListNode {
    int item;
    struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* list_node_create(int item);

typedef struct {
    int length;
    LinkedListNode* start;
} LinkedList;

LinkedList* list_create(void);
void list_insert_at(LinkedList* list, int at, int item);
void list_print(LinkedList* list);
void list_free(LinkedList* list);

// ############################################################################
// Doubly Linked List
// ############################################################################
typedef struct DoublyLinkedListNode {
    int item;
    struct DoublyLinkedListNode* prev;
    struct DoublyLinkedListNode* next;
} DoublyLinkedListNode;

DoublyLinkedListNode* dlist_node_create(int item);

typedef struct {
    int length;
    DoublyLinkedListNode* start;
    DoublyLinkedListNode* end;
} DoublyLinkedList;

DoublyLinkedList* dlist_create(void);
void dlist_insert_at(DoublyLinkedList* l, int at, int item);
void dlist_print(DoublyLinkedList* l);
void dlist_free(DoublyLinkedList* l);
