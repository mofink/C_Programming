//assert.h standard header


//if NDEBUG is defined before including <assert.h> then we disable assertions 
//because of this, each time <assert.h> is included its behavior can vary, unlike most other header files 

//to turn on assertions, use  
//#define NDEBUG
//#include <assert.h>

//(Not a problem to redefine macros according to the C standard)

//to turn off, use 
//#undef NDEBUG
//#include <assert.h>

#undef assert //remove previous definition, if exists

#ifdef NDEBUG //turned off
#define assert(condition) ((void)0) //https://stackoverflow.com/a/25021889/6521643
#else //turned on
	void _Assert(char *);
	#define _STR(x) _VAL(x) //these two lines convert __LINE__ to string literal
	// "#" is the stringizing operator -- https://www.geeksforgeeks.org/and-operators-in-c/
	#define _VAL(x) #x 
	//https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
	#define assert(condition) ((condition) ? ((void)0) : _Assert(__FILE__ ":" _STR(__LINE__) " " #condition))
#endif


////////////////////////////////////////////////

//Normally we would store this "hidden" function in another file to make the headers independent of each other

//#include <assert.h>
#include <stdio.h> //fputs()
#include <stdlib.h> //abort()

void _Assert(char *) //print assertion message and abort
{
	fputs(message,stderr);
	fputs("assertion failed\n",stderr);
	abort();
}




