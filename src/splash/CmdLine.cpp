#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

extern string user;     // Username input string
extern string pass;     // Password input string
extern int caller;      // Variable for switch(caller) in main()
extern bool admin;      // Admin value

string error(string error);

int add(int i1, int i2);
int wipe_ulib();
int make_admin(string userIn);

int cmd_line()
{
    string cmd;
    cout << "Enter Command: ";
    cin >> cmd;
    if (cmd == "help")
    {
        cout << "========\n"
             << "Commands\n"
             << "--------\n";
        return caller = 2;//Calls splash()
    }
    else if (cmd == "logout")
    {
        cout << "\n> Logging out...";
        admin = false;
        cout << "\n> "
             << user
             << " logged out\n\n";
        return caller = 1;//Calls login()
    }
    else if (cmd == "add")
    {
        int x1, x2;
        cin >> x1 >> x2;
        cout << "\n> "
             << x1
             << " + "
             << x2
             << " = "
             << add(x1, x2)
             << "\n\n";
        return caller = 2;//Calls splash()
    }
    //  else if (cmd == "reddit")
    //{
    //       string sub;
    //       cin >> sub;
    //       getReddit();
    //}
    else if (admin)
    {
        if (cmd == "break")
        {
            cout << "\n> Breaking...\n";
            return caller = 0;//Breaks loop
        }
        else if (cmd == "wipe-ulib")
        {
            cout << "\n> Wipeing user library...\n\n";
            wipe_ulib();
            admin = false;
            cout << "\n> User library wiped\n\n";
            return caller = 1;//Calls login()
        }
    //}
        else if (cmd == "admin")
        {
            cin >> user;
            //cout << user;
            cout << "\n> Changing "
                 << user
                 << "'s user-type...\n\n";
            make_admin(user);
            cout << "\n> "
                 << user
                 << "'s user-type changed to admin\n\n";
            return caller = 2;//Calls splash()
        }
    }
    else
    {
        cerr << error("cmdUnknown");
        return caller = 2;//Calls splash()
    }
}