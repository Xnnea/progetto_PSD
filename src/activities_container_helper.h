#ifndef ACTIVITIES_CONTAINER_HELPER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_HELPER_H             // Macro definition to avoid multiple inclusions

#define DEFAULT_ACTIVITIES_FILE "activities_list.txt"

#include "activities_container.h"
#include "activity_helper.h"


int saveActivitiesToFile(const char* filename, ActivitiesContainer container);
ActivitiesContainer readActivitiesFromFile(const char* filename, int* count);

void addNewActivityToContainer(ActivitiesContainer container);

void printActivityWithId(ActivitiesContainer container, int activityId);
void printActivities(ActivitiesContainer container);
void printActivitiesProgress(ActivitiesContainer container);
void printActivitiesReport(ActivitiesContainer container);

void printActivitiesToFile(ActivitiesContainer container, FILE* file);
void printActivitiesProgressToFile(ActivitiesContainer container, FILE* file);
void printActivitiesReportToFile(ActivitiesContainer container, time_t beginDate, FILE* file);

#endif // ACTIVITIES_CONTAINER_HELPER_H          // End of inclusion block