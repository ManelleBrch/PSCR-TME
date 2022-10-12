#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include "HashTable.h"

template <typename iterator>

std::size_t count (iterator begin, iterator end){
	std::size_t cpt = 0;
	while(begin != end){
		cpt++;
		++begin;
	}
	return cpt;
}

template <typename iterator, typename T>
std::size_t count_if_equal (iterator begin, iterator end, const T & val){
	std::size_t cpt = 0;
		while(begin != end){
			if(val == *begin){
				cpt++;
			}
			++begin;
		}
		return cpt;
}



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

	HashTable<string, int> h_tab;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		int * val_cpt = h_tab.get(word);
		if(val_cpt){
			*val_cpt+=1;
		}
		if(!val_cpt){
			h_tab.put(word, 1);
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
    cout << "Nombre de mots différents = " << h_tab.size() << endl;
    //cout << "Nombre de mots différents = " << count(h_tab.begin(), h_tab.end()) << endl;


    vector< pair<string, int> > vect;
    for(HashTable::Entry & elem : h_tab){
    	vect.push_back(std::make_pair(elem.key, elem.value));
    }

    std::sort(vect.begin(), vect.end(), [] (const auto & a, const auto & b) { return a.second > b.second ;});

    size_t i = 0;
    for(HashTable::Entry & elem : h_tab){
    	cout << i <<"eme mot le plus fréquent = " << elem.first << endl;
    	++i;
    	if(i >= 10)
    		break;

    }
    return 0;
}

