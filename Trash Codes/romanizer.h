#ifndef ROMANIZER_H
#define ROMANIZER_H

// Function to initialize the mapping of Bangla to Romanized characters/words.
void initialize_romanization();

// Function to convert a Bangla string to its Romanized equivalent.
void romanize_text(const char* bangla_text, char* romanized_text);

#endif
