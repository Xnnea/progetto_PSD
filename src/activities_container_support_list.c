#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

//Used for print the activities
void printActivitiesInSupportList(ActivitiesContainerSupportList list, int printType, FILE* file) {
	if ( isSupportListEmpty(list) == 1 ) return;
	
	NodeList* currentNode = list->head;
	
	while (currentNode != NULL) {
		if (file == NULL) {
			switch (printType) {
				case 0: printActivityForList(currentNode->activity);
						break;
						
				case 1: printActivityProgressForList(currentNode->activity);
						break;
						
				default: printActivityForList(currentNode->activity);
						break;	
			}
		} else {
			switch (printType) {
				case 0: printActivityForListToFile(currentNode->activity, file);
						break;
						
				case 1: printActivityProgressForListToFile(currentNode->activity, file);
						break;
						
				default: printActivityForListToFile(currentNode->activity, file);
						break;	
			}
		}

		currentNode = currentNode->next;
	}
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
		switch (sortBy) {
			case 0: cmp = compareAcivityById(listA->activity, listB->activity);
					break;
					
			case 1: cmp = compareAcivityByName(listA->activity, listB->activity);
					break;
					
			case 2: cmp = compareAcivityByDescr(listA->activity, listB->activity);
					break;
					
			case 3: cmp = compareAcivityByCourse(listA->activity, listB->activity);
					break;
					
			case 4: cmp = compareAcivityByInsertDate(listA->activity, listB->activity);
					break;
					
			case 5: cmp = compareAcivityByExpiryDate(listA->activity, listB->activity);
					break;
					
			case 6: cmp = compareAcivityByCompletionDate(listA->activity, listB->activity);
					break;
					
			case 7: cmp = compareAcivityByTotalTime(listA->activity, listB->activity);
					break;
					
			case 8: cmp = compareAcivityByUsedTime(listA->activity, listB->activity);
					break;
					
			case 9: cmp = compareAcivityByPriority(listA->activity, listB->activity);
					break;
					
			case 10: cmp = compareAcivityByPercentCompletion(listA->activity, listB->activity);
					break;
					
			case 11: cmp = compareAcivityByTimeToCompletion(listA->activity, listB->activity);
					break;
					
			default: cmp = compareAcivityById(listA->activity, listB->activity);
					break;
		}
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