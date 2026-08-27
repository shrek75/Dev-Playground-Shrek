#include "UserInterface.h"
#include "UserData.h"
#include "MyList.h"

int main()
{
	MyList DB(new UserData());
	UserInterface UI(DB);
	UI.Run();

	return 0;
}