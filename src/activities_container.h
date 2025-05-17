#ifndef ACTIVITIES_CONTAINER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

typedef struct activityItem* ActivitiesContainer;

ActivitiesContainer buildActivities();
void printActivities(ActivitiesContainer);

#endif // ACTIVITIES_CONTAINER_H          // End of inclusion block