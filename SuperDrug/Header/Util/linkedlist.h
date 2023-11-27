#pragma once

typedef struct node Node;
typedef struct list List;

struct node {
    void* val;
    struct node* next;
};

struct list {
    struct node* head;
    struct node* tail;
    int len;
};

void List_Init(List* list);

int List_Push(List* list, void* data);

void* List_Pop(List* list, int index);

int List_Insert(List* list, int index, void* data);

void* List_Remove(List* list, void* data);

void* List_Search(List* list, int index);

void List_Release(List* list);
