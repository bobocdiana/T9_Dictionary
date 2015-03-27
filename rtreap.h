#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct elem {
  string text;
  int na;
};

template <typename T> struct Treap {
  T key;
  int priority;
  Treap<T> *left, *right;
  bool nil;

  // Pentru a rezolva problema 3 trebuie ca fiecare nod sa retina numarul de
  // noduri din subarborle sau
  int nr_nodes;

  // Creaza un nod nil
  Treap() : priority(-1), left(NULL), right(NULL), nil(true), nr_nodes(0) {}

  // Adaugam date, transformand un nod nil intr-un nod obisnuit
  void addData(T key, int priority) {
    this->nil = false;
    this->key = key;
    this->priority = priority;
    this->nr_nodes = 1;
    this->left = new Treap();
    this->right = new Treap();
  }

  // Stergem un nod obisnuit, transformandu-l intr-unul nil
  void delData() {
    this->nil = true;
    this->priority = -1;
    delete this->left;
    delete this->right;
    this->nr_nodes = 0;
  }

  bool isNil() {
    return this->nil;
  }

  bool find(T key) {
    if (this->isNil()) {
      return false;
    }
    if (this->key==key) {
        return true;
    }
    else if (key<this->key) {
       return left->find(key);
    }
    else {
        return right->find(key);
    }   
  }

  /* Atat insert cat si erase au nevoie de o referinta catre un fatherPointer,
   adica de pointerul left sau right din parinte care pointeaza catre obiectul
   curent. De ce?
   Sa presupunem ca avem urmatoarea configuratie:
                 a
                / \
               b   c
                  / \
                 d   e

   si facem o rotatie dreapta in nodul c. Configuratia care rezulta este:
                 a
                / \
               b   d
                    \
                     c
                      \
                       e

   Dupa cum se poat vedea pointerul right a lui a trebuie sa pointeze in urma
   rotirii catre d. De aceea, o referinta a acelui pointer trebuie pasata catre
   fiul care reprezinta acel pointer, pentru ca nodul a sa vada eventualele
   inlocuiri ce pot aparea in urma unor rotiri.
   Atentie! - desi s-ar putea sa spunem ca putem folosi pointerul this pentru
   a rezolva problema de mai sus, acest lucru este gresit, deoarece this este un
   pointer constant, asupra caruia nu se pot face asignari de forma this = ...
  */

  void rotateRight(Treap<T> *&fatherPointer) {
    Treap<T>* aux;
    aux=fatherPointer->left;
    fatherPointer->left=aux->right;
    aux->right=fatherPointer;
    fatherPointer=aux;
    

    // Recalcularea dimensiunii subarborilor
    fatherPointer->right->nr_nodes=fatherPointer->right->right->nr_nodes +
                                    fatherPointer->right->left->nr_nodes+1;
    fatherPointer->nr_nodes=fatherPointer->right->nr_nodes +
                            fatherPointer->left->nr_nodes+1;
  }

  void rotateLeft(Treap<T> *&fatherPointer) {
    Treap<T>* aux;
    aux=fatherPointer->right;
    fatherPointer->right=aux->left;
    aux->left=fatherPointer;
    fatherPointer=aux;

    // Recalcularea dimensiunii subarborilor
    fatherPointer->left->nr_nodes=fatherPointer->left->right->nr_nodes +
                                    fatherPointer->left->left->nr_nodes+1;
    fatherPointer->nr_nodes=fatherPointer->right->nr_nodes +
                            fatherPointer->left->nr_nodes+1;

  }

  // Functie de inserare a unei chei in treap pe baza prioritatii random
  void insert(Treap<T> *&fatherPointer, T key, int priority) {
    if (fatherPointer->isNil()) {
      fatherPointer->addData(key, priority);   
      return ;
    }
    else{
      if (key.na < fatherPointer->key.na) {
          insert(fatherPointer->left,key,priority);
      }   
      else if (key.na > fatherPointer->key.na) {
              insert(fatherPointer->right,key,priority);
          }
          else {
            if (key.text < fatherPointer->key.text) {
              insert(fatherPointer->right,key,priority);
            }
            else {
              insert(fatherPointer->left,key,priority);
            }
          }
          fatherPointer->nr_nodes++;   // incrementarea dimensiunii subarborilor
      
      if (fatherPointer->left->priority > fatherPointer->priority) {
          rotateRight(fatherPointer);
      }   else if (fatherPointer->right->priority > fatherPointer->priority ) {
             rotateLeft(fatherPointer);
          }
    }
  }

  // Afisare in inordine a treap-ului
  void inOrder() {
    if (this->isNil()) {
      return ;
    }
    if (! this->left->isNil()) {
        left->inOrder();
    }
    cout<<key.text<<" "<<nr_nodes<<endl;
    if (! this->right->isNil()) {
        right->inOrder();
    }        
  }

  //Functie de stergere a unei chei din treap si de rebalansare a acestuia
  void erase(Treap<T> *&fatherPointer, T key) {
    if (fatherPointer->isNil()) {
      return ;
    }
    fatherPointer->nr_nodes--;
    if (key.na < fatherPointer->key.na) {
        erase(fatherPointer->left,key);
    } 
    else if (key.na > fatherPointer->key.na) {
           erase(fatherPointer->right,key);
    } 
    else {
      if (key.text < fatherPointer->key.text) {
            erase(fatherPointer->right,key);
      }
      else if (key.text > fatherPointer->key.text) {
        erase(fatherPointer->left,key);
      }
      else if (fatherPointer->left->isNil() && fatherPointer->right->isNil()) {
        return fatherPointer->delData();
      } 
      else if (fatherPointer->left->priority > fatherPointer->right->priority) {
          rotateRight(fatherPointer);
          erase(fatherPointer,key);
                    
      } else {
              rotateLeft(fatherPointer);
              erase(fatherPointer,key);
          }
    }
  }

  //Functie de afisare in preordine a prioritatilor
  void preOrder(int level = 0) {
    if (this->isNil()) {
      return ;
    }
    std::cout<<this->priority<<' ';
    if (!this->left->isNil()){
        left->preOrder(level+1);
    }
    if (!this->right->isNil()){
        right->preOrder(level+1);
    }       
  }

  T findK(int k) {
    // Pe baza nr_nodes se determina cea de-a k cheie in ordinea sortarii

    int nodes=this->left->nr_nodes;
    if (nodes+1==k) {
        return this->key;
    }
    else if (k<nodes+1) {
        return left->findK(k);
    }
    else return right->findK(k-nodes-1);    
  }         

// Functie ce cauta a k-a cheie in treap,pornind de la dreapta la stanga,
// in functie de criteriul de inserare al unei chei in acest treap
  void findp(int &k,int &priority,struct elem &key) {
    int nodes=this->right->nr_nodes;
    if (nodes+1==k){
      priority=this->priority;
      key=this->key;
    }
    else{
      if (k<nodes+1){
        right->findp(k,priority,key);
      }
      else {
        k=k-nodes-1;
        left->findp(k,priority,key);
      }
    }
  }

// Functie de eliberare a memoriei alocata treap-ului
  void delTreap (Treap<T> *&fatherPointer) {
    while (! fatherPointer->isNil()) {
      fatherPointer->erase(fatherPointer,fatherPointer->key);
    }
  }    
};
