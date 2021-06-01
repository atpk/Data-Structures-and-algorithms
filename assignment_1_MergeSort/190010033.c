#include<stdio.h>
#include<stdlib.h>
#define SIZE 1000005

void merge(int arr[], int start, int middle, int end){
//start, middle and end are just to differentiate two arrays that to bo merged

    int n1,n2;//for size of two arrays
    n1 = middle - start + 1;
    n2 = end - middle;
    
    /*creating and copying temporary arrays to compare and merge into original*/
    int arr1[n1],arr2[n2];
    for(int i = start; i <= middle; i++)
        arr1[i-start] = arr[i];
    for(int i = middle+1; i <= end; i++)
        arr2[i-middle-1] = arr[i];
    
    /*merging two temporary arrays into original*/
    int arr_1 = 0;//index for arr1
    int arr_2 = 0;//index for arr2
    int n = start;//index for original array
    
    while(arr_1<n1 && arr_2<n2){
        
        /*inserting elements in ascending order */
        if(arr1[arr_1] < arr2[arr_2]){
            arr[n] = arr1[arr_1];
            arr_1++;
        }
        else{
            arr[n] = arr2[arr_2];
            arr_2++;
        }
        n++;
    }
    
    //copy the remaining elements from both arrays
    while(arr_1 < n1){
        arr[n] = arr1[arr_1];
        arr_1++;
        n++;
    }
    while(arr_2 < n2){
        arr[n] = arr2[arr_2];
        arr_2++;
        n++;
    }
}

void merge_sort(int arr[], int start, int end){
    //start is the starting index and end is the last index to apply merge sort
    
    if(end > start){
        int middle = start + (end - start)/2;//middle is to split array into two halves
        
        //apply merge sort for both the falf arrays
        merge_sort(arr,start,middle);
        merge_sort(arr,middle+1,end);
        
        //merge both the half arrays
        merge(arr,start,middle,end);
    }
}

int main(int argc, char* argv[]){
    
    /*taking file name input as command line argument*/
    FILE *fp = fopen(argv[1],"r");
    
    int ch,a=0,n=0,i;
    int arr[SIZE];
    
    //reading elements from the file
    while(1){
        i=0;
        ch = fgetc(fp);
        while(ch>47&&ch<58&&ch!=EOF){
            a = a*10 + ch-48;
            ch = fgetc(fp);
            i++;
        }
        if(i==0)break;
        arr[n]=a;
        n++;
        if(ch==EOF)break;
        a=0;
    }
    
    fclose(fp);//close the input file
    
    /*applying merge sort*/
    merge_sort(arr,0,n-1);
    
    fp = fopen("mergesort.txt","w");//output file
    
    /*producing output in the file*/
    for(i = 0; i < n; i++)
        fprintf(fp,"%d\n",arr[i]);
    
    fclose(fp);//close output file
}

//Code by: Pranav Kanire