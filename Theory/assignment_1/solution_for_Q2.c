#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
    int data;
    struct node *left,*right;
};

// Create node
struct node *newNode (int data)
{
    struct node *p = (struct node *) malloc (sizeof(struct node));
    
    p->data = data;
    p->left = p->right = NULL;
    
    return p;
}

struct node *construct_bst (int arr[], int start, int end)
{
    // Base cases
    if (start > end) {
        struct node *p = NULL;
        return p;
    }
    else if (start == end)
        return newNode(arr[start]);
    
    // Recursion
    struct node *root;
    root = newNode(arr[start]);
    
    int i = start+1;
    while (i<=end && arr[i] < arr[start])
        i++;
    
    root->left = construct_bst(arr, start+1, i-1);
    root->right = construct_bst(arr, i, end);
    
    return root;
}

// Inorder traversal
void inorder (struct node* root)
{
    if(root->left != NULL)
        inorder(root->left);
    
    if(root != NULL)
        printf("%d ",root->data);
    
    if(root->right != NULL)
        inorder(root->right);
}

// Postorder traversal
void postorder(struct node *curr)
{
    if(curr->left != NULL)
        postorder(curr->left);

    if(curr->right != NULL)
        postorder(curr->right);

    printf("%d ", curr->data);        
}


int main ()
{
    int preorder[] = {5, 4, 2, 1, 3, 7, 6, 9, 8};
    int n = sizeof(preorder)/sizeof(preorder[0]);
    
    // Construct bst from given preorder
    struct node *root;
    root = construct_bst(preorder, 0, n-1);
    
    // Inorder traversal of bst
    printf("inorder traversal of the given preorder is:\n");
    inorder(root);
    printf("\n");
    
    // postorder traversal of bst
    printf("\npostoreder traversal of the given preorder is:\n");
    postorder(root);
    printf("\n");
    
    // To check code in case
    printf("\nIf u want to check the code for different preorders, then justc hange the initialized preorder array in the ’main function’\n");
    return 0;
}