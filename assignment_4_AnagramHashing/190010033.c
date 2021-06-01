#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node {
    char *word;
    struct node *next;
};

// Hash function
int hash (char *word, int m)
{
    int i=0, s=0;
    
    // Sum of ASCII values
    while (word[i] != '\0') {
        s += word[i];
        i++;
    }
    
    // Return index in hashtable
    return s%m;
}

void addToHashtable (char temp[], struct node *hashtable[], int m, int i)
{
    // Incex number in hashtable
    int index = hash(temp, m);
    
    // Creating new node
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->word = (char *)malloc((i+1)*sizeof(char));
    strcpy(new_node->word, temp);
    
    // Add at first position
    if (hashtable[index] == NULL)
        hashtable[index] = new_node;
    else {
        new_node->next = hashtable[index];
        hashtable[index] = new_node;
    }
}

int isAnagram (char *temp, char *word)
{
    // Arrays to count frequency of each char
    int num_char = 126;
    int count1[126] = {0};
    int count2[126] = {0};
    int i = 0;
    
    // Counting frequency of each char in string
    while (temp[i] != '\0') {
        count1[temp[i]]++;
        i++;
    }
    i = 0;
    while (word[i] != '\0') {
        count2[word[i]]++;
        i++;
    }
    
    // Anagram check using frequency of chars
    for(i = 0; i < num_char; i++){
        if (count2[i] != count1[i])
            return 0;
    }
    return 1;
}

void searchHashtable (char temp[], struct node *hashtable[], int m, FILE *fptr)
{
    // Returns index to check for given word in hashtable
    int index = hash(temp, m);
    
    // Searching at correct slot
    struct node *check = hashtable[index];
    
    if (check == NULL)
        fprintf(fptr,"\n");
    else {
        while (check) {
            if (isAnagram(temp, check->word))
                fprintf(fptr,"%s ",check->word);
            check = check->next;
        }
        fprintf(fptr,"\n");
    }
    
    return;
}

// Initiate each slot hashtable as NULL
void initiate (struct node *hashtable[], int m)
{
    for (int i = 0; i < m; i++) {
        hashtable[i] = NULL;
    }
    return;
}

int main (int argc, char **argv)
{
    int m = atoi(argv[2]);
    struct node *hashtable[m];
    initiate (hashtable, m);
    
    FILE *fp = fopen(argv[1], "r");
    int ch = fgetc(fp);
    
    // Take input through file
    while (ch != EOF) {
        char temp[32];
        int i = 0;
        while (ch != '\n' && ch != EOF) {
            temp[i] = ch;
            i++;
            ch = fgetc(fp);
        }
        temp[i] = '\0';
        
        // Function to add words in hashtable
        addToHashtable (temp, hashtable, m, i);
        
        if (ch == '\n') {
            ch = fgetc(fp);
            continue;
        }
    }
    
    fclose(fp);
    
    
    fp = fopen(argv[3], "r");
    ch = fgetc(fp);
    FILE *fptr = fopen("anagrams.txt", "w");
    
    // Query words to find anagrams
    while (ch != EOF) {
        char temp[32];
        int i = 0;
        while (ch != '\n' && ch != EOF) {
            temp[i] = ch;
            i++;
            ch = fgetc(fp);
        }
        temp[i] = '\0';
        
        // Function call to search for anaagrams
        searchHashtable (temp, hashtable, m, fptr);
        
        if (ch == '\n') {
            ch = fgetc(fp);
            continue;
        }
    }
    
    return 0;
}

// Code by: Pranav Kanire