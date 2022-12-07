#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "hash_map.h"


int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	bool mots_vu;
	size_t non_repeter = 0;
	size_t nombre_lu = 0;
	std::vector<pair<string, int>> mots_repeter (1000);
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		

		/*question 2
		mots_vu = false;
		for(unsigned int curseur = 0; curseur < mots_repeter.size(); curseur++){
			//cout << mots_repeter.at(curseur)<<endl;
			if(mots_repeter.at(curseur) == word){
				mots_vu = true;
				break;
			}
		}*/

		mots_vu = false;
		for(unsigned int curseur = 0; curseur < mots_repeter.size(); curseur++){
			//cout << mots_repeter.at(curseur)<<endl;
			if(mots_repeter.at(curseur).first == word){
				mots_repeter.at(curseur).second++;
				mots_vu = true;
				break;
			}
		}

		if(mots_vu == false){
			//cout << "!" <<endl;
			mots_repeter.push_back(make_pair(word, 1));
		    non_repeter++;
		}
		
		if (nombre_lu % 100 == 0){
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl ;
			//<< non_repeter << endl;

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
	cout << "Number of non-repeated words :" << non_repeter << endl;

	int toto = 0, war = 0, peace = 0;


	for(unsigned int curseur = 0; curseur < mots_repeter.size(); curseur++){
		if(mots_repeter.at(curseur).first == "toto"){
			toto = mots_repeter.at(curseur).second;
		}
		if(mots_repeter.at(curseur).first == "war"){
			war = mots_repeter.at(curseur).second;
		}
		if(mots_repeter.at(curseur).first == "peace"){
			peace = mots_repeter.at(curseur).second;
		}
	}

	cout << "Peace : " << peace << " times." << endl;
	cout << "War : " << war << " times." << endl;
	cout << "Toto : " << toto << " times." << endl;
    return 0;
}


