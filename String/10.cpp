#include <stdio.h>

int main() {
    char sentence[1000];  // Array to store the input sentence
    int charCount = 0, wordCount = 0, i = 0;

    // Input the sentence
    printf("Enter a sentence: ");
    gets(sentence);  // Using gets to read the sentence (deprecated in modern C, but simple for learning)

    // Count characters and words
    while (sentence[i] != '\0') {
        // Count characters (all alphabetic characters and digits)
        if (sentence[i] != ' ' && sentence[i] != '\t' && sentence[i] != '\n') {
            charCount++;
        }

        // Count words (words are separated by spaces)
        if ((i == 0 || sentence[i - 1] == ' ' || sentence[i - 1] == '\t') && sentence[i] != ' ' && sentence[i] != '\t' && sentence[i] != '\n') {
            wordCount++;
        }

        i++;
    }

    // Output the results
    printf("Total number of characters: %d\n", charCount);
    printf("Total number of words: %d\n", wordCount);

    return 0;
}
