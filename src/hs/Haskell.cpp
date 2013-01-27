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

int haskell(int argc, char *argv[])
{
    string cmd;
    cout << "Enter Haskell Command: ";
    getline (cin, cmd);
    if (cmd == "test")
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
        return caller = 4;//Calls haskell()
    }
    else if (cmd == "return")
    {
    	cout << "\n> Returning to command line...\n"
    		 << endl;
    	return caller = 2;//Calls cmd_line()
    }
    else
    {
    	cout << error("cmdUnknown")
    		 << endl;
    	return caller = 4;//Calls haskell()
    }
}