#pragma once
#include <vector>
#include "Person.h"
class Book;

using namespace std;

class Member:public Person
{
private:
	// Member ID
	int memberId;
	// Books loaned by the member
	vector<Book> booksLoaned;
public:
	Member() = default;
	// Constructor
	Member(int memberId, string name, string address, string email);
	int getMemberId();
	// Get the books borrowed by the member
	vector<Book> getBooksBorrowed();
	// Set the books borrowed by the member
	void setBooksBorrowed(vector<Book> book);

};
