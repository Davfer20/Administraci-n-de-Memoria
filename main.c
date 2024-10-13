#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.c"

// Function to process each line
void processLine(const char *line)
{
  char command[10]; // Buffer para almacenar el comando
  char name;        // Variable para el nombre (carácter)
  size_t size;      // Variable para el tamaño

  // Parse the line (con ALLOC, MALLOC, REALLOC)
  if (sscanf(line, "%s %c %zu", command, &name, &size) == 3) // Usa &name para pasar la dirección de name
  {
    if (strcmp(command, "ALLOC") == 0)
    {
      printf("Function ALLOC with: %s, %c, %zu\n", command, name, size);
      // allocateMemory(name, size);
    }
    else if (strcmp(command, "MALLOC") == 0)
    {
      printf("Function MALLOC with: %s, %c, %zu\n", command, name, size);
      // Implementa la función de MALLOC aquí
    }
    else if (strcmp(command, "REALLOC") == 0)
    {
      printf("Function REALLOC with: %s, %c, %zu\n", command, name, size);
      // Implementa la función de REALLOC aquí
    }
  }
  // Parse the line for FREE (no incluye tamaño)
  else if (sscanf(line, "%s %c", command, &name) == 2)
  {
    if (strcmp(command, "FREE") == 0)
    {
      printf("Function FREE with: %s, %c\n", command, name);
      freeMemory(name);
      // Implementa la función de FREE aquí
    }
  }
  // Caso de PRINT que no requiere más argumentos
  else if (strcmp(command, "PRINT") == 0)
  {
    printf("Function PRINT with: %s\n", command);
    // Implementa la función de imprimir aquí
  }
  else
  {
    printf("Invalid command: %s\n", line); // Mensaje de error si el comando no es válido
  }
}

// Function to read lines from a file
void readLinesFromFile(const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    perror("Error opening the file");
    exit(EXIT_FAILURE);
  }

  char line[50]; // Buffer para almacenar cada línea

  // Leer línea por línea del archivo
  while (fgets(line, sizeof(line), file))
  {
    if (line[0] == '#')
    {
      continue; // Ignorar comentarios
    }

    printf("Processing line: %s\n", line);
    processLine(line); // Procesar la línea
  }

  fclose(file); // Cerrar el archivo
}

int main(int argc)
{

  // Create global lists
  createList(&assignedList);
  createList(&unassignedList);
  startMemory();
  addValue(unassignedList, '0', 0, MEMORY_SIZE);

  allocateMemory('A', 10);
  allocateMemory('B', 40);
  allocateMemory('C', 30);
  allocateMemory('D', 20);
  allocateMemory('E', 25);
  allocateMemory('F', 35);
  allocateMemory('G', 40);

  //printMemory();
  freeMemory('D');
  //printMemory();
  freeMemory('B');
  freeMemory('C');
  printf("Unassigned list:\n");

  printList(unassignedList);
  
  
  // printMemory();
  // printf("Assigned list:\n");
  // printList(assignedList);

  // printf("Unassigned list:\n");

  // printList(unassignedList);

  // allocateMemory('G', 20);

  // printf("Assigned list:\n");
  // printList(assignedList);

  // printf("Unassigned list:\n");

  // printList(unassignedList);

  // readLinesFromFile("comands.txt");
  return 0;
}
