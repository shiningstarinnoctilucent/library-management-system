#pragma once
#include "Person.h"

class Librarian : public Person
{
private:
	int staffId;
	int salary;
public:
	// Constructor
	Librarian();
	// Parameterized constructor
	Librarian(int staffId, string name, string address, string email, int salary);
	// Get staff ID
	int getStaffId();
	// Set staff ID
	void setStaffId(int staffId);
	// Get salary
	int getSalary();
	// Set salary
	void setSalary(int salary);
	// Add member
	void addMember();
	// Issue book
	void issueBook(int memberId, int bookId);
	// Return book
	void returnBook(int memberId, int bookId);
	// Display borrowed books
	void displayBorrowedBooks(int memberId);
	// Calculate fine
	void calcFine(int memberId);
};
