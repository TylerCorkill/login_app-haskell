#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int caller = 1;				// Variable for switch(caller) in main()

int login();
int cmd_line();
int new_user();

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
        case 2:               //Calls cmd_line()
            caller = 1;
            cmd_line();
            main();
            break;
        case 3:               //Calls new_user()
            caller = 1;
            new_user();
            main();
            break;
        default:              //Breaks
            return 0;
            break;
    }
    if (hold() == 'r') main();
    return 0;
}