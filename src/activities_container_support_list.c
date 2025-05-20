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

//Used mainly for print the activities
void doActionOnSupportListActivities(ActivitiesContainerSupportList list, void (*actionFunction)(Activity) ) {
	if ( isSupportListEmpty(list) == 1 ) return;
	
	NodeList* currentNode = list->head;
	
	while (currentNode != NULL) {
		(*actionFunction)(currentNode->activity);
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
NodeList* mergeSupportLists(NodeList* listA, NodeList* listB, int (*compareFunction)(Activity, Activity)) {
	if (listA == NULL && listA == NULL) return NULL;

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
		cmp = (*compareFunction)(listA->activity, listB->activity);
	}
	
	if (cmp < 0) { //listA->data < listB->data
		// Recursively merge the rest of the lists and link the result to the current node
		listA->next = mergeSupportLists(listA->next, listB, compareFunction);
		return listA;
	} else {
		// Recursively merge the rest of the lists and link the result to the current node
		listB->next = mergeSupportLists(listA, listB->next, compareFunction);
		return listB;
	}
}

// Function to perform merge sort on a list. Return the pointer to the new head of the list.
NodeList* mergeSortSupportList(NodeList* head, int (*compareFunction)(Activity, Activity) ) {

	// if the list is empty or has only one node, it's already sorted (base case)
	if (head == NULL || head->next == NULL) return head;

	// Split the list into two halves
	NodeList* secondHalf = splitSupportList(head);

	// Recursively sort each half
	head = mergeSortSupportList(head, compareFunction);
	secondHalf = mergeSortSupportList(secondHalf, compareFunction);

	// Merge the two sorted halves
	return mergeSupportLists(head, secondHalf, compareFunction);
}

// Function to sort a list. The original list will be modified.
void sortSupportList(ActivitiesContainerSupportList list, int (*compareFunction)(Activity, Activity) ) {
	if ( isSupportListEmpty(list) == 1 ) return;
	
	list->head = mergeSortSupportList(list->head, compareFunction); 
}