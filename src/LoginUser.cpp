#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string user;            // Username input string
string pass;            // Password input string
string pin;             // Pin input string
string chkUser;         // Username check string
string chkPass;         // Password check string
string chkType;         // User type check string
string holdHash;        // Hash holder
int caller = 1;         // Variable for switch(caller) in main()
bool admin = false;     // Admin value




//Called independently
//--------------------
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
                make_hash(holdHash.substr(0, 3));
                if (holdHash == chkType) return 0;
                else
                {
                    make_hash(pin);
                    if (holdHash == chkType) return 0;
                    else return 2;
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
    make_hash(holdHash.substr(0, 3));
    userLib << holdHash
            << "\n";
    userLib.close();
    cout << "\n> User "
         << user
         << " created!\n\n";
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
        colon = holdUser.find(':');
        exPoint = holdUser.find('!');
        chkUser = holdUser.substr(0, colon);
        chkType = holdUser.substr(exPoint + 1, holdUser.length() - (exPoint + 1));
        if (holdHash == chkUser)
        {
            cout << "> Making account "
                 << userIn
                 << " admin...\n\n"
                 << "> Enter "
                 << userIn
                 << "'s admin pin: ";
            cin >> pin;
            make_hash(pin);
            userLib.seekg(exPoint + 1);
            userLib << holdHash;
            cout << "\n\n> "
                 << userIn
                 << " is now an admin\n\n";
        }
    }
    pin = "";
}
//---------------------------------------------



//Command functions
//-----------------
int wipe_ulib();

int add(int i1, int i2);

//int getReddit();
//-----------------

//Called with switch(caller)
//--------------------------------------------
int splash()
{
    pin = "";
    string cmdUnknown = "\n----------------------\nError: Unknown Command\n----------------------\n\n";
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
        cout << '\n'
             << "> Logged out "
             << user
             << "\n\n";
        admin = false;
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
    }
    //  else if (cmd == "reddit")
    //{
    //       string sub;
    //       cin >> sub;
    //       getReddit();
    //}
    else if (cmd == "admin")
    {
        if (admin)
        {
            cin >> user;
            make_admin(user);
        }
        else
        {
            cout << cmdUnknown;
        }
        return caller = 2;//Calls splash()
    }
    else if (cmd == "wipe-ulib")
    {
        if (admin)
        {
            cout << "\n> Wipeing user library...\n\n";
            wipe_ulib();
            admin = false;
            return caller = 1;//Calls login()
        }
        else
        {
            cout << cmdUnknown;
            return caller = 2;//Calls splash()
        }
    }
    else if (cmd == "break")
    {
        if (admin)
        {
            cout << "\n> Breaking...\n";
            return caller = 0;//Breaks loop
        }
        else
        {
            cout << cmdUnknown;
            return caller = 2;//Calls splash()
        }
    }
    else
    {
        cerr << cmdUnknown;
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
    //else if (user == "break") return caller = 0;
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
            else if (check_login() == 2)
            {
                cout << "\nAdmin pin: ";
                cin >> pin;
                if (check_login() == 0)
                {
                    cout << "\n> Logged in admin "
                         << user
                         << "\n\n";
                    admin = true;
                    return caller = 2;//Calls splash()
                }
                else
                {
                    cout << "\n> Bad pin\n\n";
                    return caller = 1;//Calls login()
                }
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
        default:
            return 0;
            break;
    }
    if (hold() == 'r') main();
    return 0;
}
