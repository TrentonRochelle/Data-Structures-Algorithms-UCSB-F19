#include "UserNetwork.h"
#include <sstream>
using namespace std;


void UserNetwork::inputFile(ifstream &data){
    string line;
    string temp,name,genre1,genre2;
    int perm;
    int index;
    while(getline(data, line)){
        replace(line.begin(), line.end(), ';', ' ');
        stringstream ss(line);
        ss>>temp;
        perm = atoi(temp.c_str());
        friend_list fl(perm);
        ss>>temp; //name
        name = temp;
        ss>>temp; //genre1
        while(temp!="Action"&& temp!="Adventure"&& temp!="Comedy"&& temp!= "Crime"&& temp!="Drama"&& temp!="Fantasy"&& temp!="Horror"&& temp!="Sci-Fi"){
            name = name + " " + temp;
            ss>>temp;
        }
        genre1 = temp;
        ss>>temp; //genre2
        genre2 = temp;
        while (ss >> temp){
            fl.add_friend(atoi(temp.c_str()));
        }
        FG.add_friend_list(fl);
        index = FG.find_index_of_perm(perm);
        BT.addUserInfo(perm,name,genre1,genre2,index);
    }
}
void UserNetwork::addUser(int Perm, string Name, string Genre1, string Genre2, vector<int> friend_perms){
    FG.add_user(Perm,Name,Genre1,Genre2,friend_perms);
    int Index = FG.find_index_of_perm(Perm);
    BT.addUserInfo(Perm,Name,Genre1,Genre2,Index);
}
void UserNetwork::findUser(int Perm){ //print found if in system, else print not found
    if(BT.find(Perm)){
        cout << "SUCCESS: " << Perm << " found!\n";
    }
    else{
        cout << "ERROR: " << Perm << " not found!\n";
    }
}
void UserNetwork::findUserInfo(int Perm){
    BT_Leaf* data = new BT_Leaf;
    data=BT.userDetails(Perm);
    if(data!=nullptr){
        for(int i=0;i<data->number;i++){
            if(data->UserObj[i]->getPerm()==Perm){
                data->UserObj[i]->printInfo();
                int index=data->vector_index[i];
                cout << "Perms are: ";
                FG.vector_friend_list[index].print_all_perms();
            }
        }
    }
    else{ //data is nullptr since not in the tree??
        cout << "ERROR: User not in BTree; now you fucked up. Now you fucked up. You have fucked up now.\n";
    }
    cout << "\n";
}
void UserNetwork::recommendFriends(int Perm){
    BT_Leaf* data = new BT_Leaf;
    data=BT.userDetails(Perm);
    int index;
    string genre1;
    string genre2;
    vector<int> userFriends;
    if(data!=nullptr){
        for(int i=0;i<data->number;i++){
            if(data->UserObj[i]->getPerm()==Perm){
                //data->UserObj[i]->printInfo();
                genre1 = data->UserObj[i]->getGenre1();
                genre2 = data->UserObj[i]->getGenre2();
                index=data->vector_index[i];
            }
        }
    }
    else{
        cout << "Can't recommend friends for user not in the system!\n";
        return;
    }
    userFriends = FG.vector_friend_list[index].vectorFriendPerms();
    userFriends.push_back(Perm);
    vector<int> checked;
    int V = FG.vector_friend_list.size();
    //cout << "Size of V: " << V << "\n";
    bool* visited = new bool[V];
    for (int i =0;i< V;i++){
        visited[i] = false;
    }
    vector<int> recommendedFriends;
    //vector<int> recommendFriends = DFSUtil(Perm, visited); 
    recommendedFriends = DFS(Perm, visited, genre1, genre2, recommendedFriends);
    // cout << "userFriends are: ";
    // for(int i=0;i<userFriends.size();i++){
    //     cout << userFriends[i] << " ";
    //     for(int y =0; y<recommendedFriends.size();y++){
    //         if(userFriends[i]==recommendedFriends[y]){
    //             recommendedFriends.erase(recommendedFriends.begin() + y-1);
    //             //break;
    //         }
    //     }
    // }
    recommendedFriends.erase( remove_if( begin(recommendedFriends),end(recommendedFriends),
    [&](int x){return find(begin(userFriends),end(userFriends),x)!=end(userFriends);}), end(recommendedFriends) );
    sort(recommendedFriends.begin(),recommendedFriends.end());
    cout << "\n";
    cout << "Recommended friends are:\n";
    for(int i=0;i<recommendedFriends.size();i++){
        cout << recommendedFriends[i] << " ";
    }
    cout << "\n";

}

vector<int> UserNetwork::DFS(int Perm, bool visited[], string Genre1, string Genre2, vector<int> recommendedFriends){
    //cout << Perm << "\n";
    BT_Leaf* data = new BT_Leaf;
    data=BT.userDetails(Perm);
    int index;
    vector<int> userFriends;
    string genre1;
    string genre2;
    for(int i=0;i<data->number;i++){
        if(data->UserObj[i]->getPerm()==Perm){
            genre1 = data->UserObj[i]->getGenre1();
            genre2 = data->UserObj[i]->getGenre2();
            index=data->vector_index[i];
            userFriends = FG.vector_friend_list[index].vectorFriendPerms();
            break;
        }
    }
    if(visited[index]==true){
        //cout << "visited == true\n";
        return recommendedFriends;
    }
    else{
        visited[index] = true;
        if(genre1==Genre1 || genre1==Genre2 || genre2==Genre1 || genre2==Genre2){
            recommendedFriends.push_back(Perm);
        }
        for(int i=0; i < userFriends.size(); i++){
            recommendedFriends = DFS(userFriends[i],visited, Genre1, Genre2, recommendedFriends);
        }
        return recommendedFriends;
    }
}


void UserNetwork::printFriendGraph(){
    cout << "Printing the friend graph:\n";
    FG.display_all();
}
void UserNetwork::printBTree(){
    cout << "Printing the BTree:\n";
    BT.print();
}