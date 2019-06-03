#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "sha256.h"
#include "picosha2.h"
#include <algorithm>
using namespace std;

class Transaction
{
 public:
  Transaction(int amount1, string sender1, string receiver1, Transaction* next1 = NULL);
  Transaction(){
    next=NULL;
  }
  int getAmount(){
    return amount;
  }
  string getSender(){
    return sender;
  }
  string getReceiver(){
    return receiver;
  }
  string getNonce(){
    return nonce;
  }
  string getHash(){
    return hash;
  }
  Transaction* getNext(){
    return next;
  }

 private:
  Transaction* next;
  int amount;
  string sender;
  string receiver;
  string nonce;
  string hash;
};

class Linked_Transaction{
  public:
    Transaction* getHead(){
      return head;
    }
    void add_transaction(int amount, string sender, string receiver);
    void find(string sender_name);
    bool verify();
    Linked_Transaction(){
        head=NULL;
    }
  private:
    Transaction* head;
};