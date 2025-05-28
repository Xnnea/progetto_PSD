#ifndef ACTIVITIES_CONTAINER_HELPER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_HELPER_H             // Macro definition to avoid multiple inclusions

#include "activities_container.h"
#include "activity_helper.h"

#define DEFAULT_ACTIVITIES_FILE "activities_list.txt"


/*
 * saveActivitiesFromTreeToFile
 * 
 * Syntactic Specification:
 * int saveActivitiesFromTreeToFile(const char* filename, TreeNode root);
 * 
 * Semantic Specification:
 * Saves all activities from the tree to a file.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'root == NULL' or 'filename != NULL', returns 1 (error)
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
int saveActivitiesFromTreeToFile(const char* filename, TreeNode root);

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
 * printAllActivities
 * 
 * Syntactic Specification:
 * void printAllActivities(TreeNode root);
 * 
 * Semantic Specification:
 * Prints all activities (list format, one per line) from the tree in ascending order of ID.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'root != NULL', prints all activities with headers
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout
 */
void printAllActivities(TreeNode root);

/*
 * printTreeActivitiesProgress
 * 
 * Syntactic Specification:
 * void printTreeActivitiesProgress(TreeNode root);
 * 
 * Semantic Specification:
 * Prints the progress of all container activities (progress list format, one per line) with headers.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'root != NULL', prints progress of all activities in tree
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout
 */
void printTreeActivitiesProgress(TreeNode root);

/*
 * printTreeActivitiesReport
 * 
 * Syntactic Specification:
 * void printTreeActivitiesReport(TreeNode root);
 * 
 * Semantic Specification:
 * Generates and prints a detailed report of activities categorized by status and period.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'root' is valid, prints a complete report with categorized activities
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
void printTreeActivitiesReport(TreeNode root);




/*
 * printAllActivitiesToFile
 * 
 * Syntactic Specification:
 * void printAllActivitiesToFile(TreeNode root, FILE* file);
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
void printAllActivitiesToFile(TreeNode root, FILE* file);

/*
 * printTreeActivitiesProgressToFile
 * 
 * Syntactic Specification:
 * void printTreeActivitiesProgressToFile(TreeNode root, FILE* file);
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
void printTreeActivitiesProgressToFile(TreeNode root, FILE* file);

/*
 * printTreeActivitiesReportToFile
 * 
 * Syntactic Specification:
 * void printTreeActivitiesReportToFile(TreeNode root, time_t beginDate, FILE* file);
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
void printTreeActivitiesReportToFile(TreeNode root, time_t beginDate, FILE* file);


#endif // ACTIVITIES_CONTAINER_HELPER_H          // End of inclusion block