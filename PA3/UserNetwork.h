#include "BTree.h"

using namespace std;

class UserNetwork{
    public:
        BTree BT;
        Friend_Graph FG;
        void inputFile(ifstream &data);
        void addUser(int Perm, string Name, string Genre1, string Genre2, vector<int> friend_perms);
        void findUser(int Perm);
        void findUserInfo(int Perm);
        void recommendFriends(int Perm);
        void printFriendGraph();
        void printBTree();

        vector<int> DFS(int Perm, bool visited[], string Genre1, string Genre2, vector<int> recommendedFriends);
};


