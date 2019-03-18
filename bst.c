#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//Struct for a node, includes the data and pointers to the right and left
//and right of the node
struct node {
    int data;
    struct node *right;
    struct node *left;
};
typedef struct node node;

//Allocates memeory for a new node
node *newNode(int new_data) {

    node *newnode = malloc(sizeof(node));
    *newnode = (node) {new_data, NULL, NULL};
    return newnode;
}

//Inserts a new node, if node already found prints out error stating
//that it has been found
node *insert(node *root, int data) {
    node *new_node = newNode(data);

    if (root == NULL) {
        root = new_node;
        return root;
    }

    if (data == root->data) printf("Node already inputted\n");
    
    else if (data > root->data) root->right = insert(root->right, data);
    else root->left = insert(root->left, data);

    return root;


}

//Finds the minimum node in a tree/subtree
node *minNode(node *node2) {
    node *temp = node2;

    while (temp->left != NULL) temp = temp->left;

    return temp;
}

//Deletes a node from the tree. Has different cases depending on whether the
//parent node has no children, one child or two children.
node *delete(node *root, int data) {
    if (root == NULL) return NULL;

    node *temp = NULL;
    if (data < root->data) root->left = delete(root->left, data);
    else if (data > root->data) root->right = delete(root->right, data);
    else {
        if (root->right == NULL) {
            temp = root->left;
            root = temp;
        }
        else if (root->left == NULL) {
            temp = root->right;
            root = temp;
        }
        else {
            temp = minNode(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;

}

//Finds a node in the tree
node *find(node *root, int data) {
    node *temp = root;

    if (root == NULL) return NULL;
    while(temp != NULL) {
        if(data > temp->data) temp = temp->right;
        else if (data < temp->data) temp = temp->left;
        else return temp;
    }
    return temp;

}

//Displays the tree in full
void display_tree(node* node)
{
    if (node == NULL) return;

    printf("%d",node->data);
    if(node->left != NULL) printf("(L:%d)",node->left->data);
    if(node->right != NULL) printf("(R:%d)",node->right->data);
    printf("\n");

    display_tree(node->left);
    display_tree(node->right);
}

int main() {

    node* root = NULL;

    //Inserts predefined data into tree
    int datas[11] = {20,7,25,3,9,29,8,13,31,15,22};
    printf("New Tree: ");
    for(int i = 0; i < 11; i++) {
        printf("%d ",datas[i]);
        root = insert(root,datas[i]);
    }
    display_tree(root);
    printf("To move onto next function enter -1\n");

    //Allows user to remove element from the tree
    int choice;
    do {
        printf("Enter data to remove: ");
        scanf("%d", &choice);
        if(choice == -1) break;
        root = delete(root, choice);

        if(root != NULL) display_tree(root);
        else break;
    } while(root != NULL);

    //Allows user to insert a new node into the tree
    int choice2;
    do {
        printf("Enter a new node to insert: ");
        scanf("%d", &choice2);
        if(choice2 == -1) break;
        root = insert(root, choice2);

        if (root != NULL) display_tree(root);
        else break;
    } while(root != NULL);

    //Allows user to search for a node within the tree
    int choice3 = 0;
    node *found;
    while(choice3 != -1) {
        printf("Enter data to search: ");
        scanf("%d",&choice3);

        found = find(root,choice3);
        if(found != NULL) {
            printf("Data found %d\n",found->data);
            if(found->left != NULL) printf("(L: %d)\n",found->left->data);
            if(found->right != NULL) printf("(R: %d)\n",found->right->data);
        }
        if (choice3 == -1) break;
        else printf("Node %d not in tree\n",choice3);
    }


}
