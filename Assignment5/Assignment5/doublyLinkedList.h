#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

//--------------------------------------------
//The Node class
//--------------------------------------------
template <typename T, typename U>
class Node{
public:
    T key;
    U info;
    Node *backward;
    Node *forward;

};


//--------------------------------------------
//For error handling
//--------------------------------------------
class Error {};



//--------------------------------------------
//The linked list base class.
//--------------------------------------------
//Complete the methods indicated by TODO below.  Implement a doubly linked list.  These methods must work as specified in the assignment.
template <typename T, typename U>
class DoublyLinkedList{
private:
    int count;
    Node<T, U> *first;
    Node<T, U> *last;

    void destroyList();

public:

    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList(); 
    ~DoublyLinkedList();     
    int getCount() const;
    void insertLast(const T&, const U&);
    bool nodeWithKeyExists(const T&) const;
    U& searchForKey(const T&);
    void deleteNodeWithKey(const T&);

};

template <typename T, typename U>
DoublyLinkedList<T, U>::DoublyLinkedList(){
    first = NULL;
    last = NULL;
    count = 0;
}

//copy constructor
template <typename T, typename U>
DoublyLinkedList<T, U>::DoublyLinkedList(const DoublyLinkedList<T,U>& other){
    if (other.first == NULL) {
        this->first = NULL;
        this->last = NULL;
        count = 0;
        return;
    }

    if (other.first != NULL) {
        Node<T,U> *temp = new Node<T,U>();
        temp->key = other.first->key;
        temp->info = other.first->info;
        temp->backward = NULL;
        temp->forward = NULL;
        this->first = temp;
    }

    //start at the second node now
    Node<T,U> *previous = other.first;
    Node<T,U> *current = other.first->forward;
    while (current != NULL) {
        Node<T,U> *temp = new Node<T,U>();
        temp->key = current->key;
        temp->info = current->info;
        temp->backward == previous;
        previous->forward = temp;
        temp->forward = NULL;
        previous = current;
        current = current->forward;

    }
    last = previous;

    this->count = other.count;

}


template <typename T, typename U>
DoublyLinkedList<T, U>::~DoublyLinkedList(){    
    this->destroyList();
}

//Destroy the list, and reclaim all memory.
template <typename T, typename U>
void DoublyLinkedList<T, U>::destroyList() {
    Node<T, U> *temp;
    while (first != NULL) {
        temp = first;
        first = first->forward;
        delete temp;
    }
    last = NULL;
    count = 0;
}

//Returns the number of nodes in this linked list.
template <typename T, typename U>
int DoublyLinkedList<T,U>::getCount() const {
    return count;
}
//Done
//Add/insert an node onto the end of the list.
template <typename T, typename U>
void DoublyLinkedList<T,U>::insertLast(const T& key, const U& value) {
  
	//TODO: Complete this:
}

//Done
template <typename T, typename U>
bool DoublyLinkedList<T, U>::nodeWithKeyExists(const T& key) const {
    //TODO: Complete this:
    
    return false;

}


//Done
template <typename T, typename U>
U& DoublyLinkedList<T, U>::searchForKey(const T& key) {
    //TODO: Complete this
    
    //throw an error if there's nothing to delete
    throw Error();
}


//Done
template <typename T, typename U>
void DoublyLinkedList<T, U>::deleteNodeWithKey(const T& key) {
    //TODO: Complete this:
    
}

#endif

