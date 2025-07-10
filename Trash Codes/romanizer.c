#include <stdio.h>
#include <string.h>
#include "romanizer.h"

#define MAX_CHAR 256  // Maximum characters in input strings

// Mapping for Bangla to Roman
char roman_map[MAX_CHAR][MAX_CHAR];  // Stores Romanized versions for each Bangla character/word.

void initialize_romanization()
{
    // Populate roman_map with Bangla to Roman equivalents
    strcpy(roman_map['অ'], "a");
    strcpy(roman_map['আ'], "aa");
    strcpy(roman_map['ই'], "i");
    strcpy(roman_map['ঈ'], "ii");
    strcpy(roman_map['উ'], "u");
    strcpy(roman_map['ঊ'], "uu");
    strcpy(roman_map['ঋ'], "ri");
    strcpy(roman_map['এ'], "e");
    strcpy(roman_map['ঐ'], "oi");
    strcpy(roman_map['ও'], "o");
    strcpy(roman_map['ঔ'], "ou");

    strcpy(roman_map['া'], "aa"); // আ-কার
    strcpy(roman_map['ি'], "i");  // ই-কার
    strcpy(roman_map['ী'], "ii"); // ঈ-কার
    strcpy(roman_map['ু'], "u");  // উ-কার
    strcpy(roman_map['ূ'], "uu"); // ঊ-কার
    strcpy(roman_map['ৃ'], "ri"); // ঋ-কার
    strcpy(roman_map['ে'], "e");  // এ-কার
    strcpy(roman_map['ৈ'], "oi"); // ঐ-কার
    strcpy(roman_map['ো'], "o");  // ও-কার
    strcpy(roman_map['ৌ'], "ou"); // ঔ-কার

    strcpy(roman_map['ক'], "k");
    strcpy(roman_map['খ'], "kh");
    strcpy(roman_map['গ'], "g");
    strcpy(roman_map['ঘ'], "gh");
    strcpy(roman_map['ঙ'], "ng");

    strcpy(roman_map['চ'], "ch");
    strcpy(roman_map['ছ'], "chh");
    strcpy(roman_map['জ'], "j");
    strcpy(roman_map['ঝ'], "jh");
    strcpy(roman_map['ঞ'], "nj");

    strcpy(roman_map['ট'], "t");
    strcpy(roman_map['ঠ'], "th");
    strcpy(roman_map['ড'], "d");
    strcpy(roman_map['ঢ'], "dh");
    strcpy(roman_map['ণ'], "n");

    strcpy(roman_map['ত'], "t");
    strcpy(roman_map['থ'], "th");
    strcpy(roman_map['দ'], "d");
    strcpy(roman_map['ধ'], "dh");
    strcpy(roman_map['ন'], "n");

    strcpy(roman_map['প'], "p");
    strcpy(roman_map['ফ'], "ph");
    strcpy(roman_map['ব'], "b");
    strcpy(roman_map['ভ'], "bh");
    strcpy(roman_map['ম'], "m");

    strcpy(roman_map['য'], "y");
    strcpy(roman_map['র'], "r");
    strcpy(roman_map['ল'], "l");
    strcpy(roman_map['শ'], "sh");
    strcpy(roman_map['ষ'], "ss");
    strcpy(roman_map['স'], "s");
    strcpy(roman_map['হ'], "h");

    strcpy(roman_map['ড়'], "r");
    strcpy(roman_map['ঢ়'], "rh");
    strcpy(roman_map['য়'], "y");
    strcpy(roman_map['ৎ'], "t");
    strcpy(roman_map['ং'], "ng");
    strcpy(roman_map['ঃ'], "h");
    strcpy(roman_map['ঁ'], "n");

    // Numbers
    strcpy(roman_map['০'], "0");
    strcpy(roman_map['১'], "1");
    strcpy(roman_map['২'], "2");
    strcpy(roman_map['৩'], "3");
    strcpy(roman_map['৪'], "4");
    strcpy(roman_map['৫'], "5");
    strcpy(roman_map['৬'], "6");
    strcpy(roman_map['৭'], "7");
    strcpy(roman_map['৮'], "8");
    strcpy(roman_map['৯'], "9");

    // Add mappings for all Bangla characters and keywords as needed.
}

void romanize_text(const char* bangla_text, char* romanized_text)
{
    int len = strlen(bangla_text);
    romanized_text[0] = '\0';  // Start with an empty string.

    for (int i = 0; i < len; i++)
    {
        if (bangla_text[i] >= 0 && bangla_text[i] < MAX_CHAR && roman_map[(int)bangla_text[i]][0] != '\0')
        {
            strcat(romanized_text, roman_map[(int)bangla_text[i]]);
        }
        else
        {
            // If character is not found in the map, use it as is (or handle as an error).
            strncat(romanized_text, &bangla_text[i], 1);
        }
    }
}
