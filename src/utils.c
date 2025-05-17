#include "utils.h"

// Utility function to get the maximum of two integers
int max(int a, int b) {
	return (a > b) ? a : b;
}

// Function to read a line from the file and allocate memory for the string
char* readLine(FILE* file) {
	char buffer[1024];
    
	// Read a line from the file
	if (fgets(buffer, sizeof(buffer), file) == NULL) {
		return NULL;
	}
    
	// Rimuove il carattere newline se presente
	size_t len = strlen(buffer);
	if (len > 0 && buffer[len-1] == '\n') {
		buffer[len-1] = '\0';
		len--;
	}
    
	// Removes newline character if present
	if (len == 0) {
		char* emptyLine = (char*)malloc(1);
		if (emptyLine == NULL) return NULL;
		emptyLine[0] = '\0';
		return emptyLine;
	}
    
	// Allocate memory for the read string
	char* line = (char*)malloc(len + 1);
	if (line == NULL) {
		return NULL;
	}
	strcpy(line, buffer);
    
	return line;
}


// Function to copy a string allocating memory
char* copyString(const char* str) {
	if (str == NULL) return NULL;
    
	char* newStr = (char*)malloc(strlen(str) + 1);
	if (newStr == NULL) return NULL;
    
	strcpy(newStr, str);
	return newStr;
}