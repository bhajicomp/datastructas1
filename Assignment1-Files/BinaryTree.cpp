#include <iostream>
#include <cstdlib>
#include "BinaryTree.h"

using namespace std;


BTNode * createBTNode (string word) {

	return NULL;
}



void preOrder (BTNode * root) {
	
	if (root == NULL)
		return;
		
	// visit node
	
	preOrder (root->left);
	preOrder (root->right);
}



void inOrder (BTNode * root) {
	
	if (root == NULL)
		return;

	inOrder (root->left);
	
	// visit node
		
	inOrder (root->right);
}



void postOrder (BTNode * root) {
	
	if (root == NULL)
		return;

	postOrder (root->left);
	postOrder (root->right);
	
	// visit node
	
}



int moment (BTNode * root) {

	if (root == NULL)
		return 0;
		
	return (1 + moment (root->left) + moment (root->right));
}



int numOneChild (BTNode * root) {

	if (root == NULL)
		return 0;
		
	if (root->left == NULL && root->right == NULL)
		return 0;

	if (root->left == NULL)
		return 1 + numOneChild (root->right);
	else
	if (root->right == NULL)
		return 1 + numOneChild (root->left);
	else
		return (numOneChild (root->left) + numOneChild (root->right));
}



int numNonTerminal (BTNode * root) {

	if (root == NULL)
		return 0;
		
	if (root->left == NULL && root->right == NULL)
		return 0;
		
	return (1 + numNonTerminal (root->left) + numNonTerminal (root->right));
}



int nodeDepth (BTNode * node) {
	int branch;
	
	branch = 0;
	
	while (node->parent != NULL) {
		node = node->parent;
		branch++;
	}
	
	return branch;
}
