#include <fstream>

using namespace std;

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