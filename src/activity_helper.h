#ifndef ACTIVITY_HELPER_H             // Start of inclusion block
#define ACTIVITY_HELPER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

int isActivityYetToBegin(Activity a); //used by weekly report
int isActivityCompleted(Activity a); //used by weekly report
int wasActivityCompletedAfterDate(Activity a, time_t thresholdDate); //used by weekly report
int wasActivityExpiredBeforeDate(Activity a, time_t thresholdDate); //used by weekly report
int activityCompletionPercentage(Activity activity);
char * getActivityPriorityText(Activity activity) ;

//compare activity with an int
int compareWithId(Activity a, int activityId);

// Compare 2 activities
int compareActivityById(Activity a, Activity b);
int compareActivityByName(Activity a, Activity b); //At now, not used
int compareActivityByDescr(Activity a, Activity b); //At now, not used
int compareActivityByCourse(Activity a, Activity b); //At now, not used
int compareActivityByInsertDate(Activity a, Activity b);
int compareActivityByExpiryDate(Activity a, Activity b);
int compareActivityByCompletionDate(Activity a, Activity b);
int compareActivityByTotalTime(Activity a, Activity b); //At now, not used
int compareActivityByUsedTime(Activity a, Activity b); //At now, not used
int compareActivityByPriority(Activity a, Activity b); //At now, not used
int compareActivityByPercentCompletion(Activity a, Activity b);
int compareActivityByTimeToCompletion(Activity a, Activity b); //At now, not used

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

#endif // ACTIVITY_HELPER_H          // End of inclusion block
