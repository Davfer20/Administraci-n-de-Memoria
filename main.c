#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
