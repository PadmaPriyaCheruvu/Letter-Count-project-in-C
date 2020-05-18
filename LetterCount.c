//Input files - palidrome.c goodvsevil.txt simpleSentence.txt fibonacci.c fightclub.txt

#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <sys/signal.h>
#include <unistd.h>

void main(int argc, char * argv[]) {
  int result;
  char decision;

  //Error checking

  //Minimum 4 arguments
  if (argc < 4) {
    printf("Usage:\n ./a.out N f1 f2 ... fn output_filename \n N - Number of files \n f1 f2 ... fn - File names of N files \nPlease run again in this format.\n Exiting...\n");
    exit(0);
  } 

  if (argc > 3) {
      if (atoi(argv[1]) != argc - 3) {
		
      		if(0!=atoi(argv[1]))
			
            		{printf("The number of files not matching the number of file names give. Try again. Exiting...\n");
	          		exit(0);}
		  else
		   {printf("Enter number of files. Exiting...\n");
		                     exit(0);}

	}

  }
  //Check if N files exist
  int f = 0;
  int n = argc - 3;
  int test = 0;
  for (f = 0; f < n; f++) {
    test = access(argv[f + 2], F_OK);
    if (test != 0) {
      printf("%s does not exist. Please try again. Exiting...\n", argv[f + 2]);
      exit(0);
    }

  }

  //Check if result file exists. If it does, ask user's permission to delete. Otherwise, create a new one. 
  int status = 0;
  result = access(argv[argc - 1], F_OK);
  if (result == 0) {
    printf("The output file with the name '%s' already exists. \nIf you want to overwrite it, please enter 'y'. Otherwise enter 'n' and run again with new output file name\n", argv[argc - 1]);
    scanf("%c", & decision);
    if (decision == 'y') {
      status = remove(argv[argc - 1]);
      if (status == 0)
        printf("%s file deleted successfully.Continuing execution...\n", argv[argc - 1]);
      else {
        printf("File couldn't be deleted. Exiting...\n");
        exit(0);
      }
    } else {
      printf("Exiting...\n");
      exit(0);
    }
  }
  
  
  int j;
  int num_of_files = atoi(argv[1]);
  for (j = 0; j < num_of_files; j++) {
    char c;
    int arr[26] = {0 };
    int pos = 0;
    int temp = 0;
    int pid;
    FILE * fp = fopen(argv[j + 2], "r"); //Opening input file
    FILE * wr_pt = fopen(argv[argc - 1], "a"); //Opening output file in append mode

    pid = fork(); //Fork to create child process that will work on (j+2)th file
    if (pid == 0) {
      printf("Child processing %s \n\n", argv[j + 2]);
      if (fp == NULL) {
        printf("Could not open file\n");
        exit(0);
      } else //Counting being done by child
      {
        c = fgetc(fp);
        while (c != EOF) {
          temp = toascii(c);
          if (temp >= 97 && temp <= 122) {
            pos = temp - 97;
            arr[pos] = arr[pos] + 1;
          } else if (temp >= 65 && temp <= 90) {
            pos = temp - 65;
            arr[pos] = arr[pos] + 1;
          }
          c = fgetc(fp);
        }
        fclose(fp);
      }
      fprintf(wr_pt, "%s result\n", argv[j + 2]);
      int i = 0;
      for (i = 0; i < 26; i++) {
        fprintf(wr_pt, "%s ............ %c - %d\n", argv[j + 2], i + 97, arr[i]);
      }
      fclose(wr_pt);
      exit(0);
    } //if process is child
  } //for(j<n)

  //Wait for all children to terminate
  if (getpid() != 0) {
    pid_t wpid;
    int status = 0;
    while ((wpid = wait( & status)) > 0);
    printf("\n\nPARENT EXITING......\n\n");
  }
} //main close
