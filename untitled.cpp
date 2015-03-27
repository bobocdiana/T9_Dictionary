if (this->isNil()) {
      return ;
    }

    // TODO: Afisati parcurgerea inordine a cheilor
    if (! this->left->isNil()) {
        left->findp(k,priority,key);
    }
    
    if (! this->right->isNil()) {
        right->findp(k,priority,key);
    }
    if (k==1){
      priority=this->priority;
      key=this->key;
    }
    k--;
  }  