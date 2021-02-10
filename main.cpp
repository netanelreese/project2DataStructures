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
    myString ();
    myString(char* inpStr);
    myString (myString& B);
    int Size();
    bool operator == (myString& B);
    bool operator > (myString& B);
    bool operator < (myString& B);
    myString& operator = (myString& B);
    myString& operator = (char* B);
};
myString::myString() {
    strArray = NULL;
    size = 0;
}
myString::myString(char* inpStr) {
    size = sizeof(inpStr);
    strArray = new char[size];
    for(int i = 0; i < sizeof(size); ++i) strArray[i] = inpStr[i];
}
myString::myString(myString& B) {

}
int myString::Size(){
    return size;
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

