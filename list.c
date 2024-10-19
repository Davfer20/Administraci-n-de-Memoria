#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_SIZE 1000
#define SORTING_ALGORITHM 1 // 1: First Fit, 2: Best Fit, 3: Worst Fit,

// Structure for the node that contains the key and the value
// Struct para los nodos de las listas.
struct Node
{
    char name;         // El nombre de la variable y valor por almacenar.
    int address;       // Dirección
    int size;          // Tamaño
    struct Node *prev; // Puntero al nodo anterior
    struct Node *next; // Puntero al próximo nodo
};

// Struct para la lista
struct List
{
    struct Node *head;
    struct Node *tail;
};

// Variables globales
static char simulatedMemory[MEMORY_SIZE];
static struct List *assignedList = NULL;
static struct List *unassignedList = NULL;

// Función para crear una lista
static struct List *createList(struct List **list)
{
    *list = (struct List *)malloc(sizeof(struct List)); // Asignar memoria para la lista
    if (*list == NULL)
    {
        printf("Error de asignación de memoria para la lista!\n");
        exit(1);
    }
    (*list)->head = NULL;
    (*list)->tail = NULL;
    return *list;
}

// Función para imprimir la lista
static void printList(struct List *list)
{
    struct Node *temp = list->head; // Variable local para iterar sobre la lista
    while (temp != NULL)
    {
        printf("Nombre: %c, Desde: %d, Hasta: %d\n", temp->name, temp->address, temp->address + temp->size);
        temp = temp->next;
    }
}

// Función para inicializar la memoria
static void startMemory()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        simulatedMemory[i] = '0';
    }
}

// Función para crear un nodo
static struct Node *createNode(char name, int address, int size)
{
    // Asignar memoria al nodo
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Error de asignación de memoria para el nodo!\n");
        exit(1);
    }
    // Inicializar el nodo
    newNode->name = name;
    newNode->address = address; // Todavía no hay una dirección asignada
    newNode->size = size;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}



// Función para dividir la lista en dos mitades. Esto se usa en el mergeSort
struct Node *split(struct Node *head)
{
    struct Node *fast = head, *slow = head;

    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    struct Node *second_half = slow->next;
    slow->next = NULL;
    if (second_half)
        second_half->prev = NULL;

    return second_half;
}

// Función para comparar dos nodos y verificar cuál debería ir antes en la lista
static int compareNodesMerge(struct List *list, struct Node *node1, struct Node *node2)
{
    if (list == assignedList)
    {
        // Compare addresses
        if (node1->address < node2->address)
            return -1;
        else if (node1->address > node2->address)
            return 1;
        else
            return 0;
    }
    else
    {
        // Sorting algorithm based on sorting type
        switch (SORTING_ALGORITHM)
        {
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

static int compareNodes(struct List* list, struct Node *node1, struct Node *node2)
{
    if (list == assignedList)
    {
        return node1->address > node2->address;
    } else {
        switch (SORTING_ALGORITHM)
        {
        case 1: // First Fit
            return node1->address > node2->address;
            break;
        case 2: // Best Fit
            return node1->size > node2->size;
            break;
        case 3: // Worst Fit
            return node1->size < node2->size;
            break;
        default:
            break;
        }
    }
    
}

// Función para fusionar dos listas
struct Node *merge(struct List *list, struct Node *first, struct Node *second)
{
    // Si la primera lista está vacía
    if (!first)
        return second;

    // Si la segunda lista está vacía
    if (!second)
        return first;

    // Se comparan los nodos y se fusionan en orden
    if (compareNodesMerge(list, first, second) <= 0)
    {
        first->next = merge(list, first->next, second);
        if (first->next)
            first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(list, first, second->next);
        if (second->next)
            second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

// Función para ordenar la lista
struct Node *mergeSort(struct List *list, struct Node *head)
{
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

// Function para ordenar la lista
void sortList(struct List *list)
{
    if (!list->head)
        return;

    // Se ordena la lista
    list->head = mergeSort(list, list->head);

    // Se actualiza la cola
    struct Node *temp = list->head;
    while (temp->next)
        temp = temp->next;
    list->tail = temp;
}

// Función para añadir un valor a la lista
static struct Node *addValue(struct List *list, char name, int address, int size)
{
    struct Node *newNode = createNode(name, address, size); // Se crea el nodo

    // Si la lista está vacía, se añade el nodo al principio
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        // Se recorre la lista para insertar el nodo con base en el ordenamiento
        struct Node *temp = list->head;
        while (temp != NULL)
        {
            if (compareNodes(list, temp, newNode) == 1)
            { // Si el nodo debe ir antes que el nodo actual
                newNode->next = temp;
                newNode->prev = temp->prev;
                if (temp->prev == NULL)
                {
                    list->head = newNode;
                }
                else
                {
                    temp->prev->next = newNode;
                }
                temp->prev = newNode;
                break;
            } else {
                temp = temp->next;
            }
        }
        if (temp == NULL)
        { // Si el nodo debe ir al final de la lista
            newNode->prev = list->tail;
            list->tail->next = newNode;
            list->tail = newNode;
        }
    }
    // sortList(list);
    return newNode;
}

// Función para borrar un nodo de una lista
static void deleteNode(struct List *list, struct Node *nodeToDelete)
{
    if (nodeToDelete == NULL)
    {
        printf("El nodo a eliminar no es válido.\n");
        return;
    }

    // Si el nodo es la cabeza
    if (nodeToDelete == list->head)
    {
        // Si la lista solo tiene un nodo
        if (list->tail == list->head)
        {
            list->tail = NULL;
        }
        list->head = nodeToDelete->next; // Se actualiza la cabeza
        
        // Si la lista no está vacía, se actualiza el puntero previo de la nueva cabeza
        if (list->head != NULL)
        {
            list->head->prev = NULL;
        }
    }
    // Si el nodo es la cola
    else if (nodeToDelete == list->tail)
    {
        list->tail = nodeToDelete->prev; // Update the tail
        if (list->tail != NULL)
        {
            list->tail->next = NULL; // Set the next pointer of the new tail to NULL
        }
    }
    // If the node to delete is in the middle
    else
    {
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    free(nodeToDelete); // Se libera la memoria
}

// Función para encontrar si hay un hueco en la memoria donde cabe el valor
static signed int findHole(char name, int size)
{
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
        // No hay espacio suficiente
        printf("No hay espacio contiguo suficiente para asignar memoria a %c.\n", name);
        return -1;
    }

    addValue(assignedList, name, holeNode->address, size); // Se añade el valor a la lista de asignados
    int address = holeNode->address; // Se guarda la dirección del nodo
    holeNode->address += size; // Se actualiza la dirección del hueco
    holeNode->size -= size; // Se actualiza el tamaño del hueco

    if (holeNode->size == 0)
    {
        deleteNode(unassignedList, holeNode); // Se elimina el nodo si ya no tiene tamaño
    }

    return address; // Se regresa la dirección del nodo
}

// Función para asignar memoria
static void allocateMemory(char name, int size)
{
    // Caso cuando no hay espacio en la memoria
    if (unassignedList == NULL || unassignedList->head == NULL)
    {
        printf("No hay espacio disponible para asignar memoria a %c.\n", name);
    }
    // Cuando hay huecos en la memoria
    else
    {
        // Se busca el hueco
        signed int address = findHole(name, size);
        if (address != -1) // Si se encontró el hueco
        {
            for (int i = 0; i < size; i++) // Se escribe en la memoria
            {
                simulatedMemory[address + i] = name;
            }
        }
        else
        { // Si no, no hay espacio suficiente
            printf("No hay espacio contiguo suficiente para asignar memoria a %c.\n", name);
        }
    }
}

// Función para fusionar la memoria
static void mergeMemory(struct Node *current)
{
    struct Node *afterHoleNode = NULL;
    struct Node *beforeHoleNode = NULL;
    struct Node *unassignedNode = unassignedList->head;
    while (unassignedNode != NULL)
    {
        if (unassignedNode->address == (current->address + current->size))
        {
            afterHoleNode = unassignedNode; // Se encuentra si hay un hueco después del que se intenta fusionar.
        }
        else if (current->address == (unassignedNode->address + unassignedNode->size))
        {
            beforeHoleNode = unassignedNode; // Se encuentra is hay un hueco antes del que se intenta fusionar.
        }
        unassignedNode = unassignedNode->next;
    }
    // Si hay un hueco antes y después
    if (afterHoleNode != NULL && beforeHoleNode != NULL)
    {
        // Se eliminan los dos nodos de la derecha, se deja solo el de la izquierda y se suma al tamaño el tamaño de los borrados
        beforeHoleNode->size = current->size + afterHoleNode->size + beforeHoleNode->size;
        deleteNode(unassignedList, afterHoleNode);
        deleteNode(unassignedList, current);
    } // Si solo hay un hueco después
    else if (afterHoleNode != NULL)
    { 
        // Se elimina el nodo después y se suma su tamaño al hueco actual
        current->size = current->size + afterHoleNode->size;
        deleteNode(unassignedList, afterHoleNode);
    }
    // Si solo hay un hueco antes
    else if (beforeHoleNode != NULL)
    {
        // Se elimina el hueco actual y se añade su tamaño al hueco anterior
        beforeHoleNode->size = current->size + beforeHoleNode->size;
        deleteNode(unassignedList, current);
    }
    sortList(unassignedList); // Se ordena la lista
}

// Función para eliminar nodos no asignados y escribir '0' en la memoria
static void freeNodeMemory(struct Node *unassignedNode, int size, int address)
{
    if (unassignedNode->size == 0)
    {
        deleteNode(unassignedList, unassignedNode);
        return;
    }
    mergeMemory(unassignedNode);
    for (int i = 0; i < size; i++)
    {
        simulatedMemory[address + i] = '0';
    }
}

// Función para reasignar memoria
static void reallocateMemory(char name, int newSize)
{
    // Se valida que el tamaño sea válido
    if (newSize <= 0)
    {
        printf("Error: El tamaño de la memoria debe ser mayor a 0.\n");
        return;
    }
    struct Node *current = assignedList->head;
    while (current != NULL)
    {
        if (current->name == name)
        {
            // Hay seis casos posibles:
            // 1. La nueva asignacion de tamaño es menor a la actual
            if (newSize <= current->size)
            {
                struct Node *unassignedNode = unassignedList->tail;
                while (unassignedNode != NULL) // Se busca si hay un hueco después del nodo asignado
                {
                    if (unassignedNode->address == (current->address + newSize))
                    {
                        // Si hay un hueco después, se le añade el tamaño restante
                        int remainderSize = current->size - newSize;
                        current->size = newSize; // Se actualiza el tamaño
                        unassignedNode->size += remainderSize; // Se actualiza el tamaño del hueco
                        unassignedNode->address -= remainderSize; // Se actualiza la dirección del hueco
                        freeNodeMemory(unassignedNode, current->size, current->address); // Se llama a esta función para escribir '0' en la memoria
                        for (int i = 0; i < current->size; i++) // Se escribe en la memoria
                        {
                            simulatedMemory[current->address + i] = current->name;
                        }
                        return;
                    } else {
                        unassignedNode = unassignedNode->prev;
                    }
                }
                // Si no hay hueco después del nodo asignado
                if (unassignedNode == NULL)
                {
                    // Se añade un hueco después del nodo asignado	
                    addValue(unassignedList, '0', current->address + newSize, current->size - newSize);
                    // Se escribe '0' en la memoria
                    for (int i = 0; i < current->size - newSize; i++)
                    {
                        simulatedMemory[current->address + newSize + i] = '0';
                    }
                    current->size = newSize; // Se actualiza el tamaño
                    for (int i = 0; i < current->size; i++) // Se escribe en la memoria
                    {
                        simulatedMemory[current->address + i] = current->name;
                    }
                    printf("Memoria reasignada para %c.\n", current->name);
                    return;
                }
            }
            // Se va a buscar si hay un hueco antes y después del nodo asignado
            struct Node *beforeHoleNode = NULL; // Hueco que está antes del hueco actual
            struct Node *unassignedNode = unassignedList->tail; // Hueco actual
            beforeHoleNode = unassignedNode->prev;
            while (unassignedNode != NULL)
            {

                // 2. Hay un hueco después de la asignación del cual se le puede asignar más memoria
                if (unassignedNode->address == (current->address + current->size) && newSize <= (unassignedNode->size + current->size))
                {
                    int remainderSize = newSize - current->size; 
                    current->size = newSize; // Se actualiza el tamaño
                    unassignedNode->size -= remainderSize; // Se actualiza el tamaño del hueco
                    unassignedNode->address += remainderSize; // Se actualiza la dirección del hueco
                    freeNodeMemory(unassignedNode, current->size, current->address); // Se escribe un 0 en la memoria
                    for (int i = 0; i < remainderSize; i++)
                    {
                        simulatedMemory[current->address+newSize - i] = current->name;
                    }
                    return;

                } // 3. Hay un hueco antes de la asignación del cual se le puede asignar más memoria
                else if (beforeHoleNode != NULL && ((current->address == (beforeHoleNode->address + beforeHoleNode->size)) && newSize <= (beforeHoleNode->size + current->size)))
                {

                    int remainderSize = newSize - current->size;
                    current->size = newSize;
                    current->address -= remainderSize;

                    beforeHoleNode->size -= remainderSize;
                    freeNodeMemory(beforeHoleNode, current->size, current->address); // Function to free memory and merge
                    for (int i = 0; i < current->size; i++)
                    {
                        simulatedMemory[current->address + i] = current->name;
                    }
                    return;
                }
                // 4. Hay huecos antes y después de la asignación de los cuales se le puede asignar más memoria
                else if (beforeHoleNode != NULL && // Validación de que beforeHoleNode no sea nulo
                         ((current->address == (beforeHoleNode->address + beforeHoleNode->size)) &&
                          (unassignedNode->address == (current->address + current->size))) &&
                         newSize <= (unassignedNode->size + current->size + beforeHoleNode->size))
                {
                    // El tamaño disponible es la suma del hueco antes, el nodo actual y el hueco después
                    int remainderSize = current->size + beforeHoleNode->size + unassignedNode->size - newSize;

                    // Mover la dirección actual al comienzo del hueco anterior
                    current->address = beforeHoleNode->address;
                    current->size = newSize;

                    // Eliminar el hueco anterior
                    deleteNode(unassignedList, beforeHoleNode);

                    // Ajustar el hueco siguiente (después del bloque actual)
                    unassignedNode->size = remainderSize;
                    unassignedNode->address = current->address + newSize;

                    // Si el hueco después ya no tiene tamaño, eliminarlo
                    if (unassignedNode->size == 0)
                    {
                        deleteNode(unassignedList, unassignedNode);
                        mergeMemory(unassignedNode);
                    } else { // Limpiar la memoria del bloque anterior
                        for (int i = 0; i < unassignedNode->size; i++)
                        {
                            simulatedMemory[unassignedNode->address + i] = '0';
                        }
                    }
                    // Escribir en la memoria el valor que había en el bloque anterior
                    for (int i = 0; i < current->size; i++)
                    {
                        simulatedMemory[current->address + i] = current->name;
                    }
                    printf("Memoria reasignada para %c.\n", current->name);
                    return;
                } // 5. El espacio alrededor del nodo asignado no es suficiente para la reasignación, entonces se tiene que mover a otro lado.
                else if ((unassignedNode->address == (current->address + current->size)) || (beforeHoleNode != NULL && (current->address == (beforeHoleNode->address + beforeHoleNode->size))))
                {
                    // Se busca un hueco donde quepa el nuevo tamaño
                    int newAddress = findHole(current->name, newSize);
                    if (newAddress != -1) // Si hay un hueco donde cabe
                    {
                        for (int i = 0; i < current->size; i++) // Se reinicia la memoria donde está el nodo actual
                        {
                            simulatedMemory[current->address + i] = '0';
                        }
                        struct Node *newUnassignedNode = addValue(unassignedList, '0', current->address, current->size); // Se añade un hueco donde está el nodo actual
                        mergeMemory(newUnassignedNode); // Se fusiona la memoria
                        deleteNode(assignedList, current); // Eliminar de la lista de asignados, ya que se insertó en la nueva posición
                        
                        for (int i = 0; i < newSize; i++)
                        { // Se escribe en la memoria el nuevo valor
                            simulatedMemory[newAddress + i] = current->name;
                        }
                        printf("Memoria reasignada para %c.\n", current->name);
                        return;
                    } else {
                        // 6. En ningún lado de la memoria hay suficiente espacio, da error.
                        printf("Error: No hay espacio suficiente para reasignar %c.\n", current->name);
                        return;
                    }
                } else {
                    unassignedNode = unassignedNode->prev;
                    if (beforeHoleNode != NULL)
                    {
                        beforeHoleNode = unassignedNode->prev;
                    }
                }
            }
        }
        current = current->next;
    }
}

// Esta función libera la memoria de un nodo asignado
static void freeMemory(char name)
{
    struct Node *current = assignedList->head;
    while (current != NULL)
    {
        if (current->name == name)
        {
            struct Node *newUnassignedNode = addValue(unassignedList, '0', current->address, current->size); // Se añade un hueco
            mergeMemory(newUnassignedNode); // Se fusiona la memoria
            printf("Memoria liberada para %c.\n", current->name);
            for (int i = 0; i < current->size; i++)
            {
                simulatedMemory[current->address + i] = '0'; // Se reinicia la memoria
            }
            deleteNode(assignedList, current); // Eliminar de la lista
            return;
        }
        else
        {
            current = current->next;
        }
    }
}

// Se imprime la memoria
static void printMemory()
{
    printf("Memoria simulada:\n");
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        // Print the index and character in the same line
        printf("%d: %c ", i, simulatedMemory[i]);

        // After printing 100 characters, print a new line
        if ((i + 1) % 100 == 0)
        {
            printf("\n");
        }
    }

    // Add a new line at the end if MEMORY_SIZE is not a multiple of 100
    if (MEMORY_SIZE % 100 != 0)
    {
        printf("\n");
    }
}


static void reset(){
    unassignedList = createList(&unassignedList);
    assignedList = createList(&assignedList);
    startMemory();    
    addValue(unassignedList, '0', 0, MEMORY_SIZE);
}