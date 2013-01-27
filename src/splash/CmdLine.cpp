#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Foo_stub.h"

using namespace std;

extern string user;     // Username input string
extern string pass;     // Password input string
extern int caller;      // Variable for switch(caller) in main()
extern bool admin;      // Admin value

string error(string error);

int add(int i1, int i2);
int wipe_ulib();
int make_admin(string userIn);

int cmd_line(int argc, char *argv[])
{
    string cmd;
    cout << "Enter Command: ";
    getline (cin, cmd);
    //cin >> cmd;
    if (cmd == "help")
    {
        cout << "========\n"
             << "Commands\n"
             << "--------\n";
        return caller = 2;//Calls cmd_line()
    }
    else if (cmd == "logout")
    {
        cout << "\n> Logging out...\n"
             << endl;
        admin = false;
        cout << "> "
             << user
             << " logged out\n"
             << endl;
        return caller = 1;//Calls login()
    }
    else if (cmd.substr(0,3) == "add")
    {
        cout << true;
        //int x1, x2;
        //cin >> x1 >> x2;
        //cout << "\n> "
        //     << x1
        //     << " + "
        //     << x2
        //     << " = "
        //     << add(x1, x2)
        //     << "\n"
        //     << endl;
        return caller = 2;//Calls cmd_line()
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
            cout << "\n> Wipeing user library...\n"
                 << endl;
            wipe_ulib();
            admin = false;
            cout << "\n> User library wiped\n"
                 << endl;
            return caller = 1;//Calls login()
        }
    //}
        else if (cmd == "admin")
        {
            cin >> user;
            //cout << user;
            cout << "\n> Changing "
                 << user
                 << "'s user-type...\n"
                 << endl;
            make_admin(user);
            cout << "\n> "
                 << user
                 << "'s user-type changed to admin\n"
                 << endl;
            return caller = 2;//Calls cmd_line()
        }
        else if (cmd == "testHS")
        {
            string test;
            cout << "\nEnter word: ";
            getline (cin, test);
            hs_init(&argc, &argv);
            cout << "\n> Square of length is "
                 << test_hs(test.length())
                 << "\n"
                 << endl;
            hs_exit();
            return caller = 2;//Calls cmd_line()
        }
        else
        {
            cerr << error("cmdUnknown")
                 << endl;
            return caller = 2;//Calls cmd_line()
        }
    }
    else
    {
        cerr << error("cmdUnknown")
             << endl;
        return caller = 2;//Calls cmd_line()
    }
}