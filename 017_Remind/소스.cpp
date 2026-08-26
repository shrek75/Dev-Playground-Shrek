#include <iostream>
#include <memory>

using namespace std;

class CMyData
{
public:
	CMyData()
	{
		cout << "CMyData" << endl;
	}

	~CMyData()
	{
		cout << "~CMyData()" << endl;
	}
};

int main()
{	
	{
		cout << "start!" << endl;
		shared_ptr<CMyData> ptr1(new CMyData);

		cout << ptr1.use_count() << endl;

		{
			shared_ptr<CMyData> ptr2 = ptr1;
			cout << ptr1.use_count() << endl;

		}
		cout << ptr1.use_count() << endl;
	}
	cout << "end!" << endl;
	
	unique_ptr<CMyData> ptr3(new CMyData);
	// unique_ptr<CMyData> ptr4 = ptr3;
	return 0;
}