#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
    char* fname = (char*)malloc(128*sizeof(char));
    fname = argv[1];
    FILE *fp = fopen(fname,"r");
    int ch,a=0;
    int n=0,min,max=0;
    long sum=0;
    while(1){
        ch = fgetc(fp);
        while(ch>47&&ch<58&&ch!=EOF){
            a = a*10 + ch-48;
            ch = fgetc(fp);
        }
        if(a==0)break;
        sum+=a;
        n++;
        if(max<a)max=a;
        if(!(min)||min>a)min=a;
        if(ch==EOF)break;
        a=0;
    }
    float avg = (float)sum/(float)n;
    fclose(fp);
    fp = fopen("output.txt","w");
    fprintf(fp,"%d\n",n);
    fprintf(fp,"%d\n",min);
    fprintf(fp,"%d\n",max);
    fprintf(fp,"%ld\n",sum);
    fprintf(fp,"%.2f",avg);
    fclose(fp);
}

//Code by: Pranav Kanire