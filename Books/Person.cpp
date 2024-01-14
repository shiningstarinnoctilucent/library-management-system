#include "Person.h"

string Person::getName()
{
	return (name);
}

string Person::getAddress()
{
	return (address);
}

string Person::getEmail()
{
	return (email);
}

void Person::setName(string name)
{
	this->name = name;
}

void Person::setAddress(string address)
{
	this->address = address;
}

void Person::setEmail(string email)
{
	this->email = email;
}
