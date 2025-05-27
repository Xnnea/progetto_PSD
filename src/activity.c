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






/*
 * newActivity
 * 
 * Syntactic Specification:
 * Activity newActivity(int id, char* name, char* descr, char* course, 
 *                     time_t insertDate, time_t expiryDate, time_t completionDate, 
 *                     unsigned int totalTime, unsigned int usedTime, 
 *                     short unsigned int priority);
 * 
 * Semantic Specification:
 * Creates a new activity with the specified parameters.
 * 
 * Preconditions:
 * - Sufficient memory available for allocation
 * - String parameters may be NULL
 * - copyString must be defined and working
 * 
 * Postconditions:
 * - Returns a pointer to an Activity initialized with the provided values
 * - Returns NULL if allocation fails
 * - Strings are copied, not just referenced
 * 
 * Effects:
 * Allocates dynamic memory for a new Activity structure and its strings.
 * 
 * Side Effects:
 * - None
 */
Activity newActivity( int id, char* name, char* descr, char* course, 
							time_t insertDate, time_t expiryDate, time_t completionDate, 
							unsigned int totalTime, unsigned int usedTime, 
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

/*
 * deleteActivity
 * 
 * Syntactic Specification:
 * void deleteActivity(Activity a);
 * 
 * Semantic Specification:
 * Frees the memory allocated for an activity.
 * 
 * Preconditions:
 * - 'a' must be a valid pointer or NULL
 * 
 * Postconditions:
 * - All dynamic memory associated with the activity is freed
 * 
 * Effects:
 * Deallocates dynamic memory.
 * 
 * Side Effects:
 * - None
 */
void deleteActivity(Activity a) {
	if(!a) return;
	
	free(a->name);
	free(a->descr);
	free(a->course);
	
	free(a);
}

/*
 * copyActivity
 * 
 * Syntactic Specification:
 * Activity copyActivity(Activity old);
 * 
 * Semantic Specification:
 * Creates a complete copy of an existing activity.
 * 
 * Preconditions:
 * - Sufficient memory available for allocation
 * 
 * Postconditions:
 * - Returns a pointer to a new Activity that is a copy of old
 * - Returns NULL if old is NULL or if allocation fails
 * 
 * Effects:
 * Allocates dynamic memory for a new Activity structure and its strings.
 * 
 * Side Effects:
 * None
 */
Activity copyActivity(Activity old) {
	if(!old) return NULL;
	
	return newActivity(old->id, old->name, old->descr, old->course, 
							old->insertDate, old->expiryDate, old->completionDate, 
							old->totalTime, old->usedTime, old->priority);
}









/*
 * Getter Functions (getActivityId, getActivityName, getActivityDescr, etc.)
 * 
 * Syntactic Specification:
 * int getActivityId(Activity a);
 * char* getActivityName(Activity a);
 * char* getActivityDescr(Activity a);
 * char* getActivityCourse(Activity a);
 * time_t getActivityInsertDate(Activity a);
 * time_t getActivityExpiryDate(Activity a);
 * time_t getActivityCompletionDate(Activity a);
 * unsigned int getActivityTotalTime(Activity a);
 * unsigned int getActivityUsedTime(Activity a);
 * short unsigned int getActivityPriority(Activity a);
 * char* getActivityPriorityFormatted(Activity a);
 * 
 * Semantic Specification:
 * Return the values of the corresponding activity fields.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Return the field's value if a is not NULL
 * - Return NULL if a is NULL and the return type is char*
 * - Return 0 if a is NULL and the return type is not char*
 * - getActivityPriorityFormatted returns a textual representation of the priority
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
 
int getActivityId(Activity a) {
	if(!a) return 0;
	return a->id;
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






 
/*
 * Setter Functions (setActivityId, setActivityName, setActivityDescr, etc.)
 * 
 * Syntactic Specification:
 * void setActivityId(Activity a, int newId);
 * void setActivityName(Activity a, char* name);
 * void setActivityDescr(Activity a, char* descr);
 * void setActivityCourse(Activity a, char* course);
 * void setActivityInsertDate(Activity a, time_t insertDate);
 * void setActivityExpiryDate(Activity a, time_t expiryDate);
 * void setActivityCompletionDate(Activity a, time_t completionDate);
 * void setActivityTotalTime(Activity a, unsigned int totalTime);
 * void setActivityUsedTime(Activity a, unsigned int usedTime);
 * void setActivityPriority(Activity a, short unsigned int priority);
 * 
 * Semantic Specification:
 * Set the values of the corresponding activity fields.
 * 
 * Preconditions:
 * - For string functions: copyString must be defined and functional
 * 
 * Postconditions:
 * - The corresponding field is updated if a is not NULL
 * - For strings: the old string is freed and the new one is copied
 * - No effect if a is NULL
 * 
 * Effects:
 * Modify the activity's fields and manage memory for strings.
 * 
 * Side Effects:
 * - String memory deallocation and allocation
 * - Modification of the Activity object's state
 */
 
void setActivityId(Activity a, int newId) {
	if(a) a->id = newId;
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









