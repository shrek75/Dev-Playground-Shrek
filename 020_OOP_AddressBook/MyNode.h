#pragma once
class MyNode
{
	friend class MyList;
	
private:
	MyNode* _next;

public:
	MyNode();
	virtual ~MyNode();

	MyNode* GetNext() const { return _next; }

	//관리를 위해 꼭 필요한 인터페이스 함수들을 순수가상함수로 선언
	virtual const char* GetKey() = 0;
	virtual void PrintNode() = 0;

};

