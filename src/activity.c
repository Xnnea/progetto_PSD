#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activity.h"

// Activity data structure definition
struct activity {
	int id;	// Unique identifier of the activity
	char* name;
	char* descr;
	char* course;
	time_t insertDate;
	time_t expiryDate;
	time_t completionDate;
	unsigned int totalTime; //minutes
	unsigned int usedTime;  //minutes
	short unsigned int priority;
};










/*Activity newEmptyActivity() {
	Activity activity = (Activity)malloc(sizeof(struct activity));
	if (activity == NULL) {
   		return NULL;
	}
	 
	activity->id = 0; 
	activity->name = NULL;
	activity->descr = NULL;
	activity->course = NULL;
	activity->insertDate = 0;
	activity->expiryDate = 0;
	activity->completionDate = 0;
	activity->totalTime = 0;
	activity->usedTime = 0;
	activity->priority = 0;
	
	return activity;
}*/


Activity newActivity( int id,
								char* name, 
								char* descr, 
								char* course, 
								time_t insertDate, 
								time_t expiryDate, 
								time_t completionDate, 
								unsigned int totalTime, 
								unsigned int usedTime, 
								short unsigned int priority ) {
	Activity activity = (Activity)malloc(sizeof(struct activity));
	if (activity == NULL) {
   		return NULL;
	}
	 
	activity->id = id; 
	
	activity->name = copyString(name);
	activity->descr = copyString(descr);
	activity->course = copyString(course);
	
	activity->insertDate = insertDate;
	activity->expiryDate = expiryDate;
	activity->completionDate = completionDate;
	activity->totalTime = totalTime;
	activity->usedTime = usedTime;
	activity->priority = priority;
	
	return activity;
}


void deleteActivity(Activity a) {
	if(!a) return;
	
	free(a->name);
	free(a->descr);
	free(a->course);
	
	free(a);
}


Activity copyActivity(Activity old) {
	if(!old) return NULL;
	
	Activity activity = (Activity)malloc(sizeof(struct activity));
	if (activity == NULL) {
   		return NULL;
	}
	 
	activity->id = old->id; 

	activity->name = copyString(old->name);
	activity->descr = copyString(old->descr);
	activity->course = copyString(old->course);
	
	activity->insertDate = old->insertDate;
	activity->expiryDate = old->expiryDate;
	activity->completionDate = old->completionDate;
	activity->totalTime = old->totalTime;
	activity->usedTime = old->usedTime;
	activity->priority = old->priority;
	
	return activity;
}




int getActivityId(Activity a) {
	if(!a) return 0;
	return a->id;
}

void setActivityId(Activity a, int newId) {
	if(a) a->id = newId;
}









char* getActivityName(Activity a) {
	if (a == NULL) return NULL;
	
	return a->name;
}

char* getActivityDescr(Activity a) {
	if (a == NULL) return NULL;
	
	return a->descr;
}

char* getActivityCourse(Activity a) {
	if (a == NULL) return NULL;
	
	return a->course;
}

time_t getActivityInsertDate(Activity a) {
	if (a == NULL) return 0;
	
	return a->insertDate;
}

time_t getActivityExpiryDate(Activity a) {
	if (a == NULL) return 0;
	
	return a->expiryDate;
}

time_t getActivityCompletionDate(Activity a) {
	if (a == NULL) return 0;
	
	return a->completionDate;
}

unsigned int getActivityTotalTime(Activity a) {
	if (a == NULL) return 0;
	
	return a->totalTime;
}

unsigned int getActivityUsedTime(Activity a) {
	if (a == NULL) return 0;
	
	return a->usedTime;
}

short unsigned int getActivityPriority(Activity a) {
	if (a == NULL) return 0;
	
	return a->priority;
}







void setActivityName(Activity a, char* name) {
	if (a == NULL) return;
	
	if (a->name != NULL) {
		free(a->name);
	}
	
	a->name = copyString(name);
}

void setActivityDescr(Activity a, char* descr) {
	if (a == NULL) return;
	
	if (a->descr != NULL) {
		free(a->descr);
	}
	
	a->descr = copyString(descr);
}

void setActivityCourse(Activity a, char* course) {
	if (a == NULL) return;
	
	if (a->course != NULL) {
		free(a->course);
	}
	
	a->course = copyString(course);
}

void setActivityInsertDate(Activity a, time_t insertDate) {
	if (a == NULL) return;
	
	a->insertDate = insertDate;
}

void setActivityExpiryDate(Activity a, time_t expiryDate) {
	if (a == NULL) return;
	
	a->expiryDate = expiryDate;
}

void setActivityCompletionDate(Activity a, time_t completionDate) {
	if (a == NULL) return;
	
	a->completionDate = completionDate;
}




void setActivityTotalTime(Activity a, unsigned int totalTime) {
	if (a == NULL) return;
	
	a->totalTime = totalTime;
}

void setActivityUsedTime(Activity a, unsigned int usedTime) {
	if (a == NULL) return;
	
	a->usedTime = usedTime;
}

void setActivityPriority(Activity a, short unsigned int priority) {
	if (a == NULL) return;
	
	a->priority = priority;
}









