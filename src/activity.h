#ifndef ACTIVITY_H             // Start of inclusion block
#define ACTIVITY_H             // Macro definition to avoid multiple inclusions

#include "utils.h"

// Declare an opaque type for the activity type
typedef struct activity* Activity;



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
							short unsigned int priority );

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
void deleteActivity(Activity a);

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
Activity copyActivity(Activity old); //used on node rotation (tree, on node delete)



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
 
int getActivityId(Activity a);
char* getActivityName(Activity a);
char* getActivityDescr(Activity a);
char* getActivityCourse(Activity a);
time_t getActivityInsertDate(Activity a);
time_t getActivityExpiryDate(Activity a);
time_t getActivityCompletionDate(Activity a);
unsigned int getActivityTotalTime(Activity a);
unsigned int getActivityUsedTime(Activity a);
short unsigned int getActivityPriority(Activity a);



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
 
void setActivityId(Activity a, int newId);
void setActivityName(Activity a, char* name);
void setActivityDescr(Activity a, char* descr);
void setActivityCourse(Activity a, char* course);
void setActivityInsertDate(Activity a, time_t insertDate);
void setActivityExpiryDate(Activity a, time_t expiryDate);
void setActivityCompletionDate(Activity a, time_t completionDate);
void setActivityTotalTime(Activity a, unsigned int totalTime);
void setActivityUsedTime(Activity a, unsigned int usedTime);
void setActivityPriority(Activity a, short unsigned int priority);


#endif // ACTIVITY_H          // End of inclusion block
