#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <vector>
#include <sstream>
#include <assert.h>
#include "BTree.h"
using namespace std;


/* #region BT_PointyBoi */
BT_PointyBoi::BT_PointyBoi(){
    type = EMPTY;
}
BT_PointyBoi::BT_PointyBoi(BT_Node* Node){
    type = NODE;
    node = Node;
}
BT_PointyBoi::BT_PointyBoi(BT_Leaf* Leaf){
    type = LEAF;
    leaf = Leaf;
}
void BT_PointyBoi::makeEmptyLeaf(){
    assert(type==EMPTY);
    type = LEAF;
    BT_Leaf* newLeaf = new BT_Leaf;
    leaf = newLeaf;

}
void BT_PointyBoi::makeEmptyNode(){
    assert(type==EMPTY);
    type = NODE;
    BT_Node* newNode = new BT_Node;
    node = newNode;
}
BT_PointyBoi BT_PointyBoi::addUser(User* user, int index){
    switch(type){
        case(BT_PointyBoi::EMPTY):{
            cout << "WARNING: Adding to an empty pointy boi\n";
        }
        case(BT_PointyBoi::NODE):{
            BT_Node* returnedNode = node->addUser(user,index);
            if(returnedNode==nullptr){
                return BT_PointyBoi();
            }
            else{
                return BT_PointyBoi(returnedNode);
            }
        }
        case(BT_PointyBoi::LEAF):{
            return BT_PointyBoi(leaf->addUserLeaf(user,index));
        }        
    }
    return BT_PointyBoi();
}


void BT_PointyBoi::deleteBoi(){
    switch(type){
        case EMPTY:{
            break;
        }
        case NODE:{
            if(node){
                delete node;
                node = nullptr;
            }
            break;
        }
        case LEAF:{
            if(leaf){
                delete leaf;
                leaf = nullptr;
            }
            break;
        }
    }
}
int BT_PointyBoi::getMinPerm(){
    assert(type!=EMPTY);
    switch(type){
        case EMPTY:{
            return -1;
        }
        case NODE:{
            return node->getMinPerm();
        }
        case LEAF:{
            return leaf->getMinPerm();
        }
    }
    return -1; 
}
void BT_PointyBoi::print(){
    switch(type){
        case EMPTY:{
            cout << "EMPTY\n";
            break;
        }
        case NODE:{
            cout << "Type = NODE, ";
            node->print();
            break;
        }
        case LEAF:{
            cout << "Type = LEAF, ";
            leaf->print();
            break;
        }
    } 
}

bool BT_PointyBoi::find(int Perm){
    switch(type){
        case BT_PointyBoi::EMPTY:{
            cout << "ERROR: Doing a find on an empty PointyBoi.\n";
            break;
        }
        case BT_PointyBoi::NODE:{
            return node->find(Perm);
        }
        case BT_PointyBoi::LEAF:{
            return leaf->find(Perm);
        }
    }
    return false;
}

BT_Leaf* BT_PointyBoi::getLeaf(int Perm){
    switch(type){
        case BT_PointyBoi::EMPTY:{
            cout << "ERROR: Trying to get leaf on an empty PointyBoi.\n";
        }
        case BT_PointyBoi::NODE:{
            return node->getLeaf(Perm);
        }
        case BT_PointyBoi::LEAF:{
            return leaf->getLeaf(Perm);
        }
    }
    return nullptr;
}

/* #endregion */

/* #region BT_Node */
BT_Node::BT_Node(){
    numberPerms = 0;
    numberGorls=0;
    daddy=nullptr;
};
int BT_Node::getMinPerm(){
    return babyGorls[0].getMinPerm();
};
void BT_Node::print(){
    cout << "Number of perms keys: "<< numberPerms << ", Perm keys are: ";
    for(int i = 0; i< numberPerms;i++){
        cout << permArray[i] << " ";
    }
    cout << "\n";
    for(int i=0; i<numberGorls;i++){
        babyGorls[i].print();
    }
}

bool BT_Node::find(int Perm){
    if(numberGorls==0){
        return false;
    }
    else{
        int i=0;//index for child to go to
        while(i<numberPerms && Perm>=permArray[i]){
            i++;
        }
        return babyGorls[i].find(Perm);
        
    }
}
BT_Leaf* BT_Node::getLeaf(int Perm){
    if(numberGorls==0){
        return nullptr;
    }
    else{
        int i=0;//index for child to go to
        while(i<numberPerms && Perm>=permArray[i]){
            i++;
        }
        return babyGorls[i].getLeaf(Perm);
        
    }
}


void BT_Node::addBabyGorl(BT_PointyBoi pointer){ //this is to add a pointer to the children, not an insert user function
    if(numberGorls!=4){ //BT_Node not full
        int i=numberGorls;
        while(i>0 && pointer.getMinPerm()<=babyGorls[i-1].getMinPerm()){
            babyGorls[i] = babyGorls[i-1];
            i--;
        }
        babyGorls[i] = pointer;
        numberGorls++;
        updatePermArray();
    }
    else{
        cout << "Adding child to full node! Split first!\n";
    }
}

BT_Node* BT_Node::split(){ //call when node is full
    BT_Node* newNode = new BT_Node;
    for(int i = 3;i>1;i--){
        BT_PointyBoi temp;
        newNode->babyGorls[i-2] = babyGorls[i];
        babyGorls[i] = temp;
    }
    numberGorls=2;
    newNode->numberGorls=2;
    updatePermArray();
    newNode->updatePermArray();
    return newNode;
}


BT_Node* BT_Node::addUser(User* user, int index){ //add user to a node and return BT_Node* if overflow, else nullptr
    int i =0;
    while(i<numberPerms && user->getPerm()>=permArray[i]){
        i++;
    }
    BT_Node* returnNode = new BT_Node;
    //need an addUser for pointyboi 
    BT_PointyBoi returned = babyGorls[i].addUser(user,index);
    if(user->getPerm()==88){
        returned.leaf->print();
    }
    switch(returned.type){
        case BT_PointyBoi::EMPTY:{

            returned.deleteBoi();
            return nullptr;
        }
        case BT_PointyBoi::NODE:{//add node to node, if full, split node
            if(numberGorls==4){
                returnNode = split();
                if(returned.node->getMinPerm()>returnNode->getMinPerm()){ //node min perm > bigger node min perm -> add to here
                    returnNode->addBabyGorl(returned);
                    return returnNode;
                }
                else{
                    addBabyGorl(returned);
                    return returnNode;
                }               
            }
            else{
                addBabyGorl(returned);
                return nullptr;
            }
        }
        case BT_PointyBoi::LEAF:{ //add leaf to node, if full, split node
            if(numberGorls==4){ //trying to add leaf to a full node. Splitting node first then adding
                returnNode = split();//split the node and assigning it to a variable

                //freezing during split()

                if(returned.leaf->getMinPerm()>returnNode->getMinPerm()){ //leaf min perm > bigger node min perm -> add to here
                    returnNode->addBabyGorl(returned);
                    return returnNode;
                }
                else{
                    addBabyGorl(returned);
                    return returnNode;
                }
            }
            else{//add leaf to the node (not full)
                addBabyGorl(returned);
                return nullptr;
            }
        }
    }
    return nullptr;


}

void BT_Node::updatePermArray(){ 
    int numPerms=0;
    if(numberGorls>1){//check if # of children is greater than 1, else do nothing cuz won't happen
        for(int i=1;i<numberGorls;i++){
                numPerms++;
                permArray[i-1]=babyGorls[i].getMinPerm();
        }
    }
    numberPerms = numPerms;
}
bool BT_Node::notFullGorls(){
    if(numberGorls!=4){ //numberGorls<4
        return true;
    }
    else{
        return false; //numberGorls==4
    }
    
}

/* #endregion */

/* #region BT_Leaf */
BT_Leaf::BT_Leaf(){
    number = 0;
};
BT_Leaf::~BT_Leaf(){
    for(int i=0;i<number;i++){
        delete UserObj[i];
    }
};
bool BT_Leaf::notFull(){
    if(number==2){//full
        return false;
    }
    else{
        return true;
    }
}

BT_PointyBoi BT_Leaf::addUserLeaf(User* user,int index){
    if(number!=2){//adding to a not full leaf
        addUser(user,index);
        return BT_PointyBoi();
    }
    else{//adding to a full leaf, returning split part of leaf in a pointyboi
        return BT_PointyBoi(split(user,index));
    }


}

void BT_Leaf::addUser(User* user,int index){
    if(number==0){
        UserObj[0] = user;
        vector_index[0] = index;
        number=1;
    }
    else{ //number==1
        if(user->getPerm()>UserObj[0]->getPerm()){
            UserObj[1] = user;
            vector_index[1] = index;
        }
        else{
            UserObj[1] = UserObj[0];
            vector_index[1] = vector_index[0];
            UserObj[0] = user;
            vector_index[0] = index;
        }
        number=2;
    }
};

BT_Leaf* BT_Leaf::split(User* user, int index){//splits the leaf and returns the larger value
    BT_Leaf* newLeaf = new BT_Leaf();
    int i;
    if(user->getPerm() < UserObj[0]->getPerm()){ //user is the smallest
        newLeaf->UserObj[0] = UserObj[1];
        newLeaf->vector_index[0] = vector_index[1];
        newLeaf->UserObj[1] = nullptr;
        newLeaf->vector_index[1] = -1;
        newLeaf->number = 1;
        UserObj[1] = UserObj[0];
        vector_index[1] = vector_index[0];
        UserObj[0] = user;
        vector_index[0] = index;
        number = 2;    
    }
    else if(user->getPerm() > UserObj[1]->getPerm()){ //user is the biggest
        // newLeaf->UserObj[0] = UserObj[0];
        // newLeaf->vector_index[0] = vector_index[0];
        // newLeaf->UserObj[1] = UserObj[1];
        // newLeaf->vector_index[1] = vector_index[1];
        // newLeaf->number = 2;
        // UserObj[0] = user;
        // vector_index[0] = index;
        // UserObj[1] = nullptr;
        // vector_index[1] = -1;
        // number = 1;

        newLeaf->UserObj[0] = user;
        newLeaf->vector_index[0] = index;
        newLeaf->UserObj[1] = nullptr;
        newLeaf->vector_index[1] = -1;
        newLeaf->number = 1;
        number=2;



    }
    else{ //user is in between
        newLeaf->UserObj[0] = UserObj[1];
        newLeaf->vector_index[0] = vector_index[1];
        newLeaf->UserObj[1] = nullptr;
        newLeaf->vector_index[1] = -1;
        newLeaf->number = 1;
        UserObj[1] = user;
        vector_index[1] = index;
        number = 2;
    }
    return newLeaf;
};



int BT_Leaf::getMinPerm(){
    return UserObj[0]->getPerm();
};
void BT_Leaf::print(){
    cout << "Number of leaves: " << number << ", ";
    for(int i=0;i<number;i++){
        cout << "Perm is: " << UserObj[i]->getPerm() << ", vector index is: " << vector_index[i] << ".   ";
    }
    cout << "\n";
}
bool BT_Leaf::find(int Perm){ 
    for(int i=0;i<number;i++){
        if(UserObj[i]->getPerm()==Perm){
            return true;
        }
    }
    return false;
}

BT_Leaf* BT_Leaf::getLeaf(int Perm){
    for(int i=0;i<number;i++){
        if(UserObj[i]->getPerm()==Perm){
            return this;
        }
    }
    return nullptr;
}

/* #endregion */

/* #region BT_Tree */
    BTree::BTree(){
        BT_PointyBoi *Root = new BT_PointyBoi; //root will always be a node, not a leaf
        root = Root;
    }
    void BTree::addUser(User* user,int index){
        switch(root->type){
            case BT_PointyBoi::EMPTY:{ //first insert
                root->makeEmptyLeaf();
                    //insert to leaf
                root->leaf->addUser(user,index);
                break;
            }
            case BT_PointyBoi::NODE:{
                //search thru and find place to insert, then propagate up if need to
                BT_PointyBoi temp;
                temp = root->addUser(user,index); 
                if(temp.type==BT_PointyBoi::EMPTY){ //temp is empty so no need to split root
                    break;
                }
                else{ //split the root
                    BT_PointyBoi* newRoot = new BT_PointyBoi;
                    newRoot->makeEmptyNode();
                    newRoot->node->addBabyGorl(*root);
                    newRoot->node->addBabyGorl(temp);
                    root = newRoot;
                    break;
                }
            }
            case BT_PointyBoi::LEAF:{//The second and third inserts
                BT_PointyBoi temp;
                temp = root->addUser(user,index);
                if(temp.type==BT_PointyBoi::EMPTY){ //temp is empty so no need to split root
                    break;
                }
                else{ //split the root
                    BT_PointyBoi* newRoot = new BT_PointyBoi;
                    newRoot->makeEmptyNode();
                    newRoot->node->addBabyGorl(*root);
                    newRoot->node->addBabyGorl(temp);
                    root = newRoot;
                    break;
                }
                // //use not full function
                // if(root->leaf->notFull()){ //add to the leaf
                //     root->leaf->addUser(user,index);
                // }
                // else{//leaf is full and need to change root to node
                //     BT_PointyBoi* newRoot = new BT_PointyBoi;
                //     newRoot->makeEmptyNode();
                //     BT_Leaf* newLeaf = root->leaf->split(user,index); //get the smaller leaf from the split leaf
                //     BT_PointyBoi temp(newLeaf); //create a pointy boi from the split leaf (larger value)
                //     newRoot->node->addBabyGorl(*root); //add the smaller value
                //     newRoot->node->addBabyGorl(temp); //add the bigger value
                //     root = newRoot;
                    // cout << "root babyGorls[0]->UserObj[0] is :" << root->node->babyGorls[0].leaf->UserObj[0]->getPerm() << "\n";
                    // cout << "root babyGorls[0]->UserObj[1] is :" << root->node->babyGorls[0].leaf->UserObj[1]->getPerm() << "\n";
                    // cout << "root babyGorls[1]->UserObj[0] is :" << root->node->babyGorls[1].leaf->UserObj[0]->getPerm() << "\n";
                    //cout << "root babyGorls[1]->UserObj[1] is :" << root->node->babyGorls[1].leaf->UserObj[1]->getPerm() << "\n";
                    //root->node->updatePermArray();
                break;
            }
        }
    }
    void BTree::addUserInfo(int Perm, string Name, string Genre1, string Genre2, int index){
        User* user = new User(Perm,Name,Genre1,Genre2);
        addUser(user,index);
    }
    bool BTree::find(int Perm){ //boolean to see if Perm is in the BTree
        return root->find(Perm);
    }
    BT_Leaf* BTree::userDetails(int Perm){
        return root->getLeaf(Perm);
    }
    void BTree::print(){
        root->print();
    }

/* #endregion */
