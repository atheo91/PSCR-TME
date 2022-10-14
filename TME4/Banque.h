#pragma once
#include "Compte.h"
#include <vector>

class Banque {
	typedef std::vector<Compte> comptes_t;
	comptes_t comptes;
public:
	Banque(size_t ncomptes, size_t solde) : comptes(ncomptes, Compte(solde)) {}
	void transfert(size_t deb, size_t cred, unsigned int val) {
		Compte & debiteur = comptes[deb];
		Compte & crediteur = comptes[cred];
		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}
	}
	int solde_compte(size_t compt) {
		return comptes[compt].getSolde();
	}
	size_t size() const {
		return comptes.size();
	}
};