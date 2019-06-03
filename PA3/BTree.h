#include "users.cpp"
using namespace std;

struct BT_Node;
struct BT_Leaf;
struct BT_PointyBoi;

struct BT_PointyBoi{
    union{
        BT_Node* node;
        BT_Leaf* leaf;
    };
    enum Type{EMPTY, NODE, LEAF};
    Type type;
    BT_PointyBoi();
    BT_PointyBoi(BT_Node* Node);
    BT_PointyBoi(BT_Leaf* Leaf);
    void makeEmptyLeaf();
    void makeEmptyNode();
    void deleteBoi();
    int getMinPerm();
    void print();
    bool find(int Perm);
    BT_Leaf* getLeaf(int Perm);
    BT_PointyBoi addUser(User* user, int index);
};

struct BT_Node{
    BT_PointyBoi *daddy; //parent node
    BT_PointyBoi babyGorls[4]; //pointers to children
    int numberPerms; //number of perms
    int numberGorls; //number of children
    int permArray[3]; //keys of perms for path
    BT_Node();
    BT_Node* split(); //does an even split (2 on left, 2 on right) returns the larger node
    BT_Node* addUser(User* user, int index);
    void addBabyGorl(BT_PointyBoi pointer); 
    void updatePermArray(); //goes through the children to find what the perm keys should be
    bool notFullGorls();
    int getMinPerm();
    void print();
    bool find(int Perm);
    BT_Leaf* getLeaf(int Perm);
};

struct BT_Leaf{
    User *UserObj[2];
    int vector_index[2];
    int number;
    BT_Leaf();
    ~BT_Leaf();
    BT_PointyBoi addUserLeaf(User* user,int index); //main add function
    void addUser(User* user,int index); //add when not full
    BT_Leaf* split(User* user, int index); //add when full
    bool notFull();
    int getMinPerm();
    void print();
    bool find(int Perm);
    BT_Leaf* getLeaf(int Perm);
};



class BTree{
    private:
        BT_PointyBoi *root;
    public:
        BTree();
        void addUser(User* user, int index);
        void addUserInfo(int Perm, string Name, string Genre1, string Genre2, int index);
        bool find(int Perm);
        BT_Leaf* userDetails(int Perm);
        void print();

};
