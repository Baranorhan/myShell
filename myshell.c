#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int flag = 0;
int * flagptr= &flag;
// Flag created for checking does the threads finish their job.

void *Threadss(void *message) {
  // Thread codes which converts void message to string then increase flag
   char* tid;
   tid = (char*) message;
    system(tid);

   *flagptr = *flagptr+1;
   pthread_exit(NULL);
}
 
void SplitFirst(char * command){
  // First method to split. Splits "|"
char* token;
  token = strtok(command, "|");

  while( token != NULL  ) {

    SplitSecond(token);
     
      token = strtok(NULL, "|");
   }

}
void SplitSecond(char *command){
// second method to split. Splits ";" resets flag to zero and has an quit atr to quit after other 
// commands are done.
     printf("echo:%s\n", command);
  char* token;
  pthread_t threads;
  token = strtok(command, ";");
  int quit = 0;
   /* walk through other tokens */
   *flagptr = 0;
   int count= 0;
  while( token != NULL  ) {
    if ( strcmp(token,"quit" ) ){
    count += 1;
     long rc = pthread_create(&threads, NULL, Threadss, (void *)token );

    }else quit = 1; 
    token = strtok(NULL, ";");
   }

  while(flag!=count);
  if (quit)
  exit(0);

}

 void batchMode(char *commands){
   // File reader for batch mode opens the file and calls SplitFirst with each line 
  FILE *file;
  char str[512];
  char* commmands = commands;
  int status = 1;
  int quit = 0;
  file = fopen(commmands, "r");
  if (file == NULL) {
    printf("File not found", commmands);
    return;
  }
  while (fgets(str, 512, file) != EOF && status != 0 && !feof(file)) {
    str[strcspn(str, "\n\r")] = 0;
    str[strcspn(str, "\r")] = 0;

   if ( !strcmp(str,"quit" ) )
    quit = 1;
    else {
   SplitFirst(str);
    printf("________________________\n ");
    }
  }
  fclose(file);
  if (quit){
    exit(0);
    
  }

 }
 int main(int argc, char** argv){
   // Main function first checks for argc then if batch mode doesn't quit, continues with Interactive method until quit command.

  if (argc >1){
    batchMode(argv[1]);
    
  }

  char input[50];
  char *inputptr;

  inputptr = input;

  printf("\n S H E L L:>");

  gets(inputptr);
  

  while(strcmp(inputptr, "quit")!= 0) {   
      SplitFirst(inputptr);

      printf("______________________________\n S H E L L:>");
     
      gets(inputptr);

  }

  return 0;

}