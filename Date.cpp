#include <iostream>
#include <string>
#include <sstream>
#include "headers/Date.h"

using namespace std;

// Constructor
Date::Date(string month0, int day0) : month(month0), day(day0) { }

/* Overload of >> operator to input the object in the following
format: Day Month
Also used when reading from the file */
istream& operator>>(istream& in, Date& targetDate)
{
	in >> targetDate.day;

	if (in.peek() == ' ') {
		in.ignore(1, ' ');
		in >> targetDate.month;
	}

	else {
		in.setstate(ios_base::failbit);
	}

	if (targetDate.day < 0 || targetDate.day > 31) {
		in.setstate(ios_base::failbit);
	}

	return in;
}

/* Overloaded << operator with the simple spacing */
ostream& operator<<(std::ostream& out, const Date& targetDate)
{
	// Ostringstream is used to apply output formatting for the whole date,
	// not the first part of date input stream
	ostringstream tempDate;
	tempDate << targetDate.day << " " << targetDate.month;

	out << tempDate.str();
	return out;
}