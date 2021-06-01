#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

// Stack structure
struct stack {
    int top;
    int size;
    int *arr;
};

// Creating stack
struct stack *newstack (int capacity)
{
    struct stack *new = (struct stack *) malloc (sizeof(struct stack));
    new->top = -1;
    new->size = capacity;
    new->arr = (int *) malloc (new->size*sizeof(int));
    
    return new;
}

// Inserting item to the stack
void push (int k, struct stack *st)
{
    // Checking if Stack is full
    if (st->top == st->size - 1) {
        printf("Stack Overflow");
        return;
    }
    
    st->top++;
    st->arr[st->top] = k;
}

// Remove item from the stack
int pop (struct stack *st)
{
    // Checking if stack is empty
    if (st->top == -1) {
        printf("Stack Underflow\n");
        return INT_MIN;
    }
    
    st->top--;
    return st->arr[st->top+1];
}

// Rcursive function to solve Tower of Hanoi
void toh (int n, struct stack *A, struct stack *C, struct stack *B, char a, char c, char b, FILE *fp)
{
    // Base case
    if (n == 1) {
        int k = pop(A);
        fprintf(fp,"Pop disk %d from Stack %c\n",k,a);
        push(k, C);
        fprintf(fp,"Push disk %d to Stack %c\n",n,c);
        return;
    }
    
    // Recursive step
    toh(n-1, A, B, C, a, b, c, fp);
    int k = pop(A);
    fprintf(fp,"Pop disk %d from Stack %c\n",k,a);
    push(k, C);
    fprintf(fp,"Push disk %d to Stack %c\n",n,c);
    toh(n-1, B, C, A, b, c, a, fp);
}

int main (int argc, char **argv)
{
    // Number of disks
    int n = atoi(argv[1]);
    
    // Create stacks
    struct stack *A = newstack(n);
    struct stack *B = newstack(n);
    struct stack *C = newstack(n);
    
    // Output file
    FILE *fp = fopen("toh.txt","w");
    
    // Enter n disks on stack A
    for (int i = 0; i < n; i++) {
        push(n-i, A);
        fprintf(fp,"Push disk %d to Stack A\n",A->arr[A->top]);
    }
    
    // Shifting disk from stack A to stack C
    // Taking stack B as middle stack
    char a = 'A';
    char b = 'B';
    char c = 'C';
    toh(n, A, C, B, a, c, b, fp);
    
    // Close output file
    fclose(fp);
    
    return 0;
}

// Code by: Pranav Kanire