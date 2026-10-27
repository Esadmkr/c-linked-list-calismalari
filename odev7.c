#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}
int searchTreasure(struct Node* root, int target) {
    if(root == NULL){
        return 0;}
    
    if(root->data==target){
        return 1;}
    
    if(target<root->data){
        return(searchTreasure(root->left,target));}
    
    if(target>root->data){
        return(searchTreasure(root->right,target));}   

    return 0; 
}
int main() {
    struct Node* root = NULL;


    root = insert(root, 20);
    insert(root, 10);
    insert(root, 30);
    insert(root, 5);
    insert(root, 15);
    insert(root, 40);

    int guess;
    printf("--- Hazine Agaci Oyunu ---\n");
    printf("Kazi yapmak istediginiz sayiyi girin: ");
    if (scanf("%d", &guess) != 1) {
        printf("Gecersiz giris!\n");
        return 1;
    }

    
    if (searchTreasure(root, guess)) {
        printf("Tebrikler, Hazine bulundu!\n");
    } else {
        printf("Bosuna kazdin!\n");
    }

    return 0;
}