#pragma once
#include <mutex>

class Compte
{
	mutable std::mutex m;
	int solde;
public:
	Compte(int solde = 0) :solde(solde) {}
	void crediter(unsigned int val) {
		m.lock();
		solde += val;
		m.unlock();
	}
	bool debiter(unsigned int val) {
		m.lock();
		bool doit = solde >= (int)val;
		if (doit) {
			solde -= val;
		}
		m.unlock();
		return doit;
	}
	int getSolde() const {
		m.lock();
		int s = solde;
		m.unlock();
		return s;
	}
	// NB : vector exige Copyable, mais mutex ne l’est pas...
	 Compte(const Compte & other) {
		other.m.lock();
		solde = other.solde;
		other.m.unlock();
	 }
};

