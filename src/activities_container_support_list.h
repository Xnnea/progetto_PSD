#ifndef ACTIVITIES_CONTAINER_SUPPORT_LIST_H             //  Start of inclusion block
#define ACTIVITIES_CONTAINER_SUPPORT_LIST_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

// Declare an opaque type for the activities support list.
typedef struct listItem* ActivitiesContainerSupportList;


/*
 * newSupportList
 * 
 * Syntactic Specification:
 *   ActivitiesContainerSupportList newSupportList(void);
 * 
 * Semantic Specification:
 *   Creates and initializes a new empty list to contain activities. 
 *   Dynamically allocates memory for the list structure and 
 *   initializes the head pointer to NULL.
 * 
 * Preconditions:
 *   - No specific preconditions
 * 
 * Postconditions:
 *   - If memory allocation succeeds: returns a valid pointer 
 *     to an empty list with head = NULL
 *   - If allocation fails: returns NULL
 * 
 * Side Effects:
 *   - Allocates dynamic memory for a listItem structure
 *   - Initializes the list's head field to NULL
 */
ActivitiesContainerSupportList newSupportList(void);

/*
 * addActivityToSupportList
 * 
 * Syntactic Specification:
 *   void addActivityToSupportList(ActivitiesContainerSupportList list, Activity activity);
 * 
 * Semantic Specification:
 *   Adds a new activity to the beginning of the list (head insertion). 
 *   Creates a new node, copies the activity (the activity pointer) to it and 
 *   links it as the new head of the list.
 * 
 * Preconditions:
 *   - list must be a valid pointer to a listItem structure (not NULL)
 *   - activity must be a valid Activity structure
 * 
 * Postconditions:
 *   - If new node allocation succeeds: the activity is added 
 *     at the head of the list
 *   - If allocation fails: the list remains unchanged
 *   - The new node becomes the new head of the list
 * 
 * Side Effects:
 *   - Modifies the list structure
 *   - Allocates memory for a new NodeList node
 *   - Copies the activity to the new node
 *   - Updates pointers to insert the node at the head
 */
void addActivityToSupportList(ActivitiesContainerSupportList list, Activity activity);

/*
 * deleteSupportList
 * 
 * Syntactic Specification:
 *   void deleteSupportList(ActivitiesContainerSupportList* list);
 * 
 * Semantic Specification:
 *   Completely deallocates an activity list, freeing the memory of 
 *   all nodes and the main structure. Sets the list pointer to NULL 
 *   to avoid dangling references. The parameter is a pointer 
 *   passed by reference.
 * 
 * Preconditions:
 *   - list can be NULL or point to a valid/NULL pointer
 * 
 * Postconditions:
 *   - All allocated memory for the list and its nodes is freed
 *   - *list is set to NULL
 *   - If list or *list were NULL, the function has no effect
 * 
 * Side Effects:
 *   - Frees memory of all list nodes
 *   - Frees memory of the main structure
 *   - Modifies the value of the pointer passed by reference
 */
void deleteSupportList(ActivitiesContainerSupportList* list);

/*
 * sortSupportList
 * 
 * Syntactic Specification:
 *   void sortSupportList(ActivitiesContainerSupportList list, int sortBy);
 * 
 * Semantic Specification:
 *   Sorts an activity list according to the specified criterion using 
 *   the merge sort algorithm. Modifies the original list.
 * 
 * Preconditions:
 *   - list must be a valid pointer to a listItem structure (not NULL)
 *   - sortBy must be a valid integer value (0-11) that specifies the 
 *     sorting criterion
 * 
 * Postconditions:
 *   - If the list is empty: no effect
 *   - If the list is not empty: it is sorted according to the sortBy criterion
 *   - The list's head field points to the new first sorted element
 * 
 * Side Effects:
 *   - Permanently modifies the order of elements in the list
 *   - Reorders all elements in the list
 *   - Updates the head pointer of the main structure
 */
void sortSupportList(ActivitiesContainerSupportList list, int sortBy);

/*
 * printActivitiesInSupportList
 * 
 * Syntactic Specification:
 *   void printActivitiesInSupportList(ActivitiesContainerSupportList list, int printType, FILE* file);
 * 
 * Semantic Specification:
 *   Prints all activities present in the list according to the specified 
 *   print type. Can print to stdout or to a specified file.
 * 
 * Preconditions:
 *   - list can be NULL or point to a valid listItem structure
 *   - printType: 0 for normal print, 1 for progress print, others force 
 *     normal print (considered default)
 *   - file can be NULL (for stdout) or a valid FILE pointer
 * 
 * Postconditions:
 *   - If the list is empty: no printing is performed
 *   - If the list is not empty: all activities are printed in list order
 *   - Print destination depends on file value: to file if file 
 *     is not NULL, to stdout otherwise
 * 
 * Side Effects:
 *   - Traverses all nodes in the list
 *   - Output to stdout or specified file
 *   - No modification to the data structure
 */
void printActivitiesInSupportList(ActivitiesContainerSupportList list, int printType, FILE* file);

#endif // ACTIVITIES_CONTAINER_SUPPORT_LIST_H          //  End of inclusion block