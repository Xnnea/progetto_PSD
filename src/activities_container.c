#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activities_container.h"

// Defining the node structure for the AVL tree
typedef struct node {
	Activity * activity;   // Data structure pointer: activity stored in the node
	struct node* left;
	struct node* right; 
	int height;
} Node;


// Definition of the containerItem structure that points to the initial node of the tree (root).
// It also contains the next id to use when inserting a node.
struct containerItem {
	Node* avlTree;
	int nextId;
};




// Return the node with minimum key (id) value found in that tree.
Node * minValueNode(Node* node) {
	if (!node) return NULL;
	Node* current = node;

	// Loop down to find the leftmost leaf
	while (current->left != NULL)
		current = current->left;

	return current;
}


// Return the node with maximum key (id) value found in that tree.
Node * maxValueNode(Node* node) {
	if (!node) return NULL;
	Node* current = node;

	// Loop down to find the rightmost leaf
	while (current->right != NULL)
		current = current->right;

    return current;
}






// Function to get height of a node
int getHeight(Node* n) {
	if (n == NULL) return 0;
	return n->height;
}

// Function to create a new node
Node* createNode(Activity * activity) {
	if (!activity) return NULL;
	Node* node = (Node*) malloc(sizeof(Node));
	node->activity = activity;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // New node is initially added at leaf
	return node;
}


// Function to get balance factor of a node
int getBalanceFactor(Node* n) {
	if (n == NULL) return 0;
	return getHeight(n->left) - getHeight(n->right);
}

// Right rotation function
Node* rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

	return x;
}

// Left rotation function
Node* leftRotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	return y;
}




// Function to insert a new node (and an activity) into a subtree
Node* insertNode(Node* node, Activity * activity) {
	
	// 0 - If node is null
	if (!node) {
		return createNode(activity);
	}
	
	int compareResult = compare(activity, node->activity);
	
	// 1 - Perform standard BST insertion
	if (compareResult < 0)
		node->left = insertNode(node->left, activity);
	else if (compareResult > 0)
		node->right = insertNode(node->right, activity);
	else // Equal keys are not allowed in BST
		return node; // Return the unchanged tree

	// 2 - Update height of this ancestor node
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));

	// 3 - Get the balance factor of this ancestor node to
	//     check whether this node became unbalanced
	int balance = getBalanceFactor(node);

	// 4 - If the node becomes unbalanced, then there are 4 cases
	
	if (node->left && node->left->activity) {
		int compareResultLeft = compare(activity, node->left->activity);
		
		// Case "LL" - Left Left
		if (balance > 1 && compareResultLeft < 0)
			return rightRotate(node);
			
		// Case "LR" - Left Right
		if (balance > 1 && compareResultLeft > 0) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
	}
	
		
	if (node->right && node->right->activity) {
		int compareResultRight = compare(activity, node->right->activity);
		
		// Case "RR" - Right Right
		if (balance < -1 && compareResultRight > 0)
			return leftRotate(node);
	
		// Case "RL" - Right Left
		if (balance < -1 && compareResultRight < 0) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	}

	// Return the node (unchanged)
	return node;
}

// Function to insert a new Activity into AVL tree.
// The activity key (activity->id) is automatically generated if id is initially valorized with 0. 
ActivitiesContainer insertActivity(ActivitiesContainer container, Activity * activity) {
	if (!activity) return container; // No action
	
	int currentActivityId = getActivityId(activity);
	
	// 0 - Tree is null or empty
	if (!container) {
		struct containerItem* tree = (struct containerItem*) malloc(sizeof(struct containerItem));
		tree->nextId = 1;
		if(currentActivityId == 0 && currentActivityId < tree->nextId) setActivityId(activity, tree->nextId);
		tree->avlTree = createNode(activity);
		tree->nextId = getActivityId(activity) + 1;
		return tree;
	} else if (!container->avlTree) {
		container->nextId = 1;
		if(currentActivityId == 0 && currentActivityId < container->nextId) setActivityId(activity, container->nextId);
		container->avlTree = createNode(activity);
		container->nextId = getActivityId(activity) + 1;
		return container;
	}
	
	if(currentActivityId == 0 && currentActivityId < container->nextId) setActivityId(activity, container->nextId);
	
	container->avlTree = insertNode(container->avlTree, activity);
	container->nextId = getActivityId(activity) + 1;
	
	return container;
}







// Function (recursive) to delete a node with given activityId (key) from a subtree. 
// It returns root of the modified subtree.
Node* deleteNode(Node* root, int activityId) {
	if (root == NULL) return root;
	
	// === 1 -  perform standard BST delete ===
	
	int compareResult = compareWithId(root->activity, activityId);
	
	// If the id (key) to be deleted is smaller than the root's key,
	// then it lies in left subtree.
	if ( compareResult > 0 ) {
		root->left = deleteNode(root->left, activityId);
	} else if( compareResult < 0 ) { 
		// If the id (key) to be deleted is greater than the root's key,
		// then it lies in right subtree
		root->right = deleteNode(root->right, activityId);
	} else {
		// id (key) is same as root's id (key), then this is
		// the node to be deleted
		
		// Node with only one child or no child
		if( (root->left == NULL) || (root->right == NULL) ) {
			Node *temp = root->left ? root->left : root->right;
			Activity * activityToDelete = root->activity;
				
			// No child case
			if (temp == NULL) {
				temp = root;
				root = NULL;
			} else { // One child case
				*root = *temp; // Copy the contents of the non-empty child
			}          
            
			deleteActivity(activityToDelete);
			free(temp);
		} else { // Node with two children
			// Get the inorder successor (smallest in the right subtree)
			Node* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node
			Activity * tempActivity = root->activity;
			root->activity = copyActivity(temp->activity);

			// Delete the inorder successor
			deleteActivity(tempActivity);
			root->right = deleteNode(root->right, getActivityId(temp->activity) );
		}
	}

	// If the tree had only one node then return
	if (root == NULL) return root;

	// === 2 - UPDATE HEIGHT OF THE CURRENT NODE ===
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));

	// === 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced) ===
	int balance = getBalanceFactor(root);

	// If this node becomes unbalanced, then there are 4 cases

	// Case "LL" - Left Left
	if (balance > 1 && getBalanceFactor(root->left) >= 0)
		return rightRotate(root);

	// Case "LR" - Left Right
	if (balance > 1 && getBalanceFactor(root->left) < 0) {
		root->left =  leftRotate(root->left);
		return rightRotate(root);
	}

	// Case "RR" - Right Right
	if (balance < -1 && getBalanceFactor(root->right) <= 0)
		return leftRotate(root);

	// Case "RL" - Right Left
	if (balance < -1 && getBalanceFactor(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

ActivitiesContainer removeActivity(ActivitiesContainer container, int activityId) {
	if (!container || !container->avlTree) return container; //No action
	
	container->avlTree = deleteNode(container->avlTree, activityId);
	return container;
}




// Search a node in the AVL tree
Node * search(Node* root, int activityId) {
	if (root == NULL) return NULL;
	
	int compareResult = compareWithId(root->activity, activityId);
	
	if(compareResult == 0) return root;
	else if(compareResult > 0) search(root->right, activityId);
	else search(root->left, activityId);
}



// Function to perform inorder traversal of AVL tree and print the contained activity
void inOrder(Node* root) {
	if (root != NULL) {
		inOrder(root->left);
		print(root->activity);
		inOrder(root->right);
	}
}

// Function to perform preorder traversal of AVL tree and print the contained activity
void preOrder(Node* root) {
	if (root != NULL) {
		print(root->activity);
		preOrder(root->left);
		preOrder(root->right);
	}
}

// Function to perform postorder traversal of AVL tree and print the contained activity
void postOrder(Node* root) {
	if (root != NULL) {
		postOrder(root->left);
		postOrder(root->right);
		print(root->activity);
	}
}





// Creates and returns a new empty activity container (tree)
ActivitiesContainer newActivityContainer(void) {
	ActivitiesContainer tree = malloc(sizeof(struct containerItem)); 
	if (tree != NULL) {
		tree->avlTree = NULL;
		tree->nextId = 1;
	}
	
	return tree;
}









// Function to read all activities from a file
ActivitiesContainer readActivitiesFromFile(const char* filename, int* count) {
	ActivitiesContainer newContainer = newActivityContainer();
	if(newContainer == NULL) return NULL;
	
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Il file %s non esiste. Verrà creato un contenitore vuoto per le attività.\n", filename);
		*count = 0;
		return newContainer;
	}
	
	*count = 0;
	
	while (!feof(file)) {  
		Activity * currentActivity = readActivityFromFile(file);
		if (currentActivity == NULL) {
			fclose(file);
			return newContainer;
		}
		
		newContainer = insertActivity(newContainer, currentActivity);
	}
	  
	fclose(file);
	return newContainer;
}



// Function to perform preorder traversal of AVL tree and save to file activity by activity
void inOrderSaveActivitiesToFile(FILE* file, Node* root) {
	if (root != NULL) {
		inOrderSaveActivitiesToFile(file, root->left);
		saveActivityToFile(file, root->activity);
		inOrderSaveActivitiesToFile(file, root->right);
	}
}

// Function to save activities (tree) to a file
// 0 = OK, 1 = ERROR
int saveActivitiesToFile(const char* filename, ActivitiesContainer container) {
	if (container == NULL) return 1;
	
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("Errore nell'apertura del file %s per la scrittura.\n", filename);
		return 1;
	}

	inOrderSaveActivitiesToFile(file, container->avlTree);

	fclose(file);
	printf("Attività salvate con successo nel file %s\n", filename);
	return 0;
}





// Function to perform postorder delete of nodes
void deleteActivityContainerSubtree(Node* root) {
	if (root != NULL) {
		deleteActivityContainerSubtree(root->left);
		deleteActivityContainerSubtree(root->right);
		
		deleteActivity(root->activity);
		free(root->activity);
		free(root);
	}
}

// Function to delete the container
void deleteActivityContainer(ActivitiesContainer container) {
	if (container == NULL) return;
	
	if (container->avlTree == NULL) {
		free(container);
		return;
	}
	
	deleteActivityContainerSubtree(container->avlTree);
	free(container);
}






// Utility function to do some test
ActivitiesContainer buildActivities() {
	/*ActivitiesContainer newContainer = newActivityContainer();
	if (newContainer == NULL) return newContainer;    // Se la lista è NULL, ritorna NULL (errore)
 
	Activity* activity = newActivity( 1, "Nome attività", "Descr attività", "Corso 1", 1746613562, 1748600762, 1747736762, 7200, 600, 1);
	Activity* activity2 = newActivity( 5, "Nome attività", "Descr attività", "Corso 2", 1746613562, 1748600762, 1747736762, 7200, 600, 1);
	Activity* activity3 = newActivity( 3, "Nome attività", "Descr attività", "Corso 3", 1746613562, 1748600762, 1747736762, 7200, 600, 1);
	Activity* activity4 = newActivity( 7, "Nome attività", "Descr attività", "Corso 4", 1746613562, 1748600762, 1747736762, 7200, 600, 1);
  	
  	newContainer = insertActivity(newContainer, activity);
  	newContainer = insertActivity(newContainer, activity2);
  	newContainer = insertActivity(newContainer, activity3);
  	newContainer = insertActivity(newContainer, activity4);*/
  	
  	int countActivities = 0;
  	ActivitiesContainer newContainer = readActivitiesFromFile(DEFAULT_ACTIVITIES_FILE, &countActivities);
  	
  	printf("========================= dopo inserimento iniziale ========================\n");
  	printActivities(newContainer);
  	printf("============================================================================\n");
  	printf("============== dopo delete ==============\n");
  	
	newContainer = removeActivity(newContainer, 1); 
  	
  	int saveResult = saveActivitiesToFile("activities_list_SAVED.txt", newContainer);
  	
  	return newContainer; 
}






// Prints all activities
void printActivities(ActivitiesContainer container) {
	inOrder(container->avlTree);
}



