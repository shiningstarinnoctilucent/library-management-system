#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
// Date class
class Date
{
	// Friend declarations
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	// Functions that do not modify internal data can be marked as const

	// Copy constructor (fully default)
	Date(int year = 1949, int month = 10, int day = 1);

	// Print function
	void Print() const;

	// Overloaded == operator
	bool operator==(const Date& d) const;
	// Overloaded != operator
	bool operator!=(const Date& d) const;
	// Overloaded < operator
	bool operator<(const Date& d) const;
	// Overloaded <= operator
	bool operator<=(const Date& d) const;
	// Overloaded > operator
	bool operator>(const Date& d) const;
	// Overloaded >= operator
	bool operator>=(const Date& d) const;
	// Get the number of days in a specific month
	int GetMonthDay(int year, int month) const;
	// Overloaded += operator
	Date& operator+=(int day);
	// Overloaded + operator
	Date operator+(int day) const;
	// Overloaded -= operator
	Date& operator-=(int day);
	// Overloaded - operator
	Date operator-(int day) const;
	// Subtract one date from another
	int operator-(const Date& d) const;

private:
	int _year;  // Year
	int _month; // Month
	int _day;   // Day
};

// Stream insertion
ostream& operator<<(ostream& out, const Date& dt);

// Stream extraction
istream& operator>>(istream& in, Date& d);