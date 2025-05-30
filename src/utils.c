#include "utils.h"

/*
 * max
 *
 * Syntactic Specification:
 * int max(int a, int b)
 *
 * Semantic Specification:
 * Returns the greater value between two integers.
 *
 * Preconditions:
 * - 'a' and 'b' must be valid integer values
 *
 * Postconditions:
 * - The returned value equals 'a' if 'a > b', otherwise it equals 'b'
 * - The returned value is always greater than or equal to both input parameters
 *
 * Side Effects:
 * - None
 */
int max(int a, int b) {
	return (a > b) ? a : b;
}


/*
 *  minToHoursAnMinutes
 * 
 * Syntactic Specification:
 * void minToHoursAnMinutes(unsigned int minIn, unsigned int * hoursOut, unsigned int * minOut)
 * 
 * Semantic Specification:
 * Converts a number of minutes to hours and minutes (e.g.: minIn=80 ==> hoursOut=1, minOut=20).
 * 
 * Preconditions:
 * - 'minIn' must be a valid unsigned int value
 * - 'hoursOut' must be a valid pointer to unsigned int
 * - 'minOut' must be a valid pointer to unsigned int
 * 
 * Postconditions:
 * - '*hoursOut' contains the number of complete hours (minIn / 60)
 * - '*minOut' contains the remaining minutes (minIn % 60)
 * - '*minOut' is always between 0 and 59
 * 
 * Side Effects:
 * - Modifies the values pointed to by 'hoursOut' and 'minOut'
 */
void minToHoursAnMinutes(unsigned int minIn, unsigned int * hoursOut, unsigned int * minOut) {
	*hoursOut = minIn / 60;
	*minOut = minIn % 60;
}

/*
 * readLine
 * 
 * Syntactic Specification:
 * char* readLine(FILE* file)
 * 
 * Semantic Specification:
 * Reads a line from a file and dynamically allocates memory to store the read string.
 * 
 * Preconditions:
 * - 'file' must be a valid pointer to FILE opened in read mode
 * - The file must be accessible for reading
 * 
 * Postconditions:
 * - Returns a pointer to a dynamically allocated string containing the read line (without newline character)
 * - Returns NULL if a read error or memory allocation error occurs
 * - The returned string is null-terminated with '\0'
 * 
 * Side Effects:
 * - Heap memory allocation (must be freed by the caller)
 * - Modification of file pointer position
 */
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


/*
 * copyString
 * 
 * Syntactic Specification:
 * char* copyString(const char* str)
 * 
 * Semantic Specification:
 * Creates a copy of a string by dynamically allocating the necessary memory.
 * 
 * Preconditions:
 * - 'str' can be NULL or a valid pointer to a null-terminated string
 * 
 * Postconditions:
 * - If 'str' is NULL, returns NULL
 * - If 'str' is valid, returns a pointer to a new identical string allocated dynamically
 * - Returns NULL if memory allocation fails
 * 
 * Side Effects:
 * - Dynamically allocates memory for the new string (must be freed by the caller)
 */
char* copyString(const char* str) {
	if (str == NULL) return NULL;
    
	char* newStr = (char*)malloc(strlen(str) + 1);
	if (newStr == NULL) return NULL;
    
	strcpy(newStr, str);
	return newStr;
}


/*
 * getChoiceWithLimits
 * 
 * Syntactic Specification:
 * unsigned int getChoiceWithLimits(unsigned int minLimit, unsigned int maxLimit)
 * 
 * Semantic Specification:
 * Requests the user to enter an integer between two specified limits, repeating the request until valid input is obtained.
 * 
 * Preconditions:
 * - 'minLimit' <= 'maxLimit'
 * - Standard input must be available for reading
 * 
 * Postconditions:
 * - Returns an unsigned int value between 'minLimit' and 'maxLimit' (inclusive)
 * - The returned value is the one entered by the user
 * 
 * Side Effects:
 * - Output to stdout (error messages)
 * - Reading from stdin
 * - Possible infinite loop if input continues to be invalid
 */
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

/*
 * getChoice
 * 
 * Syntactic Specification:
 * unsigned int getChoice(unsigned int limit)
 * 
 * Semantic Specification:
 * Requests the user to enter an integer between 0 and a specified limit. Used mainly in menu management.
 * 
 * Preconditions:
 * - 'limit' must be a valid unsigned int value
 * - Standard input must be available for reading
 * 
 * Postconditions:
 * - Returns an unsigned int value between 0 and 'limit' (inclusive)
 * 
 * Side Effects:
 * - Same as 'getChoiceWithLimits'
 */
unsigned int getChoice(unsigned int limit) {
   return getChoiceWithLimits(0, limit);
}

/*
 * getInfoFromUser
 * 
 * Syntactic Specification:
 * char* getInfoFromUser(const char* prompt)
 * 
 * Semantic Specification:
 * Displays a prompt to the user and reads an input string, dynamically allocating memory to store it.
 * 
 * Preconditions:
 * - 'prompt' can be NULL or a valid pointer to a string
 * - Standard input must be available for reading
 * 
 * Postconditions:
 * - If the user enters a non-empty string, returns a pointer to the dynamically allocated string
 * - If the user enters an empty string or an error occurs, returns NULL
 * - The returned string does not contain the newline character
 * 
 * Side Effects:
 * - Output to stdout (prompt)
 * - Reading from stdin
 * - Dynamically allocates memory (must be freed by the caller)
 */
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

/*
 * dateToEpoch
 * 
 * Syntactic Specification:
 * time_t dateToEpoch(int year, int month, int day, int hour, int min)
 * 
 * Semantic Specification:
 * Converts a specified date and time to Unix timestamp format (epoch time).
 * 
 * Preconditions:
 * - 'year' must be between 1900 and 2037
 * - 'month' must be between 1 and 12
 * - 'day' must be between 1 and 31
 * - 'hour' must be between 0 and 23
 * - 'min' must be between 0 and 59
 * 
 * Postconditions:
 * - If all parameters are valid, returns the corresponding Unix timestamp
 * - If one or more parameters are not valid, returns 0
 * - The timestamp represents the specified date/time
 * 
 * Side Effects:
 * - None
 */
time_t dateToEpoch(int year, int month, int day, int hour, int min) {
	if (year < 1900 || year > 2037) return 0;
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
	
	return mktime(&date);
}

/*
 * getDateFromUser
 * 
 * Syntactic Specification:
 * time_t getDateFromUser()
 * 
 * Semantic Specification:
 * Interactively requests the user to enter year, month, day, hour and minutes, validating each input and returning the corresponding Unix timestamp.
 * 
 * Preconditions:
 * - Standard input must be available for reading
 * - Standard output must be available for writing
 * 
 * Postconditions:
 * - Returns a valid Unix timestamp corresponding to the date/time entered by the user
 * - All entered values respect the specified limits (year: 2000-2037, etc.)
 * - Takes leap years into account for day validation
 * 
 * Side Effects:
 * - Output to stdout (prompts and error messages)
 * - Reading from stdin
 * - Possible loops for requesting valid input
 */
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

/*
 * displayConfirmMenu
 * 
 * Syntactic Specification:
 * void displayConfirmMenu(const char* confirmInfo)
 * 
 * Semantic Specification:
 * Displays a confirmation menu with "Continue" and "Cancel" options, preceded by an optional informational message.
 * 
 * Preconditions:
 * - 'confirmInfo' can be NULL or a valid pointer to a string
 * - Standard output must be available for writing
 * 
 * Postconditions:
 * - Displays the formatted confirmation menu
 * - If 'confirmInfo' is not NULL, displays the warning message
 * 
 * Side Effects:
 * - Displays the formatted confirmation menu
 * - If 'confirmInfo' is not NULL, displays the warning message
 */
void displayConfirmMenu(const char* confirmInfo) {
	printf("\n=========================\n");
	if (confirmInfo != NULL) printf("Attenzione: %s\n", confirmInfo);
	printf("1. Continua\n");
	printf("0. Annulla\n");
	printf("Scelta: ");
}

/*
 * getConfirmMenuChoice
 * 
 * Syntactic Specification:
 * int getConfirmMenuChoice(const char* confirmInfo)
 * 
 * Semantic Specification:
 * Displays a confirmation menu and requests the user to choose between "Continue" (1) and "Cancel" (0).
 * 
 * Preconditions:
 * - 'confirmInfo' can be NULL or a valid pointer to a string
 * - Standard input and output must be available
 * 
 * Postconditions:
 * - Returns 0 or 1 based on user choice
 * - The user must necessarily choose one of the two valid options
 * 
 * Side Effects:
 * - Output to stdout (menu)
 * - Reading from stdin
 * - Possible error messages for invalid input (via getChoice)
 */
int getConfirmMenuChoice(const char* confirmInfo) {
	displayConfirmMenu(confirmInfo);
	return getChoice(1);
}
