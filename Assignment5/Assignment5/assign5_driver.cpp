#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <map>

#include "hashTable.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;


//--------------------------------------------
//A quick and dirty class that simulates a product object.
//--------------------------------------------
class product {
public:
    void setCost(int cost);
    void setName(const string&);
    string getName();
    int getCost();
    string getAllInfo();
private:
    string name;
    int cost;
};
void product::setCost(int cost) {
    this->cost = cost;
}
void product::setName(const string& name) {
    this->name = name;
}

string product::getName() {
    return name;
}

int product::getCost() {
    return cost;
}

string product::getAllInfo() {
    stringstream ss;
    ss << "Name: " << name << ", Cost: " << cost << endl;
    return ss.str();
}


//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else { 
        if (whatItShouldBe == "") {
            cout << "***Failed test " << testName << " *** " << endl << "   Output was "<< whatItIs << endl << "   Output should have been blank. " << endl;
        } else {
            cout << "***Failed test " << testName << " *** " << endl << "   Output was "<< whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
        }
        return false;
    }
}

//This helps with testing, do not modify.
bool checkEmpty(string testName, string whatItIs) {

    if (whatItIs != "") {
        cout << "Passed " << testName << ", the data was " << whatItIs << endl;
        return true;
    }
    else { 
        cout << "***Failed test " << testName << " *** " << endl << "   No data was found! "<< endl;
        return false;
    }
}
//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else { 
        cout << "***Failed test " << testName << " *** " << endl << "   Output was "<< whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
        return false;
    }
}


//This helps with testing, do not modify.
void testSimpleIntHash() {

    //Create a hashTable. We want this to be a hash table with int keys, string object values,
    //And we also supply the hash function we want to use for integers..
    hashTable<int, string> myHash(&hashFunctionInt);

    //Test #1, add "Jazz" into our hash with a key of 6.  Try to retrive it.  
    myHash.add(6, "Jazz");
    checkTest("testSimpleIntHash #1", "Jazz", myHash.item(6));

    //Test #2, attempt to get the Jazz using the operator[] code.
    checkTest("testSimpleIntHash #2", "Jazz", myHash[6]);

    //Test #3, attempt to change the value at this location:
    myHash[6] = "Nuggets";
    checkTest("testSimpleIntHash #3", "Nuggets", myHash[6]);

    //Test #4, 
    //See if we can find it
    if (myHash.exists(6)) {
        checkTest("testSimpleIntHash #4", "", "");
    } else {
        checkTest("testSimpleIntHash #4", "This test should have found an item with key 6", "This test did NOT find an item with key 6");
    }

    //Test #5, see if we can find something that doesn't exist yet.
    if (myHash.exists(1234)) {
        checkTest("testSimpleIntHash #5", "This test should NOT have found an item with key 1234.", "This test found an item with key 1234");
    } else {
        checkTest("testSimpleIntHash #5", "", "");
    }

    //Test #6, removing it from the hash
    myHash.remove(6);
    if (myHash.exists(6)) {
        checkTest("testSimpleIntHash #6", "This test should NOT have found an item with key 6.", "This test found an item with key 6");
    } else {
        checkTest("testSimpleIntHash #6", "", "");
    }

    //Add more into the hash
    myHash.add(13, "Lakers");
    myHash.add(25, "Bulls");
    myHash.add(101, "Pelicans");
    myHash.add(77, "Bucks");
    myHash.add(12, "Thunder");
    myHash.add(42, "Nets");
    myHash.add(97, "Timberwolves");
    myHash.add(123, "Bobcats");
    myHash.add(500, "Mavericks");

    //Attempt to retrieve some
    checkTest("testSimpleIntHash #7", "Thunder", myHash.item(12));
    checkTest("testSimpleIntHash #8", "Bucks", myHash.item(77));
    checkTest("testSimpleIntHash #9", "Bobcats", myHash.item(123));

    //Now count up how many are in there
    checkTest("testSimpleIntHash #10", 9, myHash.getTotalCount());

    //Now just verify that they aren't all going into the same bucket
    int worst = 0;
    worst = myHash.getWorstBucket();
    if (worst > 4) {
        cout << "Failed testSimpleIntHash #11!  One bucket has " << worst << " items in it.  That's too many!" << endl;
    } else {
        cout << "Passed testSimpleIntHash #11." << endl;
    }

    //Now go crazy and throw in 1000 more items.
    int key = 0;
    for(int i = 0; i < 1000; i++){
        //this next part just helps create some variation in generated W#s...
        if (i % 2 == 0) {
            key += 107;
        } else if (i % 3 == 0) {
            key += 91;
        } else if (i % 5 == 0) {
            key += 113;
        } else if (i % 7 == 0) {
            key += 13;
        } else {
            key += 61;
        }
        myHash.add(key, "a"); //Just add a bunch of letter a's
    }

    //Make sure they all go in there.  We put in 9 manually, then we added in 1000 more.  
    checkTest("testSimpleIntHash #12", 1009, myHash.getTotalCount());

    //Now test how good your int hash function is.  
    worst = myHash.getWorstBucket();
    if (worst > 10) {
        cout << "Failed testSimpleIntHash #13!  One bucket has " << worst << " items in it, it shouldn't be more than 10." << endl;
    } else {
        cout << "Passed testSimpleIntHash #13." << endl;
    }


}


void testHashOfObjects() {

    //Create a hashTable. We want this to be a hash table with string keys, product object values,
    //And we also supply the hash function we want to use for strings..

    hashTable<string, product> myHash(&hashFunctionString);

    //Test #1, add in a product.  Try to retrive it.  
    product tempProduct;
    tempProduct.setCost(5);
    tempProduct.setName("Silly string");
    myHash.add("12341-51231", tempProduct);
    checkTest("testHashOfObjects #1", "Silly string", myHash.item("12341-51231").getName());

    //Test #2, attempt to get the product using its ID code
    checkTest("testHashOfObjects #2", "Silly string", myHash["12341-51231"].getName());

    //Test #3, see what happens if two products have the same ID code.  This should overwrite the former.
    tempProduct.setCost(18);
    tempProduct.setName("Novelty foam hat");
    myHash["12341-51231"] = tempProduct;
    checkTest("testHashOfObjects #3", "Novelty foam hat", myHash["12341-51231"].getName());

    //Test #4, 
    //See if we can find it
    if (myHash.exists("12341-51231")) {
        checkTest("testHashOfObjects #4", "", "");
    } else {
        checkTest("testHashOfObjects #4", "This test should have found an item with key 12341-51231", "This test did NOT find an item with key 12341-51231");
    }

    //Test #5, see if we can find something that doesn't exist yet.
    if (myHash.exists("56756-75675")) {
        checkTest("testHashOfObjects #5", "This test should NOT have found an item with key 56756-75675.", "This test found an item with key56756-75675");
    } else {
        checkTest("testHashOfObjects #5", "", "");
    }

    //Test #6, removing it from the hash
    myHash.remove("12341-51231");
    if (myHash.exists("12341-51231")) {
        checkTest("testHashOfObjects #6", "This test should NOT have found an item with key 12341-51231.", "This test found an item with key 12341-51231");
    } else {
        checkTest("testHashOfObjects #6", "", "");
    }



    //Now throw in 1000 more items.
    int value = 0;
    string key;
    stringstream out;
    for(int i = 0; i < 1000; i++){
        //this next part just helps create some variation for our product ID codes.
        if (i % 2 == 0) {
            value += 107;
        } else if (i % 3 == 0) {
            value += 83;
        } else if (i % 5 == 0) {
            value += 47;
        } else if (i % 7 == 0) {
            value += 131;
        } else {
            value += 53;
        }
        key = "12345-";
        out.str("");
        if (value < 10000) 
            key = key + "0";
        if (value < 1000)
            key = key + "0";
        if (value < 100)
            key = key + "0";
        if (value < 10)
            key = key + "0";
        out << value;
        string temp = out.str();
        if (temp.length() > 5) {
            temp = temp.substr(0, 5);
        }
        key = key + temp;
        //Whew, that took a while, but the product ID is in key, and is ready to go

        //Create the product, and load in values.
        tempProduct.setName("Acme product");
        tempProduct.setCost(rand() % 41);

        //Testing the hash table "add" method
        myHash.add(key,tempProduct);
    }

    //Make sure one went in correctly.  Retrieve it.
    checkEmpty("testHashOfObjects #7", myHash["12345-02112"].getAllInfo());

    //Make sure they all go in there.
    checkTest("testHashOfObjects #8", 1000, myHash.getTotalCount());

    //Now test how good your int hash function is.  
    int worst = myHash.getWorstBucket();
    if (worst > 10) {
        cout << "Failed testHashOfObjects #9!  One bucket has " << worst << " items in it, it shouldn't be more than 10." << endl;
    } else {
        cout << "Passed testHashOfObjects #9." << endl;
    }
}


//This helps with testing, do not modify.
void testHashofHashes() {

    //A rather complicated declaration, but it works!
    hashTable< string, hashTable<int, int> > studentAssignments(&hashFunctionString);
    hashTable<int, int> tempHash1(&hashFunctionInt);
    studentAssignments.add("Alice", tempHash1);

    hashTable<int, int> tempHash2(&hashFunctionInt);
    studentAssignments.add("Bob", tempHash2);

    hashTable<int, int> tempHash3(&hashFunctionInt);
    studentAssignments.add("Karl", tempHash3);

    //Give alice some assignment scores
    studentAssignments["Alice"].add(1,73);
    studentAssignments["Alice"].add(2,65);
    studentAssignments["Alice"].add(4,91);
    //Ensure it went in
    checkTest("testHashofHashes #1", 65, studentAssignments["Alice"][2]);

    //And Bob
    studentAssignments["Bob"].add(1,90);
    studentAssignments["Bob"].add(3,84);
    studentAssignments["Bob"].add(4,99);

    //And Karl
    studentAssignments["Karl"].add(1,92);
    studentAssignments["Karl"].add(2,92);
    studentAssignments["Karl"].add(3,87);
    studentAssignments["Karl"].add(4,10);

    //Now find the average of assignment 4 scores
    int average = (studentAssignments["Alice"][4] + studentAssignments["Bob"][4] + studentAssignments["Karl"][4]) / 3;
    checkTest("testHashofHashes #2", 66, average);

    //clean up 
} 


int main(){

    testSimpleIntHash();
    testHashOfObjects();
    testHashofHashes();

    return 0;
}

