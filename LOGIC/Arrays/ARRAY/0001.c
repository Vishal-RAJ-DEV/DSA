#include <stdio.h>

int compress(char* chars, int size) {
    int write = 0;
    for (int read = 0; read < size; read++) {
        int count = 1;
        while (read + 1 < size && chars[read] == chars[read + 1]) {
            read++;
            count++;
        }
        chars[write++] = chars[read];
        if (count > 1) {
            char buffer[10];
            int length = sprintf(buffer, "%d", count);
            for (int i = 0; i < length; i++) {
                chars[write++] = buffer[i];
            }
        }
    }
    return write;
}

int main() {
    char chars[] = {'a','a','b','b','c','c','c'};
    int size = sizeof(chars) / sizeof(chars[0]);
    int newSize = compress(chars, size);
    printf("New length: %d\n", newSize);
    for (int i = 0; i < newSize; i++) {
        printf("%c ", chars[i]);
    }
    printf("\n");
    return 0;
}
