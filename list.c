#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char name;         // Key as a string
    int address;       // Address as an integer
    int size;          // Size as an integer
    struct Node *prev; // Pointer to the previous node
    struct Node *next; // Pointer to the next node
};

// Estructura para la lista que contiene los punteros head y tail
struct List
{
    struct Node *head;
    struct Node *tail;
};

// Variables globales en list.c
struct Node *globalNodeMemory = NULL; // Global para manejo de memoria
struct List *globalList = NULL;       // Lista global

// Función para crear una lista
struct List *createList()
{
    globalList = (struct List *)malloc(sizeof(struct List));
    if (globalList == NULL)
    {
        printf("Error en la asignación de memoria para la lista!\n");
        exit(1);
    }
    globalList->head = NULL;
    globalList->tail = NULL;
    return globalList;
}

// Función para crear un nuevo nodo
struct Node *createNode(char name, int address, int size)
{
    globalNodeMemory = (struct Node *)malloc(sizeof(struct Node));
    if (globalNodeMemory == NULL)
    {
        printf("Error en la asignación de memoria para el nodo!\n");
        exit(1);
    }
    globalNodeMemory->name = name;
    globalNodeMemory->address = address;
    globalNodeMemory->size = size;
    globalNodeMemory->next = NULL;
    globalNodeMemory->prev = NULL;
    return globalNodeMemory;
}

// Función para añadir un valor al final de la lista
void addValue(struct List *list, char name, int address, int size)
{
    struct Node *newNode = createNode(name, address, size); // Crear el nuevo nodo

    // Si la lista está vacía, el nuevo nodo se convierte en head y tail
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        // Enlazar el nuevo nodo al final de la lista
        list->tail->next = newNode;
        newNode->prev = list->tail; // Establecer el puntero previo del nuevo nodo
        list->tail = newNode;       // Actualizar la cola
    }
}

void deleteValue(struct List *list, char name)
{
    struct Node *current = list->head; // Comenzar desde la cabeza

    // Buscar el nodo con el valor especificado
    while (current != NULL && current->name != name)
    {
        current = current->next;
    }

    // Si no se encontró el valor
    if (current == NULL)
    {
        printf("Valor %d no encontrado en la lista.\n", name);
        return;
    }

    // Si el nodo a eliminar es la cabeza
    if (current == list->head)
    {
        list->head = current->next; // Actualizar la cabeza

        // Si la lista no está vacía, actualizar el puntero prev de la nueva cabeza
        if (list->head != NULL)
        {
            list->head->prev = NULL;
        }
    }
    // Si el nodo a eliminar es la cola
    else if (current == list->tail)
    {
        list->tail = current->prev; // Actualizar la cola
        list->tail->next = NULL;
    }
    // Si el nodo está en el medio
    else
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    // Liberar la memoria del nodo eliminado
    free(current);
    printf("Valor %d eliminado de la lista.\n", name);
}

// Función para imprimir los valores de la lista (recorrido hacia adelante)
void printList(struct List *list)
{
    struct Node *temp = list->head; // Variable local para recorrer la lista
    printf("Forward: ");
    while (temp != NULL)
    {
        printf("%c %d %d ->", temp->name, temp->address, temp->size);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Función para imprimir los valores de la lista (recorrido hacia atrás)
void printListReverse(struct List *list)
{
    struct Node *temp = list->tail; // Variable local para recorrer la lista desde el final
    printf("Backward: ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->name, temp->address, temp->size);
        temp = temp->prev;
    }
    printf("NULL\n");
}
