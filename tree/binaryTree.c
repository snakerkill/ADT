/*=======================================================================
 File Name : binaryTree.c
 author    : 王浩 <snakerkill@163.com>
 touch     : 2015-04-23 16:38:59
 description : 
 history  : 
=======================================================================*/
#include<stdio.h>
#include<stdlib.h>
typedef struct TNode* BST;
typedef struct TNode* Position;
struct TNode {
    int value;
    BST left;
    BST right;
};


Position get(BST tree, int x){
    if (tree == NULL) {
        return NULL;
    }
    if (x == tree->value) {
        return tree;
    }
    if (x < tree->value) {
        return get(tree->left, x);
    }
    if (x > tree->value) {
        return get(tree->right, x);
    }

    return NULL;
}
Position findMin(BST tree){
    if (tree->left != NULL) {
        return findMin(tree->left);
    }
    return tree;
}
BST delete(BST tree, int x){
    if (tree == NULL) {
        return NULL;
    }

    if (x < tree->value) {
        tree->left = delete(tree->left, x);
    } else if (x > tree->value) {
        tree->right = delete(tree->right, x);
    } else if (x == tree->value) {
        BST temp;
        // leaf node
        if (tree->left == NULL && tree->right == NULL) {
            free(tree);
            return NULL;
        // one child
        } else if(tree->left == NULL) {
            temp = tree->right;
            free(tree);
            return temp;
        } else if(tree->right == NULL) {
            temp = tree->left;
            free(tree);
            return temp;
        // two child
        } else {
            temp = findMin(tree->right);
            tree->value = temp->value;
            tree->right = delete(tree->right, temp->value);
            return tree;
        }
    }

    return tree;
}
BST insert(BST tree, int x){
    // empty tree
    if (tree == NULL) {
        tree = malloc(sizeof(BST));
        if (tree == NULL) {
            return NULL;
        }
        tree->value = x;
        tree->left = NULL;
        tree->right = NULL;
    }

    // left
    if (x < tree->value) {
        tree->left = insert(tree->left, x);
        return tree;
    }
    // right
    if (x > tree->value) {
        tree->right = insert(tree->right, x);
        return tree;
    }

    return tree;
}
void printBST(BST t){
    if (t == NULL) {
        return;
    }

    printBST(t->left);
    printf("%s\n", " /\\");
    printf("%s\n", "2  3");
    exit(0);
    //printf("%100.d ",t->value);
    printBST(t->right);
}

int main() {
    BST tree;
    int a[10] = {8,12,2,4,6,7,1,0,-6,9};

    for (int i = 0; i < 10; i ++) {
        tree = insert(tree, a[i]);
    }
    printBST(tree);
    printf("\n");


    tree = delete(tree, 2);

    printBST(tree);
    printf("\n");
}
