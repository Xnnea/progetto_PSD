#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "activities_container.h"
//#include "activities_container_avl.h"

int main() {
	ActivitiesContainer activities = buildActivities();
	printActivities(activities);
}




