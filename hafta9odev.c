#include <stdio.h>
#include <stdlib.h>


struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};


int max(int a, int b) {
    return (a > b) ? a : b;
}


int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}


struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}


struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    
    x->right = y;
    y->left = T2;

  
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; 
}


struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    
    y->left = x;
    x->right = T2;

    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // Yeni kök
}


int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


struct Node* insertAVL(struct Node* node, int key) {
    
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else // AVL ağacında eşit değerlere genelde izin verilmez
        return node;

    
    node->height = 1 + max(height(node->left), height(node->right));

    
    int balance = getBalance(node);

    

    
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


int main() {
    
    struct Node *rootA = NULL;
    rootA = insertAVL(rootA, 30);
    rootA = insertAVL(rootA, 20);
    rootA = insertAVL(rootA, 10);
    printf("Test A (LL) Koku: %d, Preorder: ", rootA->key);
    preOrder(rootA);
    printf("\n");

   
    struct Node *rootB = NULL;
    rootB = insertAVL(rootB, 10);
    rootB = insertAVL(rootB, 20);
    rootB = insertAVL(rootB, 30);
    printf("Test B (RR) Koku: %d, Preorder: ", rootB->key);
    preOrder(rootB);
    printf("\n");

    
    struct Node *rootC = NULL;
    rootC = insertAVL(rootC, 30);
    rootC = insertAVL(rootC, 10);
    rootC = insertAVL(rootC, 20);
    printf("Test C (LR) Koku: %d, Preorder: ", rootC->key);
    preOrder(rootC);
    printf("\n");

    
    struct Node *rootD = NULL;
    rootD = insertAVL(rootD, 10);
    rootD = insertAVL(rootD, 30);
    rootD = insertAVL(rootD, 20);
    printf("Test D (RL) Koku: %d, Preorder: ", rootD->key);
    preOrder(rootD);
    printf("\n");

    return 0;
}