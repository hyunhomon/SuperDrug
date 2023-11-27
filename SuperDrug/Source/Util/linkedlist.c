#include "../../Header/Util/pch.h"

void List_Init(List* list)
{
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
}

int List_Push(List* list, void* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        return -1;
    }

    newNode->next = NULL;
    newNode->val = data;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->len++;
    return 1;
}

void* List_Pop(List* list, int index)
{
    if (index < 0 || index >= list->len) {
        return NULL;
    }

    Node* removedNode;

    if (index == 0) {
        removedNode = list->head;
        list->head = removedNode->next;

        if (list->tail == removedNode) {
            list->tail = NULL;
        }
    }
    else {
        Node* prevNode = list->head;

        for (int i = 1; i < index; i++) {
            prevNode = prevNode->next;
        }

        removedNode = prevNode->next;
        prevNode->next = removedNode->next;

        if (removedNode == list->tail) {
            list->tail = prevNode;
        }
    }

    void* val = removedNode->val;
    free(removedNode);

    list->len--;
    return val;
}

int List_Insert(List* list, int index, void* data)
{
    if (index < 0 || index > list->len) {
        return 0;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        return 0;
    }

    newNode->val = data;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;

        if (list->tail == NULL) {
            list->tail = newNode;
        }
    }
    else {
        Node* prevNode = list->head;

        for (int i = 1; i < index; i++) {
            prevNode = prevNode->next;
        }

        newNode->next = prevNode->next;
        prevNode->next = newNode;

        if (newNode->next == NULL) {
            list->tail = newNode;
        }
    }

    list->len++;
    return 1;
}

void* List_Remove(List* list, void* data)
{
    Node* prevNode = NULL;
    Node* currentNode = list->head;

    while (currentNode != NULL) {
        if (currentNode->val == data) {
            if (prevNode == NULL) {
                list->head = currentNode->next;

                if (list->tail == currentNode) {
                    list->tail = NULL;
                }
            }
            else {
                prevNode->next = currentNode->next;

                if (currentNode == list->tail) {
                    list->tail = prevNode;
                }
            }

            void* val = currentNode->val;
            free(currentNode);

            list->len--;
            return val;
        }

        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    return NULL;
}

void* List_Search(List* list, int index)
{
    if (index < 0 || index >= list->len) {
        return NULL;
    }

    Node* currentNode = list->head;

    for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }

    return currentNode->val;
}

void List_Release(List* list)
{
    Node* currentNode = list->head;

    while (currentNode != NULL) {
        Node* nextNode = currentNode->next;
        free(currentNode);

        currentNode = nextNode;
    }

    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}
