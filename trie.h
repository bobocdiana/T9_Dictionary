#include <iostream>
#include <string>
#include <stdlib.h>
#include "rtreap.h"
using namespace::std;

template <typename T> struct Trie {
	Trie<T> **son; // vector de pointeri ce retine cei 10 fii ai nodului radacina
	Treap<T> *key; // treap ce retine toate combinatiile de text pentru un cod
	bool nil; // variabila ce retine daca a fost sau nu alocat un treap ptr nodul curent

	Trie(): nil(true) {}

//	Functie ce aloca pentru nodul curent vectorul sau de fii,treap-ul corespunzator
//  si anunta prin variabila nil ca acest nod retine un treap	
	void initialise () {
		son= new Trie<T>* [10];
		for(int i =0;i<=9;i++){
			son[i]=new Trie<T>;
			son[i]->son=NULL;
		}
		key=new Treap<T>();
		nil=false;
	}

// Functie de inserare a unui text in treap-ul corespunzator nodului ce reprezinta
//	codul numeric al  textului
	void insert (Trie<T> *&fatherPointer,T tkey,string code){
		if (son==NULL){
			initialise();
		}
		if (code.size()==0) {
			fatherPointer->key->insert(fatherPointer->key,tkey,rand()%1000);
		}
		else {
			fatherPointer->son[(int)code[0]-48]->insert(fatherPointer->son[(int)code[0]-48],
			                                            tkey,code.substr(1));
		}
	}

//	Functie de cautare a unui cod in trie si care returneaza pointer la nodul
//  final ce reprezinta  codul respectiv sau NULL daca acesta nu este in trie
	Trie<T>* lookup (Trie<T> *&fatherPointer,string code) {
		if (code.size()==0) {
			if (nil) {
				return NULL;
			}
			else return fatherPointer;
		}
		else {
			if(son){
				return son[(int)code[0]-48]->lookup(fatherPointer->son[(int)code[0]-48],
				                                    code.substr(1));
			}
			else{
				return NULL;
			}
		}
	}

//	Functie ce dezaloca trie-ul si implicit treap-ul corespunzator fiecarui nod ce 
//	reprezinta un cod	
	void deallocate() {
		if (this!=NULL){
			if (son){
				for (int i=0;i<=9;i++){
					if (son[i])
					{
						this->son[i]->deallocate();
					}
				}
				delete [] son;
				if (key){
					key->delTreap(key);
					delete key;
				}

			}
			delete this;
		} 		
	}

};
