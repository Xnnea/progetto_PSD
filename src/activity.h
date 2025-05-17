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

int getActivityId(Activity * a);
void setActivityId(Activity * a, int newId);
void print(Activity* activity);

Activity * readActivityFromFile(FILE* file);
void saveActivityToFile(FILE* file, Activity * activity);

#endif // ACTIVITY_H          // End of inclusion block
