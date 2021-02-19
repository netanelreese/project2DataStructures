#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
    for (int i=0; i < n; i++) {
        A[i] = '\0';
    }
}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
    for (int i=0; i < n; i++) {
        B[i] = A[i];
    }
}

// return the length of a given string A
int stringLength (char* A) {
    int size = 0;
    while (A[size] != '\0') size++;
    return size; //size is the last index position
}



class myString;

class myString {
    friend ostream& operator << (ostream& s, myString& A);
protected:
    char* strArray;
    int size;
public:
    myString ();
    myString(char* inpStr);
    myString (myString& B);
    int Size();
    char* getWord();
    bool operator == (myString& B);
    bool operator > (myString& B);
    bool operator < (myString& B);
    myString& operator = (myString& B);
    myString& operator = (char* B);
    ~myString();
};

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
    s << A.strArray;
    return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
    size = 0;
    strArray = new char[1];
    strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
    int i = 0;
    while (inpStr[i] != '\0')
        i++;
    size = i;
    strArray = new char[size];
    emptyString (strArray, size+1);
    for (int j=0; j < size; j++)
        strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
    delete [] strArray;
    strArray = NULL;
    size = B.size;
    strArray = new char[size];
    emptyString(strArray, size+1);
    stringCopy (B.strArray, size, strArray);
}

char* myString::getWord()
{
    return strArray; //returns the char array that represents the string of this object
}

// getter for size of myString
int myString::Size () {
    return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {
    myString output; //initializing a new myString object
    output.strArray = new char[stringLength(B)]; //initializing the strArray member of the output obkect
    for (int i = 0; i < stringLength(B); ++i) { //copying the input char array over
        output.strArray[i] = B[i];
    }
    output.size = stringLength(B); //setting the size of this object

    return output; //returning the output object
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
    myString output; //initializing a new myString object
    output.strArray = new char[B.Size()]; //initializing the strArray member of the output object with size of B's string
    for (int i = 0; i < B.Size(); ++i) { //copying the input char array over
        output.strArray[i] = B.getWord()[i];
    }
    output.size = B.Size(); //setting the size of this object

    return output; //returning the output object

    return output;
}

// checking if two myString objects are the same - return true or false
bool myString::operator==(myString& B) {
    bool same = false;
    for (int i = 0; i < Size(); ++i) {
        if (B.getWord()[i] == getWord()[i]) {
            same = true;
        }
        else {
            same = false;
        }
    }
    return same;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator<(myString& B) {
    bool lessThan = false;
    if (Size() == B.Size()) {
        for (int i = 0; i < Size(); ++i) {
            if (getWord()[i] < B.getWord()[i]) {
                lessThan = true;
            }
            else {
                lessThan = false;
            }
        }
    }
    else if (Size() < B.Size()) {
        lessThan = true;
    }
    else {
        lessThan = false;
    }
    return lessThan;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator>(myString& B) {
    bool greaterThan = false;
    if (Size() == B.Size()) {
        for (int i = 0; i < Size(); ++i) {
            if (getWord()[i] > B.getWord()[i]) {
                greaterThan = true;
            }
            else {
                greaterThan = false;
            }
        }
    }
    else if (Size() > B.Size()) {
        greaterThan = true;
    }
    else {
        greaterThan = false;
    }
    return greaterThan;
}
myString::~myString() {
    delete [] strArray;
    size = 0;
    cout << "myString object destroyed." << endl;
}

// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
    char* str = new char[20]; //assumes a max token size of 20
    emptyString (str, 20);

    char c;
    int i = 0;
    while (!cin.eof()) {
        cin.get(c);
        if (!cin.eof ()) {
            if ((c != '\n') && (c != ' ')) {
                if ( ((c >= 'a') && (c <= 'z')) ||
                     ((c >= 'A') && (c <= 'Z')) ||
                     ((c >= '0') && (c <= '9')) )
                    str[i++] = c;
            }
            else if ((c == '\n') && (i > 0))
                return str;
            else if ((c == ' ') && (i > 0))
                return str;
        }
    }
    if (i > 0) return str;
    else return NULL;
}

int binarySearch(myString* arr, int left, int right, myString& stringNeeded) {
    int mid = (left + (right - 1))/2;

    if (arr[mid] == stringNeeded){
        return 1;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bagOfWords {
private:
    int binarySearchAndInsert (myString& W);
protected:
    myString* _words;
    int* _frequencies;
    int _size;

public:
    bagOfWords ();
    bagOfWords (int numOfWords);

    myString* get_Words();
    int* get_Freq();
    int get_size();
    void setSize(int i);

    void addWord (myString& W);//insert word w into the array _words - keep it sorted alphabetically
    void sortFreq(); //sort words array based on frequency
    void sortWords(); //sort words array alphabetically
    void display(); //print word followed by a colon followed by a single space and frequencuy
    bagOfWords* removeStopWords(myString* stopWords, int numStopWords); //stopWords from _words array
    ~bagOfWords();
};

// default constructor - initializes with no words
bagOfWords::bagOfWords()
{
    _size = 0;
    _words = new myString[0];
    _frequencies = new int[0];
}

// non default constructor - initializes with a known number of words
bagOfWords::bagOfWords (int numOfWords)
{
    _size = numOfWords;
    _words = new myString[numOfWords];
    _frequencies = new int[numOfWords];
}

myString* bagOfWords::get_Words()
{
    return _words;
}

int* bagOfWords::get_Freq()
{
    return _frequencies;
}

int bagOfWords::get_size()
{
    return _size;
}

void bagOfWords::setSize(int i)
{
    _size = i;
}

// print the bag of words in dictionary format
void bagOfWords::display()
{
    for (int i = 0; i < _size; ++i) {
        cout << _words[i] << ": " << _frequencies[i] << endl;
    }
}

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq()
{
    // TODO
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords()
{
    //sorts the bagOfWords alphabetically using insertion sort
    int i, j, keyFreq;
    myString keyWord;
    for (int i = 1; i < get_size(); ++i) {
        keyWord = get_Words()[i];
        keyFreq = get_Freq()[i];
        j = i - 1;
        //move words that are "greater" than the key to one position ahead
        while (j >= 0 && get_Words()[j] > keyWord) {
            get_Words()[j + 1] = get_Words()[j];
            get_Freq()[j+1] = get_Freq()[j];
            j--;
        }
        get_Words()[j+1] = keyWord;
        get_Freq()[j+1] = keyFreq;
    }
}

bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords)
{

    // TODO

    return NULL;
}
bagOfWords::~bagOfWords() {
   delete [] _words;
   delete [] _frequencies;
   _size = 0;
   cout << "bagOfWords object destroyed." << endl;

}
// to search for a given word in _words - returns 0 if not found, 1 if found
int bagOfWords::binarySearchAndInsert (myString& wordToFind)
{
    return binarySearch(get_Words(), 0, get_size(), wordToFind);
}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString & newWord)
{
    _size++;

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {

    int numStopWords;
    char* token;
    myString* tokenString;

    //read the first number from the file that contains the number of stop words
    cin >> numStopWords;
    cout << "Number of Stop words: " << numStopWords << endl;
    myString* stopWordsList = new myString[numStopWords];

    //read the stop words
    for (int i=0; i < numStopWords; i++)
    {
        token = getNextToken ();
        stopWordsList[i] = token; //calls the overloaded = operator on myString class
    }

    //Now read a text and put them in the bagOfWords instance.
    bagOfWords* myBag = new bagOfWords ();

    while (token != NULL)
    {
        tokenString = new myString (token); //create a myString object with the token
        (*myBag).addWord(*tokenString); //add token to myBag
        token = getNextToken ();
    }

    // this should display the token and frequency;
    // note that becuase you are using binary search and insert the tokens will
    // be sorted alphabetically
    cout << endl;
    cout << "Input display:" << endl;
    (*myBag).display ();

    (*myBag).sortFreq ();
    cout << endl;
    cout << "myBag - Sorted based on frequency:" << endl;
    (*myBag).display ();

    (*myBag).sortWords();
    cout << endl;
    cout << "myBag - Sorted alphabetically:" << endl;
    (*myBag).display ();

    bagOfWords* newBag = (*myBag).removeStopWords(stopWordsList, numStopWords); // new parameter added here
    cout << endl;
    cout << "newBag - Sorted alphabetically:" << endl;
    (*newBag).display();

    (*newBag).sortFreq ();
    cout << endl;
    cout << "newBag - Sorted based on frequency:" << endl;
    (*newBag).display ();

    delete [] stopWordsList;
    delete myBag;
    delete newBag;

}

