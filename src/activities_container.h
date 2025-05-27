#ifndef ACTIVITIES_CONTAINER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"
#include "activities_container_avl.h"

// Declare an opaque type for the activities container
typedef struct containerItem* ActivitiesContainer;

TreeNode getRootNode(ActivitiesContainer container);
int getNextId(ActivitiesContainer container);

ActivitiesContainer newActivityContainer(void);

Activity getActivityWithId(ActivitiesContainer container, int activityId);

// Function to insert a new Activity into AVL tree.
// The activity key (activity->id) is automatically generated if id is initially valorized with 0. 
ActivitiesContainer insertActivity(ActivitiesContainer container, Activity activity);

ActivitiesContainer removeActivity(ActivitiesContainer container, int activityId);

void deleteActivityContainer(ActivitiesContainer container);

#endif // ACTIVITIES_CONTAINER_H          // End of inclusion block