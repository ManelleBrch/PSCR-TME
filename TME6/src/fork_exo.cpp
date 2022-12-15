#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


using namespace std;

int main0 () {
	int nbfils = 0;
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	pid_t pid;
	int j = N;
	for (int i=1; i<=N && j==N ; i++ ) {
		if((pid =fork()) == 0){
			nbfils =0;
			std::cout << " i:j " << i << ":" << j << std::endl;
			for (int k=1; k<=i && j==N ; k++) {
				if ((pid =fork()) == 0) {
					nbfils = 0;
					j=0;
					std::cout << " k:j " << k << ":" << j << std::endl;
				}else{
					nbfils++;

				}
			}
		}
		else{
			nbfils++;
			break;
		}
	}

	if(j == N){
		for(int m = 0; m < nbfils; m++){
			cout << "J'attend mon fils" << endl;
			wait(nullptr);
		}
	}
	return 0;
}
