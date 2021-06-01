#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
 
// For getting max value
int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int d)
{
    int power = 1;
    for(int i = 1; i < d; i++)
        power *= 10;
    
    int i, count[10] = { 0 };
 
    // Frequency of each digit 0 to 9 in array
    for (i = 0; i < n; i++)
        count[(arr[i] / power) % 10]++;
 
    // Assign count[i] its position in final array
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Output array
    int output[n];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / power) % 10] - 1] = arr[i];
        count[(arr[i] / power) % 10]--;
    }
 
    // Copy sorted array according to given digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(int arr[], int n, int d)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
    
    // Count sort digit by digit
    for (int i = 1; i <= d; i++)
        countSort(arr, n, i);
}
 
int main(int argc, char** argv)
{
    
    int d = atoi(argv[2]);
    int arr[1000006];
    int number = 0;
    
    // Input from file
    FILE *fp = fopen(argv[1],"r");
    char ch = fgetc(fp);
    while(ch != EOF){
        
        int n = 0;
        int i = 0;
        
        while(ch >= '0' && ch <= '9'){
            n = n*10 + ch-48;
            ch = fgetc(fp);
            i++;
        }
        if(i == 0)
            break;
        
        number++;
        arr[number-1] = n;
        
        if(ch != EOF)ch = fgetc(fp);
        else break;
        
    }
    fclose(fp);
     
    // Function Call
    radixsort(arr, number, d);
    
    // Function to write array in file
    fp = fopen("radix.txt","w");
    
    for (int i = 0; i < number; i++)
        fprintf(fp,"%d\n",arr[i]);
        
    fclose(fp);
        
    return 0;
}

// Code by: Pranav Kanire