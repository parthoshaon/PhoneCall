#include <bits/stdc++.h>
#define BUF cin.ignore(256, '\n')
using namespace std;


class callDuration
{
    public:
        int time;
        callDuration* next;
        callDuration* prev;
};


class User
{
    public:
        string phoneNumber;
        string name;
        callDuration* head = NULL;

        void makeCall();
        void userDetails();
        void callDeurationList();
        void deleteCallDeurations(int position);
        void searchCallDuration(int position);
};


void User::userDetails()
{
    cout << "User's Name: " << name << endl;
    cout << "User's Phone Number: " << phoneNumber << endl;
    cout << name <<"'s" << " todays all call duration lists: \n";

    callDeurationList();
}


void User::callDeurationList()
{
    int count = 1;
    callDuration* node = head;
    callDuration* last;

    while (node != NULL)
    {
        cout << count << ". " << node->time << "s, \n";
        last = node;
        node = node->next;

        count++;
    }

    cout << endl << endl;
}


void User::makeCall()
{
    int newTime = (rand()) % 3600;

    callDuration** temporaryHead = &head;
    callDuration* newCallDuration = new callDuration();

    newCallDuration->time = newTime;
    newCallDuration->next = (*temporaryHead);
    newCallDuration->prev = NULL;

    if ((*temporaryHead) != NULL)  (*temporaryHead)->prev = newCallDuration;

    (*temporaryHead) = newCallDuration;
}


void deleteNow(callDuration** temporaryHead, callDuration* del)
{
    if(*temporaryHead == NULL || del == NULL)
        return;

    if(*temporaryHead == del)
        *temporaryHead = del->next;

    if(del->next != NULL)
        del->next->prev = del->prev;

    if(del->prev != NULL)
        del->prev->next = del->next;


    free(del);

    cout << "Deletion Successful\n";
}


void User::deleteCallDeurations(int position)
{
    int i;

    callDuration** temporaryHead = &head;

    if (*temporaryHead == NULL || position <= 0)
        return;

    callDuration* current = *temporaryHead;

    for(int i = 1; current != NULL && i < position; i++) {
        current = current->next;
    }

    if (current == NULL)
        return;

    deleteNow(temporaryHead, current);
}


void User::searchCallDuration(int position)
{
    int count = 1;

    callDuration* temporaryHead = head;
    callDuration* current = temporaryHead;

    while (current != NULL)
    {
        if(count == position) {
            cout << endl << "You have talked " << current->time << "s in your "
                << "No." << position << " call\n";

            return;
        }

        count++;
        current = current->next;
    }

    assert(0);
}



int main() {

    int totalUser, flag = 2;
    cout << "How many users are initially in the database?" << endl;
    cin >> totalUser;

    User object[totalUser];

    
    for(int i = 0; i < totalUser; i++) {
        cout << "\n\n\n\nNumber " << i+1 << "." << endl;
        cout << "Type user's first name: ";
        cin >> object[i].name;
        cout << "Type user's phone number: ";
        cin >> object[i].phoneNumber;
        cout << "==============================================\n\n\n\n\n\n";
    }

    
    for(int i = 0; i < totalUser; i++) {
            
        cout << "                   >> Attention <<               \n\n"
            "Now for the testing purpose the program will show all\nthe users one by one and for some time you "
            << "have to assume\nthat you are the specific user\n\n";
        cout << "No. " << i+1 << endl;
        cout << "Hello " << object[i].name << ", this is your phonebook. "
            << "Do you want to make a phone call?\nType 1 for YES\nType 2 for NO\n";
    

        cin >> flag;
        int total = 1;
        while(flag == 1) 
        {
            object[i].makeCall();
            cout << "\n\n\n\n\n\n\n\nYou made " << total << " phonecall. Which was for "
            << object[i].head->time << "s\n\n" << "Do you want another?\n";
            cin >> flag;
            total++;
        }

        
        cout << endl << endl << endl << endl << object[i].name << ", today you've made " << total-1
        << " phonecalls.\nHere's the call duration lists:\n";
        object[i].callDeurationList();
        cout << "\n\n\n\n\n\n\n\nDo you want to delete any item?\nIf yes enter it's position "
            << "number\nFor the position see above\nElse type 0\n";
            
            
        cin >> flag;
        if(flag != 0) {
            cout << "\n\n";
            object[i].deleteCallDeurations(flag);
            cout << endl << endl << object[i].name << " here's your call duraton lists after deleting the "
            << "No." << flag << " position item:\n";
            object[i].callDeurationList();
        }

        else cout << "\nNothing is deleted\n";
        

        cout << "\n\n\n\n\n\n\n\nDo you want to see any specific call duration?\nEnter the position "
        << "number\nElse type 0\n";
        BUF;
        
        
        cin >> flag;
        if(flag != 0) {
            object[i].searchCallDuration(flag);
        }

        cout << "===============================================\n\n\n\n";
    }

    return 0;
}
