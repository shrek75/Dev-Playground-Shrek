#include <iostream>

using namespace std;

template<typename T>
class CMyArray
{
public:
	explicit CMyArray(int nSize)
		:m_nSize(nSize)
	{
		m_pData = new T[nSize];
	}

	~CMyArray()
	{
		if(m_pData != nullptr)
			delete[] m_pData;
	}

	//복사생성자
	CMyArray(const CMyArray& rhs)
		:CMyArray(rhs.m_nSize)
	{
		memcpy(m_pData, rhs.m_pData, sizeof(T) * m_nSize);
	}

	//대입연산자
	CMyArray& operator=(const CMyArray& rhs)
	{
		if (this == &rhs)
			return *this;

		if (m_pData != nullptr) delete[] m_pData;
		if (rhs.m_nSize != 0)
		{
			m_pData = new T[rhs.m_nSize];
			m_nSize = rhs.m_nSize;
			memcpy(m_pData, rhs.m_pData, rhs.m_nSize);
		}
		else
		{
			m_pData == nullptr;
			m_nSize = 0;
		}
		return *this;

	}
	//이동생성자
	CMyArray(CMyArray&& rhs)
	{
	//	operator=(rhs);

		m_pData = rhs.m_pData;
		m_nSize = rhs.m_nSize;

		rhs.m_pData = nullptr;
		rhs.m_nSize = 0;
	}

	//이동대입연산자
	CMyArray& operator=(CMyArray&& rhs)
	{
		delete[] m_pData;

		m_pData = rhs.m_pData;
		m_nSize = rhs.m_nSize;

		rhs.m_pData = nullptr;
		rhs.m_nSize = 0;
	}


	//배열연산자
	T& operator[](int nIndex)
	{
		return m_pData[nIndex];
	}

	const T& operator[](int nIndex) const
	{
		return m_pData[nIndex];
	}

private:
	T* m_pData = nullptr;
	int m_nSize = 0;
};

int main()
{
	const CMyArray<int> a(5);
	// a[0] = 1;
	// a[1] = 2;
	// a[2] = 3;
	// a[3] = 4;
	// a[4] = 5;

	CMyArray<int> b(a);
}