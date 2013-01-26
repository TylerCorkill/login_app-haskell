#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string error(string error)
{
	string userExists = "\n------------------------------\nError: Username already exists\n------------------------------\n\n";
	string passMismatch = "\n----------------------------\nError: Passwords don't match\n----------------------------\n\n";
	string cmdUnknown = "\n----------------------\nError: Unknown Command\n----------------------\n\n";
	string badLogin = "\n----------------------\nError: Incorrect login\n----------------------\n\n";
	string emptyUser = "\n-------------------------\nError: Must type username\n-------------------------\n\n";

	string errorErr = "\n-----------------\nError: in error()\n-----------------\n\n";

	if (error == "userExists") return userExists;
	else if (error == "passMismatch") return passMismatch;
	else if (error == "cmdUnknown") return cmdUnknown;
	else if (error == "badLogin") return badLogin;
	else if (error == "emptyUser") return emptyUser;
	else return errorErr;
}