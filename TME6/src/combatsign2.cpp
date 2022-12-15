#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "rsleep.h"

using namespace std;

int vie = 3;
int nbattaque = 0;
int nbdefense = 0;

void handler(int sig){
	if(sig == SIGINT){
		vie --;
		cout << "Nombre vie restant de " << getpid() << " = " << vie <<endl;
		if(vie == 0){
			cout << "Le processus " << getpid() << " se termine" << endl;
			cout << "Nb attaques " << getpid() << " = " << nbattaque << endl;
			cout << "Nb defense " << getpid() << " = " << nbdefense << endl;
			exit(1);
		}
	}
}

void handlerFils(int sig){
	if (sig == SIGINT){
		cout << "Coup paré" << endl;
	}
}



void attaque (pid_t adversaire){
	nbattaque ++;
	//cout << getpid() << " attaque" << endl;
	signal(SIGINT, handler);
	if (kill(adversaire, SIGINT) == -1){
		cout << "Mon adversaire est mort" << endl;
		cout << "Nb attaques " << getpid() << " = " << nbattaque << endl;
		cout << "Nb defense " << getpid() << " = " << nbdefense << endl;
		exit(0);
	}
	randsleep();

}

void defense(){
	nbdefense ++;
	signal(SIGINT, SIG_IGN);
	randsleep();

}

void defenseFils(){
	nbdefense ++;

	struct sigaction action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = handlerFils;

	sigaction(SIGINT, &action, NULL);

	sigset_t sig;
	sigfillset(&sig);
	sigprocmask(SIG_SETMASK, &sig, NULL);

	randsleep();

	sigfillset(&sig);
	sigdelset(&sig, SIGINT);
	sigsuspend(&sig);


}

void combat(pid_t adversaire){
	while(true){
		defense();
		attaque(adversaire);
	}
}

void combatFils(pid_t adversaire){
	while(true){
		defenseFils();
		attaque(adversaire);
	}
}


int main2(){
	pid_t pid = fork();
	if(pid == 0){
		combatFils((int)getppid());
	}
	else{
		combat(pid);
	}

	return 0;
}

