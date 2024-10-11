#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.c"

#define MEMORY_SIZE 1024

struct MemoryManager
{
  struct Node *head;        // Pointer to the start of the list
  char memory[MEMORY_SIZE]; // Simulated memory
};

// Initializes the memory manager
void initialize_memory_manager(struct MemoryManager *manager)
{
  manager->head = NULL;                    // Initialize the head of the list to NULL
  memset(manager->memory, 0, MEMORY_SIZE); // Initialize memory to 0
}

void processLine(const char *line)
{
  char command[10], name[10];
  size_t size;

  // Parse line
  if (sscanf(line, "%s %s %zu", command, name, &size) == 3)
  {
    if (strcmp(command, "ALLOC") == 0)
    {
      printf("Function ALLOC with: %s, %s, %zu\n", command, name, size);
      // Call the memory allocation function here.
    }
    else if (strcmp(command, "MALLOC") == 0)
    {
      printf("Function MALLOC with: %s, %s, %zu\n", command, name, size);
      // Call the specific function here.
    }
    else if (strcmp(command, "REALLOC") == 0)
    {
      printf("Function REALLOC with: %s, %s, %zu\n", command, name, size);
      // Call the specific function here.
    }
  }
  else if (sscanf(line, "%s %s", command, name) == 2)
  {
    if (strcmp(command, "FREE") == 0)
    {
      printf("Function FREE with: %s, %s\n", command, name);
      // Call the specific function here.
    }
  }
  else if (strcmp(command, "PRINT") == 0)
  {
    printf("Function PRINT with: %s\n", command);
    // Call the specific function here.
  }
  else
  {
    printf("Invalid command\n");
  }
}

void readLinesFromFile(const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    perror("Error opening the file");
    exit(EXIT_FAILURE);
  }

  char line[50]; // Buffer to store each line

  // Read line by line from the file
  while (fgets(line, sizeof(line), file))
  {

    if (line[0] == '#')
    {
      continue; // Ignore comments
    }

    printf("Processing line: %s\n", line);

    processLine(line); // Process the line
  }

  fclose(file); // Close the file
}

int main()
{
  struct MemoryManager manager;
  initialize_memory_manager(&manager);

  struct List *memoryList = createList(); // Create the list that stores what is in memory

  // Uncomment to add values to the list
  // addValue(myList, 'A', 10, 30);
  // addValue(myList, 'B', 10, 30);
  // addValue(myList, 'E', 130, 10);
  // addValue(myList, 'Q', 150, 60);
  // addValue(myList, 'U', 10, 30);
  // Uncomment to print the list in order
  // printList(myList);
  // deleteValue(myList, 'E');
  // printList(myList);

  // readLinesFromFile(argv[1]); // Reads the file specified as an argument
  readLinesFromFile("comands.txt");
}
