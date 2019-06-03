#include "blockchain.h"



Transaction::Transaction(int amount, string sender, string receiver, Transaction* next1){
    next = next1;
    amount = amount;
    sender = sender;
    receiver = receiver;
    string TnextHash;
    string Hashed;
    srand(time(NULL));
    for(int i = 0; i<63; i++){
        nonce = nonce + char(rand()%26+97);
    }
    if(next1==NULL){
        hash = "";
    }
    else{
        TnextHash = (to_string(next1->amount)) + (next1->sender) + (next1->receiver) + (next1->nonce);
        string Hashed;
        int mySet[5] = {0,1,2,3,4};
        bool found = false;
        while(found){
            picosha2::hash256_hex_string(TnextHash, Hashed);
            found = std::find(mySet, mySet+4, Hashed[-1]) != mySet+4;
        }
        hash = Hashed;
    }
    
}

void Linked_Transaction::add_transaction(int amount, string sender, string receiver){
    Transaction* newHead = new Transaction(amount, sender, receiver, this->head);

}
