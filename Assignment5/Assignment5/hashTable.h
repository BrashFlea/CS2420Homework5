#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "doublyLinkedList.h"

using std::string;

//--------------------------------------------
//Two hash functions for you to complete
//--------------------------------------------
unsigned int hashFunctionInt(const void *void_key) {
    //Get that parameter back into an int pointer.  
    unsigned int *temp = static_cast<unsigned int *>(const_cast<void *>(void_key));
    unsigned int key = *temp;
    //TODO: Complete this.  You need to hash the int variable key and return a value between 0 and 999.


    return 0;


}

unsigned int hashFunctionString(const void *void_key) {
    string *temp = static_cast<string *>(const_cast<void *>(void_key));
    string key = *temp;
    //TODO: Complete this.  You need to hash the int variable key and return a value between 0 and 999.
    
    //Hint, don't return a negative value!

    return 0;
    
}


//***********************************
//The hash table class
//***********************************
//Complete the methods indicated by TODO below.  Implement a doubly linked list.  These methods must work as specified in the assignment.
template <typename T, typename U>
class hashTable{
public:

    hashTable() {hashFunction = &hashFunctionInt; linkedListArray = new DoublyLinkedList<T, U>[NUMBER_OF_LINKED_LISTS];}
    hashTable(unsigned int(*hashFunction)(const void *));
    hashTable(const hashTable& obj);
    ~hashTable();
    hashTable& operator=( hashTable tmp );

    void add(const T& key, const U& value);
    bool exists(const T& key) const;
    void remove(const T& key);
    U item(const T& key);
    U& operator[](const T& key);

    //friended so the checkTest function can have access to private data members of this class.
    friend void testSimpleIntHash();
    friend void testHashOfObjects();

protected:

    DoublyLinkedList<T, U> *linkedListArray; //The array of linked lists
    unsigned int hash(const T& key) const;
private:
    int getWorstBucket() const;
    int getTotalCount() const;
    unsigned int(*hashFunction)(const void*);
    static const int NUMBER_OF_LINKED_LISTS = 1000;
};

template <typename T, typename U>
hashTable<T,U>::hashTable(unsigned int (* hashFunction)(const void*)) {

    this->hashFunction = hashFunction;
    //TODO: Initialize an array of 1000 linked lists using the 
    //new keyword, storing the array starting address in the 
    //pointer linkedListArray
    linkedListArray = NULL;

}


//copy constructor
template <typename T, typename U>
hashTable<T,U>::hashTable(const hashTable& obj) {
    this->hashFunction = obj.hashFunction;
    if (obj.linkedListArray == NULL) {
        this->linkedListArray = NULL;
    } else {
        this->linkedListArray = new DoublyLinkedList<T, U>[NUMBER_OF_LINKED_LISTS];    
        for (int i = 0; i < NUMBER_OF_LINKED_LISTS; i++) {
            this->linkedListArray[i] = obj.linkedListArray[i];
        }
    }
}

template <typename T, typename U>
hashTable<T,U>& hashTable<T,U>::operator=( hashTable<T,U> tmp ) {
    this->hashFunction = tmp.hashFunction;
	delete [] (this->linkedListArray);
	if (tmp.linkedListArray == NULL) {
        this->linkedListArray = NULL;
    } else { 
		this->linkedListArray = new DoublyLinkedList<T, U>[NUMBER_OF_LINKED_LISTS];
        for (int i = 0; i < NUMBER_OF_LINKED_LISTS; i++) {
            this->linkedListArray[i] = tmp.linkedListArray[i];
        }
    }
    return *this;
}


template <typename T, typename U>
hashTable<T,U>::~hashTable() {
    if (linkedListArray != NULL) {
        delete[] linkedListArray;
    }

}

template <typename T, typename U>
void hashTable<T, U>::add(const T& key, const U& value)  {
    //TODO: 
    //hash the key hash(key)
    //Get the returned index
    //use that index in your array of linked lists
  
}


template <typename T, typename U>
bool hashTable<T, U>::exists(const T& key) const {
    //TODO: 
    //hash the key hash(key)
    //Get the returned index
    //use that index in your array of linked lists
    
    return false;

}


template <typename T, typename U>
U hashTable<T, U>::item(const T& key) {
    //TODO: 
    //hash the key hash(key)
    //Get the returned index
    //use that index in your array of linked lists
    
    //to get it to compile
    U temp;
    return temp;
}


template <typename T, typename U>
U& hashTable<T, U>::operator[](const T& key) {
    //TODO: 
    //hash the key hash(key)
    //Get the returned index
    //use that index in your array of linked lists


    //These two lines are to just get it to compile, you don't want them.
    //(this is also causing the memory leak test to fail)
    U* temp = new U;
    return *temp;

}



template <typename T, typename U>
void hashTable<T, U>::remove(const T& key) {
    //TODO:
    //hash the key hash(key)
    //Get the returned index
    //use that index in your array of linked lists
    
}



template <typename T, typename U>
unsigned int hashTable<T, U>::hash(const T& key) const {
    //A helpful method which does all the function pointer work
    //for you so it knows which hash function to call.
    return (*hashFunction)(&key);
}

template <typename T, typename U>
int hashTable<T, U>::getWorstBucket() const{
    int count;
    int highest = 0;
    if (linkedListArray != NULL) {
        for (int i = 0; i < 1000; i++) {
            count = linkedListArray[i].getCount();
            if (count > highest) {
                highest = count;
            }
        }
    }
    return highest;
}

template <typename T, typename U>
int hashTable<T, U>::getTotalCount() const{
    int count;
    int sum = 0;
    if (linkedListArray != NULL) {
        for (int i = 0; i < 1000; i++) {
            count = linkedListArray[i].getCount();
            sum += count;
        }
    }
    return sum;
}

#endif

