#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LEN 4096

// Define keyword mappings
typedef struct {
    const char *banglish;  // Bangla in English letters
    const char *c;         // C equivalent
} Keyword;

Keyword keywords[] = {
    // Control flow
    {"যদি", "if"},
    {"নাহলে", "else"},
    {"যতক্ষণ", "while"},
    {"জন্য", "for"},
    {"থামাও", "break"},
    {"চালাও", "continue"},
    {"ফেরত", "return"},

    // Data types
    {"পূর্ণ", "int"},
    {"ভগ্ন", "float"},
    {"বড়_ভগ্ন", "double"},
    {"বর্ণ", "char"},
    {"খালি", "void"},
    {"ঠিক", "bool"},

    // I/O functions
    {"লেখো", "printf"},
    {"নাও", "scanf"},
    {"নির্দেশ", "#define"},

    // Operators
    {"সমান_সমান", "=="},
    {"সমান", "="},
    {"সমান_নয়", "!="},
    {"বড়", ">"},
    {"ছোট", "<"},
    {"বড়_সমান", ">="},
    {"ছোট_সমান", "<="},
    {"যোগ", "+"},
    {"বিয়োগ", "-"},
    {"গুণ", "*"},
    {"ভাগ", "/"},
    {"ভাগশেষ", "%"},
    {"বা", "||"},
    {"এবং", "&&"},
    {"নয়", "!"},

    // Boolean values
    {"সত্য", "true"},
    {"মিথ্যা", "false"},

    // Structure keywords
    {"নির্বাচন", "switch"},
    {"ক্ষেত্রে", "case"},
    {"চলবে", "default"},
    {"স্ট্রাক্ট", "struct"},
    {"এনাম", "enum"},

    // Memory management
    {"ম্যালোক", "malloc"},
    {"ফ্রি", "free"},

    // File I/O
    {"ফাইলখোল", "fopen"},
    {"ফাইলবন্ধ", "fclose"},
    {"ফাইললেখ", "fprintf"},
    {"ফাইলপড়", "fscanf"},

    // Special
    {"প্রধান", "main"},
    {"লাগাও", "#include"},
    {"লাইব", "stdlib.h"},
    {"সটডিও", "stdio.h"},
    {"গণিত", "math.h"},
    {"স্ট্রিং", "string.h"},
};

int keyword_count = sizeof(keywords) / sizeof(Keyword);

// Simple UTF-8 aware string replacement
void replace_all(char *str, const char *find, const char *replace) {
    char temp[MAX_LINE_LEN];
    char *pos;
    size_t find_len = strlen(find);
    size_t replace_len = strlen(replace);
    
    while ((pos = strstr(str, find))) {
        // Copy the part before the match
        strncpy(temp, str, pos - str);
        temp[pos - str] = '\0';
        
        // Append replacement
        strcat(temp, replace);
        
        // Append the part after the match
        strcat(temp, pos + find_len);
        
        // Copy back to original string
        strcpy(str, temp);
    }
}

void translate_line(char *line) {
    // Replace multi-word keywords first (longest first)
    for (int i = 0; i < keyword_count; i++) {
        if (strstr(keywords[i].banglish, " ")) {
            replace_all(line, keywords[i].banglish, keywords[i].c);
        }
    }
    
    // Replace single-word keywords
    for (int i = 0; i < keyword_count; i++) {
        if (!strstr(keywords[i].banglish, " ")) {
            replace_all(line, keywords[i].banglish, keywords[i].c);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), input)) {
        translate_line(line);
        fprintf(output, "%s", line);
    }

    fclose(input);
    fclose(output);
    return 0;
}