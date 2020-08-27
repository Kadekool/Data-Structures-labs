#include <ios>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

// this is reference for reading a file word by word  (Can be used for reading both stop words and unique words)

struct wordItem {
    string word;
    int count;
};

bool isStopWord(string word, string ignoreWords[])
{
    for(int i=0;i<50;i++){
        if(ignoreWords[i]==word){
            return true;
        }
    }
    return false;
}

void printNext10(wordItem wordItemList[], int startRank, int totalWords)
{
    //int i=0;
    //int x=0;
    //while(i<10){
        //bool check = isStopWord(wordItemList[startRank+x], wordItemList);
        //if(!check){
    //}
    if(startRank+10<=totalWords){
        for(int i=startRank;i<startRank+10;i++){
            double mult=10000*((double)wordItemList[i].count / totalWords);
            mult=round(mult);
            mult=mult/10000;
            string store=to_string(mult);
            store=store+"00";
            std::cout<<store.substr(0,6)<<" - "<< wordItemList[i].word<<endl;
        }
    }else{
        for(int i=startRank;i<totalWords;i++){
            double mult=10000*((double)wordItemList[i].count / totalWords);
            mult=round(mult);
            mult=mult/10000;
            string store=to_string(mult);
            store=store+"00";
            cout<<store.substr(0,6)<<" - "<< wordItemList[i].word<<endl;
        }
    }
}



void arraySort(wordItem uniqueWords[], int length){
    for(int i=0;i<length-1;i++){
        for(int k=0;k<length-i-1;k++){
            //cout<<uniqueWords[k].count<<endl;
            if(uniqueWords[k].count<uniqueWords[k+1].count){
                wordItem temp=uniqueWords[k];
                uniqueWords[k]=uniqueWords[k+1];
                uniqueWords[k+1]=temp;
            }
        }
        
    }
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int
length){
    int count=0;
    for(int i=0;i<length;i++){
        if(uniqueWords[i].word!=uniqueWords[i+1].word){
            count+=uniqueWords[i].count;
        }
    }
    return count;
}

void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
    string filename=ignoreWordFileName;
    string word;
    ifstream inStream;      // stream for reading in file
    inStream.open(filename); // open the file
    int i=0;
    while (inStream >> word){
        ignoreWords[i]=word;
        i++;
    }
}

wordItem* resize(wordItem* arrayPtr, int &capacity)
{
    int newCapacity =2*capacity;
    wordItem *newArray =new wordItem [newCapacity];
    for(int i=0;i<capacity;i++){
        *(newArray+i)=*(arrayPtr+i);
    }
    delete [] arrayPtr;
    capacity = newCapacity;

    return newArray;

}



int checkUnique(wordItem uniqueWords[],wordItem newOne, int length){
    for(int i=0;i<length;i++){
        if(newOne.word==uniqueWords[i].word){
            uniqueWords[i].count++;
            //cout<<"count:"<<uniqueWords[i].count<<endl;
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[] ){
    string filename=argv[2];
    ifstream inStream;      // stream for reading in file
    inStream.open(filename); // open the file
    int capacity=100;
    wordItem *Arr = new wordItem[capacity];
    string Ignore[50];
    string word;
    int doubling=0;
    int i=0;
    int count=0;
    const char *ignoreWordFileName = argv[3];
    getStopWords(ignoreWordFileName, Ignore);
    //for(int i=0;i<50;i++){
        //cout<<Ignore[i]<<endl;
    //}
    while (inStream >> word ){
        wordItem W={word,1};
        bool add=isStopWord(W.word, Ignore);
        bool add2=false;
        if(i>0){
            //arraySort(Arr,i);
            add2=checkUnique(Arr,W,i);
        }
        
        if(!add&&!add2){
            Arr[i]=W;
            i++;
            if(i==capacity){
               Arr=resize(Arr,capacity);
               doubling++;
               //cout<<doubling<<endl;
            }
         // get stop words / unique words into array
        }
    }
    
    int tot=getTotalNumberNonStopWords(Arr,i);
    cout<<"Array doubled: "<<doubling<<endl<<"#"<<endl;
    cout<<"Unique non-common words: "<<i<<endl<<"#"<<endl;
    cout<<"Total non-common words: "<<tot<<endl<<"#"<<endl;
    arraySort(Arr,i);
    cout<<"Probability of next 10 words from rank "<<argv[1]<<endl<<"---------------------------------------"<<endl;
    string store=argv[1];
    int stored=stoi(store);
    printNext10(Arr,stored,tot);
    
    inStream.close(); // close the file
}

