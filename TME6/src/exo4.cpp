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


int wait_till_pid(pid_t pid, int sec){
	int expire = 0; //si epire = 0 -> temps pas écoulé sinon si = 1 temps écoulé

	struct sigaction act_alrm;
	sigemptyset(&act_alrm.sa_mask);
	act_alrm.sa_handler = [&expire] (int) {
		std::cout<<"Signal SIGCHLD reçu" << std::endl;
		expire = 1;
	};
	act_alrm.sa_flags = 0;
	sigaction(SIGALRM, &act_alrm, nullptr);

	struct sigaction act_chld;
	sigemptyset(&act_chld.sa_mask);
	act_chld.sa_handler = [] (int) { std::cout<<"Signal SIGCHLD reçu" << std::endl; };
	act_chld.sa_flags = 0;
	sigaction(SIGCHLD, &act_chld, nullptr);


	sigset_t sigset;
	sigfillset(&sigset);
	sigdelset(&sigset,SIGALRM || SIGCHLD);

	while(true){
		sigsuspend(&sigset);
		if(expire == 1){ //si temporisateur pas fini et recu signal sigchld
			return -1;
		}
		else{
			pid_t termine = wait(nullptr);
			if(termine == pid){
				alarm(0);
				return pid;
			}
			if(termine == -1){
				return -1;
			}

		}
	}
}


