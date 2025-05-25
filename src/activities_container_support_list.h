#ifndef ACTIVITIES_CONTAINER_SUPPORT_LIST_H             //  Start of inclusion block
#define ACTIVITIES_CONTAINER_SUPPORT_LIST_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

typedef struct listItem* ActivitiesContainerSupportList;

ActivitiesContainerSupportList newSupportList(void);
void addActivityToSupportList(ActivitiesContainerSupportList list, Activity activity);
void deleteSupportList(ActivitiesContainerSupportList* list);

void printActivitiesInSupportList(ActivitiesContainerSupportList list, int printType, FILE* file);
void sortSupportList(ActivitiesContainerSupportList list, int sortBy);

#endif // ACTIVITIES_CONTAINER_SUPPORT_LIST_H          //  End of inclusion block