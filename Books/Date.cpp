#include"Date.h"

// Copy constructor (default)
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

// Print function
void Date::Print() const
{
	cout << _year << "/" << _month << "/" << _day << endl;
}

// Overload == operator
bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

// Overload != operator
bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}

// Overload < operator
bool Date::operator<(const Date& d) const
{
	if (_year < d._year)
	{
		return true;
	}
	else if (_year == d._year && _month < d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day < d._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Overload <= operator
bool Date::operator<=(const Date& d) const
{
	return *this == d || *this < d;
}

// Overload > operator
bool Date::operator>(const Date& d) const
{
	return !(*this <= d);
}

// Overload >= operator
bool Date::operator>=(const Date& d) const
{
	return !(*this < d);
}

// Get the number of days in a specific month
int Date::GetMonthDay(int year, int month) const
{
	const static int MonthArray[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2
		&& (year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return 29;
	}
	return MonthArray[month];
}

// Overload += operator
Date& Date::operator+=(int day)
{
	_day += day;
	// Check the validity of the day
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;  // Carry over to the next month
		if (_month == 13)
		{
			++_year;   // Carry over to the next year
			_month = 1;
		}
	}
	return *this;
}

// Overload + operator
Date Date::operator+(int day) const
{
	// Create a new Date object
	Date tmp(*this);
	tmp += day;
	return tmp;
}

// Overload -= operator
Date& Date::operator-=(int day)
{
	_day -= day;
	while (_day <= 0)
	{
		// Borrow from the previous month
		--_month;
		if (_month == 0)
		{
			// Borrow from the previous year
			--_year;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

// Overload - operator
Date Date::operator-(int day) const
{
	Date tmp(*this);
	tmp -= day;
	return tmp;
}

// Insertion operator for output stream
ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "/" << d._month << "/" << d._day;
	return out;
}

// Extraction operator for input stream
istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

// Subtract one date from another
int Date::operator-(const Date& d) const
{
	// Determine which date is larger
	Date max = *this;
	Date min = d;
	int flag = 1; // Default is positive

	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}

	// n records the number of days
	int n = 0;
	while (max != min)
	{
		// Pre-increment is more efficient
		min += 1;
		n++;
	}

	return n * flag;
}
