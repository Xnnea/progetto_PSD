#include "activity_helper.h"
#include "activities_container_avl.h"

/*
 * "struct node" Documentation
 * 
 * Syntactic Specification:
 * typedef struct node {
 *     Activity activity;
 *     struct node* left;
 *     struct node* right;
 *     int height;
 * } Node;
 * 
 * Semantic Specification:
 * Defines the node structure for the AVL tree. Each node contains an activity data structure (pointer),
 * pointers to left and right child nodes, and stores its height for efficient AVL balancing operations.
 * 
 * Fields:
 * - activity: The Activity data structure (pointer) stored in this node
 * - left: Pointer to the left child node (contains activities with smaller IDs)
 * - right: Pointer to the right child node (contains activities with larger IDs)
 * - height: The height of this node in the tree (length of longest path to a leaf)
 * 
 * Notes:
 * - For any node, all activities in the left subtree have IDs smaller than the node's activity ID
 * - For any node, all activities in the right subtree have IDs larger than the node's activity ID
 * - The height field accurately reflects the node's height in the tree
 * - The AVL balance property is maintained: |height(left) - height(right)| <= 1
 */
typedef struct node {
	Activity activity;   // Data structure pointer (activity stored in the node)
	struct node* left;
	struct node* right; 
	int height;
} Node;




/*
 * getLeftNode
 * 
 * Syntactic Specification:
 * TreeNode getLeftNode(TreeNode node);
 * 
 * Semantic Specification:
 * Returns the left child of the specified node.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'node == NULL', returns 'NULL'
 * - Otherwise, returns 'node->left'
 * 
 * Side Effects:
 * - None
 */
TreeNode getLeftNode(TreeNode node) {
	if (!node) return NULL;
	
	return node->left;
}

/*
 * getRightNode
 * 
 * Syntactic Specification:
 * TreeNode getRightNode(TreeNode node);
 * 
 * Semantic Specification:
 * Returns the right child of the specified node.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'node == NULL', returns 'NULL'
 * - Otherwise, returns 'node->right'
 * 
 * Side Effects:
 * - None
 */
TreeNode getRightNode(TreeNode node) {
	if (!node) return NULL;
	
	return node->right;
}

/*
 * getActivityFromNode
 * 
 * Syntactic Specification:
 * Activity getActivityFromNode(TreeNode node);
 * 
 * Semantic Specification:
 * Returns the activity stored in the specified node.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'node == NULL', returns 'NULL'
 * - Otherwise, returns 'node->activity'
 * 
 * Side Effects:
 * - None
 */
Activity getActivityFromNode(TreeNode node) {
	if (!node) return NULL;
	
	return node->activity;
}

/*
 * search
 * 
 * Syntactic Specification:
 * TreeNode search(Node* root, int activityId);
 * 
 * Semantic Specification:
 * Searches for an activity with the specified ID (key of the AVL tree) in the tree rooted at 'root'.
 * 
 * Preconditions:
 * - 'activityId' must be a valid ID
 * 
 * Postconditions:
 * - If 'root == NULL', returns 'NULL'
 * - If it finds the activity with the specified ID, returns the corresponding node
 * - Otherwise, returns 'NULL'
 * 
 * Side Effects:
 * - None
 */
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

/*
 * getHeight
 * 
 * Syntactic Specification:
 * int getHeight(Node* n);
 * 
 * Semantic Specification:
 * Returns the height of node 'n'. Remember that the height of a node is the length of the longest path from the node to a leaf. 
 * In AVL trees it's important to store it because it makes the calculation of the balance factor efficient and the verification 
 * of the need for rebalancing.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'n == NULL', returns 0
 * - Otherwise, returns 'n->height'
 * 
 * Side Effects:
 * - None
 */
int getHeight(Node* n) {
	if (n == NULL) return 0;
	return n->height;
}

/*
 * createNode
 * 
 * Syntactic Specification:
 * Node* createNode(Activity activity);
 * 
 * Semantic Specification:
 * Creates a new node containing the specified activity.
 * 
 * Preconditions:
 * - 'activity != NULL'
 * 
 * Postconditions:
 * - If 'activity == NULL', returns 'NULL'
 * - Otherwise, allocates a new node with the specified activity
 * - The new node has 'NULL' children and height 1
 * 
 * Side Effects:
 * - Allocates memory for a new node
 */
Node* createNode(Activity activity) {
	if (!activity) return NULL;
	Node* node = (Node*) malloc(sizeof(Node));
	if (node == NULL) return NULL;
	node->activity = activity;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // New node is initially added at leaf
	return node;
}


/*
 * getBalanceFactor
 * 
 * Syntactic Specification:
 * int getBalanceFactor(Node* n);
 * 
 * Semantic Specification:
 * Calculates the balance factor of the node (left subtree height - right subtree height).
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - If 'n == NULL', returns 0
 * - Otherwise, returns the difference between left and right child heights
 * 
 * Side Effects:
 * - None
 */
int getBalanceFactor(Node* n) {
	if (n == NULL) return 0;
	return getHeight(n->left) - getHeight(n->right);
}

/*
 * rightRotate
 * 
 * Syntactic Specification:
 * Node* rightRotate(Node* y);
 * 
 * Semantic Specification:
 * Performs a right rotation on node 'y' to maintain AVL tree properties.
 * 
 * Preconditions:
 * - 'y != NULL'
 * - 'y->left != NULL'
 * 
 * Postconditions:
 * - Returns the new root after rotation
 * - Heights of involved nodes are updated
 * - AVL properties are maintained
 * 
 * Side Effects:
 * - Modifies tree structure
 * - Updates node heights
 */
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

/*
 * leftRotate
 * 
 * Syntactic Specification:
 * Node* leftRotate(Node* x);
 * 
 * Semantic Specification:
 * Performs a left rotation on node 'x' to maintain AVL tree properties.
 * 
 * Preconditions:
 * - 'x != NULL'
 * - 'x->right != NULL'
 * 
 * Postconditions:
 * - Returns the new root after rotation
 * - Heights of involved nodes are updated
 * - AVL properties are maintained
 * 
 * Side Effects:
 * - Modifies tree structure
 * - Updates node heights
 */
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



/*
 * insertNode
 * 
 * Syntactic Specification:
 * TreeNode insertNode(TreeNode node, Activity activity);
 * 
 * Semantic Specification:
 * Inserts a new activity into the subtree rooted at 'node' while maintaining AVL properties.
 * 
 * Preconditions:
 * - 'activity != NULL'
 * 
 * Postconditions:
 * - If 'node == NULL', creates and returns a new node
 * - If the activity already exists (same ID), returns the unmodified tree
 * - Otherwise, inserts the activity and rebalances the tree if necessary
 * - The resulting tree maintains AVL properties
 * 
 * Side Effects:
 * - May allocate memory for new nodes
 * - Modifies tree structure
 * - Updates node heights
 */
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



/*
 * minValueNode
 * 
 * Syntactic Specification:
 * Node* minValueNode(Node* node);
 * 
 * Semantic Specification:
 * Returns the node with the minimum key value (id) in the tree rooted at 'node'. Leftmost leaf.
 * 
 * Preconditions:
 * - None (the function handles the case 'node == NULL')
 * 
 * Postconditions:
 * - If 'node == NULL', returns 'NULL'
 * - Otherwise, returns the leftmost node in the tree
 * - The returned node has no left child (if not 'NULL')
 * 
 * Side Effects:
 * - None
 */
Node* minValueNode(Node* node) {
	if (!node) return NULL;
	Node* current = node;

	// Loop down to find the leftmost leaf
	while ( current->left != NULL)
		current = current->left;

	return current;
}

/*
 * deleteNode
 * 
 * Syntactic Specification:
 * TreeNode deleteNode(TreeNode root, int activityId);
 * 
 * Semantic Specification:
 * Deletes the node with the specified ID from the subtree rooted at 'root' while maintaining AVL properties.
 * 
 * Preconditions:
 * - 'activityId' must be a valid ID
 * 
 * Postconditions:
 * - If 'root == NULL', returns 'NULL'
 * - If the node with 'activityId' doesn't exist, returns the unmodified tree
 * - Otherwise, deletes the node and rebalances the tree
 * - The activity contained in the deleted node is deallocated
 * 
 * Side Effects:
 * - Deallocates memory of the deleted node
 * - Deallocates the contained activity
 * - Modifies tree structure
 * - Updates node heights
 */
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

/*
 * deleteSubtree
 * 
 * Syntactic Specification:
 * void deleteSubtree(Node* root);
 * 
 * Semantic Specification:
 * Recursively (perform postorder visit) deletes all nodes of a subtree and their related activities.
 * 
 * Preconditions:
 * - None
 * 
 * Postconditions:
 * - All subtree nodes are deallocated
 * - All contained activities are deallocated
 * 
 * Side Effects:
 * - Deallocates all tree memory
 */
void deleteSubtree(TreeNode root) {
	if (root != NULL) {
		deleteSubtree(root->left);
		deleteSubtree(root->right);
		
		deleteActivity(root->activity);
		free(root);
	}
}

