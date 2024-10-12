#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_SIZE 1000

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

static void sortListByAddress(struct List *list)
{
    if (list->head == NULL)
    {
        return; // Empty list, nothing to sort
    }

    int swapped;
    struct Node *current;
    struct Node *last = NULL; // End of the list

    do
    {
        swapped = 0;
        current = list->head;

        while (current->next != last) // While the current node is not the last node
        {
            if (current->address > current->next->address)
            {
                // Exchange values between adjacent nodes
                char tempName = current->name;
                int tempAddress = current->address;
                int tempSize = current->size;

                // Exchange the values of the nodes
                current->name = current->next->name;
                current->address = current->next->address;
                current->size = current->next->size;

                current->next->name = tempName;
                current->next->address = tempAddress;
                current->next->size = tempSize;

                swapped = 1; // Indicate that a swap was made
            }
            current = current->next;
        }
        last = current; // Update the last node
    } while (swapped);
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
    sortListByAddress(list); // Sort the list by address
}

// Function to delete a value from the list
static void deleteNode(struct List *list, struct Node *nodeToDelete)
{
    // Validar si el nodo a eliminar es NULL
    if (nodeToDelete == NULL)
    {
        printf("El nodo a eliminar no es válido.\n");
        return;
    }

    // Si el nodo a eliminar es el head
    if (nodeToDelete == list->head)
    {
        list->head = nodeToDelete->next; // Actualizar el head

        // Si la lista no está vacía, actualizar el puntero prev del nuevo head
        if (list->head != NULL)
        {
            list->head->prev = NULL;
        }
    }
    // Si el nodo a eliminar es el tail
    else if (nodeToDelete == list->tail)
    {
        list->tail = nodeToDelete->prev; // Actualizar el tail
        if (list->tail != NULL)
        {
            list->tail->next = NULL; // Asegurarse de que el nuevo tail no tenga next
        }
    }
    // Si el nodo está en medio
    else
    {
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
}
// Function to sort the list by address

static void bestFit(char name, int size, int freeMemory)
{
    // Here the parameter size is the size of the memory to be allocated
    struct Node *bestFitNode = NULL;
    struct Node *unassignedNode = unassignedList->head;

    // Recorrer la lista de no asignados para encontrar el mejor ajuste
    while (unassignedNode != NULL)
    {
        // Verificar si el tamaño del nodo no asignado es suficiente
        if (unassignedNode->size >= size)
        {
            // Si es la primera coincidencia o si es mejor que el anterior mejor ajuste
            if (bestFitNode == NULL || unassignedNode->size < bestFitNode->size)
            {
                bestFitNode = unassignedNode; // Actualizar el mejor ajuste
            }
        }
        unassignedNode = unassignedNode->next; // Ir al siguiente nodo no asignado
    }

    // Si no se encontró un hueco adecuado
    if (bestFitNode == NULL && freeMemory >= size)
    {
        // Adds the value to the end of the list
        struct Node *lastAssigned = assignedList->tail;
        addValue(assignedList, name, lastAssigned->address + lastAssigned->size, size);
        return;
    }

    addValue(assignedList, name, bestFitNode->address, size);

    bestFitNode->address += size;
    bestFitNode->size -= size;

    printf("Size bestNode", bestFitNode->size);
    if (bestFitNode->size == 0)
    {
        deleteNode(unassignedList, bestFitNode);
    }

    printf("Memoria asignada a %c en la direccion %d con el tamano %d.\n", name, bestFitNode->address - size, size);
}

static void wortsFit(char name, int size)
{
}

static void firstFit(char name, int size)
{
}

// Function to allocate memory
static void allocateMemory(char name, int size)
{
    // Case if there is holes con memory
    if (unassignedList == NULL || unassignedList->head == NULL)
    {
        // Falta validar cuando esta llena la memoria
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
    // Case if there are holes in memory
    else
    {
        // Know the free memory in the list
        struct Node *lastAssigned = assignedList->tail;
        int freeMemory = (MEMORY_SIZE - (lastAssigned->address + lastAssigned->size));
        printf("Memoria libre: %d\n", freeMemory);

        // Call the type of memory allocation
        bestFit(name, size, freeMemory);
    }
}

// Function to free memory
static void freeMemory(char name)
{
    struct Node *current = assignedList->head;
    while (current != NULL)
    {
        if (current->name == name)
        {
            // Free the memory from the simulated memory
            addValue(unassignedList, '0', current->address, current->size);

            printf("Memoria liberada para %c.\n", current->name);
            deleteNode(assignedList, current); // Eliminar de la lista
        }
        current = current->next;
    }
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
