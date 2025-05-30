#ifndef ACTIVITIES_CONTAINER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"
#include "activities_container_avl.h"

/* Declare an opaque type for the activities container.
 * Used in the program (main) to masks the underlying structure (tree). 
 */
typedef struct containerItem* ActivitiesContainer;




/*
 * getNextId
 * 
 * Syntactic Specification:
 * int getNextId(ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Returns the next available ID for a new activity.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'container == NULL', returns -1
 * - Otherwise, returns 'container->nextId'
 * 
 * Side Effects:
 * - None
 */
int getNextId(ActivitiesContainer container);

/*
 * newActivityContainer
 * 
 * Syntactic Specification:
 * ActivitiesContainer newActivityContainer(void);
 * 
 * Semantic Specification:
 * Creates and initializes a new empty activity container.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - Returns a new container with 'NULL' tree and 'nextId = 1'
 * - If allocation fails, returns 'NULL'
 * 
 * Side Effects:
 * - Allocates memory for the container structure
 */
ActivitiesContainer newActivityContainer(void);

/*
 * getActivityWithId
 * 
 * Syntactic Specification:
 * Activity getActivityWithId(ActivitiesContainer container, int activityId);
 * 
 * Semantic Specification:
 * Returns the activity with the specified ID.
 * 
 * Preconditions:
 * - 'activityId' must be a valid ID
 * 
 * Postconditions:
 * - If the activity is found, returns it
 * - Otherwise, returns 'NULL'
 * 
 * Side Effects:
 * - None
 */
Activity getActivityWithId(ActivitiesContainer container, int activityId);

/*
 * insertActivity
 * 
 * Syntactic Specification:
 * void insertActivity(ActivitiesContainer container, Activity activity);
 * 
 * Semantic Specification:
 * Inserts an activity into the container (the AVL tree), automatically generating an activity ID if necessary (id = 0).
 * 
 * Preconditions:
 * - 'activity != NULL'
 * 
 * Postconditions:
 * - If 'container == NULL', creates a new container
 * - If the activity ID is 0, generates a new unique ID
 * - Inserts the activity into the container
 * - Updates the container's 'nextId'
 * 
 * Side Effects:
 * - May allocate memory for the container
 * - Modifies the activity ID if it was 0
 * - Modifies the AVL tree structure
 */
void insertActivity(ActivitiesContainer container, Activity activity);

/*
 * removeActivity
 * 
 * Syntactic Specification:
 * void removeActivity(ActivitiesContainer container, int activityId);
 * 
 * Semantic Specification:
 * Removes an activity from the container (the tree) given its ID.
 * 
 * Preconditions:
 * - 'container' can be 'NULL'
 * - 'activityId' must be a valid ID
 * 
 * Postconditions:
 * - If 'container == NULL' or 'container->avlTree == NULL', no action
 * - Otherwise, removes the activity with the specified ID
 * 
 * Side Effects:
 * - Modifies the container's AVL tree structure
 * - Updates the container's pointer 'avlTree' to point to the new root of the AVL tree structure
 * - Effects from calls to 'deleteNode()': deallocate memory.
 */
void removeActivity(ActivitiesContainer container, int activityId);

/*
 * deleteActivityContainer
 * 
 * Syntactic Specification:
 * void deleteActivityContainer(ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Completely deletes an activity container and all its content (tree and activities).
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'container == NULL', no action
 * - Otherwise, deallocates the entire container and its activities
 * 
 * Side Effects:
 * - Deallocates all container memory
 */
void deleteActivityContainer(ActivitiesContainer container);

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
 * Side Effects:
 * - File opening and writing
 * - Output to stdout (informational messages)
 */
int saveActivitiesToFile(const char* filename, ActivitiesContainer container);


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
 * - If 'container != NULL', prints all activities with headers (see 'printAllActivities')
 * 
 * Side Effects:
 * - Output to stdout
 */
void printActivities(ActivitiesContainer container);


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
 * Side Effects:
 * - Writing to file
 */
void printActivitiesToFile(ActivitiesContainer container, FILE* file);


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
 * Side Effects:
 * - Output to stdout
 */
void printActivitiesProgress(ActivitiesContainer container);


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
 * Side Effects:
 * - Writing to file
 */
void printActivitiesProgressToFile(ActivitiesContainer container, FILE* file);


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
 * Side Effects:
 * - Allocates and deallocates temporary support lists
 * - User interaction (input/output)
 * - Output to stdout
 * - Calls to time management functions
 */
void printActivitiesReport(ActivitiesContainer container);


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
 * Side Effects:
 * - Allocates and deallocates temporary support lists
 * - Writing to file
 */
void printActivitiesReportToFile(ActivitiesContainer container, time_t beginDate, FILE* file);



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
 * Side Effects:
 * - Allocates memory for the container and activities
 * - Modifies '*count' (number of activities read)
 * - File opening and reading
 * - Output to stdout (informational messages)
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
 * - If 'container == NULL', returns
 * - Otherwise, asks user for data and adds the new activity
 * 
 * Side Effects:
 * - Modifies the container by adding a new activity
 * - Allocates memory for the new activity
 * - User interaction (input/output)
 */
void addNewActivityToContainer(ActivitiesContainer container);



#endif // ACTIVITIES_CONTAINER_H          // End of inclusion block