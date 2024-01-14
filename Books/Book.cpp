#include "book.h"
#include "Member.h"

Book::Book(int bookID, string bookName, string authorFirstName, string authorLastName,string bookType)
{
	this->bookID = bookID;
	this->bookName = bookName;
	this->authorFirstName = authorFirstName;
	this->authorLastName = authorLastName;
	this->bookType = bookType;
};

int Book::getBookID()
{
	return bookID;
}

string Book::getBookName()
{
	return bookName;
}

string Book::getAuthorFirstName()
{
	return authorFirstName;
}

string Book::getAuthorLastName()
{
	return authorLastName;
}

Date Book::getDueDate()
{
	return dueDate;
}

void Book::setDueDate(Date dueDate)
{
	this->dueDate = dueDate;
}

void Book::returnBook()
{
	this->setDueDate(Date());
	this->borrower = NULL;
}

void Book::borrowBook(Member* borrower, Date dueDate)
{
	this->setDueDate(dueDate);
	this->borrower = borrower;
}

