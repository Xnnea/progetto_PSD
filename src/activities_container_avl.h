#ifndef ACTIVITIES_CONTAINER_AVL_H             // Start of inclusion block
#define ACTIVITIES_CONTAINER_AVL_H             // Macro definition to avoid multiple inclusions

#include "activity.h"

// Declare an opaque type for the tree node
typedef struct node* TreeNode;

TreeNode getLeftNode(TreeNode node);
TreeNode getRightNode(TreeNode node);
Activity getActivityFromNode(TreeNode node);

TreeNode search(TreeNode root, int activityId);

TreeNode insertNode(TreeNode node, Activity activity);

// Function to delete a node with given activityId (key) from a subtree. 
// It returns root of the modified subtree.
TreeNode deleteNode(TreeNode root, int activityId);

// Function to perform postorder delete of a subtree
void deleteSubtree(TreeNode root);

#endif // ACTIVITIES_CONTAINER_AVL_H          // End of inclusion block