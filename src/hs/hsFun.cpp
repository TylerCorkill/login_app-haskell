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

int open_hask(int argc, char *argv[])
{
	hs_init(&argc, &argv);
#ifdef __GLASGOW_HASKELL__
	hs_add_root(__stginit_Foo);
#endif
	//test_hs();
}
int close_hask(int argc, char *argv[])
{
	hs_exit();
}