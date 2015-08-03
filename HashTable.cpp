#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
 int const Size = 15;

class _Hash{
private:
    struct item{
        string name, id;
        double cgpa;
        item* next;
    };

    item* HashTable[Size];

public:
    _Hash();
    int Hash(string key);                       ///Generates the Hash value and returns it
    int NumofItemsinIndex(int index);          /// A sub function to find out total entry on an index
    void PrintTable();                        ///Prints the HASH table
    void PrintAllUnderOneIndex(int a);       ///Prints all Entry under an Index
    void SearchIndex(string a);             ///Searching Function
    void AddItem(string name, string id, double cgpa);       ///new Entry
    void EditItemsInfo(string name, string id, double cgpa); ///To Edit an Entry
    void DeleteAnItem(string a);                           ///To delete an Entry
};

_Hash::_Hash(){     ///default Constructor

    for(int i=0; i<Size; i++){          ///giving a default value
        HashTable[i]       = new item;
        HashTable[i]->name = "Empty";
        HashTable[i]->id   = "Empty";
        HashTable[i]->cgpa = 0.00;
        HashTable[i]->next = NULL;
    }

}

int _Hash::Hash(string key){    ///Generates Hash key
    int k=0;                    ///this variable will be the total ascii value of key aka the name;
    for(int i=0; i<key.length(); i++)
        k+=(int)key[i];         ///adding

    int index = k%Size;        ///to get the index in between our HashTable's index Size
    return index;
}


void _Hash :: AddItem(string name, string id, double cgpa){ ///adding an item

    int index = Hash(name);    ///gets the index
    if(HashTable[index]->name == "Empty"){ ///if The index is empty this will be the first entry.
         HashTable[index]->name = name;
         HashTable[index]->id   = id;
         HashTable[index]->cgpa = cgpa;
    }

    else{     ///if the index has previous entry, this entry will be linked after the last one
        item* ptr = HashTable[index]; ///ptr is pointing the first entry
        item* n   = new item;        ///new node n
        n->name   = name;           ///lets put the given values
        n->id     = id;            ///name,id,cgpa
        n->cgpa   = cgpa;         ///as we are going to add this node to the last, its next pointer
        n->next   = NULL;        ///will point NULL
        while(ptr->next!=NULL)  ///this will run untill we reach the last node
            ptr = ptr->next;   ///lets go to the next node.
                              ///While loop Ends, whoa! we are in the last node
                             ///Even till now line ptr->next is NULL
            ptr->next = n;  ///we need to put out new node after the last one. Job Accomplished

    }


}


int _Hash::NumofItemsinIndex(int index){    ///returns the number of entry in an index
    int count = 0;                         ///Counter
    if(HashTable[index]->name=="Empty")   ///determines whether the index is empty or not
        return count;                    ///returns the number zero

    else{
        count++;                       ///so we are not empty Counter is 1
        item* ptr = HashTable[index]; ///ptr points the first node
        while(ptr->next!=NULL){      ///this will run untill we reach the last node
            count++;                ///keep incrementing our Counter
            ptr=ptr->next;         ///lets go to the next node.
        }                         ///While loop Ends
        return count;            ///returning the total number of existing nodes
    }
}

void _Hash::EditItemsInfo(string name, string id, double cgpa){  ///Edits information
    int index = Hash(name);                        ///gets the index
    int choice;
    if(HashTable[index]->name != "Empty"){       ///gets into if the index is not Empty
        if(NumofItemsinIndex(index)>1){         ///if the number of items in index is > 1
             item* ptr = HashTable[index];          ///Points the first node
             while(ptr->name!=name && ptr->next !=NULL)//(choice--)                       ///we need to go to the choice'th index
                ptr = ptr->next;                  ///so lets go
                                                 ///loop Ends, perhaps we are at the right position
            if(ptr->name==name){                ///checking whether its exact match or not
                ptr->id   = id;                ///time to put new values
                ptr->cgpa = cgpa;             ///id,cgpa
            }
            else
                cout<<"Not Found\n";
        }

        else{                              ///only one entry, so nothing to do much
            HashTable[index]->id   = id;   ///puting the new values
            HashTable[index]->cgpa = cgpa;///same here
        }
    }
    else
        cout<<"Not Found\n"; ///Not Found
}

void _Hash::PrintTable(){       ///prints the  total Hashtable

    for(int i=0; i<Size; i++){
        cout<<"|------------------\n";
        cout<<"| Index # "<<i<<endl;         ///Index Number
        cout<<"| Name = "<<HashTable[i]->name<<endl; ///Name
        cout<<"| ID   = "<<HashTable[i]->id<<endl; ///ID
        cout<<"| CGPA = "<<HashTable[i]->cgpa<<endl; ///CGPA
        cout<<"| # of total items = " <<NumofItemsinIndex(i)<<endl;
        cout<<"|--------------------\n";
    }
}

void _Hash::SearchIndex(string a){  ///Function for Searching
    int index = Hash(a);           ///gets the index
    item* ptr = HashTable[index]; ///points it

    if(ptr->name=="Empty")
        cout<<"index = "<<index<<" is Empty\nNotFound\n"; ///if not found

    else{
           while(ptr->name!=a && ptr->next!=NULL)
                ptr = ptr->next;

           if(ptr->name!=a)
                cout<<"Not Found\n";

           else{    ///printing informations
                cout<<"|----------------------\n";
                cout<<"| Name: "<<ptr->name<<endl;
                cout<<"| ID  : "<<ptr->id<<endl;
                cout<<"| CGPA: "<<ptr->cgpa<<endl;
                cout<<"|----------------------\n";
            }
    }

}
/*
Shubho -> 10/04/2015
https://sites.google.com/site/vinceandcode/data-structure/hash-table
*/
void _Hash::PrintAllUnderOneIndex(int a){
    int index = a;//Hash(a);
    if(HashTable[index]->name == "Empty")
        cout<<"Not Found\n";
    else{
        item* ptr = HashTable[index];
        while(ptr!=NULL){
        cout<<"=============================\n";
        cout<<"| Name : "<<ptr->name<<endl;
        cout<<"| ID   : "<<ptr->id<<endl;
        cout<<"| CGPA : "<<ptr->cgpa<<endl;
         ptr=ptr->next;
        }

    }
}

void _Hash::DeleteAnItem(string a){
    int index = Hash(a);
    if(HashTable[index]->name == "Empty")
        cout<<"Not Found\n";
    else if(NumofItemsinIndex(index)==1){   ///if index has only one Entry
        HashTable[index]->name = "Empty";  ///giving it the dafault value
        HashTable[index]->id   = "Empty";
        HashTable[index]->cgpa = 0.00;
        HashTable[index]->next = NULL;
    }
    else{
        item* ptr = HashTable[index];
        item* prev;     ///this pointer will keep the track of previous node of ptr's currently pointed node

        while(ptr->name!=a && ptr!=NULL){
            prev = ptr; /// follows ptr
            ptr=ptr->next; ///ptr is pointing the next node but prev not
        }

        if(ptr->next!=NULL){///if its not the last node
             ptr->name = ptr->next->name;
             ptr->id   = ptr->next->id;
             ptr->next = ptr->next->next;
         }
         else{ ///this is the last node
             prev->next=NULL; ///so if we set prev's next is null the last node will be out of our linked list
         }
    }

}

int main(){

    _Hash ob;

    int choice, index;
    string a,b;
    double c;
    //freopen("input.txt","r",stdin);
    cout<<"press\n1 to Add Items\n2 to Search\n3 to Edit Items\n4 to Print Table\n";
    cout<<"5 to delete an Item\n6 to view all elements\n7 to exit\n";

    while(cin>>choice){
        switch(choice){
        case 1:
            cout<<"Enter Name, ID, CGPA\nType quit to exit\n";
           while(1){
                cout<<"Name : ";cin>>a;
                if(a=="quit")break;
                cout<<"ID   : ";cin>>b;
                if(b=="quit")break;
                cout<<"CGPA : ";cin>>c;
                ob.AddItem(a,b,c);
           }
            break;
        case 2:
            cout<<"Search for Student by name\n";
            cin>>a;
            ob.SearchIndex(a);
            break;
        case 3:
            cout<<"Enter the name, of then node that you want to edit\n";
            cin>>a>>b>>c;///actually we can add more flexiblity here
                        ///like what if i don't wanna chage the ID, only the CGPA
                       ///that just needs more 5 or 6 lines of code
                      ///for now, lets skip that
            ob.EditItemsInfo(a,b,c);
            break;
        case 4:
            ob.PrintTable();
            break;
        case 5:
            cout<<"Enter the name, that you want to delete its info\n";
            cin>>a;
            ob.DeleteAnItem(a);
            break;
        case 6:
            cout<<"To view all the info under one index, Enter the index number: ";
            cin>>index;
            ob.PrintAllUnderOneIndex(index);
            break;
        case 7:
            exit(1);
        default:
            cout<<"Wrong Input, try again\n";
        }
    }//end of while
    return 0;
}
