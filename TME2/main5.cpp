#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include <unordered_map>
#include <forward_list>

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

	unordered_map<string, int> map;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		auto val_cpt = map.find(word);
		if(val_cpt != map.end()){
			val_cpt->second++;
		}
		if(val_cpt == map.end()){
			map.insert({word, 1});
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
    cout << "Nombre de mots différents = " << map.size() << endl;
    //cout << "Nombre de mots différents = " << count(h_tab.begin(), h_tab.end()) << endl;


    vector< pair<string, int> > vect;
    for(auto & elem : map){
    	vect.push_back(std::make_pair(elem.first, elem.second));
    }

    std::sort(vect.begin(), vect.end(), [] (const auto & a, const auto & b) { return a.second > b.second ;});

    unordered_map<int,forward_list<string>> freq_map;
    for(auto & elem : vect){
    	auto val = freq_map.find(elem.second);
    	if(val != freq_map.end()){
    		val->second.push_front(elem.first);
   		}
    	if(val == freq_map.end()){
    		forward_list<string> words{elem.first};
    		freq_map.insert({elem.second,words});
    	}
    }

    int n=1;
    auto v = freq_map.find(n);
    cout << "mots de fréquence " << n << " sont :" <<endl;
    for(auto & elem : v->second){
    	cout << elem << endl;
    }




    return 0;
}
