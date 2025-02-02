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

public:
	class Entry{
	public:
		const K key;
		V value;

		Entry(K k, V v) : key(k), value(v){}
	};

private:

	typedef std::vector<std::forward_list<Entry>> buckets_t;

	buckets_t buckets;
	size_t taille;

public:
	class iterator{
		buckets_t & buck;
		typename buckets_t::iterator vit;
		typename std::forward_list<Entry>::iterator lit;

	public:
		iterator(const buckets_t & buckets, const typename buckets_t::iterator vit, typename std::forward_list<Entry>::iterator lit) : buck(buckets), vit(vit), lit(lit){}

		iterator & operator++(){
			++lit;

			if(lit == nullptr){
				++vit;
				while(vit.begin() == nullptr && vit != buck.end()){
					++vit;
				}


				if(vit != buck.end()){
					lit = vit.begin();
				}
			}

			return *this;
		}

		bool operator!=(const iterator &other){

			if(vit != other.vit || lit != other.lit){
				return true;
			}

			return false;
		}

		Entry & operator*(){
			return *lit;
		}

		iterator begin(){

			while(vit.begin() == nullptr && vit != buck.end()){
				++vit;
			}

			if(vit != buckets.end){
				return iterator(buckets, vit, vit.begin());
			}

			return iterator(buckets, vit, nullptr);
		}

		iterator end(){
			return iterator(buckets, buckets.end(), nullptr);
		}


	};



public:
	HashTable(size_t init = 100):buckets(init){
//		buckets.reserve(init);
//		for(size_t i = 0; i < init; i++){
//			buckets.push_back(std::forward_list<Entry>());
		//ou buckets.emplace_back();
//		}
		taille = 0;
	}


	V* get(const K & key){

		size_t h = std::hash<K>()(key);
		size_t indice = h % buckets.size();

		for(Entry & e : buckets[indice]){
			if (e.key == key){
				return & e.value;
			}
		}

		return nullptr;
	}

	bool put (const K & key, const V & value){
		size_t h = std::hash<K>()(key);
		size_t indice = h % buckets.size();

		for(Entry & e : buckets[indice]){
			if(e.key == key){
				e.value = value;
				return true;
			}
		}
		Entry ajout(key,value);
		buckets[indice].push_front(ajout);
		taille++;
		return false;
	}

	 size_t size() const{
		 return taille;
	 }

	 void grow(){
		 HashTable new_tab(buckets.size()*2);

		 for(buckets_t & liste : buckets){
			 for(Entry & e : liste){
				new_tab.put(e.key, e.value);
			 }
		 }
		 buckets = new_tab.buckets;
	 }
};

#endif /* HASHTABLE_H_ */
