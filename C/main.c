#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// external symbol that always points to the list of enviornment variables
extern char **environ;

int main(int argc, char **argv) {
	char *args[4] = {"/bin/echo", "Hello", "CS361", 0};
	int child_status = 0;
	int result = 0;
	int bytes_read;
	char buffer[255];
	//Open file and acquire file descriptor
	int file_fd = open("announcement.txt",O_RDONLY);
	
	if(file_fd == -1){
		perror("Failed to open announcement.txt");
		exit(1);
	}
	printf("Parent process ID: %d, FD for announcement.txt: %d \n",getpid(),file_fd);

	result = fork();
        
	//To-Do 1: Change the following condition so that it will execute on fork failure 
	if (0) {
		perror("Fork failed, exiting process without creating child process");
		exit(1);
	}
	//To-Do 2: Change the following condition so that it will be executed by child process only
	if (1) {

		bytes_read = read(file_fd,buffer,16);
		if(bytes_read>0){
			printf("announcement with pid %d and FD %d : %s\n",getpid(),file_fd,buffer);
		}
		else{
			printf("Failed to read announcement with pid %d and FD %d\n",getpid(),file_fd);

		}
		//close(file_fd);
		
		bytes_read = read(file_fd,buffer,16);
		if(bytes_read>0){
			printf("announcement with pid %d and FD %d : %s\n",getpid(),file_fd,buffer);
		}
		else{
			printf("Failed to read announcement with pid %d and FD %d\n",getpid(),file_fd);

		}

		//To-Do 4: Override child process to execute command in args
		
		bytes_read = read(file_fd,buffer,16);
		if(bytes_read>0){
			printf("announcement with pid %d and FD %d : %s\n",getpid(),file_fd,buffer);
		}
		else{
			printf("Failed to read announcement with pid %d and FD %d\n",getpid(),file_fd);

		}
		
		//Error Handling on Failure of To-Do 3
		//perror("execv failed");
		exit(1);
	}
	//To-Do 2.5: Make sure that else part is execute by parent process only
	else {
		//To-Do 3: Make sure that Child process has finished execution 
		if(child_status == 0){	
			bytes_read = read(file_fd,buffer,16);
			if(bytes_read>0){
				printf("announcement with pid %d and FD %d : %s\n",getpid(),file_fd,buffer);
			}
			else{
				printf("Failed to read announcement with pid %d and FD %d\n",getpid(),file_fd);

			}
		}
	}

	printf("Exiting Parent Process\n");
	return 0;
}
