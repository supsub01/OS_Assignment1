#include<stdio.h> 
#include <stdlib.h>

  
int main(int n, char** argv) 
{ 
    int i=0;
    printf("n is %d",n);
    for(i=1;i<n-1;i++) // loop will run n times 
    { 
        if(fork() == 0) 
        {   //write the file analysis code here
            FILE *fptr;
            FILE *file_write;
            char filename[15];
            char ch;
            int freq[26];

             //filename=argv[i];
             file_write=fopen(argv[n],"w");
             fptr = fopen(argv[i], "r");
             printf("INDEX i=%d \n",i);
             if (fptr == NULL)
             {
                printf("Cannot open reading file at index %d \n",i);
                printf("Filename=%s",argv[i]);
                exit(0);
            }
            if (file_write == NULL)
             {
                printf("Cannot open writing file \n");
                exit(0);
            }

             ch = fgetc(fptr);

             while (ch != EOF)
             {
                //printf("%s has been opened!",argv[i]);
                //printf("%c \n", ch);
                 if(ch>='a' && ch<='z')
                 {
                    freq[ch - 97]++;
                 }
                 else if(ch>='A' && ch<='Z')
                 {
                     freq[ch - 65]++;
                 }

                 ch = fgetc(fptr);
             }
             int j;
             for(j=0;j<26;j++){
                fprintf (file_write, "Frequency of %c=%d \n",65+j,freq[j]);
             }
             fclose(fptr);


           
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            exit(0); 
        } 
    } 

    //After child process terminates, parent continues its execution after wait system call instruction
    for(i=0;i<5;i++) // loop will run n times (n=5) 
    wait(NULL); 
      
} 
