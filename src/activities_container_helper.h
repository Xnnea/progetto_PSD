#ifndef ACTIVITIES_CONTAINER_HELPER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_HELPER_H             // Macro definition to avoid multiple inclusions

#include "activities_container.h"
#include "activity_helper.h"

#define DEFAULT_ACTIVITIES_FILE "activities_list.txt"


/*
 * saveActivitiesToFile
 * 
 * Syntactic Specification:
 * int saveActivitiesToFile(const char* filename, ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Saves all activities from the container to a file.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'container == NULL' or 'filename != NULL', returns 1 (error)
 * - If unable to open the file, returns 1 (error)
 * - Otherwise, saves all activities and returns 0 (success)
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - File opening and writing
 * - Output to stdout (informational messages)
 */
int saveActivitiesToFile(const char* filename, ActivitiesContainer container);

/*
 * readActivitiesFromFile
 * 
 * Syntactic Specification:
 * ActivitiesContainer readActivitiesFromFile(const char* filename, int* count);
 * 
 * Semantic Specification:
 * Reads activities from a file and inserts them into a new container.
 * 
 * Preconditions:
 * - 'count != NULL'
 * 
 * Postconditions:
 * - Creates a new container
 * - If the file doesn't exist, returns an empty container and '*count = 0'
 * - Otherwise, reads all activities from the file and updates '*count' (number of activities read)
 * 
 * Effects:
 * - Allocates memory for the container and activities
 * - Modifies '*count' (number of activities read)
 * 
 * Side Effects:
 * - File opening and reading
 * - Output to stdout (informational messages)
 * - Calls to 'readActivityFromFile()'
 */
ActivitiesContainer readActivitiesFromFile(const char* filename, int* count);

/*
 * addNewActivityToContainer
 * 
 * Syntactic Specification:
 * ActivitiesContainer addNewActivityToContainer(ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Interacts with the user to create and add a new activity to the container.
 * 
 * Preconditions:
 * - 'container != NULL'
 * 
 * Postconditions:
 * - If 'container == NULL', returns 0
 * - Otherwise, asks user for data and adds the new activity
 * 
 * Effects:
 * - Modifies the container by adding a new activity
 * - Allocates memory for the new activity
 * 
 * Side Effects:
 * - User interaction (input/output)
 * - Calls to user input functions
 * - Calls to 'time()' for timestamp
 */
void addNewActivityToContainer(ActivitiesContainer container);



/*
 * printActivityWithId
 * 
 * Syntactic Specification:
 * void printActivityWithId(ActivitiesContainer container, int activityId);
 * 
 * Semantic Specification:
 * Prints the details of the activity with the specified ID.
 * 
 * Preconditions:
 * - 'container' can be 'NULL'
 * - 'activityId' must be a valid ID
 * 
 * Postconditions:
 * - If the activity is found, its details are printed
 * - Otherwise, no action
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout via 'printActivityDetailWithMenu()'
 */
void printActivityWithId(ActivitiesContainer container, int activityId);

/*
 * printActivities
 * 
 * Syntactic Specification:
 * void printActivities(ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Prints all activities (list format, one per line) from the container in ascending order of ID.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'container != NULL', prints all activities with headers
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout
 */
void printActivities(ActivitiesContainer container);

/*
 * printActivitiesProgress
 * 
 * Syntactic Specification:
 * void printActivitiesProgress(ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Prints the progress of all container activities (progress list format, one per line) with headers.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'container != NULL', prints progress of all activities
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout
 */
void printActivitiesProgress(ActivitiesContainer container);

/*
 * printActivitiesReport
 * 
 * Syntactic Specification:
 * void printActivitiesReport(ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Generates and prints a detailed report of activities categorized by status and period.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'container' is valid, prints a complete report with categorized activities
 * - Interacts with user to define the report period
 * 
 * Effects:
 * - Allocates and deallocates temporary support lists
 * 
 * Side Effects:
 * - User interaction (input/output)
 * - Output to stdout
 * - Calls to time management functions
 */
void printActivitiesReport(ActivitiesContainer container);




/*
 * printActivitiesToFile
 * 
 * Syntactic Specification:
 * void printActivitiesToFile(ActivitiesContainer container, FILE* file);
 * 
 * Semantic Specification:
 * Prints all container activities to file (list format, one per line).
 * 
 * Preconditions:
 * - 'file' must be opened for writing
 * 
 * Postconditions:
 * - If both parameters are valid, prints all activities to file
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Writing to file
 */
void printActivitiesToFile(ActivitiesContainer container, FILE* file);

/*
 * printActivitiesProgressToFile
 * 
 * Syntactic Specification:
 * void printActivitiesProgressToFile(ActivitiesContainer container, FILE* file);
 * 
 * Semantic Specification:
 * Prints the progress of all container activities to file (progress list format, one per line).
 * 
 * Preconditions:
 * - 'file' must be opened for writing
 * 
 * Postconditions:
 * - If both parameters are valid, prints progress with header
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Writing to file
 */
void printActivitiesProgressToFile(ActivitiesContainer container, FILE* file);

/*
 * printActivitiesReportToFile
 * 
 * Syntactic Specification:
 * void printActivitiesReportToFile(ActivitiesContainer container, time_t beginDate, FILE* file);
 * 
 * Semantic Specification:
 * Prints an activity report to file for a specified period.
 * 
 * Preconditions:
 * - 'file' must be opened for writing
 * - 'beginDate >= 0'
 * 
 * Postconditions:
 * - If all parameters are valid, prints the report to file
 * 
 * Effects:
 * - Allocates and deallocates temporary support lists
 * 
 * Side Effects:
 * - Writing to file
 */
void printActivitiesReportToFile(ActivitiesContainer container, time_t beginDate, FILE* file);


#endif // ACTIVITIES_CONTAINER_HELPER_H          // End of inclusion block