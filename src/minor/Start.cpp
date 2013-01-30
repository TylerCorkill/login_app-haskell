#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

string error(string error);

int start(string prgm)
{
	if (prgm == "minecraft")
	{
		string mUser, mPass;
        cout << "\nUsername: ";
        cin >> mUser;
        cout << "Password: ";
        cin >> mPass;
        cout << "\n> Launching minecraft..."
        	 << endl;
        string mineLogin = "minecraft ";
        	   mineLogin += mUser;
        	   mineLogin += " ";
        	   mineLogin += mPass;
    	system(mineLogin.c_str());
	}
	else error("prgmUnknown");
}