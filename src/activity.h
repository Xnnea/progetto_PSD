#ifndef ACTIVITY_H             // Start of inclusion block
#define ACTIVITY_H             // Macro definition to avoid multiple inclusions

#include "utils.h"

// Declare an opaque type for the activity type
typedef struct activity* Activity;

int compareWithId(Activity a, int activityId);

// Compare 2 activities
int compareAcivityById(Activity a, Activity b);
int compareAcivityByName(Activity a, Activity b); //At now, not used
int compareAcivityByDescr(Activity a, Activity b); //At now, not used
int compareAcivityByCourse(Activity a, Activity b); //At now, not used
int compareAcivityByInsertDate(Activity a, Activity b);
int compareAcivityByExpiryDate(Activity a, Activity b);
int compareAcivityByCompletionDate(Activity a, Activity b);
int compareAcivityByTotalTime(Activity a, Activity b); //At now, not used
int compareAcivityByUsedTime(Activity a, Activity b); //At now, not used
int compareAcivityByPriority(Activity a, Activity b); //At now, not used
int compareAcivityByPercentCompletion(Activity a, Activity b);
int compareAcivityByTimeToCompletion(Activity a, Activity b); //At now, not used


Activity newActivity( int id,
								char* name, 
								char* descr, 
								char* course, 
								time_t insertDate, 
								time_t expiryDate, 
								time_t completionDate, 
								unsigned int totalTime, 
								unsigned int usedTime, 
								short unsigned int priority );


void deleteActivity(Activity a);
Activity copyActivity(Activity old); //used on node rotation (tree, on node delete)


int isActivityYetToBegin(Activity a); //used by weekly report
int isActivityCompleted(Activity a); //used by weekly report
int wasActivityCompletedAfterDate(Activity a, time_t thresholdDate); //used by weekly report
int wasActivityExpiredBeforeDate(Activity a, time_t thresholdDate); //used by weekly report


int activityCompletionPercentage(Activity activity);

// getters
int getActivityId(Activity a);
char* getActivityName(Activity a);
char* getActivityDescr(Activity a);
char* getActivityCourse(Activity a);
time_t getActivityInsertDate(Activity a); //non used
time_t getActivityExpiryDate(Activity a);
time_t getActivityCompletionDate(Activity a); //not used

unsigned int getActivityTotalTime(Activity a);
unsigned int getActivityUsedTime(Activity a);
short unsigned int getActivityPriority(Activity a); //not used
char*  getActivityPriorityFormatted(Activity a);

// setters
void setActivityId(Activity a, int newId);
void setActivityName(Activity a, char* name);
void setActivityDescr(Activity a, char* descr);
void setActivityCourse(Activity a, char* course);
void setActivityInsertDate(Activity a, time_t insertDate);
void setActivityExpiryDate(Activity a, time_t expiryDate);
void setActivityCompletionDate(Activity a, time_t completionDate);
void setActivityTotalTime(Activity a, unsigned int totalTime);
void setActivityUsedTime(Activity a, unsigned int usedTime);
void setActivityPriority(Activity a, short unsigned int priority);

//print
void printActivity(Activity activity);
void printActivityDetailWithMenu(Activity activity);
void printActivityForList(Activity activity);
void printActivityProgressForList(Activity activity);

//print to file
void printActivityToFile(Activity activity, FILE* file);
void printActivityForListToFile(Activity activity, FILE* file);
void printActivityProgressForListToFile(Activity activity, FILE* file);

//file functions
Activity readActivityFromFile(FILE* file);
void saveActivityToFile(FILE* file, Activity activity);

#endif // ACTIVITY_H          // End of inclusion block
