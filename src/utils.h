#ifndef UTILS_H             // Start of inclusion block
#define UTILS_H             // Macro definition to avoid multiple inclusions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int max(int a, int b);
void minToHoursAnMinutes(unsigned int minIn, unsigned int * hoursOut, unsigned int * minOut);
char* readLine(FILE* file);
char* copyString(const char* str);
unsigned int getChoiceWithLimits(unsigned int minLimit, unsigned int maxLimit);
unsigned int getChoice(unsigned int limit);
char* getInfoFromUser(const char* prompt);

time_t dateToEpoch(int year, int month, int day, int hour, int min);
time_t getDateFromUser();
void displayConfirmMenu(const char* confirmInfo);
int getConfirmMenuChoice(const char* confirmInfo);

#endif // UTILS_H          // End of inclusion block
