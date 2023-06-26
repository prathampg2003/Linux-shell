#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include <limits.h>
#include <pthread.h>



#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens
*
*/
pid_t pid;
int flag=0;
pid_t bg;
pid_t hell[MAX_INPUT_SIZE];
int countb=0;

char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}

int arrlen(char **tokens){
	int j=0;
	int len=0;
	while(tokens[j]!=NULL){
		j++;
		len++;
	}
	return len;
}

// void sigint_handler(int sig) {
//    int status;
//     pid_t pid = waitpid(-1, &status, WNOHANG);
//     if (pid > 0) {
//         printf("Foreground process %d terminated.\n", pid);
// }
// }

void sigchld_handler(int signum) {
    
   while((pid = waitpid(-1, NULL, WNOHANG))>0){

   	}
}


void  INThandler(int sig){
	
  signal(sig, SIG_IGN);
  
  kill(bg, SIGINT);
  
}


void forking(char **tokens){
		pid = fork();
			if (pid < 0) { /* error occurred */
			printf( "Fork Failed");
			
			}
			else if (pid == 0) { /* child process */
			if(execvp(*tokens,tokens)<0){
				printf("Command not found");
			}
			}
			else { /* parent process */
			/* parent will wait for the child to complete */
			wait(NULL);
		}
}

void seriess(char **tokens,int arlen){
	flag =-1;
	char **arr1=(char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	
	int count=0;
	
	int i=0;
	
	for( i=0;i<arlen;i++){

		if(strcmp(tokens[i],"&&")==0){
			arr1[count+1]=NULL;
			count=0;
			
			
			forking(arr1);
		// 	for(i=0;arr1[i]!=NULL;i++){
		// 	free(arr1[i]);
		// }

			
		}
		else{
			
			arr1[count]=tokens[i];
			
			count=count+1;
			
			

		}

		
	}
	
	
	
	if(i==arlen){
		
		forking(arr1);
	}
	return;

}



void parallel(char**tokens,int arlen){
	 pthread_t thread1, thread2;
	  pthread_t threads[arlen];

	 char **arr1=(char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	
	int count=0;
	
	int i=0;
	flag =-1;
	for( i=0;i<arlen;i++){



		if(strcmp(tokens[i],"&&&")==0){
			arr1[count+1]=NULL;
			count=0;
			
			
			forking(arr1);

		}

		else{
			
			
			arr1[count]=tokens[i];
			
			count=count+1;
			
			

		}

		
	}

	if(i==arlen){
		
		forking(arr1);
	}
	return;



	
	
	
	
	 

}






int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;


	while(1) {		
		
		signal(SIGCHLD, sigchld_handler);
		
		
			
		signal(SIGINT, INThandler);
		/* BEGIN: TAKING INPUT */

		char cwd[PATH_MAX];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("%s/ ", cwd);
		} else {
			perror("getcwd() error");
			return 1;
		}

		
		bzero(line, sizeof(line));
		printf("$ ");
		scanf("%[^\n]", line);
		getchar();
		if((strcmp(line,"")==0)|| (strcmp(line,"  ")==0)){
			continue;
		}
		

		

		char bin[10]="/bin/";
		int arrl;


		

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
		if(tokens[0]==NULL){
			continue;
		}
		if(strcmp(tokens[0],"\n")==0 ){
			
			continue;
		}
		
   

	   if(strcmp(tokens[0],"cd")==0){
			if(chdir(tokens[1])<0){
				printf("\nIncorrect\n");
				continue;
			}
			else{
				printf("\n Changed directory to check the directory type ls\n");
			}
			continue;

			
			
		}
		
		

		if(strcmp(tokens[0],"exit")==0){
			for(int i=0;i<countb;i++){
				kill(hell[i],SIGKILL);
			}
			
			kill(0,SIGKILL);
			
			exit(0);
		}

		arrl=arrlen(tokens);

		for(i=0;tokens[i]!=NULL;i++){

			if(strcmp(tokens[i],"&&")==0){
				

				seriess(tokens,arrl);
				break;
				

			}
			if(strcmp(tokens[i],"&&&")==0){
				parallel(tokens,arrl);
				
				break;
			}
			
		}
		if(flag==-1){
			flag=0;
			continue;
		}

		if(strcmp(tokens[arrl-1],"&")==0){
			tokens[arrl-1]=NULL;
			pid = fork();
			hell[countb]=pid;
			countb=countb+1;
			
			if (pid < 0) { /* error occurred */
			printf( "Fork Failed");
			
			}
			else if (pid == 0) { 
				
				/* child process */
				setpgid(0,0);
			execvp(*tokens,tokens);
			
			}
			else{
				setpgid(pid,pid);
				int stat;
				pid_t chld_pid = waitpid(pid, &stat,WNOHANG);
				printf("%d\n", pid);
				if (chld_pid == -1) 
				{
					perror("waitpid");
					return -1;
				}
			}
		}

		
		else{

			pid = fork();
			bg=pid;
			if (pid < 0) { /* error occurred */
			printf( "Fork Failed");
			
			}
			else if (pid == 0) { /* child process */
			if(execvp(*tokens,tokens)<0){
				printf("Command not found");
			}
			}
			else { /* parent process */
			/* parent will wait for the child to complete */
			wait(NULL);
		}
	}

   		
		
		
       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	return 0;
}
