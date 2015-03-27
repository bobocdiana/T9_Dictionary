#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "rtreap.h"
using namespace::std;

template <typename T> struct trie {
	string code;
	Treap<T> *word;

	void addcode(string code) {
		this->code=code;
		word=new Treap<T>();
	}
	void addtext(string text,int na) {
		struct elem aux;
		aux.text=text;
		aux.na=na;
		word->insert(word,aux,rand() % 1000);
	}
	void display(){
		word->inOrder();
	}
};

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
int main () {
	int n,m,i,nr,k,j,p,l=0,priority;
	string code,input,number;
	struct elem in;
	trie<struct elem>* T9;
	T9=new trie<struct elem>[100000];
	ifstream f("date.in");
	f>>n;
	for (i=1;i<=n;i++) {
		f>>input;
		f>>nr;
		code=identify(input);
		for (j=1;j<=l;j++)
			if (T9[j].code==code) break;
		if (j>l) {
			l++;
			T9[l].addcode(code);
			T9[l].addtext(input,nr);
		}
		else {
			T9[j].addtext(input,nr);
		}
	}
	ofstream g("date.out");
	f>>m;
	for (i=1;i<=m;++i) {
		f>>code;
		p=code.find('*');
		if (p>0) {
			number=code.substr(p+1);
			k=atoi(number.c_str())+1;			
		}
		else k=1;
		code=code.substr(0,p);
		for (j=1;j<=l;++j){
				if (code==T9[j].code)
					break;
		}
		while (T9[j].word->nr_nodes<k) {
			k=k-T9[j].word->nr_nodes;
		} 
		if (k==0) k=1;
		priority=0;
		T9[j].word->findp(k,priority,in);
		g<<in.text<<"\n";
		T9[j].word->erase(T9[j].word,in);
		in.na++;
		T9[j].addtext(in.text,in.na);
	}
	g.close();
	f.close();
	for (i=1;i<=l;i++)
		delete T9[i].word;
	delete [] T9;
return 0;
}