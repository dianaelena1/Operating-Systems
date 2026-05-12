#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_word(char *buf, const char *word) {
    size_t wlen = strlen(word), blen = strlen(buf);
    for (char *p; (p = strstr(buf, word)); blen -= wlen)
        memmove(p, p + wlen, blen - (p - buf) - wlen + 1);
}

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("fopen"); return 1; }

    fseek(f, 0, SEEK_END); long size = ftell(f); rewind(f);
    
    char *buf = malloc(size + 1);
    fread(buf, 1, size, f); buf[size] = '\0';
    fclose(f);

    for (int i = 2; i < argc; i++) {
        remove_word(buf, argv[i]);
    }

    printf("%s", buf);
    free(buf);
    return 0;
}
