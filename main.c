#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Define the structure for a node in the doubly linked list
struct AssignNode {
    char name[10];        // Key as a string
    int address;          // Address as an integer
    int size;             // Size as an integer
    void *mallocAddress;  // Malloc address
    struct AssignNode* prev;    // Pointer to the previous node
    struct AssignNode* next;    // Pointer to the next node
};

struct UnAssignNode { 
    int address;          // Address as an integer
    int size;             // Size as an integer
    struct AssignNode* prev;    // Pointer to the previous node
    struct AssignNode* next;    // Pointer to the next node
};

struct AssignedList {
    int length;   // Malloc address
    struct AssignNode* head;    // Pointer to the previous node
    struct AssignNode* tail;    // Pointer to the next node
};

struct UnAssignedList {
    int length;   // Malloc address
    struct UnAssignNode* head;    // Pointer to the previous node
    struct UnAssignNode* tail;    // Pointer to the next node
};

struct AssignedList assignedList = {0, NULL, NULL};
struct UnAssignedList unAssignedList = {0, NULL, NULL};
// Function to create a new node
struct AssignNode* createAssignNode(char* name, int address, int size, void* mallocAddress) {
    struct AssignNode* newAssignNode = (struct AssignNode*)malloc(sizeof(struct AssignNode));
    
    strcpy(newAssignNode->name, name);
    newAssignNode->address = address;
    newAssignNode->size = size;
    newAssignNode->mallocAddress = mallocAddress;
    newAssignNode->prev = NULL;
    newAssignNode->next = NULL;
    
    return newAssignNode;
};

void compare(struct AssignNode* node1, struct AssignNode* node2) {
    if (node1->address < node2->address) {
        return -1;
    } else if (node1->address > node2->address) {
        return 1;
    } else {
        return 0;
    }
}

// Function to insert a node at the end of the doubly linked list
void insert(char* name, int address, int size, void* mallocAddress) {
    struct AssignNode* newAssignNode = createAssignNode(name, address, size, mallocAddress);

    if (assignedList.head != NULL && assignedList.tail != NULL) {
        struct AssignNode* compareNode = assignedList.head;
        while (compareNode->next){
            if (compareNodes(newAssignNode, compareNode)) {
                newAssignNode->next = compareNode;
                newAssignNode->prev = compareNode->prev;
                compareNode->prev->next = newAssignNode;
                compareNode->prev = newAssignNode;
            }

        }
        return;
        
        
    } else {
        assignedList.head = newAssignNode;
        assignedList.tail = newAssignNode;
    }
}

// Function to display the doubly linked list
void displayList(struct AssignNode* head) {
    struct AssignNode* temp = head;

    while (temp != NULL) {
        printf("AssignNode - Name: %s, Address: %d, Size: %d, Malloc Address: %p\n", 
               temp->name, temp->address, temp->size, temp->mallocAddress);
        temp = temp->next;
    }
}

// Function to delete a node by its name
void deleteAssignNode(struct AssignNode** head, char* name) {
    struct AssignNode* temp = *head;

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
            printf("AssignNode with name '%s' deleted.\n", name);
            return;
        }
        temp = temp->next;
    }

    printf("AssignNode with name '%s' not found.\n", name);
}

int main() {
    struct AssignNode* head = NULL;

    // Insert nodes into the doubly linked list
    insertEnd(&head, "block1", 100, 50, malloc(50));
    insertEnd(&head, "block2", 200, 100, malloc(100));
    insertEnd(&head, "block3", 300, 150, malloc(150));

    // Display the list
    printf("Doubly Linked List:\n");
    displayList(head);

    // Delete a node
    deleteAssignNode(&head, "block2");

    // Display the list again after deletion
    printf("After Deletion:\n");
    displayList(head);

    return 0;
}


TABLE_SIZE = 50;
struct MemoryAddress {
    char key[10];  // Key as a string (char array)
    int address;   // Address as an integer
    int size;      // Size as an integer
    void* mallocAddress;
};

struct MemoryAddress* assignedTable[TABLE_SIZE];
struct MemoryAddress* unAssignedTable[TABLE_SIZE];

// Hash function
unsigned int hash(char* key) {
    unsigned long int value = 0;
    for (int i = 0; i < strlen(key); i++) {
        value = value * 37 + key[i];
    }
    return value % TABLE_SIZE;
}

int findRoom(struct MemoryAddress* variable){
    for (int i = 0; i < sizeof(unAssignedTable); i++) {
        if (unAssignedTable[i].size < variable->size) {
            return i;
        }
    }
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
