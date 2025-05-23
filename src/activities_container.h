#ifndef ACTIVITIES_CONTAINER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

#define DEFAULT_ACTIVITIES_FILE "activities_list.txt"

// Declare an opaque type for the activities container
typedef struct containerItem* ActivitiesContainer;

ActivitiesContainer newActivityContainer(void);
ActivitiesContainer addNewActivityToContainer(ActivitiesContainer container);
ActivitiesContainer removeActivity(ActivitiesContainer container, int activityId);
ActivitiesContainer readActivitiesFromFile(const char* filename, int* count);
int saveActivitiesToFile(const char* filename, ActivitiesContainer container);
void deleteActivityContainer(ActivitiesContainer container);

int getNextId(ActivitiesContainer container);
void printActivityWithId(ActivitiesContainer container, int activityId);

void printActivities(ActivitiesContainer);
void printActivitiesProgress(ActivitiesContainer);
void printActivitiesReport(ActivitiesContainer);

//print to file
void printActivitiesToFile(ActivitiesContainer container, FILE* file);
void printActivitiesProgressToFile(ActivitiesContainer container, FILE* file);
void printActivitiesReportToFile(ActivitiesContainer container, time_t beginDate, FILE* file);

//used for test
Activity getActivityWithIdForTest(ActivitiesContainer container, int activityId);

#endif // ACTIVITIES_CONTAINER_H          // End of inclusion block