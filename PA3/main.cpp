#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <vector>
#include <sstream>
#include "UserNetwork.h"
using namespace std;

/* #region generate fake info */

void generateSetOfNumbers(int arr[], int n){
  int p[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
  //shuffle p
  for (int i=19; i>0; --i)
  {
    //get swap index
    int j = rand()%i;
    //swap p[i] with p[j]
    int temp = p[i];
    p[i] = p[j];
    p[j] = temp;
  }
  //copy first n elements from p to arr
  for (int i=0; i<n; ++i)
    arr[i] = p[i];
}
void generateTestCase(){
    string names[20] = {"Reid","Jamal","Ema","Margery","Clelia","Isaac","Josef","Fletcher","Jinny","Amira","Cory","Mariann","Lidia","Werner","Brendan","Delmy","Elma","Ines","Shyla","Micha"};
    string genres[8] = {"Action", "Adventure", "Comedy", "Crime", "Drama", "Fantasy", "Horror", "Sci-Fi"};
    ofstream data;
    data.open("user_info.txt");
    srand(time(NULL));
    int adj_matrix[20][20];
    for(int u = 0; u < 20; u++) {
        for (int v = u; v < 20; v++) { //you don't need to calculate weight twice so loop starts from u
            if(v == u) {
                adj_matrix[u][v] = 0;
            }
            else {
                adj_matrix[u][v] = adj_matrix[v][u] = rand()%2;
            }
        }
    }
    
    for(int y =0;y<20;y++){
        for(int x =0;x<20;x++){
            cout << adj_matrix[y][x] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
    int rand_i1,rand_i2;
    for(int i =0;i<20;i++){
        rand_i1 = rand()%8;
        rand_i2 = rand()%8;
        while(rand_i2==rand_i1){
            rand_i2 = rand()%8;
        }
        data << i << ";" << names[i] << ";" << genres[rand_i1] << ";" << genres[rand_i2] << ";";
        for(int x = 0; x<20 ;x++){
            if(adj_matrix[i][x]==1){
                data << x << ";";
            }
        }
        data << "\n";
    }
}

/* #endregion */

Friend_Graph data_to_graph(ifstream &data){
    Friend_Graph FG;
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
        genre1 = temp;
        ss>>temp; //genre2
        genre2 = temp;
        while (ss >> temp){
            fl.add_friend(atoi(temp.c_str()));
        }
        FG.add_friend_list(fl);
        //index = FG.find_index_of_perm(perm);
        //User user(perm,name, genre1,genre2,index);
    }
    return FG;
}




void main_output(){
  cout << "Welcome to the Friend Recommender! Type the number to select the action.\n";
  cout << "1) Input File\n";
  cout << "2) Add User\n";
  cout << "3) Find User\n";
  cout << "4) Find User Details\n";
  cout << "5) Recommend Friends\n";
  cout << "6) Print FriendGraph\n";
  cout << "7) Print BTree (Depth First)\n";
  cout << "8) Exit\n";
  cout << "Which operation do you want to make? (1, 2, 3, 4, 5, 6, 7, 8):\n";
}
int inputNumber(){
    //cout << "Enter an int: ";
    int x = 0;
    while(!(cin >> x)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    //cout << "You entered: " << x << endl;  
    return x; 
}

string getGenre(){
    cout <<"Type one of the following numbers to choose a genre:\n"
    << "1: Action\n"
    << "2: Adventure\n"
    << "3: Comedy\n"
    << "4: Crime\n"
    << "5: Drama\n"
    << "6: Fantasy\n"
    << "7: Horror\n"
    << "8: Sci-Fi\n";
    int number = inputNumber();
    while(number>8 && number<1){
        cout << "Not valid number, try again.\n";
        number = inputNumber();
    }
    switch(number){
        case 1:{
            return "Action";
        }
        case 2:{
            return "Adventure";
        }
        case 3:{
            return "Comedy";
        }
        case 4:{
            return "Crime";
        }
        case 5:{
            return "Drama";
        }
        case 6:{
            return "Fantasy";
        }
        case 7:{
            return "Horror";
        }
        case 8:{
            return "Sci-Fi";
        }
        default:{
            return "Error";
        }
    }
}




UserNetwork callFunction(int number, UserNetwork userNetwork){
    switch(number){
        case 1:{ //input file
            cout << "Type the file name: ";
            string filename;
            ifstream data;
            cin >> filename;
            data.open(filename);
            // data.open("user_friendship_two.txt");
            userNetwork.inputFile(data);
            break;
        }
        case 2:{ //add user

            cout << "What is the User's perm?: ";
            int perm = inputNumber();
            string name,genre1,genre2;
            cout << "What is the User's name?: ";
            cin >> name;
            genre1 = getGenre();
            genre2 = getGenre();
            vector<int> friend_perms;
            cout << "To add a friend, enter a number and then enter. Type -1 to stop adding friends.\n";
            int numPerm = inputNumber();
            while(numPerm!=-1){
                friend_perms.push_back(numPerm);
                numPerm = inputNumber();
            }
            int found = userNetwork.FG.find_index_of_perm(perm);
            if(found!=-1){
                cout << "Error! User is already in the system!\n";
                break;
            }
            userNetwork.addUser(perm, name, genre1, genre2,friend_perms);
            cout << name << " is added to the network.\n";
            break;

        }
        case 3:{ //find user
            cout << "What is the User's perm?: ";
            int perm = inputNumber();
            userNetwork.findUser(perm);
            break;
        }
        case 4:{ //find user details
            cout << "What is the User's perm?: ";
            int perm = inputNumber();
            userNetwork.findUserInfo(perm);
            break;
        }
        case 5:{ //recommend friends
            cout << "What is the User's perm?: ";
            int perm = inputNumber();
            userNetwork.recommendFriends(perm);
            break;
        }
        case 6:{//print friendgraph
            userNetwork.printFriendGraph();
            break;
        }
        case 7:{//print btree depth first
            userNetwork.printBTree();
            break;
        }
        case 8:{ //exit (won't happen)
            break;
        }
        default:{
            cout << "Not a valid input! Try Again!\n";
            break;
        }
    }
    return userNetwork;
}

int main(){
    UserNetwork userNetwork;
    //ifstream data;
    //data.open("user_friendship_two.txt");
    //userNetwork.inputFile(data);
    // userNetwork.findUser(1);
    // userNetwork.findUser(2);
    // userNetwork.findUser(3);
    // userNetwork.findUser(107);
    // userNetwork.findUser(109);
    //userNetwork.printFriendGraph();
    //userNetwork.printBTree();
    //main_output();
    string input;
    bool end_bool=1;
    int number=0;
    while(end_bool){
        main_output();
        number = inputNumber();
        if(number==8){
            cout << "Cya l8er nerd.\n";
            end_bool = 0;
        }
        else{
            userNetwork = callFunction(number, userNetwork);
        }
    }
    return 0;
}

/*
int main(){
    //generateTestCase();
    ifstream data;
    data.open("user_friendship.txt");
    Friend_Graph FG;
    FG = data_to_graph(data);
    FG.display_all();
    //vector<int> friends;
    //friends.push_back(5);
    //friends.push_back(102);
    //FG.add_user(108,"JJBB", "Comedy", "Adventure", friends);
    //FG.display_all();
    //cout << FG.find_index_of_perm(20);
    return 0;
}
*/
