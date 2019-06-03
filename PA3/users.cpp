#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;
class User{ //User object for the B-tree
    private:
        int perm;
        string name;
        string genre1;
        string genre2;
    public:
        User(int Perm, string Name, string Genre1, string Genre2){ 
            perm=Perm;
            name=Name;
            genre1=Genre1;
            genre2=Genre2;
        };
        User(){
            perm = 0;
            name = "";
            genre1 = "";
            genre2 = "";
        }
        int getPerm(){
            return perm;
        };
        string getName(){
            return name;
        };
        string getGenre1(){
            return genre1;
        };
        string getGenre2(){
            return genre2;
        };
        void printInfo(){
            cout << "Name: " << name << "\n";
            cout << "Perm: " << perm << "\n";
            cout << "Genre1: " << genre1 << "\n";
            cout << "Genre2: " << genre2 << "\n";
        };

};

struct perm_of_friend{
    int perm;
    perm_of_friend* next;
};
class friend_list{
    private:
        perm_of_friend * head;
        perm_of_friend * tail;
    public:
        perm_of_friend* getHead(){
            return head;
        }
        friend_list(){
            head=NULL;
            tail=NULL;
        };
        friend_list(int Perm){
            perm_of_friend* temp = new perm_of_friend;
            temp->perm = Perm;
            temp->next = NULL;
            head=temp;
            tail=temp;
            temp=NULL;
        };
        void add_friend(int Perm){
            perm_of_friend* temp = new perm_of_friend;
            temp->perm = Perm;
            temp->next = NULL;
            if(head==NULL){
                head = temp;
                tail = temp;
                temp = NULL;
            }
            else{
                perm_of_friend* iter = new perm_of_friend;
                iter=head;
                while(iter!=NULL){
                    if(iter->perm==Perm){
                        return;
                    }
                    iter=iter->next;
                }
                tail->next = temp;
                tail = temp;
            }
        };
        void print_all_perms(){
            perm_of_friend* iter = new perm_of_friend;
            iter=head;
            //iter = iter->next;
            while(iter!=NULL){
                cout << iter->perm << " ";
                iter = iter->next;
            }
        };
        vector<int> vectorFriendPerms(){
            vector<int> perms;
            perm_of_friend* iter = new perm_of_friend;
            iter=head;
            iter = iter->next;
            while(iter!=NULL){
                //cout << iter->perm << " ";
                perms.push_back(iter->perm);
                iter = iter->next;
            }
            return perms;
        }
        bool is_user(int Perm){
            if(head->perm==Perm){
                return true;
            }
            else{
                return false;
            }
        }


};

class Friend_Graph{ //list of linked lists
    public:
        vector<friend_list> vector_friend_list; //vector of linked list
        Friend_Graph(){

        }
        void add_user(int Perm, string Name, string Genre1, string Genre2, vector<int> friend_perms){
            friend_list new_friend(Perm);
            int f_perm;
            for(vector<int>::iterator it= friend_perms.begin();it!= friend_perms.end();++it){
                //it->print_all_perms();
                f_perm = *it;
                //                          still need to add new friend to everyone else's friend list
                update_friends(Perm,f_perm);
                new_friend.add_friend(f_perm);
            }            
            add_friend_list(new_friend);
        }
        void add_friend_list(friend_list user_friend_list){
            vector_friend_list.push_back(user_friend_list);
        };
        void display_all(){
            for(vector<friend_list>::iterator it= vector_friend_list.begin();it!= vector_friend_list.end();++it){
                it->print_all_perms();
                cout << "\n";
            }
        }
        int find_index_of_perm(int Perm){ //returns index of vector for a given perm, -1 if not found
            for(std::vector<friend_list>::size_type i = 0; i != vector_friend_list.size(); i++) {
                if(vector_friend_list[i].is_user(Perm)){
                    return i;
                }
            }
            return -1;
        }
        void update_friends(int new_friend_perm, int to_update_friend_perm){
            for(vector<friend_list>::iterator it= vector_friend_list.begin();it!= vector_friend_list.end();++it){ //iterate through friend graph, getting heads
                if(it->getHead()->perm == to_update_friend_perm){
                    it->add_friend(new_friend_perm);
                    return;
                }          
            }          
        }




};