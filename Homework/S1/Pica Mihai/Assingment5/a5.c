#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s file\n", argv[0]);
    return 1;
  }

  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  char *line = NULL;
  size_t len = 0;
  int line_num = 1;

  while (getline(&line, &len, f) != -1) {
    int count = 0;

    for (int i = 0; line[i] != '\0'; i++) {
      if (line[i] >= '0' && line[i] <= '9') {
        count++;
      }
    }

    printf("Line %d: %d\n", line_num, count);
    line_num++;
  }

  free(line);
  fclose(f);

  return 0;
}
