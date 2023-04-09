#include<iostream>
using namespace std;
class Employee
{
	int _id;
	string _name;
public:
	Employee(int id,string name):_id(id),_name(name)
	{}
	void Show()
	{
		cout << "Employee Id:" << _id << "\nEmployee Name:" << _name << endl;
	}
};
class RefCount
{
	int _count;
public:
	RefCount():_count(0)
	{}
	void AddCount()
	{
		++_count;
	}
	int ReleaseCount()
	{
		return --_count;
	}
	int GetCount()
	{
		return _count;
	}
};
template<typename T>
class MyShared
{
	T* _ptr;
	RefCount* _pcount;
public:
	MyShared(T* ptr = nullptr) :_ptr(ptr)
	{
		_pcount = new RefCount;
		_pcount->AddCount();
	}
	T operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	MyShared(const MyShared<T>& robj)
	{
		_ptr = robj._ptr;
		_pcount = robj._pcount;
		_pcount->AddCount();
	}
	MyShared<T>& operator=(const MyShared<T>& robj)
	{
		if (this != &robj)
		{
			if (_pcount->ReleaseCount == 0)
			{
				delete _ptr;
				delete	_pcount;
			}
			_ptr = robj._ptr;
			_pcount = robj._pcount;
			_pcount->AddCount();
		}
	}
	int UseCount()
	{
		return _pcount->GetCount();
	}
	~MyShared()
	{
		if (_pcount->ReleaseCount() == 0)
		{
			delete _ptr;
			delete _pcount;
		}
	}
};
int main()
{
	MyShared<Employee> emp1(new Employee(101, "Rajesh"));
	emp1->Show();

	return 0;
}