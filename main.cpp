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
    myString (); //default constructor
    myString(char* inpStr); //copy constructor from char array
    myString (myString& B); //copy constructor from myString object
    int Size(); //returns the size of this string object
    char* getWord(); //returns the strArray object
    bool operator == (myString& B); //operator to see if two strings are equal
    bool operator > (myString& B); //operator to see if this string is greater than the input string
    bool operator < (myString& B); //operator to see if this string is less than the input string
    myString& operator = (myString& B); //assignment operator from myString object
    myString& operator = (char* B); //assignment operator from char array object
    ~myString(); //destructor
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
    strArray = nullptr; //setting the strArray to null
    size = B.size; //setting size equals to input object size
    strArray = new char[size+1]; //initializing the new array object
    emptyString(strArray, size+1); //emptying string
    stringCopy (B.strArray, size, strArray); //copying string ovwer
}

char* myString::getWord()
{
    return strArray; //returns the char array that represents the string of this object
}

// getter for size of myString
int myString::Size () {
    return size; //returns sizze of this string object
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
        return *this; //if the two strings are equals to eachother dont bother with copying it over
    }
    delete [] strArray; //delete the array if it holds anything
    strArray = nullptr; //set the array equals to null
    size = B.size; //set sizes equals to eachother
    strArray = new char[size + 1]; //initializing the array to miss out on all the garbage in the string
    emptyString(strArray, size + 1); //empty this sttring
    stringCopy(B.strArray, size, strArray); //copy the string over

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
                return false; //if any of the characters dont equal eachother return false
            }
        }
    }
    return true; //else return true
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator<(myString& B) {
    if (Size() == B.Size()) {
        for (int i = 0; i < Size(); ++i) {
            if (getWord()[i]<B.getWord()[i]) {
                return true; //if any character is less than return true
            }
            else if(getWord()[i] > B.getWord()[i]) {
                return false; //else return false
            }
        }
        return false; //else return false
    }
    else if (Size() < B.Size() || Size() > B.Size()) { //if the sizes do not equal you wanna iterate over the smaller ones size
        int smaller;
        if (Size() < B.Size()) { //setting smaller size equal to smaller
            smaller = Size();
        }
        else {
            smaller = B.Size();
        }
        for (int i = 0; i < smaller; ++i) { //iterating over the two words
            if(getWord()[i] < B.getWord()[i]) {
                return true; //if any character is less than return true
            }
            else if(getWord()[i] > B.getWord()[i]) {
                return false; //else return false
            }
        }
        return (Size() < B.Size()); //if all of the characters of the smaller string is equal to the first few
        //characters of the bigger string return which one is smaller (true if this* is smaller, false if not)
    }
    else {
        return false; //failsafe return false
    }
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator>(myString& B) { //the methodology for this operator is the same as the previous
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

int binarySearch(myString* arr, int left, int right, myString& stringNeeded) { //binary search algorithm
    int middle; //making middle variable
    if(left <= right) { //to make sure the arrayt isnt screwy
        middle = (left + right)/2;
        //Checking if the element is at the middle thingy
        if(arr[middle] == stringNeeded){
            return middle;
        }

            //checking if element is in right half
        else if(arr[middle] < stringNeeded){
            return binarySearch(arr,middle+1,right,stringNeeded);
        }

            //Checking string needed is in left half
        else{
            return binarySearch(arr,left,middle-1,stringNeeded);
        }
    }
    return -1; //NOT FOUND!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 0_0
    }


void sort(int* freq, myString* words, int n) { //insertion sort of frequencies
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
    _size = numOfWords; //setting size equal to input num
    _words = new myString[numOfWords]; //initializing both arrays
    _frequencies = new int[numOfWords];

    for(int i = 0; i < _size; ++i) { //initializing each variable of both arrays
        _words[i] = "";
        _frequencies[i] = 0;
    }
}
bagOfWords::bagOfWords(bagOfWords &bag) { //non default copy constructor
    _size = bag.get_size(); //initialize all elements of bag over
    _words = new myString[_size];
    _frequencies = new int[_size];

    for(int i = 0; i < _size; ++i)_words[i] = bag.get_Words()[i]; //copy each element of bag over
    for(int j = 0; j < _size; ++j)_frequencies[j] = bag.get_Freq()[j];
}
myString* bagOfWords::get_Words()
{
    return _words; //get words arr
}

int* bagOfWords::get_Freq()
{
    return _frequencies; //get the frequencies thing
}

int bagOfWords::get_size()
{
    return _size; //return size of bag
}

void bagOfWords::setSize(int i)
{
    _size = i; //setting size
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
    sort(_frequencies, _words, _size); //calling the insertion sort on both the frequency array and the words array
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords(){ //sorting words using insertion sort;
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

bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords) { //remove all words in stopWords from this _words and put them in a new bag
    bagOfWords* newBag = new bagOfWords(); //new gucci bag
    bool found = false; //initializing this variable to see if the words equal eachother to prevent adding

    for(int i = 0; i < _size-1; ++i) {
        for(int j = 0; j < numStopWords; ++j) {

            if (_words[i] == stopWords[j]) {
                found = true; //if they equal then get that outta here
            }
        }
        if (!found) for(int k = 0; k < _frequencies[i]; ++k) newBag->addWord(_words[i]); //if found = false add the word to the bag
        found = false; //reset found var
    }

    return newBag; //return this bag
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
    if(_size == 0) { //if size = 0 then go in and initialize all the necessary fields and add the word
        delete [] _words;
        delete [] _frequencies;
        _size++;
        _words = new myString[_size];
        _frequencies = new int[_size];
        _words[0] = " ";
        _words[0] = wordToFind;
        _frequencies[0] = 1;
        return 0; //return zero because the word was not found
    }
    else{
        int index = binarySearch(_words, 0, _size - 1, wordToFind); //using binary search to find the element's index
        if (index == -1) { //if word is not found need to insert the word in alphabetical order
            myString* newWords = new myString[_size + 1]; //initialize a new _words var
            for(int i = 0; i < _size + 1; ++i) newWords[i] = " ";
            for(int j = 0; j < _size; ++j)newWords[j] = _words[j]; //copy each element over
            _words = newWords; //set them equal to eachother
            int i = _size - 1; //initialize the while loop
            while (i >= 0 && wordToFind < _words[i]) {
                _words[i + 1] = _words[i]; //scooch each element over until the word is in the right spot
                _frequencies[i + 1] = _frequencies[i];
                --i;
            }
            _words[i + 1] = wordToFind; //place the element in the right spot
            _frequencies[i + 1] = 1; //set frequency at this index equal to 1 since the word is added
            _size++; //increment size

            return 0; //return 0 since word wasnt found
        }
        else {
            _frequencies[index]++; //increment at this index to account for repeated word being added again
            return 1; //return one since word was found
        }
    }
}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString & newWord)
{
    binarySearchAndInsert(newWord); //adds a word in alphabetical order using binarysearch and insert
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
        delete [] token;
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


    delete tokenString;
    delete [] stopWordsList;
    delete myBag;
    delete newBag;

}

