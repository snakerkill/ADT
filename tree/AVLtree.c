/*=======================================================================
 File Name : binaryTree.c
 author    : 王浩 <snakerkill@163.com>
 touch     : 2015-04-23 16:38:59
 description : 平衡二叉查找树
=======================================================================*/
#include<stdio.h>
#include<stdlib.h>
typedef struct TNode* AVL;
typedef struct TNode* Position;
struct TNode {
    int value;
    int height;
    AVL left;
    AVL right;
};


Position get(AVL tree, int x){
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
int height(AVL tree) {
    if (tree == NULL) {
        return -1;
    }
    return tree->height;
}
int getHeight(AVL tree) {
    int h1 = height(tree->left) + 1;
    int h2 = height(tree->right) + 1;

    return (h1 > h2)? h1 : h2;
}

// single rotate 
AVL singleRotateWithLeft(AVL tree) {
    AVL temp = tree;
    tree = tree->left;
    temp->left = tree->right;
    temp->height = getHeight(temp);
    tree->right = temp;

    return tree;
}

AVL singleRotateWithRight(AVL tree) {
    AVL temp = tree;
    tree = tree->right;
    temp->right = tree->left;
    temp->height = getHeight(temp);
    tree->left = temp;

    return tree;
}

// double rotate
AVL doubleRotateWithLeft(AVL tree) {
    tree->left = singleRotateWithRight(tree->left);
    return singleRotateWithLeft(tree);
}

AVL doubleRotateWithRight(AVL tree) {
    tree->right = singleRotateWithLeft(tree->right);
    return singleRotateWithRight(tree);
}

AVL insert(AVL tree, int x){
    // empty tree
    if (tree == NULL) {
        tree = malloc(sizeof(AVL));
        if (tree == NULL) {
            return NULL;
        }
        tree->value = x;
        tree->height = 0;
        tree->left = NULL;
        tree->right = NULL;
    }

    // left
    if (x < tree->value) {
        tree->left = insert(tree->left, x);
        tree->height = getHeight(tree);
        // not balance
        if (height(tree->left) - height(tree->right) == 2) {
            // left child's left subtree
            if (x < tree->left->value) {
                tree = singleRotateWithLeft(tree);
            } else {
                tree = doubleRotateWithLeft(tree);
            }
        }
        return tree;
    }
    // right
    if (x > tree->value) {
        tree->right = insert(tree->right, x);
        tree->height = height(tree);
        // not balance
        if (height(tree->right) - height(tree->left) == 2) {
            // right child's right subtree
            if (x > tree->right->value) {
                tree = singleRotateWithRight(tree);
            } else {
                tree = doubleRotateWithRight(tree);
            }
        }
        return tree;
    }

    return tree;
}

void printAVL(AVL t){
    if (t == NULL) {
        return;
    }
    printAVL(t->left);
    printf("%d ",t->value);
    printAVL(t->right);
}

int main() {
    AVL tree;
    int a[10] = {8,12,2,4,6,7,1,0,-6,9};

    for (int i = 0; i < 10; i ++) {
        tree = insert(tree, a[i]);
    }
    printAVL(tree);
    printf("\n");

}
