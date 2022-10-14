#include "Banque.h"

using namespace std;
using namespace pr;

const int NB_THREAD = 10;

void transactions(Banque & banq){
	for(int k = 0; k < 1000; k++){
		int i = std::rand() % banq.size();
		int j = std::rand() % banq.size();
		int m = 1 + std::rand() % 100;
		int s = std::rand() % 20;
		banq.transfert(i, j, m);
		std::this_thread::sleep_for (std::chrono::milliseconds(s));
	}
}


int main () {

	Banque banq(100, 100);
	vector<thread> threads;


	for(int k = 0; k < NB_THREAD; k++){
		threads.emplace_back(transactions, std::ref(banq));
	}


	for (auto & t : threads) {
		t.join();
	}

	return 0;
}
