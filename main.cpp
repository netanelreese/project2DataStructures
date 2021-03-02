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
    strArray = new char[0];
    strArray[0] = ' ';
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
    strArray = NULL;
    size = B.size;
    strArray = new char[size+1];
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
    size = stringLength(B);
    strArray = new char[size];
    for(int i = 0; i < size; i++) {
        strArray[i] = B[i];
    }
    return *this; //returning the output object
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
    if(this == &B) {
        return *this;
    }
    delete [] strArray;
    strArray = NULL;
    size = B.size;
    strArray = new char[size + 1];
    emptyString(strArray, size + 1);
    stringCopy(B.strArray, size, strArray);

    return *this; //returning the output object
}

// checking if two myString objects are the same - return true or false
bool myString::operator==(myString& B) {
    if (this->Size() != B.Size()) {
        return false; //if the sizes do not equal eachother automatically return false
    }
    else {
        for (int i = 0; i < Size(); ++i) {
            if (B.getWord()[i] != this->getWord()[i]) {
                return false;
            }
        }
    }
    return true;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator<(myString& B) {
    if (Size() == B.Size()) {
        for (int i = 0; i < Size(); ++i) {
            if (getWord()[i]<B.getWord()[i]) {
                return true;
            }
            else if(getWord()[i] > B.getWord()[i]) {
                return false;
            }
        }
        return false;
    }
    else if (Size() < B.Size() || Size() > B.Size()) {
        int smaller;
        if (Size() < B.Size()) {
            smaller = Size();
        }
        else {
            smaller = B.Size();
        }
        for (int i = 0; i < smaller; ++i) {
            if(getWord()[i] < B.getWord()[i]) {
                return true;
            }
            else if(getWord()[i] > B.getWord()[i]) {
                return false;
            }
        }
        return (Size() < B.Size());
    }
    else {
        return false;
    }
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator>(myString& B) {
    if (Size() == B.Size()) {
        for (int i = 0; i < Size(); ++i) {
            if (getWord()[i] > B.getWord()[i]) {
                return true;
            }
            else if(getWord()[i] < B.getWord()[i]) {
                return false;
            }
            else return false;
        }
    }
    else if (Size() < B.Size() || Size() > B.Size()) {
        int smaller;
        if (Size() < B.Size()) {
            smaller = Size();
        }
        else {
            smaller = B.Size();
        }
        for (int i = 0; i < smaller; ++i) {
            if(getWord()[i] > B.getWord()[i]) {
                return true;
            }
            else if (getWord()[i] < B.getWord()[i]) {
                return false;
            }
        }
        return (Size() > B.Size());

    }
    else {
        return true;
    }
}
myString::~myString() {
    delete [] strArray; //deleting the array
    size = 0; //setting the size to 0
    //cout << "myString object destroyed." << endl; //confirmation that object is destroyed
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
    int middle;
    if(left <= right) {
        middle = (left + right)/2;
        //Checking if the element is present at middle loc
        if(arr[middle] == stringNeeded){
            return middle;
        }

            //Checking if the search element is present in greater half
        else if(arr[middle] < stringNeeded){
            return binarySearch(arr,middle+1,right,stringNeeded);
        }

            //Checking if the search element is present in lower half
        else{
            return binarySearch(arr,left,middle-1,stringNeeded);
        }
    }
    return -1;
    }


void sort(int* freq, myString* words, int n) {
        int i, j, key;
        myString* wordKey;
        for (i = 1; i < n; i++){
            key = freq[i];
            wordKey = new myString(words[i]);
            j = i - 1;

            while (j >= 0 && freq[j] > key)
            {
                freq[j + 1] = freq[j];
                words[j + 1] = words[j];
                j = j - 1;
            }
            freq[j + 1] = key;
            words[j + 1] = *wordKey;
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
    bagOfWords(bagOfWords &bag); //copy constructor
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

    for(int i = 0; i < _size; ++i) {
        _words[i] = "";
        _frequencies[i] = 0;
    }
}
bagOfWords::bagOfWords(bagOfWords &bag) {
    _size = bag.get_size();
    _words = new myString[_size];
    _frequencies = new int[_size];

    for(int i = 0; i < _size; ++i)_words[i] = bag.get_Words()[i];
    for(int j = 0; j < _size; ++j)_frequencies[j] = bag.get_Freq()[j];
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
    cout << "Bag of Words: " << get_size() << endl; //giving a title to the bag of words with size
    for (int i = 0; i < _size; ++i) {
        cout << get_Words()[i] << ": " << get_Freq()[i] << endl; //displays each word and their frequency
    }
}

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq()
{
    sort(_frequencies, _words, _size); //calling the bubble sort on both the frequency array and the words array
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords(){
    int i, j, key;
    myString* wordKey;
    for (i = 1; i < _size; i++){
        key = _frequencies[i];
        wordKey = new myString(_words[i]);
        j = i - 1;

        while (j >= 0 && _words[j] > *wordKey)
        {
            _frequencies[j + 1] = _frequencies[j];
            _words[j + 1] = _words[j];
            j = j - 1;
        }
        _frequencies[j + 1] = key;
        _words[j + 1] = *wordKey;
    }
}

bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords){
    // TODO
    int numWordsRemoved = 0;
    bagOfWords* newBag = new bagOfWords(_size);
    int inArr;
    int j = 0;

    for(int i = 0; i < numStopWords; ++i){
        inArr = binarySearch(_words, 0, _size, stopWords[i]);
        while(inArr != -1 && j < _size) {
            if (stopWords[i] == get_Words()[j]) {
                _words[i] = "";
                _frequencies[i] = 0;
            }
            ++j;
            inArr = binarySearch(_words, 0, _size, stopWords[i]);
        }
        j = 0;
    }
    sortWords();
    for (int i = 0; i < newBag->get_size(); ++i)newBag->_words[i] = _words[i];

    return newBag;
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
    if(_size == 0) {
        delete [] _words;
        delete [] _frequencies;
        _size++;
        _words = new myString[_size];
        _frequencies = new int[_size];
        _words[0] = " ";
        _words[0] = wordToFind;
        _frequencies[0] = 1;
        return 0;
    }
    else{
        int index = binarySearch(_words, 0, _size - 1, wordToFind);
        if (index == -1) {
            myString* newWords = new myString[_size + 1];
            for(int i = 0; i < _size + 1; ++i) newWords[i] = " ";
            for(int j = 0; j < _size; ++j)newWords[j] = _words[j];
            _words = newWords;
            int i = _size - 1;
            while (i >= 0 && wordToFind < _words[i]) {
                _words[i + 1] = _words[i];
                _frequencies[i + 1] = _frequencies[i];
                --i;
            }
            _words[i + 1] = wordToFind;
            _frequencies[i + 1] = 1;
            _size++;


            return 0;
        }
        else {
            _frequencies[index]++;
            return 1;
        }
    }
}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString & newWord)
{
    binarySearchAndInsert(newWord);
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

    token = getNextToken (); // v2: this was the error.

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

