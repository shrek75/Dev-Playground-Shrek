#include "UserInterface.h"
#include "MyList.h"

int main()
{
	MyList DB;
	UserInterface UI(DB);
	UI.Run();

	return 0;
}