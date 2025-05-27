#include "activity_helper.h"
#include "activities_container_avl.h"

// Defining the node structure for the AVL tree
typedef struct node {
	Activity activity;   // Data structure pointer: activity stored in the node
	struct node* left;
	struct node* right; 
	int height;
} Node;



TreeNode getLeftNode(TreeNode node) {
	if (!node) return NULL;
	
	return node->left;
}

TreeNode getRightNode(TreeNode node) {
	if (!node) return NULL;
	
	return node->right;
}


Activity getActivityFromNode(TreeNode node) {
	if (!node) return NULL;
	
	return node->activity;
}


// Search a node in the AVL tree
TreeNode search(TreeNode root, int activityId) {
	if (root == NULL) return NULL;
	
	int compareResult = compareWithId( getActivityFromNode(root), activityId );
	
	if(compareResult == 0) {
		return root;
	} else if(compareResult < 0) { // root->activity is < of activityId
		return search( getRightNode(root), activityId );
	} else {
		return search( getLeftNode(root), activityId );
	}
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
TreeNode insertNode(TreeNode node, Activity activity) {
	
	// 0 - If node is null
	if (!node) {
		return createNode(activity);
	}
	
	int compareResult = compareActivityById(activity, node->activity);
	
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
		int compareResultLeft = compareActivityById(activity, node->left->activity);
		
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
		int compareResultRight = compareActivityById(activity, node->right->activity);
		
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



// Return the node with minimum key (id) value found in that subtree. Used only by deleteNode.
Node* minValueNode(Node* node) {
	if (!node) return NULL;
	Node* current = node;

	// Loop down to find the leftmost leaf
	while ( current->left != NULL)
		current = current->left;

	return current;
}

// Function (recursive) to delete a node with given activityId (key) from a subtree. 
// It returns root of the modified subtree.
TreeNode deleteNode(TreeNode root, int activityId) {
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
			// Node* is the same as TreeNode
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
			// Node* is the same as TreeNode
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


// Function to perform postorder delete of a subtree
void deleteSubtree(TreeNode root) {
	if (root != NULL) {
		deleteSubtree(root->left);
		deleteSubtree(root->right);
		
		deleteActivity(root->activity);
		//free(root->activity);
		free(root);
	}
}

