#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>

/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
    // TODO
    head=NULL;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    // TODO
    if(previous!=NULL){
        Country* newOne=new Country;
        newOne->name=countryName;
        newOne->next=previous->next;
        previous->next=newOne;
        cout << "adding: " << countryName << " (prev: " << previous->name <<
        ")" << endl;
    }else{
        Country* firstOne=new Country;
        firstOne->next=head;
        firstOne->name=countryName;
        head=firstOne;
        cout << "adding: " << countryName << " (HEAD)" << endl;
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    // TODO
    insertCountry(head,"United States");
    Country *next=searchNetwork("United States");
    insertCountry(next,"Canada");
    next=searchNetwork("Canada");
    insertCountry(next,"Brazil");
    next=searchNetwork("Brazil");
    insertCountry(next,"India");
    next=searchNetwork("India");
    insertCountry(next,"China");
    next=searchNetwork("China");
    insertCountry(next,"Australia");
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    // TODO
    Country *check;
    check=head;
    while(check!=NULL){
        if(check->name==countryName){
            return check;
        }else{
            check=check->next;
        }
    }
    return NULL;
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    // TODO
    if(head==NULL){
        cout<<"Empty list"<<endl;
    }else{
        //cout<<"here1"<<endl;
        Country *location=searchNetwork(receiver);
        // cout<<"here2"<<endl;
        if(location==NULL){
            cout<<"Country not found"<<endl;
        }else{
            // cout<<"here3"<<endl;
            Country* check;
            check=head;
            // cout<<"here4"<<endl;
            while(location->name!=check->name){
                check->numberMessages++;
                check->message=message;
                cout << check->name << " [# messages received: " <<
                check->numberMessages << "] received: " << check->message << endl;
                check=check->next;
            }
            if((location->name==check->name)){
                location->numberMessages++;
                location->message=message;
                cout << check->name << " [# messages received: " <<
                location->numberMessages << "] received: " << location->message << endl;
            }
        }
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    Country* check;
    while(check->next!=NULL){
        cout<<check->name<<"->"<<endl;
        check=check->next;
    }
}

string upperMake(string one){
    string letter=one.substr(1,one.length()-1);
    char upper=one[0];
    upper=toupper(upper);
    one=upper+letter;
    return one;
}

void CountryNetwork::deleteCountry(string countryName){
    Country *location=searchNetwork(countryName);
    if(location==NULL){
        cout<<"Country does not exist."<<endl;
        return;
    }
    Country *lead=head;
    if(head==location){
        head=location->next;
        delete location;
    }else{
        lead=lead->next;
        Country *behind=head;
        while(lead!=location){
            lead=lead->next;
            behind=behind->next;
        }
        behind->next=lead->next;
        delete lead;
    }
}
#include <vector>

bool CountryNetwork::detectLoop(){
    Country *loop=head;
    vector <Country *> store;
    while(loop!=NULL){
        loop=loop->next;
        for(int i=0;i<store.size();i++){
            Country *temp=store[i];
            if(loop==temp){
                return true;
            }
        }
    Country *stored=loop;
    store.push_back(stored);
    }
    return false;
    
}
void CountryNetwork::deleteEntireNetwork(){
    Country *traverse=head;
    while(traverse!=NULL){
        Country *next=traverse->next;
        cout<<"deleting: "<<traverse->name<<endl;;
        deleteCountry(traverse->name);
        traverse=next;
    }
    cout<<"Deleted network"<<endl;
}


Country* CountryNetwork:: createLoop(string countryName){
    Country *location=searchNetwork(countryName);
    if(location==NULL){
        Country *check=head;
        while(check->next!=NULL){
            check=check->next;
        }
        return check;
    }else{
        Country *loop=location;
        while(loop->next!=NULL){
            loop=loop->next;
        }
        loop->next=location;
        return loop;
    }
}
void CountryNetwork::readjustNetwork(int startIndex, int endIndex){
    //cout<<startIndex<<" "<<endIndex<<endl;
    Country *adj=head;
    Country *adj2=head;
    Country *adj3=head;
    Country *final=head;
    if(head==NULL){
        cout<<"Linked List is Empty"<<endl;
        return;
    }
    if(endIndex<=0||startIndex<0){
        cout<<"Invalid end index"<<endl;
        //cout<<"here1"<<endl;
        return;
    }
    if(startIndex>endIndex){
        cout<<"Invalid indices"<<endl;
        return;
    }
    int count=0;
    while(final->next!=NULL){
        final=final->next;
        count++;
        //cout<<count<<endl;
    }
    if(endIndex>count){
        cout<<"Invalid end index"<<endl;
        return;
    }
    for(int i=0;i<startIndex;i++){
        adj=adj->next;
        if(i!=0){
            adj2=adj2->next;
        }
    }
    for(int i=0;i<endIndex;i++){
        adj3=adj3->next;
    }
    if(adj==head){
        head=adj3->next;
        final->next=adj;
        adj3->next=NULL;
    }else{
    //cout<<adj2->name<<" "<<adj3->name<<endl;
        adj2->next=adj3->next;
        final->next=adj;
        adj3->next=NULL;
    }
}
    
/************************************************
           Definitions for main.cpp
************************************************/
void displayMenu()
{
    // COMPLETE
    int choice;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
    cin>>choice;
    bool repeat=true;
    CountryNetwork Count;
    while(repeat){
        if(choice==1){
        Count.loadDefaultSetup();
    }else if(choice==2){
        Count.printPath();
    }else if(choice==3){
        string one;
        string two;
        cout<<"Enter name of the country to receive the message:"<<endl;
        getline(cin,one);
        cout<<"Enter the message to send:"<<endl;
        getline(cin,two);
        Count.transmitMsg(one,two);
    }else if(choice==4){
        string one;
        string two;
        cout<<"Enter a new country name:"<<endl;
        getline(cin,one);
        one=upperMake(one);
        cout<<"Enter the previous country name (or First):"<<endl;
        getline(cin,two);
        two=upperMake(two);
        string three;
        bool continu=false;
        if(Count.searchNetwork(two)==NULL&&two!="First"){
            continu=true;
        }
        while(continu==true){
            cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
            getline(cin,three);
            three=upperMake(three);
            if(three=="First"||Count.searchNetwork(three)!=NULL){
                continu=false;
                two=three;
            }
        }
        Count.insertCountry(Count.searchNetwork(two),one);
        
    }else if(choice==5){
        cout << "Quitting..." << endl;
        cout << "Goodbye!" << endl;
        repeat=false;
    }
    }
    
}
int main(){
    displayMenu();
}


