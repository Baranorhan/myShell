#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int flag = 0;
int * flagptr= &flag;

void *Threadss(void *message) {

   char* tid;
   tid = (char*) message;
    system(tid);

   *flagptr = *flagptr+1;
   pthread_exit(NULL);
}
void SplitFirst(char * command){
char* token;
  token = strtok(command, "|");

  while( token != NULL  ) {

    SplitSecond(token);
     
      token = strtok(NULL, "|");
   }

}
void SplitSecond(char *command){

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
  FILE *file;
  char str[512];
  char* filecommands = commands;
  int status = 1;

  file = fopen(filecommands, "r");
  if (file == NULL) {
    printf("Could not open file %s", filecommands);
    return ;
  }
  while (fgets(str, 512, file) != EOF && status != 0 && !feof(file)) {
    str[strcspn(str, "\n\r")] = 0;
    str[strcspn(str, "\r")] = 0;
    printf("------------------------\nCommand : %s\n", str);
  int c=0;
while (str[c] != '\0') {
      printf("\n  %c  \n", str[c]);
      c++;
   }    
   
   SplitFirst(str);
  }
  fclose(file);


 }
 int main(int argc, char** argv){

  if (argc >1){
    batchMode(argv[1]);
    
  }

  char input[50];
  char *inputptr;

  inputptr = input;

  printf("myshell:>");

  gets(inputptr);
  

  while(strcmp(inputptr, "quit")!= 0) {   
      SplitFirst(inputptr);

      printf("\n\n\n myshell:>");
     
      gets(inputptr);

  }

  return 0;

}