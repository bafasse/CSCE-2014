
#include <iostream>
using namespace std;

class Foo
{
public:
	//Default Constructor
	Foo();

	//Non Default Constructor- Call them explicitly
	Foo(int x);
	Foo(string w);

	//Copy Constructor
	Foo(const Foo& orig);

	//Destructor
	~Foo();

	int getX() const;
	void setX(const int _x);

private:
	string w;
	int x;

};

int Foo::getX() const
{

}

void Foo::setX(const int _x)
{
	//private = public
	x = _x;
}

template <class T>
struct Point3D
{
	T x,y,z;
};

Foo createFoo()
{
	Foo f;
	return f;
}

int main()
{
	Point3D<int> p1;
	Point3D<double> p2;
	p1.x = 5;
	p2.y = 7.2;

	Foo f;
	Foo g(5); //Non Default
	Foo h(g); //Copy

	int* ptr1 = new int;
	int* ptr2 = new int[10];
	*ptr1 = 5;
	*ptr2 = 7;
	cout << *ptr1 << endl;
	ptr2[5] == *(ptr2 + 5) == *(5 + ptr2) == 5[ptr2];
	delete ptr1;
	delete[] ptr2;
}