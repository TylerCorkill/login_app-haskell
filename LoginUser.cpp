#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string user;            // Username input string
string pass;            // Password input string
string chkUser;         // Username check string
string chkPass;         // Password check string
string holdHash;        // Hash holder
int caller = 1;         // Variable for switch(caller) in main()



//Called independently
//--------------------
unsigned int make_hash(string hashIn)                  //APHash, algorithim by Arash Partow
{
    unsigned int hash = 0xAAAAAAAA;
    for (int i = 0; i < hashIn.length(); i++)
    {
        hash ^= ((i & 1) == 0) ?
                ((hash << 7) ^ hashIn[i] * (hash >> 3)) :
                (~((hash << 11) + (hashIn[i] ^ (hash >> 5))));
    }
    stringstream hashOut;
    hashOut << hash;
    holdHash = hashOut.str();
}

int check_login()
{
    ifstream loginLib;
    loginLib.open("ulib"); 
    string holdUser;
    int colon;
    make_hash(user);
    while (loginLib >> holdUser)
    {
          colon = holdUser.find(':');
          chkUser = holdUser.substr(0, colon);
          chkPass = holdUser.substr(colon + 1, holdUser.length());
          if (holdHash == chkUser)
          {
             make_hash(pass);
             if (holdHash == chkPass) return 0;
             else return 1;
          }
             
          //cout << "\nholdUser: " << holdUser << '\n';
          //cout << "\nholdPass: " << holdPass << '\n';
    }
    loginLib.close();       
    //if (userInput == "tyler") return true;
    //else return false;
}

int create_user()
{
    ofstream loginLib;
    loginLib.open("ulib", fstream::app);
    make_hash(user);
    loginLib << holdHash
             << ":";
    make_hash(pass);
    loginLib << holdHash
             << "\n";
    loginLib.close();
    cout << "\n> User "
         << user
         << " created!\n\n";
}    
//---------------------------------------------




//Called with switch(caller)
//--------------------------------------------
int splash()
{
    string cmd;
    string logout = "logout";
    cout << "Enter Command: ";
    cin >> cmd;
    if (cmd == "help")
    {
            cout << "========\n"
                 << "Commands\n"
                 << "--------\n"
                 << logout
                 << " - Logs user out\n";
            return caller = 2;//Calls splash()
    }
    else if (cmd == logout)
    {
         cout << '\n'
              << "> Logged out "
              << user
              << "\n\n";
         return caller = 1;//Calls login()
    }
    else
    {
        cerr << '\n'
             << "----------------------\n"
             << "Error: Unknown Command\n"
             << "----------------------\n\n";
        return caller = 2;//Calls splash()
    }
}

int new_user()
{
    pass = "";
    cout << "\n\n> Type 'cancel' to return to login\n"
         << "\nEnter desired username: ";
    cin >> user;
    if (user == "cancel")
    {
                cout << '\n'
                     << "> Canceled\n\n";
                return caller = 1;//Calls login()
    }
    else if (check_login() == 1)
    {
       cerr << '\n'
            << "------------------------------\n"
            << "Error: Username already exists\n"
            << "------------------------------\n\n";
       return caller = 3;//Calls new_user()
    }
    else
    {
        cout << "\nEnter desired password: ";
        cin >> pass;
        cout << "\nConfirm desired password: ";
        cin >> chkPass;
        if (pass != chkPass)
        {
                    cerr << '\n'
                         << "----------------------------\n"
                         << "Error: Passwords don't match\n"
                         << "----------------------------\n\n";
                    return caller = 3;//Calls new_user()
        }
        else
        {
            create_user();
            return caller = 1;//Calls login()
        }
    }
}

int login()
{
    cout << "> Type 'new' to create new user, or enter username.\n\n"
         << "Username: ";
    cin >> user;
    if (user == "new")
    {
             return caller = 3;//Calls new_user()
    }
    else
    {
        if (user != "")
        {
           cout << "\nPassword: ";
           cin >> pass;
           if (check_login() == 0)
           {
              cout << '\n'
                   << "> Logged in "
                   << user
                   << "\n\n";
              return caller = 2;//Calls splash()
           }
           else
           {
               cerr << '\n'
                    << "----------------------\n"
                    << "Error: Incorrect login\n"
                    << "----------------------\n\n";
               return caller = 1;//Calls login()
           }
        }
        else
        {
            cerr << '\n'
                 << "-------------------------\n"
                 << "Error: Must type username\n"
                 << "-------------------------\n\n";
            return caller = 1;//Calls login()
        }
    }             
}
//-------------------------------------------------




char hold()
{
    char hold;
    cin >> hold;
    return hold;
}

int main()
{
    switch (caller)
    {
           case 1:               //Calls login()
                caller = 1;
                login();
                main();
                break;
           case 2:               //Calls splash()
                caller = 1;
                splash();
                main();
                break;
           case 3:               //Calls new_user()
                caller = 1;
                new_user();
                main();
                break;
    }
    if (hold() == 'r') main();
}
