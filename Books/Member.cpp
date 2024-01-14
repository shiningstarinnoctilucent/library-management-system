#include "Member.h"
#include "Book.h"

Member::Member(int memberId, string name, string address, string email)
{
	this->memberId = memberId;
	this->setName(name);
	this->setAddress(address);
	this->setEmail(email);
}

int Member::getMemberId()
{
	return memberId;
}

vector<Book> Member::getBooksBorrowed()
{
	return booksLoaned;
}

void Member::setBooksBorrowed(vector<Book> book)
{
	this->booksLoaned = book;
}
