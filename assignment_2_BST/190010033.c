#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
    int data;
    struct node *left, *right;
};
struct node *root = NULL;

// Create a node
struct node *new_node(int key){
    struct node *t = (struct node *)malloc(sizeof(struct node));
    t->data = key;
    t->left = t->right = NULL;
    return t;
}

struct node *insert(struct node *node, int key){
    if(node == NULL)
      return new_node(key);

    // Traverse to leaf node to insert new node
    if (key < node->data)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    
    return node;
}

struct node *search(int key){
    struct node* curr = root;
    // Traverse down the tree
    while(curr){
            // 
        if(curr->data == key)
            break;
        
        if(key > curr->data)
            // Traverse right
            curr = curr->right;
        else
            // Traverse left
            curr = curr->left;
    }
    // Empty tree or key not found curr==NULL
    return curr;
}

struct node *minimum(struct node* curr){
    
    if(curr == NULL)
        // Empty tree
        return NULL;
    else{
        //Traverse left
        while(curr->left != NULL){
            curr=curr->left;
        }
    }
    return curr;
}

struct node *maximum(struct node* curr){
    
    if(curr == NULL)
    {
        // Empty tree
        return NULL;
    }
    else{
        //Traverse right
        while(curr->right){
            curr=curr->right;
        }
    }
    return curr;
}

void inorder(struct node *curr, FILE *fptr){
    
    // Traversing through left
    if(curr->left != NULL)
        inorder(curr->left,fptr);

    // printing root
    fprintf(fptr,"%d ", curr->data);

    // Traversing through right
    if(curr->right != NULL)
        inorder(curr->right,fptr);
}

void preorder(struct node *curr, FILE *fptr){
    // printing root
    fprintf(fptr,"%d ", curr->data);
    
    // Traversing through left
    if(curr->left != NULL)
        preorder(curr->left,fptr);
        
    // Traversing through right
    if(curr->right != NULL)
        preorder(curr->right,fptr);
}

void postorder(struct node *curr, FILE *fptr){

    // Traversing through left
    if(curr->left != NULL)
        postorder(curr->left,fptr);

        
    // Traversing through right
    if(curr->right != NULL)
        postorder(curr->right,fptr);

    // printing root
    fprintf(fptr,"%d ", curr->data);        
}

struct node *predecessor(struct node *curr){
    if (curr->left != NULL) 
        return maximum(curr->left);
    
    // Start from root and going down for predecessor
    struct node *pre = NULL;
    struct node *r = root;
    while(r != NULL){
        if(curr->data < r->data && r->left)
            r = r->left;
        else if(curr->data > r->data && r->right){
            pre = r;
            r = r->right;
        }
        else
            break;
    }
    
    return pre;
}

struct node* successor(struct node *curr){
    if (curr->right != NULL) 
        return minimum(curr->right); 
  
    // Start from root and going down for successor
    struct node* succ = NULL;
    struct node *r = root;
    while(r != NULL){ 
        if(curr->data < r->data && r->left){ 
            succ = r; 
            r = r->left; 
        } 
        else if(curr->data > root->data && r->right) 
            r = r->right; 
        else
            break; 
    } 
  
    return succ; 

}

void pro(char *a, int key, FILE *fptr){
    if(strcmp(a,"insert")==0){
        if(root == NULL)
            root = insert(root, key);
        else
            insert(root, key);
        fprintf(fptr,"%d inserted\n",key);
    }
    else{
        struct node *p = search(key);
        if(strcmp(a,"search")==0){
            if(p == NULL)
                fprintf(fptr,"%d not found\n",key);
            else
                fprintf(fptr,"%d found\n",key);
        }
        else if(strcmp(a,"successor")==0){
            if(p != NULL){
                // Node with given key is present in tree
                struct node* succ = successor(p);
                if(succ != NULL)
                    fprintf(fptr,"%d\n",succ->data);
                else
                    // Given key is maximum
                    fprintf(fptr,"successor of %d does not exist\n",key);
            }
            else
                // Node with given key doesn't exist
                fprintf(fptr,"%d does not exist\n",key);
        }
        else{
            if(p != NULL){
                // Node with given key is present in tree
                struct node *pre = predecessor(p);
                if(pre != NULL)
                    fprintf(fptr,"%d\n",pre->data);
                else
                    // Given key is minimum
                    fprintf(fptr,"predecessor of %d does not exist\n",key);
            }
            else
                // Node with given key doesn't exist
                fprintf(fptr,"%d does not exist\n",key);
        }
        
    }
}

void proceed(char *a, FILE *fptr){
    struct node *p = NULL;
    if(strcmp(a,"minimum")==0){
        p = minimum(root);
        if(p != NULL)
            fprintf(fptr,"%d\n",p->data);
        else
            // Empty tree
            fprintf(fptr,"\n");
    }
    else if(strcmp(a,"maximum")==0){
        p = maximum(root);
        if(p !=NULL)
            fprintf(fptr,"%d\n",p->data);
        else
            // Empty tree
            fprintf(fptr,"\n");
    }
    else if(strcmp(a,"inorder")==0){
        // Non-Empty tree
        if(root!=NULL)
            inorder(root,fptr);
        fprintf(fptr,"\n");
    }
    else if(strcmp(a,"preorder")==0){
        if(root!=NULL)// Non-Empty tree
            preorder(root,fptr);
        fprintf(fptr,"\n");
    }
    else{
        if(root!=NULL)// Non-Empty tree
            postorder(root,fptr);
        fprintf(fptr,"\n");
    }
}

int main(int argc, char **argv){
    struct node *root = NULL;
    FILE *fp = fopen(argv[1],"r");
    FILE *fptr = fopen("bst.txt","w");
    int ch;
    ch = fgetc(fp);
    while(ch != EOF){
        
        char a[15];
        int i = 0;
        while(ch > 96 && ch < 123){
            a[i] = ch;
            i++;
            ch = fgetc(fp);
        }
        a[i] = '\0';
        
        if(ch == ' '){
            ch = fgetc(fp);
            int n = 0;
            while(ch >= '0' && ch <= '9'){
                n = n*10 + ch-48;
                ch = fgetc(fp);
            }
            pro(a,n,fptr);
        }
        else
            proceed(a,fptr);
        if(ch == '\n')ch = fgetc(fp);
    }
    fclose(fp);
    return 0;
}

// Code by: Pranav Kanire