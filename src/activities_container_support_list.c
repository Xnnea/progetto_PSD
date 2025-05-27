#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activity_helper.h"
#include "activities_container_support_list.h"


/*
 * Structure: nodelist (NodeList)
 * 
 * Definition:
 *   typedef struct nodelist {
 *       Activity activity;
 *       struct nodelist* next;
 *   } NodeList;
 * 
 * Description:
 *   Represents a single node of a simple linked list that contains
 *   an activity and a pointer to the next node. This structure implements
 *   the linked list pattern to store sequences of activities.
 * 
 * Fields:
 *   - Activity activity: Pointer to the activity contained in the node. Can be
 *                       NULL if the node does not contain a valid activity.
 *   - struct nodelist* next: Pointer to the next node in the linked list.
 *                           It is NULL if this is the last node in the list.
 * 
 * Usage:
 *   - Used to create chains of nodes that form a linked list
 *   - Each node maintains a reference to the activity and the next node
 *   - Allows sequential traversal of the list
 *   - Supports dynamic insertions and deletions
 * 
 * Notes:
 *   - If next is NULL, the node is the last in the list
 *   - The activity field can be NULL (empty node)
 *   - The structure is recursive through the next pointer
 */
typedef struct nodelist {
    Activity activity;
    struct nodelist* next;
} NodeList;



/*
 * Structure: listItem (ActivitiesContainerSupportList)
 * 
 * Definition:
 *   struct listItem {
 *       NodeList* head;
 *   };
 * 
 * Description:
 *   Represents the main structure that manages a linked list of
 *   activities. Acts as a container and access point for the list, maintaining
 *   a reference to the first node (head) of the chain.
 * 
 * Fields:
 *   - NodeList* head: Pointer to the first node of the linked list. It is NULL
 *                    if the list is empty. Represents the entry point
 *                    for all operations on the list.
 * 
 * Usage:
 *   - Main access point for all list operations
 *   - Maintains the integrity of the data structure
 *   - Allows quick identification if the list is empty (head == NULL)
 *   - Facilitates insertion operations at the head of the list
 * 
 * Notes:
 *   - If head is NULL, the list is empty
 *   - If head is not NULL, it points to a valid NodeList node
 *   - The structure must be dynamically allocated before use
 *   - Must be properly deallocated to avoid memory leaks
 * 
 * Implementation Notes:
 *   - ActivitiesContainerSupportList is a typedef that points to struct listItem*
 *   - The list supports head insertions for O(1) efficiency
 *   - Traversal operations always start from head
 *   - Deallocation requires freeing all nodes before the structure
 */
struct listItem {
    NodeList* head;
};




/*
 * Function: newSupportList
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
 * Effects:
 *   - Allocates dynamic memory for a listItem structure
 *   - Initializes the list's head field to NULL
 * 
 * Side Effects:
 *   - None
 */
ActivitiesContainerSupportList newSupportList(void) {
	ActivitiesContainerSupportList list = (struct listItem*)malloc(sizeof(struct listItem));
	if (list != NULL) {
		list->head = NULL;
	}
	return list;
}

/*
 * Function: deleteSupportList
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
 * Effects:
 *   - Frees memory of all list nodes
 *   - Frees memory of the main structure
 *   - Sets *list to NULL
 * 
 * Side Effects:
 *   - Modifies the value of the pointer passed by reference
 */
void deleteSupportList(ActivitiesContainerSupportList* list) {
	if (list == NULL || *list == NULL) return;
	
	NodeList* currentNode = (*list)->head;
	NodeList* nextNode = NULL;
	
	while (currentNode != NULL) {
		nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}
	
	free(*list);
	*list = NULL;
}


/*
 * Function: isSupportListEmpty
 * 
 * Syntactic Specification:
 *   int isSupportListEmpty(ActivitiesContainerSupportList list);
 * 
 * Semantic Specification:
 *   Checks if an activity list is empty by verifying if the list is 
 *   NULL or if its head is NULL.
 * 
 * Preconditions:
 *   - list can be NULL or point to a valid listItem structure
 * 
 * Postconditions:
 *   - Returns 1 if the list is empty or NULL
 *   - Returns 0 if the list contains at least one element
 * 
 * Effects:
 *   - No effect on the data structure (read-only function)
 * 
 * Side Effects:
 *   - No side effects
 */
int isSupportListEmpty(ActivitiesContainerSupportList list) {
	return (list == NULL || list->head == NULL) ? 1 : 0;
}


/*
 * Function: addActivityToSupportList
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
 * Effects:
 *   - Allocates memory for a new NodeList node
 *   - Copies the activity to the new node
 *   - Updates pointers to insert the node at the head
 * 
 * Side Effects:
 *   - Modifies the list structure
 */
void addActivityToSupportList(ActivitiesContainerSupportList list, Activity activity) {
	if (list == NULL) return;

	NodeList* newNode = (NodeList *)malloc(sizeof(NodeList));
	if (newNode == NULL) return; // return (list is unchanged)

	newNode->activity = activity;
	newNode->next = list->head;
	list->head = newNode;
}





/*
 * Function: splitSupportList
 * 
 * Syntactic Specification:
 *   NodeList* splitSupportList(NodeList* head);
 * 
 * Semantic Specification:
 *   Support function for merge sort that divides a list into two approximately 
 *   equal halves using the "tortoise and hare" technique 
 *   (slow - the tortoise - and fast - the hare - pointers).
 * 
 * Preconditions:
 *   - head can be NULL or point to a valid node
 * 
 * Postconditions:
 *   - If head is NULL: returns NULL
 *   - Otherwise: divides the list and returns pointer to the second half
 *   - The first half remains linked to head
 *   - The connection between the two halves is broken
 * 
 * Effects:
 *   - Modifies next pointers to divide the list
 *   - Does not allocate or deallocate memory
 * 
 * Side Effects:
 *   - Modifies the original list structure by breaking connections
 */
NodeList* splitSupportList(NodeList* head) {
	if (head == NULL) return NULL;

	NodeList* ptrSlow = head;
	NodeList* ptrFast = head; // prtFast moves at 2X

	// Move ptrSlow one step and ptrFast two steps (until ptrFast reaches the end)
	while (ptrFast != NULL && ptrFast->next != NULL) {
		ptrFast = ptrFast->next->next;
		if (ptrFast != NULL) {
			ptrSlow = ptrSlow->next;
		}
	}

	// Split the list into two halves
	NodeList* temp = ptrSlow->next;
	ptrSlow->next = NULL;
	return temp;
}

/*
 * Function: mergeSupportLists
 * 
 * Syntactic Specification:
 *   NodeList* mergeSupportLists(NodeList* listA, NodeList* listB, int sortBy);
 * 
 * Semantic Specification:
 *   Support function for merge sort that merges two sorted lists into 
 *   a single sorted list according to the criterion specified by sortBy.
 * 
 * Preconditions:
 *   - listA and listB can be NULL or point to already sorted lists
 *   - sortBy must be a valid integer value (0-11) that specifies the 
 *     sorting criterion
 * 
 * Postconditions:
 *   - Returns a sorted list containing all elements from listA and listB
 *   - If both lists are NULL: returns NULL
 *   - If one list is NULL: returns the other list
 *   - Sorting follows the criterion specified by sortBy
 * 
 * Effects:
 *   - Reorganizes pointers to merge the lists
 *   - Uses activity comparison functions
 *   - Does not allocate new memory for nodes
 * 
 * Side Effects:
 *   - Modifies the structure of the original lists by reconnecting nodes
 */
NodeList* mergeSupportLists(NodeList* listA, NodeList* listB, int sortBy) {
	if (listA == NULL && listB == NULL) return NULL;

	// If either list is empty, return the other list
	if (listA == NULL) return listB;
	if (listB == NULL) return listA;

	// Pick the smaller value between listA and listB nodes
	int cmp = 0;
	if (listA->activity == NULL && listB->activity != NULL) {
		cmp = 1;
	} else if (listA->activity != NULL && listB->activity == NULL) {
		cmp = -1;
	} else if (listA->activity != NULL && listB->activity != NULL) {		
		cmp = compareActivityBy(listA->activity, listB->activity, sortBy);
	}
	
	if (cmp < 0) { //listA->data < listB->data
		// Recursively merge the rest of the lists and link the result to the current node
		listA->next = mergeSupportLists(listA->next, listB, sortBy);
		return listA;
	} else {
		// Recursively merge the rest of the lists and link the result to the current node
		listB->next = mergeSupportLists(listA, listB->next, sortBy);
		return listB;
	}
}

/*
 * Function: mergeSortSupportList
 * 
 * Syntactic Specification:
 *   NodeList* mergeSortSupportList(NodeList* head, int sortBy);
 * 
 * Semantic Specification:
 *   Implements the recursive merge sort algorithm to sort a linked 
 *   list of activities according to the specified criterion (sortBy).
 * 
 * Preconditions:
 *   - head can be NULL or point to a valid node
 *   - sortBy must be a valid integer value (0-11)
 * 
 * Postconditions:
 *   - Returns pointer to the new head of the sorted list
 *   - If the list is empty or has one element: returns head unchanged
 *   - The resulting list is sorted according to the sortBy criterion
 * 
 * Effects:
 *   - Recursively divides the list into sublists
 *   - Sorts and merges the sublists
 *   - Reorganizes all list pointers
 * 
 * Side Effects:
 *   - Completely modifies the original list structure
 *   - Uses the stack for recursion
 */
NodeList* mergeSortSupportList(NodeList* head, int sortBy) {

	// if the list is empty or has only one node, it's already sorted (base case)
	if (head == NULL || head->next == NULL) return head;

	// Split the list into two halves
	NodeList* secondHalf = splitSupportList(head);

	// Recursively sort each half
	head = mergeSortSupportList(head, sortBy);
	secondHalf = mergeSortSupportList(secondHalf, sortBy);

	// Merge the two sorted halves
	return mergeSupportLists(head, secondHalf, sortBy);
}

/*
 * Function: sortSupportList
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
 * Effects:
 *   - Reorders all elements in the list
 *   - Updates the head pointer of the main structure
 * 
 * Side Effects:
 *   - Permanently modifies the order of elements in the list
 *   - Uses the stack for merge sort recursion
 */
void sortSupportList(ActivitiesContainerSupportList list, int sortBy) {
	if ( isSupportListEmpty(list) == 1 ) return;
	
	list->head = mergeSortSupportList(list->head, sortBy); 
}



/*
 * Function: printActivitiesInSupportList
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
 * Effects:
 *   - Traverses all nodes in the list
 *   - Calls appropriate print functions for each activity
 * 
 * Side Effects:
 *   - Output to stdout or specified file
 *   - No modification to the data structure
 */
void printActivitiesInSupportList(ActivitiesContainerSupportList list, int printType, FILE* file) {
	if ( isSupportListEmpty(list) == 1 ) return;
	
	NodeList* currentNode = list->head;
	Activity activity = NULL;
	int pType = (printType == 0 || printType == 1) ? printType : 0;

	while (currentNode != NULL) {
		activity = currentNode->activity;
		(pType == 0) ? printActivityForListToScreenOrFile(activity, file) : printActivityProgressForListToScreenOrFile(activity, file);
		currentNode = currentNode->next;
	}
}

