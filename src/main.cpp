#include <iostream>
using namespace std;
#include "String.h"
#include "Alloc.h"

size_t strlen(const char * s){
    size_t i = 0;
    for (;s[i] != '\0';i++){}
    return i;
}

char * strcpy( char * dest, const char * src ){
    int i = 0;
    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char * strdup(const char * s){
    char *p = new char[strlen(s) + 1];
    strcpy(p, s);
    return p;
}

char * strncpy( char * dest, const char * src, int n ){
    int i = 0;
    for (; src[i] != '\0' && i < n; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char* strcat(char* dest, const char* src) {
    size_t dest_len = strlen(dest);
    return strcpy(dest + dest_len, src);
}

char* strncat(char* dest, const char* src, int n) {
    size_t dest_len = strlen(dest);
    return strncpy(dest + dest_len, src, n);
}

int strcmp( const char * left, const char * right ){
    int i = 0;
    while (left[i] != '\0' && right[i] != '\0'){
        if (left[i] < right[i]){
            return -1;
        } else if (left[i] > right[i]){
            return 1;
        }
        i++;
    }
    if (left[i] == '\0' && right[i] == '\0'){
        return 0;
    } else if (left[i] == '\0'){
        return -1;
    } else {
        return 1;
    }
}



int main() {
    cout << strlen("C++") << endl;
    char dest[6];
    strcpy(dest, "qwerty");
    cout << dest << endl;
    char dest1[7];
    strncpy(dest, "qwerty", 3);
    cout << dest << endl;
    char dest2[20] = "Hello, ";
    const char* src = "world!";
    strcat(dest2, src);
    cout << dest2 << endl; // Output: "Hello, world!"
    char dest3[20] = "Hello, ";
    const char* src1 = "world!";
    strncat(dest3, src1, 3); // Only copy the first 3 characters of src
    cout << dest3 << endl; // Output: "Hello, wor"
    const char* s1 = "hello";
    const char* s2 = "world";
    cout << strcmp(s1, s2) << endl; // Output: -1
    cout << strcmp(s2, s1) << endl; // Output: 1
    cout << strcmp(s1, s1) << endl; // Output: 0
    return 0;
}


