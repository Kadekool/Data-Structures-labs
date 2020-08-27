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
    //check=check->next;
    //
    while(check!=NULL){
        string store=check->name;
        //cout<<store<<endl;
        if(store==countryName){
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
    Country* check;
    check=head;

    if(check==NULL){
        cout<<"Empty list"<<endl;
    }else{

        Country *location=searchNetwork(receiver);

        if(location==NULL){
            cout<<"Country not found"<<endl;
        }else{

            //Country* check;
            //check=head;

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
    cout<<"== CURRENT PATH =="<<endl;
    Country* check=head;
    bool nothing=false;
    while(check!=NULL){
        nothing =true;
        cout<<check->name<<" -> ";
        check=check->next;
    }
    if(nothing==true){
       cout<<"NULL"<<endl; 
    }else{
        cout<<"nothing in path"<<endl;
    }
    cout<<"==="<<endl;
}

string upperMake(string one){
    string letter=one.substr(1,one.length()-1);
    char upper=one[0];
    upper=toupper(upper);
    one=upper+letter;
    return one;
}


/************************************************
           Definitions for main.cpp
************************************************/
void displayMenu()
{
    // COMPLETE
    bool repeat=true;
    CountryNetwork Count;
    while(repeat){
    string choic;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
    getline(cin,choic);
    int choice=stoi(choic);
    
    
    if(choice==1){
    Count.loadDefaultSetup();
    
    Count.printPath();
   
    }else if(choice==2){
        Count.printPath();
    }else if(choice==3){
        string one;
        string two;
        cout<<"Enter name of the country to receive the message:"<<endl;
        getline(cin,one);
        //cout<<"countryname"<<one<<endl;
        cout<<"Enter the message to send:"<<endl<<endl;
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
        Count.printPath();
        
    }else{
        cout << "Quitting..." << endl;
        cout << "Goodbye!" << endl;
        repeat=false;
    }
    }
    
}
int main(){
    displayMenu();
}
    

