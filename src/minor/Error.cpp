#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string error(string error)
{
	string userExists = 	"\n------------------------------\nError: Username already exists\n------------------------------\n";
	string passMismatch = 	"\n----------------------------\nError: Passwords don't match\n----------------------------\n";
	string badLogin = 		"\n----------------------\nError: Incorrect login\n----------------------\n";
	string emptyUser = 		"\n-------------------------\nError: Must type username\n-------------------------\n";
	string prgmUnknown = 	"\n----------------------\nError: Unknown Program\n----------------------\n";
	string cmdUnknown = 	"\n----------------------\nError: Unknown Command\n----------------------\n";

	string errorErr = 		"\n-----------------\nError: in error()\n-----------------\n";

	if 		(error == "userExists") 	cerr << userExists;
	else if (error == "passMismatch") 	cerr << passMismatch;
	else if (error == "badLogin") 		cerr << badLogin;
	else if (error == "emptyUser") 		cerr << emptyUser;
	else if (error == "prgmUnknown")	cerr << prgmUnknown;
	else if (error == "cmdUnknown") 	cerr << cmdUnknown;
	else 								cerr << errorErr;
}