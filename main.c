#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.c"

// // Define the structure for a node in the doubly linked list
// struct Node
// {
//   char name;         // Key as a string
//   int address;       // Address as an integer
//   int size;          // Size as an integer
//   struct Node *prev; // Pointer to the previous node
//   struct Node *next; // Pointer to the next node
// };

// struct List
// {
//   int length;        // Malloc address
//   struct Node *head; // Pointer to the previous node
//   struct Node *tail; // Pointer to the next node
// };

// struct List assignedList = {0, NULL, NULL};
// struct List unAssignedList = {0, NULL, NULL};
// // Function to create a new node
// struct Node *createNode(char *name, int address, int size, void *mallocAddress)
// {
//   struct Node *newAssignedNode = (struct Node *)malloc(sizeof(struct Node));

//   strcpy(newAssignedNode->name, name);
//   newAssignedNode->address = address;
//   newAssignedNode->size = size;
//   newAssignedNode->prev = NULL;
//   newAssignedNode->next = NULL;

//   return newAssignedNode;
// };

// int compareUnAssignedNode(struct Node *node1, struct Node *node2)
// {
//   if (node1->size < node2->size)
//   {
//     return -1;
//   }
//   else if (node1->size > node2->size)
//   {
//     return 1;
//   }
//   else
//   {
//     return 0;
//   }
// }

// // Function to insert a node at the end of the doubly linked list
// struct Node *insertAssigned(char *name, int address, int size, void *mallocAddress)
// {
//   struct Node *newAssignedNode = createAssignedNode(name, address, size, mallocAddress);

//   if (assignedList.head != NULL && assignedList.tail != NULL)
//   {
//     struct Node *compareNode = assignedList.head;
//     while (compareNode->next)
//     {
//       if (compareNode->address > newAssignedNode->address)
//       {
//         newAssignedNode->next = compareNode;
//         newAssignedNode->prev = compareNode->prev;
//         compareNode->prev->next = newAssignedNode;
//         compareNode->prev = newAssignedNode;
//         if (compareNode == assignedList.head)
//         {
//           assignedList.head = newAssignedNode;
//         }
//         return newAssignedNode;
//       }
//       else
//       {
//         compareNode = compareNode->next;
//       }
//     }
//     if (compareNode == assignedList.tail)
//     {
//       compareNode->prev = newAssignedNode;
//       newAssignedNode->next = compareNode;
//       assignedList.tail = newAssignedNode;
//     }
//   }
//   else
//   {
//     assignedList.head = newAssignedNode;
//     assignedList.tail = newAssignedNode;
//   }
//   return newAssignedNode;
// }

// int compareUnAssignedNode(int size, struct Node *node2)
// {
//   if (size < node2->size)
//   {
//     return -1;
//   }
//   else if (size > node2->size)
//   {
//     return 1;
//   }
//   else
//   {
//     return 0;
//   }
// }

// // Function to insert a node at the end of the doubly linked list
// void insertUnAssigned(int size)
// {
//   struct Node *newAssignedNode = createUnAssignedNode(0, size);

//   if (unAssignedList.head != NULL && unAssignedList.tail != NULL)
//   {
//     struct Node *compareNode = unAssignedList.head;
//     while (compareNode->next)
//     {
//       if (compareUnAssignedNode(size, compareNode))
//       {
//         newAssignedNode->next = compareNode;
//         newAssignedNode->prev = compareNode->prev;
//         compareNode->prev->next = newAssignedNode;
//         compareNode->prev = newAssignedNode;
//         if (compareNode == unAssignedList.head)
//         {
//           unAssignedList.head = newAssignedNode;
//         }
//         return;
//       }
//       else
//       {
//         compareNode = compareNode->next;
//       }
//     }
//     if (compareNode == unAssignedList.tail)
//     {
//       compareNode->prev = newAssignedNode;
//       newAssignedNode->next = compareNode;
//       unAssignedList.tail = newAssignedNode;
//       if (compareNode == unAssignedList.head)
//       {
//         unAssignedList.head = newAssignedNode;
//       }
//     }
//   }
//   else
//   {
//     unAssignedList.head = newAssignedNode;
//     unAssignedList.tail = newAssignedNode;
//   }
// }

// void insertInHole(char *variable, int size)
// {

//   struct Node *compareNode = unAssignedList.head;
//   while (compareNode)
//   {
//     if (compareNode->size >= size)
//     {
//       struct Node *newNode = insertAssigned(variable, compareNode->address, size, malloc(size));
//       compareNode->address += size;
//       compareNode->size -= size;
//       if (compareNode->size == 0)
//       {
//         // Delete the node
//         if (compareNode->prev != NULL)
//         {
//           compareNode->prev->next = compareNode->next;
//         }
//         else
//         {
//           unAssignedList.head = compareNode->next;
//         }
//         if (compareNode->next != NULL)
//         {
//           compareNode->next->prev = compareNode->prev;
//         }
//         else
//         {
//           unAssignedList.tail = compareNode->prev;
//         }
//         free(compareNode);
//       }
//       return;
//     }
//     else
//     {
//       compareNode = compareNode->next;
//     }
//   }
// }

// // Function to display the doubly linked list
// void displayList(struct Node *head)
// {
//   struct Node *temp = head;

//   while (temp != NULL)
//   {
//     printf("AssignedNode - Name: %s, Address: %d, Size: %d, Malloc Address: %p\n",
//            temp->name, temp->address, temp->size);
//     temp = temp->next;
//   }
// }

// // Function to delete a node by its name
// void deleteAssignedNode(struct Node **head, char *name)
// {
//   struct Node *temp = *head;

//   while (temp != NULL)
//   {
//     if (strcmp(temp->name, name) == 0)
//     {
//       if (temp->prev != NULL)
//       {
//         temp->prev->next = temp->next;
//       }
//       else
//       {
//         *head = temp->next;
//       }

//       if (temp->next != NULL)
//       {
//         temp->next->prev = temp->prev;
//       }

//       free(temp);
//       printf("AssignedNode with name '%s' deleted.\n", name);
//       return;
//     }
//     temp = temp->next;

//     printf("AssignedNode with name '%s' not found.\n", name);
//   }
// }

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

int main()
{
  struct List *myList = createList(); // Crear la lista

  // Añadir valores a la lista
  addValue(myList, 'A', 10, 30);
  addValue(myList, 'B', 10, 30);
  addValue(myList, 'E', 130, 10);
  addValue(myList, 'Q', 150, 60);
  addValue(myList, 'U', 10, 30);

  // Imprimir la lista en orden
  printList(myList);

  deleteValue(myList, 'E');

  printList(myList);

  return 0;
  // readFile(argv[1]); // Lee el archivo especificado como argumento
  // readFile("comands.txt"); // Lee el archivo "comands.txt"
}
