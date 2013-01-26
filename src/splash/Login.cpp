#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

extern int caller;      // Variable for switch(caller) in main()

string user;            // Username input string
string pass;            // Password input string
bool admin = false;     // Admin value

string error(string error);

int check_login();

int login()
{
    cout << "> Type 'new' to create new user, or enter username.\n\n"
         << "Username: ";
    cin >> user;
    if (user == "new")
    {
        return caller = 3;//Calls new_user()
    }
    //else if (user == "break") return caller = 0;
    else
    {
        if (user != "")
        {
            cout << "\nPassword: ";
            cin >> pass;
            if (check_login() == 0)//Normal user login
            {
                cout << '\n'
                     << "> Logged in "
                     << user
                     << "\n\n";
                return caller = 2;//Calls splash()
            }
            else if (check_login() == 2)
            {
                cout << "\n> Logged in admin "
                     << user
                     << "\n\n";
                admin = true;
                return caller = 2;//Calls splash()
            }
            else
            {
                cerr << error("badLogin");
                return caller = 1;//Calls login()
            }
        }
        else
        {
            cerr << error("emptyUser");
            return caller = 1;//Calls login()
        }
    }             
}