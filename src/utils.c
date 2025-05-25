#include "utils.h"

// Utility function to get the maximum of two integers
int max(int a, int b) {
	return (a > b) ? a : b;
}

void minToHoursAnMinutes(unsigned int minIn, unsigned int * hoursOut, unsigned int * minOut) {
	*hoursOut = minIn / 60;
	*minOut = minIn % 60;
}

// Function to read a line from the file and allocate memory for the string
char* readLine(FILE* file) {
	char buffer[1024];
    
	// Read a line from the file
	if (fgets(buffer, sizeof(buffer), file) == NULL) {
		return NULL;
	}
    
	// Removes newline character if present
	size_t len = strlen(buffer);
	if (len > 0 && buffer[len-1] == '\n') {
		buffer[len-1] = '\0';
		len--;
	}
	
	// Removes \r character if present
	if (len > 0 && buffer[len-1] == '\r') {
		buffer[len-1] = '\0';
		len--;
	}
    
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


//Only positive number
unsigned int getChoiceWithLimits(unsigned int minLimit, unsigned int maxLimit) {
	int choice = -1;
	char buffer[10];
    
	while (choice < minLimit || choice > maxLimit) {
        
		if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			if (sscanf(buffer, "%d", &choice) != 1) {
				choice = -1;
			}
		}
      
      if (choice < minLimit || choice > maxLimit) {
      	printf("Scelta non valida. Riprova.\n");
      }
   }
   
   return choice;
}


unsigned int getChoice(unsigned int limit) {
   return getChoiceWithLimits(0, limit);
}

char* getInfoFromUser(const char* prompt) {
	char* info = NULL;
	char buffer[1024]; // input buffer
	
	if (prompt != NULL) {
		printf("\n%s", prompt);
	}
	
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		buffer[strcspn(buffer, "\n")] = 0;  // remove newline, overwrite with string terminator
		if (strlen(buffer) > 0) {
			info = copyString(buffer);
		}
	}
	
	return info;
}


time_t dateToEpoch(int year, int month, int day, int hour, int min) {
	if (year < 1900 || year > 9999) return 0;
	if (month < 1 || month > 12) return 0;
	if (day < 1 || day > 31) return 0;
	if (hour < 0 || hour > 23) return 0;
	if (min < 0 || min > 59) return 0;
	
	struct tm date;

	date.tm_sec = 0;
	date.tm_min = min;
	date.tm_hour = hour;
	date.tm_mday = day;
	date.tm_mon = month - 1;
	date.tm_year = year - 1900;
	//date.tm_wday = 0;
	//date.tm_isdst = 0;
	
	return mktime(&date);
}

time_t getDateFromUser() {
	printf("\nInserisci l'anno (nel formato YYYY, compreso tra il 2000 e il 2037):");
	int year = getChoiceWithLimits(2000, 2037);
		
	printf("\nInserisci il mese (nel formato MM):");
	int month = getChoiceWithLimits(1, 12);
		
	int isLeapYear = ( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ) ? 1 : 0;
	int febDays = 28 + isLeapYear;
	int daysInMonth[] = {31, febDays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		
	printf("\nInserisci il giorno (nel formato DD):");
	int day = getChoiceWithLimits(1, daysInMonth[month - 1] );
		
	printf("\nInserisci l'ora (senza i minuti e nel formato hh):");
	int hour = getChoiceWithLimits(0, 23);
		
	printf("\nInserisci i minuti dell'orario (nel formato mm):");
	int min = getChoiceWithLimits(0, 59);
		
	return dateToEpoch(year, month, day, hour, min);
}

void displayConfirmMenu(const char* confirmInfo) {
	printf("\n=========================\n");
	if (confirmInfo != NULL) printf("Attenzione: %s\n", confirmInfo);
	printf("1. Continua\n");
	printf("0. Annulla\n");
	printf("Scelta: ");
}


int getConfirmMenuChoice(const char* confirmInfo) {
	displayConfirmMenu(confirmInfo);
	return getChoice(1);
}