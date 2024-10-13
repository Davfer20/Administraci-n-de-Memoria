#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_SIZE 200
#define SORTING_ALGORITHM 3 // 1: First Fit, 2: Best Fit, 3: Worst Fit, 

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

static void startMemory()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        simulatedMemory[i] = '0';
    }
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

// Function to split the doubly linked list into two halves
struct Node* split(struct Node *head) {
    struct Node *fast = head, *slow = head;

    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    struct Node *second_half = slow->next;
    slow->next = NULL;
    if (second_half)
        second_half->prev = NULL;

    return second_half;
}

// Your compareNodes function adjusted to return -1, 0, or 1
static int compareNodes(struct List* list, struct Node *node1, struct Node *node2) {
    if (list == assignedList) {
        // Compare addresses
        if (node1->address < node2->address)
            return -1;
        else if (node1->address > node2->address)
            return 1;
        else
            return 0;
    } else {
        switch (SORTING_ALGORITHM) {
            case 1: // First Fit
                if (node1->address < node2->address)
                    return -1;
                else if (node1->address > node2->address)
                    return 1;
                else
                    return 0;
            case 2: // Best Fit
                if (node1->size < node2->size)
                    return -1;
                else if (node1->size > node2->size)
                    return 1;
                else
                    return 0;
            case 3: // Worst Fit
                if (node1->size > node2->size)
                    return -1;
                else if (node1->size < node2->size)
                    return 1;
                else
                    return 0;
            default:
                return 0;
        }
    }
}

// Function to merge two sorted doubly linked lists
struct Node* merge(struct List* list, struct Node *first, struct Node *second) {
    // If first linked list is empty
    if (!first)
        return second;

    // If second linked list is empty
    if (!second)
        return first;

    // Compare the nodes using compareNodes
    if (compareNodes(list, first, second) <= 0) {
        first->next = merge(list, first->next, second);
        if (first->next)
            first->next->prev = first;
        first->prev = NULL;
        return first;
    } else {
        second->next = merge(list, first, second->next);
        if (second->next)
            second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

// Function to perform merge sort on the doubly linked list
struct Node* mergeSort(struct List* list, struct Node *head) {
    if (!head || !head->next)
        return head;

    // Split the list into two halves
    struct Node *second = split(head);

    // Recursively sort the sublists
    head = mergeSort(list, head);
    second = mergeSort(list, second);

    // Merge the sorted halves
    return merge(list, head, second);
}

// Function to sort the entire list and update head and tail pointers
void sortList(struct List *list) {
    if (!list->head)
        return;

    // Sort the list starting from head
    list->head = mergeSort(list, list->head);

    // Update the tail pointer
    struct Node *temp = list->head;
    while (temp->next)
        temp = temp->next;
    list->tail = temp;
}

// Function to add a value to the end of the list
static struct Node* addValue(struct List *list, char name, int address, int size)
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
    sortList(list);
    return newNode;
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
static signed int findHole(char name, int size)
{
    // Here the parameter size is the size of the memory to be allocated
    struct Node *holeNode = NULL;
    struct Node *unassignedNode = unassignedList->head;

    // Recorrer la lista de no asignados para encontrar un nodo donde quepa el valor
    while (unassignedNode != NULL)
    {
        // Verificar si el tamaño del nodo no asignado es suficiente
        if (unassignedNode->size >= size)
        {
            holeNode = unassignedNode; // Si el nodo cabe, se asigna a ese nodo.
            break;
        }
        unassignedNode = unassignedNode->next; // Ir al siguiente nodo no asignado
    }

    // Si no se encontró un hueco adecuado
    if (holeNode == NULL)
    {
        // Ni hay espacio suficiente
        printf("No hay espacio contiguo suficiente para asignar memoria a %c.\n", name);
        return -1;
    }

    addValue(assignedList, name, holeNode->address, size);
    int address = holeNode->address;
    holeNode->address += size;
    holeNode->size -= size;

    printf("Size holeNode", holeNode->size);
    if (holeNode->size == 0)
    {
        deleteNode(unassignedList, holeNode);
    }

    printf("Memoria asignada a %c en la direccion %d con el tamano %d.\n", name, holeNode->address - size, size);
    return address;
}

// Function to allocate memory
static void allocateMemory(char name, int size)
{
    // Case if there are no holes on memory
    if (unassignedList == NULL || unassignedList->head == NULL)
    {
        printf("No hay espacio contiguo suficiente para asignar memoria a %c.\n", name);
    }
    // Case if there are holes in memory
    else
    {
        // Know the free memory in the list
        struct Node *lastAssigned = assignedList->tail;

        // Call the type of memory allocation
        signed int address = findHole(name, size);
        if (address != -1)
        {
            for (int i = 0; i < size; i++)
            {
                simulatedMemory[address + i] = name;
            }
        } else {
            printf("No hay espacio contiguo suficiente para asignar memoria a %c.\n", name);
        }
    }
}

static void mergeMemory(struct Node *current){
    printf("Unassigned list:\n");

    printList(unassignedList);   
    struct Node *afterHoleNode = NULL;
    struct Node *beforeHoleNode = NULL;
    struct Node *unassignedNode = unassignedList->head;
    while (unassignedNode != NULL) {
        if (unassignedNode->address == (current->address + current->size)) {
            afterHoleNode = unassignedNode;
        } else if (current->address == (unassignedNode->address + unassignedNode->size)) {
            beforeHoleNode = unassignedNode;
        }
        unassignedNode = unassignedNode->next;
    }
    if (afterHoleNode != NULL && beforeHoleNode != NULL) {
        beforeHoleNode->size = current->size + afterHoleNode->size + beforeHoleNode->size;
        deleteNode(unassignedList, afterHoleNode);
        deleteNode(unassignedList, current);
    } else if (afterHoleNode != NULL) {
        current->size = current->size + afterHoleNode->size;
        deleteNode(unassignedList, afterHoleNode);
    } else if (beforeHoleNode != NULL) {
        beforeHoleNode->size = current->size + beforeHoleNode->size;
        deleteNode(unassignedList, current);
    }
}

// Function to reallocate memory
static void reallocateMemory(char name, int newSize)
{
    struct Node *current = assignedList->head;
    while (current != NULL)
    {
        if (current->name == name)
        {
            // Hay cinco casos posibles:
            
            struct Node *afterHoleNode = NULL;
            struct Node *beforeHoleNode = NULL;
            struct Node *unassignedNode = unassignedList->tail;
            while (unassignedNode != NULL) {
                // 1. Hay un hueco después de la asignación del cual se le puede asignar más memoria
                if (unassignedNode->address == (current->address + current->size)) {
                    afterHoleNode = unassignedNode;
                    if (newSize <= (unassignedNode->size + current->size)) {
                        int remainderSize = newSize - current->size;
                        current->size =  newSize;
                        unassignedNode->size -= remainderSize;
                        unassignedNode->address += remainderSize;
                        if (unassignedNode->size == 0)
                        {
                            deleteNode(unassignedList, unassignedNode);
                        }
                        
                    } 
                // 2. Hay un hueco antes de la asignación del cual se le puede asignar más memoria
                // Cambiar a que el espacio reasignado empiece desde el hueco y el address del hueco se mueve
                } else if (current->address == (unassignedNode->address + unassignedNode->size)) {
                    afterHoleNode = unassignedNode;
                    if (newSize <= (unassignedNode->size + current->size)) {
                        int remainderSize = newSize - current->size;
                        current->size =  newSize;
                        unassignedNode->size -= remainderSize;
                        unassignedNode->address += remainderSize;
                        if (unassignedNode->size == 0)
                        {
                            deleteNode(unassignedList, unassignedNode);
                        }
                    } 
                } 
                unassignedNode = unassignedNode->next;
            }
            

            // 3. Hay huecos antes y después de la asignación de los cuales se le puede asignar más memoria

            // 4. El espacio alrededor del nodo asignado está no es suficiente para la reasignación, entonces se tiene que mover a otro lado. 

            // 5. En todo ningún lado de la memoria hay campo.
            // Da error
            // Se busca el hueco
            struct Node * newUnassignedNode = addValue(unassignedList, '0', current->address, current->size);
            mergeMemory(newUnassignedNode);
            printf("Memoria liberada para %c.\n", current->name);
            for (int i = 0; i < current->size; i++)
            {
                simulatedMemory[current->address + i] = '0';
            }
            deleteNode(assignedList, current); // Eliminar de la lista
        }
        current = current->next;
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
            struct Node * newUnassignedNode = addValue(unassignedList, '0', current->address, current->size);
            mergeMemory(newUnassignedNode);
            printf("Memoria liberada para %c.\n", current->name);
            for (int i = 0; i < current->size; i++)
            {
                simulatedMemory[current->address + i] = '0';
            }
            deleteNode(assignedList, current); // Eliminar de la lista
            return;
        } else {
            current = current->next;
        }
    }
}

static void printMemory() {
    printf("Memoria simulada: \n");
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        printf("%d: %c\n", i, simulatedMemory[i]);
    }
    printf("\n");
}
