#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

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

void handlerAlarm(int sig){

}

int wait_till_pid(pid_t pid, int sec){
	static int expire = 0; //si epire = 0 -> temps pas écoulé sinon si = 1 temps écoulé
	signal(SIGALRM, handlerAlarm(SIGALRM));


	sigset_t sigset;
	sigfillset(&set);
	sigdelset(&set,SIGALRM || SIGCHLD);


}
