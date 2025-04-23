#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

// Convert a string to uppercase
void to_upper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

// Convert a string to lowercase
void to_lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <inputfile> <shortfile> <longfile>\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    FILE *shortfile = fopen(argv[2], "w");
    FILE *longfile = fopen(argv[3], "w");

    if (!infile || !shortfile || !longfile) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int shortCount = 0;
    int longCount = 0;

    while (fgets(line, sizeof(line), infile)) {
        // Remove newline for clean processing
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) < 20) {
            to_upper(line);
            fprintf(shortfile, "%s\n", line);
            shortCount++;
        } else {
            to_lower(line);
            fprintf(longfile, "%s\n", line);
            longCount++;
        }
    }

    fclose(infile);
    fclose(shortfile);
    fclose(longfile);

    printf("%d lines written to %s\n", shortCount, argv[2]);
    printf("%d lines written to %s\n", longCount, argv[3]);

    return 0;
}
