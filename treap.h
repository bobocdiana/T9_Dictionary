#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

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
    // TODO: Completati functia de cautare
    if (this->key==key) {
        return true;
    }
    else if (key<this->key) {
       return left->find(key);
    }
    else {
        return right->find(key);
    }   

//    return false;
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
    // TODO: Completati rotirea dreapta
    Treap<T>* aux;
    aux=fatherPointer->left;
    fatherPointer->left=aux->right;
    aux->right=fatherPointer;
    fatherPointer=aux;
    

    // TODO: Recalculati dimensiunea subarborilor
    fatherPointer->right->nr_nodes=fatherPointer->right->right->nr_nodes+fatherPointer->right->left->nr_nodes+1;
    cout<<fatherPointer->right->nr_nodes<<'*';
    fatherPointer->nr_nodes=fatherPointer->right->nr_nodes+fatherPointer->left->nr_nodes+1;
    cout<<fatherPointer->nr_nodes<<endl;
  }

  void rotateLeft(Treap<T> *&fatherPointer) {
    // TODO: Completati rotirea stanga
    Treap<T>* aux;
    aux=fatherPointer->right;
    fatherPointer->right=aux->left;
    aux->left=fatherPointer;
    fatherPointer=aux;

    // TODO: Recalculati dimensiunea subarborilor
    fatherPointer->left->nr_nodes=fatherPointer->left->right->nr_nodes+fatherPointer->left->left->nr_nodes+1;
    cout<<fatherPointer->left->nr_nodes<<'*';
    fatherPointer->nr_nodes=fatherPointer->right->nr_nodes+fatherPointer->left->nr_nodes+1;
    cout<<fatherPointer->nr_nodes<<endl;

  }

  void insert(Treap<T> *&fatherPointer, T key, int priority) {
    if (this->isNil()) {
      this->addData(key, priority);   
      return ;
    }

    // TODO: Completati inserarea
    if (key < this->key) {
        left->insert(this->left,key,priority);
        //this->left->nr_nodes++;
    }   else {
            right->insert(this->right,key,priority);
          //  this->right->nr_nodes++;
        }

    // TODO: Incrementati dimensiunea subraborelui curenti
    fatherPointer->nr_nodes++;
    if (this->left->priority > this->priority) {
        rotateRight(fatherPointer);
    }   else if (this->right->priority > this->priority) {
           rotateLeft(fatherPointer);
        }
  }

  void inOrder() {
    if (this->isNil()) {
      return ;
    }

    // TODO: Afisati parcurgerea inordine a cheilor
    if (! this->left->isNil()) {
        left->inOrder();
    }
    std::cout<<this->key<<' '<<this->nr_nodes<<' '<<this->priority<<endl;
    if (! this->right->isNil()) {
        right->inOrder();
    }        
  }

  void erase(Treap<T> *&fatherPointer, T key) {
    if (this->isNil()) {
      return ;
    }

    // TODO: Decrementati dimensiunea subarborelui curent
    fatherPointer->nr_nodes--;
    if (key < fatherPointer->key) {
        erase(fatherPointer->left,key);

    }   else if (key > fatherPointer->key) {
           erase(fatherPointer->right,key);
        } else if (fatherPointer->left->isNil() && fatherPointer->right->isNil()) {
                return fatherPointer->delData();
            } else if (fatherPointer->left->priority > fatherPointer->right->priority) {
                    cout<<"drepata"<<endl;
                    rotateRight(fatherPointer);
                    fatherPointer->inOrder();
                    erase(fatherPointer,key);
                    
                } else {
                        cout<<"stanga"<<endl;
                        rotateLeft(fatherPointer);
                        fatherPointer->inOrder();
                        erase(fatherPointer,key);

                    }
    }
  

  void preOrder(int level = 0) {
    if (this->isNil()) {
      return ;
    }

//    for (int i = 0; i < level; i++) {
//      cout << ' ';
//    }

    // TODO: Afisati parcurgerea preordine a prioritatilor
    std::cout<<this->priority<<' ';
    if (!this->left->isNil()){
        left->preOrder(level+1);
    }
//    std::cout<<this->priority<<' ';
    if (!this->right->isNil()){
        right->preOrder(level+1);
    }       
  }

  T findK(int k) {
    // TODO: Pe baza nr_nodes determinati cea de-a k cheie in ordinea sortarii

    int nodes=this->left->nr_nodes;
    if (nodes+1==k) {
        return this->key;
    }
    else if (k<nodes+1) {
        return left->findK(k);
    }
    else return right->findK(k-nodes-1);    
  }         

  void duplicates(Treap<T> *&fatherPointer,Treap<T> *&taux,int &k,T key,int priority) {
      if (fatherPointer->priority==fatherPointer->left->priority) {
        duplicates(fatherPointer->left,taux,k,key,priority);
        if (k>1) {
          k--;
          taux->insert(taux,fatherPointer->key,fatherPointer->priority); 
          fatherPointer->erase(fatherPointer,fatherPointer->key); 
        }    
        else if (k==1) {
          key=fatherPointer->key;
          priority=fatherPointer->priority;
        }
      }
      else {
         taux->insert(taux,fatherPointer->key,fatherPointer->priority); 
         key=fatherPointer->key;
         priority=fatherPointer->priority;
         fatherPointer->erase(fatherPointer,fatherPointer->key); 
         k--;     
      }
  }

  T findp(Treap<T> *&fatherPointer,int k,int &priority) {
    Treap<T> *aux=new Treap<T>;
    T key; 
     fatherPointer->inOrder();
    while (k>1) {
      if (!fatherPointer->left->isNil() && fatherPointer->left->priority==fatherPointer->priority ) {
        duplicates(fatherPointer,aux,k,key,priority);
      }
      else {
      aux->insert(aux,fatherPointer->key,fatherPointer->priority);
      fatherPointer->erase(fatherPointer,fatherPointer->key);
      k--;
      cout<<k<<endl;
      cout<<"In vechiul treap"<<endl;
      fatherPointer->inOrder();
      cout<<endl;
      cout<<"In nodul treap"<<endl;
      aux->inOrder();
      cout<<endl;
      }
    }
    /*if (k==2 && (fatherPointer->left->isNil() || fatherPointer->right->isNil())) {
      aux->insert(aux,fatherPointer->key,fatherPointer->priority);
      fatherPointer->erase(fatherPointer,fatherPointer->key);
      k--;
      cout<<k<<endl;
      cout<<"In vechiul treap"<<endl;
      fatherPointer->inOrder();
      cout<<endl;
      cout<<"In nodul treap"<<endl;
      aux->inOrder();
      cout<<endl;
    }*/
      cout<<"Noul cap este:"<<fatherPointer->key<<endl;
    /*if (k==2 && ! fatherPointer->left->isNil())  {
      while (k>1&&fatherPointer->left->left->priority==fatherPointer->left->priority) {
        aux->insert(aux,fatherPointer->key,fatherPointer->priority);
        fatherPointer->erase(fatherPointer,fatherPointer->key);
        k--;
        cout<<k<<endl;
      cout<<"In vechiul treap"<<endl;
      fatherPointer->inOrder();
      cout<<endl;
      cout<<"In nodul treap"<<endl;
      aux->inOrder();
      cout<<endl;
      }
    }*/
    if (k==2) {
      if (fatherPointer->left->priority==fatherPointer->priority) {
          key=fatherPointer->key;
          priority=fatherPointer->priority;
      }
      else if (fatherPointer->priority==fatherPointer->right->priority) {
              key=fatherPointer->right->key;
              priority=fatherPointer->right->priority;
      }
      else if (fatherPointer->right->priority>=fatherPointer->left->priority) {
                key=fatherPointer->right->key;
                priority=fatherPointer->right->priority;
      }
      else {
            key=fatherPointer->left->key;
            priority=fatherPointer->left->priority; 
      }
    }
    else if (k==1) {
      if (fatherPointer->priority==fatherPointer->left->priority) {
          key=fatherPointer->left->key;
      }
      else { key=fatherPointer->key;}
      priority=fatherPointer->priority;
    }
    while (!aux->isNil()) {
      fatherPointer->insert(fatherPointer,aux->key,aux->priority);
      aux->erase(aux,aux->key);
    }
    delete aux;
    cout<<"Inainte sa iasa din find:"<<endl;
    fatherPointer->inOrder();
    cout<<endl;
    return key;
  }
};
