#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Define the structure for a node in the doubly linked list
struct AssignedNode {
    char name;        // Key as a string
    int address;          // Address as an integer
    int size;             // Size as an integer
    void *mallocAddress;  // Malloc address
    struct AssignedNode* prev;    // Pointer to the previous node
    struct AssignedNode* next;    // Pointer to the next node
};

struct UnAssignedNode { 
    int address;          // Address as an integer
    int size;             // Size as an integer
    struct AssignedNode* prev;    // Pointer to the previous node
    struct AssignedNode* next;    // Pointer to the next node
};

struct AssignedList {
    int length;   // Malloc address
    struct AssignedNode* head;    // Pointer to the previous node
    struct AssignedNode* tail;    // Pointer to the next node
};

struct UnAssignedList {
    int length;   // Malloc address
    struct UnAssignedNode* head;    // Pointer to the previous node
    struct UnAssignedNode* tail;    // Pointer to the next node
};

struct AssignedList assignedList = {0, NULL, NULL};
struct UnAssignedList unAssignedList = {0, NULL, NULL};
// Function to create a new node
struct AssignedNode* createAssignedNode(char* name, int address, int size, void* mallocAddress) {
    struct AssignedNode* newAssignedNode = (struct AssignedNode*)malloc(sizeof(struct AssignedNode));
    
    strcpy(newAssignedNode->name, name);
    newAssignedNode->address = address;
    newAssignedNode->size = size;
    newAssignedNode->mallocAddress = mallocAddress;
    newAssignedNode->prev = NULL;
    newAssignedNode->next = NULL;
    
    return newAssignedNode;
};

struct UnAssignedNode* createUnAssignedNode(int address, int size) {
    struct UnAssignedNode* newUnAssignedNode = (struct UnAssignedNode*)malloc(sizeof(struct UnAssignedNode));
    
    newUnAssignedNode->address = address;
    newUnAssignedNode->size = size;
    newUnAssignedNode->prev = NULL;
    newUnAssignedNode->next = NULL;
    
    return newUnAssignedNode;
};

int compareUnAssignedNode(struct AssignedNode* node1, struct AssignedNode* node2) {
    if (node1->size < node2->size) {
        return -1;
    } else if (node1->size > node2->size) {
        return 1;
    } else {
        return 0;
    }
}

// Function to insert a node at the end of the doubly linked list
struct AssignedNode* insertAssigned(char* name, int address, int size, void* mallocAddress) {
    struct AssignedNode* newAssignedNode = createAssignedNode(name, address, size, mallocAddress);

    if (assignedList.head != NULL && assignedList.tail != NULL) {
        struct AssignedNode* compareNode = assignedList.head;
        while (compareNode->next){
            if (compareNode->address > newAssignedNode->address) {
                newAssignedNode->next = compareNode;
                newAssignedNode->prev = compareNode->prev;
                compareNode->prev->next = newAssignedNode;
                compareNode->prev = newAssignedNode;
                if (compareNode == assignedList.head) {
                    assignedList.head = newAssignedNode;
                }
                return newAssignedNode;
            } else {
                compareNode = compareNode->next;
            }
        }
        if (compareNode == assignedList.tail) {
            compareNode->prev = newAssignedNode;
            newAssignedNode->next = compareNode;
            assignedList.tail = newAssignedNode;
        }
    } else {
        assignedList.head = newAssignedNode;
        assignedList.tail = newAssignedNode;
    }
    return newAssignedNode;
}

int compareUnAssignedNode(int size, struct UnAssignedNode* node2) {
    if (size < node2->size) {
        return -1;
    } else if (size > node2->size) {
        return 1;
    } else {
        return 0;
    }
}

// Function to insert a node at the end of the doubly linked list
void insertUnAssigned(int size) {
    struct UnAssignedNode* newAssignedNode = createUnAssignedNode(0, size);

    if (unAssignedList.head != NULL && unAssignedList.tail != NULL) {
        struct UnAssignedNode* compareNode = unAssignedList.head;
        while (compareNode->next){
            if (compareUnAssignedNode(size, compareNode)) {
                newAssignedNode->next = compareNode;
                newAssignedNode->prev = compareNode->prev;
                compareNode->prev->next = newAssignedNode;
                compareNode->prev = newAssignedNode;
                if (compareNode == unAssignedList.head) {
                    unAssignedList.head = newAssignedNode;
                }
                return;
            } else {
                compareNode = compareNode->next;
            }
        }
        if (compareNode == unAssignedList.tail) {
            compareNode->prev = newAssignedNode;
            newAssignedNode->next = compareNode;
            unAssignedList.tail = newAssignedNode;
            if (compareNode == unAssignedList.head) {
                unAssignedList.head = newAssignedNode;
            }
        }
    } else {
        unAssignedList.head = newAssignedNode;
        unAssignedList.tail = newAssignedNode;
    }
}

void insertInHole(char* variable, int size) {
    
    struct UnAssignedNode* compareNode = unAssignedList.head;
    while (compareNode){
        if (compareNode->size >= size) {
            struct AssignedNode* newNode = insertAssigned(variable, compareNode->address, size, malloc(size));
            compareNode->address += size;
            compareNode->size -= size;
            if (compareNode->size == 0) {
                // Delete the node
                if (compareNode->prev != NULL) {
                    compareNode->prev->next = compareNode->next;
                } else {
                    unAssignedList.head = compareNode->next;
                }
                if (compareNode->next != NULL) {
                    compareNode->next->prev = compareNode->prev;
                } else {
                    unAssignedList.tail = compareNode->prev;
                }
                free(compareNode);
            }
            return;
        } else {
            compareNode = compareNode->next;
        }
    }
}

// Function to display the doubly linked list
void displayList(struct AssignedNode* head) {
    struct AssignedNode* temp = head;

    while (temp != NULL) {
        printf("AssignedNode - Name: %s, Address: %d, Size: %d, Malloc Address: %p\n", 
               temp->name, temp->address, temp->size, temp->mallocAddress);
        temp = temp->next;
    }
}

// Function to delete a node by its name
void deleteAssignedNode(struct AssignedNode** head, char* name) {
    struct AssignedNode* temp = *head;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                *head = temp->next;
            }

            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }

            free(temp);
            printf("AssignedNode with name '%s' deleted.\n", name);
            return;
        }
        temp = temp->next;
    }

    printf("AssignedNode with name '%s' not found.\n", name);
}


// Prototipo de la función processLine
void processLine(const char *line);

void readFile(const char *fileName)
{
  FILE *file = fopen(fileName, "r");
  if (!file)
  {
    perror("Error al abrir el archivo");
    exit(EXIT_FAILURE);
  }

  char line[256];
  while (fgets(line, sizeof(line), file))
  {
    // Ignorar comentarios
    if (line[0] == '#')
      continue;
    processLine(line);
  }

  fclose(file);
}

void processLine(const char *line)
{
  char command[10], name[50];
  size_t size;

  // Parse line
  if (sscanf(line, "%s %s %zu", command, name, &size) == 3)
  {
    if (strcmp(command, "ALLOC") == 0)
    {
      printf("Function ALLOC with: %s, %s, %zu\n", command, name, size);
    }
    else if (strcmp(command, "MALLOC") == 0)
    {
      printf("Function MALLOC with: %s, %s, %zu\n", command, name, size);
    }
    else if (strcmp(command, "REALLOC") == 0)
    {
      printf("Function REALLOC with: %s, %s, %zu\n", command, name, size);
    }
  }
  else if (sscanf(line, "%s %s", command, name) == 2)
  {
    if (strcmp(command, "FREE") == 0)
    {
      printf("Function FREE with: %s, %s\n", command, name);
    }
  }
  else if (strcmp(command, "PRINT") == 0)
  {
    printf("Function PRINT with: %s\n", command);
  }
  else
  {
    printf("Invalid command\n");
  }
}

int main()
{
  // readFile(argv[1]); // Lee el archivo especificado como argumento
  readFile("comands.txt"); // Lee el archivo "comands.txt"
  return 0;
}
