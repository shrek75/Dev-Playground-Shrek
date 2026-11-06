#include <iostream>
#include <chrono>
#include <conio.h>

int main()
{
	

	std::chrono::steady_clock clock;
	auto startTime = clock.now(); //프로그램 시작 시간
	auto nowTime = clock.now();   //프로그램 현재 시간
	auto inputTime = clock.now();
	auto inputdms = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - startTime);
	bool perfect = false;

	

	while (1)
	{	
		nowTime = clock.now();
		auto dms = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - startTime);
		if (_kbhit())
		{
			inputdms = dms;
			_getch();

			if (inputdms.count() % 1000 < 100 || inputdms.count() % 1000 > 900)
				perfect = true;
			else perfect = false;
		}

		
		
		system("cls");
		printf("%02lld:%03lld\n", dms.count() / 1000, dms.count() % 1000);
		printf("%02lld:%03lld\n", inputdms.count() / 1000, inputdms.count() % 1000);
		if (perfect)
			printf("PERFECT !!!\n");
		else printf("FAIL...\n");
	}

	return 0;



}