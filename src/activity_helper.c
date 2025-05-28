#include "activity_helper.h"


/*
 * isActivityYetToBegin
 * 
 * Syntactic Specification:
 * int isActivityYetToBegin(Activity a);
 * 
 * Semantic Specification:
 * Checks whether an activity has yet to start (used time = 0).
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 1 if used time == 0
 * - Returns 0 otherwise or if a is NULL (activity is completed or ongoing)
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int isActivityYetToBegin(Activity a) {
	if (a == NULL) return 0;
	
	unsigned int usedTime = getActivityUsedTime(a);
	
	return (usedTime == 0) ? 1 : 0;
}

/*
 * isActivityCompleted
 * 
 * Syntactic Specification:
 * int isActivityCompleted(Activity a);
 * 
 * Semantic Specification:
 * Checks whether an activity is completed (has a completion date).
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 1 if completion date != 0
 * - Returns 0 otherwise or if a is NULL
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int isActivityCompleted(Activity a) {
	if (a == NULL) return 0;
	
	time_t completionDate = getActivityCompletionDate(a);
	
	return (completionDate != 0) ? 1 : 0;
}

/*
 * wasActivityCompletedAfterDate
 * 
 * Syntactic Specification:
 * int wasActivityCompletedAfterDate(Activity a, time_t thresholdDate);
 * 
 * Semantic Specification:
 * Checks whether an activity was completed after a given threshold date.
 * 
 * Preconditions:
 * - thresholdDate must be a valid time_t value
 * 
 * Postconditions:
 * - Returns 1 if completion date > thresholdDate
 * - Returns 0 otherwise or if a is NULL
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int wasActivityCompletedAfterDate(Activity a, time_t thresholdDate) {
	if (a == NULL) return 0;
	
	time_t completionDate = getActivityCompletionDate(a);
	
	return (completionDate > thresholdDate) ? 1 : 0;
}

/*
 * wasActivityExpiredBeforeDate
 * 
 * Syntactic Specification:
 * int wasActivityExpiredBeforeDate(Activity a, time_t thresholdDate);
 * 
 * Semantic Specification:
 * Checks whether an activity expired before a given threshold date.
 * 
 * Preconditions:
 * - thresholdDate must be a valid time_t value
 * 
 * Postconditions:
 * - Returns 1 if expiry date > 0 && expiry date < thresholdDate
 * - Returns 0 otherwise or if a is NULL
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int wasActivityExpiredBeforeDate(Activity a, time_t thresholdDate) {
	if (a == NULL) return 0;
	
	time_t expiryDate = getActivityExpiryDate(a);
	
	//expiryDate = 0 mean no expiry date
	return (expiryDate > 0 && expiryDate < thresholdDate) ? 1 : 0;
}

/*
 * compareWithId
 * 
 * Syntactic Specification:
 * int compareWithId(Activity a, int activityId);
 * 
 * Semantic Specification:
 * Compares the ID of an activity with a specified ID.
 * 
 * Preconditions:
 * - activityId must be a valid integer
 * 
 * Postconditions:
 * - Returns 0 if a_id == activityId
 * - Returns -1 if a_id < activityId
 * - Returns 1 if a_id > activityId
 * - Returns -2 if a is NULL
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareWithId(Activity a, int activityId) {
	if (!a) return -2;
	
	int a_id = getActivityId(a);
	
	if (a_id == activityId) return 0;
	
	return (a_id < activityId) ? -1 : 1;
}

/*
 * activityCompletionPercentage
 * 
 * Syntactic Specification:
 * int activityCompletionPercentage(Activity activity);
 * 
 * Semantic Specification:
 * Calculates the (int) completion percentage of an activity based on the used time relative to the total time.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - Returns an integer representing the percentage (0-100+)
 * - Returns 0 if activity is NULL or if activity total time is 0
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int activityCompletionPercentage(Activity activity) {
	if (activity == NULL) return 0;
	
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	
	if (usedTime == 0 || totalTime == 0 ) return 0;
	
	int completionPercentage = (usedTime * 100) / totalTime;
	return completionPercentage;
}

/*
 * compareNullActivity
 * 
 * Syntactic Specification:
 * int compareNullActivity(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two Activity pointers to handle NULL cases.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if both are NULL
 * - Returns 1 if only a is not NULL
 * - Returns -1 if only b is not NULL
 * - Returns 0 if both are not NULL
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareNullActivity(const Activity a, const Activity b) {
	if (!a && !b) return 0;
	if (a && !b) return 1;
	if (b && !a) return -1;
	
	return 0;
}

/*
 * compareNullString
 * 
 * Syntactic Specification:
 * int compareNullString(const char* a, const char* b);
 * 
 * Semantic Specification:
 * Compares two string pointers to handle NULL cases.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if both are NULL
 * - Returns 1 if only a is not NULL
 * - Returns -1 if only b is not NULL
 * - Returns 0 if both are not NULL
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareNullString(const char* a, const char*  b) {
	if (!a && !b) return 0;
	if (a && !b) return 1;
	if (b && !a) return -1;
	
	return 0;
}


/*
 * compareActivityById
 * 
 * Syntactic Specification:
 * int compareActivityById(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by ID.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns the result of the ID comparison if both are not NULL
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityById(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	int b_id = getActivityId(b);
	
	return compareWithId(a, b_id);
}

/*
 * compareActivityByName
 * 
 * Syntactic Specification:
 * int compareActivityByName(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by name using strcmp.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns the result of strcmp if both names are not NULL
 * - Handles NULL cases using compareNullString
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByName(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	char* a_name = getActivityName(a);
	char* b_name = getActivityName(b);
	
	if (a_name == NULL || b_name == NULL) {
		return compareNullString(a_name, b_name);
	}
	
	return strcmp(a_name, b_name);
}

/*
 * compareActivityByDescr
 * 
 * Syntactic Specification:
 * int compareActivityByDescr(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by description using strcmp.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns the result of strcmp if both descriptions are not NULL
 * - Handles NULL cases using compareNullString
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByDescr(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	char* a_descr = getActivityDescr(a);
	char* b_descr = getActivityDescr(b);
	
	if (a_descr == NULL || b_descr == NULL) {
		return compareNullString(a_descr, b_descr);
	}
	
	return strcmp(a_descr, b_descr);
}

/*
 * compareActivityByCourse
 * 
 * Syntactic Specification:
 * int compareActivityByCourse(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by course using strcmp.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns the result of strcmp if both courses are not NULL
 * - Handles NULL cases using compareNullString
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByCourse(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	char* a_course = getActivityCourse(a);
	char* b_course = getActivityCourse(b);
	
	if (a_course == NULL || b_course == NULL) {
		return compareNullString(a_course, b_course);
	}
	
	return strcmp(a_course, b_course);
}

/*
 * compareActivityByInsertDate
 * 
 * Syntactic Specification:
 * int compareActivityByInsertDate(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by insertion date.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if the dates are equal
 * - Returns -1 if a->insertDate < b->insertDate
 * - Returns 1 if a->insertDate > b->insertDate
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByInsertDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	time_t a_insertDate = getActivityInsertDate(a);
	time_t b_insertDate = getActivityInsertDate(a);
	
	if (a_insertDate == b_insertDate) return 0;
	
	return (a_insertDate < b_insertDate) ? -1 : 1;
}

/*
 * compareActivityByExpiryDate
 * 
 * Syntactic Specification:
 * int compareActivityByExpiryDate(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by expiry date.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if the dates are equal
 * - Returns -1 if a->expiryDate < b->expiryDate
 * - Returns 1 if a->expiryDate > b->expiryDate
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByExpiryDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	time_t a_expiryDate = getActivityExpiryDate(a);
	time_t b_expiryDate = getActivityExpiryDate(a);
	
	if (a_expiryDate == b_expiryDate) return 0;
	
	return (a_expiryDate < b_expiryDate) ? -1 : 1;
}

/*
 * compareActivityByCompletionDate
 * 
 * Syntactic Specification:
 * int compareActivityByCompletionDate(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by completion date.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if the dates are equal
 * - Returns -1 if a->completionDate < b->completionDate
 * - Returns 1 if a->completionDate > b->completionDate
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByCompletionDate(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	time_t a_completionDate = getActivityCompletionDate(a);
	time_t b_completionDate = getActivityCompletionDate(a);
	
	if (a_completionDate == b_completionDate) return 0;
	
	return (a_completionDate < b_completionDate) ? -1 : 1;
}

/*
 * compareActivityByTotalTime
 * 
 * Syntactic Specification:
 * int compareActivityByTotalTime(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by total time.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if times are equal
 * - Returns -1 if a->totalTime < b->totalTime
 * - Returns 1 if a->totalTime > b->totalTime
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByTotalTime(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	unsigned int a_totalTime = getActivityTotalTime(a);
	unsigned int b_totalTime = getActivityTotalTime(b);
	
	if (a_totalTime == b_totalTime) return 0;
	
	return (a_totalTime < b_totalTime) ? -1 : 1;
}

/*
 * compareActivityByUsedTime
 * 
 * Syntactic Specification:
 * int compareActivityByUsedTime(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by used time.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if times are equal
 * - Returns -1 if a->usedTime < b->usedTime
 * - Returns 1 if a->usedTime > b->usedTime
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByUsedTime(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	unsigned int a_usedTime = getActivityUsedTime(a);
	unsigned int b_usedTime = getActivityUsedTime(b);
	
	if (a_usedTime == b_usedTime) return 0;
	
	return (a_usedTime < b_usedTime) ? -1 : 1;
}

/*
 * compareActivityByPriority
 * 
 * Syntactic Specification:
 * int compareActivityByPriority(const Activity a, const Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by priority.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if priorities are equal
 * - Returns -1 if a->priority < b->priority
 * - Returns 1 if a->priority > b->priority
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByPriority(const Activity a, const Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	short unsigned int a_priority = getActivityPriority(a);
	short unsigned int b_priority = getActivityPriority(b);
	
	if (a_priority == b_priority) return 0;
	
	return (a_priority < b_priority) ? -1 : 1;
}

/*
 * compareActivityByPercentCompletion
 * 
 * Syntactic Specification:
 * int compareActivityByPercentCompletion(Activity a, Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by completion percentage.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if percentages are equal
 * - Returns -1 if a's percentage < b's percentage
 * - Returns 1 if a's percentage > b's percentage
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByPercentCompletion(Activity a, Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	int a_percent = activityCompletionPercentage(a);
	int b_percent = activityCompletionPercentage(b);
	
	if (a_percent == b_percent) return 0;
	
	return (a_percent < b_percent) ? -1 : 1;
}

/*
 * compareActivityByTimeToCompletion
 * 
 * Syntactic Specification:
 * int compareActivityByTimeToCompletion(Activity a, Activity b);
 * 
 * Semantic Specification:
 * Compares two activities by remaining time to completion.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns 0 if remaining times are equal
 * - Returns -1 if a's remaining time < b's remaining time
 * - Returns 1 if a's remaining time > b's remaining time
 * - Handles NULL cases using compareNullActivity
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityByTimeToCompletion(Activity a, Activity b) {
	if (!a || !b) return compareNullActivity(a, b);
	
	unsigned int a_timeToCompletion = 0;
	unsigned int b_timeToCompletion = 0;
	
	unsigned int a_totalTime = getActivityTotalTime(a);
	unsigned int a_usedTime = getActivityUsedTime(a);
	
	if (a_totalTime >= a_usedTime) {
		a_timeToCompletion = a_totalTime - a_usedTime;
	}
	
	unsigned int b_totalTime = getActivityTotalTime(b);
	unsigned int b_usedTime = getActivityUsedTime(b);
	
	if (b_totalTime >= b_usedTime) {
		b_timeToCompletion = b_totalTime - b_usedTime;
	}
	
	if (a_timeToCompletion == b_timeToCompletion) return 0;
	
	return (a_timeToCompletion < b_timeToCompletion) ? -1 : 1;
}

/*
 * compareActivityBy
 * 
 * Syntactic Specification:
 * int compareActivityBy(Activity a, Activity b, int compareBy);
 * 
 * Semantic Specification:
 * Compares two activities using a specified comparison criterion. The comparison
 * method is determined by the compareBy parameter, which selects from various
 * activity attributes (ID, name, description, course, dates, times, priority, etc.).
 *
 * SORTING CRITERIA (sortBy)
 * 
 * Value  | Criterion
 * -------|----------
 *   0    | Activity ID
 *   1    | Activity Name
 *   2    | Description
 *   3    | Course
 *   4    | Insert Date
 *   5    | Expiry Date
 *   6    | Completion Date
 *   7    | Total Time
 *   8    | Used Time
 *   9    | Priority
 *  10    | Completion Percentage
 *  11    | Time to Completion
 *
 * 
 * Preconditions:
 * - compareBy should be a valid integer (0-11 for defined comparisons)
 * 
 * Postconditions:
 * - Returns 0 if the activities are equal according to the specified criterion
 * - Returns -1 if activity a is less than activity b according to the specified criterion
 * - Returns 1 if activity a is greater than activity b according to the specified criterion
 * - Uses ID comparison as default for invalid compareBy values
 * - Handles NULL cases appropriately based on the selected comparison method
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
int compareActivityBy(Activity a, Activity b, int compareBy) {
	int cmp = 0;
	switch (compareBy) {
		case 0: cmp = compareActivityById(a, b);
				break;
				
		case 1: cmp = compareActivityByName(a, b);
				break;
				
		case 2: cmp = compareActivityByDescr(a, b);
				break;
				
		case 3: cmp = compareActivityByCourse(a, b);
				break;
				
		case 4: cmp = compareActivityByInsertDate(a, b);
				break;
				
		case 5: cmp = compareActivityByExpiryDate(a, b);
				break;
				
		case 6: cmp = compareActivityByCompletionDate(a, b);
				break;
				
		case 7: cmp = compareActivityByTotalTime(a, b);
				break;
				
		case 8: cmp = compareActivityByUsedTime(a, b);
				break;
				
		case 9: cmp = compareActivityByPriority(a, b);
				break;
				
		case 10: cmp = compareActivityByPercentCompletion(a, b);
				break;
				
		case 11: cmp = compareActivityByTimeToCompletion(a, b);
				break;
				
		default: cmp = compareActivityById(a, b);
				break;
	}
	
	return cmp;
}


/*
 * priorityToText
 * 
 * Syntactic Specification:
 * char* priorityToText(int priority);
 * 
 * Semantic Specification:
 * Returns a string representing the priority.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Returns "HIGH" if priority == 1
 * - Returns "MEDIUM" if priority == 2  
 * - Returns "LOW" if priority == 3
 * - Returns "?" for other values
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
char * priorityToText(int priority) {
	switch(priority) {
		case 1: return "ALTA";
		case 2: return "MEDIA";
		case 3: return "BASSA";
		default: break;
	}
	
	return "?";
}

/*
 * getActivityPriorityText
 * 
 * Syntactic Specification:
 * char* getActivityPriorityText(Activity a);
 * 
 * Semantic Specification:
 * Returns a string representing the priority fileds of the activity.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Return NULL if a is NULL
 * - Returns a textual representation of the priority using 'priorityToText' function
 * 
 * Effects:
 * No effect on the program state.
 * 
 * Side Effects:
 * None.
 */
char*  getActivityPriorityText(Activity a) {
	if (a == NULL) return NULL;
	
	return priorityToText( getActivityPriority(a) );
}



/*
 * displayActivityDetailMenu
 * 
 * Syntactic Specification:
 * void displayActivityDetailMenu();
 * 
 * Semantic Specification:
 * Displays the activity detail menu. UI function.
 * 
 * Preconditions:
 * - stdout must be available
 * 
 * Postconditions:
 * - The menu is printed to stdout
 * 
 * Effects:
 * Prints text to the console.
 * 
 * Side Effects:
 * Output to stdout.
 */
void displayActivityDetailMenu() {
	printf("===================================\n");
	printf("====[ Menu dettaglio attività ]====\n");
	printf("===================================\n");
	printf("1. Aggiorna nome\n");
	printf("2. Aggiorna descrizione\n");
	printf("3. Aggiorna corso\n");
	printf("4. Cambia data di scadenza\n");
	printf("5. Cambia la durata totale\n");
	printf("6. Aggiorna il tempo impiegato sull'attività\n");
	printf("7. Cambia la priorità\n");
	printf("8. Imposta come COMPLETATA\n");
	printf("0. Torna al menu precedente\n");
	printf("Scelta: ");
}

/*
 * handleActivityDetailMenu
 * 
 * Syntactic Specification:
 * Activity handleActivityDetailMenu(Activity activity);
 * 
 * Semantic Specification:
 * Handles user interaction with the activity detail menu.
 * 
 * Preconditions:
 * - activity must be a valid Activity pointer
 * 
 * Postconditions:
 * - Returns activity if the user continues editing
 * - Returns NULL if the user exits the menu
 * - The activity may be modified based on user choices (name, description, etc.)
 * 
 * Effects:
 * Potentially modifies the activity based on user input.
 * 
 * Side Effects:
 * - Console input/output
 * - Modification of the Activity object's state
 * - String memory allocation/deallocation
 */
Activity handleActivityDetailMenu(Activity activity) {
	displayActivityDetailMenu();
	int choice = getChoice(8);
	
	Activity returnActivity = activity;
	
	char* tmpString = NULL;
	printf("\n");
	
	switch (choice) {
		case 0: { //Menu: '0. Torna al menu precedente'
			printf("Torno al menu precedente...\n");
			returnActivity = NULL;
			break;
		}

		case 1: { //Menu: '1. Aggiorna nome'
			printf("[Aggiorna nome]\n");
			tmpString = getActivityName(activity);
			printf("Nome (valore attuale): %s\n", tmpString ? tmpString : "NULL" );
			tmpString = getInfoFromUser("Inserisci in nuovo valore (lascia vuoto per non cambiarlo): ");
			if (tmpString != NULL) {
				setActivityName(activity, tmpString);
				free(tmpString);
			}
			break;
		}		
		
		case 2: { //Menu: '2. Aggiorna descrizione'
			printf("[Aggiorna descrizione]\n");
			tmpString = getActivityDescr(activity);
			printf("Descrizione (valore attuale): %s\n", tmpString ? tmpString : "NULL" );
			tmpString = getInfoFromUser("Inserisci in nuovo valore (lascia vuoto per non cambiarlo): ");
			if (tmpString != NULL) {
				setActivityDescr(activity, tmpString);
				free(tmpString);
			}
			break;
		}
		
		case 3: { //Menu: '3. Aggiorna corso'
			printf("[Aggiorna corso]\n");
			tmpString = getActivityCourse(activity);
			printf("Corso (valore attuale): %s\n", tmpString ? tmpString : "NULL" );
			tmpString = getInfoFromUser("Inserisci in nuovo valore (lascia vuoto per non cambiarlo): ");
			if (tmpString != NULL) {
				setActivityCourse(activity, tmpString);
				free(tmpString);
			}
			break;
		}
		
		case 4: { //Menu: '4. Cambia data di scadenza'
			printf("[Cambia data di scadenza]\n");
			time_t expDate = getActivityExpiryDate(activity);
			if ( expDate > 0) {
				char timeBuffer[100];
				struct tm* tmInfo;
				tmInfo = localtime(&expDate);
				strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
				printf("Data di scadenza (valore attuale): %s\n", timeBuffer);
			} else {
				printf("Data di scadenza (valore attuale): Non impostata\n");
			}
			
			int userConfirmation = getConfirmMenuChoice("Vuoi davvero modificare la data di scadenza? ");
			if (userConfirmation == 1) {
				time_t dateFromUser = getDateFromUser();
				setActivityExpiryDate(activity, dateFromUser);
			}
			break;
		}
		
		case 5: { //Menu: '5. Cambia la durata totale'
			printf("[Cambia la durata totale]\n");
			unsigned int totalTime = getActivityTotalTime(activity);
			printf("Durata totale (valore attuale in min): %u\n", totalTime );
			printf("Inserisci il nuovo valore (espresso in MINUTI, compreso 1 e un anno): ");
			totalTime = getChoiceWithLimits(1, 525600);
			setActivityTotalTime(activity, totalTime);
			break;
		}
		
		case 6: { //Menu: '6. Aggiorna il tempo impiegato sull'attività'
			printf("[Aggiorna il tempo impiegato sull'attività]\n");
			unsigned int totalTime = getActivityTotalTime(activity);
			unsigned int usedTime = getActivityUsedTime(activity);
			printf("Tempo impiegato (valore attuale in min): %u\n", usedTime );
			printf("Inserisci il nuovo valore (espresso in MINUTI, compreso 0 e %u): ", totalTime);
			usedTime = getChoiceWithLimits(0, totalTime);
			setActivityUsedTime(activity, usedTime);
			break;
		}
		
		case 7: { //7. Cambia la priorità
			printf("[Cambia la priorità]\n");
			printf("Priorità (valore attuale): %s\n", getActivityPriorityText(activity) );
			printf("\nInserisci la nuova priorità.\n");
			printf("1. ALTA\n");
			printf("2. MEDIA\n");
			printf("3. BASSA\n");
			printf("Scelta: ");
			short unsigned int priority = (short unsigned int) getChoiceWithLimits(1, 3);
			setActivityPriority(activity, priority);
			break;
		}
		
		case 8: { //Menu: '8. Imposta come COMPLETATA'
			printf("[Imposta come COMPLETATA]\n");
			int userConfirmation = getConfirmMenuChoice("Vuoi davvero segnare questa attività come completata? ");
			if (userConfirmation == 1) {
				setActivityCompletionDate(activity, time(NULL) );
			}
			break;
		}
		
		default: {
			printf("Scelta non gestita...\n");
			returnActivity = NULL;
			break;
		}
	}
	
	tmpString = NULL;
	return returnActivity;
}

/*
 * printActivity
 * 
 * Syntactic Specification:
 * void printActivity(Activity activity);
 * 
 * Semantic Specification:
 * Prints all the details of an activity in a readable format.
 * 
 * Preconditions:
 * - stdout must be available
 * 
 * Postconditions:
 * - Activity details are printed to stdout if activity is not NULL
 * - No output if activity is NULL
 * 
 * Effects:
 * Prints text to the console.
 * 
 * Side Effects:
 * Output to stdout.
 */
void printActivity(Activity activity) {
	if (activity == NULL) return;
	
	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t insertDate = getActivityInsertDate(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	time_t completionDate = getActivityCompletionDate(activity);
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	short unsigned int priority = getActivityPriority(activity);
	
	printf("\n===========================================\n");
	printf("==== Dettaglio attività con id %d \n", id);
	printf("===========================================\n\n");
    
	printf("Id: %d \n", id);
	printf("Nome: %s\n", name ? name : "NULL");
	printf("Descrizione: %s\n", descr ? descr : "NULL");
	printf("Corso: %s\n", course ? course : "NULL");

	char timeBuffer[100];
	struct tm* tmInfo;
	
	if (insertDate != 0) {
		tmInfo = localtime(&insertDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data inserimento: %s\n", timeBuffer);
	} else {
		printf("Data inserimento: Non impostata\n");
	}

	if (expiryDate != 0) {
		tmInfo = localtime(&expiryDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data scadenza: %s\n", timeBuffer);
	} else {
		printf("Data scadenza: Non impostata\n");
	}

 	if (completionDate != 0) {
		tmInfo = localtime(&completionDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		printf("Data completamento: %s\n", timeBuffer);
	} else {
		printf("Data completamento: ancora da completare\n");
	}
	
	printf("Tempo speso/usato (min): %u\n", usedTime);
	unsigned int hours = 0;
	unsigned int minutes = 0;
	minToHoursAnMinutes(usedTime, &hours, &minutes);
	printf("Tempo speso/usato (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	printf("Durata totale attività (min): %u\n", totalTime);
	minToHoursAnMinutes(totalTime, &hours, &minutes);
	printf("Durata totale attività (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	if (totalTime >= usedTime) {
		unsigned int diff = totalTime - usedTime;
		printf("Tempo stimato per il completamento (min): %u\n", diff);
		minToHoursAnMinutes(diff, &hours, &minutes);
		printf("Tempo stimato per il completamento (ore e min): %u ore e %u minuti\n", hours, minutes);
	}
	
	int completionPercentage = activityCompletionPercentage(activity);
	printf("Percentuale di completamento: %d%%\n", completionPercentage);
	
	printf("Priorità: %s\n", getActivityPriorityText(activity) );

	printf("========= Fine dettaglio attività =========\n\n");
}

/*
 * printActivityDetailWithMenu
 * 
 * Syntactic Specification:
 * void printActivityDetailWithMenu(Activity activity);
 * 
 * Semantic Specification:
 * Prints the details of an activity and manages the interactive menu.
 * 
 * Preconditions:
 * - activity must be a valid pointer to an Activity
 * 
 * Postconditions:
 * - The activity is displayed and the user can interact through the menu
 * 
 * Effects:
 * Loop for displaying and editing the activity.
 * 
 * Side Effects:
 * - Console input/output
 * - Potential modification of the Activity object state
 */
void printActivityDetailWithMenu(Activity activity) {
	Activity current = activity;
	while(current != NULL) {
		printActivity(current); 
		current = handleActivityDetailMenu(current);
	}
}



/*
 * printActivityToFile
 * 
 * Syntactic Specification:
 * void printActivityToFile(Activity activity, FILE* file);
 * 
 * Semantic Specification:
 * Prints all details of an activity to a file in a readable format. Its main purpose is to allow testing of modifications made to an activity.
 * 
 * Preconditions:
 * - file must be a valid pointer to a FILE opened in write mode
 * 
 * Postconditions:
 * - The activity details are written to the file if both parameters are not NULL
 * 
 * Effects:
 * Writes data to the file.
 * 
 * Side Effects:
 * File output.
 */
void printActivityToFile(Activity activity, FILE* file) {
	if (activity == NULL || file == NULL) return;

	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t insertDate = getActivityInsertDate(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	time_t completionDate = getActivityCompletionDate(activity);
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	short unsigned int priority = getActivityPriority(activity);

	fprintf(file, "Id: %d \n", id);
	fprintf(file, "Nome: %s\n", name ? name : "NULL");
	fprintf(file, "Descrizione: %s\n", descr ? descr : "NULL");
	fprintf(file, "Corso: %s\n", course ? course : "NULL");

	char timeBuffer[100];
	struct tm* tmInfo;
	
	if (insertDate != 0) {
		tmInfo = localtime(&insertDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data inserimento: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data inserimento: Non impostata\n");
	}

	if (expiryDate != 0) {
		tmInfo = localtime(&expiryDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data scadenza: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data scadenza: Non impostata\n");
	}

 	if (completionDate != 0) {
		tmInfo = localtime(&completionDate);
		strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
		fprintf(file, "Data completamento: %s\n", timeBuffer);
	} else {
		fprintf(file, "Data completamento: ancora da completare\n");
	}
	
	fprintf(file, "Tempo speso/usato (min): %u\n", usedTime);
	unsigned int hours = 0;
	unsigned int minutes = 0;
	minToHoursAnMinutes(usedTime, &hours, &minutes);
	fprintf(file, "Tempo speso/usato (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	fprintf(file, "Durata totale attività (min): %u\n", totalTime);
	minToHoursAnMinutes(totalTime, &hours, &minutes);
	fprintf(file, "Durata totale attività (ore e min): %u ore e %u minuti\n", hours, minutes);
	
	if (totalTime >= usedTime) {
		unsigned int diff = totalTime - usedTime;
		fprintf(file, "Tempo stimato per il completamento (min): %u\n", diff);
		minToHoursAnMinutes(diff, &hours, &minutes);
		fprintf(file, "Tempo stimato per il completamento (ore e min): %u ore e %u minuti\n", hours, minutes);
	}
	
	int completionPercentage = activityCompletionPercentage(activity);
	fprintf(file, "Percentuale di completamento: %d%%\n", completionPercentage);
	
	fprintf(file, "Priorità: %s\n", priorityToText(priority) );
}







/*
 * printActivityForListToScreenOrFile
 * 
 * Syntactic Specification:
 * void printActivityForListToScreenOrFile(Activity activity, FILE* file);
 * 
 * Semantic Specification:
 * Prints an activity in list format (single line) to screen or file.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Prints to stdout if file is NULL
 * - Prints to file if file is not NULL
 * - No output if activity is NULL
 * 
 * Effects:
 * Prints text to the console or writes to a file.
 * 
 * Side Effects:
 * Output to stdout or file write.
 */
void printActivityForListToScreenOrFile(Activity activity, FILE* file) {
	if (activity == NULL) return;

	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	time_t completionDate = getActivityCompletionDate(activity);
	short unsigned int priority = getActivityPriority(activity);
 
	// Format dates in a human-readable way
	char expiryDateBuffer[100];
	char completionDateBuffer[100];
	int isCompleted = 0;
	char priorityBuffer[10];
	struct tm* tm_info;

	if (expiryDate != 0) {
		tm_info = localtime(&expiryDate);
		strftime(expiryDateBuffer, sizeof(expiryDateBuffer), "%d/%m/%Y %H:%M", tm_info);
	} else {
		strcpy(expiryDateBuffer, "Non impostata");
	}
    
	if (completionDate != 0) {
		isCompleted = 1;
		tm_info = localtime(&completionDate);
		strftime(completionDateBuffer, sizeof(completionDateBuffer), "%d/%m/%Y %H:%M", tm_info);
	}
	
	strcpy(priorityBuffer, priorityToText(priority));
	
	if (file == NULL) {
		if (isCompleted == 0) {
			printf("[%d] %.20s | %.20s | %.20s | %s | SCADENZA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, expiryDateBuffer);
		} else {
			printf("[%d] %.20s | %.20s | %.20s | %s | COMPLETATA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, completionDateBuffer);
		}
	} else {
		if (isCompleted == 0) {
			fprintf(file, "[%d] %.20s | %.20s | %.20s | %s | SCADENZA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, expiryDateBuffer);
		} else {
			fprintf(file, "[%d] %.20s | %.20s | %.20s | %s | COMPLETATA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, completionDateBuffer);
		}	
	}
}

/*
 * printActivityForList
 * 
 * Syntactic Specification:
 * void printActivityForList(Activity activity);
 * 
 * Semantic Specification:
 * Prints an activity in list format to the screen.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - The activity is printed to stdout in list format
 * 
 * Effects:
 * Prints text to the console.
 * 
 * Side Effects:
 * Output to stdout.
 */
void printActivityForList(Activity activity) {
	printActivityForListToScreenOrFile(activity, NULL);
}

/*
 * printActivityForListToFile
 * 
 * Syntactic Specification:
 * void printActivityForListToFile(Activity activity, FILE* file);
 * 
 * Semantic Specification:
 * Prints an activity in list format to a file.
 * 
 * Preconditions:
 * - file must be a valid pointer to a FILE opened in write mode
 * 
 * Postconditions:
 * - The activity is written to the file in list format if file is not NULL
 * 
 * Effects:
 * Writes data to the file.
 * 
 * Side Effects:
 * File write.
 */
void printActivityForListToFile(Activity activity, FILE* file) {
	if (file == NULL) return;
	printActivityForListToScreenOrFile(activity, file);
}



/*
 * printActivityProgressForListToScreenOrFile
 * 
 * Syntactic Specification:
 * void printActivityProgressForListToScreenOrFile(Activity activity, FILE* file);
 * 
 * Semantic Specification:
 * Prints a 'not completed' activity with progress information (as a single line) to screen or file.
 * Differs from printActivityForListToScreenOrFile in the amount of detail included in the printed line.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - Prints to stdout if file is NULL
 * - Prints to file if file is not NULL
 * - No output if activity is NULL or completed
 * 
 * Effects:
 * Prints text to the console or writes to a file.
 * 
 * Side Effects:
 * Output to stdout or file write.
 */
void printActivityProgressForListToScreenOrFile(Activity activity, FILE* file) {
	if (activity == NULL || isActivityCompleted(activity) == 1) return;
	
	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t insertDate = getActivityInsertDate(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	short unsigned int priority = getActivityPriority(activity);

	// Format dates in a human-readable way
	char expiryDateBuffer[100];
	char priorityBuffer[10];
	struct tm* tmInfo;

	if (expiryDate != 0) {
		tmInfo = localtime(&expiryDate);
		strftime(expiryDateBuffer, sizeof(expiryDateBuffer), "%d/%m/%Y %H:%M", tmInfo);
	} else {
		strcpy(expiryDateBuffer, "Non impostata");
	}
   
	strcpy(priorityBuffer, priorityToText(priority));
	int completionPercentage = activityCompletionPercentage(activity);
	
	if (file == NULL) {
		// [id] title | descr | course | priority | PROGRESS | usedTime | TIME REMAINING | totalTime | expiryDate
		printf("[%d] %.20s | %.10s | %.10s | %s | %d%% | %d min | %d min | %d min | SCADENZA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, completionPercentage, usedTime, totalTime - usedTime,  totalTime, expiryDateBuffer);
	} else {
		// [id] title | descr | course | priority | PROGRESS | usedTime | TIME REMAINING | totalTime | expiryDate
		fprintf(file, "[%d] %.20s | %.10s | %.10s | %s | %d%% | %d min | %d min | %d min | SCADENZA: %s\n", id, name ? name : "NULL", descr ? descr : "NULL", course ? course : "NULL", priorityBuffer, completionPercentage, usedTime, totalTime - usedTime,  totalTime, expiryDateBuffer);	
	}
}

/*
 * printActivityProgressForList
 * 
 * Syntactic Specification:
 * void printActivityProgressForList(Activity activity);
 * 
 * Semantic Specification:
 * Prints a 'not completed' activity with progress information to the screen.
 * 
 * Preconditions:
 * None.
 * 
 * Postconditions:
 * - The activity is printed to stdout with progress information
 * 
 * Effects:
 * Prints text to the console.
 * 
 * Side Effects:
 * Output to stdout.
 */
void printActivityProgressForList(Activity activity) {
	printActivityProgressForListToScreenOrFile(activity, NULL);
}

/*
 * printActivityProgressForListToFile
 * 
 * Syntactic Specification:
 * void printActivityProgressForListToFile(Activity activity, FILE* file);
 * 
 * Semantic Specification:
 * Prints a 'not completed' activity with progress information to a file.
 * 
 * Preconditions:
 * - file must be a valid pointer to a FILE opened in write mode
 * 
 * Postconditions:
 * - The activity is written to the file with progress information if file is not NULL
 * 
 * Effects:
 * Writes data to the file.
 * 
 * Side Effects:
 * File write.
 */
void printActivityProgressForListToFile(Activity activity, FILE* file) {
	if (file == NULL) return;
	printActivityProgressForListToScreenOrFile(activity, file);
}





/*
 * readActivityFromFile
 * 
 * Syntactic Specification:
 * Activity readActivityFromFile(FILE* file);
 * 
 * Semantic Specification:
 * Reads an activity from a file (format: 10 lines per activity). It reads the format written by saveActivityToFile.
 * 
 * Preconditions:
 * - file must be a valid pointer to a FILE opened in read mode
 * - The file must contain at least 10 lines in the correct format
 * 
 * Postconditions:
 * - Returns a pointer to the Activity read from the file
 * - Returns NULL if it fails to read 10 lines or if allocation fails
 * 
 * Effects:
 * - Reads from the file
 * - Allocates memory for the new activity
 * 
 * Side Effects:
 * - File read
 * - Heap memory allocation
 * - Advances the file pointer
 */
Activity readActivityFromFile(FILE* file) {
	int id = 0;
	char* name = NULL; 
	char* descr = NULL; 
	char* course = NULL; 
	time_t insertDate = 0; 
	time_t expiryDate = 0; 
	time_t completionDate = 0; 
	unsigned int totalTime = 0; 
	unsigned int usedTime = 0; 
	short unsigned int priority = 2;  
	
	//try to read 10 lines (an activity) from file
	char* lines[10];
	for(int i=0; i<10; i++) {
		lines[i] = readLine(file);
	}
	
	int someNull = 0;
	for(int i=0; i<10; i++) {
		if(lines[i] == NULL) {
			someNull = 1;
		}
	}
	
	//Less than 10 lines have been read
	if(someNull == 1) {
		for(int i=0; i<10; i++) {
			free(lines[i]);
		}
		
		return NULL;
	}
	
	//Ok, exactly 10 lines have been read

	//line for: id
	if (strlen(lines[0]) > 0) {
		sscanf(lines[0], "%d", &id);
	}
   free(lines[0]);

   //line for: name
	if (strlen(lines[1]) == 0) {
		free(lines[1]);
	} else {
		name = lines[1];
	}

	//line for: descr
	if (strlen(lines[2]) == 0) {
		free(lines[2]);
	} else {
		descr = lines[2];
	}
	
	//line for: course
	if (strlen(lines[3]) == 0) {
		free(lines[3]);
	} else {
		course = lines[3];
	}

	//line for: insertDate
	if (strlen(lines[4]) > 0) {
		sscanf(lines[4], "%ld", &insertDate);
	}
	free(lines[4]);

	//line for: expiryDate
	if (strlen(lines[5]) > 0) {
		sscanf(lines[5], "%ld", &expiryDate);
	}
	free(lines[5]);

	//line for: completionDate
	if (strlen(lines[6]) > 0) {
		sscanf(lines[6], "%ld", &completionDate);
	}
	free(lines[6]);

	//line for: totalTime
	if (strlen(lines[7]) > 0) {
		sscanf(lines[7], "%u", &totalTime);
	}
	free(lines[7]);

	//line for: usedTime
	if (strlen(lines[8]) > 0) {
		sscanf(lines[8], "%u", &usedTime);
	}
	free(lines[8]);

	//line for: priority
	if (strlen(lines[9]) > 0) {
		sscanf(lines[9], "%hu", &priority);
	}
	free(lines[9]);
	
	return newActivity(id,name, descr, course, insertDate, expiryDate, completionDate, totalTime, usedTime, priority);
}


/*
 * saveActivityToFile
 * 
 * Syntactic Specification:
 * void saveActivityToFile(FILE* file, Activity activity);
 * 
 * Semantic Specification:
 * Saves an activity to a file using a 10-line format. Writes in the same format that readActivityFromFile reads.
 * 
 * Preconditions:
 * - file must be a valid pointer to a FILE opened in write mode
 * 
 * Postconditions:
 * - The activity is written to the file in 10 lines if activity is not NULL
 * - No output if activity is NULL
 * 
 * Effects:
 * Writes data to the file.
 * 
 * Side Effects:
 * File write.
 */
void saveActivityToFile(FILE* file, Activity activity) {
	if (activity == NULL) return;
	
	int id =  getActivityId(activity);
	char* name = getActivityName(activity);
	char* descr = getActivityDescr(activity);
	char* course = getActivityCourse(activity);
	time_t insertDate = getActivityInsertDate(activity);
	time_t expiryDate = getActivityExpiryDate(activity);
	time_t completionDate = getActivityCompletionDate(activity);
	unsigned int totalTime = getActivityTotalTime(activity);
	unsigned int usedTime = getActivityUsedTime(activity);
	short unsigned int priority = getActivityPriority(activity);
	
	fprintf(file, "%d\n", id);
	fprintf(file, "%s\n", name ? name : "");
	fprintf(file, "%s\n", descr ? descr : "");
	fprintf(file, "%s\n", course ? course : "");
	fprintf(file, "%ld\n", insertDate);
	fprintf(file, "%ld\n", expiryDate);
	fprintf(file, "%ld\n", completionDate);
	fprintf(file, "%u\n", totalTime);
	fprintf(file, "%u\n", usedTime);
	fprintf(file, "%hu\n", priority);
}



