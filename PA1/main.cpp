#include "blockchain.h"
using namespace std;

void main_output(){
  cout << "Welcome to the transaction-chain application....\n";
  cout << "1) Add a transaction to the chain\n";
  cout << "2) Find a transaction witht he name of the receiver or sender.\n";
  cout << "3) Verify and print the chain.\n";
  cout << "Which operation do you want to make? (1, 2, 3):\n";
}

int main(){
  bool repeat_input=true,repeat_bool=true;
  int input;
  int temp_int;
  string temp_string;
  while(repeat_bool){
    while(repeat_input){
      main_output();
      cin >> input;
      if(input == 1 || input == 2 || input == 3){
	repeat_input=false;
      }
      else{
	cout << "Wrong operation!\n";
      }
    }
    repeat_input=true;
    if(input==1){
      Linked_Transaction *Blockchain;
      Blockchain->add_transaction(100, "Trenton", "Matt");
      int money = Blockchain->getHead()->getAmount();
      cout << money;


      
    }
    else if(input==2){
    }
    else if(input==3){
    }
  }

  return 0;
}
