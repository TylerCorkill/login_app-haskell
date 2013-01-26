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
         << endl
         << "Enter desired username: ";
    getline (cin, user);
    if (user == "cancel")
    {
        cout << '\n'
             << "> Canceling...\n"
             << endl;
        return caller = 1;//Calls login()
    }
    else if (check_login() == 1 || 2)
    {
        cerr << error("userExists")
             << endl;
        return caller = 3;//Calls new_user()
    }
    else
    {
        cout << endl
             << "Enter desired password: ";
        getline (cin, pass);
        cout << endl
             << "Confirm desired password: ";
        getline (cin, chkPass);
        if (pass != chkPass)
        {
            cerr << error("passMismatch")
                 << endl;
            return caller = 3;//Calls new_user()
        }
        else
        {
            cout << "\n> Creating user "
                 << user
                 << "\n"
                 << endl;
            create_user();
            cout << "\n> User "
                 << user
                 << " created!\n"
                 << endl;
            return caller = 1;//Calls login()
        }
    }
}