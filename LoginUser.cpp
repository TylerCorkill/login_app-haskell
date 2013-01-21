#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>

using namespace std;

string user;            // Username input string
string pass;            // Password input string
string holdUser;        // Username check string
string holdPass;        // Password check string
int loginAuth = 0;      // Login Authenticator



int check_login(string userIn, string passIn)
{
    ifstream loginLib;
    loginLib.open("logins.txt");
    string holdWord;
    int colon;
    while (loginLib >> holdWord)
    {
          colon = holdWord.find(':');
          holdUser = holdWord.substr(0, colon);
          holdPass = holdWord.substr(colon + 1, holdWord.length());
          if (holdUser == userIn)
          {
             if (holdPass == passIn) return 0;
             else return 1;
          }
             
          //cout << "\nholdUser: " << holdUser << '\n';
          //cout << "\nholdPass: " << holdPass << '\n';
    }
    loginLib.close();       
    //if (userInput == "tyler") return true;
    //else return false;
}

int create_user(string nUserIn, string nPassIn)
{
    ofstream loginLib;
    loginLib.open("logins.txt", fstream::app);
    loginLib << nUserIn
             << ":"
             << nPassIn
             << endl;
    loginLib.close();
    cout << "\n"
         << nUserIn
         << " created!\n\n";
}

int new_user()
{
    string newUser;
    string newPass;
    string newPass2;
    string nullPass = "";
    cout << "\n\nType 'cancel' to return to login\n"
         << "\nEnter desired username: ";
    cin >> newUser;
    if (newUser == "cancel")
    {
                cout << "\nCanceled\n";
                return loginAuth = 1;
    }
    else if (check_login(newUser, nullPass) == 1)
    {
       cerr << "\nError: Username already exists\n";
       return loginAuth = 1;
    }
    else
    {
        cout << "\nEnter desired password: ";
        cin >> newPass;
        cout << "\nConfirm desired password: ";
        cin >> newPass2;
        if (newPass != newPass2)
        {
                    cerr << "\nPasswords don't match\n";
                    return loginAuth = 1;
        }
        else
        {
            create_user(newUser, newPass);
            return loginAuth = 1;
        }
    }
}

int login()
{
    cout << "\nType 'new' to create new user, or enter username.\n"
         << "\nUsername: ";
    cin >> user;
    if (user == "new")
    {
             new_user();
    }
    //else if (user == "test") check_lib(user);
    else
    {
        if (user != "")
        {
           cout << "\nPassword: ";
           cin >> pass;
           if (check_login(user, pass) == 0)
           {
              cout << "\nAccess Granted\n\n"
                   << "Welcome, "
                   << user
                   << "\n";
              return loginAuth = 2;
           }
           else
           {
               cerr << "\nError: Incorrect login\n\n";
               return loginAuth = 1;
           }
        }
        else
        {
            cerr << "\nError: Must type username\n\n";
            return loginAuth = 1;
        }
    }             
}

int splash()
{
    string cmd;
    string logout = "logout";
    cout << "\n\nEnter Command: ";
    cin >> cmd;
    if (cmd == "help") cout << "Commands\n"
                            << "--------\n"
                            << logout
                            << " - Logs user out\n";
    else if (cmd == logout)
    {
         cout << "\nLogging out...\n\n";
         login();
    }
    else
    {
        cout << "\n\nError: Command Unknown";
        splash();
    }
}

char hold()
{
    char hold;
    cin >> hold;
    return hold;
}

int main()
{
    login();
    if (loginAuth == 1)                 // value 1 restarts login()
    {
       loginAuth = 0;
       main();
    }
    else if (loginAuth == 2)            // value 2 starts splash()
    {
         splash();
    }
    if (hold() == 'r') main();
}
