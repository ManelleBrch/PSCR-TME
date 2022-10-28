#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
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

void combat(pid_t adversaire){
	while(true){
		defense();
		attaque(adversaire);
	}
}

int main(){
	pid_t pid = fork();
	if(pid == 0){
		combat(getppid());
	}
	else{
		combat(pid);
	}
}


