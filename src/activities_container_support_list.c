#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activity_helper.h"
#include "activities_container_support_list.h"

typedef struct nodelist {
    Activity activity;
    struct nodelist* next;
} NodeList;


struct listItem {
    NodeList* head;
};

ActivitiesContainerSupportList newSupportList(void) {
	ActivitiesContainerSupportList list = (struct listItem*)malloc(sizeof(struct listItem));
	if (list != NULL) {
		list->head = NULL;
	}
	return list;
}

void deleteSupportList(ActivitiesContainerSupportList* list) {
	if (list == NULL || *list == NULL) return;
	
	NodeList* currentNode = (*list)->head;
	NodeList* nextNode = NULL;
	
	while (currentNode != NULL) {
		nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}
	
	free(*list); //test this after use. remember to set fo NULL externally.
	*list = NULL;
}


// 1 = list is empty
int isSupportListEmpty(ActivitiesContainerSupportList list) {
	return (list == NULL || list->head == NULL) ? 1 : 0;
}


// Add an Activity to the head of the list
void addActivityToSupportList(ActivitiesContainerSupportList list, Activity activity) {
	if (list == NULL) return;

	NodeList* newNode = (NodeList *)malloc(sizeof(NodeList));
	if (newNode == NULL) return; // return (list is unchanged)

	newNode->activity = activity;
	newNode->next = list->head;
	list->head = newNode;
}






// Function to split the list into two halves (support function for merge sort)
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

// Function to merge two sorted lists (support function for merge sort)
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

// Function to perform merge sort on a list. Return the pointer to the new head of the list.
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

// Function to sort a list. The original list will be modified.
void sortSupportList(ActivitiesContainerSupportList list, int sortBy) {
	if ( isSupportListEmpty(list) == 1 ) return;
	
	list->head = mergeSortSupportList(list->head, sortBy); 
}




//Used for print the activities
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

