// 8_1_17.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include "HashTable.h"
#include <string>

// This structure describes a single Person
struct Person
{
	string firstName;
	string lastName;
	char gender;
	int age;
	double height;
};

// Used to compare two Person objects. (p1 == p2)
bool operator==(const Person& p1, const Person& p2)
{
	return p1.firstName == p2.firstName &&
		p1.lastName == p2.lastName  &&
		p1.gender == p2.gender    &&
		p1.age == p2.age       &&
		p1.height == p2.height;
}

// Allows us to print Person objects using cout. E.g. cout << p << endl;
ostream& operator<<(ostream& out, const Person& p)
{
	out << "[" << p.firstName << ", "
		<< p.lastName << ", "
		<< p.gender << ", "
		<< p.age << ", "
		<< p.height << "]";
	return out;
}

// Fill a Person object with random data
void randPerson(Person& person)
{
	const string FIRST_NAMES[28] =
	{
		"Austin",  "Logan", "Nigel", "Vincent", "Zhizhan",
		"Sam", "Sarah", "Blake", "Daninthia", "Jose",
		"Erica", "Aaron", "Jacob", "Larenz", "Alexis",
		"Christopher", "Jasbir", "Jessica", "John", "Noah",
		"Daniel", "Ashley", "Kyle", "Derek", "Rafael",
		"Chelsea", "Matthew", "Ting"
	};

	const string LAST_NAMES[28] =
	{
		"Brown", "Campbell", "Castillo", "Chang", "Chen",
		"Collins", "Colpitts", "Fasse", "Fox", "Fraga",
		"Graham", "Green", "Hammers", "Hampton", "Jimenez",
		"Johnson", "Khatrao", "Mai", "Mangrum", "Paden",
		"Perez", "Ritchey", "Smith", "Taylor", "Toche",
		"Vang", "Ward", "Yan"
	};

	const char GENDERS[3] = { 'M', 'F', 'X' };

	person.firstName = FIRST_NAMES[rand() % 28];
	person.lastName = LAST_NAMES[rand() % 28];
	person.gender = GENDERS[rand() % 3];
	person.age = rand() % 100;
	person.height = (rand() / (double)RAND_MAX) * 6.5;
}

int hashFn(const Person& p)
{
	int num1 = hashFn(p.firstName);
	int num2 = hashFn(p.lastName);
	int num3 = hashFn((int)p.gender);
	int num4 = hashFn(p.age);
	int num5 = hashFn(p.height);

	return abs((7 * num1 + 9 * num2 + 13 * num3 + 17 * num4 + 31 * num5) * 31);
}

int main()
{
	HashTable<Person> table(100);
	Person person;
	
	for (int i = 0; i < 50; ++i)
	{
		randPerson(person);
		table.insert(person);
	}
	//table.print();
	cout << collisions << endl;
	/*cout << hashFn(4.2) << endl;
	cout << hashFn(4.3) << endl;

	cout << hashFn("Mom") << endl;
	cout << hashFn("Dad") << endl;

	HashTable<string> table(10);
	table.insert("Hello");
	table.insert("Goodbye");
	table.print();*/
    return 0;
}

