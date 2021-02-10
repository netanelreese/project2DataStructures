#include <iostream>
class myString;

using namespace std;

class myString {
    friend ostream& operator << (ostream& s, myString& A);
protected:
    char* strArray;
    int size;
    void strCpy (char* A, char* B, int n);
public:
    myString();
    myString(char* inpStr);
    myString(myString& B);
    int Size();
    bool operator == (myString& B);
    bool operator > (myString& B);
    bool operator < (myString& B);
    myString& operator = (myString& B);
    myString& operator = (char* B);
    char* getString();
};
myString::myString() { //default constructor
    strArray = NULL; //making the strArray array null
    size = 0; //setting size equal to zero
}
myString::myString(char* inpStr) { //non default constructor
    size = sizeof(inpStr); //setting the size equal to the size of the input array
    strArray = new char[size]; //creating instance of the strArray variable
    for(int i = 0; i < sizeof(size); ++i) strArray[i] = inpStr[i]; //copying over the elements to strArray
}
myString::myString(myString& B) { //copy constructor
    size = B.Size(); //setting this objects size equal to the input object's size
    strArray = new char[size]; //creating an array with size equal to the input
    for (int i = 0; i < B.Size(); ++i) strArray[i] = B.getString()[i]; //deep copying the strArray to this strArray
}
int myString::Size(){ //returning the size of this object
    return this->size;
}
char* myString::getString() { //returns the string array of this object
    return this->strArray;
}
bool myString::operator==(myString& B) {

}
bool myString::operator>(myString& B) {

}
bool myString::operator<(myString& B) {

}
myString& myString::operator=(myString& B) {

}
myString& myString::operator=(char* B) {

}

class bagOfWords {
private:
    int binarySearchAndInsert (myString& W);
protected:
    myString* _words;
    int* _frequencies;
    int _size;
public:
    bagOfWords ();
    void addWord (myString& W);//insert word w into the array _words - keep it sorted alphabetically
    void sortFreq(); //sort words array based on frequency
    void sortWords(); //sort words array alphabetically
    void display(); //print word followed by a colon followed by a single space and frequencuy
    bagOfWords* removeStopWords(myString* stopWords); //remove all the words in the array
    //stopWords from _words array
    ~bagOfWords();
};

int main () {

    int numStopWords;
    char* token;
    myString* tokenString;

    //read the first number from the file that contains the number of stop words
    cin >> numStopWords;
    myString* stopWordsList = new myString[numStopWords];

    //read the stop words
    for (int i=0; i < numStopWords; ++i) {
        token = getNextToken();
        stopWordsList[i] = token; //calls the overloaded = operator on myString class
    }

    //Now read a text and put them in the bagOfWords instance.
    bagOfWords* myBag = new bagOfWords ();
    token = getNextToken(); //first read the token as an array of characters
    tokenString = new myString (token);//create a myString object with the token
    while (token != NULL) {
        (*myBag).addWord(*tokenString); //add token to myBag
        token = getNextToken();
    }

    // this should display the token and frequency;
    // note that becuase you are using binary search and insert the tokens will
    // be sorted alphabetically
    (*myBag).display ();

    (*myBag).sortFreq ();
    (*myBag).display ();
    (*myBag).sortWords();
    (*myBag).display ();
    bagOfWords* newBag = (*myBag).removeStopWords(stopWordsList);
    (*newBag).display();
    (*newBag).sortFreq ();
    (*newBag).display ();

    delete stopWordsList;
    delete myBag;
    delete newBag;

    return 0;
}

