#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	//unique_lock<mutex> l(mb);
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	if(deb < cred){
		debiteur.lock();
		crediteur.lock();
	}

	if(deb > cred){
		crediteur.lock();
		debiteur.lock();
	}

	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	debiteur.unlock();
	crediteur.unlock();

}
size_t Banque::size() const {
	//unique_lock<mutex> l(mb);
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	//unique_lock<mutex> l(mb);
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		compte.lock();
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	for(const auto & compte : comptes){
		compte.unlock();
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
}
