#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include  <vector>

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	vector< pair<string, int> > vect;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		size_t i=0;
		for(i; i < vect.size(); i++){
			if (word == vect[i].first){ //vect[i].first pour recupérer la string
				vect[i].second ++; //vect[i].seconde pour récupérer le int
				break;
			}
		}
		if(i==vect.size()){
			vect.push_back(std::make_pair(word, 1));
		}


		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    cout << "Nombre de mots différents = " << vect.size() << endl;

    size_t i = 0;
    for(i; i < vect.size(); i++){
    	if(vect[i].first == "war"){
    		cout << "Nombre de mots war = " << vect[i].second << endl;
    	}
    	if(vect[i].first == "peace"){
    	    cout << "Nombre de mots peace = " << vect[i].second << endl;
    	}
    	if(vect[i].first == "toto"){
    		cout << "Nombre de mots toto = " << vect[i].second << endl;
    	}

    }
    return 0;
}

