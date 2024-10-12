#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_SIZE 1024

// Structure for the node that contains the key and the value
struct Node
{
    char name;         // Key as a string
    int address;       // Address as an integer
    int size;          // Size as an integer
    struct Node *prev; // Pointer to the previous node
    struct Node *next; // Pointer to the next node
};

// Structure for the list that contains head and tail pointers
struct List
{
    struct Node *head;
    struct Node *tail;
};

// Global variables in list.c
static char simulatedMemory[MEMORY_SIZE];
static struct List *assignedList = NULL;
static struct List *unassignedList = NULL;

// Function to create a new list
static struct List *createList(struct List **list)
{
    *list = (struct List *)malloc(sizeof(struct List));
    if (*list == NULL)
    {
        printf("Error de asignación de memoria para la lista!\n");
        exit(1);
    }
    (*list)->head = NULL;
    (*list)->tail = NULL;
    return *list;
}
// Function to create a new node
static struct Node *createNode(char name, int adress, int size)
{
    // Allocate memory for the new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Error de asignación de memoria para el nodo!\n");
        exit(1);
    }
    // Initialize the new node
    newNode->name = name;
    newNode->address = adress; // No address assigned yet
    newNode->size = size;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to add a value to the end of the list
static void addValue(struct List *list, char name, int address, int size)
{
    struct Node *newNode = createNode(name, address, size); // Create the new node

    // If the list is empty, the new node becomes head and tail
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        // Link the new node to the end of the list
        list->tail->next = newNode;
        newNode->prev = list->tail; // Set the previous pointer of the new node
        list->tail = newNode;       // Update the tail
    }
}

// Function to delete a value from the list
static void deleteValue(struct List *list, char name)
{
    struct Node *current = list->head; // Start from the head

    // Search for the node with the specified value
    while (current != NULL && current->name != name)
    {
        current = current->next;
    }

    // If the value was not found
    if (current == NULL)
    {
        printf("Value %c not found in the list.\n", name);
    }

    // If the node to delete is the head
    if (current == list->head)
    {
        list->head = current->next; // Update the head

        // If the list is not empty, update the previous pointer of the new head
        if (list->head != NULL)
        {
            list->head->prev = NULL;
        }
    }
    // If the node to delete is the tail
    else if (current == list->tail)
    {
        list->tail = current->prev; // Update the tail
        list->tail->next = NULL;
    }
    // If the node is in the middle
    else
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
}

// Función para asignar memoria
static void allocateMemory(char name, int size)
{
    // Caso si no hay agujeros en la memoria
    if (unassignedList == NULL || unassignedList->head == NULL)
    {
        if (assignedList == NULL || assignedList->head == NULL)
        {
            addValue(assignedList, name, 0, size);
            return; // Termina la función, no es necesario retornar un valor
        }
        else
        {
            struct Node *lastAssigned = assignedList->tail; // Obtener el último nodo asignado
            addValue(assignedList, name, lastAssigned->address + lastAssigned->size, size);
            return; // Termina la función
        }
    }

    // struct Node *unassignedNode = unassignedList->head;
    // while (unassignedNode != NULL)
    // {
    //     // Verificar si el tamaño del nodo no asignado es suficiente
    //     if (unassignedNode->size >= node->size)
    //     {
    //         // Asignar la dirección de memoria
    //         node->address = unassignedNode->address; // Asignar dirección
    //         // Marcar la memoria como ocupada en simulatedMemory
    //         memset(&simulatedMemory[node->address], 1, node->size); // Marcar como ocupada (puedes usar otro valor si es necesario)
    //         // Eliminar el nodo de unassignedList
    //         deleteValue(unassignedList, unassignedNode->name);
    //         // Agregar el nodo a assignedList
    //         addValue(assignedList, node->name, node->address, node->size);
    //         printf("Memoria asignada a %c en la dirección %d.\n", node->name, node->address);
    //         return; // Termina la función
    //     }
    //     unassignedNode = unassignedNode->next; // Ir al siguiente nodo no asignado
    // }
}

// Function to free memory
static void freeMemory(struct Node *node)
{
    struct Node *current = assignedList->head;
    while (current != NULL)
    {
        if (current->name == node->name)
        {
            // Liberar la memoria en el array simulado
            memset(&simulatedMemory[current->address], 0, current->size);
            deleteValue(assignedList, node->name); // Eliminar de la lista
            printf("Memoria liberada para %c.\n", node->name);
        }
        current = current->next;
    }
    printf("No se encontró memoria asignada para %c.\n", node->name);
}

// Function to print the values of the list (forward traversal)
static void printList(struct List *list)
{
    struct Node *temp = list->head; // Local variable to traverse the list
    printf("Memoria asignada: \n");
    while (temp != NULL)
    {
        printf("Nombre: %c, Desde: %d, Hasta: %d\n", temp->name, temp->address, temp->address + temp->size);
        temp = temp->next;
    }
}