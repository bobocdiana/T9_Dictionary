T findp(int k,int &priority) {
    if (k==1) {
      priority=this->priority;
      if (this->left->priority==priority) {
        return this->left->key;
      }
      else {
        return this->key;
      }
    }
    else if (k==2) {
          if (this->priority==this->left->priority) {
            priority=this->priority;
            return this->key;
          }
          else if (!this->left->isNil()) {
                if (!this->right->isNil()) {
                  if (this->left->priority>this->right->priority) {
                    return left->findp(k-1,priority);
                  }
                  else { return right->findp(k-1,priority); }
                }
                else { return left->findp(k-1,priority);}
                }
                else {
                    if (!this->right->isNil()) {
                      return right->findp(k-1,priority);
                    }
                    else { 
                      priority=this->priority;
                      return this->key; 
                    }
                }
    }
    else {
      if (!this->left->isNil()) {
        if (!this->right->isNil()) {
          if (this->left->priority>this->right->priority) {
              return left->findp(k-1,priority);
          }
          else { return right->findp(k-1,priority); }
        }
        else { return left->findp(k-1,priority);}
      }
      else {
            if (!this->right->isNil()) {
              return right->findp(k-1,priority);
            }
            else { 
              priority=this->priority;
              return this->key; 
            }
      }
    }
  }