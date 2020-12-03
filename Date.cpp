#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

/* Date implementation */
// Constructor
Date::Date(string month0, int day0) : month(month0), day(day0) { }

/* Overload of >> operator to input the object in the following
format: Day:Month */
istream& operator>>(istream& in, Date& targetDate)
{
	in >> targetDate.day;

	if (in.peek() == ':') {
		in.ignore(1, ':');
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
	out << targetDate.month << " " << targetDate.day;
	return out;
}