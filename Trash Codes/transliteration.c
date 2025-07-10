#include <stdio.h>
#include <string.h>

// Define a structure for mapping Bangla characters to Romanized equivalents
typedef struct {
    char *bangla;
    char *romanized;
} TransliterationMap;

// Transliteration table
TransliterationMap table[] = {
    {"অ", "a"}, {"আ", "aa"}, {"ই", "i"}, {"ঈ", "ii"}, {"উ", "u"},
    {"ঊ", "uu"}, {"ঋ", "ri"}, {"এ", "e"}, {"ঐ", "oi"}, {"ও", "o"}, {"ঔ", "ou"},
    {"ক", "k"}, {"খ", "kh"}, {"গ", "g"}, {"ঘ", "gh"}, {"ঙ", "ng"},
    {"চ", "ch"}, {"ছ", "chh"}, {"জ", "j"}, {"ঝ", "jh"}, {"ঞ", "ny"},
    {"ট", "t"}, {"ঠ", "th"}, {"ড", "d"}, {"ঢ", "dh"}, {"ণ", "n"},
    {"ত", "t"}, {"থ", "th"}, {"দ", "d"}, {"ধ", "dh"}, {"ন", "n"},
    {"প", "p"}, {"ফ", "ph"}, {"ব", "b"}, {"ভ", "bh"}, {"ম", "m"},
    {"য", "y"}, {"র", "r"}, {"ল", "l"}, {"শ", "sh"}, {"ষ", "sh"},
    {"স", "s"}, {"হ", "h"}, {"ক্ষ", "kkh"}, {"ত্র", "tr"}, {"জ্ঞ", "gy"},
};

// Function to transliterate a Bangla string
void transliterate(char *input, char *output) {
    char *ptr = input;
    output[0] = '\0'; // Initialize the output string
    
    while (*ptr) {
        int found = 0;
        for (int i = 0; i < sizeof(table) / sizeof(table[0]); i++) {
            if (strncmp(ptr, table[i].bangla, strlen(table[i].bangla)) == 0) {
                strcat(output, table[i].romanized);
                ptr += strlen(table[i].bangla);
                found = 1;
                break;
            }
        }
        if (!found) {
            // If no match found, copy the character as is
            strncat(output, ptr, 1);
            ptr++;
        }
    }
}

int main() {
    char banglaText[256];
    char romanizedText[512];

    printf("Enter Bangla text: ");
    fgets(banglaText, sizeof(banglaText), stdin);

    transliterate(banglaText, romanizedText);

    printf("Romanized text: %s\n", romanizedText);

    return 0;
}

/*int main() {
    char banglaText[] = "বল ভষ চল চল চল রণ কন মন পণ জন গণ টনক রনক কনক জনক গনক"; // Predefined Bangla string
    char romanizedText[512];

    transliterate(banglaText, romanizedText);

    printf("Romanized text: %s\n", romanizedText);

    return 0;
}*/
