#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>

/*
Question 1/
Question 2/

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
	
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re(R"([^a-zA-Z])");
	while (input >> word) {
		w_new = true;
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace(word, re, "");
		// passe en lowercase
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		// word est maintenant "tout propre"

		//Parcours toutes la table a chaque nouveaux mots pour savoir si il est nouveaux
		for (auto i = liste.begin(); i != liste.end(); i++) {
			if (i->first == word) {
				w_new = false;
				++i->second;
			}
		}

		//Si c'est un nouveau mots.
		if (w_new == true) {

			//On l'ajoute a la liste
			liste.push_back({ word,1 });
		
			
			/*if (n_nrepeat % 1000 == 0) {
				// on affiche un mot "propre" sur 1000
				cout << nombre_lu << ": " << liste.at(n_nrepeat) << endl;
			}*/
			
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
	cout << "And a total of " << nombre_lu << " unrepeated words." << endl;
	cout << "And a total of " << nombre_lu << " unrepeated words." << endl;
	return 0;
}