#ifndef ACTIVITIES_CONTAINER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

#define DEFAULT_ACTIVITIES_FILE "activities_list.txt"

// Declare an opaque type for the activities container
typedef struct containerItem* ActivitiesContainer;

ActivitiesContainer newActivityContainer(void);
ActivitiesContainer readActivitiesFromFile(const char* filename, int* count);
int saveActivitiesToFile(const char* filename, ActivitiesContainer container);
void deleteActivityContainer(ActivitiesContainer container);

ActivitiesContainer buildActivities();
void printActivities(ActivitiesContainer);

#endif // ACTIVITIES_CONTAINER_H          // End of inclusion block