#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

extern string user;     // Username input string
extern string pass;     // Password input string
extern int caller;      // Variable for switch(caller) in main()
extern bool admin;      // Admin value

string error(string error);

int start(string prgm);
int stop(string sPrgm);
int add(int i1, int i2);
int wipe_ulib();
int make_admin(string userIn);
int minecraft(string mUser, string mPass);

//string cmd;

int cmd_line()
{
    string cmd;
    cout << "\nEnter Command: ";
    //getline (cin, cmd);
    cin >> cmd;
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
    else if (cmd == "start")                // Starts program
    {
        string program;
        cin >> program;
        start(program);
        return caller = 2;//Calls cmd_line()
    }
    else if (cmd == "stop")                 // Stops program
    {
        string program;
        cin >> program;
        stop(program);
        return caller = 2;//Calls cmd_line()
    }
    else if (cmd == "add")
    //else if (cmd.substr(0,3) == "add")
    {
        //cout << true;
        int x1, x2;
        cin >> x1 >> x2;
        cout << "\n> "
             << x1
             << " + "
             << x2
             << " = "
             << add(x1, x2)
             << endl;
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
        if (cmd == "sys")
        {
            string command;
            cin >> command;
            system(command.c_str());
            return caller = 2;//Calls cmd_line()
        }
        else if (cmd == "break")
        {
            cout << "\n> Breaking...\n";
            return caller = 0;//Breaks loop
        }
        else if (cmd == "wipe-ulib")
        {
            cout << "\n> Wipeing user library..."
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
                 << "'s user-type..."
                 << endl;
            make_admin(user);
            cout << "\n> "
                 << user
                 << "'s user-type changed to admin"
                 << endl;
            return caller = 2;//Calls cmd_line()
        }
        else if (cmd == "HS")
        //else if (cmd.substr(0,2) == "HS")
        {
            //cout << "\n> Entering haskell test...\n"
            //     << endl;
            return caller = 4;//Calls haskell()
        }
        else
        {
            error("cmdUnknown");
            return caller = 2;//Calls cmd_line()
        }
    }
    else
    {
        error("cmdUnknown");
        return caller = 2;//Calls cmd_line()
    }
}