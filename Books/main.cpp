#include <iostream>
#include <fstream>
#include <sstream>
#include "Member.h"
#include "Book.h"
#include "Librarian.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

// Librarian
Librarian librarians = Librarian(1, "Zhang San", "Haidian District, Beijing", "", 6000);

// Library members
vector<Member> members;

// Library books
vector<Book> books;

// System date
Date currentDate = Date(2024, 1, 10);

// Initialize books
void initBooks()
{
	// Define the path of the book CSV file
	string path = "C:/Users/ASUS/Desktop/library_books/library_books.csv";
	// Open the file
	ifstream file(path);

	if (file) {
		string line;
		// Ignore the first line which is the header
		getline(file, line);
		while (getline(file, line)) {
			stringstream ss(line);
			string bookIdStr, bookName, pageCount, authorFirstName, authorLastName, bookType;

			// Splitting the CSV line by comma
			getline(ss, bookIdStr, ',');
			getline(ss, bookName, ',');
			getline(ss, pageCount, ',');
			getline(ss, authorFirstName, ',');
			getline(ss, authorLastName, ',');
			getline(ss, bookType, ',');

			// Converting bookId from string to int
			int bookId = stoi(bookIdStr);

			// Creating Book object and storing it in the vector
			books.emplace_back(bookId, bookName, authorFirstName, authorLastName, bookType);
		}

		file.close(); // Closing the file after reading
	}
	else {
		cout << "Failed to open the file. The book data will be empty." << endl;
	}
}

// Check if a member exists based on memberId
bool isMemberExist(int memberId)
{
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].getMemberId() == memberId)
		{
			return true;
		}
	}
	return false;
}

// Get a member by memberId
Member* getMemberById(int memberId)
{
	Member* member = NULL;
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].getMemberId() == memberId)
		{
			member = &members[i];
		}
	}
	return member;
}

// Check if a book exists based on bookId
bool isBookExist(int bookId, vector<Book> books)
{
	for (int i = 0; i < books.size(); i++)
	{
		if (books[i].getBookID() == bookId)
		{
			return true;
		}
	}
	return false;
}

// Check if a book exists based on bookId
bool isBookExist(int bookId)
{
	return isBookExist(bookId, books);
}

// Get a book by bookId
Book* getBookById(int bookId)
{
	Book* book = NULL;
	for (int i = 0; i < books.size(); i++)
	{
		if (books[i].getBookID() == bookId)
		{
			book = &books[i];
		}
	}
	return book;
}

// Add a member
void Librarian::addMember()
{
	string name;
	string address;
	string email;
	cout << "Please enter the member's name: ";
	cin >> name;
	cout << "Please enter the member's address: ";
	cin >> address;
	cout << "Please enter the member's email: ";
	cin >> email;
	int memberId = members.size() + 1;
	members.emplace_back(memberId, name, address, email);
	Member* member = getMemberById(memberId);
	cout << "Member added successfully! Member information:" << endl << endl;
	cout << "Member ID: " << member->getMemberId() << "\tMember Name: " << member->getName() << "\tMember Address: " << member->getAddress() << "\tMember Email: " << member->getEmail() << endl;
}

// Issue a book to a member
void Librarian::issueBook(int memberId, int bookId)
{
	// Get the member
	Member* member = getMemberById(memberId);
	// Get the book
	Book* book = getBookById(bookId);
	// Set the due date for the book
	book->setDueDate(currentDate + 3);
	// Get the books borrowed by the member
	vector<Book> booksBorrowed = member->getBooksBorrowed();
	// Add the book to the borrowed books
	booksBorrowed.push_back(*book);
	// Set the borrowed books for the member
	member->setBooksBorrowed(booksBorrowed);
	book->borrowBook(member, currentDate + 3);
}

// Return a book
void Librarian::returnBook(int memberId, int bookId)
{
	// Get the member
	Member* member = getMemberById(memberId);
	// Get the book
	Book* book = getBookById(bookId);
	// Get the books borrowed by the member
	vector<Book> booksBorrowed = member->getBooksBorrowed();
	// Remove the borrowed book
	for (int i = 0; i < booksBorrowed.size(); i++)
	{
		if (booksBorrowed[i].getBookID() == bookId)
		{
			cout << "Book ID: " << booksBorrowed[i].getBookID() << "\tName: " << booksBorrowed[i].getBookName() << "\tAuthor: " << booksBorrowed[i].getAuthorFirstName() << " " << booksBorrowed[i].getAuthorLastName() << "\tDue Date:" << booksBorrowed[i].getDueDate() << endl;
			booksBorrowed.erase(booksBorrowed.begin() + i);
		}
	}
	// Set the borrowed books for the member
	member->setBooksBorrowed(booksBorrowed);
	book->returnBook();
	cout << "Book returned successfully for member " << member->getName() << "!" << endl;
}

// Display borrowed books
void Librarian::displayBorrowedBooks(int memberId)
{
	// Get the member
	Member* member = getMemberById(memberId);
	// Get the borrowed books by the member
	vector<Book> booksBorrowed = member->getBooksBorrowed();
	// Display the borrowed books
	cout << "Member ID: " << member->getMemberId() << "\tMember " << member->getName() << ", borrowed books:" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < booksBorrowed.size(); i++)
	{
		cout << "Book ID: " << booksBorrowed[i].getBookID() << "\tName: " << booksBorrowed[i].getBookName() << "\tAuthor: " << booksBorrowed[i].getAuthorFirstName() << " " << booksBorrowed[i].getAuthorLastName() << "\tDue Date:" << booksBorrowed[i].getDueDate() << endl;
	}
	cout << "------------------------------------------------------------------------------------------" << endl;
}

// Calculate fine for a member
void Librarian::calcFine(int memberId)
{
	// Get the member
	Member* member = getMemberById(memberId);
	// Get the borrowed books by the member
	vector<Book> booksBorrowed = member->getBooksBorrowed();
	// Calculate the fine
	int fine = 0;
	for (int i = 0; i < booksBorrowed.size(); i++)
	{
		if (booksBorrowed[i].getDueDate() < currentDate)
		{
			fine += (currentDate - booksBorrowed[i].getDueDate());
		}
	}
	// Display the fine
	cout << "Member ID: " << member->getMemberId() << "\tMember " << member->getName() << ", fine to be paid: " << fine << " pounds" << endl;
}

// Menu function
char menu() {
	char n[6];
	cout << "\n\nSystem Date: " << currentDate << "   Welcome to the Library Management System" << endl << endl
		<< "  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl
		<< "    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl
		<< "        * *     A       S 1:  Add Member                 A     * *" << endl
		<< "        * *    /.\\      S 2:  Issue Book                /.\\    * *" << endl
		<< "        * *   /..'\\     S 3:  Return Book              /..'\\   * *" << endl
		<< "        * *   /'.'\\     S 4:  Display Borrowed Books   /'.'\\   * *" << endl
		<< "        * *  /.''.'\\    S 5:  Calculate Fine          /.''.'\\  * *" << endl
		<< "        * *  /.'.'.\\    S 6:  Modify System Date      /.'.'.\\  * *" << endl
		<< "        * * /'.''.'.\\   S                            /'.''.'.\\ * *" << endl
		<< "        * * ^^^[_]^^^   S 0:  Exit System            ^^^[_]^^^ * *" << endl
		<< "    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl
		<< "  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl
		<< "Please enter [0-6] to make a selection: ";
	cin >> n;
	return(n[0]);
}

 //Main function
int main() {
	// Initialize books
	initBooks();
	char n;
	int	k = 1;
	while (k == 1)
	{
		n = menu();
		switch (n)
		{
		case '1': librarians.addMember();  break;
		case '2': {
			int issue = 1;
			int memberId;
			int bookId;
			while (issue == 1)
			{
				// Enter the member ID
				cout << "Please enter the member ID, enter '0' to return: ";
				cin >> memberId;
				// Check if returning to the menu
				if (memberId == 0) break;
				// Check if the member ID exists
				if (!isMemberExist(memberId))
				{
					cout << "The member does not exist. Please enter again!" << endl;
					continue;
				}
				else
				{
					issue = 0;
				}
			}
			if (memberId == 0) break;
			issue = 1;
			while (issue == 1)
			{
				// Enter the book ID
				cout << "Please enter the book ID, enter '0' to return: ";
				cin >> bookId;
				// Check if returning to the menu
				if (bookId == 0) break;
				// Check if the book ID exists
				if (!isBookExist(bookId)) {
					cout << "The book does not exist. Please enter again!" << endl;
					continue;
				}
				else
				{
					issue = 0;
				}
			}
			if (bookId == 0) break;
			librarians.issueBook(memberId, bookId);
			break;
		}
		case '3': {
			int issue = 1;
			int memberId;
			int bookId;
			while (issue == 1)
			{
				// Enter the member ID
				cout << "Please enter the member ID, enter '0' to return: ";
				cin >> memberId;
				// Check if returning to the menu
				if (memberId == 0) break;
				// Check if the member ID exists
				if (!isMemberExist(memberId))
				{
					cout << "The member does not exist. Please enter again!" << endl;
					continue;
				}
				else
				{
					issue = 0;
				}
			}
			if (memberId == 0) break;
			issue = 1;
			while (issue == 1)
			{
				// Enter the book ID
				cout << "Please enter the book ID, enter '0' to return: ";
				cin >> bookId;
				// Check if returning to the menu
				if (bookId == 0) break;
				// Check if the book ID exists
				if (!isBookExist(bookId)) {
					cout << "The book does not exist. Please enter again!" << endl;
					continue;
				}
				if (!isBookExist(bookId, getMemberById(memberId)->getBooksBorrowed()))
				{
					cout << "The member has not borrowed this book. Please enter again!" << endl;
					continue;
				}
				else
				{
					issue = 0;
				}
			}
			if (bookId == 0) break;
			librarians.returnBook(memberId, bookId);
			break;
		}
		case '4': {
			int issue = 1;
			int memberId;
			while (issue == 1)
			{
				// Enter the member ID
				cout << "Please enter the member ID, enter '0' to return: ";
				cin >> memberId;
				// Check if returning to the menu
				if (memberId == 0) break;
				// Check if the member ID exists
				if (!isMemberExist(memberId))
				{
					cout << "The member does not exist. Please enter again!" << endl;
					continue;
				}
				else
				{
					issue = 0;
				}
			}
			if (memberId == 0) break;
			librarians.displayBorrowedBooks(memberId);
			break;
		}
		case '5': {
			int issue = 1;
			int memberId;
			while (issue == 1)
			{
				// Enter the member ID
				cout << "Please enter the member ID, enter '0' to return: ";
				cin >> memberId;
				// Check if returning to the menu
				if (memberId == 0) break;
				// Check if the member ID exists
				if (!isMemberExist(memberId))
				{
					cout << "The member does not exist. Please enter again!" << endl;
					continue;
				}
				else
				{
					issue = 0;
				}
			}
			if (memberId == 0) break;
			librarians.calcFine(memberId);
			break;
		}
		case '6': {
			cout << "Please enter the system date, for example: 2024 1 4: ";
			cin >> currentDate;
			cout << "System date modified successfully!" << endl;
			break;
		}
		case '0':
			k = 0;
			break;
		default:
			cout << "Input error. Please enter a number between 0 and 6!" << endl;
			break;
		}
	}
	return 0;
}

TEST_CASE("Librarian::addMember", "[Librarian]") {
	Librarian librarian(1, "Zhang San", "Haidian District, Beijing", "", 6000);

	// Call the addMember method
	librarian.addMember();

	// Check if the member is added successfully (you may need to modify this based on your implementation)
	REQUIRE(members.size() > 0);
}

TEST_CASE("Librarian::issueBook", "[Librarian]") {
	// Set up initial state with a member and a book
	members.emplace_back(1, "John Doe", "123 Main St", "john@example.com");
	books.emplace_back(1, "The Catcher in the Rye", "J.D.", "Salinger", "Fiction");
	Librarian librarian(1, "Zhang San", "Haidian District, Beijing", "", 6000);

	// Call the issueBook method
	librarian.issueBook(1, 1);

	// Check if the book is issued successfully (you may need to modify this based on your implementation)
	REQUIRE(members[1].getBooksBorrowed().size() > 0);
}

TEST_CASE("Librarian::returnBook", "[Librarian]") {
	// Set up initial state with a member, a book, and the book being borrowed
	members.emplace_back(1, "John Doe", "123 Main St", "john@example.com");
	books.emplace_back(1, "The Catcher in the Rye", "J.D.", "Salinger", "Fiction");
	Librarian librarian(1, "Zhang San", "Haidian District, Beijing", "", 6000);
	librarian.issueBook(1, 1);

	// Call the returnBook method
	librarian.returnBook(1, 1);

	// Check if the book is returned successfully (you may need to modify this based on your implementation)
	REQUIRE(members[0].getBooksBorrowed().size() == 0);
}