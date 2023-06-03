#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define COUNT 10

int max(int num1, int num2){
    return (num1 > num2 ) ? num1 : num2;
}
int min(int num1, int num2) {
    return (num1 > num2 ) ? num2 : num1;
}
struct node{
    int value;
    struct node* parent;
    struct node* left;
    struct node* right;
};

struct node* newNode(int item, struct node* previous) {
    struct node* temp
        = (struct node*)malloc(sizeof(struct node));
    temp->value = item;
    temp->left = temp->right = NULL;
    temp->parent = previous;
    return temp;
}
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

void print2DUtil(struct node* root, int space) {
    // Base case
    if (root == NULL){
        return;
    }
    // Increase distance between levels
    space += COUNT;
    // Process right child first
    print2DUtil(root->right, space);
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    if(root->parent != NULL)
        printf("%d p%d\n", root->value, root->parent->value);
    else
        printf("%d pNULL\n", root->value);
    // Process left child
    print2DUtil(root->left, space);
}
// Wrapper over print2DUtil()
void print2D(struct node* root) {
    printf("--------------------------------------------------------------------------------\n");
    if (root == NULL){
        printf("EMPTY\n");
        printf("--------------------------------------------------------------------------------\n");
        return;
    }
    print2DUtil(root, 0);
    printf("--------------------------------------------------------------------------------\n");
}

struct node* insert(struct node* node, int k, struct node* previous) {
    // If the tree is empty, return a new node
    if (node == NULL){
        return newNode(k, previous);
    }
    previous = node;
    // Otherwise, recur down the tree
    if (k <= node->value){
        node->left = insert(node->left, k, previous);
    }
    else if (k > node->value){
        node->right = insert(node->right, k, previous);
    }
    // Return the (unchanged) node pointer
    return node;
}

struct node* search(struct node* node, int k){
    //printf("searching for %d, currently %d\n", k, node->value);
    if ( node == NULL ){
        return NULL;
    }
    if ( k == node->value ) {
        return node;
    } else if ( k < node->value ) {
        if (node->left == NULL) {
            return NULL;
        }
        search( node->left, k );
    } else if ( k > node->value ) {
        if (node->right == NULL) {
            return NULL;
        }
        search( node->right, k );
    }  
}


struct node* findMIN(struct node* node){
    if (node == NULL) {
            perror("dont give me NULL");
            return NULL;
    } else {
        if (node->left == NULL)
            return node;
        else 
            findMIN(node->left);
    }
}
struct node* findMAX(struct node* node){
    if (node == NULL) {
            perror("dont give me NULL");
            return NULL;
    } else {
        if (node->right == NULL)
            return node;
        else 
            findMAX(node->right);
    }
}
void BSTdelete( struct node* node, int k ){
    struct node* to_delete = search(node, k );
    if (to_delete == NULL){
        printf("no such a value to delete\n");
        return;
    } else {

        if(to_delete->right != NULL){//we have right child
            struct node* our_min = findMIN(to_delete->right);
            printf("our_min %d\n", our_min->value);

            to_delete->value = our_min->value;      
            // if (to_delete == node) {// == root
            //     to_delete
            // }
            if(our_min->right != NULL){
                our_min->right->parent = our_min->parent;
        
                if (our_min->parent->left == our_min) {//we are left child
                    our_min->parent->left = our_min->right;
                } else {   //we are right child //special case
                    our_min->parent->right = our_min->right;
                }
            } else {
                // 2cases
                if (our_min->parent->right == our_min) {
                    our_min->parent->right = NULL;
                } else {            
                    our_min->parent->left = NULL;
                }
            }
            free(our_min);
            our_min = NULL;
            return;
        } else  if (to_delete->left != NULL) {//we have left child
            
            if (to_delete == node) {// == root
                to_delete->left->parent = NULL;
                free(to_delete);
                to_delete = NULL;
                return;
            } 
            to_delete->left->parent = to_delete->parent;
            if (to_delete->parent->left == to_delete) {//we are left child
                to_delete->parent->left = to_delete->left;
            } else {  //we are right child
                to_delete->parent->right = to_delete->left;
            }
            free(to_delete);
            to_delete = NULL;
            return;
        } else { //leaf
            if (to_delete == node) {// == root
                free(to_delete);
                to_delete = NULL;
                return;
            }
            if (to_delete->parent->left == to_delete) {//we are left child
                to_delete->parent->left = NULL;
            } else {  //we are right child
                to_delete->parent->right = NULL;
            }
            free(to_delete);
            to_delete = NULL;
            return;
        }
    }
}

int tree_height(struct node* root) {
    if (root == NULL) 
        return 0;
    else {
        // Find the height of left, right subtrees
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        // Find max(subtree_height) + 1 to get the height of the tree
        return max(left_height, right_height) + 1;
    }
}

int main( int argc, char* argv[] ) {
    struct node* root = NULL;

    for ( int i = 1; i < argc; i += 2)  {
        if (strcmp(argv[i], "insert") == 0) {
            printf("insert %s\n",argv[i+1]);
            if ( root == NULL ) {
                root = insert(root, atoi(argv[i+1]), NULL);
            } else {
                insert(root, atoi(argv[i+1]), NULL);
            }
            print2D(root);
            printf("\n");
        } else if (strcmp(argv[i], "delete") == 0) {
            printf("delete %s\n",argv[i+1]);
            if ( root->value == atoi(argv[i+1]) ) {//delete value
                if (root->right != NULL) {
                    struct node* tmp_root = findMIN(root->right);
                    root->value = tmp_root->value;
                    if(tmp_root->right != NULL){
                        tmp_root->right->parent = tmp_root->parent;
                
                        if (tmp_root->parent->left == tmp_root) {//we are left child
                            tmp_root->parent->left = tmp_root->right;
                        } else {   //we are right child //special case
                            tmp_root->parent->right = tmp_root->right;
                        }
                    } else {
                        // 2cases
                        if (tmp_root->parent->right == tmp_root) {
                            tmp_root->parent->right = NULL;
                        } else {            
                            tmp_root->parent->left = NULL;
                        }
                    }
                    free(tmp_root);
                    tmp_root = NULL;
                } else if (root->left != NULL) {
                    root->left->parent = NULL;
                    root = root->left;
                } else {
                    free(root); //przy insercie jak root jest == null to rob root =  insert...
                    root = NULL;
                }
            } else {
                BSTdelete( root, atoi(argv[i+1]) );
            }
            print2D(root);
            printf("\n");
        } else {
            printf("wrond data %s\n", argv[i]);
            printf("wrond data %s\n", argv[i+1]);
        }
    }  
    printf("height %d", tree_height(root));
    return 0;
}
