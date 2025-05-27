#ifndef ACTIVITIES_CONTAINER_AVL_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_AVL_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

// Declare an opaque type for the tree node
typedef struct node* TreeNode;



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
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - None
 */
TreeNode getLeftNode(TreeNode node);

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
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - None
 */
TreeNode getRightNode(TreeNode node);

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
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - None
 */
Activity getActivityFromNode(TreeNode node);

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
 * Effects:
 * - No modifications to data structures
 * 
 * Side Effects:
 * - None
 */
TreeNode search(TreeNode root, int activityId);

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
 * Effects:
 * - May allocate memory for new nodes
 * - Modifies tree structure
 * - Updates node heights
 * 
 * Side Effects:
 * - None
 */
TreeNode insertNode(TreeNode node, Activity activity);

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
 * Effects:
 * - Deallocates memory of the deleted node
 * - Deallocates the contained activity
 * - Modifies tree structure
 * - Updates node heights
 * 
 * Side Effects:
 * - Calls to 'deleteActivity()' and 'free()'
 */
TreeNode deleteNode(TreeNode root, int activityId);

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
 * Effects:
 * - Deallocates all tree memory
 * 
 * Side Effects:
 * - Calls to 'deleteActivity()' and 'free()'
 */
void deleteSubtree(TreeNode root);

#endif // ACTIVITIES_CONTAINER_AVL_H          // End of inclusion block