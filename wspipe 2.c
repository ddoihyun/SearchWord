#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024
#define AC_RED "\x1b[31m"

// Print text in red color
void print_red(const char *str){
    printf("%s%s\033[0m", AC_RED, str);}

// Custom implementation of strcat function
char* my_strcat(char *dest, const char* src) {
    char* ptr = dest + strlen(dest);
    while (*src != '\0') // Until the end (null character) of 'source'
        *ptr++ = *src++; // Append the string
    *ptr = '\0'; // Add the end (null character) of the string
    return dest;}

// Custom implementation of strstr function
char* my_strstr(const char * string, const char * search){
    const char* tmp = search;  // Save the address of 'search' to 'tmp'
    int cnt = -1;
    while (*string){  // Repeat until the value of 'string' is not null
        if (*string != *search){ // If the value of 'string' is different from 'search'
            cnt = -1;  // Reset the counter
            search = tmp;}  // Reset the address of 'search' to the original address
        if (*string == *search){ // If the value of 'string' is the same as 'search'
            search++;  // Increment the address of 'search'
            cnt++;   // Increment the counter
            if (*search == '\0') // If the value of 'search' is null
                return (char *)string - cnt; // Return the address of 'string' minus the counter
        }
        string++;} // Increment the address of 'string'
    return NULL;}  // If not found, return null

// Function to search for a word in the output of a command
void SearchWord(const char* url, const char* word) {
    FILE* fp = popen(url, "r");
    if (fp == NULL) {
        printf("Failed to run command.\n");
        exit(1);}

    char buff[1024];
    int cnt = 1;
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        char* found = strstr(buff, word);
        if (found != NULL) {
            // Print the sentence with the word highlighted
            printf("%d: ", cnt);
            char* ptr = buff;
            while (ptr != found) {
                printf("%c", *ptr);
                ptr++;}
            print_red(word);
            ptr += strlen(word);
            while (*ptr != '\0') {
                printf("%c", *ptr);
                ptr++;}}
        cnt++;}
    pclose(fp);}


int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Program should follow usage below\n");
        printf("$ ./wspipe <command> <search word>\n");
        exit(0);}
    
    char *url = argv[1];
    char *word = argv[2];

    SearchWord(url, word);

    return 0;}