#ifndef ACTIVITY_H             // Start of inclusion block
#define ACTIVITY_H             // Macro definition to avoid multiple inclusions

#include "utils.h"

// Declare an opaque type for the activity type
typedef struct activity Activity;


int compare(Activity * a, Activity * b);

int compareWithId(Activity * a, int activityId);


Activity * newActivity( int id,
								char* name, 
								char* descr, 
								char* course, 
								time_t insertDate, 
								time_t expiryDate, 
								time_t completionDate, 
								unsigned int totalTime, 
								unsigned int usedTime, 
								short unsigned int priority );


void deleteActivity(Activity * a);
Activity * copyActivity(Activity * old);


// getters
int getActivityId(Activity * a);
char* getActivityName(Activity * a);
char* getActivityDescr(Activity * a);
char* getActivityCourse(Activity * a);
time_t getActivityInsertDate(Activity * a);
time_t getActivityExpiryDate(Activity * a);
time_t getActivityCompletionDate(Activity * a);
char* getActivityInsertDateFormatted(Activity * a);
char* getActivityExpiryDateFormatted(Activity * a);
char* getActivityCompletionDateFormatted(Activity * a);
unsigned int getActivityTotalTime(Activity * a);
unsigned int getActivityUsedTime(Activity * a);
short unsigned int getActivityPriority(Activity * a);
char*  getActivityPriorityFormatted(Activity * a);

// setters
void setActivityId(Activity * a, int newId);
void setActivityName(Activity * a, char* name);
void setActivityDescr(Activity * a, char* descr);
void setActivityCourse(Activity * a, char* course);
void setActivityInsertDate(Activity * a, time_t insertDate);
void setActivityExpiryDate(Activity * a, time_t expiryDate);
void setActivityCompletionDate(Activity * a, time_t completionDate);
void setActivityInsertDateFormatted(Activity * a, int year, int month, int day, int hour, int min);
void setActivityExpiryDateFormatted(Activity * a, int year, int month, int day, int hour, int min);
void setActivityCompletionDateFormatted(Activity *a, int year, int month, int day, int hour, int min);
void setActivityTotalTime(Activity * a, unsigned int totalTime);
void setActivityUsedTime(Activity * a, unsigned int usedTime);
void setActivityPriority(Activity * a, short unsigned int priority);
void setActivityPriorityFormatted(Activity * a, char* priority);

//print
void print(Activity* activity);
void printActivityForList(Activity* activity);
void printActivityProgressForList(Activity* activity);

//file functions
Activity * readActivityFromFile(FILE* file);
void saveActivityToFile(FILE* file, Activity * activity);

#endif // ACTIVITY_H          // End of inclusion block
