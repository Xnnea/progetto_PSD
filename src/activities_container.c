#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "activities_container.h"
#include "activities_container_support_list.h"

// Defining the node structure for the AVL tree
typedef struct node {
	Activity activity;   // Data structure pointer: activity stored in the node
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
Node* createNode(Activity activity) {
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
Node* insertNode(Node* node, Activity activity) {
	
	// 0 - If node is null
	if (!node) {
		return createNode(activity);
	}
	
	int compareResult = compareAcivityById(activity, node->activity);
	
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
		int compareResultLeft = compareAcivityById(activity, node->left->activity);
		
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
		int compareResultRight = compareAcivityById(activity, node->right->activity);
		
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
ActivitiesContainer insertActivity(ActivitiesContainer container, Activity activity) {
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
			Activity activityToDelete = root->activity;
				
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
			Activity tempActivity = root->activity;
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
Node* search(Node* root, int activityId) {
	if (root == NULL) return NULL;
	
	int compareResult = compareWithId(root->activity, activityId);
	
	if(compareResult == 0) {
		return root;
	} else if(compareResult < 0) { // root->activity is < of activityId
		return search(root->right, activityId);
	} else {
		return search(root->left, activityId);
	}
}

void printActivityWithId(ActivitiesContainer container, int activityId) {
	if(container == NULL || container->avlTree == NULL ) return;

	Node* activityNode = search(container->avlTree, activityId);
	if (activityNode != NULL && activityNode->activity != NULL) {
		//printActivity(activityNode->activity);
		printActivityDetailWithMenu(activityNode->activity);
	}
}



// Function to perform inorder traversal of AVL tree and print the contained activity
void inOrder(Node* root) {
	if (root != NULL) {
		inOrder(root->left);
		//printActivity(root->activity);
		printActivityForList(root->activity);
		inOrder(root->right);
	}
}

// Function to perform preorder traversal of AVL tree and print the contained activity
void preOrder(Node* root) {
	if (root != NULL) {
		printActivity(root->activity);
		preOrder(root->left);
		preOrder(root->right);
	}
}

// Function to perform postorder traversal of AVL tree and print the contained activity
void postOrder(Node* root) {
	if (root != NULL) {
		postOrder(root->left);
		postOrder(root->right);
		printActivity(root->activity);
	}
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
		Activity currentActivity = readActivityFromFile(file);
		if (currentActivity == NULL) {
			fclose(file);
			return newContainer;
		}
		
		newContainer = insertActivity(newContainer, currentActivity);
		*count += 1;
	}
	  
	fclose(file);
	printf("Lette %d attività dal file %s.\n", *count, filename);
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
		//free(root->activity);
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






ActivitiesContainer addNewActivityToContainer(ActivitiesContainer container) {
	
	if (container == NULL) return 0;
	
	
	printf("\n====== Inserisci una nuova attività ======\n");
	
	char* activityName = NULL;
	while (activityName == NULL) {
		activityName = getInfoFromUser("Nome dell'attività (non vuoto): ");
		if (activityName == NULL) {
			printf("\nNome non valido. Per favore inserisci un nome valido.\n");
		}
	}

	char* activityDesr = NULL;
	while (activityDesr == NULL) {
		activityDesr = getInfoFromUser("Descrizione dell'attività (non vuota): ");
		if (activityDesr == NULL) {
			printf("\nDescrizione non valida. Per favore inserisci una descrizione valida.\n");
		}
	}

	char* activityCourse = NULL;
	while (activityCourse == NULL) {
		activityCourse = getInfoFromUser("Corso dell'attività (non vuoto): ");
		if (activityCourse == NULL) {
			printf("\nCorso non valido. Per favore inserisci un corso valido.\n");
		}
	}
	
	time_t insertDate = time(NULL);
	
	printf("\nVuoi inserire la data di scadenza per questa attività?\n");
	printf("1. Si\n");
	printf("0. No\n");
	printf("Scelta: ");
	int insertExpiryDate = getChoice(1);
	
	time_t expiryDate = 0; 
	if (insertExpiryDate == 1) {
		expiryDate = getDateFromUser();
	}
	
	time_t completionDate = 0;
	
	printf("\nCi siamo quasi! Inserisci il tempo stimato per il completamento dell'attività (espresso in MINUTI, compreso 1 e un anno):");
	unsigned int totalTime = getChoiceWithLimits(1, 525600);
	unsigned int usedTime = 0;
	
	printf("\nUltimo passo. Inserisci la priorità.\n");
	printf("1. ALTA\n");
	printf("2. MEDIA\n");
	printf("3. BASSA\n");
	printf("Scelta: ");
	short unsigned int priority = (short unsigned int) getChoiceWithLimits(1, 3);
	
	//With 0 id is automatically calculated
	Activity activity = newActivity( 0, activityName, activityDesr, activityCourse, insertDate, expiryDate, completionDate, totalTime, usedTime, priority);
	
	return insertActivity(container, activity);
}








// Prints all activities
void printActivities(ActivitiesContainer container) {
	if (container != NULL) {
		printf("\n=============================\n");
		printf("====== Tutte le attività =====\n");
		printf("==============================\n");
		printf("[NOTA: titolo, descrizione e corso potrebbero essere abbreviati. Vai al dettaglio attività per vedere le info complete]\n");
		printf("[Le attività sono ordinate per id]\n");
		printf("\n====================================================================================================\n");
		printf("[id] Titolo | Descrizione | Corso | Priorità | Data scadenza o data completamento\n");
		printf("====================================================================================================\n\n");

		inOrder(container->avlTree);
	}
}

void printInOrderToFile(Node* root, FILE* file) {
	if (root != NULL) {
		printInOrderToFile(root->left, file);
		printActivityForListToFile(root->activity, file);
		printInOrderToFile(root->right, file);
	}
}

// Prints all activities to file
void printActivitiesToFile(ActivitiesContainer container, FILE* file) {
	if (container != NULL && file != NULL) {
		printInOrderToFile(container->avlTree, file);
	}
}









void printInOrderProgress(Node* root) {
	if (root != NULL) {
		printInOrderProgress(root->left);
		printActivityProgressForList(root->activity);
		printInOrderProgress(root->right);
	}
}

// Prints activities progress
void printActivitiesProgress(ActivitiesContainer container) {
	if (container != NULL) {
		printf("\n=============================\n");
		printf("=== MONITORAGGIO PROGRESSO ===\n");
		printf("==============================\n");
		printf("[NOTA: titolo, descrizione e corso potrebbero essere abbreviati. Vai al dettaglio attività per vedere le info complete]\n");
		printf("[Le attività sono ordinate per id. Qui NON vengono mostrate le attività completate]\n");
		printf("\n====================================================================================================================================================\n");
		printf("[id] Titolo | Descrizione | Corso | Priorità | Progresso (%%) | Tempo usato (min) | Tempo al completamento (min) | Tempo totale (min) | Data scadenza\n");
		printf("====================================================================================================================================================\n\n");
		printInOrderProgress(container->avlTree);
	}
}

void printInOrderProgressToFile(Node* root, FILE* file)  {
	if (root != NULL) {
		printInOrderProgressToFile(root->left, file);
		printActivityProgressForListToFile(root->activity, file);
		printInOrderProgressToFile(root->right, file);
	}
}

void printActivitiesProgressToFile(ActivitiesContainer container, FILE* file) {
	if (container != NULL && file != NULL) {
		fprintf(file, "=== MONITORAGGIO PROGRESSO ===\n");
		printInOrderProgressToFile(container->avlTree, file);
	}
}


int getNextId(ActivitiesContainer container) {
	if (container == NULL) return -1;
	
	return container->nextId;
}





void buildInOrdeSupportListsForActivitiesReport(Node* root, ActivitiesContainerSupportList completedList, ActivitiesContainerSupportList ongoingList, ActivitiesContainerSupportList expiredList, ActivitiesContainerSupportList yetToBeginList, time_t beginDate, time_t nowDate) {
	if (root != NULL) {
		buildInOrdeSupportListsForActivitiesReport(root->left, completedList, ongoingList, expiredList, yetToBeginList, beginDate, nowDate); //left
		
		int isCompleted = isActivityCompleted(root->activity);
		if (isCompleted == 1) { //all complete activities
			int wasCompletedInLastPeriod = wasActivityCompletedAfterDate(root->activity, beginDate);
			if (wasCompletedInLastPeriod == 1) { //completed in the last period
				addActivityToSupportList(completedList, root->activity);
			}
		} else if ( wasActivityExpiredBeforeDate(root->activity, nowDate) == 1 ) { //expired and not completed
			addActivityToSupportList(expiredList, root->activity);
		} else if ( isActivityYetToBegin(root->activity) == 1 ) { //yet to begin
			addActivityToSupportList(yetToBeginList, root->activity);
		} else { //ongoing
			addActivityToSupportList(ongoingList, root->activity);
		}
		
		buildInOrdeSupportListsForActivitiesReport(root->right, completedList, ongoingList, expiredList, yetToBeginList, beginDate, nowDate); //right
	}
}

void printActivitiesReport(ActivitiesContainer container) {
	if (container == NULL || container->avlTree == NULL) return;
	
	time_t beginDate = time(NULL); //now
	beginDate = beginDate - 60*60*24*7; //one week ago
	
	char timeBuffer[100];
	struct tm* tmInfo;
	
	tmInfo = localtime(&beginDate);
	strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
	
	printf("\n\nIl report settimanale di default mostra i cambiamenti nell'ultima settimana.\n");
	printf("\nVuoi visualizzare il report a partire da %s (se scegli 'No' dovrai inserire una data)?\n", timeBuffer);
	printf("1. Si\n");
	printf("0. No\n");
	printf("Scelta: ");
	int insertReportDate = getChoice(1);
	
	if (insertReportDate == 0) {		
		time_t userDate = getDateFromUser();
		
		if (userDate >= time(NULL)) {
			printf("\nLa data inserita è nel futuro: verrà usata la data di default.");
		} else {
			tmInfo = localtime(&userDate);
			strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M", tmInfo);
			printf("\nSarà usata la seguente data per il report: %s\n", timeBuffer);
			beginDate = userDate;
		}
	}
	
	ActivitiesContainerSupportList completedList = newSupportList();
	ActivitiesContainerSupportList ongoingList = newSupportList();
	ActivitiesContainerSupportList expiredList = newSupportList();
	ActivitiesContainerSupportList yetToBeginList = newSupportList();
	buildInOrdeSupportListsForActivitiesReport(container->avlTree, completedList, ongoingList, expiredList, yetToBeginList, beginDate, time(NULL) );

	sortSupportList(completedList, compareAcivityByCompletionDate);
	sortSupportList(yetToBeginList, compareAcivityByInsertDate);
	sortSupportList(ongoingList, compareAcivityByPercentCompletion);
	sortSupportList(expiredList, compareAcivityByExpiryDate);

	printf("\n=============================\n");
	printf("=== REPORT ULTIMO PERIODO ====\n");
	printf("==============================\n");
	printf("[NOTA: titolo, descrizione e corso potrebbero essere abbreviati. Vai al dettaglio attività per vedere le info complete]\n");
	printf("[Qui le attività completate vengono mostrate solo se completate nel periodo di riferimento del report (e non prima)]\n");

	printf("\n\n=========================================================================");
	printf("\n=== Attività COMPLETATE nel periodo (ordinate per data di completamento):\n");
	printf("=======================================================================================\n");
	printf("[id] Titolo | Descrizione | Corso | Priorità | Data scadenza o data completamento\n\n");
	doActionOnSupportListActivities(completedList, printActivityForList);
	
	printf("\n\n=========================================================================");
	printf("\n=== Attività ANCORA DA INIZIARE (ordinate per data di inserimento):\n");
	printf("=======================================================================================\n");
	printf("[id] Titolo | Descrizione | Corso | Priorità | Data scadenza\n\n");
	doActionOnSupportListActivities(yetToBeginList, printActivityForList);
	
	printf("\n\n=========================================================================");
	printf("\n=== Attività IN CORSO (ordinate per percentuale di completamento):\n");
	printf("====================================================================================================================================================\n");
	printf("[id] Titolo | Descrizione | Corso | Priorità | Progresso (%%) | Tempo usato (min) | Tempo al completamento (min) | Tempo totale (min) | Data scadenza\n\n");
	doActionOnSupportListActivities(ongoingList, printActivityProgressForList);
	
	printf("\n\n=========================================================================");
	printf("\n=== Attività IN RITARDO (ordinate per data di scadenza):\n");
	printf("====================================================================================================================================================\n");
	printf("[id] Titolo | Descrizione | Corso | Priorità | Progresso (%%) | Tempo usato (min) | Tempo al completamento (min) | Tempo totale (min) | Data scadenza\n\n");
	doActionOnSupportListActivities(expiredList, printActivityProgressForList);
	
	printf("\n");
	
	//delete support lists
	deleteSupportList(&completedList);
	deleteSupportList(&yetToBeginList);
	deleteSupportList(&ongoingList);
	deleteSupportList(&expiredList);
}

void printActivitiesReportToFile(ActivitiesContainer container, time_t beginDate, FILE* file) {
	if (container == NULL || container->avlTree == NULL || file == NULL || beginDate < 0) return;
	
	ActivitiesContainerSupportList completedList = newSupportList();
	ActivitiesContainerSupportList ongoingList = newSupportList();
	ActivitiesContainerSupportList expiredList = newSupportList();
	ActivitiesContainerSupportList yetToBeginList = newSupportList();
	buildInOrdeSupportListsForActivitiesReport(container->avlTree, completedList, ongoingList, expiredList, yetToBeginList, beginDate, time(NULL) );

	sortSupportList(completedList, compareAcivityByCompletionDate);
	sortSupportList(yetToBeginList, compareAcivityByInsertDate);
	sortSupportList(ongoingList, compareAcivityByPercentCompletion);
	sortSupportList(expiredList, compareAcivityByExpiryDate);

	fprintf(file, "Data: %ld\n", beginDate);
	fprintf(file, "=== REPORT ULTIMO PERIODO ====\n\n");

	fprintf(file, "\n=== Attività COMPLETATE nel periodo (ordinate per data di completamento):\n");
	doActionWithFileOnSupportListActivities(completedList, file, printActivityForListToFile);
	
	fprintf(file, "\n\n=== Attività ANCORA DA INIZIARE (ordinate per data di inserimento):\n");
	doActionWithFileOnSupportListActivities(yetToBeginList, file, printActivityForListToFile);
	
	fprintf(file, "\n\n=== Attività IN CORSO (ordinate per percentuale di completamento):\n");
	doActionWithFileOnSupportListActivities(ongoingList, file, printActivityProgressForListToFile);
	
	fprintf(file, "\n\n=== Attività IN RITARDO (ordinate per data di scadenza):\n");
	doActionWithFileOnSupportListActivities(expiredList, file, printActivityProgressForListToFile);
 
	//delete support lists
	deleteSupportList(&completedList);
	deleteSupportList(&yetToBeginList);
	deleteSupportList(&ongoingList);
	deleteSupportList(&expiredList);
}

Activity getActivityWithIdForTest(ActivitiesContainer container, int activityId) {
	if(container == NULL || container->avlTree == NULL ) return NULL;

	Node* activityNode = search(container->avlTree, activityId);
	if (activityNode != NULL && activityNode->activity != NULL) {
		return activityNode->activity;
	}
	
	return NULL;
}