#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;



extern string user;		// Username input string
extern string pass;		// Password input string

string chkUser;			// Username check string
string chkPass;			// Password check string
string chkType;			// User type check string
string holdHash;		// Hash holder

int add(int i1, int i2)
{
    return i1 + i2;
}

int wipe_ulib()
{
	ofstream userLib;
	userLib.open("lib/ulib");
	userLib.close();
}

unsigned int make_hash(string hashIn)
{                                    //APHash, algorithim by Arash Partow
    unsigned int hash = 0xAAAAAAAA;
    for (int i = 0; i < hashIn.length(); i++)
    {
        hash ^= ((i & 1) == 0) ?
                ((hash << 7) ^ hashIn[i] * (hash >> 3)) :
                (~((hash << 11) + (hashIn[i] ^ (hash >> 5))));
    }                                //End APHash algorithim
    stringstream hashOut;
    hashOut << hash;
    holdHash = hashOut.str();
}

int create_user()
{
    ofstream userLib;
    userLib.open("lib/ulib", fstream::app);
    make_hash(user);
    userLib << holdHash
            << ":";
    make_hash(pass);
    userLib << holdHash
            << "!";
    make_hash(holdHash.substr(0, 3));//Normal password hash section
    userLib << holdHash
            << "\n";
    userLib.close();
}

int make_admin(string userIn)
{
    fstream userLib;
    userLib.open("lib/ulib");
    string holdUser;
    int colon;
    int exPoint;
    make_hash(userIn);
    while (userLib >> holdUser)
    {
    	int inputLoc = userLib.tellg();
    	//cout << "\n" << inputLoc << "\n";
        colon = holdUser.find(':');
        exPoint = holdUser.find('!');
        chkUser = holdUser.substr(0, colon);
        chkPass = holdUser.substr(colon + 1, exPoint - (colon + 1));
        chkType = holdUser.substr(exPoint + 1, holdUser.length() - (exPoint + 1));
        if (holdHash == chkUser)
        {
            make_hash(chkPass.substr(3, 3));//Admin password hash section
            userLib.seekp(inputLoc - (holdUser.length() - exPoint));
            userLib << holdHash;
        }
    }
    userLib.close();
}

int check_login()
{
    ifstream userLib;
    userLib.open("lib/ulib"); 
    string holdUser;
    int colon;
    int exPoint;
    make_hash(user);
    while (userLib >> holdUser)
    {
        colon = holdUser.find(':');
        exPoint = holdUser.find('!');
        chkUser = holdUser.substr(0, colon);
        chkPass = holdUser.substr(colon + 1, exPoint - (colon + 1));
        chkType = holdUser.substr(exPoint + 1, holdUser.length() - (exPoint + 1));
        if (holdHash == chkUser)
        {
            make_hash(pass);
            if (holdHash == chkPass)
            {
                make_hash(chkPass.substr(0, 3));//Normal password hash section
                if (holdHash == chkType) return 0;
                else
                {
                    make_hash(chkPass.substr(3, 3));//Admin password hash section
                    if (holdHash == chkType) return 2;
                    else return 1;
                }
            }
            else return 1;
        }
             
        //cout << "\nholdUser: " << holdUser << '\n';
        //cout << "\nholdPass: " << holdPass << '\n';
    }
    userLib.close();       
    //if (userInput == "tyler") return true;
    //else return false;
}