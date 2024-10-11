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

// Structure for the list that contains head and tail pointers
struct List
{
    struct Node *head;
    struct Node *tail;
};

// Global variables in list.c
struct Node *globalNodeMemory = NULL; // Global for memory management
struct List *globalList = NULL;       // Global list

// Function to create a list
struct List *createList()
{
    globalList = (struct List *)malloc(sizeof(struct List));
    if (globalList == NULL)
    {
        printf("Memory allocation error for the list!\n");
        exit(1);
    }
    globalList->head = NULL;
    globalList->tail = NULL;
    return globalList;
}

// Function to create a new node
struct Node *createNode(char name, int address, int size)
{
    globalNodeMemory = (struct Node *)malloc(sizeof(struct Node));
    if (globalNodeMemory == NULL)
    {
        printf("Memory allocation error for the node!\n");
        exit(1);
    }
    globalNodeMemory->name = name;
    globalNodeMemory->address = address;
    globalNodeMemory->size = size;
    globalNodeMemory->next = NULL;
    globalNodeMemory->prev = NULL;
    return globalNodeMemory;
}

// Function to add a value to the end of the list
void addValue(struct List *list, char name, int address, int size)
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

void deleteValue(struct List *list, char name)
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
        return;
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

    // Free the memory of the deleted node
    free(current);
    printf("Value %c removed from the list.\n", name);
}

// Function to print the values of the list (forward traversal)
void printList(struct List *list)
{
    struct Node *temp = list->head; // Local variable to traverse the list
    printf("Forward: ");
    while (temp != NULL)
    {
        printf("%c %d %d ->", temp->name, temp->address, temp->size);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to print the values of the list (backward traversal)
void printListReverse(struct List *list)
{
    struct Node *temp = list->tail; // Local variable to traverse the list from the end
    printf("Backward: ");
    while (temp != NULL)
    {
        printf("%c -> ", temp->name, temp->address, temp->size);
        temp = temp->prev;
    }
    printf("NULL\n");
}
