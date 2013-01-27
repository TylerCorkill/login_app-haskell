#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include <HsFFI.h>
#ifdef __GLASGOW_HASKELL__
#include "Foo_stub.h"
extern "C" void __stginit_Foo(void);
#endif
#include <stdio.h>

using namespace std;

class HS
{
	string haskStr;
public:
	int sqr_length(int argc, char *argv[])
	{
		hs_init(&argc, &argv);
	#ifdef __GLASGOW_HASKELL__
		hs_add_root(__stginit_Foo);
	#endif
		cout << test_hs(haskStr.length());
		hs_exit();
	}
};