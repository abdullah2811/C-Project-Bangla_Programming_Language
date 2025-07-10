#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define MAX_LINE_LEN 4096  // Maximum line length for translation

// Define keyword mappings
typedef struct {
    const char *banglish;  // Bangla in English letters
    const char *c;         // C equivalent
} Keyword;

Keyword keywords[] = {
    // Control flow
    {"jodi", "if"},
    {"nahole", "else"},
    {"nahole_jodi", "else if"},
    {"jotokkhon", "while"},
    {"jonno", "for"},
    {"bondho", "break"},
    {"chalaw", "continue"},
    {"ferot_de", "return"},

    // Data types
    {"purno", "int"},
    {"doshomik", "float"},
    {"boro_doshomik", "double"},
    {"borno", "char"},
    {"khali", "void"},
    {"thik", "bool"},

    // I/O functions
    {"lekho", "printf"},
    {"grohon", "scanf"},
    {"nirdesh", "#define"},

    // Operators
    {"soman_soman", "=="},
    {"soman", "="},
    {"soman_noi", "!="},
    {"boro", ">"},
    {"choto", "<"},
    {"boro_soman", ">="},
    {"choto_soman", "<="},
    {"jog", "+"},
    {"biyog", "-"},
    {"gun", "*"},
    {"vag", "/"},
    {"vagshesh", "%"},
    {"ba", "||"},
    {"ebong", "&&"},
    {"noi", "!"},

    // Boolean values
    {"shotto", "true"},
    {"mittha", "false"},

    // Structure keywords
    {"nirbacha", "switch"},
    {"khetre", "case"},
    {"cholbe", "default"},
    {"struct", "struct"},
    {"enum", "enum"},

    // Memory management
    {"malloc_de", "malloc"},
    {"free_de", "free"},

    // File I/O
    {"file_khol", "fopen"},
    {"file_bandho", "fclose"},
    {"file_lekho", "fprintf"},
    {"file_por", "fscanf"},

    // Special
    {"shuru", "main"},
    {"lagaao", "#include"},
    {"lib", "stdlib.h"},
    {"io", "stdio.h"},
    {"onko", "math.h"},
    {"shobdo", "string.h"},
};
int keyword_count = sizeof(keywords) / sizeof(keywords[0]);

// Replace all occurrences of a Banglish keyword with C
// Translates one line in-place, assuming 'line' has capacity up to MAX_LINE_LEN
void translate_line(char *line) {
    char temp[MAX_LINE_LEN];
    int  ti = 0;   // index in temp
    int  i  = 0;   // index in line

    while (line[i]) {
        // 1) If start of an identifier/token:
        if (isalnum(line[i]) || line[i]=='_') {
            // extract the token
            int  start = i;
            while (isalnum(line[i]) || line[i]=='_') i++;
            int len = i - start;

            char word[256];
            strncpy(word, &line[start], len);
            word[len] = '\0';

            // look for exact match in keywords[]
            const char *rep = NULL;
            for (int k = 0; k < keyword_count; k++) {
                if (strcmp(word, keywords[k].banglish) == 0) {
                    rep = keywords[k].c;
                    break;
                }
            }

            if (rep) {
                // copy replacement
                int rlen = strlen(rep);
                memcpy(&temp[ti], rep, rlen);
                ti += rlen;
            } else {
                // copy the original word
                memcpy(&temp[ti], word, len);
                ti += len;
            }
        }
        // 2) Otherwise copy delimiter character as-is
        else {
            temp[ti++] = line[i++];
        }
    }

    temp[ti] = '\0';
    // copy back into original
    strcpy(line, temp);
}


int main()
{
    // Open input.txt (Banglish code)
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    // Create output.txt (Translated C code)
    FILE *output = fopen("output.txt", "w");
    if (!output) {
        printf("Error: Could not create output.txt\n");
        return 1;
    }

    // Write C headers to output
    //fprintf(output, "#include <stdio.h>\n\nint main() {\n");

    // Read Banglish, translate line-by-line, write to output.txt
    char line[256];
    while (fgets(line, sizeof(line), input)) {
        translate_line(line);
        fprintf(output, "    %s", line);
    }

    // Close main() in output.c
    //fprintf(output, "    return 0;\n}\n");
    fclose(input);
    // After writing all translated C code to output.txt:
    fclose(output);  // Close the file first!

    // Rename .txt to .c
    if (rename("output.txt", "output.c") != 0) {
        printf("Error: Could not rename to output.c\n");
        return 1;
    }

    // Compile and run After generating output.c:
    system("gcc output.c -o output_program.exe && output_program.exe");

    // Optional: Clean up
    remove("output.c");
    remove("output_program.exe");

    return 0;
}