#include <iostream>
#include <exception>
#include "ogre_application.h"

using namespace std;

/* Macro for printing exceptions */
#define PrintException(exception_object)\
	cerr << exception_object.what() << endl

int main(int argc, char *argv[])
{
    ogre_application::OgreApplication application;

	try
	{
		application.Initialize();
		application.MainLoop();
	}
	catch (exception &e)
	{
		PrintException(e);
		getchar();
	}
	
	return 0;
}