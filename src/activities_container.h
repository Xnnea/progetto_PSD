#ifndef ACTIVITIES_CONTAINER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

// Declare an opaque type for the activities container
typedef struct containerItem* ActivitiesContainer;

ActivitiesContainer buildActivities();
void printActivities(ActivitiesContainer);

#endif // ACTIVITIES_CONTAINER_H          // End of inclusion block