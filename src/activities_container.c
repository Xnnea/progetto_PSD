#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activity_helper.h"
#include "activities_container.h"
#include "activities_container_helper.h"


/*
* "struct containerItem" Documentation
* 
* Syntactic Specification:
* struct containerItem {
*     TreeNode avlTree;
*     int nextId;
* };
* 
* Semantic Specification:
* Defines the activities container structure that provides an abstraction layer between the application
* and the underlying AVL tree data structure. This container encapsulates the complexity of tree
* operations and ID management, offering a simplified interface for activity management.
* 
* Fields:
* - avlTree: Pointer to the root node of the AVL tree containing all activities
* - nextId: The next unique ID to assign to a new activity when inserted
* 
* Abstraction Benefits:
* - Data Structure Independence: The application code doesn't need to know about AVL tree
*   implementation details, rotations, or balancing operations
* - Simplified Interface: Client code uses high-level operations (insert, remove, search)
*   without managing tree pointers or node structures directly
* - Automatic ID Management: The container handles unique ID generation automatically,
*   preventing ID conflicts and ensuring data integrity
* - Implementation Flexibility: The underlying data structure could be changed (e.g., to
*   hash table, B-tree) without affecting client code
* - Error Handling: Container functions provide consistent error handling and validation
*   without exposing tree-specific error conditions
* - Memory Management: Centralized allocation and deallocation of tree resources through
*   container-level functions
* 
* Notes:
* - When the container is empty, avlTree is NULL and nextId is typically 1
* - The nextId is automatically incremented when activities are inserted
* - Activities are stored in the AVL tree ordered by their unique ID values
* - The container ensures efficient O(log n) operations while hiding complexity from users
* - This abstraction follows the principle of information hiding and modular design
*/
struct containerItem {
	TreeNode avlTree; // Pointer to the root node of the AVL tree
	int nextId; // Next available unique ID for new activities
};



/*
 * getRootNode
 * 
 * Syntactic Specification:
 * TreeNode getRootNode(ActivitiesContainer container);
 * 
 * Semantic Specification:
 * Returns the root node of the AVL tree contained within the given activities container.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'container == NULL', returns 'NULL'
 * - Otherwise, returns 'container->avlTree'
 * 
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - None
 */
TreeNode getRootNode(ActivitiesContainer container) {
	if(container == NULL) return NULL;
	
	return container->avlTree;
}

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
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - None
 */
int getNextId(ActivitiesContainer container) {
	if (container == NULL) return -1;
	
	return container->nextId;
}


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
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - None
 */
Activity getActivityWithId(ActivitiesContainer container, int activityId) {
	TreeNode root = getRootNode(container);
	if(root == NULL) return NULL;

	TreeNode activityNode = search(root, activityId);
	if (activityNode != NULL) {
		return getActivityFromNode(activityNode);
	}
	
	return NULL;
}



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
 * Effects:
 * - May allocate memory for the container
 * - Modifies the activity ID if it was 0
 * - Modifies the AVL tree structure
 * 
 * Side Effects:
 * - Modification of the passed activity (if ID was 0)
 */
void insertActivity(ActivitiesContainer container, Activity activity) {
	if (!activity || !container) return; // No action
	
	int currentActivityId = getActivityId(activity);
	
	// if tree is empty
	if (!container->avlTree) {
		container->nextId = 1;
	}
	
	// Automatically set the correct ID if needed (id = 0)
	if(currentActivityId == 0 && currentActivityId < container->nextId) setActivityId(activity, container->nextId);
	
	container->avlTree = insertNode(container->avlTree, activity);
	container->nextId = getActivityId(activity) + 1;
}





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
 * Effects:
 * - Modifies the container's AVL tree structure
 * - Updates the container's pointer 'avlTree' to point to the new root of the AVL tree structure
 * 
 * Side Effects:
 * - Effects from calls to 'deleteNode()'
 */
void removeActivity(ActivitiesContainer container, int activityId) {
	if (!container || !container->avlTree) return; //No action
	
	container->avlTree = deleteNode(container->avlTree, activityId);
}




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
 * Effects:
 * - Allocates memory for the container structure
 * 
 * Side Effects:
 * - None
 */
ActivitiesContainer newActivityContainer(void) {
	ActivitiesContainer tree = (struct containerItem*)malloc(sizeof(struct containerItem)); 
	if (tree != NULL) {
		tree->avlTree = NULL;
		tree->nextId = 1;
	}
	
	return tree;
}






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
 * Effects:
 * - Deallocates all container memory
 * 
 * Side Effects:
 * - Calls to deallocation functions
 */
void deleteActivityContainer(ActivitiesContainer container) {
	if (container == NULL) return;
	
	if (container->avlTree == NULL) {
		free(container);
		return;
	}
	
	deleteSubtree(container->avlTree);
	free(container);
}



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
int saveActivitiesToFile(const char* filename, ActivitiesContainer container) {
	if (container == NULL || filename == NULL) return 1;
	
	TreeNode root = getRootNode(container);
	return saveActivitiesFromTreeToFile(filename, root);
}


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
void printActivityWithId(ActivitiesContainer container, int activityId) {
	TreeNode root = getRootNode(container);
	if(root == NULL) return;

	TreeNode activityNode = search(root, activityId);
	if (activityNode != NULL) {
		printActivityDetailWithMenu( getActivityFromNode(activityNode) );
	}
}


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
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - Output to stdout
 */
void printActivities(ActivitiesContainer container) {
	if (container != NULL) {
		TreeNode root = getRootNode(container);
		printAllActivities(root);
	}
}


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
void printActivitiesToFile(ActivitiesContainer container, FILE* file) {
	if (container != NULL && file != NULL) {
		TreeNode root = getRootNode(container);
		printAllActivitiesToFile(root, file);
	}
}


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
void printActivitiesProgress(ActivitiesContainer container) {
	if (container != NULL) {
		TreeNode root = getRootNode(container);
		printTreeActivitiesProgress(root);
	}
}


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
void printActivitiesProgressToFile(ActivitiesContainer container, FILE* file) {
	if (container != NULL && file != NULL) {	
		TreeNode root = getRootNode(container);
		printTreeActivitiesProgressToFile(root, file);
	}
}


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
void printActivitiesReport(ActivitiesContainer container) {
	if (container == NULL) return;
	TreeNode root = getRootNode(container);
	
	printTreeActivitiesReport(root);
}


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
void printActivitiesReportToFile(ActivitiesContainer container, time_t beginDate, FILE* file) {
	if (container == NULL) return;
	TreeNode root = getRootNode(container);
	
	printTreeActivitiesReportToFile(root, beginDate, file);
}




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
ActivitiesContainer readActivitiesFromFile(const char* filename, int* count) {
	ActivitiesContainer newContainer = newActivityContainer();
	if(newContainer == NULL) return NULL;
	
	if (filename == NULL) {
		printf("Il nome di file fornito è NULL. Verrà creato un contenitore vuoto per le attività.\n", filename);
		*count = 0;
		return newContainer;
	} 
	
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Il file %s non esiste. Verrà creato un contenitore vuoto per le attività.\n", filename);
		*count = 0;
		return newContainer;
	}
	
	*count = 0;
	
	while (!feof(file)) {  
		Activity currentActivity = readActivityFromFile(file);
		if (currentActivity == NULL) {
			fclose(file);
			return newContainer;
		}
		
		insertActivity(newContainer, currentActivity);
		*count += 1;
	}
	  
	fclose(file);
	printf("Lette %d attività dal file %s.\n", *count, filename);
	return newContainer;
}



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
 * Effects:
 * - Modifies the container by adding a new activity
 * - Allocates memory for the new activity
 * 
 * Side Effects:
 * - User interaction (input/output)
 * - Calls to user input functions
 * - Calls to 'time()' for timestamp
 */
void addNewActivityToContainer(ActivitiesContainer container) {
	if (container == NULL) return;
	
	Activity activity = createNewActivityFromUserInput();
	
	if (activity == NULL) return;
	insertActivity(container, activity);
}

