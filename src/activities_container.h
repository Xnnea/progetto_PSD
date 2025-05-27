#ifndef ACTIVITIES_CONTAINER_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_H             // Macro definition to avoid multiple inclusions

#include "activity.h"
#include "activities_container_avl.h"

/* Declare an opaque type for the activities container.
 * Used in the program (main) to masks the underlying structure (tree). 
 */
typedef struct containerItem* ActivitiesContainer;



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
TreeNode getRootNode(ActivitiesContainer container);

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
 * Effects:
 * - Allocates memory for the container structure
 * 
 * Side Effects:
 * - None
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
 * Effects:
 * - No modifications to data structures
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
 * Effects:
 * - May allocate memory for the container
 * - Modifies the activity ID if it was 0
 * - Modifies the AVL tree structure
 * 
 * Side Effects:
 * - Modification of the passed activity (if ID was 0)
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
 * Effects:
 * - Modifies the container's AVL tree structure
 * - Updates the container's pointer 'avlTree' to point to the new root of the AVL tree structure
 * 
 * Side Effects:
 * - Effects from calls to 'deleteNode()'
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
 * Effects:
 * - Deallocates all container memory
 * 
 * Side Effects:
 * - Calls to deallocation functions
 */
void deleteActivityContainer(ActivitiesContainer container);

#endif // ACTIVITIES_CONTAINER_H          // End of inclusion block