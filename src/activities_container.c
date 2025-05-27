#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activity_helper.h"
#include "activities_container.h"




// Definition of the containerItem structure that points to the initial node of the tree (root).
// It also contains the next id to use when inserting a node.
struct containerItem {
	TreeNode avlTree;
	int nextId;
};




TreeNode getRootNode(ActivitiesContainer container) {
	if(container == NULL) return NULL;
	
	return container->avlTree;
}


int getNextId(ActivitiesContainer container) {
	if (container == NULL) return -1;
	
	return container->nextId;
}



Activity getActivityWithId(ActivitiesContainer container, int activityId) {
	TreeNode root = getRootNode(container);
	if(root == NULL) return NULL;

	TreeNode activityNode = search(root, activityId);
	if (activityNode != NULL) {
		return getActivityFromNode(activityNode);
	}
	
	return NULL;
}




// Function to insert a new Activity into AVL tree.
// The activity key (activity->id) is automatically generated if id is initially valorized with 0. 
ActivitiesContainer insertActivity(ActivitiesContainer container, Activity activity) {
	if (!activity || !container) return container; // No action
	
	int currentActivityId = getActivityId(activity);
	
	// if tree is empty
	if (!container->avlTree) {
		container->nextId = 1;
	}
	
	// Automatically set the correct ID if needed (id = 0)
	if(currentActivityId == 0 && currentActivityId < container->nextId) setActivityId(activity, container->nextId);
	
	container->avlTree = insertNode(container->avlTree, activity);
	container->nextId = getActivityId(activity) + 1;
	
	return container;
}






ActivitiesContainer removeActivity(ActivitiesContainer container, int activityId) {
	if (!container || !container->avlTree) return container; //No action
	
	container->avlTree = deleteNode(container->avlTree, activityId);
	return container;
}




// Creates and returns a new empty activity container (tree)
ActivitiesContainer newActivityContainer(void) {
	ActivitiesContainer tree = (struct containerItem*)malloc(sizeof(struct containerItem)); 
	if (tree != NULL) {
		tree->avlTree = NULL;
		tree->nextId = 1;
	}
	
	return tree;
}










// Function to delete the container
void deleteActivityContainer(ActivitiesContainer container) {
	if (container == NULL) return;
	
	if (container->avlTree == NULL) {
		free(container);
		return;
	}
	
	deleteSubtree(container->avlTree);
	free(container);
}



