#include<stdio.h> 
#include <stdlib.h>

  
int main(int n, char** argv) 
{ 
    int i=0;
    int n_files=atoi(argv[1]);
    //printf("n_files is %d",n_files);
    for(i=2;i<n_files+2;i++) // loop will run n times  
    { 
        if(fork() == 0) 
        {   //write the file analysis code here
            FILE *fptr;
            FILE *file_write;
            char filename[15];
            char ch;
            int freq[26]={0};

            //Opening input and output files
            if(i==2) file_write=fopen(argv[n-1],"w");
            else file_write=fopen(argv[n-1],"a");

            printf("Opening %s .... \n",argv[i]);
            fptr = fopen(argv[i], "r");
            
            if (fptr == NULL)
             {
                printf("Cannot open reading file %s \n",argv[i]);
                exit(0);
            }

            if (file_write == NULL)
             {
                printf("Cannot open writing file \n");
                exit(0);
            }

            //Iterating each character and incrementing frequncy array
             ch = fgetc(fptr);

             while (ch != EOF)
             {
        
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

             //Printing the frequency values into the new folder
             int j;
             fprintf (file_write, "FREQUENCIES FOR FILE %s: \n",argv[i]);
             for(j=0;j<26;j++){
                fprintf (file_write, "Frequency of %c=%d \n",65+j,freq[j]);
             }

             //closing input and output files
             fclose(fptr);
             fclose(file_write);

            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            exit(0); 
        } 
    } 

    //After child process terminates, parent continues its execution after wait system call instruction
    for(i=0;i<5;i++) // loop will run n times (n=5) 
    wait(NULL); 
      
} 
