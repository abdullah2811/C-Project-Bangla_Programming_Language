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

// Bangla to Romanized mapping
typedef struct {
    const char *bangla;
    const char *roman;
} Transliteration;

Transliteration translit_map[] = {
    {"অ", "o"}, {"আ", "aa"}, {"ই", "i"}, {"ঈ", "ee"}, {"উ", "u"},
    {"ঊ", "oo"}, {"ঋ", "ri"}, {"এ", "e"}, {"ঐ", "oi"}, {"ও", "o"},
    {"ঔ", "ou"}, {"া", "a"}, {"ি", "i"}, {"ী", "ee"}, {"ু", "u"},
    {"ূ", "oo"}, {"ৃ", "ri"}, {"ে", "e"}, {"ৈ", "oi"}, {"ো", "o"},
    {"ৌ", "ou"}, {"ক", "k"}, {"খ", "kh"}, {"গ", "g"}, {"ঘ", "gh"},
    {"ঙ", "ng"}, {"চ", "ch"}, {"ছ", "chh"}, {"জ", "j"}, {"ঝ", "jh"},
    {"ঞ", "ya"}, {"ট", "t"}, {"ঠ", "th"}, {"ড", "d"}, {"ঢ", "dh"},
    {"ণ", "n"}, {"ত", "t"}, {"থ", "th"}, {"দ", "d"}, {"ধ", "dh"},
    {"ন", "n"}, {"প", "p"}, {"ফ", "ph"}, {"ব", "b"}, {"ভ", "bh"},
    {"ম", "m"}, {"য", "z"}, {"র", "r"}, {"ল", "l"}, {"শ", "sh"},
    {"ষ", "sh"}, {"স", "s"}, {"হ", "h"}, {"ড়", "r"}, {"ঢ়", "rh"},
    {"য়", "y"}, {"ৎ", "t"}, {"ং", "ng"}, {"ঃ", "h"}, {"ঁ", "n"},
    {"্", ""}, {"্য", "y"}, {"্র", "r"}, {"্র্য", "ry"}, {"্ব", "v"},
    {"্ম", "m"}, {"্ন", "n"}, {"্ল", "l"}, {"্ষ", "sh"}, {"্শ", "sh"},
    {"্স", "s"}, {"্ছ", "cch"}, {"্জ", "jj"}, {"্ত", "t"}, {"্ত্য", "ty"},
    {"ত্র", "tr"}, {"্দ", "d"}, {"্দ্য", "dy"}, {"্ন্য", "ny"}, {"প্য", "py"},
    {"ভ্য", "bhy"}, {"ম্য", "my"}, {"ল্য", "ly"}, {"শ্য", "shy"}, 
    {"ষ্য", "shy"}, {"স্য", "sy"}, {"হ্য", "hy"}, {"ক্র", "kr"}, {"প্র", "pr"},
    {"হ্র", "hr"}, {"দ্র", "dr"}, {"ড্র", "dr"}, {"ব্র", "br"}, {"গ্র", "gr"},
    {"ফ্র", "fr"}, {"থ্র", "thr"}, {"দ্র", "dr"}, {"ষ্ণ", "shn"}, {"ক্ষ", "kkh"},
    {"জ্ঞ", "gg"}, {"শ্র", "shr"}, {"চ্চ", "cch"}, {"চ্ছ", "cch"}, {"জ্জ", "jj"},
    {"ত্ত", "tt"}, {"দ্ধ", "ddh"}, {"দ্ভ", "dbh"}, {"ড্ড", "dd"}, {"ণ্ঠ", "nth"},
    {"ন্থ", "nth"}, {"ন্ড", "nd"}, {"ন্ধ", "ndh"}, {"ম্প", "mp"}, {"ম্ফ", "mph"},
    {"্ন্ত", "nt"}, {"ণ্ড", "nd"}, {"র্প", "rp"}, {"র্ফ", "rf"}, {"র্ভ", "rbh"},
    {"র্ম", "rm"}, {"র্ত", "rt"}, {"র্দ", "rd"}, {"র্ধ", "rdh"}, {"র্ন", "rn"},
    {"র্ব", "rb"}, {"র্ল", "rl"}, {"র্শ", "rsh"}, {"র্ষ", "rsh"}, {"র্স", "rs"},
    {"র্হ", "rh"}, {"র্ট", "rt"}, {"র্ড", "rd"}, {"র্ণ", "rn"}, {"০", "0"},
    {"১", "1"}, {"২", "2"}, {"৩", "3"}, {"৪", "4"}, {"৫", "5"},
    {"৬", "6"}, {"৭", "7"}, {"৮", "8"}, {"৯", "9"}
};

int translit_count = sizeof(translit_map) / sizeof(Transliteration);

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

// Transliterate Bangla characters to Romanized
void transliterate(char *line) {
    char result[MAX_LINE_LEN * 3] = {0};  // Extra space for expansion
    int in_string = 0;  // Track if we're inside quotes
    
    for (int i = 0; line[i] != '\0';) {
        
        // Inside strings: keep original characters
        if (in_string) {
            strncat(result, &line[i], 1);
            i++;
            continue;
        }
        
        // Check for Bangla characters (UTF-8)
        if ((unsigned char)line[i] >= 0xE0 && 
            (unsigned char)line[i] <= 0xEF && 
            line[i+1] != '\0' && 
            line[i+2] != '\0') {
            
            // Extract the 3-byte UTF-8 sequence
            char bangla_char[4] = {line[i], line[i+1], line[i+2], '\0'};
            bool found = false;
            
            // Look for transliteration
            for (int j = 0; j < translit_count; j++) {
                if (strcmp(bangla_char, translit_map[j].bangla) == 0) {
                    strcat(result, translit_map[j].roman);
                    found = true;
                    i += 3;
                    break;
                }
            }
            
            // If no mapping found, keep original
            if (!found) {
                strncat(result, bangla_char, 3);
                i += 3;
            }
        } 
        // Handle ASCII characters
        else if (isascii(line[i]) || in_string) {
            strncat(result, &line[i], 1);
            i++;
        }
        // Skip invalid UTF-8 sequences
        else {
            i++;
        }
    }
    
    strcpy(line, result);
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
    
    // Second pass: transliterate non-keywords
    transliterate(line);
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