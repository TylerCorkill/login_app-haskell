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
    cout << "> Type 'new' to create new user, or enter username.\n"
         << endl
         << "Username: ";
    getline (cin, user);
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
            getline (cin, pass);
            if (check_login() == 0)//Normal user login
            {
                cout << '\n'
                     << "> Logged in "
                     << user
                     << "\n"
                     << endl;
                return caller = 2;//Calls cmd_line()
            }
            else if (check_login() == 2)
            {
                cout << "\n> Logged in admin "
                     << user
                     << "\n"
                     << endl;
                admin = true;
                return caller = 2;//Calls cmd_line()
            }
            else
            {
                cerr << error("badLogin")
                     << endl;
                return caller = 1;//Calls login()
            }
        }
        else
        {
            cerr << error("emptyUser")
                 << endl;
            return caller = 1;//Calls login()
        }
    }             
}