#include "Librarian.h"
#include <iostream>
#include "Member.h"

Librarian::Librarian()
{
}

Librarian::Librarian(int staffId, string name, string address, string email, int salary)
{
	this->staffId = staffId;
	this->salary = salary;
	this->setName(name);
	this->setAddress(address);
	this->setEmail(email);
}

int Librarian::getStaffId()
{
	return staffId;
}

void Librarian::setStaffId(int staffId)
{
this->staffId = staffId;
}

int Librarian::getSalary()
{
	return 0;
}

void Librarian::setSalary(int salary)
{
	this->salary = salary;
}

