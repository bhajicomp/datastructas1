#include <iostream>
#include <cstdlib>
#include "NodeTypes.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

using namespace std;

BTNode * createBTNode (string word) {
    BTNode * newNode = new BTNode;
    newNode->word = word;
    newNode->count = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

int height(BTNode * root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

bool isEqual(BTNode * root1, BTNode * root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    }
    if (root1 == NULL || root2 == NULL) {
        return false;
    }
    return (root1->word == root2->word) && isEqual(root1->left, root2->left) && isEqual(root1->right, root2->right);
}

int weight(BTNode * root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return weight(root->left) + weight(root->right);
}

void levelOrderByLevels (BTNode * root) {
    if (root == NULL) {
        return;
    }
    queue<BTNode*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            BTNode* currentNode = q.front();
            q.pop();
            cout << currentNode->word << " ";
            if (currentNode->left != NULL) {
                q.push(currentNode->left);
            }
            if (currentNode->right != NULL) {
                q.push(currentNode->right);
            }
        }
        cout << endl;
    }
}

void deleteBT (BTNode * root) {
    if (root == NULL) {
        return;
    }
    deleteBT(root->left);
    deleteBT(root->right);
    delete root;
}

BTNode * insertBSTRec (BTNode * root, string word) {
    if (root == NULL) {
        return createBTNode(word);
    }
    if (word < root->word) {
        root->left = insertBSTRec(root->left, word);
        root->left->parent = root;
    } else if (word > root->word) {
        root->right = insertBSTRec(root->right, word);
        root->right->parent = root;
    } else {
        root->count++;
    }
    return root;
}

BTNode * containsBSTRec (BTNode * root, string word) {
    if (root == NULL || root->word == word) {
        return root;
    }
    if (root->word < word) {
        return containsBSTRec(root->right, word);
    }
    return containsBSTRec(root->left, word);
}

BTNode * deleteNodeBST (BTNode * root, string word) {
    if (root == NULL) {
        return root;
    }
    if (word < root->word) {
        root->left = deleteNodeBST(root->left, word);
    } else if (word > root->word) {
        root->right = deleteNodeBST(root->right, word);
    } else {
        if (root->left == NULL) {
            BTNode *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            BTNode *temp = root->left;
            delete root;
            return temp;
        }
        BTNode *temp = minimumBST(root->right);
        root->word = temp->word;
        root->right = deleteNodeBST(root->right, temp->word);
    }
    return root;
}

BTNode * minimumBST (BTNode * root) {
    BTNode * current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

BTNode * maximumBST (BTNode * root) {
    BTNode * current = root;
    while (current && current->right != NULL) {
        current = current->right;
    }
    return current;
}

BTNode * inOrderSuccessor (BTNode * node) {
    if (node->right != NULL) {
        return minimumBST(node->right);
    }
    BTNode * parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

BTNode * ceiling(BTNode * root, string key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->word == key) {
        return root;
    }
    if (root->word < key) {
        return ceiling(root->right, key);
    }
    BTNode *temp = ceiling(root->left, key);
    return (temp != NULL) ? temp : root;
}

BTNode * reBalanceBST (BTNode * root) {
    if (root == NULL) {
        return NULL;
    }
    vector<BTNode*> nodes;
    storeBSTNodes(root, nodes);
    int n = nodes.size();
    return buildTree(nodes, 0, n - 1);
}

void storeBSTNodes(BTNode* root, vector<BTNode*> &nodes) {
    if (root == NULL) {
        return;
    }
    storeBSTNodes(root->left, nodes);
    nodes.push_back(root);
    storeBSTNodes(root->right, nodes);
}

BTNode* buildTree(vector<BTNode*> &nodes, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    BTNode *root = nodes[mid];
    root->left = buildTree(nodes, start, mid - 1);
    root->right = buildTree(nodes, mid + 1, end);
    return root;
}