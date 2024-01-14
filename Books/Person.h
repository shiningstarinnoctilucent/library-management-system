#pragma once
#include <string>
using namespace std;

class Person
{
private:
	//Name
	string name;
	//Address
	string address;
	//Email
	string email;
public:
	string getName();
	string getAddress();
	string getEmail();
	void setName(string name);
	void setAddress(string address);
	void setEmail(string email);

	Person() = default;
};
