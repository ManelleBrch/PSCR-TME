/*
 * HashTable.h
 *
 *  Created on: 30 sept. 2022
 *      Author: 28600291
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include  <vector>
#include <forward_list>

template <typename K, typename V>

class HashTable {

	class Entry{
		const K key;
		const V value;
	};

	typedef std::vector<std::forward_list<Entry>> buckets_t;

	buckets_t buckets;

public:
	HashTable(size_t init = 100){
		buckets.reserve(init);
		for(size_t i = 0; i < init; i++){
			buckets[i] = std::forward_list<Entry>();
		}
	}

	V* get(const K & key){

		size_t h = std::hash<K>()(key);

		auto liste= buckets[h];

		for(liste; liste;){
			if (liste.key == key){
				return liste.key;
			}
		}

		return nullptr;
	}
};

#endif /* HASHTABLE_H_ */
