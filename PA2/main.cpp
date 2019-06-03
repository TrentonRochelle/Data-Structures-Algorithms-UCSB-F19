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
            return this->word;
        }
        int getAddress(){
            return this->array_address;
        }
        void setAddress(int newArrayAddress){
            array_address = newArrayAddress;
        }
        HashNode(){
            this->word = "-1";
            this->array_address = -1;
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
        HashNode *arr;
        int capacityHeap;
        int capacityTable;
        int sizeHeap;
        int sizeTable;
        int Heap[16];
        string HeapWords[16];
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
            capacityHeap = 15;
            capacityTable = 31;
            sizeHeap = 0;
            sizeTable = 0;
            arr = new HashNode[capacityTable]; //initialize the hashtable array
            //for(int i = 0; i<capacity+1; i++){ // set all values to null
            //    arr[i] = NULL;
            //}
            for(int i = 0; i<16;i++){
                Heap[i] = -1;
                HeapWords[i] = "-1";
            }
        };

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HASH TABLE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        int hashed(string word, int capacityTable){ //hash function for hash table
            std::tr1::hash<string> hash_fn;
            size_t data = hash_fn(word);
            return static_cast<unsigned int>(data)%capacityTable;
        }
        void insertNode(string word, int array_address){ //insertNode in Hash Table
            HashNode tempp = HashNode(word,array_address);
            int hashIndex = hashed(word, capacityTable);
            while(arr[hashIndex].getWord() != "-1") { 
                hashIndex++; 
                hashIndex %= (capacityTable); 
            }
            sizeTable++; 
            arr[hashIndex] = tempp; 
        }
        void deleteNode(string word) { 
            int hashIndex = hashed(word, capacityTable); 
            while(arr[hashIndex].getWord() != "-1") 
            { 
                if(arr[hashIndex].getWord() == word) 
                { 
                    arr[hashIndex] = HashNode();
                    sizeTable--; 
                    break;
                }
                hashIndex++; 
                hashIndex %= capacityTable; 
            } 
        }
        int get(string word) { // Get address of word in minheap
            int hashIndex = hashed(word,capacityTable);  
            while(arr[hashIndex].getWord() != "-1") 
            { 
                if(arr[hashIndex].getWord() == word) 
                    return arr[hashIndex].getAddress(); 
                hashIndex++; 
                hashIndex %= capacityTable; 
            } 
            return 0; 
        }
        void swapAddress(string word1, string word2) { //swap address of two words in the minheap
            int hashIndex = hashed(word1,capacityTable);
            int word1Address;
            int word1Index;
            int word2Address;
            int word2Index;
            while(arr[hashIndex].getWord() != "-1") 
            { 
                if(arr[hashIndex].getWord() == word1){ 
                    //cout << arr[hashIndex].getWord() << "\n";
                    word1Address = arr[hashIndex].getAddress();
                    word1Index = hashIndex;
                    break;
                }
                hashIndex++; 
                hashIndex %= capacityTable; 
                
            }
            //cout << word1Address;
            hashIndex = hashed(word2,capacityTable);
            while(arr[hashIndex].getWord() != word2) 
            { 
                hashIndex++; 
                hashIndex %= capacityTable; 
            }
            word2Address = arr[hashIndex].getAddress();
            word2Index = hashIndex;
            arr[word1Index].setAddress(word2Address);
            arr[word2Index].setAddress(word1Address);
        }

        
        bool isEmpty() { 
            return sizeTable == 0; 
        } 
        void PrintHashTable() { 
            for(int i=0 ; i<capacityTable ; i++) 
            { 
                if(arr[i].getWord() != "-1"){
                    cout << "word = " << arr[i].getWord()  
                    <<"  array address = "<< arr[i].getAddress() << endl; 
                }
            } 
        } 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MIN HEAP FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        int getSize(){
			return sizeHeap;
		}
        int getCapacity(){
            return capacityHeap;
        }
		void increaseFreq(int i){
			Heap[i]++;
            percolateDown(i);
		}
		/*void deleteMin(){
            swapAddress(HeapWords[1], HeapWords[getSize()]);
			Heap[1]=Heap[getSize()];
            Heap[getSize()] = -1;
            HeapWords[1] = HeapWords[getSize()];
            HeapWords[getSize()] = "-1";
			sizeHeap--;
			percolateDown(1);
		}*/
		void percolateDown(int i){
			//int i = 1;
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
                string tempString = HeapWords[i];
                HeapWords[i] = HeapWords[t];
                HeapWords[t] = tempString;
                swapAddress(HeapWords[t],HeapWords[i]);
                i = t;
            }
		}
        void percolateUp(){
            int i = getSize();
            while(true){
                int parent = Parent(i);
                if (parent > 0 && Heap[parent]>Heap[i] ){
                    int t = Heap[parent];
                    string tString = HeapWords[parent];
                    Heap[parent] = Heap[i];
                    HeapWords[parent] = HeapWords[i];
                    Heap[i] = t;
                    HeapWords[i] = tString;
                    swapAddress(HeapWords[parent],HeapWords[i]);
                    i = parent;
                }
                else{
                    break;
                }
            }
        }
        void insertHeap(string word){
            if(sizeHeap == getCapacity()){
                cout << "error full minheap";
                return;
            }
            Heap[getSize()+1] = 1;
            HeapWords[getSize()+1] = word;
            sizeHeap++;
            percolateUp();
            
        }
        void PrintHeap(){
            for(int i = 1; i<getSize()+1; i++){
                cout << HeapWords[i] << " has a frequency of " << Heap[i] << ".\n";
                //cout << Heap[i] << "\n";
            }
        }



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~COMBINED FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Insert(string word){
    int index = get(word);
    if(word == "macmillan"){
        int debug;
    }
    if(index!=0){ //word in hashtable
         increaseFreq(index);
    }
    else{ //word not in hashtable
        if(sizeHeap==capacityHeap){ //if the minheap is full
            ReplaceMin(word);
        }
        else{ //minheap isn't full
            insertNode(word, getSize()+1);
            insertHeap(word);

        }
    }
}
    void ReplaceMin(string word){
            deleteNode(HeapWords[1]);
            HeapWords[1]= word;
            insertNode(word, 1);
    }
};

int main(){
    string x;
    int heap[16];
    ifstream data;
    freqCounter Counter;
    data.open ("article_ta.txt");
    while(data >>x){
        x.erase(std::remove(x.begin(), x.end(), ','), x.end());
        x.erase(std::remove(x.begin(), x.end(), '.'), x.end());
        transform(x.begin(), x.end(), x.begin(), ::tolower);
        //cout << x << " ";
        Counter.Insert(x);

    }
    Counter.PrintHashTable();
    Counter.PrintHeap();




    data.close();
    return 0;
}
