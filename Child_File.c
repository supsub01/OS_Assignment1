//Submitted by Supriya Subramanian
//NetID: sxs180366

/*README:

-input files: f1, f2, f3, f4, f5, f6, f7, f8, f9, f10
output file: myfile

-How to run: Compile the program using command cc OS_fileRead_Assg1.c, execute using
a.out <Number of input files> <Names of input files seperated by spaces> <Name of output file>

-Objective: Generate n child processes (for n input files) that each read an input file, calculate the frequency
of each occuring alphabet, and print that information into an output file. Each process prints its contents contiguously, 
order of processes may be random.
Simple error checking to ensure correct number of files has been entered, and all files are valid has been done.
Encountering
any of these errors results in exiting the program. 

*/


#include<stdio.h> 
#include <stdlib.h>

  
int main(int n, char** argv) 
{ 
    int i=0;
    int n_files=atoi(argv[1]);


    //Error checking for valid number of files
    if((n-2)<(n_files+1)){
        printf("Not enough files! \n");
        exit(0);
    }


    if((n-2)>(n_files+1)){
        printf("Too many files! \n");
        exit(0);
    }

    if(n_files<0){
        printf("We can't have negative input files! \n");
        exit(0);
    }

    if(n_files==0){
        printf("Don't want to read any files? \n");
        exit(0);
    }

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
                printf("CANNOT OPEN READING FILE %s \n",argv[i]);
                exit(0);
            }

            if (file_write == NULL)
             {
                printf("CANNOT OPEN WRITING FILE \n");
                exit(0);
            }

            //Iterating each character and incrementing frequency array
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
             
             //Printing the frequency values into the output folder
             int j;
             fprintf (file_write, "FREQUENCIES FOR FILE %s: \n",argv[i]);
             for(j=0;j<26;j++){
                fprintf (file_write, "Frequency of %c=%d \n",65+j,freq[j]);
             }

             //Closing input and output files
             fclose(fptr);
             fclose(file_write);

            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            exit(0); 
        } 
    } 

    //After child process terminates, parent continues its execution after wait system call instruction
    for(i=0;i<n_files+2;i++) // loop will run n times 
    wait(NULL); 

    printf(" \n GOODBYE \n -Parent \n");
      
} 
