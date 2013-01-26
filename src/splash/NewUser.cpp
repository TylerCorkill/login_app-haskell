#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

extern string user;     // Username input string
extern string pass;     // Password input string
extern string chkPass;  // Password check string
extern int caller;      // Variable for switch(caller) in main()

string error(string error);

int check_login();
int create_user();

int new_user()
{
    cout << "\n\n> Type 'cancel' to return to login\n"
         << "\nEnter desired username: ";
    cin >> user;
    if (user == "cancel")
    {
        cout << '\n'
             << "> Canceling...\n\n";
        return caller = 1;//Calls login()
    }
    else if (check_login() == 1 || 2)
    {
        cerr << error("userExists");
        return caller = 3;//Calls new_user()
    }
    else
    {
        cout << "\nEnter desired password: ";
        cin >> pass;
        cout << "\nConfirm desired password: ";
        cin >> chkPass;
        if (pass != chkPass)
        {
            cerr << error("passMismatch");
            return caller = 3;//Calls new_user()
        }
        else
        {
            cout << "\n> Creating user "
                 << user
                 << "\n\n";
            create_user();
            cout << "\n> User "
                 << user
                 << " created!\n\n";
            return caller = 1;//Calls login()
        }
    }
}