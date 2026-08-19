#include <iostream>
using namespace std;

class MyQueue
{
private:
	int* _arr;
	int _front; //한칸앞 가리킴
	int _back;  //새로 push할 곳 가리킴

public:
	MyQueue()
	{
		_arr = new int[10001];
		_front = 0;
		_back = 1;
	}

	void Push(int n)
	{
		// 다찼으면
		if (_front == _back) return;
		_arr[_back] = n;
		_back = (_back + 1) % 10001;
	}

	void Pop()
	{
		//큐가 비어있다면
		if ((_front + 1)%10001 == _back)
		{
			cout << "-1\n";
			return;
		}

		_front = (_front + 1) % 10001;
		cout << _arr[_front] << '\n';
		return;
	}

	void Size()
	{
		
		//cout << _count << '\n';
		return;
	}

	void Empty()
	{
		if (_count == 0)
		{
			cout << "1\n";
		}
		else cout << "0\n";
		return;
	}

	void Top()
	{
		if (_count == 0)
		{
			cout << "-1\n";
			return;
		}

		cout << _arr[_count - 1] << '\n';
		return;
	}
};


int main()
{	
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	MyQueue queue;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		if (str == "push")
		{
			int n;
			cin >> n;
			queue.Push(n);
		}
		else if (str == "pop")
		{
			queue.Pop();
		}
		else if (str == "size")
		{
			queue.Size();
		}
		else if (str == "empty")
		{
			queue.Empty();
		}
		else if (str == "top")
		{
			queue.Top();
		}
	}
	

	return 0;
}
