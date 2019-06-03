#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <tr1/functional>
using namespace std;

class HashNode{
    friend class HashMap;
    friend class freqCounter;
    private:
        string word;
        int array_address;
    public:
        string getWord(){
            return word;
        }
        int getAddress(){
            return array_address;
        }
        void setAddress(int newArrayAddress){
            array_address = newArrayAddress;
        }
        HashNode(string word, int array_address){
            this->word = word;
            this->array_address = array_address;
        };
};

class HashMap{
    friend class HashNode;
    HashNode **arr;
    int capacity;
    int size;
    friend class MinHeap;
    //HashNode *temp;
    public:
        HashMap(){
            capacity = 15;
            size = 0;
            arr = new HashNode*[capacity];
            for(int i = 0; i<16; i++){
                arr[i] = NULL;
            }
            //temp = new HashNode("-1", -1);
        }
        
        int hashed(string word, int capacity){
	    std::tr1::hash<string> hash_fn;
	    size_t data = hash_fn(word);
            return static_cast<unsigned int>(data)%capacity;
        }
        void insertNode(string word, int array_address){
            HashNode *tempp = new HashNode(word,array_address);
            int hashIndex = hashed(word, capacity);
            while(arr[hashIndex] != NULL && arr[hashIndex]->getWord() != word && arr[hashIndex]->getWord() != "-1") { 
                hashIndex++; 
                hashIndex %= capacity; 
            }
            if(arr[hashIndex] == NULL || arr[hashIndex]->getWord() == "-1"){
                size++; 
            }
            arr[hashIndex] = tempp; 
        }
        void deleteNode(string word) { 
            // Apply hash function to find index for given key 
            int hashIndex = hashed(word, capacity); 
            
            //finding the node with given key 
            while(arr[hashIndex] != NULL) 
            { 
                //if node found 
                if(arr[hashIndex]->getWord() == word) 
                { 
                    //HashNode *tempp = arr[hashIndex]; 
                    
                    //Insert dummy node here for further use 
                    //arr[hashIndex] = temp; 
                    arr[hashIndex] = NULL;
                    
                    // Reduce size 
                    size--; 
                    //return temp->array_address; 
                } 
                hashIndex++; 
                hashIndex %= capacity; 
            } 
        }
        int get(string word) { 
            // Apply hash function to find index for given key 
            int hashIndex = hashed(word,capacity); 
    
            //finding the node with given key    
            while(arr[hashIndex] != NULL) 
            { 
                //if node found return its value 
                if(arr[hashIndex]->getWord() == word) 
                    return arr[hashIndex]->getAddress(); 
                hashIndex++; 
                hashIndex %= capacity; 
            } 
            //If not found return null 
            return 0; 
        }
        int sizeofMap(){ 
            return size; 
        }
        
        bool isEmpty() { 
            return size == 0; 
        } 
        void display() { 
            for(int i=0 ; i<capacity ; i++) 
            { 
                if(arr[i] != NULL && arr[i]->getWord() != "-1"){
                    cout << "word = " << arr[i]->getWord()  
                    <<"  array address = "<< arr[i]->getAddress() << endl; 
                }
            } 
        } 

};

class MinHeap{
    friend class HashMap;
	private:
		int size;
        int capacity;
		int Heap[16];
		int Parent(int i){
			return (i/2);
		}
		int LeftChild(int i){
			return (2*i);
		}
		int RightChild(int i){
			return (2*i +1);
		}

	public:
        MinHeap(){
            capacity = 15;
            size = 0;
        }
		int getSize(){
			return size;
		}
        int getCapacity(){
            return capacity;
        }
		void increaseFreq(int i){
			Heap[i]++;
			
		}
		void deleteMin(){
			Heap[1]=Heap[getSize()];
			size--;
			percolateDown();
		}
		void percolateDown(){
			int i = 1;
            while(i<getSize()){
                int leftChild = LeftChild(i);
                int rightChild = RightChild(i);
                int t;
                if (leftChild <= getSize()){
                    t = leftChild;
                }
                else{
                    break;
                }
                if (rightChild <= getSize() && Heap[leftChild] > Heap[rightChild]){
                    t = rightChild;
                }
                if(Heap[i] <= Heap[t]) break;
                int temp = Heap[i];
                Heap[i] = Heap[t];
                Heap[t] = temp;
                i = t;
            }
		}
        void percolateUp(){
            int i = getSize();
            while(true){
                int parent = Parent(i);
                if (parent > 0 && Heap[parent]>Heap[i] ){
                    int t = Heap[parent];
                    Heap[parent] = Heap[i];
                    Heap[i] = t;
                    i = parent;
                }
                else{
                    break;
                }
            }
        }
        void insert(int freq){
            if(size == getCapacity()){
                cout << "error full minheap";
                return;
            }
            Heap[getSize()+1] = freq;
            size++;
            percolateUp();
            
        }
        void printMinHeap(){
            for(int i = 1; i<getSize()+1; i++){
                cout << Heap[i];
            }
        }
};

class freqCounter{
    private:
        HashNode **arr;
        int capacity;
        int size;
        int Heap[16];
		int Parent(int i){
			return (i/2);
		}
		int LeftChild(int i){
			return (2*i);
		}
		int RightChild(int i){
			return (2*i +1);
		}

    public:
        freqCounter(){
            capacity = 15;
            size = 0;
            arr = new HashNode*[capacity]; //initialize the hashtable array
            for(int i = 0; i<capacity+1; i++){ // set all values to null
                arr[i] = NULL;
            }
        };

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HASH TABLE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        int hashed(string word, int capacity){ //hash function for hash table
            std::tr1::hash<string> hash_fn;
            size_t data = hash_fn(word);
            return static_cast<unsigned int>(data)%capacity;
        }
        void insertNode(string word, int array_address){ //insertNode in Hash Table
            HashNode *tempp = new HashNode(word,array_address);
            int hashIndex = hashed(word, capacity);
            while(arr[hashIndex] != NULL && arr[hashIndex]->getWord() != word && arr[hashIndex]->getWord() != "-1") { 
                hashIndex++; 
                hashIndex %= capacity; 
            }
            if(arr[hashIndex] == NULL || arr[hashIndex]->getWord() == "-1"){
                size++; 
            }
            arr[hashIndex] = tempp; 
        }
        void deleteNode(string word) { 
            int hashIndex = hashed(word, capacity); 
            while(arr[hashIndex] != NULL) 
            { 
                if(arr[hashIndex]->getWord() == word) 
                { 
                    arr[hashIndex] = NULL;
                    size--; 
                } 
                hashIndex++; 
                hashIndex %= capacity; 
            } 
        }
        int get(string word) { // Get address of word in minheap
            int hashIndex = hashed(word,capacity);  
            while(arr[hashIndex] != NULL) 
            { 
                if(arr[hashIndex]->getWord() == word) 
                    return arr[hashIndex]->getAddress(); 
                hashIndex++; 
                hashIndex %= capacity; 
            } 
            return 0; 
        }
        void swapAddress(string word1, string word2) { //swap address of two words in the minheap
            int hashIndex = hashed(word1,capacity);
            int word1Address;
            int word1Index;
            int word2Address;
            int word2Index;
            while(arr[hashIndex] != NULL) 
            { 
                if(arr[hashIndex]->getWord() == word1) 
                    word1Address = arr[hashIndex]->getAddress();
                    word1Index = hashIndex;
                hashIndex++; 
                hashIndex %= capacity; 
            }
            hashIndex = hashed(word2,capacity);
            while(arr[hashIndex] != NULL) 
            { 
                if(arr[hashIndex]->getWord() == word2) 
                    word2Address = arr[hashIndex]->getAddress();
                    word2Index = hashIndex;
                hashIndex++; 
                hashIndex %= capacity; 
            }
            arr[word1Index]->setAddress(word2Address);
            arr[word2Index]->setAddress(word1Address);
        }

        
        bool isEmpty() { 
            return size == 0; 
        } 
        void displayTable() { 
            for(int i=0 ; i<capacity ; i++) 
            { 
                if(arr[i] != NULL && arr[i]->getWord() != "-1"){
                    cout << "word = " << arr[i]->getWord()  
                    <<"  array address = "<< arr[i]->getAddress() << endl; 
                }
            } 
        } 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MIN HEAP FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        int getSize(){
			return size;
		}
        int getCapacity(){
            return capacity;
        }
		void increaseFreq(int i){
			Heap[i]++;
			
		}
		void deleteMin(){
			Heap[1]=Heap[getSize()];
			size--;
			percolateDown();
		}
		void percolateDown(){
			int i = 1;
            while(i<getSize()){
                int leftChild = LeftChild(i);
                int rightChild = RightChild(i);
                int t;
                if (leftChild <= getSize()){
                    t = leftChild;
                }
                else{
                    break;
                }
                if (rightChild <= getSize() && Heap[leftChild] > Heap[rightChild]){
                    t = rightChild;
                }
                if(Heap[i] <= Heap[t]) break;
                int temp = Heap[i];
                Heap[i] = Heap[t];
                Heap[t] = temp;
                i = t;
            }
		}
        void percolateUp(){
            int i = getSize();
            while(true){
                int parent = Parent(i);
                if (parent > 0 && Heap[parent]>Heap[i] ){
                    int t = Heap[parent];
                    Heap[parent] = Heap[i];
                    Heap[i] = t;
                    i = parent;
                }
                else{
                    break;
                }
            }
        }
        void insert(int freq){
            if(size == getCapacity()){
                cout << "error full minheap";
                return;
            }
            Heap[getSize()+1] = freq;
            size++;
            percolateUp();
            
        }
        void printMinHeap(){
            for(int i = 1; i<getSize()+1; i++){
                cout << Heap[i];
            }
        }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~COMBINED FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        void deleteTopNode(){
            

        };

};

int main(){
    string x;
    //int heap[16];
    ifstream data;
    data.open ("article_ta.txt");
    //while(data >>x){
      //  x.erase(std::remove(x.begin(), x.end(), ','), x.end());
      //  x.erase(std::remove(x.begin(), x.end(), '.'), x.end());
      //  transform(x.begin(), x.end(), x.begin(), ::tolower);
        //cout << x << " ";

   // }
    //HashMap *HashTable = new HashMap();
    freqCounter HashTable;
    HashTable.insertNode("word1", 1);
    HashTable.insertNode("word2", 2);
    HashTable.insertNode("word3", 3);
    HashTable.insertNode("word16", 16);
    //HashTable.swapAddress("word2", "word3");
    HashTable.displayTable();

    freqCounter minHeap;
    minHeap.insert(1);
    minHeap.insert(6);
    minHeap.insert(7);
    minHeap.insert(8);
    minHeap.insert(3);
    minHeap.insert(4);
    minHeap.insert(9);
    minHeap.insert(2);
    minHeap.deleteMin();
    minHeap.printMinHeap();



    data.close();
    return 0;
}
