#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int wait_till_pid(pid_t pid){
	while(true){
		pid_t termine = wait(nullptr);
		if(termine == pid){
			return pid;
		}
		if(termine == -1){
			return -1;
		}
	}
}
