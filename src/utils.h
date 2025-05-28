#ifndef UTILS_H             // Start of inclusion block
#define UTILS_H             // Macro definition to avoid multiple inclusions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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
 * Effects:
 * - No modification of program state
 *
 * Side Effects:
 * - None
 */
int max(int a, int b);

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
 * Effects:
 * - Modifies the values pointed to by 'hoursOut' and 'minOut'
 * 
 * Side Effects:
 * - None
 */
void minToHoursAnMinutes(unsigned int minIn, unsigned int * hoursOut, unsigned int * minOut);

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
 * Effects:
 * - Advances the current position in the file
 * - Dynamically allocates memory for the string
 * 
 * Side Effects:
 * - Heap memory allocation (must be freed by the caller)
 * - Modification of file pointer position
 */
char* readLine(FILE* file);

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
 * Effects:
 * - Dynamically allocates memory for the new string
 * 
 * Side Effects:
 * - Heap memory allocation (must be freed by the caller)
 */
char* copyString(const char* str);

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
 * Effects:
 * - Reads from standard input
 * - Displays error messages if input is not valid
 * 
 * Side Effects:
 * - Output to stdout (error messages)
 * - Reading from stdin
 * - Possible infinite loop if input continues to be invalid
 */
unsigned int getChoiceWithLimits(unsigned int minLimit, unsigned int maxLimit);

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
 * Effects:
 * - Delegates behavior to 'getChoiceWithLimits(0, limit)'
 * 
 * Side Effects:
 * - Same as 'getChoiceWithLimits'
 */
unsigned int getChoice(unsigned int limit);

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
 * Effects:
 * - Displays the prompt on stdout (if not NULL)
 * - Reads from standard input
 * - Dynamically allocates memory if input is valid
 * 
 * Side Effects:
 * - Output to stdout (prompt)
 * - Reading from stdin
 * - Heap memory allocation (must be freed by the caller)
 */
char* getInfoFromUser(const char* prompt);

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
 * Effects:
 * - No modification of program state
 * 
 * Side Effects:
 * - None
 */
time_t dateToEpoch(int year, int month, int day, int hour, int min);

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
 * Effects:
 * - Displays prompts on stdout
 * - Reads from standard input
 * - Validates user input
 * 
 * Side Effects:
 * - Output to stdout (prompts and error messages)
 * - Reading from stdin
 * - Possible loops for requesting valid input
 */
time_t getDateFromUser();

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
 * Effects:
 * - Displays output on stdout
 * 
 * Side Effects:
 * - Output to stdout
 */
void displayConfirmMenu(const char* confirmInfo);

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
 * Effects:
 * - Displays the confirmation menu
 * - Reads user choice
 * 
 * Side Effects:
 * - Output to stdout (menu)
 * - Reading from stdin
 * - Possible error messages for invalid input (via getChoice)
 */
int getConfirmMenuChoice(const char* confirmInfo);


#endif // UTILS_H          // End of inclusion block
