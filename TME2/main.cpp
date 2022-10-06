#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "Hash_Map.h"

/*
Question 1/566193 mots totale
Question 2/20333 mots différents
Question 3/0 toto, 114 peace, 298 war.
Question 4/ Tros complexe. On pourrais faire des table de Hash
*/

int main() {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	vector<pair<string, int>> liste;
	size_t nombre_lu = 0;
	size_t n_nrepeat = 0;
	bool w_new = true;
	int c_war = 0, c_peace = 0, c_toto = 0;

	
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re(R"([^a-zA-Z])");


	while (input >> word) {
		
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace(word, re, "");
		// passe en lowercase
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		// word est maintenant "tout propre"


		w_new = true;
		//Parcours toutes la table a chaque nouveaux mots pour savoir si il est nouveaux
		for (auto i = liste.begin(); i != liste.end() && w_new != false; i++) {
			if (i->first == word) {
				w_new = false;
				++i->second;
			}
		}

		if (word == "toto") {
			++c_toto;
		}
		else if (word == "war") {
			++c_war;
		}
		else if (word == "peace") {
			++c_peace;
		}

		//Si c'est un nouveau mots.
		if (w_new == true) {
			//On l'ajoute a la liste
			liste.push_back({ word,1 });		
			if (n_nrepeat % 1000 == 0) {
				// on affiche un mot "propre" sur 1000
				cout << nombre_lu << ": " << liste.at(n_nrepeat).first << endl;
			}
			n_nrepeat++;
		}
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
	cout << "Parsing took "
		<< duration_cast<milliseconds>(end - start).count()
		<< "ms.\n";

	cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "And a total of " << n_nrepeat << " unrepeated words." << endl;
	cout << "Number of toto: " << c_toto <<  endl;
	cout << "Number of peace:" << c_peace << endl;
	cout << "Number of war: " << c_war << endl;
	
	return 0;
}