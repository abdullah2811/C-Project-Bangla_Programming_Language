#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_BANGLA_TEXT_LENGTH 1000
#define MAX_ROMANIZED_LENGTH 1000

typedef struct {
    char *bangla;
    char *romanized;
} TransliterationMap;

// Transliteration table including all Bangla characters and numbers
TransliterationMap table[] = {
    {"অ", "a"}, {"আ", "aa"}, {"ই", "i"}, {"ঈ", "ii"}, {"উ", "u"},
    {"ঊ", "uu"}, {"ঋ", "ri"}, {"এ", "e"}, {"ঐ", "oi"}, {"ও", "o"}, {"ঔ", "ou"},
    
    {"া", "a"},    {"ি", "i"},    {"ী", "ii"},    {"ু", "u"},
    {"ূ", "uu"},    {"ৃ", "ri"},    {"ে", "e"},    {"ৈ", "oi"},
    {"ো", "o"},    {"ৌ", "ou"},
    
    {"ক", "k"}, {"খ", "kh"}, {"গ", "g"}, {"ঘ", "gh"}, {"ঙ", "ng"},
    {"চ", "ch"}, {"ছ", "chh"}, {"জ", "j"}, {"ঝ", "jh"}, {"ঞ", "nj"},
    {"ট", "t"}, {"ঠ", "th"}, {"ড", "d"}, {"ঢ", "dh"}, {"ণ", "n"},
    {"ত", "t"}, {"থ", "th"}, {"দ", "d"}, {"ধ", "dh"}, {"ন", "n"},
    {"প", "p"}, {"ফ", "ph"}, {"ব", "b"}, {"ভ", "bh"}, {"ম", "m"},
    {"য", "j"}, {"র", "r"}, {"ল", "l"}, {"শ", "sh"}, {"ষ", "ss"},
    {"স", "s"}, {"হ", "h"}, {"ড়", "r"}, {"ঢ়", "rh"}, {"য়", "y"},
    {"ৎ", "t"}, {"ং", "ng"}, {"ঃ", "h"}, {"ঁ", "n"},

    {"ক্য", "kya"}, {"খ্য", "khya"}, {"গ্য", "gya"}, {"ঘ্য", "ghya"},
    {"ঞ্চ", "nch"}, {"ট্য", "tya"}, {"ঠ্য", "thya"}, {"ড্য", "dya"}, {"ঢ্য", "dhya"},
    {"ত্য", "tya"}, {"থ্য", "thya"}, {"দ্য", "dya"}, {"ধ্য", "dhya"},
    {"ন্য", "nya"}, {"প্য", "pya"}, {"ফ্য", "phya"}, {"ব্য", "bya"}, {"ভ্য", "bhya"},
    {"ম্য", "mya"}, {"য্য", "ya"}, {"র্য", "rya"}, {"ল্য", "lya"},
    {"শ্য", "shya"}, {"ষ্য", "shya"}, {"স্য", "sya"}, {"হ্য", "hya"},
    {"ক্ষ্য", "ksha"}, {"ত্র্য", "trya"}, {"জ্ঞ্য", "gya"}, {"ঞ্জ", "njo"}, {"স্ব", "swa"},
    
    {"০", "0"}, {"১", "1"}, {"২", "2"}, {"৩", "3"}, {"৪", "4"},
    {"৫", "5"}, {"৬", "6"}, {"৭", "7"}, {"৮", "8"}, {"৯", "9"}
};


// Function to romanize the Bangla text
void romanize_text(const char *bangla_text, char *romanized_text) {
    size_t len = strlen(bangla_text);
    size_t idx = 0;
    
    for (size_t i = 0; i < len;)
    {
        int matched = 0;
        
        // Check for each transliteration entry in the table
        for (int j = 0; j < sizeof(table) / sizeof(TransliterationMap); j++) {
            size_t bangla_len = strlen(table[j].bangla);
            
            // Check if the current portion of the Bangla text matches the Bangla character
            if (strncmp(&bangla_text[i], table[j].bangla, bangla_len) == 0) {
                // If a match is found, append the Romanized version to the result
                strcpy(&romanized_text[idx], table[j].romanized);
                idx += strlen(table[j].romanized);
                i += bangla_len;  // Move the index forward by the length of the matched Bangla character
                matched = 1;
                break;
            }
        }
        
        // If no match was found, just copy the current character as-is (for unsupported characters)
        if (!matched) {
            romanized_text[idx++] = bangla_text[i++];
        }
    }
    
    romanized_text[idx] = '\0';  // Null-terminate the romanized string
}

#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 50

// Token structure
typedef struct {
    char type[MAX_TOKEN_LEN];
    char value[MAX_TOKEN_LEN];
} Token;

// Keyword list
const char *keywords[] = {"jodi", "natuba", "natuba_jodi", "phire_aso", 
                          "chalaw", "hattakhan", "thamaw", "jari", 
                          "pradhan", "dekhao", "nao", "purno", "vagno", 
                          "borno", "dabal", "long"};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

// Function to check if a word is a keyword
int is_keyword(const char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Tokenizer function
int tokenize(const char *code, Token tokens[]) {
    int token_count = 0;
    int i = 0;
    int len = strlen(code);

    while (i < len) {
        // Skip whitespace
        if (isspace(code[i])) {
            i++;
            continue;
        }

        // Match keywords and identifiers
        if (isalpha(code[i]) || code[i] == '_') {
            char buffer[MAX_TOKEN_LEN] = {0};
            int j = 0;

            while (isalnum(code[i]) || code[i] == '_') {
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';

            strcpy(tokens[token_count].value, buffer);
            if (is_keyword(buffer)) {
                strcpy(tokens[token_count].type, "KEYWORD");
            } else {
                strcpy(tokens[token_count].type, "IDENTIFIER");
            }
            token_count++;
        }
        // Match numbers
        else if (isdigit(code[i])) {
            char buffer[MAX_TOKEN_LEN] = {0};
            int j = 0;

            while (isdigit(code[i]) || code[i] == '.') {
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';

            strcpy(tokens[token_count].type, "NUMBER");
            strcpy(tokens[token_count].value, buffer);
            token_count++;
        }
        // Match operators
        else if (strchr("+-*/=<>!", code[i])) {
            char buffer[MAX_TOKEN_LEN] = {0};
            int j = 0;

            buffer[j++] = code[i++];
            if (code[i - 1] == '=' || code[i - 1] == '<' || code[i - 1] == '>') {
                if (code[i] == '=') {
                    buffer[j++] = code[i++];
                }
            }
            buffer[j] = '\0';

            strcpy(tokens[token_count].type, "OPERATOR");
            strcpy(tokens[token_count].value, buffer);
            token_count++;
        }
        // Match delimiters
        else if (strchr("(){};,", code[i])) {
            char buffer[2] = {code[i++], '\0'};
            strcpy(tokens[token_count].type, "DELIMITER");
            strcpy(tokens[token_count].value, buffer);
            token_count++;
        }
        // Match strings
        else if (code[i] == '"') {
            char buffer[MAX_TOKEN_LEN] = {0};
            int j = 0;
            i++; // Skip the opening quote
            while (code[i] != '"' && code[i] != '\0') {
                buffer[j++] = code[i++];
            }
            if (code[i] == '"') i++; // Skip the closing quote

            buffer[j] = '\0';
            strcpy(tokens[token_count].type, "STRING");
            strcpy(tokens[token_count].value, buffer);
            token_count++;
        }
        // Unsupported character
        else {
            fprintf(stderr, "Error: Unsupported character '%c'\n", code[i]);
            return -1;
        }
    }

    return token_count;
}

int main()
{
    char bangla_text[MAX_BANGLA_TEXT_LENGTH];
    char romanized_text[MAX_ROMANIZED_LENGTH];

    printf("Enter Bangla text: ");
    fgets(bangla_text, MAX_BANGLA_TEXT_LENGTH, stdin);

    bangla_text[strcspn(bangla_text, "\n")] = '\0';  // Remove trailing newline

    romanize_text(bangla_text, romanized_text);

    printf("Romanized text: %s\n", romanized_text);

    return 0;
}
