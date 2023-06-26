# Linux-shell
A Linux shell made in C is a program that emulates the functionality of a command-line interface found in Linux operating systems. 
It allows users to interact with the system by typing commands and executing them.

## ABOUT THE SHELL:-
-	This is a shell program that reads a line of input from the user and runs the corresponding commands. It uses several libraries, including stdio.h, sys/types.h, stdlib.h, string.h, unistd.h, sys/wait.h, signal.h, limits.h, and pthread.h.  
-	The tokenize function splits the input string into separate tokens (individual words) and returns an array of those tokens.  
- The arrlen function returns the length of the array of tokens.  
- The sigchld_handler function is a signal handler that catches the SIGCHLD signal and waits for child processes to complete.  
-	The INThandler function is a signal handler that catches the SIGINT signal and sends a SIGINT signal to a background process.  
-	The forking function creates a child process and runs the given commands using execvp.  
-	The seriess function executes commands in series by splitting the input string into separate commands at the && symbol, and executing them one after the other.  
-	Parallel function  of code  would allow commands to run in parallel. 

### Example **man man and echo** [Similarly it works for cd command too] and the path which is been shown in the shell is printed by me using cwd .

![image](https://github.com/pg348/Authentication-using-JWT-token/assets/89197939/b026c6a4-7f03-4971-972e-0dfbd73ee5a5)

   ![image](https://github.com/pg348/Authentication-using-JWT-token/assets/89197939/8a094697-ec0f-4c03-9fbb-00995e0fdf00)

### This (&) will run in background :- 
Lets say I write sleep 40 command  and check whether it runs in background or not:- 
Pid has been show and it is running background:- 

![image](https://github.com/pg348/Authentication-using-JWT-token/assets/89197939/6191d52f-ba65-4585-a859-ee12a12afc2c)

### Lets say a program is running in the background and if i hit exit then all the background process will be killed too:- 

![image](https://github.com/pg348/Authentication-using-JWT-token/assets/89197939/2e9894dd-ff64-4409-8d62-6b987cd6f9ca)

### If I hit **ctrl + c** then only the foreground process is terminated and none of the background processes are terminated. 

### SERIES AND PARALLEL EXECUTION.

![image](https://github.com/pg348/Authentication-using-JWT-token/assets/89197939/60f83103-1448-4128-a910-812c5c7d0c81)




