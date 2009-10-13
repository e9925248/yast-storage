
#include <StorageInterface.h>


namespace storage
{

    struct TestEnvironment : public Environment
    {
	TestEnvironment() : Environment(false)
	{
	    testmode = true;
	    autodetect = false;
	    logdir = testdir = "tmp";
	}
    };

}
