#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
using namespace::std;

//Functie care identifica codul corespunzator unui text dat
string identify(string &text) {
	int l=text.length();
	int i;
	string code;
	code.resize(l);
	for (i=0;i<l;i++) {
		if (strchr("abc",text[i]))
			code[i]='2';
		else if (strchr("def",text[i]))
				code[i]='3';
			else if (strchr("ghi",text[i]))
					code[i]='4';
				else if (strchr("jkl",text[i]))
						code[i]='5';
					else if (strchr("mno",text[i]))
							code[i]='6';
						else if (strchr("pqrs",text[i]))
								code[i]='7';
							else if (strchr("tuv",text[i]))
									code[i]='8';
								else code[i]='9';

	}
return code;	
}

int main() {
	Trie<struct elem> *T9 = new Trie<struct elem>();
	Trie<struct elem> *word;
	Trie<struct elem> *point;
	int n,m,i,k,p,priority;
	string code,number;
	struct elem in;
	char *c;
	FILE *f;

	f=fopen("date.in","r");
	fscanf(f,"%d",&n);
	c=new char[30];
	//se initializeaza primul nivel de fii ai nodului radacina al trie-ului
/*	T9->initialise(); 
	
	
	fscanf(f,"%s",c);
	in.text=c;
	fscanf(f,"%d",&(in.na));

	//se identifica codul corespunzator textului dat ca input si se insereaza 
	// in trie perechea cod-text
	code=identify(in.text);
	T9->insert(T9,in,code);
*/	
	for (i=1;i<=n;i++) {
		fscanf(f,"%s",c);
		in.text=c;
		fscanf(f,"%d",&(in.na));
		code=identify(in.text);
		//se cauta codul code in trie iar in cazul in care exista se adauga
		//in treap-ul corespunzator noul text
		//daca nu exista codul,se initializeaza treap-ul si vectorul de fii corespunzator
		point=T9->lookup(T9,code);
		if (point==NULL) {
			T9->insert(T9,in,code);
		}
		else {
			point->key->insert(point->key,in,rand()%1000);
		}
	}
	FILE *g;
	g=fopen("date.out","w");
	fscanf(f,"%d",&m);
	for (i=1;i<=m;i++) {
		fscanf(f,"%s",c);
		code=c;
		//Se identifica numarul de aparitii cerut pentru codul code,care se retine in k
		p=code.find('*');
		if (p>0) {
			number=code.substr(p+1);
			k=atoi(number.c_str())+1;			
		}
		else k=1;
		code=code.substr(0,p);
		//se cauta codul in trie si se retine pointerul nodului corespunzator in word
		word=T9->lookup(T9,code);
		if (word->key!=NULL) {
			//se modifica valoarea lui k in functie de nr de noduri existent in treap-ul
			//corespunzator codului cautat
			if (k%word->key->nr_nodes==0)
			{
				k=word->key->nr_nodes;
			}
			else{
				k%=word->key->nr_nodes; 
				}
			if (k==0) k=1;
			priority=0;
			//se cauta cheia cu numarul de aparitii k in treap si i se retine prioritatea random
			//in priority
			word->key->findp(k,priority,in);
			fprintf(g,"%s\n",in.text.c_str());
			//se sterge din treap cheia cu prioritatea priority
			word->key->erase(word->key,in);
			in.na++; //se incrementeaza numarul de aparitii corespunzator cheii gasite
			// se reinsereaza cheia cu numarul de aparitii modificat in treap
			word->key->insert(word->key,in,rand()%1000);
		}
	}
	fclose(g);
	fclose(f);
	//se elibereaza memoria pentru trie
	T9->deallocate();
	delete [] c;
return 0;	
}
