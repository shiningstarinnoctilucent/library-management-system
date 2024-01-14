#pragma once
#include <string>
#include "Date.h"
class Member;

using namespace std;
class Book
{
private:
	// Book ID
	int bookID;
	// Book name
	string bookName;
	// Author's first name
	string authorFirstName;
	// Author's last name
	string authorLastName;
	// Book type
	string bookType;
	// Due date
	Date dueDate;
	// Borrower
	Member* borrower;
public:
	Book(int bookID, string bookName, string authorFirstName, string authorLastName, string bookType);
	int getBookID();
	string getBookName();
	string getAuthorFirstName();
	string getAuthorLastName();
	// Get due date
	Date getDueDate();
	void setDueDate(Date dueDate);
	// Return the book
	void returnBook();
	// Borrow the book
	void borrowBook(Member* borrower, Date dueDate);
};
