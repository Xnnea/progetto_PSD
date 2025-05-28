#ifndef ACTIVITY_HELPER_H             // Start of inclusion block
#define ACTIVITY_HELPER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"


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
int isActivityYetToBegin(Activity a);

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
int isActivityCompleted(Activity a);

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
int wasActivityCompletedAfterDate(Activity a, time_t thresholdDate);

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
int wasActivityExpiredBeforeDate(Activity a, time_t thresholdDate);

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
int activityCompletionPercentage(Activity activity);

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
char * getActivityPriorityText(Activity activity) ;




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
int compareWithId(Activity a, int activityId);

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
int compareActivityById(Activity a, Activity b);



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
int compareActivityBy(Activity a, Activity b, int compareBy);




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
void printActivity(Activity activity);

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
void printActivityDetailWithMenu(Activity activity);

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
void printActivityForList(Activity activity);

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
void printActivityProgressForList(Activity activity);




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
void printActivityToFile(Activity activity, FILE* file);

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
void printActivityForListToFile(Activity activity, FILE* file);

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
void printActivityProgressForListToFile(Activity activity, FILE* file);




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
void printActivityForListToScreenOrFile(Activity activity, FILE* file);

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
void printActivityProgressForListToScreenOrFile(Activity activity, FILE* file);




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
Activity readActivityFromFile(FILE* file);

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
void saveActivityToFile(FILE* file, Activity activity);


#endif // ACTIVITY_HELPER_H          // End of inclusion block
